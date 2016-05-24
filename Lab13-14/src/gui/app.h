#ifndef APP_H
#define APP_H

#include <string.h>
#include <windows.h>
#include <QShortcut>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QFormLayout>
#include <qtablewidget.h>
#include <QComboBox>
#include <QCheckBox>
#include <qtabwidget.h>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMessageBox>
#include <qlistwidget.h>
#include <qpushbutton.h>
#include <qlineedit.h>
#include <QTime>
#include <QtWidgets/QMainWindow>
#include <vector>
#include <string>
#include "ui_app.h"
#include "../Model/MoviesTableModel.h"
#include "../controller/controller.h"
#include "cartwithtablegui.h"


class App : public QMainWindow
{
	Q_OBJECT
private:
	//Ui::AppClass ui;
	Controller& __ctrl;

	QTabWidget* __tabWidget;
	QWidget* __widgetMain;
	CartWithTableGUI* __widgetCart;
	QTime __timeStamp;
	QTableView* __moviesTableView = new QTableView;
	QTableView* __cartTableView = new QTableView;
	MoviesTableModel* __moviesTableModel = new MoviesTableModel({});
	MoviesTableModel* __cartTableModel = new MoviesTableModel({});
	QListView* __moviesListView = new QListView;
	QLabel* __labelMoviesNumber;
	QLabel* __labelCartMoviesNumber = new QLabel("");
	QPushButton* __refresh;
	QPushButton* __sortButton;
	QPushButton* __sortByTitleButton;
	QPushButton* __addButton;
	QPushButton* __updateButton;
	QPushButton* __deleteButton;
	QPushButton* __searchButton;
	QPushButton* __quitButton;
	QPushButton* __quitCartButton;
	QPushButton* __generateRandomButton;
	QPushButton* __manageCartButton;
	QPushButton* __addToCartButton;
	QPushButton* __undoButton;
	QComboBox* __sortByComboBox;
	QComboBox* __sortDirectionComboBox;
	QLineEdit* __titleLineEdit;
	QLineEdit* __genLineEdit;
	QLineEdit* __releaseYearLineEdit;
	QLineEdit* __mainActorLineEdit;
	QLineEdit* __searchLineEdit;
	QLineEdit* __generateRandomLineEdit;

	void __initComponents();
	void __initMainWidget();
	void __connectSignalsSlots();
	void __connectMainWidgetSignalsSlots();
	void __refreshMainTable();
	void __refreshCartTable();
	void __reloadMainTable(const std::vector<Film>& filme);
	void __reloadCartTable(const std::vector<Film>& films);
	void __inLineDetalisEdit(const std::string& title, const std::string& gen, const std::string& releaseYear, const std::string& mainActor);
	void __addComboBoxSortOptions();
	void __displayError(const std::string& error);

	private slots:
	void __on_addButton_clicked();
	void __on_selectedTableCell_clicked(const QModelIndex &index);
	void __on_deleteButton_clicked();
	void __on_searchButton_clicked();
	void __on_quitButton_clicked();
	void __on_generateRandomButton_clicked();
	void __on_updateButton_clicked();
	void __on_undoButton_clicked();
	void __on_sortButton_clicked();
	void __on_addToCartButton_clicked();
	void __on_manageCartButton_clicked();

public:
	App(Controller& __ctrl) : __ctrl{ __ctrl } {
		//boot the application here!
		__initComponents();
		__connectSignalsSlots();
	}
	~App();
};

#endif // APP_H