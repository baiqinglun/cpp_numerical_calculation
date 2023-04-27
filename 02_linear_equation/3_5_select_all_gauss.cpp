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
        double max = a[k][k];
        pivrow = k;
        for(int i=k+1;i<n;i++){
            if(a[i][k] > max){
                max = a[i][k];
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