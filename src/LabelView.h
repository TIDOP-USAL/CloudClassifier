#pragma once

#include <iostream>
#include <string>
#include <functional>

#include <QWidget>
#include <QLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

#define COLOR_BUTTON_SIZE 20
#define LINE_EDIT_WIDTH 40
#define LABEL_VIEW_HEIGHT 50

class LabelView : public QWidget {
	Q_OBJECT
private:
	unsigned int id;
	std::string text;
	QColor color;
	QPushButton* colorButton;
	QPushButton* deleteButton;
	QLineEdit* lineEdit;
	QHBoxLayout* layout;
public:
	LabelView(unsigned int _id, const std::string& _text, QWidget* parent, const char* name);
	LabelView(const LabelView& labelView);
	~LabelView();
	LabelView& operator=(const LabelView& labelView);
public:
	void setText(const std::string& text);
	void setColor(const QColor& color);
	void setDeleteFunction(const std::function<void()>& fun);
signals:
	void deleteSignal(unsigned int);
public slots:
	void colorPicker();

public:

	inline unsigned int getID() const {
		return id;
	}

	inline QString& getText() {
		return lineEdit->text();
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