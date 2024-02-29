#include "llvm/IR/PassManager.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/IRBuilder.h"

#include <unordered_set>
#include <iostream>
using namespace llvm;

namespace
{

  struct MyPass : public PassInfoMixin<MyPass>
  {
    uint32_t num = 0;
    PreservedAnalyses run(Function &F, FunctionAnalysisManager &FAM)
    {
      FunctionCallee TestHello;
      FunctionCallee endShow;
      auto &M = *F.getParent();
      AttributeList Attr;
      Attr = Attr.addFnAttribute(M.getContext(), Attribute::NoUnwind);
      IRBuilder<>
          IRB(M.getContext());

      // 查找符号名为printHello，返回值类型为void，参数列表类型为[void*]的函数，注册到TestHello中
      TestHello = F.getParent()->getOrInsertFunction("instrumentBasicBlocks", Attr, IRB.getVoidTy(), IRB.getInt32Ty());
      endShow = F.getParent()->getOrInsertFunction("printBasicBlockCoverage", Attr, IRB.getVoidTy(), IRB.getInt32Ty());
      for (BasicBlock &BB : F)
      {
        num += 1;
        IRBuilder<> IRB(&BB);
        IRB.SetInsertPoint(&BB, BB.getFirstInsertionPt());
        IRB.CreateCall(TestHello, {IRB.getInt32(num)});
      }
      if (F.getName() == "main")
      {
        // Insert a call to "instrumentBasicBlocks" at the end of the function
        IRBuilder<> EndIRB(&F.back());
        EndIRB.SetInsertPoint(&F.back().back());
        EndIRB.CreateCall(endShow, {IRB.getInt32(num)});
      }
      return PreservedAnalyses::all();
    }
  };

} // end anonymous namespace

PassPluginLibraryInfo getPassPluginInfo()
{
  const auto callback = [](PassBuilder &PB)
  {
    PB.registerPipelineEarlySimplificationEPCallback(
        [&](ModulePassManager &MPM, auto)
        {
          MPM.addPass(createModuleToFunctionPassAdaptor(MyPass()));
          return true;
        });
  };

  return {LLVM_PLUGIN_API_VERSION, "name", "0.0.1", callback};
};

extern "C" LLVM_ATTRIBUTE_WEAK PassPluginLibraryInfo llvmGetPassPluginInfo()
{
  return getPassPluginInfo();
}