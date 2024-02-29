#include "NoCompareOnPointerTypes202328015059001Check.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include <iostream>

using namespace std;
using namespace clang::ast_matchers;

namespace clang::tidy::ucassaat {

void NoCompareOnPointerTypes202328015059001Check::registerMatchers(MatchFinder *Finder) {
    // 匹配所有的二元比较操作符
    Finder->addMatcher(
        binaryOperator(
            anyOf(hasOperatorName(">"), hasOperatorName(">="), 
                  hasOperatorName("<"), hasOperatorName("<=")),
            anyOf(
                hasLHS(expr(anyOf(hasType(pointerType()), hasType(pointsTo(pointerType()))))),
                hasRHS(expr(anyOf(hasType(pointerType()), hasType(pointsTo(pointerType())))))
            )
        ).bind("ptr-compare"), this);
}

void NoCompareOnPointerTypes202328015059001Check::check(const MatchFinder::MatchResult &Result) {
    const auto *BinOp = Result.Nodes.getNodeAs<BinaryOperator>("ptr-compare");
    if (!BinOp)
        return;
    auto lhsType = BinOp->getLHS()->getType().getCanonicalType();
    auto rhsType = BinOp->getRHS()->getType().getCanonicalType();

    // 检查是否两边都是指针类型
    if (lhsType->isPointerType() && rhsType->isPointerType()) {
        diag(BinOp->getBeginLoc(), "Prohibit pointer comparisons", DiagnosticIDs::Level::Error);
    }
}

} // namespace clang::tidy::ucassaat
