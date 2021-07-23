#pragma once

#include <iostream>
#include <string>
#include <vector>

#include <QThread>
#include <QWidget>
#include <QColor>
#include <QTextEdit>
#include <QString>

#define LOG_COLOR 0x000000
#define WARN_COLOR 0xd1b200
#define ERROR_COLOR 0xeb344f
#define SUCCESS_COLOR 0x67c96a

#define LOG_PREFIX "[LOG] "
#define WARN_PREFIX "[WARN] "
#define ERROR_PREFIX "[ERROR] "
#define SUCCESS_PREFIX "[SUCCESS] "

class Console {
private:
	QTextEdit* textEdit;
public:
	Console(QWidget* parent = nullptr);
	Console(const Console& console);
	Console(Console&& console) noexcept;
	Console() = default;
	~Console() = default;

private:
	void insertText(const std::string& text, int color);
	void writeText(const std::string& prefix, const std::string& txt, int colorPrefix, int color);

public:
	inline void log(const std::string& logMsg) {
		writeText(std::string(LOG_PREFIX), logMsg, LOG_COLOR, LOG_COLOR);
	}

	inline void warn(const std::string& warnMsg) {
		writeText(std::string(WARN_PREFIX), warnMsg, WARN_COLOR, LOG_COLOR);
	}

	inline void error(const std::string& errorMsg) {
		writeText(std::string(ERROR_PREFIX), errorMsg, ERROR_COLOR, LOG_COLOR);
	}

	inline void success(const std::string& successMsg) {
		writeText(std::string(SUCCESS_PREFIX), successMsg, SUCCESS_COLOR, LOG_COLOR);
	}

	inline void clear() {
		textEdit->clear();
	}

public:
	inline QTextEdit* getWidget() {
		return textEdit;
	}
};