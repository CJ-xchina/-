#include "TooManyNestedLevelsOfStruct202328015059001Check.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include <iostream>
using namespace clang::ast_matchers;

namespace clang::tidy::ucassaat {


void TooManyNestedLevelsOfStruct202328015059001Check::registerMatchers(MatchFinder *Finder) {
Finder->addMatcher(recordDecl(isStruct(),
        unless(hasAncestor(recordDecl(isStruct())))).bind("struct"), this);
}

void TooManyNestedLevelsOfStruct202328015059001Check::check(const MatchFinder::MatchResult &Result) {
    const auto *Struct = Result.Nodes.getNodeAs<RecordDecl>("struct");
    if (!Struct || !Struct->isThisDeclarationADefinition())
      return;

    // Function to recursively check the nesting level of structs
    std::function<void(const RecordDecl *, int, const RecordDecl *)> checkNestingLevel =
        [&](const RecordDecl *RD, int level, const RecordDecl *violatingStruct)
    {
      if (level > 3) {
        diag(RD->getLocation(), "too many nested levels of struct %0 (expected <= 3, actual %1)")
        << RD << level;
      }
      for (const auto *Field : RD->fields()) {
        if (const auto *FieldRD = Field->getType()->getAsRecordDecl()) {
          checkNestingLevel(FieldRD, level + 1, violatingStruct);
        }
      }
    };

    checkNestingLevel(Struct, 1, Struct);
}

} // namespace clang::tidy::ucassaat
