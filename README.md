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

