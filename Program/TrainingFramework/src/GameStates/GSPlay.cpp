#include <sstream>
#include<iostream>
#include <iomanip>
#include <thread>
#include <fstream>
#include "GSPlay.h"
#include "Shaders.h"
#include "Texture.h"
#include "Models.h"
#include "Camera.h"
#include "Font.h"
#include "Text.h"
#include "Player.h"
#include "Enermy.h"
#include "Bullet.h"
#include "ExplosiveEffect.h"
#include "meteor.h"
#include"UFO.h"
#include"Bullet2.h"
using namespace std;
int GSPlay::m_score = 0;
GSPlay::GSPlay()
{
	m_SpawnCooldown = 0.1;
	m_SpawnCooldown2 = 1;
	m_SpawnCooldown2 = 0.3;
	m_score = 0;
	// m_sound = sound;
}


GSPlay::~GSPlay()
{

}


void GSPlay::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_play");

	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(Application::screenWidth / 2, Application::screenHeight / 2);
	m_BackGround->SetSize(Application::screenWidth, Application::screenHeight);




	texture = ResourceManagers::GetInstance()->GetTexture("player");
	m_Player = std::make_shared<Player >(model, shader, texture);
	m_Player->Set2DPosition(Application::screenWidth / 2, Application::screenHeight - 100);
	m_Player->MoveToPossition(Vector2(Application::screenWidth / 2, Application::screenHeight - 100));
	m_Player->SetSize(50, 50);
	texture = ResourceManagers::GetInstance()->GetTexture("dirt");


	//text game title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("arialbd");
	m_scoreText = std::make_shared< Text>(shader, font, "SCORE: ", TEXT_COLOR::RED, 1.0);
	m_scoreText->Set2DPosition(Vector2(5, 25));
	m_playerHealText = std::make_shared< Text>(shader, font, "HP: ", TEXT_COLOR::RED, 1.0);
	m_playerHealText->Set2DPosition(Vector2(5, 50));

	//init effect
	model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	texture = ResourceManagers::GetInstance()->GetTexture("explosive");
	shader = ResourceManagers::GetInstance()->GetShader("SpriteShader");
	std::shared_ptr<ExplosiveEffect> exp = std::make_shared<ExplosiveEffect>(model, shader, texture, Vector2(960, 768), Vector2(192, 192), 0, 19, 0.7);
	exp->SetSize(100, 100);
	exp->SetActive(false);
	m_listExplosiveEffect.push_back(exp);

	//init sound
	SoundManager::GetInstance()->AddSound("explosive");
	SoundManager::GetInstance()->AddSound("explosive_2");
	SoundManager::GetInstance()->AddSound("bground");

	SoundManager::GetInstance()->AddSound("fire");
	SoundManager::GetInstance()->AddSound("fire_enemy");
	ifstream FileIn;

	FileIn.open("config.txt", ios_base::in);

	if (FileIn.fail() == true)
	{
		cout << "\nFile cua ban khong ton tai";
	}
	int x;
	int y;
	FileIn >> x;
	FileIn >> y;
	sfx = x;
	sfx2 = y;
	//bgm = y;

	FileIn.close();
	if (sfx2 == 1) {
		SoundManager::GetInstance()->PlaySound("bground");
	}


}

void GSPlay::Exit()
{

}


void GSPlay::Pause()
{

}

void GSPlay::Resume()
{

}


void GSPlay::HandleEvents()
{

}

void GSPlay::HandleKeyEvents(int key, bool bIsPressed)
{
	if (key == 27)
	{
		SoundManager::GetInstance()->PauseSound("bground");
	}

}

void GSPlay::HandleMouseEvents(int x, int y)
{
	m_Player->MoveToPossition(Vector2(x, y));
}


void GSPlay::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	//SoundManager::GetInstance()->PauseSound("bground");
	if (m_Player->CanShoot())
		m_Player->Shoot(m_listBullet, sfx);
}

