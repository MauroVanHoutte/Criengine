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
	enum class ButtonState
	{
		OnPressed,
		OnRelease,
		Down
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		InputManager();
		~InputManager();
		void ProcessInput();
		void AddControllerCommand(unsigned controllerId, ButtonState buttonState, ControllerButton button, Command* command);
		void AddKeyboardCommand( ButtonState buttonState, int button, Command* command);

	private:
		int m_NrControllers{ 4 };
		std::multimap<std::pair<unsigned, std::pair<ButtonState, ControllerButton>>, Command*> m_ControllerCommandsMap;
		std::multimap<std::pair<ButtonState, int>, Command*> m_KeyboardCommandsMap;
		std::vector<XINPUT_STATE> m_ControllerStatesPreviousFrame;
		std::vector<Uint8> m_KeyboardSatePreviousFrame;
	};

}
