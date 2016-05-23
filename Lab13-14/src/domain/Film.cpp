/*
 * Film.cpp
 *
 *  Created on: Mar 26, 2016
 *      Author: marius
 */
#include "Film.h"

Film::Film() {
	__title = "";
	__gen = "";
	__releaseYear = 0;
	__mainActor = "";
}

Film::Film(const std::string& title, const std::string& gen, const int releaseYear, const std::string& mainActor) {
	__title = title;
	__gen = gen;
	__releaseYear = releaseYear;
	__mainActor = mainActor;
}

Film::Film(const Film& other) {
	__title = other.__title;
	__gen = other.__gen;
	__releaseYear = other.__releaseYear;
	__mainActor = other.__mainActor;
}

Film& Film::operator=(const Film& other) {
	if (this == &other){
			return *this;
		}
	__title = other.__title;
	__gen = other.__gen;
	__releaseYear = other.__releaseYear;
	__mainActor = other.__mainActor;
	return *this;
}

std::ostream& operator<<(std::ostream& out, const Film& film) {
	std::string sep = ", ";
	out << film.__title << sep << film.__gen << sep << film.__releaseYear << sep
			<< film.__mainActor;
	return out;
}

std::ostream& operator<<(std::ostream& out, const FilmException& except){
	out << except.getMsg();
	return out;
}
