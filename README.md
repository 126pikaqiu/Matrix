# Matrix
面向对象编程课的lab，在大数类的基础上实现矩阵运算。主要考察点为运算符重载。相关要求文件在lab4.docx里面。
在RPN.h声明了一个宏，是用来处理含赋值语义的运算符在运算符优先级相同时的处理顺序的问题。如果注释掉会采用从左向右计算，如果不注释，会从右向左计算。实现方法在该类的一个函数，equal_handle。主要是控制了在生成后缀表达式时，运算符的出栈顺序。

### 通过的测试案例
 1. -A + B
 2. A+=A+=B
 3. -100 * A + 1000*B
 4. -100*A + -1000*B
 5. A+B+=C
 6. A+B=C
