/**
 * @brief: 方程离散案例1
 * @birth: created by Dablelv on bql at 2023-05-02
 */
#include<iostream>

using namespace std;

class Differential 
{
private:
    int N,
        x_min,
        x_max;
    double dx,
            *x,
            *y;
public:
    Differential();
    ~Differential();
    void solution();
};

Differential::Differential()
{
    std::cout << "\n请输入网格个数:" << std::endl;
    cin >> N;
    std::cout << "\n请输入x最小值:" << std::endl;
    cin >> x_min;
    std::cout << "\n请输入x最大值:" << std::endl;
    cin >> x_max;

    dx = (x_max - x_min) / double(N) ;
    std::cout << "\ndx = " << dx << std::endl;
}

Differential::~Differential()
{
    delete [] x;
    delete [] y;
}

void Differential::solution()
{
    x = new double[N];
    y = new double[N];
   
    for(int i = 0; i < N; ++i)
    {
        x[i] = i * dx;
    };
    for(int i = 0; i < N; ++i)
    {
        y[i] = 1.0;
    };

    for(int i = 0; i < N; ++i)
    {
        y[i+1] = y[i] + dx * (y[i] - 2*x[i]/y[i]);
    };

    cout << endl;
    for(int i = 0; i < N; ++i)
    {
        std::cout << y[i] << "\t";
    };
}

int main(){
    Differential d;
    d.solution();

    return 0;
}