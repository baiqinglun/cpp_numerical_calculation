/**
 * @brief: 使用Newton-Raphson求解非线性方程组
 * @birth: created by Dablelv on bql at 2023-04-28
 */
#include<iostream>
#include<math.h>
#include<stdlib.h>

/**
 * @cname: Multivariable
 * @brief: 使用Newton-Raphson求解非线性方程组
 * @birth: created by Dablelv on bql
 */
class Multivariable{
private:
    int epsilon,    // 检测误差是否满足的标志。1或0
        iter,       // 迭代计数器
        n,          // 未知数的个数W
        pivrow;     // 主元素的行
    double df0_0, df0_1, df0_2, // 表示导数
           df1_0, df1_1, df1_2,
           df2_0, df2_1, df2_2;
    double eps,     // 允许误差
           error,
           sum,     // 累加器
           x0, x1, x2,     // 未知数
           ratio;   // 消元时的比值
    double *s,      // 存储向量分量的绝对值
           *z,      // 新的x和旧的x差值
           *F,      // 函数值
           *x_new,  // x新值
           *x_old,  // x旧值
           **a;     // Jacobian矩阵元素
public:
    Multivariable()
    {
        iter = 0;
        epsilon = 1;
        // pivrow = 0;
        // s = nullptr;
        // z = nullptr;
        // F = nullptr;
        // x_new = nullptr;
        // x_old = nullptr;
    }

    ~Multivariable()
    {
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
    void swap(const int k);
    void printMatix(const std::string);
    void printX();
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
    s = new double[n];
    z = new double[n];
    F = new double[n];
    x_new = new double[n];
    x_old = new double[n];
    a = new double* [n];
    for(int i = 0; i < n; i++)
    {
        a[i] = new double[n+1];
    }
}

/**
 * @fname: Multivariable::function
 * @brief: 求函数值和偏导数值
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
    df1_2 = sin(x0) + 2*(cos(x1)*sin(x0) - cos(x0));
    df2_0 = -2*x2*sin(x0)*sin(x1);
    df2_1 = (x2+0.25)*cos(x1) + 2*x2*(cos(x0)*cos(x1) + 1.5*sin(x1));
    df2_2 = sin(x1) + 2*(sin(x1)*cos(x0) - 1.5*cos(x1));
    printMatix("求函数值和偏导数值之后的Jacobian矩阵");
}

/**
 * @fname: Multivariable::matrixElements
 * @brief: 使用偏导数值设置Jacobian矩阵的元素值
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
    printMatix("使用偏导数值设置Jacobian矩阵的元素值");
}

/**
 * @fname: Multivariable::gauss
 * @brief: 高斯消去法迭代
 * @param: void
 * @return: void
 * @birth: created by Dablelv on bql
 */
void Multivariable::gauss()
{
    for(int k = 0;k<n-1;k++){
        // 选择主元
        double max = fabs(a[k][k]);
        pivrow = k;
        for(int i=k+1;i<n;i++){
            if(fabs(a[i][k]) > max){
                max = fabs(a[i][k]);
                pivrow = i;
                // swap
                swap(k);
            }
            // 消元
            ratio = a[i][k] / a[k][k];
            for(int j = k;j<n+1;j++){
                a[i][j] -= ratio * a[k][j];
            }
            a[i][k] = 0;
        }
    }
    printMatix("消元后的矩阵：");
    x_new = new double[n];
    x_new[n-1] = a[n-1][n]/ a[n-1][n-1];
    for(int i = n-2;i>=0;i--){
        sum = 0.0;
        for(int j = i+1;j<n;j++){
            sum += a[i][j] * x_new[j];
        }
        x_new[i] = (a[i][n] - sum) / a[i][i];
    }
    printX();
}

/**
 * @fname: Multivariable::swap
 * @brief: 交换行元素
 * @param: void
 * @return: void
 * @birth: created by Dablelv on bql
 */
void Multivariable::swap(const int k)
{
    double temp;
    for(int j = k; j < n+1; j++)
    {
        temp = a[k][j];
        a[k][j] = a[pivrow][j];
        a[pivrow][j] = temp;
    }
}

/**
 * @fname: Multivariable::sorting
 * @brief: 使用c++的qsort排序。求向量分量的最大值函数，返回最大值
 * @param: double *
 * @return: double
 * @birth: created by Dablelv on bql
 */
double Multivariable::sorting(double *y)
{
    int doublecmp(const void *,const void *);
    for(int i = 0; i < n; i++)
    {
        s[i] = fabs(y[i]);
    };
    qsort(s,n,sizeof(double),doublecmp);
    return (s[n-1]);
}

/**
 * @fname: doublecmp
 * @brief: 定义比较函数
 * @param: const void *,const void *
 * @return: int
 * @birth: created by Dablelv on bql
 */
int doublecmp(const void *v1,const void *v2)
{
    double* a = (double*)v1;    //强制类型转换
    double* b = (double*)v2;
    return (*a > *b) ? 1 : -1;
}

void Multivariable::solution()
{
    n = 3;
    memoryAllocation(); // 动态分配求解空间
    std::cout << "\n输入所有未知数的初始估值" << std::endl;
    for(int i = 0;i < n; i++)
    {
        std::cout << "\n输入初值x[" << i << "]:";
        std::cin >> x_old[i];
    }
    std::cout << "\n输入公差" ;
    std::cin >> eps;
    do
    {
        std::cout << "-------------------------------------" << std::endl;
        std::cout << "第:" << iter << "次迭代" <<std::endl;
        iter++;
        function(); // 求函数的值和偏导数的值（x_new一更新就会变）
        matrixElements(); // 设置jacobian矩阵的值
        for(int i = 0; i<n;i++)
        {
            a[i][n] = -F[i];
        }
        gauss();
        for(int i = 0; i < n; i++)
        {
            z[i] = x_new[i];
            x_new[i] = z[i] + x_old[i];
        }
        error = sorting(z) / sorting(x_new);
        if(error < eps)
        {
            epsilon = 0;
        }
        if(epsilon == 1)
        {
            for(int i = 0; i < n; i++)
            {
                x_old[i] = x_new[i];
            }
        }
    }while(epsilon == 1);
    for(int i = 0; i < n; i++)
    {
        std::cout << "\nx_new[" << i << "] = " << x_new[i] << std::endl;
    }
    std::cout << "\n收敛于" << iter << "次迭代" << std::endl;
    
}

// @brief: 打印矩阵
// @param: string
// @ret: void
// @birth: created by Dablelv on bql
void Multivariable::printMatix(const std::string msg){
    std::cout << "\n"+msg+"为：" <<  std::endl;
    for(int i=0;i<n;i++){
        for(int j=0;j<n+1;j++){
            std::cout <<  a[i][j] << "\t";
        }
        std::cout << std::endl;
    }
}

// @brief: 打印结果
// @param: void
// @ret: void
// @birth: created by Dablelv on bql
void Multivariable::printX(){
    std::cout << "\n输出结果"<< std::endl;
    for(int i=0;i<n;i++){
        std::cout << "x[" << i << "] = " << x_new[i] << std::endl;
    }
}

int main(){
    Multivariable m;
    m.solution();
    std::cout << "" << std::endl;
    return 0;
}