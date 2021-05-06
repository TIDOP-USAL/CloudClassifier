#pragma once

#include <iostream>
#include <vector>

#include <QWidget>
#include <QLayout>

class Container : public QWidget {
	Q_OBJECT
private:
	QVBoxLayout* layout;
public:
	Container(QWidget* parent, const char* name);
	~Container();
public:
	inline void addWidget(QWidget* widget) {
		layout->addWidget(widget);
	}
};