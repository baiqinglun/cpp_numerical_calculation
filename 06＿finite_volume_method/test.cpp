#include <iostream>
#include <cmath>

using namespace std;

struct Vector {
  double x, y,z;
};

Vector crossProduct(Vector a, Vector b) {
  Vector c;
  c.x = a.y * b.z - a.z * b.y;
  c.y = a.z * b.x - a.x * b.z;
  c.z = a.x * b.y - a.y * b.x;
  return c;
}

double area(Vector a, Vector b) {
  Vector c = crossProduct(a, b);
  double length = sqrt(c.x * c.x + c.y * c.y + c.z * c.z);
  return length / 2;
}

int main() {
  // 声明三个点的坐标
  double x1, y1, x2, y2, x3, y3;
  
  // 获取三个点的坐标
  cout << "请输入三个点的坐标" << endl;
  cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;

  // 计算向量a和向量b
  Vector a, b;
  a.x = x2 - x1;
  a.y = y2 - y1;
  a.z = 0;
  b.x = x3 - x2;
  b.y = y3 - y2;
  b.z = 0;

  // 计算三角形面积
  double triangleArea = area(a, b);

  // 输出结果
  cout << "三角形的面积为：" << triangleArea << endl;

  return 0;
}
