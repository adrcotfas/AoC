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

std::vector<int> getPassword(const std::vector<std::string>& instructions,
                             const int initialX,
                             const int initialY) {

    std::vector<int> password;
    int currentX = initialX;
    int currentY = initialY;

    for (auto& instruction : instructions) {
        for (auto& character : instruction) {
            switch (character) {
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
        password.push_back(buttons[currentY][currentX]);
    }
    return password;
}

const char fancyButtons[5][5] = { { ' ',' ','1',' ',' ' },
                                  { ' ','2','3','4',' ' },
                                  { '5','6','7','8','9' },
                                  { ' ','A','B','C',' ' },
                                  { ' ',' ','D',' ',' ' } };

std::vector<char> getFancyPassword(const std::vector<std::string>& instructions,
    const int initialX,
    const int initialY) {

    std::vector<char> password;
    int currentX = initialX;
    int currentY = initialY;

    for (auto& instruction : instructions) {
        for (auto& character : instruction) {
            switch (character) {
            case 'U':
                if (fancyButtons[currentY - 1][currentX] != ' ' && currentY > 0) {
                    --currentY;
                }
                break;
            case 'L':
                if (fancyButtons[currentY][currentX - 1] != ' ' && currentX > 0) {
                    --currentX;
                }
                break;
            case 'D':
                if (fancyButtons[currentY + 1][currentX] != ' ' && currentY < 4) {
                    ++currentY;
                }
                break;
            case 'R':
                if (fancyButtons[currentY][currentX + 1] != ' ' && currentX < 4) {
                    ++currentX;
                }
                break;
            }
        }
        password.push_back(fancyButtons[currentY][currentX]);
    }
    return password;
}

int main() {
    std::vector<std::string> instructions = extractInput("c:/input.txt");
    std::vector<int> password = getPassword(instructions, 1, 1);
    std::vector<char> fancyPassword = getFancyPassword(instructions, 0, 2);
    
    return 0;
}