//
// Created by DELL on 2023/10/25.
//
/**
 * 凸包：在高维空间中有一群散布各处的点，凸包是包覆这群点的所有外壳当中，
 * 表面积or容积最小的一个外壳，而最小的外壳一定是凸的。
 * */
#include <iostream>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/convex_hull_2.h>
#include <vector>
typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef Kernel::Point_2 Point_2;
typedef std::vector<Point_2> Points;

int main() {
    Points points,result;
    points.push_back(Point_2(0,0));
    points.push_back(Point_2(10,0));
    points.push_back(Point_2(10, 10));
    points.push_back(Point_2(5, 6));
    points.push_back(Point_2(4, 1));
    CGAL::convex_hull_2(points.begin(), points.end(), std::back_inserter(result));
    std::cout << result.size() << " points on the convex hull" << std::endl;
    for (int i = 0; i < result.size(); i++) {
        std::cout << result[i] << std::endl;
    }
    return 0;
}