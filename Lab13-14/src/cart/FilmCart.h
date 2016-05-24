#pragma once
#ifndef CART_FILM_CART_H_
#define CART_FILM_CART_H

#include "../domain/Film.h"
#include "../repository/repository.h"
#include "../observer/observer.h"
#include <vector>
#include <fstream>

//Extinde observable, astfel cei interesati se notifica in caz ca s-a schimbat ceva la Cos

class FilmCart: public Observable{
protected:
	std::vector<Film> __movies;
	const Repository& __repo;

	bool __isInRepo(const Film& film) const;
	bool __isInCart(const Film& film) const;
public:
	FilmCart(const Repository& repo) : __repo{ repo } {};
	void add(const Film& film);
	void del(const std::string& title);
	void fillRandom(const int howMany);

	void clear() {
		this->__movies.clear();
		this->notify();
	}

	std::vector<Film> getAll() const;
	virtual void writeToFile(const std::string& fileName) = 0;
};

class FilmCartCsv : public FilmCart {
public:
	FilmCartCsv(const Repository& repo) : FilmCart::FilmCart(repo) {
	}
	void writeToFile(const std::string& fileName) override {
		const std::vector<Film>& all = getAll();
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
};

class FilmCartHtml : public FilmCart {
public:
	FilmCartHtml(const Repository& repo) : FilmCart::FilmCart(repo) {}
	void writeToFile(const std::string& fileName) override {
		std::string filePath = "Files//exported//" + fileName;
		const std::vector<Film>& all = this->getAll();
		std::ofstream out(filePath, std::ios::trunc);
		if (!out.is_open()) {
			throw FilmException("Could not open file: " + filePath);
		}
		out << "<html><body>" << std::endl;
		out << "<table border=\"1\" style=\"width:100 % \">" << std::endl;
		for (const Film& film : all) {
			out << "<tr>" << std::endl;
			out << "<td>" << film.getTitle() << "</td>" << std::endl;
			out << "<td>" << film.getGen() << "</td>" << std::endl;
			out << "<td>" << film.getReleaseYear() << "</td>" << std::endl;
			out << "<td>" << film.getMainActor() << "</td>" << std::endl;
			out << "</tr>" << std::endl;
		}
		out << "</table>" << std::endl;
		out << "</body></html>" << std::endl;
		out.close();
	}
};
#endif // !CART_FILM_CART_H_