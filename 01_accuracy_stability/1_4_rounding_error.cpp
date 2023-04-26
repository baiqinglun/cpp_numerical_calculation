/**
 * 舍入误差
*/

#include<iostream>

using namespace std;

const float a = 1.234;
const float b = 0.0005678;
const double c = 1.234;
const double d = 0.0005678;

class p2_1{
private:
    float x;
    double y;
public:
    void floating(){
        x = a + b;
        y = c + d;
        // 设置流的输出格式，ios::fixed以便在打印浮点数时使用定点表示法（小数点右侧位数是固定的，这与科学记数法相反）
        // floatfiled指定浮点输出类型
        // 这里只是用ios::fixed就可以固定小数点位数
        cout.setf(ios::fixed,ios::floatfield); // 固定格式
        // 设置浮点数打印位数为8
        cout.precision(8); // 高精度
        cout << x << endl; // 1.23456776
        cout << y << endl; // 1.23456780
    }
};

int main()
{
    p2_1 p1;
    p1.floating();
    return 0;
}