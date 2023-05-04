/**
 * @brief:  -----------------------------
 *          |                           |
 *          |---------------------------|
 * 一根热传导杆，已知两边界为固定温度100和500℃，截面积0.01m2，热传导系数为1000，求棒上温度分布
 * @birth: created by Dablelv on bql at 2023-05-04
 */
#include<iostream>
#include<math.h>
#include<vector>
#include "../include/matplotlibcpp.h"

using namespace std;

/**
 * @cname: ODHotRod
 * @brief: 求棒上温度分布
 * @birth: created by Dablelv on bql
 */
class ODHotRod
{
private:
    int n,      // 份数
        pivrow;
    double  T1,     // 左边温度
            T2,     // 右边温度
            k,      // 热传导系数
            A,      // 截面积
            L,      // 棒的总长度
            ratio,
            dx;
    std::vector<std::vector<double>> a;     // 求解矩阵
    std::vector<double> T;     // 温度矩阵
    std::vector<double> x;
    
public:
    ODHotRod();
    ~ODHotRod();
    void swap(const int k);
    void gauss_elimenation();
    void input(); 
    void construction();
    void gauss_solveT();
    void printMatix(const string msg);
    void plotImg();
};

ODHotRod::ODHotRod()
{
    n = 5;
    T1 = 100;
    T2 = 500;
    k = 1000;
    A = 0.01;
    L = 0.5;
}

ODHotRod::~ODHotRod()
{
    
}

/**
 * @fname: printMatix
 * @brief: 打印矩阵
 * @param: const string
 * @return: void
 * @birth: created by Dablelv on bql
 */
void ODHotRod::printMatix(const string msg){
    // std::cout << "\n"+msg+"为：" <<  std::endl;
    for(int i=0;i<n;i++){
        for(int j=0;j<n+1;j++){
            cout <<  a[i][j] << "\t";
        }
        cout << endl;
    }
}

/**
 * @fname: swap
 * @brief: 交换矩阵行列
 * @param: const int
 * @return: void
 * @birth: created by Dablelv on bql
 */
void ODHotRod::swap(const int k){
    double temp;
    for(int j = k;j<n+1;j++){
        temp = a[k][j];
        a[k][j] = a[pivrow][j];
        a[pivrow][j] = temp;
    }
}

/**
 * @fname: input
 * @brief: 输入信息
 * @param: void
 * @return: void
 * @birth: created by Dablelv on bql
 */
void ODHotRod::input()
{
    std::cout << "\n默认参数为\nT1 = " << T1 << "\tT2 = " << T2 << "\tn = " << n << std::endl;
    std::cout << "A = " << A << "\tL = " << L << "\tk = " << k << std::endl;
    std::cout << "-----------------------------------------" << std::endl;
    int i = 0;
    std::cout << "\n是否需要输入值：" << std::endl;
    cin >> i;
    if(!i){
        return;
    }
    std::cout << "\n请输入划分网格个数：n = ";std::cin >> n;
    std::cout << "\n请输入左侧温度：T1 = ";std::cin >> T1;
    std::cout << "\n请输入右侧温度：T2 = ";std::cin >> T2;
    std::cout << "\n请输入横截面积：A = ";std::cin >> A;
    std::cout << "\n请输入长度：L = ";std::cin >> L;
    std::cout << "\n请输入热传导系数：k = ";std::cin >> k;

}

/**
 * @fname: construction
 * @brief: 构造矩阵
 * @param: void
 * @return: void
 * @birth: created by Dablelv on bql
 */
void ODHotRod::construction()
{
    dx = L / n;

    double gDiff_face = A / dx;
    double gDiff_wall = 2 * A / dx;

    double a_wall = -k * gDiff_wall;
    double a_face = -k * gDiff_face;

    double ac_wall = -(a_wall + a_face);
    double ac_face = -(a_face * 2);

    double bc_left = - a_wall * T1;
    double bc_right = - a_wall * T2;

    a.resize(n);
    for(int i = 0; i < n; ++i)
    {
        a[i].resize(n+1);
    };
    printMatix("初始矩阵");

    for(int i = 0; i < n; ++i)
    {
        if(i == 0)
        {
            a[0][0] = ac_wall;
            a[0][1] = a_face;
        }
        else if((n-1) == i)
        {
            a[n-1][n-2] = a_face;
            a[n-1][n-1] = ac_wall;
        }
        else
        {
            for(int j = i-1; j <= i+1; ++j)
            {
                (i == j) ? (a[i][j] = ac_face) : (a[i][j] = a_face);
            };
        }
    };
    printMatix("构造矩阵");

    // 源项
    for(int i = 0; i < n; ++i)
    {
        if(0 == i)
        {
            a[i][n] = bc_left;
        }
        else if((n-1) == i)
        {
            a[i][n] = bc_right;
        }
        else
        {
            a[i][n] = 0;
        }
    };
    printMatix("添加源项矩阵");
}

/**
 * @fname: gauss_elimenation
 * @brief: 矩阵消元
 * @param: void
 * @return: void
 * @birth: created by Dablelv on bql
 */
void ODHotRod::gauss_elimenation(){
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
    printMatix("列主元矩阵");
}

/**
 * @fname: gauss_solveT
 * @brief: 回带求解X
 * @param: void
 * @return: void
 * @birth: created by Dablelv on bql
 */
void ODHotRod::gauss_solveT(){
    T.resize(n);
    T[n-1] = a[n-1][n] / a[n-1][n-1];
    double sum;
    for(int i = n-2;i>=0;i--){
        sum = 0.0;
        for(int j = i+1;j<n;j++){
            sum += a[i][j] * T[j];
        }
        T[i] = (a[i][n] - sum) / a[i][i];
    }
    for(int i = 0; i < n; ++i)
    {
        std::cout << "T[" << i << "] = " << T[i] << std::endl;
    };
}

namespace plt = matplotlibcpp;
void ODHotRod::plotImg()
{
    x.resize(n);
    x[0] = 0;
    for(int i = 1; i < x.size(); ++i)
    {
        x[i] = x[i-1] + dx;
    }
    plt::plot(x,T);
    plt::show();
}

int main(){
    ODHotRod o;
    o.input();
    o.construction();
    o.gauss_elimenation();
    o.gauss_solveT();
    o.plotImg();
    return 0;
}