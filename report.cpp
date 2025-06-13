#ifndef REPORT_CPP
#define REPORT_CPP
#include <iostream>
#include <string>
void issue(std::string x,  int y) {
     std::cout << "Memory leak in file named " << x << std::endl;
     std::cout << "Memory leak in line number " << y << std::endl;
}
#endif