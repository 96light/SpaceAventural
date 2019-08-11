#pragma once
#include "Helper/Singleton.h"
#include "GameConfig.h"
#include "Helper/ThreadPool.h"
#include "Helper/ThreadPool.h"
#include "soloud.h"
#include "soloud_wav.h"

class SoundManager : public CSingleton<SoundManager>
{
public:
	SoundManager();
	~SoundManager();

	void AddSound(const std::string& name);
	void PlaySound(const std::string& name, bool loop = false);
	void PauseSound(const std::string& name);

private:
	std::string m_SoundsPath;
	std::map<std::string,std::shared_ptr<SoLoud::Wav>> m_MapWave;

	std::shared_ptr<SoLoud::Soloud> m_Soloud; // Engine core
};
