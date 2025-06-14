#include <iostream>
#include <filesystem>
#include "analyzer.cpp"
namespace fs = std::filesystem;
void printLogo() {
    std::cout << "\033[1;32m" << R"(
   C + +  M E M O R Y 
   H U N T E R  1.2  
    )" << "\033[0m" << std::endl;
}

int main(int argc, char* argv[]) {
    printLogo();
    std::cout << "Enter Path to File/Directory: ";
    std::string path_str;
    std::getline(std::cin, path_str); // reading input

    fs::path input_path(path_str); // converting filesystem::path


    if (!fs::exists(input_path)) {
        std::cout << "\033[1;31m[!]\033[0m Error: File dont exist!\n";
        return 1;
    }

    // if file analyze him
    if (fs::is_regular_file(input_path)) {
        std::cout << "[info] Checking file: " << input_path.string() << std::endl;
        if (input_path.extension() == ".cpp") {
            analyzeCPPFile(input_path.string());
        }
        else if (input_path.extension() == ".c") {
            analyzeCFile(input_path.string());
        }

    }
    // if folder analyze all .cpp files
    if (fs::is_directory(input_path)) {
    std::cout << "[info] Checking directory: " << input_path << std::endl;
    
    for (const auto& entry : fs::directory_iterator(input_path)) {
        if (entry.path().extension() == ".cpp" || entry.path().extension() == ".hpp") {
            std::cout << "File:" << entry.path().filename() << std::endl;
            analyzeCPPFile(entry.path().string()); 
        }
        else if (entry.path().extension() == ".c" || entry.path().extension() == ".h")
        {
            std::cout << "File:" << entry.path().filename() << std::endl;
            analyzeCFile(entry.path().string());
        }
    }
    
}

}