/**
 * 不稳定性
*/

#include<iostream>
#include<math.h>

using namespace std;

class test{
private:
    int i;
    float x,sum,mult;

public:
    // exp(x)
    void series(){
        i = 1;
        sum = mult = 1;
        cout << "\n输入x = ";
        cout.setf(ios::fixed);
        cout.precision(8);
        cin >> x;
        do{
            mult *= x/i;
            sum += mult;
            i++;
        }while(fabs(mult) > 1e-15);
        cout << "\nexp(x)的值是" << sum << endl;
        cout << "\n准确值是" << exp(x) << endl;
    }

    // exp(-x)
    void series1(){
        i = 1;
        sum = mult = 1;
        cout << "\n输入x = ";
        cout.setf(ios::fixed);
        cout.precision(8);
        cin >> x;
        do{
            mult *= x/i;
            sum += mult;
            i++;
        }while(fabs(mult) > 1e-15);
        cout << "\nexp(x)的值是" << 1/sum << endl;
        cout << "\n准确值是" << exp(-x) << endl;
    }
};

int main(){
    test t;
    t.series();
    t.series1();
}