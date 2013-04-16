#include <boost/filesystem.hpp>
#include <RAGE/Core/Core_types.hpp>
#include <RAGE/Core/App.hpp>
#include <RAGE/Core/ConfigReader.hpp>
#include <RAGE/Core/ConfigCreate.hpp>
#include <RAGE/Core/Scene.hpp>
#include <RAGE/Core/SceneManager.hpp>
#include <RAGE/Core/AssetManager.hpp>

namespace ra
{

App* App::m_instance = 0;

App* App::instance()
{
	if (m_instance == 0)
		m_instance = new App();
	return m_instance;
}

void App::release()
{
	if(m_instance)
		delete m_instance;
	m_instance = 0;
}

App::App()
	: m_running(false)
	, m_exitCode(ra::StatusNoError)
	, m_title("RAGE Application")
	, m_executableDir("")
	, m_quit(true)
	, m_initialScene(0)
	, m_sceneManager(0)
	, m_assetManager(0)
	, m_camera(0)
{
	getLog().open("rage.log");
	getLog() << "LogFile: rage.log" << std::endl;
}

App::~App()
{
	m_log.close();
}

bool App::isRunning() const
{
	return m_running;
}

void App::quit(int theExitCode)
{
	m_exitCode = theExitCode; 
	m_running = false;
}

std::string App::getTitle() const
{
	return m_title;
}

void App::setTitle(const std::string& theTitle)
{
	m_title = theTitle;
	m_window.setTitle(m_title);
}

std::ofstream& App::getLog()
{
	return m_log;
}

sf::RenderWindow& App::getWindow()
{
	return m_window;
}

SceneManager* App::getSceneManager()
{
	return m_sceneManager;
}

AssetManager* App::getAssetManager()
{
	return m_assetManager;
}

Camera& App::getCamera()
{
	return *m_camera;
}

void App::registerExecutableDir(int argc, char **argv)
{
	if (argc > 0)
	{
		boost::filesystem::path path;
		path = boost::filesystem::system_complete(argv[0]);
		path = path.remove_filename();
		m_executableDir = path.string();
#if defined(RAGE_SYSTEM_WINDOWS)
		m_executableDir.append("\\");
#else
		m_executableDir.append("/");
#endif
		m_log << "App Path: " << m_executableDir << std::endl;
	}
}

std::string App::getExecutableDir() const
{
	return m_executableDir;
}

const sf::Time& App::getUpdateTime() const
{
	return m_updateTime;
}

const sf::Time& App::getTotalTime() const
{
	return m_totalTime;
}

void App::enableQuit(bool value)
{
	m_quit = value;
}

void App::setFirstScene(ra::Scene* scene)
{
	if (m_initialScene == 0)
	{
		m_initialScene = scene;
		m_log << "Establecida escena inicial: " << scene->getID() << std::endl;
	}
	else
	{
		m_log << "[warn]Ya se había establecido una escena inicial" << std::endl;
	}
}

int App::run()
{
	m_running = true;

	createWindow();

	init();

	gameLoop();

	cleanup();

	return m_exitCode;
}

void App::createWindow()
{
	sf::VideoMode videoMode(DEFAULT_VIDEO_WIDTH, DEFAULT_VIDEO_HEIGHT, DEFAULT_VIDEO_BPP);
	ra::Int32 style = sf::Style::Default;
	bool vsync = true;
	bool resize = true;
	bool fullscreen = false;

	ra::ConfigReader confFile;
	if (confFile.loadFromFile(getExecutableDir() + "window.cfg"))
	{
		// Si está activado fullScreen obtenemos la resolución del escritorio
		if (confFile.getBool("window", "fullscreen", false))
		{
			fullscreen = true;
			videoMode = sf::VideoMode::getDesktopMode();
			style = sf::Style::Fullscreen;
		}
		else
		{
			videoMode.width = confFile.getUint32("window", "width", DEFAULT_VIDEO_WIDTH);
			videoMode.height = confFile.getUint32("window", "height", DEFAULT_VIDEO_HEIGHT);
			videoMode.bitsPerPixel = confFile.getUint32("window", "bpp", DEFAULT_VIDEO_BPP);
			if (!confFile.getBool("window", "resize", true))
			{
				resize = false;
				style = sf::Style::Close | sf::Style::Titlebar;
			}
		}

		vsync = (confFile.getBool("m_window", "vsync", true));
	}

	m_window.create(videoMode, getTitle(), style);
	m_window.setVerticalSyncEnabled(vsync);

	ra::ConfigCreate conf;
	conf.open(getExecutableDir() + "window.cfg");
	conf.putSection("window");
	conf.putValue("width", videoMode.width);
	conf.putValue("height", videoMode.height);
	conf.putValue("bpp", videoMode.bitsPerPixel);
	conf.putValue("fullscreen", fullscreen);
	conf.putValue("resize", resize);
	conf.putValue("vsync", vsync);
}

void App::init()
{
	// Creamos el AssetManager();
	m_assetManager = new AssetManager();

	// Creamos la cámara
	m_camera = new Camera();
	m_camera->setDefaultCamera();

	// Creamos el SceneManager
	m_sceneManager = new SceneManager();

	// Establecemos la escene inicial
	if (m_initialScene != 0)
	{
		// Añadimos la primera escena
		m_sceneManager->addScene(m_initialScene);
		// La establecemos como escena activa
		m_sceneManager->setActiveScene(m_initialScene->getID());
		m_sceneManager->changeScene(m_sceneManager->m_nextScene);
	}
	else
	{
		m_log << "[error] App::Init() No se ha establecido escena inicial. LLamar a App::SetFirstScene() primero" 
			<< std::endl;
		// Salimos con código -2
		quit(ra::StatusAppInitFailed);
	}

	m_log << "App::Init() Completado" << std::endl;
}

void App::gameLoop()
{
	// Bucle mientras se esté ejecutando y la ventana esté abierta
	while (isRunning() && m_window.isOpen())
	{
		// Obtenemos el tiempo pasado en cada ciclo
		m_updateTime = m_updateClock.restart();
		// Almacenamos el tiempo total
		m_totalTime += m_updateTime;

		// Llamamos al método Update() de la escena activa
		m_sceneManager->updateScene();

		// Actualizamos la cámara
		m_camera->update();
		m_window.setView(*m_camera);

		// Llamamos al método Draw() de la escena activa
		m_sceneManager->drawScene();

		// Actualizamos la ventana
		m_window.display();

		// Manejamos los eventos de la ventana
		sf::Event event;
		while (m_window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:			// La ventana es cerrada
				if (m_quit)
					quit(StatusAppOK);
				else
					m_sceneManager->eventScene(event);
				break;
			case sf::Event::GainedFocus:	// La ventana obtiene el foco
				m_sceneManager->resumeScene();
				break;
			case sf::Event::LostFocus:		// La ventana pierde el foco
				m_sceneManager->pauseScene();
				break;
			default:	// Otros eventos se los pasamos a la ecena activa
				m_sceneManager->eventScene(event);
			} // switch (event.Type)
		} // while (m_window.GetEvent(event))

		// Comprobamos cambios de escena
		if (m_sceneManager->handleChangeScene())
		{
			// Cambiamos el puntero de la escena activa
			m_sceneManager->changeScene(m_sceneManager->m_nextScene);
			// Reseteamos la cámara
			m_camera->setDefaultCamera();
		}
	} // while (IsRunning() && m_window.IsOpened())
}

void App::cleanup()
{
	// Eliminamos las escenas
	m_sceneManager->removeAllScene();

	// Eliminamos el SceneManager
	delete m_sceneManager;
	m_sceneManager = 0;

	// Eliminamos la camara
	delete m_camera;
	m_camera = 0;

	// Liberamos todos los recursos
	m_assetManager->cleanup();

	// Eliminamos el AssetManager
	delete m_assetManager;
	m_assetManager = 0;
}

} // namespace ra