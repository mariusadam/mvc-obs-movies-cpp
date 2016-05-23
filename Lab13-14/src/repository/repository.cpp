/*
 * repository.cpp
 *
 *  Created on: Mar 28, 2016
 *      Author: marius
 */

#include "repository.h"
#include <algorithm>
#include <qdebug.h>

void Repository::add(const Film& film) {
	if (std::find(__items.begin(), __items.end(), film) == __items.end()) {
		__items.push_back(film);
		return;
	}
	throw RepositoryException("Error in repository: film already added!");
}

void Repository::del(const Film& film) {
	auto filmIt = std::find(__items.begin(), __items.end(), film);
	if (filmIt == __items.end()) {
		//qDebug() << film.getTitle().c_str() << film.getGen().c_str() << film.getReleaseYear() << film.getMainActor().c_str() << "'\n";
		throw RepositoryException("Error in repository: trying to delete unexistent film!");
	}
	__items.erase(filmIt);
}

void Repository::update(const Film& newFilm) {
	auto oldFilmIterPoz = std::find_if(__items.begin(), __items.end(), [&](const Film& film) {return film.getTitle() == newFilm.getTitle(); });
	if (oldFilmIterPoz == __items.end()) {
		//qDebug() << newFilm.getTitle().c_str() << newFilm.getGen().c_str() << newFilm.getReleaseYear() << newFilm.getMainActor().c_str() << "'\n";
		throw RepositoryException(
			"Error in repository: trying to update unexistent film!");
	}
	auto offset{ std::distance(__items.begin(), oldFilmIterPoz) };
	int index = (int)offset;
	__items[index] = newFilm;
}

std::vector<Film> Repository::getBetween(int beginOffset, int howMany) const {
	howMany = howMany == -1 ? this->__items.size() : howMany;
	std::vector<Film> result;
	for (int i = beginOffset; i < this->__items.size() && howMany > 0; i++, howMany--) {
		result.push_back(this->__items[i]);
	}
	return result;
}