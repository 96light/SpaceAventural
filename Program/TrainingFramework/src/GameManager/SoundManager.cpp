#include "SoundManager.h"



SoundManager::SoundManager()
{
	std::string dataPath = "..\\Data\\";
	m_SoundsPath = dataPath + "Sounds\\";
	m_Soloud = std::make_shared<SoLoud::Soloud>();
	m_Soloud->init();
}

SoundManager::~SoundManager()
{
}

void SoundManager::AddSound(const std::string& name)
{
	auto it = m_MapWave.find(name);
	if (it != m_MapWave.end())
	{
		return;
	}
	std::shared_ptr<SoLoud::Wav>  wave;
	std::string wav = m_SoundsPath + name + ".wav";
	wave = std::make_shared<SoLoud::Wav>();
	wave->load(wav.c_str()); // Load a wave file
	m_MapWave.insert(std::pair<std::string, std::shared_ptr<SoLoud::Wav>>(name, wave));
}

void SoundManager::PlaySound(const std::string& name, bool loop)
{
	std::shared_ptr<SoLoud::Wav>  wave;
	auto it = m_MapWave.find(name);
	if (it != m_MapWave.end())
	{
		wave = it->second;
	}
	else
	{
		std::string wav = m_SoundsPath + name + ".wav";
		wave = std::make_shared<SoLoud::Wav>();
		wave->load(wav.c_str()); // Load a wave file
		m_MapWave.insert(std::pair<std::string, std::shared_ptr<SoLoud::Wav>>(name, wave));
	}
	m_Soloud->play(*wave);
	
	//m_Soloud->setLooping(bool aLoop);
}

void SoundManager::PauseSound(const std::string& name)
{
	std::shared_ptr<SoLoud::Wav>  wave;
	auto it = m_MapWave.find(name);
	if (it != m_MapWave.end())
	{
		wave = it->second;
	}
	m_Soloud->stopAudioSource(*wave);
}
