cmake_minimum_required(VERSION 3.9)

# 项目名称
project(Demo1)


# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_SRCS 变量
aux_source_directory(. DIR_SRCS)

# 添加 third_part子目录, 这样这个目录的下的cmake文件也可以处理
add_subdirectory(third_part)

add_compile_options(-Wl,--no-undefined -std=c++11 -g -O2)

# 添加链接库
add_executable(Demo main.cc)

# 这个链接库要写在后面，否则找不到
target_link_libraries(Demo myprint)
