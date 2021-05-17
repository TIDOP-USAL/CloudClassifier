#pragma once

#include <QDialog>
#include <QLayout>
#include <QLabel>

class LoadingPopup : public QDialog {
	Q_OBJECT
private:
	QLabel* labelText;
	QLabel* labelGif;
	QVBoxLayout* layout;
public:
	LoadingPopup(QWidget* parent = nullptr);
	LoadingPopup(QWidget* parent, const std::string& _text);
	~LoadingPopup();
public:
	inline void setText(const std::string& text) {
		labelText->setText(text.c_str());
	}
};