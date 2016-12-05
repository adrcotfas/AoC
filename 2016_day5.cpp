#include "md5.h" // http://www.zedwood.com/article/cpp-md5-function
#include <string>
#include <limits>

int main() {
	std::string password;
	for (long i = 0; i < std::numeric_limits<long>::max(); ++i) {		
		std::string text = "cxdnnyjw" + std::to_string(i);
		std::string digest = md5(text);		
		if (std::string{ digest.begin(), digest.begin() + 5 } == "00000") {
			password += digest.at(5);
		}
		if (password.size() == 8) {
			break;
		}
	}

	std::string secondPassword = "--------";
	int count = 0;
	for (long i = 0; i < std::numeric_limits<long>::max(); ++i) {
		std::string text = "cxdnnyjw" + std::to_string(i);
		std::string digest = md5(text);
		if (std::string{ digest.begin(), digest.begin() + 5 } == "00000") {
			int digit = digest.at(5) - '0';
			if (digit > 7) {
				continue;
			}
			else if (secondPassword[digit] == '-') {
					secondPassword[digit] = digest.at(6);
					++count;
			}
		}
		if (count == 8) {
			break;
		}
	}

	return 0;
}