#pragma once

/*
	MIT License
	Copyright (c) 2021 Alberto Morcillo Sanz
	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:
	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.
	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.
	------------------------------------------------------------------------------
	Description: Simple progress dialog in C++ using Win32
	GitHub: https://github.com/MorcilloSanz/WProgressDialog
	Twitter: @MorcilloSanz
	Email: amorcillosanz@gmail.com
*/

#if (_MSC_VER >= 1500 && _MSC_VER <= 1924 )
#define _VISUAL
#endif

#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <utility>
#include <functional>

#include "Windows.h"

#define WPROGRESSDIALOG_WIDTH 250
#define WPROGRESSDIALOG_HEIGHT 155
#define WPROGRESSDIALOG_CLASS "WPROGRESSDIALOG%d"

#define WPROGRESSDIALOG_BAR_HEIGHT 40
#define WPROGRESSDIALOG_BAR_BACKGROUND RGB(0, 0, 0)
#define WPROGRESSDIALOG_BAR_FOREGROUND RGB(200, 121, 252)

class WProgressDialog {
private:
	struct Vec {
		int x, y;

		Vec(int _x, int _y)
			: x(_x), y(_y) {
		}
		Vec() = default;
		~Vec() = default;
	};
private:
	static unsigned int windowCounter;

	HINSTANCE hInstance;
	HWND hwnd;
	MSG msg;
	WNDCLASS wc;

	std::string className;
	std::thread windowThread;
private:
	std::string title;
	static std::string label, progress;
	static long minimum, maximum, value;
	static bool showProgress;
	bool open;
public:
	WProgressDialog(const std::string& _title, const std::string& _label, long _minimum, long _maximum);
	WProgressDialog() = default;
	~WProgressDialog();
private:
	static WCHAR* toWchar(char* chr);

	static void drawRect(HDC hdc, long x, long y, long width, long height, COLORREF color);
	static void drawProgress(HDC hdc);

	static void drawText(HWND hwnd, HDC hdc, std::string& text);
	static void drawText(HWND hwnd, HDC hdc, std::string& text, long x, long y);
	static void drawText(HWND hwnd, HDC hdc, std::string& text, const Vec &pos, const Vec &size);

	static void draw(HWND hwnd, HDC hdc);
	static void drawProcedure(HWND hwnd);

	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	void registerWindowClass();
	WProgressDialog::Vec& getScreenDimensions();
	void createWindow();
	void pollEvents();
	void init();
public:
	void setRange(long minimum, long maximum);
	void reset();
	void close();
public:
	inline void setValue(long value) {
		WProgressDialog::value = value;
	}

	inline void setLabel(const std::string& label) {
		WProgressDialog::label = label;
	}

	inline void showProgressEnabled(bool enable) {
		WProgressDialog::showProgress = enable;
	}

	inline void show() {
		ShowWindow(hwnd, SW_SHOW);
	}

	inline void hide() {
		ShowWindow(hwnd, SW_HIDE);
	}
};