/**
 * @brief: Newton-Raphson法
 * @birth: created by Dablelv on bql at 2023-4-27
 */
#include<iostream>
#include<math.h>

using namespace std;

/**
 * @cname: NewtonRaphson
 * @brief: Newton-Raphson法求解
 * @birth: created by Dablelv on bql
 */
class NewtonRaphson{
private:
    int iter,
        funNum;
    double x_old,
           f_old,
           df_old,
           x_new,
           f_new,
           f,
           df,
           eps,
           error;

public:
    NewtonRaphson():iter(0),f(0.0),error(0.0),funNum(0){}
    double funtion(const double);
    double deriv_funtion(const double);
    void input();
    void solution();

};

/**
 * @fname: NewtonRaphson::funtion
 * @brief: 函数
 * @param: const double
 * @return: double
 * @birth: created by Dablelv on bql
 */
double NewtonRaphson::funtion(const double x)
{
    switch (funNum)
    {
    case 0:
        f = pow(x,2) - 5 * x + 6;
        break;
    default:
        break;
    }
    
    return f;
}

/**
 * @fname: NewtonRaphson::deriv_funtion
 * @brief: 函数的导数
 * @param: const double
 * @return: double
 * @birth: created by Dablelv on bql
 */
double NewtonRaphson::deriv_funtion(const double x)
{
    switch (funNum)
    {
    case 0:
        df = 2 * x - 5;
        break;
    default:
        break;
    }

    return df;
}

/**
 * @fname: NewtonRaphson::input
 * @brief: 选择方程、输入初始值和公差
 * @param: void
 * @return: void
 * @birth: created by Dablelv on bql
 */
void NewtonRaphson::input()
{
    cout << "\n选择方程";cin >> funNum;
    cout << "\n输入初始值";cin >> x_old;
    cout << "\n输入公差";cin >> eps;
}

/**
 * @fname: NewtonRaphson::solution
 * @brief: 求解
 * @param: void
 * @return: void
 * @birth: created by Dablelv on bql
 */
void NewtonRaphson::solution()
{
    f_old = funtion(x_old);
    if(fabs(f_old) < eps)
    {
        cout << "\n解是" << x_old;
        exit(0);
    }

    do
    {
        iter++;
        x_new = x_old - funtion(x_old) / deriv_funtion(x_old);
        error = fabs(funtion(x_new));
        x_old = x_new;
    }while(error >= eps);
    // }while(iter < 5);

    cout << "\n解是" << x_new << endl;
    cout << "\n收敛于" << iter << "次迭代" << endl;
}


int main(){
    NewtonRaphson f;
    f.input();
    f.solution();

    return 0;
}