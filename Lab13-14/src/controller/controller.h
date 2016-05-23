/*
 * controller.h
 *
 *  Created on: Mar 27, 2016
 *      Author: marius
 */

#ifndef CONTROLLER_CONTROLLER_H_
#define CONTROLLER_CONTROLLER_H_

#include "../repository/repository.h"
#include "../domain/FilmValidator.h"
#include "../cart/FilmCart.h"
#include <memory>
#include "Undo.h"

class Controller {
private:
	Repository& __repo;
	FilmValidator& __validator;
	std::vector<std::unique_ptr<UndoAction>> __undoActions;
	FilmCart& __cart;
public:
	Controller(Repository& repo, FilmValidator& valid, FilmCart& cart) :
		__repo{ repo }, __validator{ valid }, __cart{ cart } {
	}
	Controller(Controller& other) = delete;

	void undo();

	Film createFilm(const std::string& title, const std::string& gen, const int& releaseYear, const std::string& mainActor) const;

	void validateTitle(std::string title) const {
		__validator.validateTitle(title);
	}

	void validateReleaseYear(int releaseYear) const {
		__validator.validateReleaseYear(releaseYear);
	}

	void add(std::string title, std::string gen, int releaseYear, std::string mainActor);

	void del(const std::string& title);

	void delFromCart(const std::string& title) {
		this->__cart.del(title);
	}

	void update(const  Film& newFilm);

	const std::vector<Film> search(const std::string& title) const;

	const std::vector<Film> filterByTitle(const std::string& title) const;
	const std::vector<Film> filterByReleaseYear(const int& releaseYear) const;

	const std::vector<Film> getSortedByTitleAsc() const;
	const std::vector<Film> getSortedByTitleDesc() const;

	const std::vector<Film> getSortedByMainActorAsc() const;
	const std::vector<Film> getSortedByMainActorDesc() const;

	const std::vector<Film> getSortedByYearGenreAsc() const;
	const std::vector<Film> getSortedByYearGenreDesc() const;

	Film find(const std::string& title) const;

	std::vector<Film> getAll() const {
		return __repo.getAll();
	}

	std::vector<Film> getCartMovies() const {
		return __cart.getAll();
	}

	void fillCartRandom(const int howMany) {
		__cart.fillRandom(howMany);
	}

	void fillRepoRandom(int howMany);

	void clearCart() {
		__cart.clear();
	}

	void addToCart(const Film& film) {
		__cart.add(film);
	}

	void writeCartToFile(const std::string& fileName) {
		__cart.writeToFile(fileName);
	}

};

#endif /* CONTROLLER_CONTROLLER_H_ */
