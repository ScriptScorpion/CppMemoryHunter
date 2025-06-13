#include <iostream>
#include <filesystem>
#include "analyzer.cpp"
namespace fs = std::filesystem;
void printLogo() {
    std::cout << R"(
   C p p  M E M O R Y 
   H U N T E R  1.0  
    )" << std::endl;
}

int main(int argc, char* argv[]) {
    printLogo();
    std::cout << "Enter Path to File: ";
    std::string path_str;
    std::getline(std::cin, path_str); // Читаем весь ввод (пробелы в путях учтитываем)

    fs::path input_path(path_str); // Преобразуем в filesystem::path

    // Проверка существования пути
    if (!fs::exists(input_path)) {
        std::cout << "Error:File dont exist!\n";
        return 1;
    }

    // Если это файл — анализируем его
    if (fs::is_regular_file(input_path)) {
        analyzeFile(input_path.string()); // giving string
    }
    // Если это папка — анализируем все .cpp файлы внутри
    else if (fs::is_directory(input_path)) {
        for (const auto& entry : fs::directory_iterator(input_path)) {
            if (entry.path().extension() == ".cpp") {
                analyzeFile(entry.path().string());
            }
        }
    }

}