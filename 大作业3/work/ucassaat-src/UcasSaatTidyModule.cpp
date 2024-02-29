    //===------- UcasSaatTidyModule.cpp - clang-tidy --------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "../ClangTidy.h"
#include "../ClangTidyModule.h"
#include "../ClangTidyModuleRegistry.h"
#include "HelloWorldCheck.h"
#include "HelloWorldCheck.h"
#include "NoCompareOnPointerTypes202328015059001Check.h"
#include "NoDupNameFromStd202328015059001Check.h"
#include "NoRegisterVar202328015059001Check.h"
#include "NoSetjmpOrLongjmp202328015059001Check.h"
#include "NoUnnamedInnerStruct202328015059001Check.h"
#include "NoVoidPointer202328015059001Check.h"
#include "TooManyNestedLevelsOfStruct202328015059001Check.h"
using namespace clang::ast_matchers;

namespace clang::tidy {
namespace ucassaat {

class UcasSaatModule : public ClangTidyModule {
public:
  void addCheckFactories(ClangTidyCheckFactories &CheckFactories) override {
    CheckFactories.registerCheck<HelloWorldCheck>(
        "ucassaat-hello-world");
    CheckFactories.registerCheck<NoCompareOnPointerTypes202328015059001Check>(
        "ucassaat-no-compare-on-pointer-types-202328015059001");
    CheckFactories.registerCheck<NoDupNameFromStd202328015059001Check>(
        "ucassaat-no-dup-name-from-std-202328015059001");
    CheckFactories.registerCheck<NoRegisterVar202328015059001Check>(
        "ucassaat-no-register-var-202328015059001");
    CheckFactories.registerCheck<NoSetjmpOrLongjmp202328015059001Check>(
        "ucassaat-no-setjmp-or-longjmp-202328015059001");
    CheckFactories.registerCheck<NoUnnamedInnerStruct202328015059001Check>(
        "ucassaat-no-unnamed-inner-struct-202328015059001");
    CheckFactories.registerCheck<NoVoidPointer202328015059001Check>(
        "ucassaat-no-void-pointer-202328015059001");
    CheckFactories.registerCheck<TooManyNestedLevelsOfStruct202328015059001Check>(
        "ucassaat-too-many-nested-levels-of-struct-202328015059001");
  }
};

// Register the UcasSaatModule using this statically initialized variable.
static ClangTidyModuleRegistry::Add<UcasSaatModule> X("ucassaat-module",
                                                      "Add ucassaat checks.");

} // namespace ucassaat

// This anchor is used to force the linker to link in the generated object file
// and thus register the UcasSaatModule.
volatile int UcasSaatModuleAnchorSource = 0;

} // namespace clang::tidy
