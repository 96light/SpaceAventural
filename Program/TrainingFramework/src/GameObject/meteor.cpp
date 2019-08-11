#include "Meteor.h"
#include "GameManager/ResourceManagers.h"
#include <GameStates\GSPlay.h>

Meteor::Meteor(std::shared_ptr<Models>& model, std::shared_ptr<Shaders>& shader, std::shared_ptr<Texture>& texture)
	:Sprite2D(model, shader, texture)
{
	m_active = false;
	m_MaxCooldown = 0.3;
	m_Cooldown = 0.0;
	m_speed = 700;
	m_MaxSpeed = 700;
	m_Heal = 5;
	m_Damage = 30;
	m_Explosive = false;
	m_SizeCollider = 20;
}

Meteor::~Meteor()
{
}


void Meteor::Update(float deltaTime)
{
	if (!m_active)
		return;

	if (m_Heal <= 0 || m_Explosive)
	{
		m_active = false;
		GSPlay::m_score++;
		return;
	}

	if (m_Cooldown > 0)
	{
		m_Cooldown -= deltaTime;
	}

	Vector2 pos = Get2DPosition();
	pos.y = pos.y + m_speed * deltaTime;
	Set2DPosition(pos);

	if (pos.y > Application::screenHeight)
		m_active = false;
}

bool Meteor::CanShoot()
{
	return (m_Cooldown <= 0);
}

float Meteor::distance(Vector2 pos, Vector2 target)
{
	return sqrt((pos.x - target.x) * (pos.x - target.x) + (pos.y - target.y) * (pos.y - target.y));
}


bool Meteor::IsActive()
{
	return m_active;
}

void Meteor::SetActive(bool status)
{
	m_active = status;
	m_Explosive = false;
	m_Heal = 10;
}

void Meteor::SetDamage(float damage)
{
	m_Damage = damage;
}

float Meteor::GetDamage()
{
	return m_Damage;
}

void Meteor::Explosive()
{
	m_Explosive = true;
}


void Meteor::SetColliderSize(float size)
{
	m_SizeCollider = size;
}
float Meteor::GetColliderSize()
{
	return m_SizeCollider;
}