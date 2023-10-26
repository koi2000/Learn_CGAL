//
// Created by DELL on 2023/10/26.
//
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/IO/OFF/File_writer_OFF.h>
#include <CGAL/IO/Polyhedron_iostream.h>
#include <CGAL/Polyhedron_3.h>
#include <fstream>
#include <iostream>
typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef Kernel::Point_3 Point_3;
typedef CGAL::Polyhedron_3<Kernel> Polyhedron;
/*
 * OFF文件全是以OFF关键字开始的ASCII文件。
 * 下一行说明顶点的数量、面片的数量、边的数量。边的数量可以安全地省略。
 * 顶点按每行一个列出x、y、z坐标。在顶点列表后，面片按照每行一个列表，
 * 对于每个面片，顶点的数量是指定的，接下来是顶点索引列表。
 * */
/**
 * OFF
 * 顶点数 面片数 边数
 * x y z
 * x y z
 * ...
 * n个顶点 顶点1的索引 顶点2的索引 … 顶点n的索引
 * ...
 * */


//void print_OFF(std::ostream &out) {
//    CGAL::File_header_OFF header(binary, noc, skel, verbose);
//    CGAL::File_writer_OFF writer(header);
//    writer.write_header(out, points.size(), 0, facets.size());
//    while (!points.empty()) {
//        writer.write_vertex(points.front().x(),
//                            points.front().y(),
//                            points.front().z());
//        points.pop_front();
//    }
//    writer.write_facet_header();
//    while (!facets.empty()) {
//        Facet &facet = facets.front();
//        writer.write_facet_begin(facet.size());
//        while (!facet.empty()) {
//            writer.write_facet_vertex_index(facet.front());
//            facet.pop_front();
//        }
//        writer.write_facet_end();
//        facets.pop_front();
//    }
//    writer.write_footer();
//}

int main() {
    Polyhedron P;
    const char *filename = "../static/rabbit.OFF";

    std::ifstream input(filename);
    if (!input || !(input >> P) || P.empty()) {
        std::cerr << "Error reading " << filename << std::endl;
        return -1;
    }
    return 0;
}