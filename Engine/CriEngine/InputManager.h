#pragma once
#include <windows.h>
#include <XInput.h>
#include "Singleton.h"
#include "Command.h"
#include <map>
#include <SDL.h>
#include <vector>
#include <memory>

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
		None
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
		Down,
		None
	};

	struct ControllerJoystickCommandInfo
	{
		int Scene;
		unsigned ControllerId;
		short Deadzone;
		Joystick Joystick;
		JoystickDirection Direction;
		std::shared_ptr<Command> pCommand;
	};

	struct ControllerButtonCommandInfo
	{
		int Scene;
		unsigned ControllerId;
		ButtonState ButtonState;
		ControllerButton Button;
		std::shared_ptr<Command> pCommand;
	};

	struct KeyboardCommandInfo
	{
		int Scene;
		ButtonState ButtonState;
		SDL_Scancode Button;
		std::shared_ptr<Command> pCommand;
	};


	class InputManager final : public Singleton<InputManager>
	{
	public:
		InputManager();
		~InputManager();
		void ProcessInput();
		void AddControllerButtonCommand(unsigned controllerId, int scene, ButtonState buttonState, ControllerButton button, std::shared_ptr<Command> command);
		void AddControllerJoystickCommand(unsigned controllerId, int scene, short deadzone, Joystick joystick, JoystickDirection joystickDirection, std::shared_ptr<Command> command);
		void AddKeyboardCommand(int scene, ButtonState buttonState, SDL_Scancode button, std::shared_ptr<Command> command);

	private:
		int m_NrControllers{ 4 };
		std::vector<ControllerButtonCommandInfo> m_ControllerButtonCommands;
		std::vector<ControllerJoystickCommandInfo> m_ControllerJoystickCommands;
		std::vector<KeyboardCommandInfo> m_KeyboardCommands;
		std::vector<XINPUT_STATE> m_ControllerStatesPreviousFrame;
		std::vector<Uint8> m_KeyboardSatePreviousFrame;
	};

}
