#include "FilmCart.h"
#include <chrono>
#include <random>
#include <algorithm>

void FilmCart::add(const Film& film) {
	if (this->__isInRepo(film) == false) {
		throw FilmException("Error : cannot add to cart unexistent movie!");
	}
	if (this->__isInCart(film) == true) {
		throw FilmException("Error : movie already in the cart!");
	}
	this->__movies.push_back(film);
	this->notify();
}

bool FilmCart::__isInRepo(const Film& film) const {
	const std::vector<Film>& alls = this->__repo.getAll();
	auto filmIt = std::find(alls.begin(), alls.end(), film);
	return (filmIt == alls.end() ? false : true);
}

bool FilmCart::__isInCart(const Film& film) const {
	auto filmIt =  std::find(__movies.begin(), __movies.end(), film);
	return (filmIt == __movies.end() ? false : true);
}

const std::vector<Film> FilmCart::getAll() const {
	return __movies;
}

void FilmCart::fillRandom(const int howMany) {
	this->clear();
	int seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::vector<Film>& all = this->__repo.getAll();
	std::shuffle(all.begin(), all.end(), std::default_random_engine(seed));
	while (this->__movies.size() < howMany && all.size() > 0) {
		this->__movies.push_back(all.back());
		all.pop_back();
	}
	this->notify();
}

void FilmCart::del(const std::string& title) {
	auto filmIt = std::find_if(this->__movies.begin(), this->__movies.end(), [&](const Film& film) {return film.getTitle() == title; });
	if (filmIt == this->__movies.end()) {
		//qDebug() << film.getTitle().c_str() << film.getGen().c_str() << film.getReleaseYear() << film.getMainActor().c_str() << "'\n";
		throw RepositoryException("Error in cart: trying to delete unexistent film!");
	}
	this->__movies.erase(filmIt);
	this->notify();
}