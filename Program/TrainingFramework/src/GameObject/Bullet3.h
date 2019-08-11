#pragma once
#include "Sprite2D.h"
#include "Application.h"

enum class BULLET_TYPE3
{
	None,
	Player,
	Enermy
};

class Bullet3 : public Sprite2D
{
public:
	Bullet3(std::shared_ptr<Models>& model, std::shared_ptr<Shaders>& shader, std::shared_ptr<Texture>& texture);
	~Bullet3();

	void		Update(GLfloat deltatime) override;
	void		SetSpeed(float speed);

	bool		IsActive();
	void		SetActive(bool status);

	void		SetType(BULLET_TYPE3 type);
	BULLET_TYPE3	GetType();

	void		SetColliderSize(float size);
	float		GetColliderSize();

	void		SetDamage(float damage);
	float		GetDamage();

private:
	BULLET_TYPE3 m_type;
	bool	m_active;
	float	m_speed;
	float	m_SizeCollider;
	float	m_Damage;
};
