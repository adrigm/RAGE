#include <iostream> // Quitar
#include <sstream>
#include <boost/filesystem.hpp>
#include <RAGE/Core/Core_types.hpp>
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

	// code...

	return m_exitCode;
}

} // namespace ra