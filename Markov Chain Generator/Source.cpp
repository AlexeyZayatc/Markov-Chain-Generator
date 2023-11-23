#include <iostream>
#include <fstream>
#include <vector>

#include "Generator.hpp"

// for string delimiter https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
std::vector<std::string> split(std::string s, std::string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
        token = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back(token);
    }

    res.push_back(s.substr(pos_start));
    return res;
}


int main() {
    setlocale(LC_ALL, "RUS");
	std::ifstream input("Anecdots.txt", std::ios_base::in);
	std::vector<std::string> allWords;
	while (!input.eof()) {
		std::string line;
		std::getline(input, line);
        if (line.empty()) continue;
        auto words = split(line, " ");
        allWords.insert(allWords.end(), words.begin(),words.end());
	}
	input.close();

    Generator myGen(allWords);

    std::ofstream output("GeneratedAnecdots.txt", std::ios_base::out);
    for (size_t i = 30; i <= 60; i += 10) {
        output << myGen.generate(i) << "\n\n\n";
    }
    output.close();


	return 0;
}
