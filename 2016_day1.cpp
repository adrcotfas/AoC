#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <streambuf>
#include <string>
#include <utility>
#include <vector>

typedef std::pair<int, int> Point;
typedef std::pair<char, int> PathSegment;

enum Orientation {
    NORTH,
    EAST,
    SOUTH,
    WEST
};

std::string getPathAsString(std::string filePath) {
    std::ifstream t(filePath);
    std::string str((std::istreambuf_iterator<char>(t)),
        std::istreambuf_iterator<char>());
    return str;
}

std::vector<std::string> splitPathToSegments(const std::string& path) {
    std::stringstream pathStream(path);
    std::string segment;
    std::vector<std::string> output;
    while (std::getline(pathStream, segment, ',')) {
        if (segment != std::string(" ")) {
            output.push_back(segment);
        }
    }
    return output;
}

std::vector<PathSegment> convertStringSegmentsToPathSegments(const std::vector<std::string>& segments) {
    std::vector<PathSegment> output;
    output.reserve(segments.size());

    for (auto i : segments) {
        char direction = *i.begin();
        int steps = std::stoi(i.substr(1, i.size()));
        output.push_back(PathSegment(direction, steps));
    }
    return output;
}

int calculateDistance(Point a, Point b) {
    return std::abs(b.first - a.first) + std::abs(b.second - a.second);
}

Point findFirstDuplicate(std::vector<Point> points) {
    std::set<Point> sett;
    for (std::vector<Point>::iterator i = points.begin(); i != points.end(); ++i) {
        if (sett.find(*i) != sett.end()) {
            return *i;
        }
        else {
            sett.insert(*i);
        }
    }
}

std::vector<Point> travelPath(const Point& startPoint, const Orientation direction, const std::vector<PathSegment>& path) {
    std::vector<Point> visitedPositions;
    Point currentPosition = startPoint;
    Orientation currentDirection = direction;

    for (const auto& i : path) {
        switch (currentDirection) {
        case NORTH:
            if (i.first == 'L') {
                for (int idx = 1; idx <= i.second; ++idx) {
                    currentPosition.first -= 1;
                    visitedPositions.push_back(currentPosition);
                }
                currentDirection = WEST;
            }
            else if (i.first == 'R') {
                for (int idx = 1; idx <= i.second; ++idx) {
                    currentPosition.first += 1;
                    visitedPositions.push_back(currentPosition);
                }
                currentDirection = EAST;
            }
            break;
        case EAST:
            if (i.first == 'L') {
                for (int idx = 1; idx <= i.second; ++idx) {
                    currentPosition.second += 1;
                    visitedPositions.push_back(currentPosition);
                }
                currentDirection = NORTH;
            }
            else if (i.first == 'R') {
                for (int idx = 1; idx <= i.second; ++idx) {
                    currentPosition.second -= 1;
                    visitedPositions.push_back(currentPosition);
                }
                currentDirection = SOUTH;
            }
            break;
        case SOUTH:
            if (i.first == 'L') {
                for (int idx = 1; idx <= i.second; ++idx) {
                    currentPosition.first += 1;
                    visitedPositions.push_back(currentPosition);
                }
                currentDirection = EAST;
            }
            else if (i.first == 'R') {
                for (int idx = 1; idx <= i.second; ++idx) {
                    currentPosition.first -= 1;
                    visitedPositions.push_back(currentPosition);
                }
                currentDirection = WEST;
            }
            break;
        case WEST:
            if (i.first == 'L') {
                for (int idx = 1; idx <= i.second; ++idx) {
                    currentPosition.second -= 1;
                    visitedPositions.push_back(currentPosition);
                }
                currentDirection = SOUTH;
            }
            else if (i.first == 'R') {
                for (int idx = 1; idx <= i.second; ++idx) {
                    currentPosition.second += 1;
                    visitedPositions.push_back(currentPosition);
                }
                currentDirection = NORTH;
            }
            break;
        }
    }
    return visitedPositions;
}

int main() {
    std::string pathString = getPathAsString("C:/input.txt");
    pathString.erase(remove_if(pathString.begin(), pathString.end(), isspace), pathString.end());

    std::vector<std::string> segmentsString = splitPathToSegments(pathString);
    std::vector<PathSegment> segments = convertStringSegmentsToPathSegments(segmentsString);
    std::vector<Point> visitedDestinations = travelPath(Point(0, 0), NORTH, segments);
    Point destination = visitedDestinations.back();
    int length = calculateDistance(Point(0, 0), destination);

    Point realDestination = findFirstDuplicate(visitedDestinations);
    int realLength = calculateDistance(Point(0, 0), realDestination);
    return 0;
}