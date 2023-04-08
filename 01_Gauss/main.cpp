#include <iostream>
#include <iomanip>

using namespace std;
static const int SIZE = 2;

void GaussE()
{
  const int n = SIZE;
  double a[SIZE][SIZE] = {1,1,0.003,3.0};
  double b[SIZE] = {1.0,2.0001};
  double m;
  double x[SIZE];

  // 消元过程
  for (int k = 0; k < n-2; k++)
  {
    for(int i = k+1;i<=n-1;i++){
      m = a[i][k]/a[k][k];
      for(int j = k+1;j<n;j++){
        a[i][j] -= m*a[k][j];
      }
      b[i] -= m*b[k];
    }
  }

  // 回代过程
  for(int k=n-1;k>=0;k--)
  {
    double sum = 0;
    x[k] = 0;

    for(int j=k;j<=n-1;j++){
      sum += a[k][j]*x[j];
    }
    x[k] = (b[k] - sum)/a[k][k];
    cout << "x["<<k<<"]"<<x[k]<<endl;
  }
  
}

int main()
{
  cout.precision(6);
  cout.setf(ios::fixed);
  GaussE();
  system("pause");
  return 0;
}