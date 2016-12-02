#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <iostream>

std::vector<std::string> extractInput(const std::string& filePath) {
    std::ifstream fileStream(filePath);
    std::stringstream stringStream;

    std::copy(std::istreambuf_iterator<char>(fileStream),
              std::istreambuf_iterator<char>(),
              std::ostreambuf_iterator<char>(stringStream));

    std::string currentLine;
    std::vector<std::string> instructions;

    while (std::getline(stringStream, currentLine, '\n')) {
        instructions.push_back(currentLine);
    }

    return instructions;
}

const int buttons[3][3] = { {1,2,3}
                           ,{4,5,6}
                           ,{7,8,9} };

int main() {
    std::vector<std::string> instructions = extractInput("c:/input.txt");
    int currentX = 1;
    int currentY = 1;

    std::vector<int> password;
    for (auto& instruction : instructions) {
        for (auto& character : instruction) {
            switch (character){
            case 'U':
                if (currentY > 0) {
                    --currentY;
                }
                break;
            case 'L':
                if (currentX > 0) {
                    --currentX;
                }
                break;
            case 'D':
                if (currentY < 2) {
                    ++currentY;
                }
                break;
            case 'R':
                if (currentX < 2) {
                    ++currentX;
                }
                break;
            }
        }
        password.push_back(buttons[currentX][currentY]);
    }
    return 0;
}