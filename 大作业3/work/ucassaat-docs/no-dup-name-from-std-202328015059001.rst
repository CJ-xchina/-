.. title:: clang-tidy - NoDupNameFromStd202328015059001Check

NoDupNameFromStd202328015059001Check
====================================

FIXME: Describe what patterns does the check detect and why. Give examples.


**目的：**

`NoDupNameFromStd202328015059001Check`设计用于防止使用与标准库名称（如`cin`、`cout`和`endl`）冲突的变量名。此检查确保函数中的局部变量名称不会与常用的标准库名称重叠，这可能导致混淆和错误。

**实现：**

1. **匹配器注册（Matcher Registration）：**
   在`registerMatchers`函数中，检查器使用clang的AST匹配器（`ast_matchers`）匹配函数体内的变量声明（`varDecl`）。

   - 使用`varDecl`匹配变量声明。
   - 使用`hasAncestor`确保变量位于函数体内。

2. **检查器逻辑（Checker Logic）：**
   在`check`函数中，首先检查匹配结果是否有效。然后，它检索匹配到的变量声明节点。提取变量的名称，并将其与禁止名称列表（如`cin`、`cout`和`endl`）进行比较。

3. **错误诊断（Error Diagnostic）：**
   如果变量名与禁止列表中的名称相匹配，则使用`diag`方法在源代码中的变量声明位置报告一个错误，错误信息为“变量'%0'的名称与std中的名称重复”，错误级别为`DiagnosticIDs::Level::Error`。

例如，在下面的代码中：

.. code:: cpp

    int main(void) {
        unsigned int cin = 0;
        unsigned int cout = 1;
        unsigned int endl = 2;
        return 0;
    }

函数`main`中的变量声明违反了规则，因为它使用了与标准库`std`中名称相同的`cout`。这个变量声明将被`NoDupNameFromStd202328015059001Check`检查器标记为错误。这是因为该检查器旨在防止与标准库名称的冲突，以避免潜在的混淆和错误。
