/**
 * @brief: Gauss-Seidel迭代
 * @birth: created by Dablelv on bql at 2023-05-06
 */



#include<iostream>
#include<math.h>
#include<vector>

using vector_1d = std::vector<double>;
using vector_2d = std::vector<vector_1d>;

namespace Tool
{
    /**
     * @fname: 交换矩阵行列
     * @brief: vector_2d &a：需要交换的矩阵
     *          const int k：从第几行开始交换
     *          const int pivrow：最大的行
     * @param: void
     * @return: void
     * @birth: created by Dablelv on bql
     */
    void swap(vector_2d &a,const int k,const int pivrow)
    {
        double temp;
        int n = a.size();
        for(int j = k;j<n+1;j++){
            temp = a[k][j];
            a[k][j] = a[pivrow][j];
            a[pivrow][j] = temp;
        }
    }

    /**
     * @fname: da
     * @brief: 
     * @param: void
     * @return: void
     * @birth: created by Dablelv on bql
     */
    void printMatix(const vector_2d &a,const std::string msg)
    {
        int row = a.size();
        int col = a[0].size();
        std::cout << "\n"+msg+"为：" <<  std::endl;
        for(int i=0;i<row;i++){
            for(int j=0;j<col;j++){
                std::cout <<  a[i][j] << "\t";
            }
            std::cout << std::endl;
        }
    }

    void printX(const vector_1d &x)
    {
        int n = x.size();
        std::cout << "\n输出结果:"<< std::endl;
        for(int i=0;i<n;i++){
            std::cout << "x[" << i << "] = " << x[i] << std::endl;
        }
    }
}

namespace GaussSeidel
{
    void solve(vector_2d &a,vector_1d &b,vector_1d &x, const double eps)
    {
        int flag = 0,
            iter = 0,
            n = a.size();
        double xold = 0.0,
                sum = 0.0,
                error = 0.0;
        do
        {
            flag = 0;
            iter ++;
            std::cout << "第" << iter << "次迭代" << std::endl;
            for(int i = 0; i < n; ++i)
            {
                xold = x[i];    // 使用之前的值就是为了记录一下，求解残差
                sum = 0.0;
                for(int j = 0; j < n; ++j)
                {
                    if(j != i) sum += a[i][j] * x[j];
                };
                x[i] = (b[i] - sum) / a[i][i];
                error = fabs(xold - x[i]) / x[i];
                if(error >= eps){ flag = 1; }
            };
        }while(flag == 1);
        std::cout << "迭代完成" << std::endl;
    }
}


int main(){
    vector_2d a = {
        {-3.5, 1, 1.5},
        {1, 4, -1},
        {-2, -0.6, -3.5}
    };
    vector_1d b = {2.5,4,-16};
    vector_1d x = {0,0,0};
    double eps = 1e-6;
    GaussSeidel::solve(a,b,x,eps);
    Tool::printX(x);

    return 0;
}