# CPP 部分

## includePath

使用 VSCode 进行 c++ 代码编写时，配置 `includePath` 能够提供函数跳转，自动补全以及报错等帮助。


配置 `compileCommands` 自动配置 `includePath` 和 `define`，适用于 `CMakeLists.txt` 编译方式。

`compileCommands` 的官方说明如下：

>The full path to the compile_commands.json file for the workspace. The include paths and defines discovered in this file will be used instead of the values set for includePath and defines settings. If the compile commands database does not contain an entry for the translation unit that corresponds to the file you opened in the editor, then a warning message will appear and the extension will use the includePath and defines settings instead.

**具体步骤**：


**第一步**，生成 `compile_commands.json` 文件。

```shell
cd project_dir
mkdir build  
cd build
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=YES ..
make
```

如上所示，使用 cmake 时通过添加选项 `-DCMAKE_EXPORT_COMPILE_COMMANDS=YES`。

如果是 ROS，则编译命令如下：

```shell
catkin_make -DCMAKE_EXPORT_COMPILE_COMMANDS=YES
```

可在 ROS 工作空间的 `build` 文件夹下找到 `compile_commands.json` 文件

如果不想每次编译时在命令行中添加配置命令，一个简单的方式是在 `CMakeLists.txt` 的上面添加

```shell
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
```

**第二步**，在 `c_cpp_properties.json` 添加

```shell
{
    "configurations": [
        {
            "compileCommands": "${pathTo}/compile_commands.json"
        }
    ],
    "version": 4
}
```

**参考**：

* [vscode使用compile_commands.json配置includePath环境](https://blog.csdn.net/qq_37868450/article/details/105013325)

* [vscode使用compile_commands.json](https://www.cnblogs.com/cong-wang/p/15026530.html)