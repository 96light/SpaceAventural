#pragma once

#include "Sprite2D.h"
#include <Bullet.h>

class Enermy : public Sprite2D
{
public:
	Enermy(std::shared_ptr<Models>& model, std::shared_ptr<Shaders>& shader, std::shared_ptr<Texture>& texture);
	~Enermy();
	bool		IsActive();
	void		SetActive(bool status);

	void		Update(float deltaTime) override;

	bool		CanShoot();
	void		Shoot(std::vector<std::shared_ptr<Bullet>>& listBullet);
	void		CheckCollider(std::vector<std::shared_ptr<Bullet>>& listBullet);

	void		SetColliderSize(float size);
	float		GetColliderSize();

	void		SetDamage(float damage);
	float		GetDamage();

	void		Explosive();
	bool		IsExplosive();

private:
	int		m_Heal;
	bool	m_active;
	bool	m_Explosive;
	float	m_speed;
	float	m_MaxSpeed;
	float	m_MaxCooldown;
	float	m_Cooldown;
	float	m_Damage;
	float	m_SizeCollider;
	int sfx;
	float distance(Vector2 pos, Vector2 target);

};
