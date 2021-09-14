# VH-DSSE

This repository is an implementation of Volume-Hiding Dynamic Searchable Symmetric Encryption with Forward and Backward Privacy [[link]](https://eprint.iacr.org/2021/786.pdf).

## Requirements

* openssl >= 1.0

## Building

```
git clone https://github.com/lisaGuojl/VH-DSSE.git
cd VH-DSSE
mkdir build
cd build
cmake ..
make
```

## Running
After compiling the project, two executable files *StaticTest* and *DynamicTest* will be generated. 
*StaticTest* is used to evaluate the performance of the Modified Static Volume-hiding SSE scheme *dprfMM*.
*DynamicTest* is used to evaluate the performance of Single-Copy VH-DSSE.
```
# For dprfMM test
./StaticTest
# For VH-DSSE test
./DynamicTest
```



