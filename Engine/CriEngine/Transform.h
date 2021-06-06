#pragma once
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)

namespace cri
{
	class Transform final
	{
	public:
		const glm::vec2& GetPosition() const { return m_Position; }
		void SetPosition(float x, float y);
	private:
		glm::vec2 m_Position;
	};
}
