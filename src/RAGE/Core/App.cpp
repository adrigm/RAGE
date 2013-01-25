#include <iostream> // Quitar
#include <sstream>
#include <boost/filesystem.hpp>
#include <RAGE/Core/Core_types.hpp>
#include <RAGE/Core/AssetManager.hpp>
#include <RAGE/Core/ConfigReader.hpp>
#include <RAGE/Core/ConfigCreate.hpp>
#include <RAGE/Core/SceneManager.hpp>
#include <RAGE/Core/Scene.hpp>
#include <RAGE/Core/App.hpp>

namespace ra
{

App* App::ms_instance = 0;

App::App()
	: window()
	, log()
	, m_executableDir("")
	, m_running(false)
	, m_exitCode(ra::StatusNoError)
	, m_title("RAGE Application")
	, m_windowStyle(sf::Style::Default)
	, m_videoMode(DEFAULT_VIDEO_WIDTH, DEFAULT_VIDEO_HEIGHT, DEFAULT_VIDEO_BPP)
	, m_initialScene(0)
	, m_updateClock()
	, m_updateTime()
	, m_totalTime()
{
	// Se crea el archivo de log
	log.open("rage.log");
	// Se escribe nombre del archivo
	log << "LogFile: rage.log" << std::endl;
}

App::~App()
{
	// Se cierra el log
	log.close();
}

App* App::Instance()
{
	if(ms_instance == 0)
	{
		ms_instance = new App();
	}
	return ms_instance;
}

void App::Release()
{
	if(ms_instance)
	{
		delete ms_instance;
	}
	ms_instance = 0;
}

void App::RegisterExecutableDir(int argc, char **argv)
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
		log << "App Path: " << m_executableDir << std::endl;
	}
}

std::string App::GetExecutableDir() const
{
	return m_executableDir;
}

bool App::IsRunning() const
{
	return m_running;
}

void App::Quit(int the_exit_code)
{
	m_exitCode = the_exit_code;
	m_running = false;
}

std::string App::GetTitle() const
{
	return m_title;
}

void App::SetTitle(const std::string theTitle)
{
	m_title = theTitle;
	window.setTitle(theTitle);

	log << "App::SetTitle() Titulo cambiado a: " << theTitle << std::endl;
}

void App::SetFirstScene(ra::Scene* theScene)
{
	if (m_initialScene == 0)
	{
		m_initialScene = theScene;
		log << "Establecida escena inicial: " << theScene->GetID() << std::endl;
	}
	else
	{
		log << "[warn]Ya se había establecido una escena inicial" << std::endl;
	}
}

sf::Time App::GetUpdateTime() const
{
	return m_updateTime;
}

sf::Time App::GetTotalTime() const
{
	return m_totalTime;
}

int App::Run()
{
	// Comprobamos que se ha llamado a RegisterExecutableDir para establecer la ruta del ejecutable
	if (m_executableDir == "")
	{
		log << "[ERROR] No se ha definido la ruta del ejecutable. ";
		log << "LLamar a App::RegisterExecutableDir() antes que a App::Run()";
		log << std::endl;

		return ra::StatusAppInitFailed;
	}

	// Cambiamos los aplicacion a ejecutandose
	m_running = true;

	CreateWindow();

	Init();

	GameLoop();

	Cleanup();

	return m_exitCode;
}

