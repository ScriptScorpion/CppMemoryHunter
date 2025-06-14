#ifndef REPORT_CPP
#define REPORT_CPP
#include <iostream>
#include <string>
void issue(std::string x,  int y) {
     std::cout << "\033[1;33m[!]\033[0m Memory leak in file named: " << x << " " << "In line number: " << y << std::endl;
}
// Idea 1. Add suggestion how to fix issue: Done
// Idea 2. Add C language support
#endif