#include "WProgressDialog.h"

WProgressDialog::WProgressDialog(const std::string& _title, const std::string& _label, long _minimum, long _maximum)
	: title(_title), open(true) {
	reset();
	setLabel(_label);
	setRange(_minimum, _maximum);
	init();
}

WProgressDialog::~WProgressDialog() {
	close();
	windowThread.join();
}

WCHAR* WProgressDialog::toWchar(char* chr) {
	const unsigned int length = strlen(chr);
	WCHAR* buffer = (WCHAR*)malloc(sizeof(WCHAR) * length);
	int nChars = MultiByteToWideChar(CP_ACP, 0, chr, -1, NULL, 0);
	MultiByteToWideChar(CP_ACP, 0, chr, -1, (LPWSTR)buffer, nChars);
	return buffer;
}

void WProgressDialog::drawRect(HDC hdc, long x, long y, long width, long height, COLORREF color) {
	RECT rect = { x, y, width, height };
	HBRUSH brush = CreateSolidBrush(color);
	FillRect(hdc, &rect, brush);
	DeleteObject(brush);
}

void WProgressDialog::drawProgress(HDC hdc) {
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

void WProgressDialog::drawText(HWND hwnd, HDC hdc, std::string& text) {
	RECT rect;
	GetClientRect(hwnd, &rect);
#if defined(_VISUAL)
	DrawText(hdc, toWchar(&text[0]), -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
#else
	DrawText(hdc, &text[0], -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
#endif
}

void WProgressDialog::drawText(HWND hwnd, HDC hdc, std::string& text, long x, long y) {
	RECT rect;
	GetClientRect(hwnd, &rect);
	rect.left = x;
	rect.top = y;
	rect.bottom = rect.bottom - y;
	rect.right = rect.right - x;
#if defined(_VISUAL)
	DrawText(hdc, toWchar(&text[0]), -1, &rect, DT_SINGLELINE);
#else
	DrawText(hdc, &text[0], -1, &rect, DT_SINGLELINE);
#endif
}

void WProgressDialog::drawText(HWND hwnd, HDC hdc, std::string& text, const Vec& pos, const Vec& size) {
	RECT rect = { pos.x, pos.y, size.x, size.y };
#if defined(_VISUAL)
	DrawText(hdc, toWchar(&text[0]), strlen(text.c_str()), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
#else
	DrawText(hdc, &text[0], strlen(text.c_str()), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
#endif
}

void WProgressDialog::draw(HWND hwnd, HDC hdc) {
	drawProgress(hdc);
	drawText(hwnd, hdc, WProgressDialog::label, 10, 10);
	if (WProgressDialog::showProgress) {
		drawText(hwnd, hdc, WProgressDialog::progress);
	}
}

void WProgressDialog::drawProcedure(HWND hwnd) {
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

LRESULT CALLBACK WProgressDialog::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
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

void WProgressDialog::registerWindowClass() {
	className = className + std::to_string(WProgressDialog::windowCounter);
	memset(&wc, 0, sizeof(wc));
	wc.lpfnWndProc = &WProgressDialog::WindowProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = NULL;
#if defined(_VISUAL)
	wc.lpszClassName = WProgressDialog::toWchar(&className[0]);
#else
	wc.lpszClassName = &className[0];
#endif
	RegisterClass(&wc);
}

WProgressDialog::Vec& WProgressDialog::getScreenDimensions() {
	RECT desktop;
	const HWND hDesktop = GetDesktopWindow();
	GetWindowRect(hDesktop, &desktop);
	Vec dimensions(desktop.right, desktop.bottom);
	return dimensions;
}

void WProgressDialog::createWindow() {
	hInstance = GetModuleHandle(0);
	registerWindowClass();

	Vec screenDimensions = getScreenDimensions();
	int x = screenDimensions.x / 2 - WPROGRESSDIALOG_WIDTH / 2;
	int y = screenDimensions.y / 2 - WPROGRESSDIALOG_HEIGHT / 2;

#if defined(_VISUAL)
	hwnd = CreateWindowEx(0, WProgressDialog::toWchar(&className[0]), WProgressDialog::toWchar(&title[0]), WS_CAPTION | WS_POPUPWINDOW | WS_VISIBLE,
		x, y, WPROGRESSDIALOG_WIDTH, WPROGRESSDIALOG_HEIGHT, NULL, NULL, hInstance, NULL);
#else
	hwnd = CreateWindowEx(0, &className[0], &title[0], WS_CAPTION | WS_POPUPWINDOW | WS_VISIBLE,
		x, y, WPROGRESSDIALOG_WIDTH, WPROGRESSDIALOG_HEIGHT, NULL, NULL, hInstance, NULL);
#endif

	WProgressDialog::windowCounter++;
}

void WProgressDialog::pollEvents() {
	int got = GetMessage(&msg, NULL, 0, 0);
	TranslateMessage(&msg);
	DispatchMessage(&msg);
}

void WProgressDialog::init() {
	windowThread = std::thread([&]() {
		createWindow();
		show();
		while (open) {
			pollEvents();
		}
	});
}

void WProgressDialog::setRange(long minimum, long maximum) {
	WProgressDialog::minimum = minimum;
	WProgressDialog::maximum = maximum;
}

void WProgressDialog::reset() {
	WProgressDialog::label = "";
	WProgressDialog::progress = "0%";
	WProgressDialog::showProgress = true;
	WProgressDialog::minimum = 0;
	WProgressDialog::maximum = 0;
	WProgressDialog::value = 0;
}

void WProgressDialog::close() {
	open = false;
}

unsigned int WProgressDialog::windowCounter = 0;
std::string WProgressDialog::label = "";
std::string WProgressDialog::progress = "0%";
bool WProgressDialog::showProgress = true;
long WProgressDialog::minimum = 0;
long WProgressDialog::maximum = 0;
long WProgressDialog::value = 0;