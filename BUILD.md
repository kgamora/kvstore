In the project directory:

```
mkdir build
cmake -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_C_COMPILER=clang .. # you can use something other than clang
make -j10 # replace 10 with the number of threads you think is suitable for your machine
```

