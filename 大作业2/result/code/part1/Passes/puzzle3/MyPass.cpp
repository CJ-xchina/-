
// MyPass.cpp
#include "llvm/IR/PassManager.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"

using namespace llvm;

namespace
{

    struct RaceVariablePass : public PassInfoMixin<RaceVariablePass>
    {

        void instrumentLoad(LoadInst *LI, LLVMContext *C)
        {
            // 插桩load指令的逻辑
            IRBuilder<> Builder(LI);
            auto *Address = Builder.CreateBitCast(LI->getPointerOperand(), Type::getInt8PtrTy(*C));
            auto *VariableName = Builder.CreateGlobalStringPtr(LI->getPointerOperand()->getName());
            std::vector<Value *> Args = {Address, VariableName, Builder.getInt1(false)};

            FunctionCallee RecordAccessFunc = LI->getModule()->getOrInsertFunction("accessVariable", Type::getVoidTy(*C), Type::getInt8PtrTy(*C), Type::getInt8PtrTy(*C));
            Builder.CreateCall(RecordAccessFunc, Args);
        }

        void instrumentStore(StoreInst *SI, LLVMContext *C)
        {
            // 插桩store指令的逻辑
            IRBuilder<> Builder(SI);
            auto *Address = Builder.CreateBitCast(SI->getPointerOperand(), Type::getInt8PtrTy(*C));
            auto *VariableName = Builder.CreateGlobalStringPtr(SI->getPointerOperand()->getName());
            std::vector<Value *> Args = {Address, VariableName, Builder.getInt1(true)};

            FunctionCallee RecordAccessFunc = SI->getModule()->getOrInsertFunction("accessVariable", Type::getVoidTy(*C), Type::getInt8PtrTy(*C), Type::getInt8PtrTy(*C));
            Builder.CreateCall(RecordAccessFunc, Args);
        }

        void handleMutex(CallInst *CI, LLVMContext *C)
        {
            Function *CalledFunction = CI->getCalledFunction();
            if (CalledFunction == nullptr || CalledFunction->getName().empty())
            {
                return;
            }

            // 检测函数是否为pthread的锁操作
            std::string FunctionName = CalledFunction->getName().str();
            if (FunctionName == "pthread_mutex_lock" || FunctionName == "pthread_mutex_unlock")
            {
                IRBuilder<> Builder(CI);
                auto *LockAddress = CI->getArgOperand(0);
                Value *Args[] = {LockAddress};

                std::string FuncName = (FunctionName == "pthread_mutex_lock") ? "lockVariable" : "unlockVariable";
                FunctionCallee MutexFunc = CI->getModule()->getOrInsertFunction(FuncName, Type::getVoidTy(*C), Type::getInt8PtrTy(*C));
                Builder.CreateCall(MutexFunc, Args);
            }
        }

        PreservedAnalyses run(Module &M, ModuleAnalysisManager &)
        {
            for (auto &F : M)
            {
                for (auto &B : F)
                {
                    for (auto &I : B)
                    {
                        if (auto *LoadInstruction = dyn_cast<LoadInst>(&I))
                        {
                            instrumentLoad(LoadInstruction, &M.getContext());
                        }
                        else if (auto *StoreInstruction = dyn_cast<StoreInst>(&I))
                        {
                            instrumentStore(StoreInstruction, &M.getContext());
                        }
                        else if (auto *CallInstruction = dyn_cast<CallInst>(&I))
                        {
                            handleMutex(CallInstruction, &M.getContext());
                        }
                    }
                }
                if (F.getName() == "main")
                {
                    FunctionCallee TestHello;
                    FunctionCallee endShow;
                    auto &M = *F.getParent();
                    AttributeList Attr;
                    Attr = Attr.addFnAttribute(M.getContext(), Attribute::NoUnwind);
                    IRBuilder<>
                        IRB(M.getContext());

                    // 查找符号名为printHello，返回值类型为void，参数列表类型为[void*]的函数，注册到TestHello中
                    endShow = F.getParent()->getOrInsertFunction("reportRaceVariables", Attr, IRB.getVoidTy(), IRB.getVoidTy());
                    // Insert a call to "instrumentBasicBlocks" at the end of the function
                    IRBuilder<> EndIRB(&F.back());
                    EndIRB.SetInsertPoint(&F.back().back());
                    EndIRB.CreateCall(endShow, {});
                }
            }
            return PreservedAnalyses::all();
        }
    };

} // end anonymous namespace
PassPluginLibraryInfo getPassPluginInfo()
{
    const auto Callback = [](PassBuilder &PB)
    {
        PB.registerPipelineStartEPCallback(
            [&](ModulePassManager &MPM, auto)
            {
                MPM.addPass(RaceVariablePass());
            });
    };
    return {LLVM_PLUGIN_API_VERSION, "RaceVariablePass", "1.0", Callback};
}

extern "C" LLVM_ATTRIBUTE_WEAK PassPluginLibraryInfo llvmGetPassPluginInfo()
{
    return getPassPluginInfo();
}
