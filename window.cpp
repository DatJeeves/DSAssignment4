#include "window.h"

using namespace std;

Window::Window() {
	timeToCompleteTransaction = 0;
	idleTime = 0;
}

bool Window::isFree() {
	if (timeToCompleteTransaction == 0) {
		return true;
	}
	else {
		return false;
	}
}

void Window::SetProcessTime(int prTime) {
	timeToCompleteTransaction = prTime;
}

void Window::ProcessStudent() {
	--timeToCompleteTransaction;
}

void Window::incrementIdle() {
	++idleTime;
}

int Window::GetTimeToComplete() {
	return timeToCompleteTransaction;
}

int Window::GetIdleTime() {
	return idleTime;
}

Window::~Window() {
	delete this;
}

