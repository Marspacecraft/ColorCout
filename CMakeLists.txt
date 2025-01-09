
# 生成静态库
add_library(ccout STATIC src/ccout.cpp include/ccout.h)
# 设置库的包含目录，以便其他目标能够找到该库的头文件
target_include_directories(ccout PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")