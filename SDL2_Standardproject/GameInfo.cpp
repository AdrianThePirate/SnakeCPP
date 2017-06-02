#include "GameInfo.h"


GameInfo::GameInfo(int windowX, int windowY) {
	m_windowX = windowX;
	m_windowY = windowY;
}

int GameInfo::getWindowX() const {
	return m_windowX;
}

int GameInfo::getWindowY() const {
	return m_windowY;
}