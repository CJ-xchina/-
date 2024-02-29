.. title:: clang-tidy - TooManyNestedLevelsOfStruct202328015059001Check

TooManyNestedLevelsOfStruct202328015059001Check
===============================================

FIXME: Describe what patterns does the check detect and why. Give examples.

**目的：**

`TooManyNestedLevelsOfStruct202328015059001Check`检查器的目的是在C++代码中识别并报告结构体嵌套层数超过3层的情况。

**实现：**

1. **匹配器注册（Matcher Registration）：**
   在`registerMatchers`函数中，检查器使用clang的AST匹配器（`ast_matchers`）匹配定义的结构体，且这些结构体不是另一个结构体的直接子元素。

   - 使用`recordDecl(isStruct(), unless(hasAncestor(recordDecl(isStruct()))))`匹配顶层结构体声明。

2. **检查器逻辑（Checker Logic）：**
   在`check`函数中，首先检查是否存在名为`struct`的结构体声明节点。如果存在，则递归地检查该结构体及其嵌套结构体的层数。

   - 使用递归函数`checkNestingLevel`来计算嵌套层数并检查是否超出了预定的限制（例如，超过3层）。

3. **错误诊断（Error Diagnostic）：**
   如果检测到结构体嵌套层数超过了限制（在这个例子中是3层），检查器会在源代码中的相应位置报告一个错误，错误信息为“too many nested levels of struct %0 (expected <= 3, actual %1)”。

**示例：**

在下面的代码中：

.. code:: cpp

    struct A {
        int num1;
        struct B {
            int num2;
            struct C {
                int num3;
                // struct D 违背规则
                struct D {
                    int num4;
                } d;
            } c;
        } b;
    };

`struct A `结构体中嵌套了太多层级的结构体，违反了规则。`struct D`结构体是第四层嵌套，超过了限制。这个情况将被`TooManyNestedLevelsOfStruct202328015059001Check`检查器标记为错误。这是因为该检查器旨在鼓励开发者减少结构体的嵌套层数，以提高代码的可读性和可维护性。
