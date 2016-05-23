/*
 * controller.cpp
 *
 *  Created on: Mar 28, 2016
 *      Author: marius
 */

#include "controller.h"
#include <algorithm>
#include <iterator>
#include <ctype.h>
#include <sstream>
#include <algorithm>
#include <stdlib.h>
#include <time.h>


void Controller::add(std::string title, std::string gen, int releaseYear, std::string mainActor) {
	Film film{ createFilm(title, gen, releaseYear, mainActor) };
	__undoActions.push_back(std::make_unique<UndoAdd>(__repo, film));
	__repo.add(film);
}

void Controller::undo() {
	if (__undoActions.empty()) {
		throw FilmException{ "Nu se mai poate face undo!" };
	}
	__undoActions.back()->doUndo();
	__undoActions.pop_back();
}

void Controller::del(const std::string& title) {
	Film film{ find(title) };
	__undoActions.push_back(std::make_unique<UndoDel>(__repo, film));
	__repo.del(film);
}

void Controller::update(const Film& newFilm) {
	Film oldFilm = find(newFilm.getTitle());
	__undoActions.push_back(std::make_unique<UndoUpdate>(__repo, oldFilm));
	__repo.update(newFilm);
}

Film Controller::find(const std::string& title) const {
	std::vector<Film>& alls = getAll();
	auto filmIt = std::find_if(alls.begin(), alls.end(), [&](const Film& film) {return film.getTitle() == title; });
	if (filmIt == alls.end()) {
		throw RepositoryException("Error: movie not in the repository");
	}
	return *filmIt;
}

Film Controller::createFilm(const std::string& title, const std::string& gen, const int& releaseYear, const std::string& mainActor) const {
	__validator.validateFilm(title, gen, releaseYear, mainActor);
	return Film{ title, gen, releaseYear, mainActor };
}

const std::vector<Film> Controller::search(const std::string& title) const {
	std::vector<Film>& alls = getAll();
	std::vector<Film> result;
	std::copy_if(alls.begin(), alls.end(), std::back_inserter(result),
		[&](const Film& film) {return film.getTitle().find(title) != std::string::npos; });
	if (result.size() == 0) {
		throw RepositoryException("No match was found for " + title + "!");
	}
	return result;
}

const std::vector<Film> Controller::filterByTitle(const std::string& title) const {
	std::vector<Film>& alls = getAll();
	std::vector<Film> result;
	std::copy_if(alls.begin(), alls.end(), std::back_inserter(result),
		[&](const Film& film) {return film.getTitle() == title; });
	if (result.size() == 0) {
		throw RepositoryException("No match was found for " + title + "!");
	}
	return result;
}

const std::vector<Film> Controller::filterByReleaseYear(const int& releaseYear) const {
	std::vector<Film>& alls = getAll();
	std::vector<Film> result;
	std::copy_if(alls.begin(), alls.end(), std::back_inserter(result),
		[&](const Film& film) {return film.getReleaseYear() == releaseYear; });
	if (result.size() == 0) {
		throw RepositoryException("No movies were released in " + std::to_string(releaseYear) + "!");
	}
	return result;
}

std::string toUpper(std::string s) {
	for (int i = 0; i < (int)s.length(); i++) { s[i] = toupper(s[i]); }
	return s;
}

bool compareNat(const std::string& a, const std::string& b) {
	if (a.empty())
		return true;
	if (b.empty())
		return false;
	if (isdigit(a[0]) && !isdigit(b[0]))
		return true;
	if (!isdigit(a[0]) && isdigit(b[0]))
		return false;
	if (!isdigit(a[0]) && !isdigit(b[0]))
	{
		if (a[0] == b[0])
			return compareNat(a.substr(1), b.substr(1));
		return (toUpper(a) < toUpper(b));
		//toUpper() is a function to convert a std::string to uppercase.
	}

	// Both strings begin with digit --> parse both numbers
	std::istringstream issa(a);
	std::istringstream issb(b);
	int ia, ib;
	issa >> ia;
	issb >> ib;
	if (ia != ib)
		return ia < ib;

	// Numbers are the same --> remove numbers and recurse
	std::string anew, bnew;
	std::getline(issa, anew);
	std::getline(issb, bnew);
	return (compareNat(anew, bnew));
}

const std::vector<Film> Controller::getSortedByTitleAsc() const {
	std::vector<Film> result{ getAll() };
	std::sort(result.begin(), result.end(), [](const Film& f1, const Film& f2) {return f1.getTitle() < f2.getTitle(); });
	return result;
}

const std::vector<Film> Controller::getSortedByTitleDesc() const {
	std::vector<Film> result{ getAll() };
	std::sort(result.begin(), result.end(), [](const Film& f1, const Film& f2) {return f1.getTitle() > f2.getTitle(); });
	return result;
}

const std::vector<Film> Controller::getSortedByMainActorAsc() const {
	std::vector<Film> result{ getAll() };
	sort(result.begin(), result.end(), [](const Film& f1, const Film& f2) {return f1.getMainActor() < f2.getMainActor(); });
	return result;
}

const std::vector<Film> Controller::getSortedByMainActorDesc() const {
	std::vector<Film> result{ getAll() };
	sort(result.begin(), result.end(), [](const Film& f1, const Film& f2) {return f1.getMainActor() > f2.getMainActor(); });
	return result;
}

const std::vector<Film> Controller::getSortedByYearGenreAsc() const {
	std::vector<Film> result{ getAll() };
	sort(result.begin(), result.end(), [](const Film& f1, const Film& f2) {return ((f1.getReleaseYear() == f2.getReleaseYear()) ? (f1.getGen() < f2.getGen()) : (f1.getReleaseYear() < f2.getReleaseYear())); });
	return result;
}

const std::vector<Film> Controller::getSortedByYearGenreDesc() const {
	std::vector<Film> result{ getAll() };
	sort(result.begin(), result.end(), [](const Film& f1, const Film& f2) {return ((f1.getReleaseYear() == f2.getReleaseYear()) ? (f1.getGen() > f2.getGen()) : (f1.getReleaseYear() > f2.getReleaseYear())); });
	return result;
}

void Controller::fillRepoRandom(int howMany) {
	srand(time(NULL));
	std::string possible_chars{ "abcdefghijklmnoprstuvxyzQWERTYUIOPASDFGHJKLZXCVBNM" };
	for (int i = 0; i < howMany; i++) {
		int lgTitle = rand() % 10 + 2;
		int lgGen = rand() % 10 + 2;
		int lgMainActor = rand() % 10 + 2;
		std::string title(lgTitle, ' ');
		std::string gen(lgGen, ' ');
		std::string mainActor(lgMainActor, ' ');
		for (int j = 0; j < lgTitle; j++) {
			int randomCharPoz = rand() % possible_chars.size();
			title[j] = possible_chars[randomCharPoz];
		}
		for (int j = 0; j < lgGen; j++) {
			int randomCharPoz = rand() % possible_chars.size();
			gen[j] = possible_chars[randomCharPoz];
		}
		for (int j = 0; j < lgMainActor; j++) {
			int randomCharPoz = rand() % possible_chars.size();
			mainActor[j] = possible_chars[randomCharPoz];
		}
		try {
			this->add(title, gen, 1980 + rand() % 40, mainActor);
		}
		catch (FilmException& ex) {

		}
	}
}