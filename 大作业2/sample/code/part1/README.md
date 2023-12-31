## 《软件分析与测试》2023年秋季学期“软件插桩”主题课程作业
### 项目结构说明
- `Passes`文件夹下包含插桩代码。其中`MyPass`子文件夹包含一份插桩示例代码，演示如何在每一个函数入口处进行插桩，输出“hello”信息。本次作业需要修改其他三个子文件夹`puzzle1`、`puzzle2`和`puzzle3`下的代码文件，编写程序插桩模块，达成特定目的。
- `test`文件夹下包含测试程序用例。其中`hello`子文件夹包含一份helloworld代码，用于演示`MyPass`插桩模块的效果。其余三个子文件夹`puzzle1`、`puzzle2`和`puzzle3`分别存放三个插桩任务的测试用例，每种任务有1个测试样例，共3个，在最终评测中每种任务会有4个测试样例，包含当前已经提供的1个。

### 成绩说明
本次任务满分100分，其中技术分满分60分，报告分满分40分。

本次任务共有12个测试样例，每一个测试样例对应一组测试。通过一组测试，可得技术分5分；未通过一组测试，可得技术分0分。每种任务公开1个测试样例，后续测试样例会在作业截止后公开。

不得通过“硬编码”、“打表”等非插桩手段通过测试，若发现此种行为，对应部分的技术得分将记为0分。

最终提交作业时，需随源代码一并提交一份作业报告。报告将由教师及助教人工打分，满分40分。报告得评分细则为：puzzle1部分满分10分，puzzle2部分满分10分，puzzle3部分满分10分，报告书写完整性、流畅度评分10分。

在报告中，需写明小组成员，成员间的分工情况，以及插桩思路。在介绍插桩思路时，需要写明查找插桩点的方法（3分）、在插桩点进行插桩的手法（4分）、数据记录和输出的方法（3分）这三部分。


### puzzle1：基本块覆盖度插桩
给定测试样例，通过插桩记录基本块是否被执行（即基本块覆盖率），要求在程序运行退出时以输出所有基本块的数量和已覆盖的基本块的数量.
输出格式为："Basic Block Coverage: 5/6"，前者为已覆盖的基本块数量，后者为所有基本块的数量。

提示1：可通过给基本块编号，并记录执行过程中的编号信息来记录基本块的覆盖情况。
提示2：输出可通过函数调用实现，即自行实现一个函数输出信息，并在测试样例程序退出前调用该函数。

### puzzle2：共享变量识别
通过插桩，使得程序能够在运行时识别线程间共享的全局变量（被多于一个线程读或写的全局变量），并在程序退出前输出这些线程间共享的全局变量的符号名。
输出格式应为："shared variables: [var0, var1, var2]"。
注意：为降低难度，本题中全局变量仅包含基本类型（int、double、bool、pointer等），不包含数组等复杂结构。

提示1：插桩读取指令（LoadInst）和存储指令（StoreInst），识别程序读/写操作对应的内存地址。通过判断同一个内存地址是否在两个不同的线程中被读/写，来判断该内存地址对应的变量是否是线程间共享的变量。

提示2：可以借助pthread_self()函数，通过观察其返回值确定当前线程。不同线程pthread_self()的返回值一定不同，相同线程pthread_self()的返回值一定相同。

提示3：对于一个LLVM变量（llvm::Value），在插桩时可以通过llvm::Value::getName方法获取其符号名。静态变量以及栈上变量一定能获取到符号名，堆上变量不一定有符号名（即获取到的符号名为""）。

提示4：在插桩时，可以使用IRBuilder<>::CreateGlobalStringPtr方法向程序中插入一个静态字符串。此方法接受一个字符串，返回一个指向llvm::Value*类型变量的指针。该llvm::Value变量可视为指向静态字符串的起始地址的指针在LLVM IR系统中的占位符。使用该llvm::Value变量作为函数参数，创建函数调用，将新插入的静态字符串的起始地址传递给新插入的插桩函数，从而在程序运行时获取变量的符号名。


### puzzle3：lockset算法
通过插桩，使得程序能够在运行时识别存在数据竞争的全局变量（没有被同一个互斥锁保护、被多于一个线程读或写、且至少被一个线程写的全局变量），并在程序退出前输出这些存在数据竞争的全局变量的符号名。
输出格式应为："race variables: [var0, var1, var2]"。



### 辅助命令
1. 使用如下命令：
```
clang -Os -g -fno-discard-value-names ./code.c -S -emit-llvm -o ir.ll
```
可以将code.c源码文件翻译为LLVM IR文件，并存储到ir.ll中。可以通过观察LLVM IR判断插桩点。

2. 使用如下命令
```
clang -fpass-plugin=libpass.so  -Os -g -fno-discard-value-names ./code.c -S -emit-llvm -o ir.ll
```
可以将code.c源码文件使用libpass.so处理，然后翻译为LLVM IR文件，并存储到ir.ll中。libpass.so是编译得到的插桩模块，在lib文件夹下。可以通过观察LLVM IR判断插桩模块的插桩效果。

3. 请使用版本号为14.0.x的clang/llvm进行项目源码的编译、程序的插桩。

4. 使用如下命令进行项目的编译：
```
mkdir build
cd build
cmake ..
make -j
```

5. 使用如下命令运行测试
```
make test
```
测试程序会报告测试样例的通过情况。
