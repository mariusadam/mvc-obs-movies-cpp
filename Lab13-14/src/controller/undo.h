#pragma once
#include "../repository/FileRepository.h"
class UndoAction {
public:
	virtual void doUndo() = 0;
	virtual ~UndoAction() {};
};

class UndoAdd : public UndoAction {
private:
	Film __addedFilm;
	Repository& __repo;
public:
	UndoAdd(Repository& repo, const Film& film) : __repo{ repo }, __addedFilm{ film } {}
	void doUndo() override {
		__repo.del(__addedFilm);
	}
};

class UndoDel : public UndoAction {
private:
	Film __deletedFilm;
	Repository& __repo;
public:
	UndoDel(Repository& repo, const Film& film) : __repo{ repo }, __deletedFilm{ film } {}
	void doUndo() override {
		__repo.add(__deletedFilm);
	}
};

class UndoUpdate : public UndoAction {
private:
	Film __oldFilm;
	Repository& __repo;
public:
	UndoUpdate(Repository& repo, const Film& oldFilm) : __repo{ repo }, __oldFilm{ oldFilm } {}
	void doUndo() override {
		__repo.update(__oldFilm);
	}
};