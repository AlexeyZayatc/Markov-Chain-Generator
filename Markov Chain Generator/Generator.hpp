#pragma once
#include <map>
#include <string>
#include <vector>
#include <random>
#include <numeric>

class Generator
{
public:
	Generator(const std::vector<std::string>& wrds);
	std::string generate(const size_t& len, const std::string& delim = " ");

private:
	class Container {
	public:
		Container() {}
		std::string getWord(const size_t& n) const noexcept {

			size_t cnt = 0;
			for (const auto& [word, count] : probability) {
				cnt += count;
				if (cnt >= n)
					return word;

			}
			return "";
		}
		size_t getMax() const noexcept {
			size_t ret = 0;
			for (const auto& [word, count] : probability)
				ret += count;
			return ret;
		}
		void add(const std::string& str) noexcept
		{
			if (probability.count(str) == 0)
				probability[str] = 0;
			probability[str]++;
		}

	private:
		std::map<std::string,size_t> probability;
	};
	
	std::map <std::string, Container> words;

	std::random_device rd;
	std::mt19937 gen;

};

