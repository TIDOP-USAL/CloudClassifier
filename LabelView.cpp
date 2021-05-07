#include "LabelView.h"

#include <QColorDialog>

LabelView::LabelView(const std::string& _text, QWidget* parent, const char* name) 
	: text(_text) {

	label = new QLabel(this);
	label->setText("Color:");

	color = QColor(0, 0, 0);
	colorButton = new QPushButton(this);
	colorButton->setFixedWidth(COLOR_BUTTON_SIZE);
	colorButton->setFixedHeight(COLOR_BUTTON_SIZE);
	setColor(color);

	lineEdit = new QLineEdit(this);
	lineEdit->setText(text.c_str());
	
	layout = new QHBoxLayout(this);
	layout->setMargin(10);
	layout->addWidget(label);
	layout->addWidget(colorButton);
	layout->addWidget(lineEdit);
	
	setFixedWidth(parent->width());
	setFixedHeight(WIDGET_HEIGHT);
	setLayout(layout);

	connect(colorButton, &QPushButton::pressed, this, &LabelView::colorPicker);
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
	std::string red = std::to_string(color.red());
	std::string green = std::to_string(color.green());
	std::string blue = std::to_string(color.blue());
	std::string style = "background-color: rgba(" + red + ", " + green + ", " + blue + ", 1); border: none;";
	colorButton->setStyleSheet(style.c_str());
}

void LabelView::colorPicker() {
	setColor(QColorDialog::getColor(Qt::yellow, this));
}