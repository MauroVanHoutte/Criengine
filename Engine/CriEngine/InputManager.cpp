#include "InputManager.h"
#include <SDL.h>
#include "SceneManager.h"

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
	for (auto it = m_ControllerCommands.begin(); it != m_ControllerCommands.end(); it++)
	{
		
		delete it->Command;
	}
	for (auto it = m_KeyboardCommands.begin(); it != m_KeyboardCommands.end(); it++)
	{
		delete it->Command;
	}
}

void cri::InputManager::ProcessInput()
{
	XINPUT_STATE controllerState;
	auto keyboardState = SDL_GetKeyboardState(nullptr);

	int currentScene = cri::SceneManager::GetInstance().GetCurrentSceneIdx();


	for (auto it = m_KeyboardCommands.begin(); it != m_KeyboardCommands.end(); it++)
	{
		if (it->Scene != currentScene)
		{
			continue;
		}
		switch (it->ButtonState)
		{
		case ButtonState::Down:
			if (keyboardState[it->Button])
			{
				it->Command->Execute();
			}
			break;

		case ButtonState::OnPressed:
			if (keyboardState[it->Button] && !m_KeyboardSatePreviousFrame[it->Button])
			{
				it->Command->Execute();
			}
			break;

		case ButtonState::OnRelease:
			if (!keyboardState[it->Button] && m_KeyboardSatePreviousFrame[it->Button])
			{
				it->Command->Execute();
			}
			break;
		}
	}
	
	for (int i = 0; i < m_NrControllers; i++)
	{
		ZeroMemory(&controllerState, sizeof(XINPUT_STATE));
		XInputGetState(i, &controllerState);


		for (auto it = m_ControllerCommands.begin(); it != m_ControllerCommands.end(); it++)
		{
			if (it->Scene != currentScene)
			{
				continue;
			}
			if (int(it->ControllerId) == i)
			{
				switch (it->ButtonState)
				{
				case ButtonState::Down:
					if (controllerState.Gamepad.wButtons & WORD(it->Button))
					{
						it->Command->Execute();
					}
					break;

				case ButtonState::OnPressed:
					if (controllerState.Gamepad.wButtons & WORD(it->Button) && !(m_ControllerStatesPreviousFrame[i].Gamepad.wButtons & WORD(it->Button)))
					{
						it->Command->Execute();
					}
					break;

				case ButtonState::OnRelease:
					if (m_ControllerStatesPreviousFrame[i].Gamepad.wButtons & WORD(it->Button) && !(controllerState.Gamepad.wButtons & WORD(it->Button)))
					{
						it->Command->Execute();
					}
					break;
				}
			}
		}

		m_ControllerStatesPreviousFrame[i] = std::move(controllerState);
	}
	m_KeyboardSatePreviousFrame.assign(keyboardState, keyboardState + SDL_NUM_SCANCODES);
}

void cri::InputManager::AddKeyboardCommand(int scene, ButtonState buttonState, SDL_Scancode button, Command* command)
{
	cri::KeyboardCommandInfo commandInfo;
	commandInfo.Scene = scene;
	commandInfo.ButtonState = buttonState;
	commandInfo.Button = button;
	commandInfo.Command = command;
	
	m_KeyboardCommands.push_back(commandInfo);
}

void cri::InputManager::AddControllerCommand(unsigned controllerId, int scene, cri::ButtonState buttonState, cri::ControllerButton button, Command* command)
{
	cri::ControllerCommandInfo commandInfo;
	commandInfo.ControllerId = controllerId;
	commandInfo.Scene = scene;
	commandInfo.ButtonState = buttonState;
	commandInfo.Button = button;
	commandInfo.Command = command;

	m_ControllerCommands.push_back(commandInfo);
}