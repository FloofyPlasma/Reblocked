#pragma once

#include <unordered_map>
#include <unordered_set>

#include <SDL3/SDL.h>

namespace Reblocked
{
enum class GameAction
{
	MoveLeft,
	MoveRight,
	MoveForward,
	MoveBack,
	RotateX,
	RotateY,
	RotateZ,
	Drop,
	Pause,
	Quit
};

class InputManager
{
	public:
	InputManager() = default;

	void setupDefaultBindings();
	void processEvents();
	void update();

	bool isActionPressed(GameAction action) const;
	bool isActionJustPressed(GameAction action) const;
	bool isActionJustReleased(GameAction action) const;

	void setKeyBinding(GameAction action, SDL_Keycode key);

	void onKeyDown(SDL_Keycode key);
	void onKeyUp(SDL_Keycode key);

	private:
	std::unordered_map<GameAction, SDL_Keycode> m_keyBindings;
	std::unordered_map<SDL_Keycode, bool> m_keyStates;
	std::unordered_set<SDL_Keycode> m_justPressed;
	std::unordered_set<SDL_Keycode> m_justReleased;
};

}
