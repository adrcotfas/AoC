#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <iostream>
#include <iterator>


struct Triangle {
    Triangle(std::string a, std::string b, std::string c)
        : mA(std::stoi(a))
        , mB(std::stoi(b))
        , mC(std::stoi(c)) {
    }
    int mA;
    int mB;
    int mC;
};

bool isTriangle(const Triangle& triangle) {
    return (triangle.mA + triangle.mB > triangle.mC) &&
           (triangle.mA + triangle.mC > triangle.mB) &&
           (triangle.mB + triangle.mC > triangle.mA);
}

std::vector<std::string> extractTrianglesByRow(const std::string& filePath) {
    std::ifstream fileStream(filePath);
    std::stringstream stringStream;

    std::copy(std::istreambuf_iterator<char>(fileStream),
        std::istreambuf_iterator<char>(),
        std::ostreambuf_iterator<char>(stringStream));

    std::string currentTriangle;
    std::vector<std::string> triangles;

    while (std::getline(stringStream, currentTriangle, '\n')) {
        triangles.push_back(currentTriangle);
    }

    return triangles;
}

std::vector<Triangle> extractTrianglesByColumn(const std::string& filePath) {
    std::ifstream fileStream(filePath);
    std::stringstream stringStream;

    std::copy(std::istreambuf_iterator<char>(fileStream),
        std::istreambuf_iterator<char>(),
        std::ostreambuf_iterator<char>(stringStream));

    std::vector<Triangle> output;
    std::string currentTriangle;
    std::string a[3];
    std::string b[3];
    std::string c[3];

    int index = 0;
    while (std::getline(stringStream, currentTriangle, '\n')) {
        std::stringstream(currentTriangle) >> a[index] >> b[index] >> c[index];
        ++index;
        if (index == 3) {
            output.push_back(Triangle(a[0], a[1], a[2]));
            output.push_back(Triangle(b[0], b[1], b[2]));
            output.push_back(Triangle(c[0], c[1], c[2]));
            index = 0;
        }
    }
    return output;
}

std::vector<Triangle> convertToTriangles(const std::vector<std::string>& triangles) {
    std::vector<Triangle> output;
    output.reserve(triangles.size());

    for (auto triangle : triangles) {
        
        std::istringstream iss(triangle);
        std::vector<std::string> result {
            std::istream_iterator<std::string>(iss),{} };
        output.push_back(Triangle(*result.begin(), *(result.begin() + 1), *(result.begin() + 2)));
    }
    return output;
}

int main() {
    const std::vector<std::string> stringCandidates = extractTrianglesByRow("c:/input.txt");
    const std::vector<Triangle> rowCandidates = convertToTriangles(stringCandidates);
    int nOfTriangles = 0;
    for (auto candidate : rowCandidates) {
        if (isTriangle(candidate)) {
            ++nOfTriangles;
        }
    }
    const std::vector<Triangle> columnCandidates = extractTrianglesByColumn("c:/input.txt");
    int nOfTrianglesP2 = 0;
    for (auto candidate : columnCandidates) {
        if (isTriangle(candidate)) {
            ++nOfTrianglesP2;
        }
    }

    return 0;
}