cmake_minimum_required(VERSION 3.17)
project(Learn_CGAL)

set(CMAKE_CXX_STANDARD 11)
find_package(CGAL REQUIRED)

include(${CGAL_USE_FILE})

add_executable(Learn_CGAL main.cpp)
target_link_libraries(Learn_CGAL ${CGAL_LIBRARIES} m)

# 尝试使用cmake自动加入，发现似乎不太行，改为使用C/C++ Single File Execution插件
# 创建一个列表来存储可执行文件的名称
#set(executables_list "")
#
## 创建一个 target per cpp file
#file(
#        GLOB cppfiles
#        RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
#        ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

#foreach(cpp_file ${cpp_files})
#    get_filename_component(executable_name ${cpp_file} NAME_WE)
#    message(executable_name)
#    add_executable(${executable_name} ${cpp_file})
#    # 将当前可执行文件的名称添加到列表中
#    list(APPEND executables_list ${executable_name})
#endforeach()
#
## 使用 target_link_libraries 将所有的可执行文件链接到 CGAL 库
#target_link_libraries(${executables_list} ${CGAL_LIBRARIES} m)
#foreach(cpp_file ${cpp_files})
#    get_filename_component(executable_name ${cpp_file} NAME_WE)
#    message(executable_name)
#    add_executable(${executable_name} ${cpp_file} Test.cpp)
#    # 使用 target_link_libraries 将当前可执行文件链接到 CGAL 库
#    target_link_libraries(${executable_name} INTERFACE ${CGAL_LIBRARIES} m)
#endforeach()

add_executable(basic_001 Basic/basic_001.cpp)
add_executable(basic_002 Basic/basic_002.cpp)
add_executable(basic_003 Basic/basic_003.cpp)
add_executable(basic_004 Basic/basic_004.cpp)
add_executable(basic_005 Basic/basic_005.cpp)

add_executable(nearest_neighbor Point_set_2/nearest_neighbor.cpp)
add_executable(Polygon Polygon/Polygon.cpp)
add_executable(Polygon_algorithms Polygon/Polygon_algorithms.cpp)
add_executable(OBJ IO/OFF.cpp)
add_executable(OFF IO/OBJ.cpp)
add_executable(AABBTree SpatialIndex/AABBTree.cpp)
add_executable(QuadTree SpatialIndex/QuadTree.cpp)
add_executable(hds_prog_vector HalfedgeDS/hds_prog_vector.cpp)