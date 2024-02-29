.. title:: clang-tidy - ucassaat-no-compare-on-pointer-types-202328015059001

ucassaat-no-compare-on-pointer-types-202328015059001
====================================================

FIXME: Describe what patterns does the check detect and why. Give examples.

**实现思路：**

1. **Matcher Registration（匹配器注册）：**
   在\ ``registerMatchers``\ 函数中，通过使用clang的AST匹配器（\ ``ast_matchers``\ ）来匹配所有的二元比较操作符（如\ ``>``\ 、\ ``>=``\ 、\ ``<``\ 、\ ``<=``\ ）。匹配的条件是，其中一个操作数是指针类型或指向指针类型的类型。

   -  使用\ ``binaryOperator``\ 匹配二元操作符。
   -  使用\ ``hasOperatorName``\ 匹配操作符的名称（比较操作符）。
   -  使用\ ``hasType``\ 匹配指针类型。
   -  使用\ ``pointsTo``\ 匹配指向指针类型的类型。

2. **Checker Logic（检查器逻辑）：**
   在\ ``check``\ 函数中，首先检查匹配结果是否为空，如果为空则返回。然后，获取匹配到的二元操作节点。接着，获取操作的左操作数（LHS）和右操作数（RHS）的类型，并将它们转换为规范类型（Canonical
   Type）。
3. **Error Diagnostic（错误诊断）：**
   最后，检查是否左操作数和右操作数都是指针类型。如果是，就使用\ ``diag``\ 方法在源代码中的二元操作符位置报告一个错误，错误信息为”Prohibit
   pointer comparisons”，错误级别为\ ``DiagnosticIDs::Level::Error``\ 。

例如在下面代码中：

.. code:: cpp

   int fsub(int *a,  int *b) {
       int sub = 0;
       // 违背规则：比较指针类型
       if (a > b) {
           sub = *a - *b;
       }
       // 违背规则：比较指针类型
       else if (*a < b) {
           sub = 0;
       }
       return sub;
   }

函数\ ``fsub``\ 包含了两个违反规则的比较操作，即比较指针类型（\ ``a``\ 和\ ``b``\ ）的操作。这两个比较操作都会被\ ``NoCompareOnPointerTypes202328015059001Check``\ 检查器标记为错误。这是因为该检查器的目的是禁止直接比较指针类型，以避免潜在的错误和不确定行为。
