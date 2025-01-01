#pragma once

#include "core_lib/core/application.h"

namespace sauna_game
{

class GameApplication : public sauna_core::Application
{
public:
	GameApplication();
	~GameApplication();

	void init() override;
	void shutdown() override;

protected:
	const char* m_gameTitle = "Sauna Game";

private:
	void loadInitialScene();
	void loadResources();
};

}; // namespace sauna_game
