#include <iostream> // Quitar
#include <RAGE/Core.hpp>

int main(int argc, char **argv)
{
	ra::App *anApp = ra::App::Instance();

	anApp->RegisterExecutableDir(argc, argv);

	ra::AssetManager* am = ra::AssetManager::Instance();
	am->SetPath("Data");

	ra::ConfigReader* conf = am->GetConfig("../window.cfg");

	std::cout << conf->GetUint32("window", "width", 0) << std::endl;

	am->Cleanup();

	system("PAUSE");

	return 0;
}