void GSPlay::Update(float deltaTime)
{

	if (m_SpawnCooldown > 0)
	{
		m_SpawnCooldown -= deltaTime;
	}
	if (m_SpawnCooldown <= 0)
	{
		CreateRandomEnermy();
		m_SpawnCooldown = 0.3;
	}

	if (m_SpawnCooldown2 > 0)
	{
		m_SpawnCooldown2 -= deltaTime;
	}
	if (m_SpawnCooldown2 <= 0)
	{
		CreateRandomMeteor();
		m_SpawnCooldown2 = 0.9;
	}

	if (m_SpawnCooldown3 > 0)
	{
		m_SpawnCooldown3 -= deltaTime;
	}
	if (m_SpawnCooldown3 <= 0)
	{
		CreateRandomUFO();
		m_SpawnCooldown3 = 100000;
	}
	//update player
	if (m_Player->IsAlive())
	{
		m_Player->Update(deltaTime);

		/*if (m_Player->CanShoot())
			m_Player->Shoot(m_listBullet);*/

		m_Player->CheckCollider(m_listBullet, m_listBullet2, m_listBullet3, m_listEnermy);
		m_Player->CheckCollider2(m_listMeteor);
	}

	else {
		SoundManager::GetInstance()->PauseSound("bground");
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Playagain);
	}
	//update enermies
	for (auto enermy : m_listEnermy)
	{
		if (enermy->IsActive())
		{
			if (enermy->IsExplosive())
			{
				enermy->SetActive(false);
				SpawnExplosive(enermy->Get2DPosition());
				continue;
			}
			enermy->Update(deltaTime);
			if (enermy->CanShoot())
				enermy->Shoot(m_listBullet);
			enermy->CheckCollider(m_listBullet);
		}
	}/*
	for (auto UFO : m_listEnermy2)
	{
		if (UFO->IsActive())
		{
			if (UFO->IsExplosive())
			{
				UFO->SetActive(false);
				SpawnExplosive(UFO->Get2DPosition());
				continue;
			}
			UFO->Update(deltaTime);
			if (UFO->CanShoot())
				UFO->Shoot(m_listBullet);
			UFO->CheckCollider(m_listBullet);
		}
	}
	*/
	for (auto exp : m_listExplosiveEffect)
	{
		if (exp->IsActive())
		{
			exp->Update(deltaTime);
		}
	}

	//update bullets
	for (auto bullet : m_listBullet)
	{
		if (bullet->IsActive())
			bullet->Update(deltaTime);
	}
	for (auto bullet : m_listBullet2)
	{
		if (bullet->IsActive())
			bullet->Update(deltaTime);
	}
	for (auto bullet : m_listBullet3)
	{
		if (bullet->IsActive())
			bullet->Update(deltaTime);
	}
	for (auto meteor : m_listMeteor)
	{
		if (meteor->IsActive())
		{
			meteor->Update(deltaTime);

		}
	}


	//hp = m_Player->GetHeal;
	if (m_score == 42)
	{
		m_SpawnCooldown = 10000000;
		m_SpawnCooldown2 = 10000000;
		for (auto UFO : m_listEnermy2)
		{
			if (UFO->IsActive())
			{
				if (UFO->IsExplosive())
				{

					UFO->SetActive(false);
					SpawnExplosive(UFO->Get2DPosition());
					continue;


				}

				UFO->Update(deltaTime);

				if (UFO->CanShoot()) {
					UFO->Shoot(m_listBullet);
					UFO->Shoot2(m_listBullet2);
					UFO->Shoot3(m_listBullet3);
				}
				UFO->CheckCollider(m_listBullet);
			}
			if (UFO->IsActive() == false)
			{
				SoundManager::GetInstance()->PauseSound("bground");
				GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Playagain1);

			}
		}
	}

	//update Score
	std::stringstream stream;
	stream << std::fixed << std::setprecision(0) << m_score;
	std::string score = "SCORE: " + stream.str();
	m_scoreText->setText(score);
	std::stringstream stream2;
	stream2 << std::fixed << std::setprecision(0) << m_Player->GetHeal();
	std::string heal = "HP: " + stream2.str();
	m_playerHealText->setText(heal);
}

void GSPlay::Draw()
{
	//ground
	m_BackGround->Draw();

	for (auto enermy : m_listEnermy)
		if (enermy->IsActive())
			enermy->Draw();
	if (m_score == 42) {
		for (auto enermy : m_listEnermy)
			if (enermy->IsActive())
				enermy->SetActive(0);
		for (auto UFO : m_listEnermy2)
			if (UFO->IsActive())
				UFO->Draw();
	}
	if (m_Player->IsAlive())
		m_Player->Draw();

	for (auto meteor : m_listMeteor)
		if (meteor->IsActive())
			meteor->Draw();

	for (auto bullet : m_listBullet)
		if (bullet->IsActive())
			bullet->Draw();

	for (auto bullet : m_listBullet2)
		if (bullet->IsActive())
			bullet->Draw();

	for (auto bullet : m_listBullet3)
		if (bullet->IsActive())
			bullet->Draw();
	for (auto exp : m_listExplosiveEffect)
	{
		if (exp->IsActive())
		{
			exp->Draw();
		}
	}

	//UI
	m_scoreText->Draw();
	m_playerHealText->Draw();
}

