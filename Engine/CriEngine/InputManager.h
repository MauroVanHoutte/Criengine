#pragma once
#include <windows.h>
#include <XInput.h>
#include "Singleton.h"
#include "Command.h"
#include <map>
#include <SDL.h>
#include <vector>

namespace cri
{
	enum class ControllerButton : WORD
	{
		DPadUp = 0x0001,
		DPadDown = 0x0002,
		DPadLeft = 0x0004,
		DPadRight = 0x0008,
		Start = 0x0010,
		Back = 0x0020,
		LeftThumb = 0x0040,
		RightThumb = 0x0080,
		LeftShoulder = 0x0100,
		RightShoulder = 0x0200,
		ButtonA = 0x1000,
		ButtonB = 0x2000,
		ButtonX = 0x4000,
		ButtonY = 0x8000,
	};

	enum class JoystickDirection
	{
		Left,
		UpLeft,
		Up,
		UpRight,
		Right,
		DownRight,
		Down,
		DownLeft,
	};

	enum class Joystick
	{
		Left,
		Right
	};

	enum class ButtonState
	{
		OnPressed,
		OnRelease,
		Down
	};

	struct ControllerJoystickCommandInfo
	{
		int Scene;
		unsigned ControllerId;
		short Deadzone;
		Joystick Joystick;
		JoystickDirection Direction;
		Command* Command;
	};

	struct ControllerButtonCommandInfo
	{
		int Scene;
		unsigned ControllerId;
		ButtonState ButtonState;
		ControllerButton Button;
		Command* Command;
	};

	struct KeyboardCommandInfo
	{
		int Scene;
		ButtonState ButtonState;
		SDL_Scancode Button;
		Command* Command;
	};


	class InputManager final : public Singleton<InputManager>
	{
	public:
		InputManager();
		~InputManager();
		void ProcessInput();
		void AddControllerButtonCommand(unsigned controllerId, int scene, ButtonState buttonState, ControllerButton button, Command* command);
		void AddControllerJoystickCommand(unsigned controllerId, int scene, short deadzone, Joystick joystick, JoystickDirection joystickDirection, Command* command);
		void AddKeyboardCommand(int scene, ButtonState buttonState, SDL_Scancode button, Command* command);

	private:
		int m_NrControllers{ 4 };
		std::vector<ControllerButtonCommandInfo> m_ControllerButtonCommands;
		std::vector<ControllerJoystickCommandInfo> m_ControllerJoystickCommands;
		std::vector<KeyboardCommandInfo> m_KeyboardCommands;
		std::vector<XINPUT_STATE> m_ControllerStatesPreviousFrame;
		std::vector<Uint8> m_KeyboardSatePreviousFrame;
	};

}
