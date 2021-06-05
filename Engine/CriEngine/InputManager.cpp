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
}

void cri::InputManager::ProcessInput()
{
	XINPUT_STATE controllerState;
	auto keyboardState = SDL_GetKeyboardState(nullptr);

	int currentScene = cri::SceneManager::GetInstance().GetCurrentSceneIdx();


	for (size_t i = 0; i < m_KeyboardCommands.size(); i++)
	{
		if (m_KeyboardCommands[i].Scene != currentScene)
		{
			continue;
		}
		switch (m_KeyboardCommands[i].ButtonState)
		{
		case ButtonState::Down:
			if (keyboardState[m_KeyboardCommands[i].Button])
			{
				m_KeyboardCommands[i].pCommand->Execute();
			}
			break;

		case ButtonState::OnPressed:
			if (keyboardState[m_KeyboardCommands[i].Button] && !m_KeyboardSatePreviousFrame[m_KeyboardCommands[i].Button])
			{
				m_KeyboardCommands[i].pCommand->Execute();
			}
			break;

		case ButtonState::OnRelease:
			if (!keyboardState[m_KeyboardCommands[i].Button] && m_KeyboardSatePreviousFrame[m_KeyboardCommands[i].Button])
			{
				m_KeyboardCommands[i].pCommand->Execute();
			}
			break;
		}
	}
	
	for (int i = 0; i < m_NrControllers; i++)
	{
		ZeroMemory(&controllerState, sizeof(XINPUT_STATE));
		XInputGetState(i, &controllerState);


		for (size_t j = 0; j < m_ControllerButtonCommands.size(); j++)
		{
			if (m_ControllerButtonCommands[j].Scene != currentScene)
			{
				continue;
			}
			if (int(m_ControllerButtonCommands[j].ControllerId) == i)
			{
				switch (m_ControllerButtonCommands[j].ButtonState)
				{
				case ButtonState::Down:
					if (controllerState.Gamepad.wButtons & WORD(m_ControllerButtonCommands[j].Button))
					{
						m_ControllerButtonCommands[j].pCommand->Execute();
					}
					break;

				case ButtonState::OnPressed:
					if (controllerState.Gamepad.wButtons & WORD(m_ControllerButtonCommands[j].Button) && !(m_ControllerStatesPreviousFrame[i].Gamepad.wButtons & WORD(m_ControllerButtonCommands[j].Button)))
					{
						m_ControllerButtonCommands[j].pCommand->Execute();
					}
					break;

				case ButtonState::OnRelease:
					if (m_ControllerStatesPreviousFrame[i].Gamepad.wButtons & WORD(m_ControllerButtonCommands[j].Button) && !(controllerState.Gamepad.wButtons & WORD(m_ControllerButtonCommands[j].Button)))
					{
						m_ControllerButtonCommands[j].pCommand->Execute();
					}
					break;
				}
			}
		}

		for (size_t j = 0; j < m_ControllerJoystickCommands.size(); j++)
		{
			if (m_ControllerJoystickCommands[j].Scene != currentScene)
			{
				continue;
			}
			if (int(m_ControllerJoystickCommands[j].ControllerId) == i)
			{
				switch (m_ControllerJoystickCommands[j].Direction)
				{
				case JoystickDirection::Left:
					if (m_ControllerJoystickCommands[j].Joystick == Joystick::Left)
					{
						if (controllerState.Gamepad.sThumbLX < -m_ControllerJoystickCommands[j].Deadzone)
							m_ControllerJoystickCommands[j].pCommand->Execute();
					}
					else
					{
						if (controllerState.Gamepad.sThumbRX < -m_ControllerJoystickCommands[j].Deadzone)
							m_ControllerJoystickCommands[j].pCommand->Execute();
					}
					break;
				case JoystickDirection::UpLeft:
					if (m_ControllerJoystickCommands[j].Joystick == Joystick::Left)
					{
						if (controllerState.Gamepad.sThumbLX < -m_ControllerJoystickCommands[j].Deadzone && controllerState.Gamepad.sThumbLY > m_ControllerJoystickCommands[j].Deadzone)
							m_ControllerJoystickCommands[j].pCommand->Execute();
					}
					else
					{
						if (controllerState.Gamepad.sThumbRX < -m_ControllerJoystickCommands[j].Deadzone && controllerState.Gamepad.sThumbRY > m_ControllerJoystickCommands[j].Deadzone)
							m_ControllerJoystickCommands[j].pCommand->Execute();
					}
					break;
				case JoystickDirection::Up:
					if (m_ControllerJoystickCommands[j].Joystick == Joystick::Left)
					{
						if (controllerState.Gamepad.sThumbLY > m_ControllerJoystickCommands[j].Deadzone)
							m_ControllerJoystickCommands[j].pCommand->Execute();
					}
					else
					{
						if (controllerState.Gamepad.sThumbRY > m_ControllerJoystickCommands[j].Deadzone)
							m_ControllerJoystickCommands[j].pCommand->Execute();
					}
					break;
				case JoystickDirection::UpRight:
					if (m_ControllerJoystickCommands[j].Joystick == Joystick::Left)
					{
						if (controllerState.Gamepad.sThumbLX > m_ControllerJoystickCommands[j].Deadzone && controllerState.Gamepad.sThumbLY > m_ControllerJoystickCommands[j].Deadzone)
							m_ControllerJoystickCommands[j].pCommand->Execute();
					}
					else
					{
						if (controllerState.Gamepad.sThumbRX > m_ControllerJoystickCommands[j].Deadzone && controllerState.Gamepad.sThumbRY > m_ControllerJoystickCommands[j].Deadzone)
							m_ControllerJoystickCommands[j].pCommand->Execute();
					}
					break;
				case JoystickDirection::Right:
					if (m_ControllerJoystickCommands[j].Joystick == Joystick::Left)
					{
						if (controllerState.Gamepad.sThumbLX > m_ControllerJoystickCommands[j].Deadzone)
							m_ControllerJoystickCommands[j].pCommand->Execute();
					}
					else
					{
						if (controllerState.Gamepad.sThumbRX > m_ControllerJoystickCommands[j].Deadzone)
							m_ControllerJoystickCommands[j].pCommand->Execute();
					}
					break;
				case JoystickDirection::DownRight:
					if (m_ControllerJoystickCommands[j].Joystick == Joystick::Left)
					{
						if (controllerState.Gamepad.sThumbLX > m_ControllerJoystickCommands[j].Deadzone && controllerState.Gamepad.sThumbLY < -m_ControllerJoystickCommands[j].Deadzone)
							m_ControllerJoystickCommands[j].pCommand->Execute();
					}
					else
					{
						if (controllerState.Gamepad.sThumbRX > m_ControllerJoystickCommands[j].Deadzone && controllerState.Gamepad.sThumbRY < -m_ControllerJoystickCommands[j].Deadzone)
							m_ControllerJoystickCommands[j].pCommand->Execute();
					}
					break;
				case JoystickDirection::Down:
					if (m_ControllerJoystickCommands[j].Joystick == Joystick::Left)
					{
						if (controllerState.Gamepad.sThumbLY < -m_ControllerJoystickCommands[j].Deadzone)
							m_ControllerJoystickCommands[j].pCommand->Execute();
					}
					else
					{
						if (controllerState.Gamepad.sThumbRY < -m_ControllerJoystickCommands[j].Deadzone)
							m_ControllerJoystickCommands[j].pCommand->Execute();
					}
					break;
				case JoystickDirection::DownLeft:
					if (m_ControllerJoystickCommands[j].Joystick == Joystick::Left)
					{
						if (controllerState.Gamepad.sThumbLX < -m_ControllerJoystickCommands[j].Deadzone && controllerState.Gamepad.sThumbLY < -m_ControllerJoystickCommands[j].Deadzone)
							m_ControllerJoystickCommands[j].pCommand->Execute();
					}
					else
					{
						if (controllerState.Gamepad.sThumbRX < -m_ControllerJoystickCommands[j].Deadzone && controllerState.Gamepad.sThumbRY < -m_ControllerJoystickCommands[j].Deadzone)
							m_ControllerJoystickCommands[j].pCommand->Execute();
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

void cri::InputManager::AddKeyboardCommand(int scene, ButtonState buttonState, SDL_Scancode button, std::shared_ptr<Command> command)
{
	cri::KeyboardCommandInfo commandInfo;
	commandInfo.Scene = scene;
	commandInfo.ButtonState = buttonState;
	commandInfo.Button = button;
	commandInfo.pCommand = command;
	
	m_KeyboardCommands.push_back(commandInfo);
}

void cri::InputManager::AddControllerButtonCommand(unsigned controllerId, int scene, cri::ButtonState buttonState, cri::ControllerButton button, std::shared_ptr<Command> command)
{
	cri::ControllerButtonCommandInfo commandInfo;
	commandInfo.ControllerId = controllerId;
	commandInfo.Scene = scene;
	commandInfo.ButtonState = buttonState;
	commandInfo.Button = button;
	commandInfo.pCommand = command;

	m_ControllerButtonCommands.push_back(commandInfo);
}

void cri::InputManager::AddControllerJoystickCommand(unsigned controllerId, int scene, short deadzone, Joystick joystick, JoystickDirection joystickDirection, std::shared_ptr<Command> command)
{
	cri::ControllerJoystickCommandInfo commandInfo;
	commandInfo.ControllerId = controllerId;
	commandInfo.Scene = scene;
	commandInfo.Deadzone = deadzone;
	commandInfo.Joystick = joystick;
	commandInfo.Direction = joystickDirection;
	commandInfo.pCommand = command;

	m_ControllerJoystickCommands.push_back(commandInfo);
}
