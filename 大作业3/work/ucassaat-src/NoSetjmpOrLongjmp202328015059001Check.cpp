//===--- NoSetjmpOrLongjmp202328015059001Check.cpp - clang-tidy -----------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "NoSetjmpOrLongjmp202328015059001Check.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Basic/SourceLocation.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Lex/PreprocessorOptions.h"
#include "clang/Sema/Sema.h"
#include <iostream>

using namespace std;
using namespace clang::ast_matchers;

namespace clang::tidy::ucassaat {

void NoSetjmpOrLongjmp202328015059001Check::registerMatchers(MatchFinder *Finder) {
  // 使用 ASTMatchers 注册我们的匹配规则
  Finder->addMatcher(
      stmt(anyOf(
          callExpr(callee(functionDecl(hasName("_setjmp")))).bind("setjmpCall"),
          callExpr(callee(functionDecl(hasName("longjmp")))).bind("longjmpCall")
          // 可以在这里添加其他上下文的匹配器
      )),
      this);
}

void NoSetjmpOrLongjmp202328015059001Check::check(
    const MatchFinder::MatchResult &Result) {
  if (const auto *SetjmpCall = Result.Nodes.getNodeAs<CallExpr>("setjmpCall")) {
    cout << "find setjmp" << endl;
    SourceLocation CallLoc = SetjmpCall->getBeginLoc();
    diag(CallLoc, "Prohibit the use of setjmp function here", DiagnosticIDs::Level::Error);
  }

  if (const auto *LongjmpCall = Result.Nodes.getNodeAs<CallExpr>("longjmpCall")) {
    cout << "find longjmp" << endl;
    SourceLocation CallLoc = LongjmpCall->getBeginLoc();
    diag(CallLoc, "Prohibit the use of longjmp function here", DiagnosticIDs::Level::Error);
  }
}

} // namespace clang::tidy::ucassaat
