/*
 * FilmValidator.cpp
 *
 *  Created on: Mar 27, 2016
 *      Author: marius
 */
#include "FilmValidator.h"

void FilmValidator::validateTitle(const std::string& title) const {
	if (title == "" || title.length() > 20) {
		throw ValidatorException("Error : invalid title!");
	}
}

void FilmValidator::validateGen(const std::string& gen) const {
	if (gen == "" || gen.length() > 15) {
		throw ValidatorException("Error : invalid genre!");
	}
}

void FilmValidator::validateReleaseYear(const int releaseYear) const {
	if (releaseYear < 1800 || releaseYear > 2016) {
		throw ValidatorException("Error : invalid release year!");
	}
}

void FilmValidator::validateMainActor(const std::string& mainActor) const {
	if (mainActor == "" || mainActor.length() > 30) {
		throw ValidatorException(
			"Error : the name of the main actor is invalid!");
	}
}

void FilmValidator::validateFilm(const std::string& title, const std::string& gen, const int releaseYear, const std::string& mainActor) const {
	std::string errors{ "" };
	try {
		validateTitle(title);
	}
	catch (ValidatorException& ve) {
		errors += ve.getMsg() + "\n";
	}
	try {
		validateGen(gen);
	}
	catch (ValidatorException& ve) {
		errors += ve.getMsg() + "\n";
	}
	try {
		validateReleaseYear(releaseYear);
	}
	catch (ValidatorException& ve) {
		errors += ve.getMsg() + "\n";
	}
	try {
		validateMainActor(mainActor);
	}
	catch (ValidatorException& ve) {
		errors += ve.getMsg() + "\n";
	}
	if (errors.length() != 0) {
		throw ValidatorException(errors);
	}

}

