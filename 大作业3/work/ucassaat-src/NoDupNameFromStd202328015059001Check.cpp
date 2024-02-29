//===--- NoDupNameFromStd202328015059001Check.cpp - clang-tidy ------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "NoDupNameFromStd202328015059001Check.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/AST/Decl.h"


using namespace clang::ast_matchers;
namespace clang::tidy::ucassaat {

void NoDupNameFromStd202328015059001Check::registerMatchers(MatchFinder *Finder) {
  // Match var declarations inside function bodies.
  Finder->addMatcher(
      varDecl(hasAncestor(functionDecl())).bind("var"), this);
}

void NoDupNameFromStd202328015059001Check::check(const MatchFinder::MatchResult &Result) {
  const auto *Var = Result.Nodes.getNodeAs<VarDecl>("var");
  if (Var) {
    StringRef Name = Var->getName();
    if (Name == "cin" || Name == "cout" || Name == "endl") {
      diag(Var->getLocation(), "Variable '%0' has duplicate name from std", DiagnosticIDs::Level::Error)
          << Name ;
    }
  }
}


} // namespace clang::tidy::ucassaat
