# cpp_numerical_calculation

## 1、数值计算的准确性与稳定性

数值方法主要用来解决不可能得到解析解的数学问题

### 1.1 有效数字

分为两种情况

1. 没有小数点：从左非零到右非零，如13040，有效数字为4；
2. 有小数点：从左非零到右全部，如2100.5，有效数字为5；0.015，有效数字为4；

有效数字的重要性：
如：10.5

1. 三位有效数字：大概值在10.45~10.55
2. 五位有效数字：大概值在10.495~10.505

### 1.2 误差定义

绝对误差 = 真值 - 近似值

相对误差 = 误差 / 真值

### 1.4 舍入误差

float：7位有效数字；
double：15位有效数字；

示例程序代码

```c++
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
```

### 2.5 有效数字规则

乘/除法：连接多个量：有效数字位数 = 任何被乘数/除数中最低的有效数字位数；

加/减法：比较每个数相对于小数点的最后一位有效数字的位置，最左边的位置是结果最后允许的有效数字的位置。

如：3.29 * 8.654 应该 = 28.47166，但是最低有效数字位数为3，则结果为28.5

如：1.1235 + 0.034 + 0.21 = 1.37

### 2.6 级数的截断误差

```c++
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
```

### 1.7 误差传播与计算不稳定性

误差随着计算逐步增长，则认为不稳定。

如：麦克劳林逼近式e^(x)，使用float数据类型不准确，double类型准确。

```c++
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
```

## 2、求解联立线性代数方程

### 2.1 矩阵定义

1. 方阵：m = n；
2. 转置矩阵：行和列交换；
3. 对称矩阵：前提为方阵，且原矩阵 = 转置矩阵；
4. 斜对称方阵：前提为方阵，且原矩阵 = -转置矩阵；
5. 对角矩阵：主对角线上存在非0元素，其他元素为0；
6. 单位矩阵：对角线元素为1；
7. 三对角矩阵：
8. 三角矩阵：
9. 稠密矩阵：没有任何0元素的矩阵；
10. 稀疏矩阵：个别具有0元素的矩阵；
11. 非奇异矩阵：行列式不为0；（只有这种矩阵可逆）
12. 行列式值很小时成为病态矩阵；

