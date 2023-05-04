/**
 * @brief:  -----------------------------
 *          |                           |
 *          |---------------------------|
 * 一根热传导杆，已知两边界为固定温度100和500℃，截面积0.01m2，热传导系数为1000，求棒上温度分布
 * @birth: created by Dablelv on bql at 2023-05-04
 */
#include<iostream>
#include<math.h>

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
            ratio;
    double **a,     // 求解矩阵
            *T;     // 温度矩阵
    
public:
    ODHotRod();
    ~ODHotRod();
    void swap(const int k);
    void gauss_elimenation();
    void input(); 
    void construction();
    void gauss_solveT();
    void printMatix(const string msg);
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
    for(int i = 0; i < n; ++i)
    {
        delete [] a[i];
    };
    delete []a;
    delete []T;
}

/**
 * @fname: printMatix
 * @brief: 打印矩阵
 * @param: const string
 * @return: void
 * @birth: created by Dablelv on bql
 */
void ODHotRod::printMatix(const string msg){
    cout << "\n"+msg+"为：" <<  endl;
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
    double dx = L / n;
    double gDiff_face = A / dx;
    double gDiff_wall = 2 * A / dx;
    // double kf_f = k;
    // double k12 = k;
    // double k6 = k;

    // double aE_1 = -kf_f * aDiff;
    // double aW_1 = -k12 * aDiff1;
    // double aE = -kf_f * aDiff;
    // double aW = -kf_f * aDiff;
    // double aE_2 = -k6 * aDiff1;
    // double aW_2 = -kf_f * aDiff;

    double a_wall = -k * gDiff_wall;
    double a_face = -k * gDiff_face;

    // double ac1 = -(aE_1 + aW_1);
    // double ac = -(aE + aW);
    // double ac2 = -(aE_2 + aW_2);
    double ac_wall = -(a_wall + a_face);
    double ac_face = -(a_face * 2);

    // double bc1 = - aW_1 * T1;
    // double bc2 = - aE_2 * T2;
    double bc_left = - a_wall * T1;
    double bc_right = - a_wall * T2;

    // a[0][0] = ac1;
    // a[0][1] = aE_1;

    // a[1][0] = aE;
    // a[1][1] = ac;
    // a[1][2] = aW;

    // a[2][1] = aE;
    // a[2][2] = ac;
    // a[2][3] = aW;

    // a[3][2] = aE;
    // a[3][3] = ac;
    // a[3][4] = aW;

    // a[4][3] = aW_2;
    // a[4][4] = ac2;

    // a[0][5] = bc1;
    // a[1][5] = 0;
    // a[2][5] = 0;
    // a[3][5] = 0;
    // a[4][5] = bc2;

    a = new double*[n];
    for(int i = 0; i < n; ++i)
    {
        a[i] = new double[n+1];
    };


    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < n+1; ++j)
        {
            a[i][j] = 0;  
        };
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

}

/**
 * @fname: gauss_solveT
 * @brief: 回带求解X
 * @param: void
 * @return: void
 * @birth: created by Dablelv on bql
 */
void ODHotRod::gauss_solveT(){
    T = new double[n];
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

int main(){
    ODHotRod o;
    o.input();
    o.construction();
    o.gauss_elimenation();
    o.gauss_solveT();
    
    return 0;
}