![](https://test-123456-md-images.oss-cn-beijing.aliyuncs.com/img/20230504161149.png)


1、计算基本参数：网格大小、gDiff（用于控制方程系数）

```c++
double dx = L / n;
double gDiff_face = A / dx;
double gDiff_wall = 2 * A / dx;
```

2、求解方程中系数

这里为一维棒，可分为边界wall和内部面

![控制方程](https://test-123456-md-images.oss-cn-beijing.aliyuncs.com/img/20230504161425.png)

```c++
double a_wall = -k * gDiff_wall;
double a_face = -k * gDiff_face;

double ac_wall = -(a_wall + a_face);
double ac_face = -(a_face * 2);
```

3、求解源项

源项由第一种边界条件计算（恒温）

```c++
double bc_left = - a_wall * T1;
double bc_right = - a_wall * T2;
```

4、组装方程

根据性质组装方程

![组装矩阵](https://test-123456-md-images.oss-cn-beijing.aliyuncs.com/img/20230504162225.png)

```c++
for(int i = 0; i < n; ++i)
{
    if(i == 0)
    {
        a[0][0] = ac_wall;
        a[0][1] = a_face;
    }
    else if((n-1) == i)
    {
        a[n-1][n-2] = a_face;
        a[n-1][n-1] = ac_wall;
    }
    else
    {
        for(int j = i-1; j <= i+1; ++j)
        {
            (i == j) ? (a[i][j] = ac_face) : (a[i][j] = a_face);
        };
    }
};
printMatix("构造矩阵");

// 源项
for(int i = 0; i < n; ++i)
{
    if(0 == i)
    {
        a[i][n] = bc_left;
    }
    else if((n-1) == i)
    {
        a[i][n] = bc_right;
    }
    else
    {
        a[i][n] = 0;
    }
};
```

使用高斯列主元求解，这里可以使用其他方法求解。