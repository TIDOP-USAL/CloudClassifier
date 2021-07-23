#include "LightProcess.h"


LightProcess::LightProcess(const std::string& _path, const Mode& _mode, const std::function<void(const std::string&)>& _wrapper)
	: fp(nullptr), mode(_mode), path(_path), wrapper(_wrapper), running(true) {

	initProcess();
	initThread();
}

void LightProcess::initProcess() {
	switch (mode) {
	case Mode::READ:
		fp = _popen(path.c_str(), "r");
		break;
	case Mode::WRITE:
		fp = _popen(path.c_str(), "W");
		break;
	case Mode::BINARY:
		fp = _popen(path.c_str(), "b");
		break;
	case Mode::TEXT:
		fp = _popen(path.c_str(), "t");
		break;
	default:
		fp = nullptr;
		break;
	}
}

void LightProcess::initThread() {
	auto threadProc = [&]() {
		while (running) {
			/* Update output */
			char buff[BUFFER_SIZE];
			while (fgets(buff, BUFFER_SIZE, fp) != NULL) {
				std::string output(buff);
				wrapper(output);
			}

			/* Check if the process finished */
			if (_pclose(fp) == -1)
				running = false;
		}
	};

	future = std::async(std::launch::async, threadProc);
}