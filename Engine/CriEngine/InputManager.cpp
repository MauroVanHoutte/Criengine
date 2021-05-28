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
	for (auto it = m_ControllerButtonCommands.begin(); it != m_ControllerButtonCommands.end(); it++)
	{
		delete it->Command;
	}
	for (auto it = m_KeyboardCommands.begin(); it != m_KeyboardCommands.end(); it++)
	{
		delete it->Command;
	}
	for (auto it = m_ControllerJoystickCommands.begin(); it != m_ControllerJoystickCommands.end(); it++)
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


		for (auto it = m_ControllerButtonCommands.begin(); it != m_ControllerButtonCommands.end(); it++)
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

		for (auto it = m_ControllerJoystickCommands.begin(); it != m_ControllerJoystickCommands.end(); it++)
		{
			if (it->Scene != currentScene)
			{
				continue;
			}
			if (int(it->ControllerId) == i)
			{
				switch (it->Direction)
				{
				case JoystickDirection::Left:
					if (it->Joystick == Joystick::Left)
					{
						if (controllerState.Gamepad.sThumbLX < -it->Deadzone)
							it->Command->Execute();
					}
					else
					{
						if (controllerState.Gamepad.sThumbRX < -it->Deadzone)
							it->Command->Execute();
					}
					break;
				case JoystickDirection::UpLeft:
					if (it->Joystick == Joystick::Left)
					{
						if (controllerState.Gamepad.sThumbLX < -it->Deadzone && controllerState.Gamepad.sThumbLY > it->Deadzone)
							it->Command->Execute();
					}
					else
					{
						if (controllerState.Gamepad.sThumbRX < -it->Deadzone && controllerState.Gamepad.sThumbRY > it->Deadzone)
							it->Command->Execute();
					}
					break;
				case JoystickDirection::Up:
					if (it->Joystick == Joystick::Left)
					{
						if (controllerState.Gamepad.sThumbLY > it->Deadzone)
							it->Command->Execute();
					}
					else
					{
						if (controllerState.Gamepad.sThumbRY > it->Deadzone)
							it->Command->Execute();
					}
					break;
				case JoystickDirection::UpRight:
					if (it->Joystick == Joystick::Left)
					{
						if (controllerState.Gamepad.sThumbLX > it->Deadzone && controllerState.Gamepad.sThumbLY > it->Deadzone)
							it->Command->Execute();
					}
					else
					{
						if (controllerState.Gamepad.sThumbRX > it->Deadzone && controllerState.Gamepad.sThumbRY > it->Deadzone)
							it->Command->Execute();
					}
					break;
				case JoystickDirection::Right:
					if (it->Joystick == Joystick::Left)
					{
						if (controllerState.Gamepad.sThumbLX > it->Deadzone)
							it->Command->Execute();
					}
					else
					{
						if (controllerState.Gamepad.sThumbRX > it->Deadzone)
							it->Command->Execute();
					}
					break;
				case JoystickDirection::DownRight:
					if (it->Joystick == Joystick::Left)
					{
						if (controllerState.Gamepad.sThumbLX > it->Deadzone && controllerState.Gamepad.sThumbLY < -it->Deadzone)
							it->Command->Execute();
					}
					else
					{
						if (controllerState.Gamepad.sThumbRX > it->Deadzone && controllerState.Gamepad.sThumbRY < -it->Deadzone)
							it->Command->Execute();
					}
					break;
				case JoystickDirection::Down:
					if (it->Joystick == Joystick::Left)
					{
						if (controllerState.Gamepad.sThumbLY < -it->Deadzone)
							it->Command->Execute();
					}
					else
					{
						if (controllerState.Gamepad.sThumbRY < -it->Deadzone)
							it->Command->Execute();
					}
					break;
				case JoystickDirection::DownLeft:
					if (it->Joystick == Joystick::Left)
					{
						if (controllerState.Gamepad.sThumbLX < -it->Deadzone && controllerState.Gamepad.sThumbLY < -it->Deadzone)
							it->Command->Execute();
					}
					else
					{
						if (controllerState.Gamepad.sThumbRX < -it->Deadzone && controllerState.Gamepad.sThumbRY < -it->Deadzone)
							it->Command->Execute();
					}
					break;
				default:
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

void cri::InputManager::AddControllerButtonCommand(unsigned controllerId, int scene, cri::ButtonState buttonState, cri::ControllerButton button, Command* command)
{
	cri::ControllerButtonCommandInfo commandInfo;
	commandInfo.ControllerId = controllerId;
	commandInfo.Scene = scene;
	commandInfo.ButtonState = buttonState;
	commandInfo.Button = button;
	commandInfo.Command = command;

	m_ControllerButtonCommands.push_back(commandInfo);
}

void cri::InputManager::AddControllerJoystickCommand(unsigned controllerId, int scene, short deadzone, Joystick joystick, JoystickDirection joystickDirection, Command* command)
{
	cri::ControllerJoystickCommandInfo commandInfo;
	commandInfo.ControllerId = controllerId;
	commandInfo.Scene = scene;
	commandInfo.Deadzone = deadzone;
	commandInfo.Joystick = joystick;
	commandInfo.Direction = joystickDirection;
	commandInfo.Command = command;

	m_ControllerJoystickCommands.push_back(commandInfo);
}
