# cmake 的版本要求
cmake_minimum_required(VERSION 3.14) 

# 项目名称
project(GBN_Network)

# 设置 Debug 模式
set(CMAKE_BUILD_TYPE "Debug")

# # 设置源文件根目录，并设置别名为DIR_ROOT
aux_source_directory(. DIR_ROOT)
aux_source_directory(network DIR_NETWORK)
aux_source_directory(toolkit DIR_TOOLKIT)

# 设置myCppPractice版本标准
set(CMAKE_CXX_STANDARD 14)

set(HOST_ID_1 "1")
set(HOST_ID_2 "2")

# 项目包含哪些 文件
add_executable(${PROJECT_NAME}${HOST_ID_1} testTerminal.cpp ${DIR_NETWORK} ${DIR_TOOLKIT})
set_target_properties(
    ${PROJECT_NAME}${HOST_ID_1} 
    PROPERTIES
    COMPILE_DEFINITIONS HOST_ID="${HOST_ID_1}"
   )
add_executable(${PROJECT_NAME}${HOST_ID_2} testTerminal.cpp ${DIR_NETWORK} ${DIR_TOOLKIT})
set_target_properties(
    ${PROJECT_NAME}${HOST_ID_2}
    PROPERTIES
    COMPILE_DEFINITIONS HOST_ID="${HOST_ID_2}"
   )

# 设置编译选项
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -static")

# 设置输出路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)


# 设置链接库
# target_link_libraries(${PROJECT_NAME} ws2_32)
target_link_libraries(${PROJECT_NAME}${HOST_ID_1} ws2_32)
target_link_libraries(${PROJECT_NAME}${HOST_ID_2} ws2_32)

