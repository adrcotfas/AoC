#include <string>
#include <fstream>

std::string readInput(std::string filePath) {
    std::ifstream t(filePath);
    std::string str((std::istreambuf_iterator<char>(t)),
        std::istreambuf_iterator<char>());
    return str;
}

std::pair<int,int> calculateFloor(const std::string& input, char first, char second) {

    int result = 0;
    int reachedBasementAtPosition = -1;
    bool basementFound = false;
    for (std::string::const_iterator it = input.begin(); it != input.end(); ++it) {
        if (*it == first) {
            ++result;
        }
        else if (*it == second) {
            --result;
        }
        if (!basementFound && result < 0) {
            reachedBasementAtPosition = it - input.begin(); // +1
            basementFound = true;
        }
    }
    return std::pair<int,int>(result, reachedBasementAtPosition);
}

int main() {
    std::string input = readInput("c:/input.txt");
    std::pair<int,int> result  = calculateFloor(input, '(', ')');

    return 0;
}