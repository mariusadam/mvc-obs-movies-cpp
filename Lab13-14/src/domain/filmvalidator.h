/*
 * FilmValidator.h
 *
 *  Created on: Mar 27, 2016
 *      Author: marius
 */

#ifndef DOMAIN_FILMVALIDATOR_H_
#define DOMAIN_FILMVALIDATOR_H_
#include <string>
#include "Film.h"

class FilmValidator {
public:
	void validateTitle(const std::string& title) const;
	void validateGen(const std::string& gen)const;
	void validateReleaseYear(const int releaseYear)const;
	void validateMainActor(const std::string& mainActor)const;
	void validateFilm(const std::string& title, const std::string& gen, const int releaseYear, const std::string& mainActor) const;

};

class ValidatorException: public FilmException {

public:
	ValidatorException() :
			FilmException() {
	}

	ValidatorException(const std::string& msg) :
			FilmException { msg } {
	}

	~ValidatorException() {
	}
};

#endif /* DOMAIN_FILMVALIDATOR_H_ */
