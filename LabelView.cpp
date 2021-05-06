#include "LabelView.h"

LabelView::LabelView(const std::string& _text, QWidget* parent, const char* name) 
	: text(_text) {

	color = QColor(0, 0, 0);
	colorButton = new QPushButton(this);
	colorButton->setFixedWidth(COLOR_BUTTON_SIZE);
	colorButton->setFixedHeight(COLOR_BUTTON_SIZE);
	setColor(color);
	
	label = new QLabel(this);
	label->setText(text.c_str());

	layout = new QHBoxLayout(this);
	layout->addWidget(colorButton);
	layout->addWidget(label);

	setLayout(layout);
}

LabelView::~LabelView() {
	delete colorButton;
	delete label;
	delete layout;
}

void LabelView::setText(const std::string& text) {
	this->text = text;
	label->setText(text.c_str());
	label->update();
}

void LabelView::setColor(const QColor& color) {
	this->color = color;
	QPalette pal = colorButton->palette();
	pal.setColor(QPalette::Button, color);
	colorButton->setAutoFillBackground(true);
	colorButton->setPalette(pal);
	colorButton->update();
}