![三对角矩阵](https://test-123456-md-images.oss-cn-beijing.aliyuncs.com/img/20230426204042.png)
![三角矩阵](https://test-123456-md-images.oss-cn-beijing.aliyuncs.com/img/20230426204152.png)

### 2.2 解的唯一性

当且仅当增广矩阵的秩与系数矩阵的秩相同时，方程有解。如果秩为n（未知数个数），则解唯一。如果秩小于n，则存在无穷多个解。

### 2.3 顺序Gauss消去法

将增广矩阵简化成上三角矩阵。

方程式如下：

$$a_{ij}^{new} = a_{ij}^{old}-(\frac{a_{ik}}{a_{kk}})a_{kj}$$

$$k=0,1,2,...,(n-2);a_{kk}\ne0$$

$$i=(k+1),(k+2),...,(n-1)$$

$$j=k,(k+1),...,n$$

$$x_{n-1}=\frac{a_{(n-1)n}}{a_{(n-1)(n-1)}}$$

$$x_{i}=\frac{a_{in}-\sum_{j=i+1}^{n-1}a_{ij}x_{j}}{a_{ii}},i=(n-2),(n-3),...,0$$

完整代码演示

```c++
#include<iostream>
#include<math.h>
#include<process.h>
using namespace std;

class gauss{
private:
    int i,j,k,n;
    double eps,ratio,sum,*x,**a;

public:
    void gauss_input(); // 数据输入
    void gauss_elimination(); // 消去法
    void gauss_output(); // 结果输出
    ~gauss(){
        delete []x;
        for(int i=0;i<n;i++){delete [] a[i];};
        delete []a;
    }
};

int main(){
    gauss sol;
    sol.gauss_input();
    sol.gauss_elimination();
    sol.gauss_output();

    return 0;
}

void gauss::gauss_input(){
    cout << "输入方程的个数：";
    cin >> n;
    x = new double[n];
    a = new double*[n];
    for(int i = 0;i<n;i++){a[i] = new double[n+1];}
    // 输入系数矩阵元素
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            cout << "\n输入 a[" << i << "][" << j << "] = ";
            cin >> a[i][j];
        }
    }
    // 输入右端向量
    for(int i = 0;i<n;i++){
        cout << "\n输入b["<<i<<"] = ";
        cin >> a[i][n];
    }
    cout << "\n输入最小主元素";
    cin>>eps;

    // for(i=0;i<n;i++){
    //     for(j=0;j<n+1;j++){
    //         cout <<  a[i][j] << "\t";
    //     }
    //     cout << endl;
    // }
}

void gauss::gauss_elimination(){
    for(int k = 0; k < n-1; k++){
        for(int i = k+1;i<n;i++){
            if(fabs(a[k][k]<eps)){
                cout << "\n主元素太小，失败..." <<endl;
                exit(0);
            }
            ratio = a[i][k]/a[k][k];
            for(j = k;j<n+1;j++){
                a[i][j] -= ratio * a[k][j];
            }
            a[i][k] = 0;
        }
    }

    cout << "转换完成的a矩阵：" <<endl;
    for(i=0;i<n;i++){
        for(j=0;j<n+1;j++){
            cout <<  a[i][j] << "\t";
        }
        cout << endl;
    }

    x[n-1] = a[n-1][n]/a[n-1][n-1];
    for(i=n-2;i>=0;i--){
        sum = 0.0;
        for(int j = i+1;j<n;j++){
            sum+=a[i][j]*x[j];
        }
        x[i] =  (a[i][n]-sum)/a[i][i];
    }
}

void gauss::gauss_output(){
    cout << "\n结果是：" << endl;
    for(int i = 0;i<n;i++){
        cout << "\nx[" << i << "] = " << x[i] << endl;
    }
}
```

### 2.4 列主元消去法

每次消元前都要进行选主元，选绝对值最大。

```c++
/***
 * 全选主元消去法
*/

#include<iostream>
#include<math.h>

using namespace std;

class Gauss{
private:
    int n,pivrow;
    double eps,pivot,sum,aik,al,*x,**a,ratio;

public:
    void gauss_input();
    void gauss_elimenation();
    void gauss_solveX();
    void swap(const int);
    void printMatix(const string);
    void printX();
    ~Gauss(){
        // delete[] pivrow;
        // for(i = 0;i<n;i++){delete[] pivcol[i];}
        // delete[] pivcol;
        delete[] x;
        for(int i = 0;i<n;i++){delete[] a[i];}
        delete[] a;
    }
};

// @brief: 交换矩阵行
// @param: int
// @ret: void
// @birth: created by Dablelv on bql
void Gauss::swap(const int k){
    double temp;
    for(int j = k;j<n+1;j++){
        temp = a[k][j];
        a[k][j] = a[pivrow][j];
        a[pivrow][j] = temp;
    }
}

// @brief: 打印矩阵
// @param: string
// @ret: void
// @birth: created by Dablelv on bql
void Gauss::printMatix(const string msg){
    cout << "\n"+msg+"为：" <<  endl;
    for(int i=0;i<n;i++){
        for(int j=0;j<n+1;j++){
            cout <<  a[i][j] << "\t";
        }
        cout << endl;
    }
}

// @brief: 打印结果
// @param: void
// @ret: void
// @birth: created by Dablelv on bql
void Gauss::printX(){
    cout << "\n输出结果"<<endl;
    for(int i=0;i<n;i++){
        cout << "x[" << i << "] = " << x[i] << endl;
    }
}


// @brief: 输入矩阵
// @param: void
// @ret: void
// @birth: created by Dablelv on bql
void Gauss::gauss_input(){
    cout << "\n请输入方程的个数：" ;
    cin >> n;

    // 动态分配内存
    a = new double*[n];
    for(int i=0;i<n;i++){
        a[i] = new double[n+1];
    }

    cout << "\n请输入系数方程：";
    for(int i = 0;i<n;i++){
        for(int j = 0;j<n;j++){
            cout << "\na[" << i << "][" << j << "] = ";
            cin >> a[i][j];
        }
    }

    cout << "\n请输入右端矩阵：";
    for(int i= 0;i<n;i++){
        cout << "\nb[" << i << "] = ";
        cin >> a[i][n];
    }

    printMatix("增广矩阵");
}

// @brief: 矩阵消元
// @param: void
// @ret: void
// @birth: created by Dablelv on bql
void Gauss::gauss_elimenation(){
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
                printMatix("换行后矩阵");
            }
            cout << "a[" << i << "][" << k << "] = " << a[i][k] <<endl;
            cout << "a[" << k << "][" << k << "] = " << a[k][k] <<endl;
            // 消元
            ratio = a[i][k] / a[k][k];
            for(int j = k;j<n+1;j++){
                a[i][j] -= ratio * a[k][j];
            }
            a[i][k] = 0;
            printMatix("消元后矩阵");
        }
    }

}

// @brief: 回带求解X
// @param: void
// @ret: void
// @birth: created by Dablelv on bql
void Gauss::gauss_solveX(){
    x = new double[n];
    x[n-1] = a[n-1][n] / a[n-1][n-1];
    for(int i = n-2;i>=0;i--){
        sum = 0.0;
        for(int j = i+1;j<n;j++){
            sum += a[i][j] * x[j];
        }
        x[i] = (a[i][n] - sum) / a[i][i];
    }
    printX();
}

int main(){
    Gauss gauss;
    gauss.gauss_input();
    gauss.gauss_elimenation();
    gauss.gauss_solveX();
    return 0;
}
```

### 2.5 Gauss-Jordan消去法

消元前进行归一化处理

归一化

$$a_{kj}^{new} = \frac{a_{kj}^{old}}{a_{kk}},(k=0,1,...,n-1)(j=n,n-1,...,k) $$

消元

$$a_{ij}^{new} = a_{ij}^{old} - a_{ik}a_{kj}^{new},(i=0,1,...,n-1;i\ne k)(j=n,n-1,...,k) $$

回带

$$x_{i} = \frac{a_{in}}{a_{ii}},(i=0,1,...,n)$$

```c++
/***
 * Gauss-Jordan消去法
*/

#include<iostream>
#include<math.h>

using namespace std;

class Gauss{
private:
    int n,pivrow;
    double sum,*x,**a;

public:
    void gauss_input();
    void gauss_elimenation();
    void gauss_solveX();
    void swap(const int);
    void printMatix(const string);
    void printX();
    ~Gauss(){
        delete[] x;
        for(int i = 0;i<n;i++){delete[] a[i];}
        delete[] a;
    }
};

// @brief: 交换矩阵行
// @param: int
// @ret: void
// @birth: created by Dablelv on bql
void Gauss::swap(const int k){
    double temp;
    for(int j = k;j<n+1;j++){
        temp = a[k][j];
        a[k][j] = a[pivrow][j];
        a[pivrow][j] = temp;
    }
}

// @brief: 打印矩阵
// @param: string
// @ret: void
// @birth: created by Dablelv on bql
void Gauss::printMatix(const string msg){
    cout << "\n"+msg+"为：" <<  endl;
    for(int i=0;i<n;i++){
        for(int j=0;j<n+1;j++){
            cout <<  a[i][j] << "\t";
        }
        cout << endl;
    }
}

// @brief: 打印结果
// @param: void
// @ret: void
// @birth: created by Dablelv on bql
void Gauss::printX(){
    cout << "\n输出结果"<<endl;
    for(int i=0;i<n;i++){
        cout << "x[" << i << "] = " << x[i] << endl;
    }
}


// @brief: 输入矩阵
// @param: void
// @ret: void
// @birth: created by Dablelv on bql
void Gauss::gauss_input(){
    cout << "\n请输入方程的个数：" ;
    cin >> n;

    // 动态分配内存
    a = new double*[n];
    for(int i=0;i<n;i++){
        a[i] = new double[n+1];
    }

    cout << "\n请输入系数方程：";
    for(int i = 0;i<n;i++){
        for(int j = 0;j<n;j++){
            cout << "\na[" << i << "][" << j << "] = ";
            cin >> a[i][j];
        }
    }

    cout << "\n请输入右端矩阵：";
    for(int i= 0;i<n;i++){
        cout << "\nb[" << i << "] = ";
        cin >> a[i][n];
    }

    printMatix("增广矩阵");
}

// @brief: 矩阵消元
// @param: void
// @ret: void
// @birth: created by Dablelv on bql
void Gauss::gauss_elimenation(){
    for(int k = 0;k<n;k++){
        for(int i=0;i<n;i++){
            if(i != k){
                for(int j = n;j>=k;j--){
                    // 归一化
                    a[k][j] /= a[k][k];
                    // 消元
                    a[i][j] -= a[i][k] * a[k][j];
                }
            }
        }
    }
    printMatix("消元后矩阵");
}

// @brief: 回带求解X
// @param: void
// @ret: void
// @birth: created by Dablelv on bql
void Gauss::gauss_solveX(){
    x = new double[n];
    for(int i = 0;i<n;i++){
        x[i] = a[i][n] / a[i][i];
    }
    printX();
}

int main(){
    Gauss gauss;
    gauss.gauss_input();
    gauss.gauss_elimenation();
    gauss.gauss_solveX();
    return 0;
}
```

### 2.6 Gauss_Jordan求解逆矩阵

需要在增广矩阵上添加一个单位矩阵，比如方程个数为3，则要形成3*7的矩阵（列为系数矩阵的3，右端矩阵的1，单位矩阵的3）

再使用Gauss-Jordan方法归一化消元处理

完整代码如下

```c++
/***
 * Gauss-Jordan法求解矩阵的逆
*/

#include<iostream>
#include<math.h>

using namespace std;

class Gauss{
private:
    int n,pivrow;
    double sum,*x,**a,**b;

public:
    void gauss_input();
    void gauss_elimenation();
    void gauss_solveX();
    void gauss_inverse();
    void swap(const int);
    void printMatix(const string);
    void printX();
    void printInverse(const string);
    ~Gauss(){
        delete[] x;
        for(int i = 0;i<n;i++){delete[] a[i];}
        delete[] a;
    }
};

// @brief: 交换矩阵行
// @param: int
// @ret: void
// @birth: created by Dablelv on bql
void Gauss::swap(const int k){
    double temp;
    for(int j = k;j<n+1;j++){
        temp = a[k][j];
        a[k][j] = a[pivrow][j];
        a[pivrow][j] = temp;
    }
}

// @brief: 打印矩阵
// @param: string
// @ret: void
// @birth: created by Dablelv on bql
void Gauss::printMatix(const string msg){
    cout << "\n"+msg+"为：" <<  endl;
    for(int i=0;i<n;i++){
        for(int j=0;j<2*n+1;j++){
            cout <<  a[i][j] << "\t";
        }
        cout << endl;
    }
}

// @brief: 打印结果
// @param: void
// @ret: void
// @birth: created by Dablelv on bql
void Gauss::printX(){
    cout << "\n输出结果"<<endl;
    for(int i=0;i<n;i++){
        cout << "x[" << i << "] = " << x[i] << endl;
    }
}

// @brief: 打印逆矩阵
// @param: string
// @ret: void
// @birth: created by Dablelv on bql
void Gauss::printInverse(const string msg){
    cout << "\n"+msg+"为：" <<  endl;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout <<  b[i][j] << "\t";
        }
        cout << endl;
    }
}

// @brief: 输入矩阵
// @param: void
// @ret: void
// @birth: created by Dablelv on bql
void Gauss::gauss_input(){
    cout << "\n请输入方程的个数：" ;
    cin >> n;

    // 动态分配内存
    a = new double*[n];
    for(int i=0;i<n;i++){
        a[i] = new double[2*n+1];
    }

    cout << "\n请输入系数方程：";
    for(int i = 0;i<n;i++){
        for(int j = 0;j<n;j++){
            cout << "\na[" << i << "][" << j << "] = ";
            cin >> a[i][j];
        }
    }

    cout << "\n请输入右端矩阵：";
    for(int i= 0;i<n;i++){
        cout << "\nb[" << i << "] = ";
        cin >> a[i][n];
    }

    for(int i = 0;i<n;i++){
        for(int j = n+1;j<2*n+1;j++){
            if((j-n-1) != i){
                a[i][j] = 0;
            }else{
                a[i][j] = 1;
            }
        }
    }

    printMatix("加入单位矩阵后");

}

// @brief: 矩阵消元
// @param: void
// @ret: void
// @birth: created by Dablelv on bql
void Gauss::gauss_elimenation(){
    for(int k = 0;k<n;k++){
        for(int i=0;i<n;i++){
            if(i != k){
                for(int j = 2*n;j>=k;j--){
                    // 归一化
                    a[k][j] /= a[k][k];
                    // 消元
                    a[i][j] -= a[i][k] * a[k][j];
                }
            }
        }
    }
    printMatix("消元后矩阵");
}

// @brief: 回带求解X
// @param: void
// @ret: void
// @birth: created by Dablelv on bql
void Gauss::gauss_solveX(){
    x = new double[n];
    for(int i = 0;i<n;i++){
        x[i] = a[i][n];
    }
    printX();
}

// @brief: 求解逆矩阵
// @param: void
// @ret: void
// @birth: created by Dablelv on bql
void Gauss::gauss_inverse(){
    b = new double *[n];
    for(int i = 0;i<n;i++){
        b[i] = new double [n];
    }
    for(int i =0;i<n;i++){
        for(int j = n+1;j<2*n+1;j++){
            b[i][j-n-1] = a[i][j];
        }
    }
    printInverse("逆矩阵");
}

int main(){
    Gauss gauss;
    gauss.gauss_input();
    gauss.gauss_elimenation();
    gauss.gauss_solveX();
    gauss.gauss_inverse();
    return 0;
}
```

## 3、求解非线性方程

求解非线性方程组往往不能使用解析的方法，使用迭代的数值方法。

单个非线性方程
$$
\begin{equation}
F(x) = 0
\end{equation}
$$
具有n个方程和n个未知数的非线性方程组
$$
\begin{equation}
\begin{aligned}
F_{0}(x_{0},x_{1},...,x_{n-1}) = 0\\
F_{1}(x_{0},x_{1},...,x_{n-1}) = 0\\
F_{n-1}(x_{0},x_{1},...,x_{n-1}) = 0
\end{aligned}
\end{equation}
$$

方程2可以简写为
$$
\tilde{F} (\tilde {x}) = \tilde {0}
$$

方程的解法：

1. 图解法：画图看交点；
2. 反复实验法：给初值，反复试验；
3. 归类与开放法：限定在一个区间；
4. 对分法。

### 3.1 对分法

新的估计值
$$
\begin{equation}
\begin{aligned}
x_{new} = \frac{x_{low}+x_{high}}{2}\nonumber
\end{aligned}
\end{equation}
$$
这个点上的函数值共有4种情况
$$
\begin{equation}
\begin{gather}
F(x_{new})F(x_{low}) < 0 \nonumber\\
F(x_{new})F(x_{high}) < 0 \nonumber\\
|F(x_{new})| <eps \nonumber \\
F(x_{new})=0 \nonumber
\end{gather}
\end{equation}
$$

例：使用对分法求方程$x^{2}-3=0$或者$x-cos(x) = 0$的正根。

定义Bisection类实现对分求解器

```c++
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
```

求解流程：

1. 先判断上下限函数乘积是否符合对分法；
2. 判断上下限函数的值是否符合公差范围；
3. 迭代对分求解新的x值，重新规定上下限；
4. 直到新x值的函数值小于公差；


```c++
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
```

完整代码如下：

```c++
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
```

### 3.2 试位法

设有上下限$x_{low}$和$x_{high}$

则弦的斜率为
$$a=\frac{F(x_{high})-F(x_{low})}{x_{high}-x_{low}}$$

弦的截距
$$b=F(x_{low})-\frac{F(x_{high})-F(x_{low})}{x_{high}-x_{low}}x_{low}$$

弦方程为
$$y(x)=[\frac{F(x_{high})-F(x_{low})}{x_{high}-x_{low}}]x+[F(x_{low})-\frac{F(x_{high})-F(x_{low})}{x_{high}-x_{low}}x_{low}]$$

令方程等于0，即可得$x_{new}$
$$y(x)=[\frac{F(x_{high})-F(x_{low})}{x_{high}-x_{low}}]x_{new}+[F(x_{low})-\frac{F(x_{high})-F(x_{low})}{x_{high}-x_{low}}x_{low}]=0$$

可得
$$x_{new} = [\frac{x_{low}F(x_{high})-x_{high}F(x_{low})}{F(x_{high})-F(x_{low})}]$$

代码演示

求解代码

```c++
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
```

全部代码

```c++
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
```

### 3.3 Newton-Raphson法

求解非线性方程最流行的方法

