#include "NoUnnamedInnerStruct202328015059001Check.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include <iostream>

using namespace std;
using namespace clang::ast_matchers;

namespace clang::tidy::ucassaat {
void NoUnnamedInnerStruct202328015059001Check::registerMatchers(MatchFinder *Finder) {
    Finder->addMatcher(
        recordDecl(
            isDefinition(),
            unless(isUnion()),
            hasDeclContext(recordDecl(isDefinition())) // Nested in another struct
        ).bind("unnamedInnerStruct"),
        this);
}

void NoUnnamedInnerStruct202328015059001Check::check(const MatchFinder::MatchResult &Result) {
    const auto *RD = Result.Nodes.getNodeAs<RecordDecl>("unnamedInnerStruct");
    if (RD && !RD->isAnonymousStructOrUnion()) {
        const auto *Parent = dyn_cast_or_null<RecordDecl>(RD->getParent());
        if (Parent) {
            bool isFieldPresent = false;
            for (const auto &Field : Parent->fields()) {
                if (const auto *FieldType = Field->getType()->getAsTagDecl()) {
                    if (FieldType == RD) {
                        isFieldPresent = true;
                        break;
                    }
                }
            }

            if (!isFieldPresent) {
                std::string ParentName = Parent->getNameAsString();
                diag(RD->getBeginLoc(), "struct '%0' in struct '%1' is unnamed", DiagnosticIDs::Level::Error)
                    << RD->getNameAsString() << ParentName;
            }
        }
    }
}

} // namespace clang::tidy::ucassaat
