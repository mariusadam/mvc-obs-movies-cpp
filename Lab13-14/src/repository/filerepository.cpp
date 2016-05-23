#include "FileRepository.h"
#include <fstream>
#include <sstream>

void FileRepository::__saveToFile() {
	std::string fileName = this->__fileName;
	std::vector<Film>all = this->getAll();
	std::ofstream out(fileName, std::ios::trunc);
	if (out.is_open() == false) {
		throw FilmException("Could not open file: " + fileName);
	}
	for (const Film& film : all) {
		out << film.getTitle() << "," <<
			film.getGen() << "," <<
			film.getReleaseYear() << "," <<
			film.getMainActor() << std::endl;
	}
	out.close();
}

std::vector<std::string> split(const std::string& str, char delimiter) {
	std::vector<std::string> rez;
	std::stringstream ss(str);
	std::string token;
	while (std::getline(ss, token, delimiter)) {
		rez.push_back(token);
	}
	return rez;
}

std::vector<Film> FileRepository::__loadFromFile() {
	std::vector<Film> result;
	std::ifstream out(__fileName);
	if (out.is_open() == false) {
		throw RepositoryException("Could not open file: " + __fileName);
	}
	std::string line;
	std::vector<std::string> attrs;
	while (std::getline(out, line)) {
		attrs = split(line, ',');
		result.push_back(Film{ attrs[0], attrs[1], std::stoi(attrs[2]), attrs[3] });
	}
	return result;
}