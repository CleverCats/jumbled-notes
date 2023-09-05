



# GRPC部署

## 安装构建grpc所需的基本工具

```shell
更新package：
sudo apt update

安装所需库：
sudo apt-get install build-essential autoconf libtool pkg-config
```

## 克隆仓库

```shell
安装git：
sudo apt install git
克隆存储库：
git clone -b v1.28.x https://gitee.com/slrom/grpc
```

## 子模块源设置gitee

```shell
find ./grpc -name .gitmodules
替换.gitmodules:
[submodule "third_party/zlib"]
	path = third_party/zlib
	url = https://gitee.com/slrom/zlib.git
	# When using CMake to build,the zlib submodule ends up with a
	# generated file that makes Git consider the submodule dirty. This
	# state can be ignored for day-to-day development on gRPC.
	ignore = dirty
[submodule "third_party/protobuf"]
	path = third_party/protobuf
	url = https://gitee.com/slrom/protobuf.git
	branch = 3.0.x
[submodule "third_party/gflags"]
	path = third_party/gflags
	url = https://gitee.com/slrom/gflags.git
[submodule "third_party/googletest"]
	path = third_party/googletest
	url = https://gitee.com/slrom/googletest.git
[submodule "third_party/benchmark"]
	path = third_party/benchmark
	url = https://gitee.com/slrom/benchmark.git
[submodule "third_party/boringssl-with-bazel"]
	path = third_party/boringssl-with-bazel
	url = https://gitee.com/slrom/boringssl.git
[submodule "third_party/boringssl"]
	path = third_party/boringssl
	url = https://gitee.com/slrom/boringssl.git
[submodule "third_party/cares/cares"]
	path = third_party/cares/cares
	url = https://gitee.com/slrom/c-ares.git
	branch = cares-1_12_0
[submodule "third_party/bloaty"]
	path = third_party/bloaty
	url = https://gitee.com/slrom/bloaty.git
[submodule "third_party/abseil-cpp"]
	path = third_party/abseil-cpp
	url = https://gitee.com/slrom/abseil-cpp.git
	branch = lts_2020_02_25
[submodule "third_party/envoy-api"]
	path = third_party/envoy-api
	url = https://gitee.com/slrom/data-plane-api.git
[submodule "third_party/googleapis"]
	path = third_party/googleapis
	url = https://gitee.com/slrom/googleapis.git
[submodule "third_party/protoc-gen-validate"]
	path = third_party/protoc-gen-validate
	url = https://gitee.com/slrom/protoc-gen-validate.git
[submodule "third_party/udpa"]
	path = third_party/udpa
	url = https://gitee.com/slrom/udpa.git
[submodule "third_party/libuv"]
	path = third_party/libuv
	url = https://gitee.com/slrom/libuv.git
[submodule "third_party/libcxx"]
    path = third_party/libcxx
	url = https://gitee.com/slrom/libcxx.git
[submodule "third_party/libcxxabi"]
    path = third_party/libcxxabi
	url = https://gitee.com/slrom/libcxxabi.git
```

## 下载子模块

```shell
cd grpc
根据.gitmodules文件中的路径访问相应子模块并下载：
git submodule update --init
```

## 安装grpc与protobuf工具

```shell
cd grpc

若该文件夹不存在则创建文件夹：
mkdir -p cmake/build

到达cmake/build目录下：
cd cmake/build

编译构建依赖库，通过cmake安装grpc，设置-DgRPC_INSTALL=ON，-DgRPC_BUILD_TESTS=OFF；构建安装路径，通过CMAKE_INSTALL_PREFIX变量指定；想要编译动态库.so文件，设置-DBUILD_SHARED_LIBS=ON：
cmake -DgRPC_INSTALL=ON \
      -DgRPC_BUILD_TESTS=OFF \
      -DCMAKE_INSTALL_PREFIX=/usr/ \
      -DBUILD_SHARED_LIBS=ON \
      ../..
编译：
make -j16

安装：
sudo make install


```

## 测试

```shell
cd grpc/examples/cpp/helloworld
mkdir -p cmake/build
cd cmake/build
cmake ../..
make -j16
```

```shell
./greeter_server
./greeter_client
终端: Greeter received: Hello world 
环境搭建成功
```
