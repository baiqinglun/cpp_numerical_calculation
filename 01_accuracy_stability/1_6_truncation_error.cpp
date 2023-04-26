/**
 * 截断误差
*/

#include<iostream>
#include<math.h>

using namespace std;

class p2_2{
private:
    double x,expx;

public:
    void expo(){
        cout << "\n输入";
        cin >> x;
        cout.setf(ios::fixed,ios::floatfield);
        cout.precision(8);
        expx = 1 + x;
        cout << "\n截取前两项给出 " << expx << endl;
        expx = 1 + x + x * x / 2 + x * x * x / 6;
        cout << "\n截取前四项给出 " << expx << endl;
        expx = (1 + 2*x/3)+x*x/6/(1-x/3);
        cout << "\n帕德逼近式给出 " << expx << endl;
        expx = exp(x);
        cout << "\nC++库函数给出 " << expx << endl;
    }
    
    // 截取前两项给出 1.50000000

    // 截取前四项给出 1.64583333

    // 帕德逼近式给出 1.38333333

    // C++库函数给出 1.64872127


};

int main()
{
    p2_2 p2;
    p2.expo();
    return 0;
}