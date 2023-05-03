/**
 * @brief: 求解几何中心、面积与形心
 * @description: 
 * 
 *              节点    1   2   3   4   5
 *              x坐标   1.0 2.4 2.0 0.4 0.0
 *              y坐标   6.4 4.0 0.2 0.0 4.0
 * @birth: created by Dablelv on bql at 
 */
#include<iostream>
#include<math.h>

using namespace std;

class Triangle
{
private:
    int n;
    double *x,      // x坐标
            *y,     // y坐标
            *As,     // 每个三角形的面积
            **geometric_centers,      // 每个三角形的几何中心
            *centroid,       // 单元的形心
            *geometric_center,       // 单元的几何中心
            A;              // 单元的面积

public:
    Triangle();
    ~Triangle();
    void input();
    void calArea();
    void calCentroid();
    void calGeometricCenter();
};

Triangle::Triangle()
{
    x = nullptr;
    y = nullptr;
    As = nullptr;
    geometric_centers = nullptr;
    centroid = nullptr;
    geometric_center = nullptr;
}

Triangle::~Triangle()
{
    delete [] x;
    delete [] y;
    delete [] As;
    for(int i = 0; i < n; ++i)
    {
        delete [] geometric_centers[i];
    };
    delete [] geometric_centers;
    delete [] centroid;
    delete [] geometric_center;
}

void Triangle::input()
{
    std::cout << "\n请输入顶点个数" << std::endl;
    cin >> n;

    std::cout << "\n请输入x的值" << std::endl;
    x = new double[n];
    for(int i = 0; i < n; ++i)
    {
        std::cout << "\nx[" << i << "] = ";
        cin >> x[i];
    };
    
    std::cout << "\n请输入y的值" << std::endl;
    y = new double[n];
    for(int i = 0; i < n; ++i)
    {
        std::cout << "\ny[" << i << "] = ";
        cin >> y[i];
    };
    
}

/**
 * @fname: calGeometricCenter
 * @brief: 几何中心
 * @param: void
 * @return: void
 * @birth: created by Dablelv on bql
 */
void Triangle::calGeometricCenter()
{
    geometric_center = new double[2];
    double sumX = 0.0,sumY = 0.0;
    for(int i = 0; i < n; ++i)
    {
        sumX += x[i];
        sumY += y[i];
    };
    geometric_center[0] = sumX / n;
    geometric_center[1] = sumY / n;

    std::cout << "\n整个单元的几何中心为:x = " << geometric_center[0] << " y = " << geometric_center[1] << std::endl;
}

/**
 * @fname: calArea
 * @brief: 计算单元的总面积，先计算每个三角形的形心和面积
 * @param: void
 * @return: void
 * @birth: created by Dablelv on bql
 */
void Triangle::calArea()
{
    As = new double[n];
    A = 0.0;
    double *vector1 = new double[2];
    double *vector2 = new double[2];
    for(int i = 0; i < n; ++i)
    {
        if(4 == i)
        {
            vector1[0] = (x[0] - x[i]);
            vector1[1] = (y[0] - y[i]);
            vector2[0] = (geometric_center[0] - x[i]);
            vector2[1] = (geometric_center[1] - y[i]);
        }else
        {
            vector1[0] = (x[i+1] - x[i]);
            vector1[1] = (y[i+1] - y[i]);
            vector2[0] = (geometric_center[0] - x[i]);
            vector2[1] = (geometric_center[1] - y[i]);
        }
        As[i] = 0.5* abs(vector1[0] * vector2[1] - vector1[1] * vector2[0]);
        A += As[i];
        std::cout << "\nAs["  << i << "] = " << As[i] << std::endl;
    };
    std::cout << "\nA = "  << A << std::endl;
    delete [] vector1;
    delete [] vector2;
}

/**
 * @fname: calCentroid
 * @brief: 计算单元的形心
 * @param: void
 * @return: void
 * @birth: created by Dablelv on bql
 */
void Triangle::calCentroid()
{
    geometric_centers = new double* [n];
    for(int i = 0; i < n; ++i)
    {
        geometric_centers[i] = new double[2];
    };
    // 求解全部三角形的几何中心
    for(int i = 0; i < n; ++i)
    {
        if(4 == i)
        {
            geometric_centers[i][0] = (x[i] + x[0] + geometric_center[0]) / 3;
            geometric_centers[i][1] = (y[i] + y[0] + geometric_center[1]) / 3;
        }else
        {
            geometric_centers[i][0] = (x[i] + x[i+1] + geometric_center[0]) / 3;
            geometric_centers[i][1] = (y[i] + y[i+1] + geometric_center[1]) / 3;
        }
    };

    double sumX = 0.0;
    double sumY = 0.0;
    for(int i = 0; i < n; ++i)
    {
        sumX += geometric_centers[i][0] * As[i];
        sumY += geometric_centers[i][1] * As[i];
    };

    centroid = new double[2];
    centroid[0] = sumX / A;
    centroid[1] = sumY / A;
    std::cout << "\n单元的形心为: x = " << centroid[0] << " y = " << centroid[1] << std::endl;
}

int main(){
    Triangle t;
    t.input();
    t.calGeometricCenter();
    t.calArea();
    t.calCentroid();

    return 0;
}