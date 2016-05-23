#ifndef APP_H
#define APP_H

#include <QtWidgets/QMainWindow>
#include "ui_app.h"

class App : public QMainWindow
{
	Q_OBJECT

public:
	App(QWidget *parent = 0);
	~App();

private:
	Ui::AppClass ui;
};

#endif // APP_H
