//
// Created by DELL on 2023/10/26.
//
#include <algorithm>
#include <iostream>
#include <string>
// Polygon Mesh
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Surface_mesh.h>
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_3 Point;
typedef CGAL::Surface_mesh<Point> Surface_mesh;
#define CGAL_USE_VTK
#include <CGAL/boost/graph/IO/polygon_mesh_io.h>
/*支持obj off ply stl ts(gocad) vtp(vtk)
 *注意
 *1. 数据需是一个二维流形（可能有边界）
 *2. 如果数据不是一个二维流形，可尝试使用CGAL::Polygon_mesh_processing::IO::read_polygon_mesh()
 */

int main() {
    std::string in_path = R"(../static/Deer.obj)";
    std::string out_path = R"(../static/Deer.off)";
    Surface_mesh mesh;

    //内部会按照文件格式分流到具体的读写函数中
    if (!CGAL::IO::read_polygon_mesh(in_path, mesh)) {
        return 0;
    }

    //内部会按照文件格式分流到具体的读写函数中
    if (!CGAL::IO::write_polygon_mesh(in_path, mesh)) {
        std::cout << "Save Failed" << std::endl;
        return 0;
    }
    return 0;
}