void GSPlay::CreateRandomUFO()
{
	/*
	int range = Application::screenHeight- 10 + 1;
	int num = rand() % range + 10;

	Vector2 pos;
	pos.x = 100;
	pos.y = num;
	if(num < Application::screenHeight /2){
	for (auto enermy : m_listEnermy2)
	{
		if (!enermy->IsActive())
		{
			enermy->SetActive(true);
			enermy->Set2DPosition(pos);
			return;
		}
	}
	*/
	Vector2 pos;
	pos.x = Application::screenWidth / 2;
	pos.y = 200;


	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture("enemyUFO");

	std::shared_ptr<UFO> enermy = std::make_shared<UFO>(model, shader, texture);

	enermy->SetActive(true);

	enermy->Set2DPosition(pos);
	enermy->SetSize(400, 400);
	enermy->SetRotation(180);
	enermy->SetTargetPosition(Vector2(Application::screenWidth - 100, 200));
	m_listEnermy2.push_back(enermy);
	//}
}
void GSPlay::CreateRandomUFO2()
{

	int range = Application::screenHeight - 10 + 1;
	int num = rand() % range + 10;

	Vector2 pos;
	pos.x = 100;
	pos.y = num;
	if (num < Application::screenHeight / 2) {
		for (auto enermy : m_listEnermy2)
		{
			if (!enermy->IsActive())
			{
				enermy->SetActive(true);
				enermy->Set2DPosition(pos);
				return;
			}
		}

		Vector2 pos;
		pos.x = Application::screenWidth / 2;
		pos.y = 200;


		auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
		auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
		auto texture = ResourceManagers::GetInstance()->GetTexture("enemyUFO");

		std::shared_ptr<UFO> enermy = std::make_shared<UFO>(model, shader, texture);

		enermy->SetActive(true);

		enermy->Set2DPosition(pos);
		enermy->SetSize(400, 400);
		enermy->SetRotation(180);
		m_listEnermy2.push_back(enermy);
	}
}


void GSPlay::CreateRandomEnermy()
{

	int range = Application::screenWidth - 10 + 1;
	int num = rand() % range + 10;

	Vector2 pos;
	pos.x = num;
	pos.y = 10;

	for (auto enermy : m_listEnermy)
	{
		if (!enermy->IsActive())
		{
			enermy->SetActive(true);
			enermy->Set2DPosition(pos);
			return;
		}
	}
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture("enemyShip");

	std::shared_ptr<Enermy> enermy = std::make_shared<Enermy>(model, shader, texture);
	enermy->Set2DPosition(pos);
	enermy->SetSize(40, 40);
	enermy->SetRotation(180);
	m_listEnermy.push_back(enermy);
}
void GSPlay::CreateRandomMeteor()
{

	int range = Application::screenWidth - 10 + 1;
	int num = rand() % range + 10;

	Vector2 pos;
	pos.x = num;
	pos.y = 10;

	for (auto meteor : m_listMeteor)
	{
		if (!meteor->IsActive())
		{
			meteor->SetActive(true);
			meteor->Set2DPosition(pos);
			return;
		}

	}
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture("MeteorBig");



	std::shared_ptr<Meteor> meteor = std::make_shared<Meteor>(model, shader, texture);
	meteor->Set2DPosition(pos);
	meteor->SetSize(40, 40);
	meteor->SetRotation(180);
	m_listMeteor.push_back(meteor);
}

void GSPlay::SpawnExplosive(Vector2 pos)
{
	for (auto exp : m_listExplosiveEffect)
	{
		if (!exp->IsActive())
		{
			exp->SetActive(true);
			exp->Set2DPosition(pos);
			return;
		}
	}

	//animation
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("explosive");
	auto shader = ResourceManagers::GetInstance()->GetShader("SpriteShader");
	std::shared_ptr<ExplosiveEffect> exp = std::make_shared<ExplosiveEffect>(model, shader, texture, Vector2(960, 768), Vector2(192, 192), 0, 19, 0.7);
	exp->SetSize(100, 100);
	exp->Set2DPosition(pos);
	m_listExplosiveEffect.push_back(exp);
}