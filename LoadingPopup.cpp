#include "LoadingPopup.h"

#include <QMovie>

LoadingPopup::LoadingPopup(QWidget* parent)
	: QDialog(parent), labelText(nullptr), labelGif(nullptr), layout(nullptr) {
}

LoadingPopup::LoadingPopup(QWidget* parent, const std::string& _text) 
	: QDialog(parent) {

	setWindowTitle(tr("Loading Popup"));
	setWindowModality(Qt::ApplicationModal);
	setModal(true);

	labelText = new QLabel(this);
	labelText->setText(_text.c_str());

	QMovie* movie = new QMovie(":/ico/icons/loading.gif");
	movie->start();
	labelGif = new QLabel(this);
	labelGif->setAttribute(Qt::WA_NoSystemBackground);
	labelGif->setMovie(movie);
	
	layout = new QVBoxLayout(this);
	layout->addWidget(labelText);
	layout->addWidget(labelGif);

	setLayout(layout);
}

LoadingPopup::~LoadingPopup() {
	
	if (labelText != nullptr)
		delete labelText;

	if (labelGif != nullptr)
		delete labelGif;

	if (layout != nullptr)
		delete layout;
}