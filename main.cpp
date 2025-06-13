#include <iostream>
#include <filesystem>
#include "analyzer.cpp"
namespace fs = std::filesystem;
void printLogo() {
    std::cout << "\033[1;32m" << R"(
   C + +  M E M O R Y 
   H U N T E R  1.1  
    )" << "\033[0m" << std::endl;
}

int main(int argc, char* argv[]) {
    printLogo();
    std::cout << "Enter Path to File/Directory: ";
    std::string path_str;
    std::getline(std::cin, path_str); // reading input

    fs::path input_path(path_str); // converting filesystem::path

    // Проверка существования пути
    if (!fs::exists(input_path)) {
        std::cout << "\033[1;31m[!]\033[0m Error: File dont exist!\n";
        return 1;
    }

    // if file analyze him
    if (fs::is_regular_file(input_path)) {
        std::cout << "[info] Checking file: " << input_path.string() << std::endl;
        analyzeFile(input_path.string());
    }
    // if folder analyze all .cpp files
    else if (fs::is_directory(input_path)) {
    std::cout << "[info] directory: " << input_path << std::endl;
    
    for (const auto& entry : fs::directory_iterator(input_path)) {
        if (entry.path().extension() == ".cpp") {
            std::cout << "  Scanning file: " << entry.path().filename() << std::endl;
            analyzeFile(entry.path().string()); 
        }
    }
    
}

}