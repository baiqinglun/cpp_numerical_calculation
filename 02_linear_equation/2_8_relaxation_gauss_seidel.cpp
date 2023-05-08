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

namespace RelaxationGaussSeidel
{

}

int main(){
    std::cout << "555" << std::endl;

    return 0;
}