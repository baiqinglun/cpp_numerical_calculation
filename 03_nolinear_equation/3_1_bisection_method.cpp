/**
 * @brief: 对分法
 * @birth: created by Dablelv on bql at 2023-04-27
 */
#include<iostream>
#include<math.h>

using namespace std;

/**
 * @cname: Bisection
 * @brief: 使用对分法迭代求解方程
 * @birth: created by Dablelv on bql
 */
class Bisection
{
private:
    int iter,       // 迭代次数
        funNum;     // 方程序号
    double eps,     // 公差
           error,   // 残差
           f,       // 函数值
           f_low,   // 下限的函数值
           f_high,  // 上限的函数值
           f_new,   // 新x的函数值
           x_low,   // 下限
           x_high,  // 上限
           x_new;   // 新值
public:
    Bisection() {iter = 0;}
    ~Bisection() {}
    void solution();

    /**
     * @fname: Bisection::function
     * @brief: 通过funNom选择函数求解
     * @param: double
     * @return: double
     * @birth: created by Dablelv on bql
     */
    double function(double x)
    {
        switch(funNum)
        {
            case 0 :
                f = x - cos(x);
                break;
            case 1 :
                f = pow(x,2) - 3;
                break;
        }
        return f;
    }
};

/**
 * @fname: Bisection::solution
 * @brief: 求解
 * @param: void
 * @return: void
 * @birth: created by Dablelv on bql
 */
void Bisection::solution(){
    cout << "\n选择使用的方程";cin >> funNum;
    cout << "\n输入下限";cin >> x_low;
    cout << "\n输入上限";cin >> x_high;

    f_low = function(x_low);
    f_high = function(x_high);

    if((f_low*f_high) > 0)
    {
        cout << "\n错误的归类" << endl;
        exit(0);
    }

    cout << "\n输入公差: ";cin >> eps;

    if(fabs(f_low) < eps)
    {
        cout << "\n解是: " <<x_low <<endl;
        exit(0);
    }
    if(fabs(f_high) < eps)
    {
        cout << "\n解是: "<< x_high <<endl;
        exit(0);
    }

    do
    {
        iter++;
        x_new = 0.5 * (x_low + x_high);
        f_new = function(x_new);
        error = fabs(f_new);
        if((f_new * f_low) < 0)
        {
            x_high = x_new;
        }else
        {
            x_low = x_new;
        }
    }while(error >= eps);

    cout << "\n解是:" << x_new <<endl;
    cout << "\n收敛于" << iter << "次迭代" << endl;
}

int main(){
    Bisection bisection;
    bisection.solution();
    return 0;
}