# 查找当前目录下的所有源文件
# 并将名称命名为DIR_LIB_SRCS变量 
aux_source_directory(. DIR_LIB_SRCS)

# 指定生成打印库
add_library(myprint ${DIR_LIB_SRCS})
