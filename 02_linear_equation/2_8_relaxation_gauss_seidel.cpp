/**
 * @brief: 
 * @birth: created by Dablelv on bql at 
 */
#include<iostream>
#include<math.h>
#include<vector>

using vector_1d = std::vector<double>;
using vector_2d = std::vector<vector_1d>;

namespace Tool
{
    void printX(const vector_1d &x)
    {
        int n = x.size();
        std::cout << "\n输出结果:"<< std::endl;
        for(int i=0;i<n;i++){
            std::cout << "x[" << i << "] = " << x[i] << std::endl;
        }
    }
}

namespace RelaxationGaussSeidel
{
    void solution(vector_2d &a,vector_1d &b, vector_1d &x,const double eps,const double w)
    {
        int flag,
            iter = 0;
        double error,
                sum;
        int n = a.size();
        vector_1d xold(n,0);
        do
        {
            flag = 0;
            iter++;
            std::cout << "\n第" << iter << "次迭代" << std::endl;
            for(int i = 0; i < n; ++i)
            {
                sum = 0.0;
                xold[i] = x[i];
                for(int j = 0; j < n; ++j)
                {
                    if(j != i) {sum += a[i][j] * x[j];}
                };
                x[i] = (b[i] - sum) / a[i][i];
            };
            for(int i = 0; i < n; ++i)
            {
                x[i] = w * x[i] + (1 - w) * xold[i];
            };
            for(int i = 0; i < n; ++i)
            {
                error = fabs((xold[i] - x[i]) / x[i]);
                (error >= eps) ? (flag = 1) : (flag = 0);
            };

        }while(flag == 1);
    }
}

int main(){
    vector_2d a = {
        {4, 2, 0},
        {0.5, 1, 0.5},
        {0, 3, 3}
    };
    vector_1d b = {2.3,1.1,14};
    vector_1d x = {0,0,0};
    double eps = 1e-7;
    double w = 1.5;
    RelaxationGaussSeidel::solution(a,b,x,eps,w);
    Tool::printX(x);
    return 0;
}