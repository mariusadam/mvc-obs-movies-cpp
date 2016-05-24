#pragma once
#include <QAbstractTableModel>
#include "../domain/film.h"
#include <vector>

class MoviesTableModel : public QAbstractTableModel {
private:
	std::vector<Film> __movies;
public:
	MoviesTableModel(std::vector<Film> movies) : __movies{ movies } {}

	int rowCount(const QModelIndex& parent = QModelIndex()) const override {
		return __movies.size();
	}

	int columnCount(const QModelIndex& parent = QModelIndex()) const override {
		return 4;
	}

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
		if (role == Qt::DisplayRole) {
			Film film = __movies[index.row()];
			if (index.column() == 0) {
				return QString::fromStdString(film.getTitle());
			}
			else if (index.column() == 1) {
				return QString::fromStdString(film.getGen());
			}
			else if (index.column() == 2) {
				return QString::fromStdString(std::to_string(film.getReleaseYear()));
			}
			else if (index.column() == 3) {
				return QString::fromStdString(film.getMainActor());
			}
		}
		return QVariant();
	}

	QVariant headerData(int section, Qt::Orientation orientation, int role) const override {
		if (role == Qt::DisplayRole) {
			if (orientation == Qt::Horizontal) {
				switch (section) {
				case 0: return QString("Title");
				case 1: return QString("Gen");
				case 2: return QString("Release Year");
				case 3: return QString("Main Actor");
				default: return QVariant();
				}
			}
			else if (orientation == Qt::Vertical) {
				return section;
			}

		}
		return QVariant();
	}
};