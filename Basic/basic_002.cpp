//
// Created by DELL on 2023/10/25.
//
#include <CGAL/Simple_cartesian.h>
#include <iostream>
typedef CGAL::Simple_cartesian<double> Kernel;

// 高精度内核
//#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
//typedef CGAL::Exact_predicates_exact_constructions_kernel Kernel
typedef Kernel::Point_2 Point_2;
typedef Kernel::Segment_2 Segment_2;
/**
 * Point_2    2d的点
 * Segment_2  2d的扇形，若只有两个点，则为直线
 * CGAL::squared_distance(p, q): 两点距离or点到直线的距离
 * CGAL::orientation(p, q, m): 三点是否共线，若不共线，则m在p，q哪一侧
 * CGAL::midpoint(p, q):中点坐标
 * */

int main() {
    Point_2 p(1, 1), q(10, 10);
    std::cout << "p = " << p << std::endl;
    std::cout << "q = " << q.x() << " " << q.y() << std::endl;// q = 10 10
    std::cout << "sqdist(p,q) = "
              << CGAL::squared_distance(p, q) << std::endl;// sqdist(p,q) = 162
    Segment_2 s(p, q);
    Point_2 m(5, 9);
    std::cout << "m = " << m << std::endl;// m = 5 9
    std::cout << "sqdist(Segment_2(p,q), m) = "
              << CGAL::squared_distance(s, m) << std::endl;// sqdist(Segment_2(p,q), m) = 8
    std::cout << "p, q, and m ";
    switch (CGAL::orientation(p, q, m)) {
        case CGAL::COLLINEAR:
            std::cout << "are collinear\n";
            break;
        case CGAL::LEFT_TURN:
            std::cout << "make a left turn\n";
            break;
        case CGAL::RIGHT_TURN:
            std::cout << "make a right turn\n";
            break;
    } // p, q, and m make a left turn
    std::cout << "midpoint(p,q) = " << CGAL::midpoint(p, q) << std::endl;// midpoint(p,q) = 5.5 5.5
    return 0;
}