//===--- NoRegisterVar202328015059001Check.cpp - clang-tidy ---------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "NoRegisterVar202328015059001Check.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "../utils/Matchers.h"
#include <clang/ASTMatchers/ASTMatchers.h>
using namespace clang::ast_matchers;


namespace clang::tidy::ucassaat {

void NoRegisterVar202328015059001Check::registerMatchers(MatchFinder *Finder) {
  // FIXME: Add matchers.
    Finder->addMatcher(varDecl().bind("registerVar"), this);
}

void NoRegisterVar202328015059001Check::check(const MatchFinder::MatchResult &Result) {
  // FIXME: Add callback implementation.
    if (const auto *Var = Result.Nodes.getNodeAs<VarDecl>("registerVar")) {
        if (Var->getStorageClass() == SC_Register) {
            diag(Var->getLocation(), "using register variable %0") << Var;
        }
    }
}

} // namespace clang::tidy::ucassaat
