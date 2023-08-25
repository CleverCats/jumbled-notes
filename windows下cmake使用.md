```cpp
cmake_minimum_required(VERSION 3.5)

# 设置共享库输出目录为构建目录(在哪里camke)(build)下的的 lib 目录

# 获取当前目录下的所有源文件(.cpp .cxx .cc)(可混合)
aux_source_directory(. root_srcs)

project(study)

# 生成.lib(并非静态库,而是作为dll的如何导向文件(必须有))
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

# 添加并跳转子目录搜索路径(执行路径下的CMakeLists)执行完毕后跳转回来继续执行
add_subdirectory(math)
add_subdirectory(utils)
add_subdirectory(external)

# 获取所有dll后缀变量
# GLOB: 将指定目录下搜索到的满足条件的所有文件名生成一个列表，并将其存储到变量中。
# GLOB_RECURSE：递归搜索指定目录，将搜索到的满足条件的文件名生成一个列表，并将其存储
file(GLOB DLL_SRC ${PROJECT_SOURCE_DIR}/lib/*.dll)

# 复制*.dll文件到可执行文件(exe)同级目录下,若无此操作则exe运行时无法寻到dll
# 如果需要调试dll源码则需要将.dll .lib .pdb文件都拷贝到exe同级目录下

# file(GLOB DLL_SRC ${PROJECT_SOURCE_DIR}/lib/*.*) 获取所有文件
file(COPY ${DLL_SRC} DESTINATION ${EXECUTABLE_OUTPUT_PATH})

# 添加可执行目标(编译和链接的目标)
add_executable(study2 ${root_srcs})

# windows下link_...和include_...目前我尝试不起作用,建议使用target_...
target_link_directories(study2 PUBLIC  ${PROJECT_SOURCE_DIR}/lib)
target_include_directories(study2 PUBLIC ${PROJECT_SOURCE_DIR}/include)

# 链接依赖库
target_link_libraries(study2 
       external_libarry1_lib
       external_libarry2_lib
       math_power_lib
       math_trigonometry_lib
       utils_lib)

# 定义一个空列表变量
set(include_dirs "")
# 定义递归查找头文件目录的函数
function(include_sub_directories_recursively root_dir)
    if (IS_DIRECTORY ${root_dir})
        message("append dir: " ${root_dir})
        list(APPEND include_dirs ${root_dir})
        # set(include_dirs "${include_dirs}" PARENT_SCOPE)
    endif ()
    file(GLOB ALL_SUB RELATIVE ${root_dir} ${root_dir}/*)
    foreach (sub ${ALL_SUB})
        if (IS_DIRECTORY ${root_dir}/${sub})
            include_sub_directories_recursively(${root_dir}/${sub})
        endif ()
    endforeach ()
    # 递归调用结束后都能够将更新后的include_dirs变量传递回父作用域
    set(include_dirs "${include_dirs}" PARENT_SCOPE)
endfunction()

# 调用函数来查找src下所有的头文件目录, 记录在include_dirs中
include_sub_directories_recursively(${PROJECT_SOURCE_DIR}/mapper/src)

//======================linux proto编译===============================
# 寻找 Protobuf 库并自动设置相关变量(如PROTOBUF_PROTOC_EXECUTABLE/头文件/库路径)
# REQUIRED 关键字表示 Protobuf 库是必需的, 找不到则报错并终止构建过程
find_package(Protobuf REQUIRED)

# 设置 protoc 命令文件的路径(否者无法使用protoc命令)(可省-find_package已设置)
# set(PROTOBUF_PROTOC_EXECUTABLE ${PROTOBUF_PROTOC_EXECUTABLE})

# 设置 .proto 文件的路径
set(PROTO_FILE userservice.proto)

# 设置生成的 .cc 文件和 .h 文件的存放位置
set(PROTO_SRC_DIR ${PROJECT_SOURCE_DIR}/src)
set(PROTO_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/src/include)

# execute_process 允许执行外部shell命令, cmake文件中不能直接执行shell
# COMMAND 用于指定需要执行的命令 execute_process(COMMAND cmd arg1 arg2 ...)
# execute_process(command -E 命令s 命令s参数1 命令s参数2) 
# (-E表示常用的系统操作，例如创建目录、复制文件、删除文件等)
# (protoc不是这种命令所以无-E)
# 一个execute_process只能执行一条shell
# 执行 protoc 命令，生成 .cc 和 .h 文件
# PROTO_SRC_DIR .h, .cc统一的输出路径
# CMAKE_CURRENT_SOURCE_DIR .proto文件所在路径(默认当前命令执行路径current_cmake_lists同级)
# PROTO_FILE 具体.proto文件名
execute_process(
    COMMAND ${PROTOBUF_PROTOC_EXECUTABLE} --cpp_out=${PROTO_SRC_DIR} --proto_path=${CMAKE_CURRENT_SOURCE_DIR} ${PROTO_FILE}
)

# 分别获取.cc/.h 在目标目录下进行拷贝
file(GLOB PROTO_SRCS "${PROTO_SRC_DIR}/*.cc")
file(GLOB PROTO_HDRS "${PROTO_SRC_DIR}/*.h")

file(COPY ${PROTO_SRCS} DESTINATION ${PROTO_SRC_DIR})
file(COPY ${PROTO_HDRS} DESTINATION ${PROTO_INCLUDE_DIR})
```
