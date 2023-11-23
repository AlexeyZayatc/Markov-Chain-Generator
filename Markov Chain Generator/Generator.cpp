#include "Generator.hpp"

Generator::Generator(const std::vector<std::string>& wrds) {
		for (size_t i = 0; i < wrds.size() - 1; i++) {
			if (words.count(wrds[i]) == 0)
				words[wrds[i]] = Container();
			words[wrds[i]].add(wrds[i + 1]);
		}
}

std::string Generator::generate(const size_t& len, const std::string& delim)
{
	if (len == 0) return "";
	std::vector<std::string> result(len);
	std::uniform_int_distribution<size_t> distrib(0, words.size());
	size_t firstWordIndex = distrib(gen);
	for (const auto& [word, cont] : words) {
		if (firstWordIndex-- == 0)
		{
			result[0] = word;
			break;
		}
	}
	for (size_t j = 1; j < len; j++) {
		std::uniform_int_distribution<size_t> distrib(0, words[result[j - 1]].getMax() - 1);
		result[j] = words[result[j - 1]].getWord(distrib(gen));
	}
	return std::accumulate(std::next(result.begin()), result.end(), result[0], [&delim](const std::string& first, const std::string& second) {
		return first + delim + second;
		});
}
