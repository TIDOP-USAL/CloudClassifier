#pragma once

#include <iostream>
#include <string>

#include <QWidget>
#include <QLayout>
#include <QLabel>
#include <QPushButton>

#define COLOR_BUTTON_SIZE 15

class LabelView : public QWidget {
	Q_OBJECT
private:
	std::string text;
	QLabel* label;
	QPushButton* colorButton;
	QColor color;
	QHBoxLayout* layout;
public:
	LabelView(const std::string& _text, QWidget* parent, const char* name);
	~LabelView();
public:
	void setText(const std::string& text);
	void setColor(const QColor& color);
public:
	inline std::string& getText() {
		return text;
	}

	inline QColor& getColor() {
		return color;
	}

	inline QPushButton* getColorButton() {
		return colorButton;
	}

};