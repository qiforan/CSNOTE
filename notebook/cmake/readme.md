# Hello CMake

## Concepts

`CMakeLists.txt` 是存储 CMake 命令的文件，运行 cmake 时会寻找该文件，找不到则报错。

可以使用以下命令指定支持的最小版本的 CMake

```shell
cmake_minimum_required(VERSION 3.5)
```

`proect()`命令指定工程相关信息，如工程名，本质是给相关变量赋值，例如。

* `PROJECT_NAME`：将当前工程的名称赋值给 `PROJECT_NAME`
* `PROJECT_SOURCE_DIR`：当前工程的源码路径
* `<PROJECT-NAME>_SOURCE_DIR`：指定工程的源码路径
* `PROJECT_BINARY_DIR`：当前工程的二进制路径
* `<PROJECT-NAME>_BINARY_DIR`：指定工程的二进制路径
* `CMAKE_PROJECT_NAME`：顶层工程的名称

`add_executable()`指定可执行文件构建的源文件

```shell
add_executable(executable src_list)
```

>可执行文件可以和工程名 `${PROJECT_NAME}` 相同

`C_MAKE_BINARY`是运行 cmake 命令的根目录或顶层目录，也是生成相关二进制文件的根目录。

***

内部构建(In-Place Build)是指生成的临时文件和源文件在同一个目录，即直接在源文件顶层运行

```shell
cmake .
```

外部构建(Out-of-source Build)是指使用单独的 build 的文件来保存临时文件和目标文件，在 build 目录运行 cmake 命令，并指向源文件顶层目录的 `CMakeLists.txt`

```shell
mkdir build
cd build/
make ..
```

***

和目录相关的变量

* `CMAKE_SOURCE_DIR` 源文件的根目录
* `CMAKE_CURRENT_SOURCE_DIR` 当前源文件的目录(CMakeLists.txt 所在目录)
* `CMAKE_CURRENT_BINARY_DIR` 当前的二进制文件目录

***

创建源文件变量

```shell
set(SOURCES
    src/Hello.cpp
    src/main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})
```

也可以使用 `GLOB`命令和通配符来收集源文件到变量(但不推荐)

```shell
file(GLOB SOURCES "src/*.cpp")
```

*** 

包含头文件目录,相当于直接编译的时候使用 `-I` 标志

```shell
target_include_directories(target
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)
```

测试工程目录结构

```shell
cmake-test/                 工程主目录，main.c 调用 libhello-world.so
├── CMakeLists.txt
├── hello-world             生成 libhello-world.so，调用 libhello.so 和 libworld.so
│   ├── CMakeLists.txt
│   ├── hello               生成 libhello.so
│   │   ├── CMakeLists.txt
│   │   ├── hello.c
│   │   └── hello.h         libhello.so 对外的头文件
│   ├── hello_world.c
│   ├── hello_world.h       libhello-world.so 对外的头文件
│   └── world               生成 libworld.so
│       ├── CMakeLists.txt
│       ├── world.c
│       └── world.h         libworld.so 对外的头文件
└── main.c
```

调用关系：

```shell
                                 ├────libhello.so
可执行文件────libhello-world.so
                                 ├────libworld.so
```

三大关键字用法说明：
PRIVATE： **私有的**。生成 `libhello-world.so` 时，只在  hello_world.c 中包含了 hello.h，`libhello-world.so` 对外的头文件 ——hello_world.h 中不包含 hello.h 。而且 main.c 不会调用 hello.c 中的函数，或者说 main.c 不知道 hello.c 的存在，那么在 hello-world/CMakeLists.txt 中应该写入：

```shell
target_link_libraries(hello-world PRIVATE hello) // hello-world 表示可执行文件目标
target_include_directories(hello-world PRIVATE hello)
```

INTERFACE： **接口**，即提供了接口。生成 `libhello-world.so` 时，只在 `libhello-world.so` 对外的头文件 —— hello_world.h 中包含 了 hello.h， hello_world.c 中不包含 hello.h，即 `libhello-world.so` 不使用 `libhello.so` 提供的功能，只使用 hello.h 中的某些信息，比如结构体。但是 main.c 需要使用 `libhello.so` 中的功能。那么在 hello-world/CMakeLists.txt 中应该写入：

```shell
target_link_libraries(hello-world INTERFACE hello)
target_include_directories(hello-world INTERFACE hello)
```

PUBLIC：**公开**的。PUBLIC = PRIVATE + INTERFACE。生成`libhello-world.so` 时，在 hello_world.c 和 hello_world.h 中都包含了 hello.h。并且 main.c 中也需要使用 `libhello.so` 提供的功能。那么在 hello-world/CMakeLists.txt 中应该写入：

```shell
target_link_libraries(hello-world PUBLIC hello)
target_include_directories(hello-world PUBLIC hello)
```

实际上，这三个关键字指定的是目标文件依赖项的使用范围（scope）或者一种传递（propagate）。具体来说：就是对内而言，是否使用？对外而言，是否要传递出去？

本例中：
可执行文件依赖 `libhello-world.so`， `libhello-world.so` 依赖 `libhello.so` 和 `libworld.so`。

main.c 不使用 `libhello.so` 的任何功能，因此 `libhello-world.so` 不需要将其依赖 —— `libhello.so` 传递给 main.c，hello-world/CMakeLists.txt 中使用 PRIVATE 关键字；
main.c 使用 `libhello.so` 的功能，但是 `libhello-world.so` 不使用，hello-world/CMakeLists.txt 中使用 INTERFACE 关键字；
main.c 和 `libhello-world.so` 都使用 `libhello.so` 的功能，hello-world/CMakeLists.txt 中使用 PUBLIC 关键字；

`target_include_directories()` 的功能完全可以使用 `include_directories()`实现，但是前者比后者好的地方在于，后者是一个全局包含，向下传递，可能会导致生成一堆不必要的 include

***

创建静态库

```shell
# 创建一个 libhello_library.a 的静态库
add_library(hello_library STATIC
    src/Hello.cpp
)

```

***

生成可执行文件必须告诉编译器使用的库

```shell
add_executable(hello_binary
    src/main.cpp
)

target_link_libraries( hello_binary
    PRIVATE
        hello_library
)
```

三个关键字的用法：

* 如果源文件 (例如 CPP) 中包含第三方头文件，但是头文件（例如 hpp）中不包含该第三方文件头，采用 PRIVATE。
* 如果源文件和头文件中都包含该第三方文件头，采用 PUBLIC。
* 如果头文件中包含该第三方文件头，但是源文件 (例如 CPP) 中不包含，采用 INTERFACE。

***
