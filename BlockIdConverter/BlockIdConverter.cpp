// BlockIdConverter.cpp: Definiuje punkt wejścia dla aplikacji konsolowej.
//

#include "stdafx.h"

struct Entry {
	uint32_t id;
	std::string name;
	bool hasItem;
	std::string className;
};

struct Entries {
	class Tokenize {
		char sep = ',';
		size_t prev = 0;
		size_t pos = 0;
		size_t length = 0;
		const std::string& str;

	public:
		Tokenize(const std::string& str) : str(str) {}

		std::string getNextToken() {
			pos = str.find_first_of(sep, pos);
			length = pos - prev;
			auto temp = str.substr(prev, length);
			prev = ++pos;
			return std::move(temp);
		}
	};

	std::vector<Entry> list;

	Entries(const std::string& name) {
		std::fstream file(name);
		std::string line;

		std::getline(file, line);

		if (!file.is_open()) {
			std::cout << "Nie znaleziono pliku:" << name << std::endl;
			return;
		}

		while (!file.eof()) {
			std::getline(file, line);
			add(line);
		}

		std::cout << "Wczytano wpisow: " << list.size() << " z pliku: "<< name << std::endl;
	}

	bool add(const std::string& line) {
		Entry temp;
		Tokenize token(line);
		auto name = token.getNextToken();
		if (name.empty()) {
			return false;
		}
		temp.name = std::move(name);

		auto id = token.getNextToken();
		if (id.empty()) {
			return false;
		}
		temp.id = std::stoul(id);

		auto hasItem = token.getNextToken();
		if (hasItem.empty()) {
			return false;
		}
		temp.hasItem = hasItem == "TRUE";

		auto className = token.getNextToken();
		if (className.empty()) {
			return false;
		}
		temp.className = std::move(className);
		list.push_back(std::move(temp));
		return true;
	}
};

int main()
{
	Entries blockIdServer("C:\\Sources\\git\\BlockIdMapper\\BlockIdDumps\\block.Server.csv");
	Entries blockIdLocal("C:\\Sources\\git\\BlockIdMapper\\BlockIdDumps\\block.Local.csv");
	return 0;
}
