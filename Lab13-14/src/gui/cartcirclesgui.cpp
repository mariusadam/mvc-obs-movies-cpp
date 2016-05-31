#include "cartcirclesgui.h"

void CartCirclesGUI::__initComponents() {
	//do i have to set a layout ?
	/*
	std::string str{ "Total: " + std::to_string(this->__cart->size()) };
	this->__labelCartMoviesNumber = new QLabel(str.c_str());
	QVBoxLayout* layoutMain = new QVBoxLayout(this);
	layoutMain->addWidget(this->__labelCartMoviesNumber);
	//*/

}

void CartCirclesGUI::update() {
	this->repaint();
}

void CartCirclesGUI::paintEvent(QPaintEvent * e) {
	QPainter* painter = new QPainter(this);
	std::string str{ "Total: " + std::to_string(this->__cart->size()) };
	painter->drawText(0, 0, QString::fromStdString(str));
	int size = this->__cart->size();
	for (int i = 1; i <= size; i++) {
		painter->drawEllipse(10 * i, 10 * i, 40, 40);
	}
	
}
