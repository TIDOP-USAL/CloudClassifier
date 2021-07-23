#pragma once

#pragma once

#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <string>
#include <functional>
#include <future>

#define BUFFER_SIZE 4096

class LightProcess {
public:
	enum class Mode : unsigned char {
		READ, WRITE, BINARY, TEXT
	};
private:
	FILE* fp;
	std::string path;
	Mode mode;
	std::function<void(const std::string&)> wrapper;
	bool running;

	std::future<void> future;
public:
	LightProcess(const std::string& _path, const Mode& _mode, const std::function<void(const std::string&)>& _wrapper);
	~LightProcess() = default;
private:
	void initProcess();
	void initThread();
public:
	inline void wait() {
		future.wait();
	}
public:
	inline std::string& getPath() {
		return path;
	}

	inline Mode& getMode() {
		return mode;
	}

	inline const bool& isRunning() {
		return running;
	}

	inline std::future<void>* getFuture() {
		return &future;
	}
};