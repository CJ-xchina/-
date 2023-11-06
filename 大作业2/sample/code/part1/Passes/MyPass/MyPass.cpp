#include "llvm/IR/PassManager.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"
#include <iostream>
using namespace llvm;

namespace
{
  struct MyPass : public PassInfoMixin<MyPass>
  {
    PreservedAnalyses run(Function &F, FunctionAnalysisManager &FAM)
    {
      if (F.getName() != "printHello")
      {
        FunctionCallee TestHello;
        auto &M = *F.getParent();
        AttributeList Attr;
        Attr = Attr.addFnAttribute(M.getContext(), Attribute::NoUnwind);
        IRBuilder<>
            IRB(M.getContext());

        // 查找符号名为printHello，返回值类型为void，参数列表类型为[void*]的函数，注册到TestHello中
        TestHello = F.getParent()->getOrInsertFunction("printHello", Attr, IRB.getVoidTy(), IRB.getInt8PtrTy());

        // 调整插入点至函数入口
        IRB.SetInsertPoint(&F.getEntryBlock(), F.getEntryBlock().getFirstInsertionPt());

        // 插入对IRB.getVoidTy()的函数调用，并传递一个函数参数（此处参数值为NULL）
        IRB.CreateCall(TestHello, {IRB.CreateBitOrPointerCast(IRB.getInt8(0), IRB.getInt8PtrTy())});
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
