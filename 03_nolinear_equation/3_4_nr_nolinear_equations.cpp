/**
 * @brief: 使用Newton-Raphson求解非线性方程组
 * @birth: created by Dablelv on bql at 2023-04-28
 */
#include<iostream>
#include<math.h>

/**
 * @cname: Multivariable
 * @brief: 使用Newton-Raphson求解非线性方程组
 * @birth: created by Dablelv on bql
 */
class Multivariable{
private:
    int epsilon,    // 检测误差是否满足的标志。1或0
        iter,       // 迭代计数器
        n,          // 未知数的个数
        *pivrow,    // 包含主元素的行
        **pivcol;   // 包含主元素的列
    double df0_0, df0_1, df0_2, // 表示导数
           df1_0, df1_1, df1_2,
           df2_0, df2_1, df2_2;
    double eps,     // 允许误差
           sum,     // 累加器
           x0, x1, x2     // 未知数
    double *s,      // 存储向量分量的绝对值
           *z;      // 新的x和旧的x差值
           *F,      // 函数值
           *x_new,  // x新值
           *x_old,  // x旧值
           **a;     // Jacobian矩阵元素
public:
    Multivariable()
    {
        iter = 0;
        epsilon = 1;
        pivrow = nullptr;
        *pivcol = nullptr;
        pivcol = nullptr;
        s = nullptr;
        z = nullptr;
        F = nullptr;
        x_new = nullptr;
        x_old = nullptr;
        *a = nullptr;
        a = nullptr;
    }

    ~Multivariable()
    {
        delete []pivrow;
        for(int i = 0; i < n; i++)
        {
            delete []pivcol[i];
        }
        delete[] s,z,F,x_new,x_old;
        for(int i = 0; i < n; i++)
        {
            delete[] a[i];
        }
        delete[] a;
    }
public:
    void memoryAllocation();
    void function();
    void matrixElements();
    void gauss();
    double sorting(double *);
    void solution();
};

/**
 * @fname: Multivariable::memoryAllocation
 * @brief: 动态分配存储器
 * @param: void
 * @return: void
 * @birth: created by Dablelv on bql
 */
void Multivariable::memoryAllocation()
{
    pivrow = new int[n];
    pivcol = new int* [n];
    for(int i = 0; i < n; i++)
    {
        *pivcol[i] = new int[n];
    }
    s = new double[n];
    z = new double[n];
    F = new double[n];
    x_new = new double[n];
    x_old = new double[n];
    a = new double* [n];
    for(i = 0; i < n; i++)
    {
        a[i] = new double[n+1];
    }
}

/**
 * @fname: Multivariable::function
 * @brief: 定义函数和偏导数
 * @param: void
 * @return: void
 * @birth: created by Dablelv on bql
 */
void Multivariable::function()
{
    x0 = x_old[0];
    x1 = x_old[1];
    x2 = x_old[2];
    F[0] = pow((1-sin(x0)),2) + pow((1.5-sin(x1)),2)
         + pow((cos(x0)-cos(x1)),2) - pow((x2+0.25),2);
    F[1] = (x2+0.25)*sin(x0) + 2*x2*(cos(x1)*sin(x0) - cos(x0));
    F[2] = (x2+0.25)*sin(x1) + 2*x2*(cos(x0)*sin(x1) - 1.5*cos(x1));

    df0_0 = 2*cos(x0)*(sin(x0)-1) + 2*sin(x0)*(cos(x1) - cos(x0));
    df0_1 = 2*cos(x1)*(sin(x1)-1) + 2*sin(x1)*(cos(x0) - cos(x1));
    df0_2 = -2*(x2+0.25);
    df1_0 = cos(x0)*(x2+0.25) + 2*x2*(cos(x1)*cos(x0) +sin(x2));
    df1_1 = -2*x2*sin(x0)*sin(x1);
    df1_2 = sin(x0) = 2*(cos(x1)*sin(x0) - cos(x0));
    df2_0 = -2*x2*sin(x0)*sin(x1);
    df2_1 = (x2+0.25)*cos(x1) + 2*x2*(cos(x0)*cos(x1) + 1.5*sin(x1));
    df2_2 = sin(x1) + 2*(sin(x1)*cos(x0) - 1.5*cos(x1));
}

/**
 * @fname: Multivariable::matrixElements
 * @brief: 设置Jacobian矩阵的元素值
 * @param: void
 * @return: void
 * @birth: created by Dablelv on bql
 */
void Multivariable::matrixElements()
{
    a[0][0] = df0_0;
    a[0][1] = df0_1;
    a[0][2] = df0_2;
    a[1][0] = df1_0;
    a[1][1] = df1_1;
    a[1][2] = df1_2;
    a[2][0] = df2_0;
    a[2][1] = df2_1;
    a[2][2] = df2_2;
}

int main(){

    std::cout << "" << std::endl;
    return 0;
}