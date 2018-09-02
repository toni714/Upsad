#include "StringHelper.h"

std::vector<std::string> StringHelper::splitString(std::string input, const char * delimiter) {
	size_t position = input.find(delimiter);
	while (input.compare(0, strlen(delimiter), delimiter) == 0) {
		input = input.substr(strlen(delimiter));
		position = input.find(delimiter);
	}
	std::vector<std::string> result;
	while (position != std::string::npos) {
		result.push_back(input.substr(0, position));
		while (input.compare(position, strlen(delimiter), delimiter) == 0) {
			position += strlen(delimiter);
		}
		input = input.substr(position);
		position = input.find(delimiter);
	}

	if (input.compare("") != 0) {
		result.push_back(input);
	}
	return result;
}