/**
 * @brief: 使用Faddeev-Leverrier求解矩阵的特征值与特征向量
 * @birth: created by Dablelv on bql at 2023-05-01
 */
#include<iostream>

using namespace std;

/**
 * @cname: FaddeevLeverrier
 * @brief: 使用Faddeev-Leverrier法求解的类
 * @birth: created by Dablelv on bql
 */
class FaddeevLeverrier
{
private:
    int     n;
    double  sum1,        // 累加器
            sum2,
            *alpha,      // 特征多项式的系数
            **a,         // 原始矩阵
            **b,         // 矩阵Ai
            **c;         // A(k-1)-a(k-1)I
public:
    void solution();
    double trace();
    ~FaddeevLeverrier();
    FaddeevLeverrier();
};

FaddeevLeverrier::FaddeevLeverrier()
{
    n = 0;
    sum1 = 0.0;
    sum2 = 0.0;
    alpha = nullptr;
    for(int i = 0; i < n; ++i)
    {
        a[i] = nullptr;
    };
    a = nullptr;
    for(int i = 0; i < n; ++i)
    {
        b[i] = nullptr;
    };
    b = nullptr;
    for(int i = 0; i < n; ++i)
    {
        c[i] = nullptr;
    };
    c = nullptr;
}

FaddeevLeverrier::~FaddeevLeverrier()
{
    delete [] alpha;
    for(int i = 0; i < n; ++i)
    {
        delete [] a[i];
    };
    delete [] a;
    for(int i = 0; i < n; ++i)
    {
        delete [] b[i]; 
    };
    delete [] b;
    for(int i = 0; i < n; ++i)
    {
        delete [] c[i];
    };
    delete [] c;
}

/**
 * @fname: FaddeevLeverrier::solution
 * @brief: 求解
 * @param: void
 * @return: void
 * @birth: created by Dablelv on bql
 */
void FaddeevLeverrier::solution()
{
    std::cout << "\n输入矩阵阶数" << std::endl;
    std::cin >> n;
    // 动态分配内存a、b、c、alpha
    a = new double * [n];
    for(int i = 0; i < n; ++i) {a[i] = new double[n];}
    b = new double * [n];
    for(int i = 0; i < n; ++i) {b[i] = new double[n];}
    c = new double * [n];
    for(int i = 0; i < n; ++i) {c[i] = new double[n];}
    alpha = new double[n+1];

    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            std::cout << "\n请输入a[" << i << "][" << j << "] = ";
            std::cin >> a[i][j];
        };
    };
    alpha[0] = 1.0;
    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < n; ++j) {b[i][j] = a[i][j];}      
    };

    alpha[1] = trace();

    for(int k = 2; k <= n; ++k)
    {
        // 求出c矩阵
        for(int i = 0; i < n; ++i)
        {
            for(int j = 0; j < n; ++j)
            {
              if(i == j) {c[i][j] = b[i][j] - alpha[k-1];}
              else {c[i][j] = b[i][j];}
            };
        };
        for(int i = 0; i < n; ++i)
        {
            for(int j = 0; j < n; ++j)
            {
                sum2 = 0.0;
                // 计算矩阵点乘
                for(int l = 0; l < n; ++l) {sum2 += a[i][l] * c[l][j];}
                b[i][j] = sum2;
            };
        };
        alpha[k] = trace() / k;
    };
    std::cout << "\n特征多项式的系数是：" << std::endl;
    for(int i = 1; i <= n; ++i)
    {
        std::cout << "\nalpha[" << i << "] = " << alpha[i] << std::endl;
    };
}

/**
 * @fname: FaddeevLeverrier::trace
 * @brief: 计算矩阵的迹（对角线元素之和）
 * @param: void
 * @return: double
 * @birth: created by Dablelv on bql
 */
double FaddeevLeverrier::trace()
{
    sum1 = 0.0;
    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            if(i == j) {sum1 += b[i][j];}
        };
    };
    return sum1;
}

int main(){
    FaddeevLeverrier f;
    f.solution();
    return 0;
}