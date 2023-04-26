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