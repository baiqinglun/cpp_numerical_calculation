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