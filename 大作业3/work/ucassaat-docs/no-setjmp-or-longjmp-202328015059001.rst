.. title:: clang-tidy - NoSetjmpOrLongjmp202328015059001Check

NoSetjmpOrLongjmp202328015059001Check
=====================================

FIXME: Describe what patterns does the check detect and why. Give examples.


**目的：**

`NoSetjmpOrLongjmp202328015059001Check`检查器旨在识别并报告在C++代码中使用`setjmp`或`longjmp`函数的实例。

**实现：**

1. **匹配器注册（Matcher Registration）：**
   在`registerMatchers`函数中，检查器使用clang的AST匹配器（`ast_matchers`）匹配所有调用`setjmp`或`longjmp`函数的语句。

   - 使用`stmt`和`callExpr`匹配函数调用语句。
   - 使用`callee`和`functionDecl`匹配函数声明。
   - 使用`hasName`来识别`_setjmp`和`longjmp`函数的调用。

2. **检查器逻辑（Checker Logic）：**
   在`check`函数中，首先检查是否存在名为`setjmpCall`或`longjmpCall`的函数调用节点。如果存在，则进一步处理。

3. **错误诊断（Error Diagnostic）：**
   如果检测到`setjmp`或`longjmp`的调用，检查器会在源代码中的相应调用位置报告一个错误，错误信息分别为“Prohibit the use of setjmp function here”和“Prohibit the use of longjmp function here”。

**示例：**

在下面的代码中：

.. code:: cpp

    double fdiv(double a, double b) {
        double div = a / b;
        if (fobs(b) < 1e-10) {
            longjmp(mark, -1);
        }
        return div;
    }

函数`fdiv`中的`longjmp`函数调用违反了规则，因为它们使用了不建议在C++中使用的跳转函数。这些调用将被`NoSetjmpOrLongjmp202328015059001Check`检查器标记为错误。这是因为该检查器旨在识别并警告开发者避免使用可能导致不安全行为的旧C语言跳转函数。
