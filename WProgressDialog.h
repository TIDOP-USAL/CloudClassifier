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
	WProgressDialog(const std::string& _title, const std::string& _label, long _minimum, long _maximum)
		: title(_title), open(true) {
		reset();
		setLabel(_label);
		setRange(_minimum, _maximum);
		init();
	}

	WProgressDialog() = default;

	~WProgressDialog() {
		open = false;
		windowThread.join();
	}

private:

	static WCHAR* toWchar(char* chr) {
		const unsigned int length = strlen(chr);
		WCHAR* buffer = (WCHAR*)malloc(sizeof(WCHAR) * length);
		int nChars = MultiByteToWideChar(CP_ACP, 0, chr, -1, NULL, 0);
		MultiByteToWideChar(CP_ACP, 0, chr, -1, (LPWSTR)buffer, nChars);
		return buffer;
	}

	static void drawRect(HDC hdc, long x, long y, long width, long height, COLORREF color) {
		RECT rect = { x, y, width, height };
		HBRUSH brush = CreateSolidBrush(color);
		FillRect(hdc, &rect, brush);
		DeleteObject(brush);
	}

	static void drawProgress(HDC hdc) {
		long x = 10;
		long y = WPROGRESSDIALOG_HEIGHT / 2 + 15;
		long width = WPROGRESSDIALOG_WIDTH - 2 * x - 10;
		long height = WPROGRESSDIALOG_BAR_HEIGHT;

		if (WProgressDialog::value < WProgressDialog::maximum)
			drawRect(hdc, x, y, width, height, WPROGRESSDIALOG_BAR_BACKGROUND);

		if (WProgressDialog::value > 0) {
			float percent = static_cast<float>(WProgressDialog::value) / static_cast<float>((WProgressDialog::maximum - WProgressDialog::minimum));
			long progressPixels = percent * width;
			int percentProgress = percent * 100;
			WProgressDialog::progress = std::to_string(percentProgress) + "%";
			if (WProgressDialog::value < WProgressDialog::maximum)
				drawRect(hdc, x, y, progressPixels, height, WPROGRESSDIALOG_BAR_FOREGROUND);
			else
				drawRect(hdc, x, y, width, height, WPROGRESSDIALOG_BAR_FOREGROUND);
		}
	}

	static void drawText(HWND hwnd, HDC hdc, std::string& text) {
		RECT rect;
		GetClientRect(hwnd, &rect);
		DrawText(hdc, &text[0], -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}

	static void drawText(HWND hwnd, HDC hdc, std::string& text, long x, long y) {
		RECT rect;
		GetClientRect(hwnd, &rect);
		rect.left = x;
		rect.top = y;
		rect.bottom = rect.bottom - y;
		rect.right = rect.right - x;
		DrawText(hdc, &text[0], -1, &rect, DT_SINGLELINE);
	}

	static void drawText(HWND hwnd, HDC hdc, std::string& text, Vec pos, Vec size) {
		RECT rect = { pos.x, pos.y, size.x, size.y };
		DrawText(hdc, &text[0], strlen(text.c_str()), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}

	static void draw(HWND hwnd, HDC hdc) {
		drawProgress(hdc);
		drawText(hwnd, hdc, WProgressDialog::label, 10, 10);
		if (WProgressDialog::showProgress) {
			drawText(hwnd, hdc, WProgressDialog::progress);
		}
	}

	static void drawProcedure(HWND hwnd) {
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);

		RECT rect;
		GetClientRect(hwnd, &rect);

		HDC backbuffDC = CreateCompatibleDC(hdc);
		HBITMAP backbuffer = CreateCompatibleBitmap(hdc, rect.right, rect.bottom);

		int savedDC = SaveDC(backbuffDC);
		SelectObject(backbuffDC, backbuffer);
		HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 255));
		FillRect(backbuffDC, &rect, hBrush);
		DeleteObject(hBrush);

		draw(hwnd, backbuffDC);

		BitBlt(hdc, 0, 0, rect.right, rect.bottom, backbuffDC, 0, 0, SRCCOPY);
		RestoreDC(backbuffDC, savedDC);

		DeleteObject(backbuffer);
		DeleteDC(backbuffDC);

		EndPaint(hwnd, &ps);

		InvalidateRect(hwnd, &rect, FALSE);
		UpdateWindow(hwnd);
	}

	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
		switch (uMsg) {
		case WM_CLOSE:
			break;
		case WM_DESTROY:
			break;
		case WM_PAINT:
			drawProcedure(hwnd);
			break;
		case WM_ERASEBKGND:
			return 1;
		default:
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
		}
	}

	void registerWindowClass() {
		className = className + std::to_string(WProgressDialog::windowCounter);
		memset(&wc, 0, sizeof(wc));
		wc.lpfnWndProc = &WProgressDialog::WindowProc;
		wc.hInstance = hInstance;
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = NULL;
		wc.lpszClassName = &className[0];
		RegisterClass(&wc);
	}

	Vec getScreenDimensions() {
		RECT desktop;
		const HWND hDesktop = GetDesktopWindow();
		GetWindowRect(hDesktop, &desktop);
		return Vec(desktop.right, desktop.bottom);
	}

	void createWindow() {
		hInstance = GetModuleHandle(0);
		registerWindowClass();

		Vec screenDimensions = getScreenDimensions();
		int x = screenDimensions.x / 2 - WPROGRESSDIALOG_WIDTH / 2;
		int y = screenDimensions.y / 2 - WPROGRESSDIALOG_HEIGHT / 2;

		hwnd = CreateWindowEx(0, &className[0], &title[0], WS_CAPTION | WS_POPUPWINDOW | WS_VISIBLE,
			x, y, WPROGRESSDIALOG_WIDTH, WPROGRESSDIALOG_HEIGHT, NULL, NULL, hInstance, NULL);
	}

	void pollEvents() {
		int got = GetMessage(&msg, NULL, 0, 0);
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	void init() {
		windowThread = std::thread([&]() {
			createWindow();
			show();
			while (open) {
				pollEvents();
			}
			});
	}

public:
	inline void setValue(long value) {
		WProgressDialog::value = value;
	}

	void setRange(long minimum, long maximum) {
		WProgressDialog::minimum = minimum;
		WProgressDialog::maximum = maximum;
	}

	inline void setLabel(const std::string& label) {
		WProgressDialog::label = label;
	}

	inline void reset() {
		WProgressDialog::label = "";
		WProgressDialog::progress = "0%";
		WProgressDialog::showProgress = true;
		WProgressDialog::minimum = 0;
		WProgressDialog::maximum = 0;
		WProgressDialog::value = 0;
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

	void close() {
		open = false;
		PostQuitMessage(0);
	}

};

unsigned int WProgressDialog::windowCounter = 0;
std::string WProgressDialog::label = "";
std::string WProgressDialog::progress = "0%";
bool WProgressDialog::showProgress = true;
long WProgressDialog::minimum = 0;
long WProgressDialog::maximum = 0;
long WProgressDialog::value = 0;