#ifndef GAMEINFO_H
#define GAMEINFO_H

class GameInfo
{
public:
	GameInfo(int windowX, int windowY);
	int getWindowX() const;
	int getWindowY() const;
private:
	int m_windowX;
	int m_windowY;
};
#endif