#include "InputManager.h"
#include <SDL.h>

cri::InputManager::InputManager()
{
	for (int i = 0; i < m_NrControllers; i++)
	{
		m_ControllerStatesPreviousFrame.push_back(XINPUT_STATE());
	}

	m_KeyboardSatePreviousFrame.resize(SDL_NUM_SCANCODES);
}

cri::InputManager::~InputManager()
{
	for (auto it = m_ControllerCommandsMap.begin(); it != m_ControllerCommandsMap.end(); it++)
	{
		if (!it->second->m_Deleted)
		{
			delete it->second;
			it->second->m_Deleted = true;
		}
	}
	for (auto it = m_KeyboardCommandsMap.begin(); it != m_KeyboardCommandsMap.end(); it++)
	{
		if (!it->second->m_Deleted)
		{
			delete it->second;
			it->second->m_Deleted = true;
		}
	}
}

void cri::InputManager::ProcessInput()
{
	XINPUT_STATE controllerState;
	auto keyboardState = SDL_GetKeyboardState(nullptr);


	for (auto it = m_KeyboardCommandsMap.begin(); it != m_KeyboardCommandsMap.end(); it++)
	{
		switch (it->first.first)
		{
		case ButtonState::Down:
			if (keyboardState[it->first.second])
			{
				it->second->Execute();
			}
			break;

		case ButtonState::OnPressed:
			if (keyboardState[it->first.second] && !m_KeyboardSatePreviousFrame[it->first.second])
			{
				it->second->Execute();
			}
			break;

		case ButtonState::OnRelease:
			if (!keyboardState[it->first.second] && m_KeyboardSatePreviousFrame[it->first.second])
			{
				it->second->Execute();
			}
			break;
		}
	}
	
	for (int i = 0; i < m_NrControllers; i++)
	{
		ZeroMemory(&controllerState, sizeof(XINPUT_STATE));
		XInputGetState(i, &controllerState);


		for (auto it = m_ControllerCommandsMap.begin(); it != m_ControllerCommandsMap.end(); it++)
		{
			if (int(it->first.first) == i)
			{
				switch (it->first.second.first)
				{
				case ButtonState::Down:
					if (controllerState.Gamepad.wButtons & WORD(it->first.second.second))
					{
						it->second->Execute();
					}
					break;

				case ButtonState::OnPressed:
					if (controllerState.Gamepad.wButtons & WORD(it->first.second.second) && !(m_ControllerStatesPreviousFrame[i].Gamepad.wButtons & WORD(it->first.second.second)))
					{
						it->second->Execute();
					}
					break;

				case ButtonState::OnRelease:
					if (m_ControllerStatesPreviousFrame[i].Gamepad.wButtons & WORD(it->first.second.second) && !(controllerState.Gamepad.wButtons & WORD(it->first.second.second)))
					{
						it->second->Execute();
					}
					break;
				}
			}
		}

		m_ControllerStatesPreviousFrame[i] = std::move(controllerState);
	}
	m_KeyboardSatePreviousFrame.assign(keyboardState, keyboardState + SDL_NUM_SCANCODES);
}

void cri::InputManager::AddKeyboardCommand(ButtonState buttonState, int button, Command* command)
{
	std::pair<std::pair<ButtonState, int>, Command*> pair;
	pair.first.first = buttonState;
	pair.first.second = button;
	pair.second = command;
	m_KeyboardCommandsMap.insert(pair);
}

void cri::InputManager::AddControllerCommand(unsigned controllerId, cri::ButtonState buttonState, cri::ControllerButton button, Command* command)
{
	std::pair<std::pair<unsigned, std::pair<cri::ButtonState, cri::ControllerButton>>, Command*> pair;
	pair.first.first = controllerId;
	pair.first.second.first = buttonState;
	pair.first.second.second = button;
	pair.second = command;
	m_ControllerCommandsMap.insert(pair);
}