void App::CreateWindow()
{
	ra::ConfigReader confFile;
	bool vsync;

	if (confFile.LoadFromFile(GetExecutableDir() + "window.cfg"))
	{
		// Si está activado fullScreen obtenemos la resolución del escritorio
		if (confFile.GetBool("window", "fullscreen", 0))
		{
			m_videoMode = sf::VideoMode::getDesktopMode();
			m_windowStyle = sf::Style::Fullscreen;
		}
		else
		{
			m_videoMode.width = confFile.GetUint32("window", "width", DEFAULT_VIDEO_WIDTH);
			m_videoMode.height = confFile.GetUint32("window", "height", DEFAULT_VIDEO_HEIGHT);
			m_videoMode.bitsPerPixel = confFile.GetUint32("window", "bpp", DEFAULT_VIDEO_BPP);
			if(!m_videoMode.isValid())
			{
				m_videoMode = sf::VideoMode(DEFAULT_VIDEO_WIDTH, DEFAULT_VIDEO_HEIGHT, DEFAULT_VIDEO_BPP);
			}
		}
		vsync = (confFile.GetBool("window", "vsync", true));
	}
	else
	{
		ra::ConfigCreate conf;
		conf.Open(GetExecutableDir() + "window.cfg");
		conf.PutSection("window");
		conf.PutValue("width", DEFAULT_VIDEO_WIDTH);
		conf.PutValue("height", DEFAULT_VIDEO_HEIGHT);
		conf.PutValue("bpp", DEFAULT_VIDEO_BPP);
		conf.PutValue("fullscreen", false);
		conf.PutValue("vsync", true);
		conf.Close();
	}

	window.create(m_videoMode, m_title, m_windowStyle);

	log << "App::CreateWindow() ventana creada resolución (" << m_videoMode.width 
		<< ", " << m_videoMode.height << ", " << m_videoMode.bitsPerPixel << ")" 
		<< std::endl;

	if (vsync)
	{
		window.setVerticalSyncEnabled(vsync);
	}

	log << "App::CreateWindow() Completado" << std::endl;
}

void App::Init()
{
	// Creamos el Asset Manager
	m_assetManager = ra::AssetManager::Instance();

	// Creamos el Scene Manager
	m_sceneManager = ra::SceneManager::Instance();

	// Establecemos la escene inicial
	if (m_initialScene != 0)
	{
		// Añadimos la primera escena
		m_sceneManager->AddScene(m_initialScene);
		// La establecemos como escena activa
		m_sceneManager->SetActiveScene(m_initialScene->GetID());
		m_sceneManager->ChangeScene(m_sceneManager->mNextScene);
	}
	else
	{
		log << "[error] App::Init() No se ha establecido escena inicial. LLamar a App::SetFirstScene() primero" 
			<< std::endl;
		// Salimos con código -2
		Quit(ra::StatusAppInitFailed);
	}

	log << "App::Init() Completado" << std::endl;
}

void App::GameLoop()
{
	// Bucle mientras se esté ejecutando y la ventana esté abierta
	while (IsRunning() && window.isOpen())
	{
		// Manejamos los eventos de la ventana
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:			// La ventana es cerrada
				Quit(StatusAppOK);
				break;
			case sf::Event::GainedFocus:	// La ventana obtiene el foco
				m_sceneManager->ResumeScene();
				break;
			case sf::Event::LostFocus:		// La ventana pierde el foco
				m_sceneManager->PauseScene();
				break;
			default:	// Otros eventos se los pasamos a la ecena activa
				m_sceneManager->EventScene(event);
			} // switch (event.Type)
		} // while (window.GetEvent(event))

		// Obtenemos el tiempo pasado en cada ciclo
		m_updateTime = m_updateClock.restart();
		// Almacenamos el tiempo total
		m_totalTime += m_updateTime;

		// Llamamos al método Update() de la escena activa
		m_sceneManager->UpdateScene();

		// Llamamos al método Draw() de la escena activa
		m_sceneManager->DrawScene();

		// Actualizamos la ventana
		window.display();

		// Comprobamos cambios de escena
		if (m_sceneManager->HandleChangeScene())
		{
			// Cambiamos el puntero de la escena activa
			m_sceneManager->ChangeScene(m_sceneManager->mNextScene);
		}

	} // while (IsRunning() && window.IsOpened())
}

void App::Cleanup()
{
	// Eliminamos todas las escenas
	m_sceneManager->RemoveAllScene();

	// Eliminamos el SceneManager
	ra::SceneManager::Release();

	// Eliminamos todos los recursos
	m_assetManager->Cleanup();

	// Eliminamos el AssetManager
	ra::AssetManager::Release();

	log << "App::Cleanup() Completado" << std::endl;
}

} // namespace ra