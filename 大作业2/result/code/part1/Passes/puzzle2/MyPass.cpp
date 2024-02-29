// MyPass.cpp
#include "llvm/IR/PassManager.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Module.h"

using namespace llvm;

namespace
{

  struct SharedVariablePass : public PassInfoMixin<SharedVariablePass>
  {
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
          endShow = F.getParent()->getOrInsertFunction("reportSharedVariables", Attr, IRB.getVoidTy(), IRB.getVoidTy());
          // Insert a call to "instrumentBasicBlocks" at the end of the function
          IRBuilder<> EndIRB(&F.back());
          EndIRB.SetInsertPoint(&F.back().back());
          EndIRB.CreateCall(endShow, {});
        }
      }
      return PreservedAnalyses::all();
    }

  private:
    void instrumentLoad(LoadInst *LI, LLVMContext *C)
    {
      // 插桩load指令的逻辑
      IRBuilder<> Builder(LI);
      auto *Address = Builder.CreateBitCast(LI->getPointerOperand(), Type::getInt8PtrTy(*C));
      auto *VariableName = Builder.CreateGlobalStringPtr(LI->getPointerOperand()->getName());
      std::vector<Value *> Args = {Address, VariableName};

      FunctionCallee RecordAccessFunc = LI->getModule()->getOrInsertFunction("recordAccess", Type::getVoidTy(*C), Type::getInt8PtrTy(*C), Type::getInt8PtrTy(*C));
      Builder.CreateCall(RecordAccessFunc, Args);
    }

    void instrumentStore(StoreInst *SI, LLVMContext *C)
    {
      // 插桩store指令的逻辑
      IRBuilder<> Builder(SI);
      auto *Address = Builder.CreateBitCast(SI->getPointerOperand(), Type::getInt8PtrTy(*C));
      auto *VariableName = Builder.CreateGlobalStringPtr(SI->getPointerOperand()->getName());
      std::vector<Value *> Args = {Address, VariableName};

      FunctionCallee RecordAccessFunc = SI->getModule()->getOrInsertFunction("recordAccess", Type::getVoidTy(*C), Type::getInt8PtrTy(*C), Type::getInt8PtrTy(*C));
      Builder.CreateCall(RecordAccessFunc, Args);
    }
  };

} // end anonymous namespace

PassPluginLibraryInfo getPassPluginInfo()
{
  const auto callback = [](PassBuilder &PB)
  {
    PB.registerPipelineStartEPCallback(
        [&](ModulePassManager &MPM, auto)
        {
          MPM.addPass(SharedVariablePass());
          return true;
        });
  };

  return {LLVM_PLUGIN_API_VERSION, "SharedVariablePass", "1.0", callback};
};

extern "C" LLVM_ATTRIBUTE_WEAK PassPluginLibraryInfo llvmGetPassPluginInfo()
{
  return getPassPluginInfo();
}