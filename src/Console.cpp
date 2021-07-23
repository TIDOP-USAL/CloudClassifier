#include "Console.h"

#include <QtWidgets/QApplication>

Console::Console(QWidget* parent)
	: textEdit(new QTextEdit(parent)) {
	textEdit->setReadOnly(true);
}


Console::Console(const Console& console)
	: textEdit(console.textEdit) {
}

Console::Console(Console&& console) noexcept 
	: textEdit(std::move(console.textEdit)) {
}

void Console::insertText(const std::string& text, int color) {
	textEdit->moveCursor(QTextCursor::End);
	textEdit->setTextColor(QColor(color));
	textEdit->insertPlainText(text.c_str());
	textEdit->moveCursor(QTextCursor::End);
}


void Console::writeText(const std::string& prefix, const std::string& txt, int colorPrefix, int color) {
	insertText(prefix.c_str(), colorPrefix);
	insertText(std::string(txt + "\n").c_str(), color);
	QApplication::processEvents();
}