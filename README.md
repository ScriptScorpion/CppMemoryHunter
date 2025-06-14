CppMemoryHunter, this C++ code analyzer for memory leaks in dynamic memory.
Supported Languages: C++,C.
# How install
* Download gcc: For Windows download latest gcc from github "https://github.com/brechtsanders/winlibs_mingw/releases/" and edit PATH variable in Windows settings; For Linux install gcc from mirror "https://ftp.gnu.org/gnu/gcc/gcc-15.1.0/" and then "tar -xf gcc-15.1.0.tar.gz" and then "cd  gcc-15.1.0" and then "./configure -v --build=x86_64-linux-gnu --host=x86_64-linux-gnu --target=x86_64-linux-gnu --prefix=/usr/local/gcc-15.1.0 --enable-checking=release --enable-languages=c,c++  --program-suffix=-15.1.0" and then "make" and "sudo make install"
* 
* g++ main.cpp analyzer.cpp report.cpp -o analyzer -std=c++15 -lstdc++fs
* ./analyzer.exe
* or
* .\analyzer.exe
