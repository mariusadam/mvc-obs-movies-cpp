#pragma once
#include <qwidget.h>
#include "../observer/observer.h"
#include "../cart/filmcart.h"
#include <memory>
#include <qpainter.h>
#include <qlabel.h>
#include <qstring.h>
#include <string>
#include <qboxlayout.h>

class CartCirclesGUI : public QWidget, public Observer {
private:
	std::shared_ptr<FilmCart> __cart;

	QLabel* __labelCartMoviesNumber;

	void __initComponents();
public:
	CartCirclesGUI(std::shared_ptr<FilmCart> cart) {
		this->__cart = cart;
		this->__initComponents();
	}

	void update() override;
	void paintEvent(QPaintEvent* e) override;

};