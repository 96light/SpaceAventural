#include "Bullet2.h"


Bullet2::Bullet2(std::shared_ptr<Models>& model, std::shared_ptr<Shaders>& shader, std::shared_ptr<Texture>& texture)
	:Sprite2D(model, shader, texture)
{
	m_speed = 500.0;
	m_active = true;
	m_type = BULLET_TYPE2::None;
	m_SizeCollider = 10;
	m_Damage = 5;
}

Bullet2::~Bullet2()
{
}

void Bullet2::Update(GLfloat deltatime)
{
	if (!m_active)
		return;
	Vector2 pos = Get2DPosition();
	pos.y = pos.y - m_speed * deltatime;
	pos.x = pos.x - 200 * deltatime;
	Set2DPosition(pos);

	if (pos.y <= 0 || pos.y > Application::screenHeight)
		m_active = false;
}

bool Bullet2::IsActive()
{
	return m_active;
}

void Bullet2::SetActive(bool status)
{
	m_active = status;
}

void Bullet2::SetSpeed(float speed)
{
	m_speed = speed;
}

void Bullet2::SetType(BULLET_TYPE2 type)
{
	m_type = type;
}

BULLET_TYPE2 Bullet2::GetType()
{
	return m_type;
}

void Bullet2::SetColliderSize(float size)
{
	m_SizeCollider = size;
}
float Bullet2::GetColliderSize()
{
	return m_SizeCollider;
}

void Bullet2::SetDamage(float damage)
{
	m_Damage = damage;
}

float Bullet2::GetDamage()
{
	return m_Damage;
}

