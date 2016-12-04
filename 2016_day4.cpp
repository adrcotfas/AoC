#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cctype>
#include <map>
#include <algorithm>
#include <iterator>

struct Adress {

    Adress(const std::string& fullName, const std::string& shortName, const std::string& number, const std::string& checksum)
        : mFullName(fullName)
        , mShortName(shortName)
        , mNumber(number)
        , mChecksum(checksum) {
    }

    std::string mFullName;
    std::string mShortName;
    std::string mNumber;
    std::string mChecksum;
};

// get the first 5 characters in alphabetical order according to frequency
std::string getShortName(const std::map<char, int>& name) {
    
    std::string output;
    std::vector<std::pair<char, int>> s{ name.begin(), name.end() };
    std::stable_sort(s.begin(), s.end(), [](auto p1, auto p2) {
        return p1.second > p2.second;
    });
    std::transform(s.begin(), s.begin() + 5, std::back_inserter(output), [](auto &p) {
        return p.first;
    });
    return output;
}

std::vector<Adress> extractAdresses (const std::string& path) {
    std::ifstream fileStream(path);
    std::stringstream stringStream;

    std::copy(std::istreambuf_iterator<char>(fileStream),
        std::istreambuf_iterator<char>(),
        std::ostreambuf_iterator<char>(stringStream));

    std::string currentLine;
    std::vector<Adress> adresses;

    while (std::getline(stringStream, currentLine, '\n')) {
        
        std::map<char, int> shortNameData;
        std::string fullName;
        std::string number;
        std::string checksum;
        bool appendChecksum = false;

        for (char& c : currentLine) {
            if (c == '[') {
                appendChecksum = true;
            }
            else if (appendChecksum && c != ']') {
                checksum += c;
            }
            else if (std::isalpha(c)) {
                fullName += c;
                ++shortNameData[c];
            }
            else if (std::isdigit(c)) {
                number += c;
            }
        }
        adresses.push_back(Adress(fullName, getShortName(shortNameData), number, checksum));
    }
    return adresses;
}

bool isValidAdress(const Adress& adress) {
    bool isValid = false;
    if (adress.mChecksum == adress.mShortName) {
        isValid = true;
    }
    return isValid;
}

std::string findNorthPoleSector(std::vector<Adress> adresses) {
    std::string sector;
    for (auto& adress : adresses) {
        for (char& c : adress.mFullName) {
            c = ((c - 'a' + std::stoi(adress.mNumber)) % 26) + 'a';
        }
        if (adress.mFullName.find("north") != std::string::npos) {
            sector = adress.mNumber;
            break;
        }
    }
    return sector;
}

int main() {
    std::vector<Adress> adresses = extractAdresses("d:/input.txt");
    int result = 0;
    for (const auto& adress : adresses) {
        if (isValidAdress(adress)) {
            result += std::stoi(adress.mNumber);
        }
    }
    std::string northPoleSector = findNorthPoleSector(adresses);
    return 0;
}