#include "Bullet3.h"


Bullet3::Bullet3(std::shared_ptr<Models>& model, std::shared_ptr<Shaders>& shader, std::shared_ptr<Texture>& texture)
	:Sprite2D(model, shader, texture)
{
	m_speed = 500.0;
	m_active = true;
	m_type = BULLET_TYPE3::None;
	m_SizeCollider = 10;
	m_Damage = 5;
}

Bullet3::~Bullet3()
{
}

void Bullet3::Update(GLfloat deltatime)
{
	if (!m_active)
		return;
	Vector2 pos = Get2DPosition();
	pos.y = pos.y - m_speed * deltatime;
	pos.x = pos.x + 200 * deltatime;
	Set2DPosition(pos);

	if (pos.y <= 0 || pos.y > Application::screenHeight)
		m_active = false;
}

bool Bullet3::IsActive()
{
	return m_active;
}

void Bullet3::SetActive(bool status)
{
	m_active = status;
}

void Bullet3::SetSpeed(float speed)
{
	m_speed = speed;
}

void Bullet3::SetType(BULLET_TYPE3 type)
{
	m_type = type;
}

BULLET_TYPE3 Bullet3::GetType()
{
	return m_type;
}

void Bullet3::SetColliderSize(float size)
{
	m_SizeCollider = size;
}
float Bullet3::GetColliderSize()
{
	return m_SizeCollider;
}

void Bullet3::SetDamage(float damage)
{
	m_Damage = damage;
}

float Bullet3::GetDamage()
{
	return m_Damage;
}

