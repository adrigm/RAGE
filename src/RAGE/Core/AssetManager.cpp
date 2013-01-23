#include <boost/filesystem.hpp>
#include <RAGE/Core/App.hpp>
#include <RAGE/Core/AssetManager.hpp>

namespace fs = boost::filesystem;

namespace ra
{

AssetManager* AssetManager::ms_instance = 0;

AssetManager::AssetManager()
	: app(ra::App::Instance())
	, m_masterDir(app->GetExecutableDir())
	, m_textures()
	, m_images()
	, m_fonts()
	, m_sounds()
	, m_music()
	, m_configs()
{
}

AssetManager::~AssetManager()
{
}

AssetManager* AssetManager::Instance()
{
	if(ms_instance == 0)
	{
		ms_instance = new AssetManager();
	}
	return ms_instance;
}

void AssetManager::Release()
{
	if(ms_instance)
	{
		delete ms_instance;
	}
	ms_instance = 0;
}

void AssetManager::SetPath(const std::string& thePath)
{
	fs::path path = app->GetExecutableDir() + thePath;

	path = fs::system_complete(path);

	if (fs::exists(path) && fs::is_directory(path))
	{
		path = fs::canonical(path);
		path = path.generic_string();
		std::string path_s = path.string();
		path_s.append("/");

		m_masterDir = path_s;

		app->log << "Path de recursos dir=\"" << path_s << "\"" << std::endl;
	}
	else
	{

		app->log << "[error] AssetManager::SetPath() no existe dir=\"" 
			<< path.string() << "\"" << std::endl;
	}
}

sf::Texture* AssetManager::GetTexture(const std::string& theName)
{
	// Comprobamos si ya esta cargada
	std::map<std::string, sf::Texture*>::const_iterator it;
	it = m_textures.find(theName);
	if (it != m_textures.end())
	{
		app->log << "AssetManager::GetImage() " << theName << " usando archivo existente" << std::endl;
		return it->second;
	}

	// Si no lo está, la intentamos cargar
	sf::Texture *texture = new sf::Texture();

	if(!texture->loadFromFile(m_masterDir + theName))
	{
		app->log << "[error] AssetManager::GetImage() " << theName << " no se ha podido cargar" << std::endl;
		texture->create(1, 1);
		return texture;
	}

	app->log << "AssetManager::GetTexture() " << theName << " cargado" << std::endl;

	// La añadimos a la lista
	m_textures[theName] = texture;

	// Devolvemos el puntero
	return texture;
}

sf::Texture* AssetManager::GetTextureFromImage(const std::string& theName, const sf::Image* theImage, const sf::IntRect& theRect)
{
	// Comprobamos si ya esta cargada
	std::map<std::string, sf::Texture*>::const_iterator it;
	it = m_textures.find(theName);
	if (it != m_textures.end())
	{
		app->log << "AssetManager::GetTexture() " << theName << " usando archivo existente" << std::endl;
		return it->second;
	}

	// Si no lo está, la creamos a partir de la Imagen
	sf::Texture *texture = new sf::Texture();
	if(!texture->loadFromImage(*theImage, theRect))
	{
		app->log << "[error] AssetManager::GetTexture() " << theName << " no se ha podido cargar" << std::endl;
		texture->create(1, 1);
		return texture;
	}

	app->log << "AssetManager::GetTextureFromImage() " << theName << " cargado" << std::endl;

	// La añadimos a la lista
	m_textures[theName] = texture;

	// Devolvemos el puntero
	return texture;
}

void AssetManager::DeleteTexture(const std::string& theName)
{
	std::map<std::string, sf::Texture*>::const_iterator it = m_textures.find(theName);
	if (it != m_textures.end())
	{
		delete it->second;
		m_textures.erase(it);
		app->log << "AssetManager::DeleteTexture() " << theName << "archivo eliminado" << std::endl;
		return;
	}

	app->log << "AssetManager::DeleteTexture() " << theName << "no está cargado" << std::endl;
}

void AssetManager::DeleteTexture(const sf::Texture* theTexture)
{
	std::map<std::string, sf::Texture*>::const_iterator it;
	for (it = m_textures.begin(); it != m_textures.end(); it++)
	{
		if (theTexture == it->second)
		{
			delete it->second;
			app->log << "AssetManager::DeleteTexture() " << it->first << "archivo eliminado" << std::endl;
			m_textures.erase(it);
			return;
		}
	}

	app->log << "AssetManager::DeleteTexture() La dirección no corresponde a una textura cargada" << std::endl;
}

sf::Image* AssetManager::GetImage(const std::string& theName)
{
	// Comprobamos si ya esta cargada
	std::map<std::string, sf::Image*>::const_iterator it;
	it = m_images.find(theName);
	if (it != m_images.end())
	{
		app->log << "AssetManager::GetImage() " << theName << " usando archivo existente" << std::endl;
		return it->second;
	}

	// Si no lo está, la intentamos cargar
	sf::Image *image = new sf::Image();

	if(!image->loadFromFile(m_masterDir + theName))
	{
		app->log << "[error] AssetManager::GetImage() " << theName << " no se ha podido cargar" << std::endl;
		image->create(1, 1);
		return image;
	}

	app->log << "AssetManager::GetImage() " << theName << " cargado" << std::endl;

	// La añadimos a la lista
	m_images[theName] = image;

	// Devolvemos el puntero
	return image;
}

sf::Image* AssetManager::GetImageFromTexture(const std::string& theName, const sf::Texture* theTexture)
{
	// Comprobamos si ya esta cargada
	std::map<std::string, sf::Image*>::const_iterator it;
	it = m_images.find(theName);
	if (it != m_images.end())
	{
		app->log << "AssetManager::GetImageFromTexture() " << theName << " usando archivo existente" << std::endl;
		return it->second;
	}

	// Si no lo está, la intentamos cargar
	sf::Image *image = new sf::Image();
	*image = theTexture->copyToImage();

	app->log << "AssetManager::GetImageFromTexture() " << theName << " imagen creada a partir de textura" << std::endl;

	app->log << "AssetManager::GetImageFromTexture() " << theName << " cargado" << std::endl;

	// La añadimos a la lista
	m_images[theName] = image;

	// Devolvemos el puntero
	return image;
}

void AssetManager::DeleteImage(const std::string& theName)
{
	std::map<std::string, sf::Image*>::const_iterator it = m_images.find(theName);
	if (it != m_images.end())
	{
		delete it->second;
		m_images.erase(it);
		app->log << "AssetManager::DeleteImage() " << theName << "archivo eliminado" << std::endl;
		return;
	}

	app->log << "AssetManager::DeleteImage() " << theName << "no está cargado" << std::endl;
}

void AssetManager::DeleteImage(const sf::Image* theImage)
{
	std::map<std::string, sf::Image*>::const_iterator it;
	for (it = m_images.begin(); it != m_images.end(); it++)
	{
		if (theImage == it->second)
		{
			delete it->second;
			app->log << "AssetManager::DeleteImage() " << it->first << "archivo eliminado" << std::endl;
			m_images.erase(it);
			return;
		}
	}

	app->log << "AssetManager::DeleteImage() La dirección no corresponde a una imagen cargada" << std::endl;
}

sf::Font* AssetManager::GetFont(const std::string& theName)
{
	// Comprobamos si ya esta cargada
	std::map<std::string, sf::Font*>::const_iterator it;
	it = m_fonts.find(theName);
	if (it != m_fonts.end())
	{
		app->log << "AssetManager::GetFont() " << theName << " usando archivo existente" << std::endl;
		return it->second;
	}

	// Si no lo está, la intentamos cargar
	sf::Font *font = new sf::Font();

	if(!font->loadFromFile(m_masterDir + theName))
	{
		app->log << "[error] AssetManager::GetFont() " << theName << " no se ha podido cargar" << std::endl;
		return font;
	}

	app->log << "AssetManager::GetFont() " << theName << " cargado" << std::endl;

	// La añadimos a la lista
	m_fonts[theName] = font;

	// Devolvemos el puntero
	return font;
}

void AssetManager::DeleteFont(const std::string& theName)
{
	std::map<std::string, sf::Font*>::const_iterator it = m_fonts.find(theName);
	if (it != m_fonts.end())
	{
		delete it->second;
		m_fonts.erase(it);
		app->log << "AssetManager::DeleteFont() " << theName << "archivo eliminado" << std::endl;
		return;
	}

	app->log << "AssetManager::DeleteFont() " << theName << "no está cargado" << std::endl;
}

void AssetManager::DeleteFont(const sf::Font* theFont)
{
	std::map<std::string, sf::Font*>::const_iterator it;
	for (it = m_fonts.begin(); it != m_fonts.end(); it++)
	{
		if (theFont == it->second)
		{
			delete it->second;
			app->log << "AssetManager::DeleteFont() " << it->first << "archivo eliminado" << std::endl;
			m_fonts.erase(it);
			return;
		}
	}

	app->log << "AssetManager::DeleteFont() La dirección no corresponde a una fuente cargada" << std::endl;
}

sf::SoundBuffer* AssetManager::GetSoundBuffer(const std::string& theName)
{
	// Comprobamos si ya esta cargada
	std::map<std::string, sf::SoundBuffer*>::const_iterator it;
	it = m_sounds.find(theName);
	if (it != m_sounds.end())
	{
		app->log << "AssetManager::GetSoundBuffer() " << theName << " usando archivo existente" << std::endl;
		return it->second;
	}

	// Si no lo está, la intentamos cargar
	sf::SoundBuffer *sound = new sf::SoundBuffer();

	if(!sound->loadFromFile(m_masterDir + theName))
	{
		app->log << "[error] AssetManager::GetSoundBuffer() " << theName << " no se ha podido cargar" << std::endl;
		return sound;
	}

	app->log << "AssetManager::GetSoundBuffer() " << theName << " cargado" << std::endl;

	// La añadimos a la lista
	m_sounds[theName] = sound;

	// Devolvemos el puntero
	return sound;
}

void AssetManager::DeleteSoundBuffer(const std::string& theName)
{
	std::map<std::string, sf::SoundBuffer*>::const_iterator it = m_sounds.find(theName);
	if (it != m_sounds.end())
	{
		delete it->second;
		m_sounds.erase(it);
		app->log << "AssetManager::DeleteSoundBuffer() " << theName << "archivo eliminado" << std::endl;
		return;
	}

	app->log << "AssetManager::DeleteSoundBuffer() " << theName << "no está cargado" << std::endl;
}

void AssetManager::DeleteSoundBuffer(const sf::SoundBuffer* theSoundBuffer)
{
	std::map<std::string, sf::SoundBuffer*>::const_iterator it;
	for (it = m_sounds.begin(); it != m_sounds.end(); it++)
	{
		if (theSoundBuffer == it->second)
		{
			delete it->second;
			app->log << "AssetManager::DeleteSoundBuffer() " << it->first << "archivo eliminado" << std::endl;
			m_sounds.erase(it);
			return;
		}
	}

	app->log << "AssetManager::DeleteSoundBuffer() La dirección no corresponde a un sonido cargado" << std::endl;
}

sf::Music* AssetManager::GetMusic(const std::string& theName)
{
	// Comprobamos si ya esta cargada
	std::map<std::string, sf::Music*>::const_iterator it;
	it = m_music.find(theName);
	if (it != m_music.end())
	{
		app->log << "AssetManager::GetMusic() " << theName << " usando archivo existente" << std::endl;
		return it->second;
	}

	// Si no lo está, la intentamos cargar
	sf::Music *music = new sf::Music();

	if(!music->openFromFile(m_masterDir + theName))
	{
		app->log << "[error] AssetManager::GetMusic() " << theName << " no se ha podido cargar" << std::endl;
		return music;
	}

	app->log << "AssetManager::GetMusic() " << theName << " cargado" << std::endl;

	// La añadimos a la lista
	m_music[theName] = music;

	// Devolvemos el puntero
	return music;
}

void AssetManager::DeleteMusic(const std::string& theName)
{
	std::map<std::string, sf::Music*>::const_iterator it = m_music.find(theName);
	if (it != m_music.end())
	{
		delete it->second;
		m_music.erase(it);
		app->log << "AssetManager::DeleteMusic() " << theName << "archivo eliminado" << std::endl;
		return;
	}

	app->log << "AssetManager::DeleteMusic() " << theName << "no está cargado" << std::endl;
}

void AssetManager::DeleteMusic(const sf::Music* theMusic)
{
	std::map<std::string, sf::Music*>::const_iterator it;
	for (it = m_music.begin(); it != m_music.end(); it++)
	{
		if (theMusic == it->second)
		{
			delete it->second;
			app->log << "AssetManager::DeleteMusic() " << it->first << "archivo eliminado" << std::endl;
			m_music.erase(it);
			return;
		}
	}

	app->log << "AssetManager::DeleteMusic() La dirección no corresponde a una música cargada" << std::endl;
}

ra::ConfigReader* AssetManager::GetConfig(const std::string& theName)
{
	// Comprobamos si ya esta cargada
	std::map<std::string, ra::ConfigReader*>::const_iterator it;
	it = m_configs.find(theName);
	if (it != m_configs.end())
	{
		app->log << "AssetManager::GetConfig() " << theName << " usando archivo existente" << std::endl;
		return it->second;
	}

	// Si no lo está, la intentamos cargar
	ra::ConfigReader *config = new ra::ConfigReader();

	if(!config->LoadFromFile(m_masterDir + theName))
	{
		app->log << "[error] AssetManager::GetConfig() " << theName << " no se ha podido cargar" << std::endl;
		return config;
	}

	app->log << "AssetManager::GetConfig() " << theName << " cargado" << std::endl;

	// La añadimos a la lista
	m_configs[theName] = config;

	// Devolvemos el puntero
	return config;
}

void AssetManager::DeleteConfig(const std::string& theName)
{
	std::map<std::string, ra::ConfigReader*>::const_iterator it = m_configs.find(theName);
	if (it != m_configs.end())
	{
		delete it->second;
		m_configs.erase(it);
		app->log << "AssetManager::DeleteConfig() " << theName << "archivo eliminado" << std::endl;
		return;
	}

	app->log << "AssetManager::DeleteConfig() " << theName << "no está cargado" << std::endl;
}

void AssetManager::DeleteConfig(const ra::ConfigReader* theConfig)
{
	std::map<std::string, ra::ConfigReader*>::const_iterator it;
	for (it = m_configs.begin(); it != m_configs.end(); it++)
	{
		if (theConfig == it->second)
		{
			delete it->second;
			app->log << "AssetManager::DeleteConfig() " << it->first << "archivo eliminado" << std::endl;
			m_configs.erase(it);
			return;
		}
	}

	app->log << "AssetManager::DeleteConfig() La dirección no corresponde a una configuración cargada" << std::endl;
}

void AssetManager::Cleanup()
{
	std::map<std::string, sf::Texture*>::const_iterator textIt;
	for (textIt = m_textures.begin(); textIt != m_textures.end(); textIt++)
	{
		delete textIt->second;
		app->log << "AssetManager::Cleanup() Eliminado archivo " << textIt->first << std::endl;
	}
	m_textures.clear();

	std::map<std::string, sf::Image*>::const_iterator imgIt;
	for (imgIt = m_images.begin(); imgIt != m_images.end(); imgIt++)
	{
		delete imgIt->second;
		app->log << "AssetManager::Cleanup() Eliminado archivo " << imgIt->first << std::endl;
	}
	m_images.clear();

	std::map<std::string, sf::Font*>::const_iterator fonIt;
	for (fonIt = m_fonts.begin(); fonIt != m_fonts.end(); fonIt++)
	{
		delete fonIt->second;
		app->log << "AssetManager::Cleanup() Eliminado archivo " << fonIt->first << std::endl;
	}
	m_fonts.clear();

	std::map<std::string, sf::SoundBuffer*>::const_iterator souIT;
	for (souIT = m_sounds.begin(); souIT != m_sounds.end(); souIT++)
	{
		delete souIT->second;
		app->log << "AssetManager::Cleanup() Eliminado archivo " << souIT->first << std::endl;
	}
	m_sounds.clear();

	std::map<std::string, sf::Music*>::const_iterator muIt;
	for (muIt = m_music.begin(); muIt != m_music.end(); muIt++)
	{
		delete muIt->second;
		app->log << "AssetManager::Cleanup() Eliminado archivo " << muIt->first << std::endl;
	}
	m_music.clear();

	std::map<std::string, ra::ConfigReader*>::const_iterator conIt;
	for (conIt = m_configs.begin(); conIt != m_configs.end(); conIt++)
	{
		delete conIt->second;
		app->log << "AssetManager::Cleanup() Eliminado archivo " << conIt->first << std::endl;
	}
	m_configs.clear();
}

} // namespace ra