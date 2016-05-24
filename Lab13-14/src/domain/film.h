/*
 * Film.h
 *
 *  Created on: Mar 26, 2016
 *      Author: marius
 */

#ifndef DOMAIN_FILM_H_
#define DOMAIN_FILM_H_

#include <string>
#include <iostream>

class Film {
private:
	std::string __title;
	std::string __gen;
	int __releaseYear;
	std::string __mainActor;
public:

	/**
	 * Default constructor
	 */
	Film();

	/**
	 * Parametrized constructor
	 */
	Film(const std::string& title, const std::string& gen, const int releaseYear, const std::string& mainActor);

	/**
	 * Copy contructor
	 */
	Film(const Film& film);

	/**
	 * Destructor
	 */
	~Film() {
	}

	bool operator==(const Film& other) const {
		return __title == other.__title;
	}

	bool operator!=(const Film& other) const {
		return !(*this == other);
	}

	Film& operator=(const Film& other);

	const std::string& getGen() const {
		return __gen;
	}

	void setGen(const std::string& gen) {
		__gen = gen;
	}

	const std::string& getMainActor() const {
		return __mainActor;
	}

	void setMainActor(const std::string& mainActor) {
		__mainActor = mainActor;
	}

	int getReleaseYear() const {
		return __releaseYear;
	}

	void setReleaseYear(int releaseYear) {
		__releaseYear = releaseYear;
	}

	const std::string& getTitle() const {
		return __title;
	}

	void setTitle(const std::string& title) {
		__title = title;
	}

	friend std::ostream& operator<<(std::ostream& out, const Film& film);

};

class FilmException {
private:
	std::string __msg;
public:
	FilmException() {
		__msg = "An error occured in this application!";
	}

	FilmException(const std::string& msg) {
		__msg = msg;
	}

	~FilmException() {
	}

	const std::string getMsg() const {
		return __msg;
	}

	friend std::ostream& operator<<(std::ostream& out, const FilmException& except);
};

#endif /* DOMAIN_FILM_H_ */
