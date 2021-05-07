#pragma once

#include <iostream>
#include <string>

#include <QWidget>
#include <QLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

#define COLOR_BUTTON_SIZE 15
#define LINE_EDIT_WIDTH 40;
#define WIDGET_HEIGHT 35

class LabelView : public QWidget {
	Q_OBJECT
private:
	std::string text;
	QLabel* label;
	QColor color;
	QPushButton* colorButton;
	QLineEdit* lineEdit;
	QHBoxLayout* layout;
public:
	LabelView(const std::string& _text, QWidget* parent, const char* name);
	~LabelView();
public:
	void setText(const std::string& text);
	void setColor(const QColor& color);
public slots:
	void colorPicker();

public:
	inline std::string& getText() {
		std::string lineText = lineEdit->text().toLocal8Bit().constData();
		return lineText;
	}

	inline QColor& getColor() {
		return color;
	}

	inline QPushButton* getColorButton() {
		return colorButton;
	}

	inline QLineEdit* getLineEdit() {
		return lineEdit;
	}
};