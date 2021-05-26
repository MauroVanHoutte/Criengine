#pragma once
#include <TextureComponent.h>

class SingleRowAnimationComponent : public TextureComponent
{
public:
	SingleRowAnimationComponent(cri::GameObject* owner, int nrAnimations, int framesPerAnim, std::shared_ptr<cri::Texture2D> sheet);

	void Render() const override;

	void NextFrame();
	void SetNextFrame(int frame);
	void SetAnimation(int nrAnimation);


private:
	int m_NrAnimations;
	int m_NrFramesPerAnim;
	int m_CurrentAnimation;
	int m_CurrentFrame;
};