#include "LabelView.h"

#include <QColorDialog>

LabelView::LabelView(unsigned int _id, const std::string& _text, QWidget* parent, const char* name) 
	: id(_id), text(_text) {

	color = QColor(0, 0, 0);
	colorButton = new QPushButton(this);
	colorButton->setFixedWidth(COLOR_BUTTON_SIZE);
	colorButton->setFixedHeight(COLOR_BUTTON_SIZE);
	setColor(color);

	lineEdit = new QLineEdit(this);
	lineEdit->setFixedHeight(20);
	lineEdit->setText(text.c_str());

	deleteButton = new QPushButton(this);
	QIcon icon;
	icon.addFile(QStringLiteral(":/ico/icons/delete.png"), QSize(), QIcon::Normal, QIcon::Off);
	deleteButton->setFixedSize(QSize(24, 24));
	deleteButton->setIcon(icon);
	std::string style = "background-color: none; border: none;";
	deleteButton->setStyleSheet(style.c_str());
	
	layout = new QHBoxLayout(this);
	layout->setMargin(10);
	layout->addWidget(colorButton);
	layout->addWidget(lineEdit);
	layout->addWidget(deleteButton);
	
	setFixedWidth(parent->width() - 25);
	setFixedHeight(LABEL_VIEW_HEIGHT);
	setLayout(layout);

	connect(colorButton, &QPushButton::pressed, this, &LabelView::colorPicker);
	connect(deleteButton, &QPushButton::pressed, this, [&]() {
		emit deleteSignal(id);
	});
}

LabelView::LabelView(const LabelView& labelView)
	: id(0), text(labelView.text), color(labelView.color), colorButton(labelView.colorButton), deleteButton(labelView.deleteButton), 
	lineEdit(labelView.lineEdit), layout(labelView.layout) {
}

LabelView::~LabelView() {
	delete colorButton;
	delete lineEdit;
	delete layout;
}

LabelView& LabelView::operator=(const LabelView& labelView) {
	text = labelView.text;
	color = labelView.color;
	colorButton = labelView.colorButton;
	deleteButton = labelView.deleteButton;
	lineEdit = labelView.lineEdit;
	layout = labelView.layout;
	return *this;
}

void LabelView::setText(const std::string& text) {
	this->text = text;
	lineEdit->setText(text.c_str());
}

void LabelView::setColor(const QColor& color) {
	this->color = color;
	std::string red = std::to_string(color.red());
	std::string green = std::to_string(color.green());
	std::string blue = std::to_string(color.blue());
	std::string style = "background-color: rgba(" + red + ", " + green + ", " + blue + ", 1); border: none;";
	colorButton->setStyleSheet(style.c_str());
}

void LabelView::setDeleteFunction(const std::function<void()>& fun) {
	//connect(deleteButton, &QPushButton::pressed, this, fun);
}

void LabelView::colorPicker() {
	setColor(QColorDialog::getColor(Qt::yellow, this));
}