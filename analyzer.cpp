#ifndef ANALYZER_CPP
#define ANALYZER_CPP
#include <algorithm>
#include <memory>
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "report.cpp"
#include <filesystem>

void analyzeCPPFile(const std::string &file_path) {

     std::ifstream file(file_path);
     if (!file.is_open()) {
          std::cout << "\033[1;31m[!]\033[0m Error: Could not open file " << file_path << std::endl;
          return;
     }

     // getting filename
     std::string filename = file_path.substr(file_path.find_last_of("/\\") + 1);

     std::string line;
     int lineNumber = 0;
     bool inCommentBlock = false;

     while (std::getline(file, line)) {
          lineNumber++;
          std::string trimmedLine = line;

          // delete comments
          size_t commentPos = trimmedLine.find("//");
          if (commentPos != std::string::npos) {
               trimmedLine = trimmedLine.substr(0, commentPos);
          }

        // cheking start and end comments
          if (trimmedLine.find("/*") != std::string::npos) inCommentBlock = true;
          if (trimmedLine.find("*/") != std::string::npos) {
               inCommentBlock = false;
               continue;
          }
          if (inCommentBlock) continue;

        // 1. check for new/delete
          bool hasNew = trimmedLine.find("new ") != std::string::npos || 
               trimmedLine.find("new[]") != std::string::npos;
          bool hasDelete = trimmedLine.find("delete ") != std::string::npos || 
               trimmedLine.find("delete[]") != std::string::npos;

          if (hasNew && !hasDelete) {
               issue(filename, lineNumber);
          }

          // 2. check just for pointers
          size_t ptrPos = trimmedLine.find('*');
          if (ptrPos != std::string::npos) {
               bool isPointerDeclaration = true;
            
               if (ptrPos > 0 && (trimmedLine[ptrPos-1] == '/' || 
                         trimmedLine[ptrPos-1] == ' ' || 
                         trimmedLine[ptrPos-1] == '+' || 
                         trimmedLine[ptrPos-1] == '-' ||
                         trimmedLine[ptrPos-1] == '=')) {
               isPointerDeclaration = false;
               }

               if (isPointerDeclaration) {
                    bool hasAllocation = (trimmedLine.find('=', ptrPos) != std::string::npos) && 
                         (trimmedLine.find("new", ptrPos) != std::string::npos);
               if (!hasAllocation) {
                    issue(filename, lineNumber);
               }
            }
        }
    }
}

void analyzeCFile(const std::string &file_path) {
    std::ifstream file(file_path);
    if (!file.is_open()) {
        std::cerr << "\033[1;31m[!]\033[0m Error: Could not open file " << file_path << std::endl;
        return;
    }

    std::string filename = file_path.substr(file_path.find_last_of("/\\") + 1);
    std::string line;
    int lineNumber = 0;
    bool inCommentBlock = false;

    while (std::getline(file, line)) {
        lineNumber++;
        std::string trimmedLine = line;

        // comments
        if (trimmedLine.find("/*") != std::string::npos) inCommentBlock = true;
        if (trimmedLine.find("*/") != std::string::npos) {
            inCommentBlock = false;
            continue;
        }
        if (inCommentBlock) continue;

        // 1. Check for malloc/free
        bool hasMalloc = (trimmedLine.find("malloc(") != std::string::npos) ||
                        (trimmedLine.find("calloc(") != std::string::npos);
        bool hasFree = (trimmedLine.find("free(") != std::string::npos);

        if (hasMalloc && !hasFree) {
            issue(filename, lineNumber);
        }

        // 2. Cheack just for pointers
        size_t ptrPos = trimmedLine.find('*');
        if (ptrPos != std::string::npos) {
            bool isPointerDeclaration = true;
            
            if (ptrPos > 0 && (trimmedLine[ptrPos-1] == '/' || 
                              trimmedLine[ptrPos-1] == ' ' || 
                              trimmedLine[ptrPos-1] == '+' || 
                              trimmedLine[ptrPos-1] == '-' ||
                              trimmedLine[ptrPos-1] == '=')) {
                isPointerDeclaration = false;
            }

            if (isPointerDeclaration) {
                bool hasAllocation = (trimmedLine.find('=', ptrPos) != std::string::npos) && 
                                    (trimmedLine.find("malloc", ptrPos) != std::string::npos);
                if (!hasAllocation) {
                    issue(filename, lineNumber);
                }
            }
        }
    }
}

#endif