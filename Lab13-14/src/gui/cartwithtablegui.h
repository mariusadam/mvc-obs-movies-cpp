#pragma once
#include <qwidget.h>
#include <qpushbutton.h>
#include <qlineedit.h>
#include <qtableview.h>
#include <qformlayout.h>
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
#include "../observer/observer.h"
#include "../model/moviestablemodel.h"
#include "../cart/filmcart.h"
#include <memory>

class CartWithTableGUI : public QWidget, public Observer {
private:
	std::shared_ptr<FilmCart> __cart;

	QTableView* __cartTableView;
	MoviesTableModel* __cartTableModel;
	QLabel* __labelCartMoviesNumber;
	QPushButton* __generateRandomButton;
	QPushButton* __manageCartButton;
	QPushButton* __addToCartButton;
	QPushButton* __deleteFromCartButton;
	QPushButton* __fillCartRandomButton;
	QPushButton* __clearCartButton;
	QPushButton* __exportCartButton;
	QPushButton* __quitCartButton;
	QLineEdit* __generateRandomLineEdit;
	QLineEdit* __fillCartRandomLineEdit;
	QLineEdit* __exportFileNameLineEdit;

	void __initComponents();
	void __connectCartWidgetSignalsSlots();
	void __reloadTable(const std::vector<Film>& movies);
	void __refreshCartTable();
	void __displayError(const std::string& error);

	private slots:
	void __on_fillCartRandomButton_clicked();
	void __on_deleteFromCartButton_clicked();
	void __on_clearCartButton_clicked();
	void __on_exportCartButton_clicked();
	void __on_quitCartButton_clicked();

public:

	CartWithTableGUI(std::shared_ptr<FilmCart> cart) : __cart{ cart } {
		this->__initComponents();
		this->__connectCartWidgetSignalsSlots();
	}

	~CartWithTableGUI() {
		this->__cart->removeObserver(this);
	}

	void update() override {
		this->__refreshCartTable();
	}

};