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

void analyzeFile(const std::string &file_path) {

     bool hasMemoryLeakIssues = false; 
     std::ifstream file(file_path);
     if (!file.is_open()) {
          std::cerr << "\033[1;31m[!]\033[0m Error: Could not open file " << file_path << std::endl;
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
               trimmedLine.find("new[") != std::string::npos;
          bool hasDelete = trimmedLine.find("delete ") != std::string::npos || 
               trimmedLine.find("delete[]") != std::string::npos;

          if (hasNew && !hasDelete) {
               issue(filename, lineNumber);
          }

          // 2. check just for pointers
          size_t ptrPos = trimmedLine.find('*');
          if (ptrPos != std::string::npos) {
            // cheking if real pointers
               bool isPointerDeclaration = true;
        
            // cheking connected words
               if (ptrPos > 0 && (trimmedLine[ptrPos-1] == '/' || trimmedLine[ptrPos-1] == ' ')) {
                    isPointerDeclaration = false;
               }

               if (isPointerDeclaration) {
                // cheking if memory setted for pointer
                    bool hasAllocation = trimmedLine.find('=', ptrPos) != std::string::npos && 
                         (trimmedLine.find("new", ptrPos) != std::string::npos ||
                         trimmedLine.find("malloc", ptrPos) != std::string::npos);
               if (!hasAllocation) {
                         issue(filename, lineNumber);
                    
               }
               }
          }
     }
}



// void analyzeFile(const std::string &file_path) {
//      std::ifstream file(file_path);
//      if (!file.is_open()) {
//         std::cerr << "[!] Error: Could not open file " << file_path << std::endl;
//         return;
//      }

//     // Извлекаем имя файла из пути (для вывода в issue())
//      std::string filename = file_path.substr(file_path.find_last_of("/\\") + 1);

//      std::string line;
//      int lineNumber = 0;
//      bool inCommentBlock = false;

//      while (std::getline(file, line)) {
//           lineNumber++;
//           std::string trimmedLine = line;

//         // Удаляем однострочные комментарии
//           size_t commentPos = trimmedLine.find("//");
//           if (commentPos != std::string::npos) {
//                trimmedLine = trimmedLine.substr(0, commentPos);
//           }

//         // Проверяем начало/конец блочного комментария
//           if (trimmedLine.find("/*") != std::string::npos) inCommentBlock = true;
//           if (trimmedLine.find("*/") != std::string::npos) {
//                inCommentBlock = false;
//                continue;
//           }
//           if (inCommentBlock) continue;

//         // 1. Проверка на несбалансированные new/delete
//           bool hasNew = trimmedLine.find("new ") != std::string::npos || 
//                trimmedLine.find("new[") != std::string::npos;
//           bool hasDelete = trimmedLine.find("delete ") != std::string::npos || 
//                trimmedLine.find("delete[]") != std::string::npos;

//           if (hasNew && !hasDelete) {
//             issue(filename, lineNumber);
//           }

//          // 2. Проверка на "голые" указатели, которые могут привести к утечкам
//           size_t ptrPos = trimmedLine.find('*');
//           if (ptrPos != std::string::npos) {
//             // Проверяем, что это объявление указателя (не умножение и не комментарий)
//                bool isPointerDeclaration = true;
            
//             // Проверяем соседние символы
            
//                if (ptrPos > 0 && (trimmedLine[ptrPos-1] == '/' || trimmedLine[ptrPos-1] == ' ')) {
//                     isPointerDeclaration = false;
//                }

//           if (isPointerDeclaration) {
//                 // Проверяем, есть ли выделение памяти для этого указателя
//                     bool hasAllocation = trimmedLine.find('=', ptrPos) != std::string::npos && 
//                          (trimmedLine.find("new", ptrPos) != std::string::npos ||
//                          trimmedLine.find("malloc", ptrPos) != std::string::npos);
//                if (!hasAllocation) {
//                     issue(filename, lineNumber);
//                }
//           }
//           }
//      }
// }


#endif