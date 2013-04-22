#include <iostream> // Quitar
#include <RAGE/Core.hpp>
#include "SceneGame.hpp"

int main(int argc, char **argv)
{
	int anExitCode = ra::StatusNoError;
	
	ra::App* anApp = ra::App::instance();

	anApp->registerExecutableDir(argc, argv);

	ra::AssetManager::instance()->setPath("Data");

	anApp->setFirstScene(new SceneGame("Game"));

	anExitCode = anApp->run();

	ra::App::release();
	
	anApp = 0;

	return anExitCode;
}