#include "NoVoidPointer202328015059001Check.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang::tidy::ucassaat {

void NoVoidPointer202328015059001Check::registerMatchers(MatchFinder *Finder) {
    // 匹配 void* 类型的裸指针或其别名
    Finder->addMatcher(
        varDecl(hasType(pointsTo(voidType()))).bind("voidPointerVar"),
        this);

    // 匹配将指针转换为 void* 类型或其别名的 static_cast 表达式
    Finder->addMatcher(
        cxxStaticCastExpr(hasDestinationType(pointsTo(voidType()))).bind("staticCastToVoid"),
        this);
}

void NoVoidPointer202328015059001Check::check(const MatchFinder::MatchResult &Result) {
    if (const auto *VD = Result.Nodes.getNodeAs<VarDecl>("voidPointerVar")) {
        diag(VD->getBeginLoc(), "using void pointer type [ucassaat-no-void-pointer]");
    } else if (const auto *CE = Result.Nodes.getNodeAs<CXXStaticCastExpr>("staticCastToVoid")) {
        // 只在 static_cast 表达式的开始位置生成警告
        SourceLocation BeginLoc = CE->getBeginLoc();
        if (BeginLoc.isValid()) {
            diag(BeginLoc, "using void pointer type [ucassaat-no-void-pointer]");
        }
    }
}

} // namespace clang::tidy::ucassaat
