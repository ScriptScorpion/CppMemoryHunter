#ifndef REPORT_CPP
#define REPORT_CPP
#include <iostream>
#include <string>
void issue(std::string x,  int y) {
     std::cout << "[+] Memory leak in file named: " << x << " " << "In line number: " << y << std::endl;
}
// Idea 1. Add suggestion how to fix issue
// Idea 2. Add C language support
#endif