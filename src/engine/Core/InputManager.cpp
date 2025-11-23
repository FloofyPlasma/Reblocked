#include "Core/InputManager.hpp"

namespace Reblocked::Engine::Core
{
void InputManager::setupDefaultBindings()
{
	m_keyBindings[GameAction::MoveLeft] = SDLK_LEFT;
	m_keyBindings[GameAction::MoveRight] = SDLK_RIGHT;
	m_keyBindings[GameAction::MoveForward] = SDLK_UP;
	m_keyBindings[GameAction::MoveBack] = SDLK_DOWN;

	m_keyBindings[GameAction::RotateX] = SDLK_Q;
	m_keyBindings[GameAction::RotateY] = SDLK_W;
	m_keyBindings[GameAction::RotateZ] = SDLK_E;

	m_keyBindings[GameAction::Drop] = SDLK_SPACE;

	m_keyBindings[GameAction::Pause] = SDLK_P;

	m_keyBindings[GameAction::Quit] = SDLK_ESCAPE;
}

void InputManager::processEvents() { }

void InputManager::update()
{
	m_justPressed.clear();
	m_justReleased.clear();
}

bool InputManager::isActionPressed(GameAction action) const
{
	auto it = m_keyBindings.find(action);
	if (it == m_keyBindings.end())
	{
		return false;
	}

	auto stateIt = m_keyStates.find(it->second);
	return stateIt != m_keyStates.end() && stateIt->second;
}

bool InputManager::isActionJustPressed(GameAction action) const
{
	auto it = m_keyBindings.find(action);
	if (it == m_keyBindings.end())
	{
		return false;
	}

	return m_justPressed.contains(it->second);
}

bool InputManager::isActionJustReleased(GameAction action) const
{
	auto it = m_keyBindings.find(action);
	if (it == m_keyBindings.end())
	{
		return false;
	}

	return m_justReleased.contains(it->second);
}

void InputManager::setKeyBinding(GameAction action, SDL_Keycode key)
{
	m_keyBindings[action] = key;
}

void InputManager::onKeyDown(SDL_Keycode key)
{
	if (!m_keyStates[key])
	{
		m_justPressed.insert(key);
	}
	m_keyStates[key] = true;
}

void InputManager::onKeyUp(SDL_Keycode key)
{
	if (m_keyStates[key])
	{
		m_justReleased.insert(key);
	}
	m_keyStates[key] = false;
}
}
