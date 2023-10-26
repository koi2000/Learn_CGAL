//
// Created by DELL on 2023/10/26.
//
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polygon_2.h>
#include <iostream>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point;
typedef CGAL::Polygon_2<K> Polygon_2;
using std::cout; using std::endl;

/**
 * 凸多边形：每个内角都是锐角或钝角，没有大于180度的内角(例如，三角形、正方形)。
 * 凹多边形：至少有一个大于180度的内角(例如，五角星)。
 * */
int main()
{
    Point points[] = { Point(0,0), Point(5.1,0), Point(1,1), Point(0.5,6)};
    Polygon_2 pgn(points, points+4);

    // check if the polygon is simple.
    cout << "The polygon is " <<
         (pgn.is_simple() ? "" : "not ") << "simple." << endl;

    // check if the polygon is convex
    cout << "The polygon is " <<
         (pgn.is_convex() ? "" : "not ") << "convex." << endl;

    return 0;
}
