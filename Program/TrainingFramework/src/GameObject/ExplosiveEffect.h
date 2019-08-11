#pragma once
#include "SpriteSheet.h"
#include "Application.h"


class ExplosiveEffect : public SpriteSheet
{
public:
	ExplosiveEffect(std::shared_ptr<Models>& model, std::shared_ptr<Shaders>& shader, std::shared_ptr<Texture>& texture, Vector2& pictureSize, Vector2& spriteSize, int start, int end, float lengthTime = 1.0);
	~ExplosiveEffect();

	void		Update(GLfloat deltatime) override;

	bool		IsActive();
	void		SetActive(bool status);

private:
	bool	m_active;
};
