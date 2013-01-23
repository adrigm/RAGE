#include <iostream> // Quitar
#include <RAGE/Core.hpp>

int main(int argc, char **argv)
{
	ra::App *anApp = ra::App::Instance();

	anApp->RegisterExecutableDir(argc, argv);

	system("PAUSE");

	return 0;
}