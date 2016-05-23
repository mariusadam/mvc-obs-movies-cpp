/*
 * repository.h
 *
 *  Created on: Mar 27, 2016
 *      Author: marius
 */

#ifndef REPOSITORY_REPOSITORY_H_
#define REPOSITORY_REPOSITORY_H_
#include "../domain/Film.h"
#include "../domain/FilmValidator.h"
#include <vector>

class Repository {
protected:
	std::vector<Film> __items;

public:
	Repository() {

	}
	virtual ~Repository() {}
	Repository(const Repository& other) = delete;

	std::vector<Film> getAll() const {
		return __items;
	}

	virtual void setAll(const std::vector<Film>& newMovies) {
		__items = newMovies;
	}

	virtual void add(const Film& film);

	virtual void del(const Film& film);

	virtual void update(const Film& newFilm);

	std::vector<Film> getBetween(int beginOffset = 0, int howMany = -1) const;
};

class RepositoryException : public FilmException {

public:
	RepositoryException() :
		FilmException() {
	}

	RepositoryException(const std::string msg) :
		FilmException{ msg } {
	}

	~RepositoryException() {
	}
};

#endif /* REPOSITORY_REPOSITORY_H_ */
