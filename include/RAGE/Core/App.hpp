#ifndef RAGE_CORE_APP_HPP
#define RAGE_CORE_APP_HPP

#include <fstream>
#include <string>
#include <SFML/Graphics.hpp>
#include <RAGE/Core/Export.hpp>
#include <RAGE/Core/Core_types.hpp>
#include <RAGE/Core/Camera.hpp>

namespace ra
{

class RAGE_CORE_API App
{
	static App* m_instance;

public:
	static const unsigned int DEFAULT_VIDEO_WIDTH = 640;
	static const unsigned int DEFAULT_VIDEO_HEIGHT = 480;
	static const unsigned int DEFAULT_VIDEO_BPP = 32;

	static App* instance();

	static void release();

	bool isRunning() const;

	void quit(int theExitCode);

	std::string getTitle() const;

	void setTitle(const std::string& theTitle);

	std::ofstream& getLog();

	sf::RenderWindow& getWindow();

	SceneManager* getSceneManager();

	AssetManager* getAssetManager();

	Camera& getCamera();

	void registerExecutableDir(int argc, char **argv);

	std::string getExecutableDir() const;

	const sf::Time& getUpdateTime() const;

	const sf::Time& getTotalTime() const;

	void enableQuit(bool value);

	void setFirstScene(Scene* scene);

	int run();

private:
	bool m_running;
	bool m_quit;
	Int16 m_exitCode;
	std::string m_title;
	std::string m_executableDir;
	std::ofstream m_log;
	sf::RenderWindow m_window;
	sf::Clock m_updateClock;
	sf::Time m_updateTime;
	sf::Time m_totalTime;
	SceneManager *m_sceneManager;
	Scene* m_initialScene;
	AssetManager* m_assetManager;
	Camera* m_camera;

	void createWindow();

	void init();

	void gameLoop();

	void cleanup();

	App();

	~App();

	App(const App&);

	App& operator=(const App&);
}; // class App

} // namespace ra

#endif // RAGE_CORE_APP_HPP