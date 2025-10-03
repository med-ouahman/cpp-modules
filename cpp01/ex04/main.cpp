#include "Replace.hpp"

static std::string changeLine(std::string line, std::string s1, std::string s2) {
    std::string res;
    size_t start = line.find(s1);
    size_t end;
    
    while (start != std::string::npos) {
        end = start + s1.length();
        res += line.substr(0, start) + s2;
        line = line.substr(end);
        start = line.find(s1);
    }
    res += line;
    return res;
}

int main(int argc, char **argv) {

    if (argc != 4) {
        std::cerr << "Usage: ./replace filename s1 s2" << std::endl;
        return 1;
    }

    std::string res = argv[1] + std::string(".replace");
    std::string s1 = argv[2], s2 = argv[3];
    std::ifstream inFile(argv[1]);
    std::ofstream outFile(res.c_str());

    if (!inFile || !outFile) {
        std::cerr << "Error opening file" << std::endl;
        if (inFile) {
            inFile.close();
        }
        if (outFile) {
            outFile.close();
        }
        return 1;
    }
    if (s1 == s2)
        return 0;
    std::stringstream buf;
    buf << inFile.rdbuf();
    outFile << changeLine(buf.str(), s1, s2);
    inFile.close();
    outFile.close();
    return 0;
}
