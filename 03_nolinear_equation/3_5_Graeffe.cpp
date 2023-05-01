/**
 * @brief: 使用根平方法求解实根和复根
 * @birth: created by Dablelv on bql at 2023-05-01
 */
#include<iostream>
#include<math.h>
using namespace std;

class Graeffe
{
private:
    int flag,
        iter,
        iter_max,
        n;
    double eps,
           low_limit,   // Ai值的下限
           pm,          // 根的负值计算得到的多项式的值
           pp,          // 根的正值计算得到的多项式的值
           root,        // 根的值
           sum,         // 累加器
           up_limit,    // Ai值的上限
           val,         // 多项式的值
           *a,          // 原多项式的系数
           *b,          // 迭代后平方多项式的系数
           *c;          // 迭代前平方多项式的系数

public:
    Graeffe();
    ~Graeffe();
    void solution();
};

Graeffe::Graeffe()
{
    flag = 0;
    iter = 0;
    iter_max = 100;
    n = 0;
    eps = 0.0;
    low_limit = 1e-35;
    root = 0.0;
    sum = 0.0;
    up_limit = 1e35;
    val = 0.0;
    a = nullptr;
    b = nullptr;
    c = nullptr;
}

Graeffe::~Graeffe()
{
    delete [] a;
    delete [] b;
    delete [] c;
}

void Graeffe::solution()
{
    std::cout << "\n输入多项式的阶数";
    cin >> n;
    a = new double[n+1];
    b = new double[n+1];
    c = new double[n+1];

    for(int i = 0; i <= n; ++i)
    {
        std::cout << "\n请输入a[" << i << "] = " ;
        cin >> a[i];
    };
    std::cout << "\n输入可以认为多项式值为0的量";
    cin >> eps;

    for(int i = 1; i <= n; ++i)
    {
        a[i] /= a[0];
        c[i] = a[i];
    };
    a[0] = 1.0;
    b[0] = 1.0;
    c[0] = 1.0;

    do
    {
        ++iter;
        for(int i = 1; i <= n; ++i)
        {
            sum = 0.0;
            for(int k = 1; k <= i; ++k)
            {
                if((i+k) <= n)
                {
                    sum += pow((-1),k) * c[i+k] * c[i-k];
                }
                b[i] = pow((-1),i) * (c[i] * c[i] + 2*sum);
            };
        }

        for(int i = 1; i <= n; ++i)
        {
            if(b[i] != 0)
            {
                if(fabs(b[i]) > up_limit || fabs(b[i]) < low_limit) {flag = 1;}
            }
        };

        if(flag != 1)
        {
            for(int i = 1; i <= n; ++i)
            {
                c[i] = b[i];
            };
        }

        if(iter > iter_max)
        {
            std::cout << "\n经过" << iter_max << "次迭代没有找到根" << std::endl;
            exit(0);
        }
    }while(0 == flag);

    std::cout << "-----------------------------" << std::endl;
    std::cout << "\n迭代次数 = " << iter << std::endl;

    for(int i = 1; i <= n; ++i)
    {
        if(0 == b[i])
        {
            std::cout << "\n错误.A[" << i << "] = 0" << std::endl;
            exit(0);
        }
    };
    for(int i = 1; i <= n; ++i)
    {
        root = pow(fabs(b[i]/b[i-1]),pow(2,(-iter)));
        pp = 1.0;
        pm = 1.0;
        for(int j = 1; j <= n; ++j)
        {
            pp = pp * root + a[j];
            pm = pm * (-root) + a[j];
        };
        if(fabs(pp) > fabs(pm))
        {
            root = -root;
            val = pm;
        }else
        {
            val = pp;
        }
        if(fabs(val) < eps) {std::cout << "\n找到了根 = " << root << std::endl;}
        else {std::cout << "\n可能没有根.根 = " << root << ".多项式的值 = " << val << std::endl;}
    };
}


int main(){
    Graeffe g;
    g.solution();

    return 0;
}