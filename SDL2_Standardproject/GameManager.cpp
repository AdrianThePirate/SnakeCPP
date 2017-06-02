/*
 * @file: GameManager.cpp
 * @author: Stig M. Halvorsen <halsti@nith.no>
 * @version: 1.0.0 <11.02.2013>
 *
 * @description: A singleton class to control all gameplay.
 */

#include "GameManager.h"

/* Initializes SDL, creates the game window and fires off the timer. */
GameManager::GameManager()
{
	SDLManager::Instance().init();
	int windowSizeX = 550;
	int windowSizeY = 400;
	m_window = SDLManager::Instance().createWindow("SNEK", windowSizeX, windowSizeY);
	m_gameInfo = new GameInfo(windowSizeX, windowSizeY);
	Timer::Instance().init();
}


/* Kicks off/is the the gameloop */
void GameManager::play()
{
	bool running = true;
	int direction = 2;

	// Load bitmaps
	SDLBmp background("Assets/gfx/sdl2.bmp");
	SDLBmp player("Assets/gfx/sdl_bro.bmp");

	// Calculate render frames per second (second / frames) (60)
	float render_fps = 1.f / 60.f;
	m_lastRender = render_fps; // set it to render immediately

	// Gameloop
	while (running)
	{
		// Update input and deltatime
		InputManager::Instance().Update();
		Timer::Instance().update();

		// Calculate displacement based on deltatime
		float displacement = 150.F * Timer::Instance().deltaTime();

		/* Input Management */

		changeDirection(&direction);

		// Moves the snake based on direction, up = 0, right = 1 etc..
		switch (direction) {
		case 0: 
			player.y -= displacement;
			break;
		case 1: 
			player.x += displacement;
			break;
		case 2: 
			player.y += displacement;
			break;
		case 3: 
			player.x -= displacement;
		}

		running = !checkBorderCollision(&player, m_gameInfo);

		// Exit on [Esc], or window close (user X-ed out the window)
		if (InputManager::Instance().hasExit() || InputManager::Instance().KeyDown(SDL_SCANCODE_ESCAPE))
		{
			running = false;
		}

		// Update time since last render
		m_lastRender += Timer::Instance().deltaTime();

		// Check if it's time to render
		if (m_lastRender >= render_fps)
		{
			// Add bitmaps to renderer
			background.draw();
			player.draw();

			// Render window
			SDLManager::Instance().renderWindow(m_window);
			m_lastRender = 0.f;
		}

		// Sleep to prevent CPU exthaustion (1ms == 1000 frames per second)
		SDL_Delay(1);
	}
}

void GameManager::changeDirection(int *direction) {
	// Key up
	if ((InputManager::Instance().KeyDown(SDL_SCANCODE_UP) || InputManager::Instance().KeyStillDown(SDL_SCANCODE_UP))
		&& *direction != 2) {
		*direction = 0;
	}

	// Right key
	if ((InputManager::Instance().KeyDown(SDL_SCANCODE_RIGHT) || InputManager::Instance().KeyStillDown(SDL_SCANCODE_RIGHT))
		&& *direction != 3) {
		*direction = 1;
	}

	// Key down
	if ((InputManager::Instance().KeyDown(SDL_SCANCODE_DOWN) || InputManager::Instance().KeyStillDown(SDL_SCANCODE_DOWN))
		&& *direction != 0) {
		*direction = 2;
	}

	// Left key
	if ((InputManager::Instance().KeyDown(SDL_SCANCODE_LEFT) || InputManager::Instance().KeyStillDown(SDL_SCANCODE_LEFT))
		&& *direction != 1) {
		*direction = 3;
	}
}

bool GameManager::checkBorderCollision(SDLBmp* player, GameInfo* gameInfo) {
	float playerCenterX = player->x + player->getWidth() / 2;
	float playerCenterY = player->y + player->getHeight() / 2;

	if (playerCenterX + player->getWidth()/2 > gameInfo->getWindowX()) {
		return true;
	}

	if (playerCenterX - player->getWidth() / 2 < 0) {
		return true;
	}

	if (playerCenterY + player->getHeight() / 2 > gameInfo->getWindowY()) {
		return true;
	}

	if (playerCenterY - player->getHeight() / 2 < 0) {
		return true;
	}

	return false;
}
