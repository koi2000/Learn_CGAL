//
// Created by DELL on 2023/10/24.
//
#include <CGAL/Simple_cartesian.h>
#include <iostream>
// 设置计算精度
typedef CGAL::Simple_cartesian<double> Kernel;

int main() {
    // 定义几何对象
    Kernel::Point_2 p, q, r;
    std::istringstream iss("1.0 0.1 2.0 0.2 3.0 0.3");
    iss >> p >> q >> r;
    // 执行几何算法
    std::cout << (CGAL::collinear(p, q, r) ? "true" : "false");
    return 0;
}