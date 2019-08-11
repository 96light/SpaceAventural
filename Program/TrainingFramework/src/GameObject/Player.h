#pragma once
#include "Sprite2D.h"
#include "Bullet.h"
#include <Enermy.h>
#include"meteor.h"
#include<string>
#include"UFO.h"
#include "Bullet2.h"
#include "Bullet3.h"
class Player : public Sprite2D
{
	
public:
	Player(std::shared_ptr<Models>& model, std::shared_ptr<Shaders>& shader, std::shared_ptr<Texture>& texture);
	~Player();

	void MoveToPossition(Vector2 pos);
	void Update(GLfloat deltatime) override;

	bool CanShoot();
	void Shoot(std::vector<std::shared_ptr<Bullet>>& listBullet, int s);

	void CheckCollider(std::vector<std::shared_ptr<Bullet>>& listBullet, std::vector<std::shared_ptr<Bullet2>>& listBullet2, std::vector<std::shared_ptr<Bullet3>>& listBullet3, std::vector<std::shared_ptr<Enermy>> listEnermy);
	void CheckCollider2(std::vector<std::shared_ptr<Meteor>> listMeteor);
	void CheckCollider2(std::vector<std::shared_ptr<UFO>> listUFO);
	void		SetColliderSize(float size);
	float		GetColliderSize();
	int			GetHeal();
	bool		IsAlive();
private:
	Vector2 m_TargetPosition;
	int		m_Heal;
	bool	m_isAlive;
	float	m_speed;
	float	m_MaxSpeed;
	float	m_MaxCooldown;
	float	m_Cooldown;
	float	m_SizeCollider;
	
	int sfx;

	float distance(Vector2 pos, Vector2 target);
};
