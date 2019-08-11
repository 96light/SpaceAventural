#include "ExplosiveEffect.h"


ExplosiveEffect::ExplosiveEffect(std::shared_ptr<Models>& model, std::shared_ptr<Shaders>& shader, std::shared_ptr<Texture>& texture, Vector2& pictureSize, Vector2& spriteSize, int start, int end, float lengthTime)
	:SpriteSheet(model, shader, texture, pictureSize, spriteSize, start, end, lengthTime)
{
	m_active = true;
}

ExplosiveEffect::~ExplosiveEffect()
{
}

void ExplosiveEffect::Update(GLfloat deltatime)
{
	if (!m_active)
		return;

	SpriteSheet::Update(deltatime);
	if (SpriteSheet::IsDone())
	{
		m_active = false;
	}
}

bool ExplosiveEffect::IsActive()
{
	return m_active;
}

void ExplosiveEffect::SetActive(bool status)
{
	m_active = status;
	if (m_active)
	{
		SpriteSheet::StartAnimation();
	}
}

