#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <algorithm>
#include <iterator>
#include <iostream>

std::vector<std::string> splitToColumns(std::stringstream& stringStream) {

	std::vector<std::string> columns;
	columns.resize(8);

	unsigned int idx = 0;
	std::string currentLine;
	while (std::getline(stringStream, currentLine, '\n')) {
		for (auto& c : currentLine) {
			columns[idx] += c;
			++idx;
		}
		idx = 0;
	}
	return columns;
}

const char getMostFrequentChar(const std::string& column) {

	std::map<char, int> table;
	for (const char& c : column) {
		++table[c];
	}

	std::vector<std::pair<char, int>> s{ table.begin(), table.end() };
	std::stable_sort(s.begin(), s.end(), [](auto p1, auto p2) {
		return p1.second < p2.second;
	});

	return s.back().first;
}

const char getLessFrequentChar(const std::string& column) {

	std::map<char, int> table;
	for (const char& c : column) {
		++table[c];
	}

	std::vector<std::pair<char, int>> s{ table.begin(), table.end() };
	std::stable_sort(s.begin(), s.end(), [](auto p1, auto p2) {
		return p1.second > p2.second;
	});

	return s.back().first;
}

std::pair<std::string, std::string> decode(const std::string& path) {
	std::ifstream fileStream(path);
	std::stringstream stringStream;

	std::copy(std::istreambuf_iterator<char>(fileStream),
		std::istreambuf_iterator<char>(),
		std::ostreambuf_iterator<char>(stringStream));

	const std::vector<std::string> columns = splitToColumns(stringStream);

	std::string firstPartCode;
	for (auto& column : columns) {
		firstPartCode += getMostFrequentChar(column);
	}

	std::string secondPartCode;
	for (auto& column : columns) {
		secondPartCode += getLessFrequentChar(column);
	}

	return std::pair<std::string, std::string>(firstPartCode, secondPartCode);
}

int main() {
	std::pair<std::string, std::string> codes = decode("d:/input.txt");
	std::cout << "First code: " << codes.first << std::endl
		<< "Second Code: " << codes.second << std::endl;

	return 0;
}