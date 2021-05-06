#include "Container.h"

Container::Container(QWidget* parent = 0, const char* name = 0) {
	layout = new QVBoxLayout(this);
}

Container::~Container() {
	delete layout;
}