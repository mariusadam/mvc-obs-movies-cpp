#include <iostream>
#include "src/domain/Film.h"
#include "src/domain/FilmValidator.h"
#include "src/controller/controller.h"
#include "src/repository/repository.h"
#include "src/repository/FileRepository.h"
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>
#include <malloc.h>
#include <string>
#include "gui/app.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[]) {
	FilmValidator valid;
	FileRepository repo{ "Files//repo//data.csv" };
	FilmCartHtml htmlCart{ repo };
	Controller ctrl{ repo, valid, htmlCart };

	QApplication a(argc, argv);
	App gui{ ctrl };
	gui.show();
	return a.exec();
}
