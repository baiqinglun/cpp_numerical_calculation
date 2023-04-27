/**
 * @brief: 试位法 
 * @birth: created by Dablelv on bql at 2023-4-27
 */
#include<iostream>
#include<math.h>

using namespace std;

/**
 * @cname: Falsi
 * @brief: 试位法求解
 * @birth: created by Dablelv on bql
 */
class Falsi{
private:
    int iter,
        funNum;
    double x_high,
           x_low,
           f_high,
           f_low,
           x_new,
           f_new,
           f,
           eps,
           error;

public:
    Falsi():iter(0),f(0.0),error(0.0),funNum(0){}
    double funtion(const double);
    void input();
    void solution();

};

/**
 * @fname: Falsi::funtion
 * @brief: 定义函数
 * @param: const double
 * @return: double
 * @birth: created by Dablelv on bql
 */
double Falsi::funtion(const double x)
{
    switch (funNum)
    {
    case 0:
        f = pow(x,3) - 2 * pow(x,2) + x -2;
        break;
    case 1:
        f = x * pow(10 * x / (10 + 2 * x), 2.0 / 3) - 0.01 * 10 / 10 / sqrt(0.001);
        break;
    case 2:
        f = pow(x,2) - 3;
        break;
    default:
        break;
    }
    
    return f;
}

/**
 * @fname: Falsi::input
 * @brief: 输入上线限和公差
 * @param: void
 * @return: void
 * @birth: created by Dablelv on bql
 */
void Falsi::input()
{
    cout << "\n选择方程";cin >> funNum;
    cout << "\n输入下限";cin >> x_low;
    cout << "\n输入上限";cin >> x_high;
    cout << "\n输入公差";cin >> eps;
}

/**
 * @fname: Falsi::solution
 * @brief: 求解
 * @param: void
 * @return: void
 * @birth: created by Dablelv on bql
 */
void Falsi::solution()
{
    f_high = funtion(x_high);
    f_low = funtion(x_low);
    if((f_high * f_low) > 0)
    {
        cout << "\n区间有误错误";
        exit(0);
    }

    do
    {
        iter++;
        x_new = (x_low * f_high - x_high * f_low) / (f_high - f_low);
        f_new = funtion(x_new);
        error = fabs(f_new);
        if((f_new * f_low) < 0)
        {
            x_high = x_new;
        }else
        {
            x_low = x_new;
        }
    }while(error >= eps);

    cout << "\n解是" << x_new << endl;
    cout << "\n收敛于" << iter << "次迭代" << endl;
}


int main(){
    Falsi f;
    f.input();
    f.solution();

    return 0;
}