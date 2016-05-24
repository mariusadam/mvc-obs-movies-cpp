#include "cartwithtablegui.h"

void CartWithTableGUI::__initComponents() {

	__cart->addObserver(this);

	QGridLayout* layoutCart = new QGridLayout;
	this->setLayout(layoutCart);

	QWidget* widgetCartTable = new QWidget;
	QVBoxLayout* layoutCartTable = new QVBoxLayout;
	widgetCartTable->setLayout(layoutCartTable);
	this->__labelCartMoviesNumber = new QLabel("Total movies: 0");
	layoutCartTable->addWidget(this->__labelCartMoviesNumber);
	this->__cartTableView = new QTableView;
	layoutCartTable->addWidget(this->__cartTableView);
	;
	this->__deleteFromCartButton = new QPushButton("Delete selected");
	this->__clearCartButton = new QPushButton("Empty the cart");

	QWidget* widgetFillRandom = new QWidget;
	QFormLayout* layoutFormFillRandom = new QFormLayout;
	widgetFillRandom->setLayout(layoutFormFillRandom);
	QLabel* labelHowMany = new QLabel("How many:");
	this->__fillCartRandomLineEdit = new QLineEdit;
	layoutFormFillRandom->addRow(labelHowMany, this->__fillCartRandomLineEdit);
	this->__fillCartRandomButton = new QPushButton("Fill random");
	layoutFormFillRandom->addWidget(this->__fillCartRandomButton);

	QWidget* widgetExport = new QWidget;
	QFormLayout* layoutFormExport = new QFormLayout;
	widgetExport->setLayout(layoutFormExport);
	QLabel* labelFileName = new QLabel("Enter file name:");
	this->__exportFileNameLineEdit = new QLineEdit;
	layoutFormExport->addRow(labelFileName, this->__exportFileNameLineEdit);
	this->__exportCartButton = new QPushButton("Export as html");
	layoutFormExport->addWidget(this->__exportCartButton);

	this->__quitCartButton = new QPushButton("Quit");

	layoutCart->addWidget(widgetCartTable, 0, 0, 2, 2);
	//layoutCart->addWidget(widgetCartOperations, 3, 0, 1, 1);
	layoutCart->addWidget(widgetFillRandom, 2, 0);
	layoutCart->addWidget(this->__clearCartButton, 2, 1);
	layoutCart->addWidget(widgetExport, 3, 0);
	layoutCart->addWidget(this->__deleteFromCartButton, 3, 1);
	layoutCart->addWidget(this->__quitCartButton, 4, 3);

	this->__refreshCartTable();
}

void CartWithTableGUI::__connectCartWidgetSignalsSlots() {
	QObject::connect(__fillCartRandomButton, &QPushButton::clicked, this, &CartWithTableGUI::__on_fillCartRandomButton_clicked);
	QObject::connect(__deleteFromCartButton, &QPushButton::clicked, this, &CartWithTableGUI::__on_deleteFromCartButton_clicked);
	QObject::connect(__clearCartButton, &QPushButton::clicked, this, &CartWithTableGUI::__on_clearCartButton_clicked);
	QObject::connect(__exportCartButton, &QPushButton::clicked, this, &CartWithTableGUI::__on_exportCartButton_clicked);
	QObject::connect(__cartTableView, &QTableView::clicked, this, [&](const QModelIndex& index) {
		if (index.isValid() == false) {
			this->__displayError("You have not selected a valid cell!");
		}
		int row = index.row();
		this->__cartTableView->selectRow(row);
	});
}

void CartWithTableGUI::__on_fillCartRandomButton_clicked() {
	int howMany{ this->__fillCartRandomLineEdit->text().toInt() };
	this->__cart->fillRandom(howMany);
	this->__refreshCartTable();
}

void CartWithTableGUI::__on_deleteFromCartButton_clicked() {
	std::string errors{ "" };
	QModelIndexList selectedRows = this->__cartTableView->selectionModel()->selectedRows();
	if (selectedRows.empty()) {
		this->__displayError("You have not selected any movie yet");
		return;
	}
	for (auto& index : selectedRows) {
		int row = index.row();
		std::string title = index.sibling(row, 0).data().toString().toStdString();
		try {
			this->__cart->del(title);
		}
		catch (FilmException& ex) {
			errors += ex.getMsg() + "\n";
		}
	}
	this->__refreshCartTable();

	if (!errors.empty()) {
		this->__displayError(errors);
	}
}

void CartWithTableGUI::__on_clearCartButton_clicked() {
	this->__cart->clear();
	this->__refreshCartTable();
}

void CartWithTableGUI::__on_exportCartButton_clicked() {
	std::string fileName{ this->__exportFileNameLineEdit->text().toStdString() };
	if (fileName.empty()) {
		this->__displayError("You have not entered the filename!");
		return;
	}
	this->__cart->writeToFile(fileName);
	this->__displayError("Exported as html!");
}

void CartWithTableGUI::__reloadTable(const std::vector<Film>& movies) {
	std::string tmp{ "Total: " + std::to_string(movies.size()) };
	this->__labelCartMoviesNumber->setText(tmp.c_str()); 
	this->__cartTableModel = new MoviesTableModel(movies);
	this->__cartTableView->setModel(this->__cartTableModel);
	this->__cartTableView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void CartWithTableGUI::__displayError(const std::string& error) {
	QMessageBox::warning(this, "Warning", QString::fromStdString(error));
}

void CartWithTableGUI::__refreshCartTable() {
	std::vector<Film>& films = this->__cart->getAll();
	this->__reloadTable(films);
}