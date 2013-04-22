#include <RAGE/Core/AssetManager.hpp>
#include <RAGE/Core/App.hpp>
#include <boost/filesystem.hpp>
#include <string>

namespace ra
{

AssetManager* AssetManager::m_instance = 0;

AssetManager* AssetManager::instance()
{
	if (m_instance == 0)
		m_instance = new AssetManager();
	return m_instance;
}

void AssetManager::release()
{
	if(m_instance)
		delete m_instance;
	m_instance = 0;
}


AssetManager::AssetManager()
	: m_textures()
	, m_images()
	, m_fonts()
	, m_sounds()
	, m_music()
	, m_configs()
{
	m_app = App::instance();
	m_masterDir = m_app->getExecutableDir();
	m_app->getLog() << "AssetManager::ctor()" << std::endl;
}

AssetManager::~AssetManager()
{
	m_app->getLog() << "AssetManager::dtor()" << std::endl;
}

void AssetManager::setPath(const std::string& thePath)
{
	boost::filesystem::path path = m_app->getExecutableDir() + thePath;

	path = boost::filesystem::system_complete(path);

	if (boost::filesystem::exists(path) && boost::filesystem::is_directory(path))
	{
		path = boost::filesystem::canonical(path);
		path = path.generic_string();
		std::string path_s = path.string();
		path_s.append("/");

		m_masterDir = path_s;

		m_app->getLog() << "Path de recursos dir=\"" << path_s << "\"" << std::endl;
	}
	else
	{

		m_app->getLog() << "[error] AssetManager::SetPath() no existe dir=\"" 
			<< path.string() << "\"" << std::endl;
	}
}

sf::Texture* AssetManager::getTexture(const std::string& theName)
{
	// Comprobamos si ya esta cargada
	std::map<std::string, sf::Texture*>::const_iterator it;
	it = m_textures.find(theName);
	if (it != m_textures.end())
	{
		m_app->getLog() << "AssetManager::getImage() " << theName << " usando archivo existente" << std::endl;
		return it->second;
	}

	// Si no lo está, la intentamos cargar
	sf::Texture *texture = new sf::Texture();

	if(!texture->loadFromFile(m_masterDir + theName))
	{
		m_app->getLog() << "[error] AssetManager::getImage() " << theName << " no se ha podido cargar" << std::endl;
		texture->create(1, 1);
		return texture;
	}

	texture->setRepeated(true);

	m_app->getLog() << "AssetManager::getTexture() " << theName << " cargado" << std::endl;

	// La añadimos a la lista
	m_textures[theName] = texture;

	// Devolvemos el puntero
	return texture;
}

sf::Texture* AssetManager::getTexture(const std::string& theName, sf::Texture* theTexture)
{
	// Comprobamos si ya esta cargada
	std::map<std::string, sf::Texture*>::const_iterator it;
	it = m_textures.find(theName);
	if (it != m_textures.end())
	{
		m_app->getLog() << "AssetManager::getTexture() " << theName << " usando textura existente" << std::endl;
		return it->second;
	}

	sf::Texture* texture = new sf::Texture(*theTexture);

	m_app->getLog() << "AssetManager::getTexture() " << theName << " cargado" << std::endl;

	// La añadimos a la lista
	m_textures[theName] = texture;

	// Devolvemos el puntero
	return texture;
}

sf::Texture* AssetManager::getTextureFromImage(const std::string& theName, const sf::Image* theImage, const sf::IntRect& theRect)
{
	// Comprobamos si ya esta cargada
	std::map<std::string, sf::Texture*>::const_iterator it;
	it = m_textures.find(theName);
	if (it != m_textures.end())
	{
		m_app->getLog() << "AssetManager::getTextureFromImage() " << theName << " usando archivo existente" << std::endl;
		return it->second;
	}

	// Si no lo está, la creamos a partir de la Imagen
	sf::Texture *texture = new sf::Texture();
	if(!texture->loadFromImage(*theImage, theRect))
	{
		m_app->getLog() << "[error] AssetManager::getTextureFromImage() " << theName << " no se ha podido cargar" << std::endl;
		texture->create(1, 1);
		return texture;
	}

	m_app->getLog() << "AssetManager::getTextureFromImage() " << theName << " cargado" << std::endl;

	// La añadimos a la lista
	m_textures[theName] = texture;

	// Devolvemos el puntero
	return texture;
}

void AssetManager::deleteTexture(const std::string& theName)
{
	std::map<std::string, sf::Texture*>::const_iterator it = m_textures.find(theName);
	if (it != m_textures.end())
	{
		delete it->second;
		m_textures.erase(it);
		m_app->getLog() << "AssetManager::deleteTexture() " << theName << " archivo eliminado" << std::endl;
		return;
	}

	m_app->getLog() << "AssetManager::deleteTexture() " << theName << " no está cargado" << std::endl;
}

void AssetManager::deleteTexture(const sf::Texture* theTexture)
{
	std::map<std::string, sf::Texture*>::const_iterator it;
	for (it = m_textures.begin(); it != m_textures.end(); it++)
	{
		if (theTexture == it->second)
		{
			delete it->second;
			m_app->getLog() << "AssetManager::deleteTexture() " << it->first << " archivo eliminado" << std::endl;
			m_textures.erase(it);
			return;
		}
	}

	m_app->getLog() << "AssetManager::deleteTexture() La dirección no corresponde a una textura cargada" << std::endl;
}

sf::Image* AssetManager::getImage(const std::string& theName)
{
	// Comprobamos si ya esta cargada
	std::map<std::string, sf::Image*>::const_iterator it;
	it = m_images.find(theName);
	if (it != m_images.end())
	{
		m_app->getLog() << "AssetManager::getImage() " << theName << " usando archivo existente" << std::endl;
		return it->second;
	}

	// Si no lo está, la intentamos cargar
	sf::Image *image = new sf::Image();

	if(!image->loadFromFile(m_masterDir + theName))
	{
		m_app->getLog() << "[error] AssetManager::getImage() " << theName << " no se ha podido cargar" << std::endl;
		image->create(1, 1);
		return image;
	}

	m_app->getLog() << "AssetManager::getImage() " << theName << " cargado" << std::endl;

	// La añadimos a la lista
	m_images[theName] = image;

	// Devolvemos el puntero
	return image;
}

sf::Image* AssetManager::getImageFromTexture(const std::string& theName, const sf::Texture* theTexture)
{
	// Comprobamos si ya esta cargada
	std::map<std::string, sf::Image*>::const_iterator it;
	it = m_images.find(theName);
	if (it != m_images.end())
	{
		m_app->getLog() << "AssetManager::getImageFromTexture() " << theName << " usando archivo existente" << std::endl;
		return it->second;
	}

	// Si no lo está, la intentamos cargar
	sf::Image *image = new sf::Image();
	*image = theTexture->copyToImage();

	m_app->getLog() << "AssetManager::getImageFromTexture() " << theName << " imagen creada a partir de textura" << std::endl;

	m_app->getLog() << "AssetManager::getImageFromTexture() " << theName << " cargado" << std::endl;

	// La añadimos a la lista
	m_images[theName] = image;

	// Devolvemos el puntero
	return image;
}

void AssetManager::deleteImage(const std::string& theName)
{
	std::map<std::string, sf::Image*>::const_iterator it = m_images.find(theName);
	if (it != m_images.end())
	{
		delete it->second;
		m_images.erase(it);
		m_app->getLog() << "AssetManager::deleteImage() " << theName << "archivo eliminado" << std::endl;
		return;
	}

	m_app->getLog() << "AssetManager::deleteImage() " << theName << "no está cargado" << std::endl;
}

void AssetManager::deleteImage(const sf::Image* theImage)
{
	std::map<std::string, sf::Image*>::const_iterator it;
	for (it = m_images.begin(); it != m_images.end(); it++)
	{
		if (theImage == it->second)
		{
			delete it->second;
			m_app->getLog() << "AssetManager::deleteImage() " << it->first << "archivo eliminado" << std::endl;
			m_images.erase(it);
			return;
		}
	}

	m_app->getLog() << "AssetManager::deleteImage() La dirección no corresponde a una imagen cargada" << std::endl;
}

sf::Font* AssetManager::getFont(const std::string& theName)
{
	// Comprobamos si ya esta cargada
	std::map<std::string, sf::Font*>::const_iterator it;
	it = m_fonts.find(theName);
	if (it != m_fonts.end())
	{
		m_app->getLog() << "AssetManager::getFont() " << theName << " usando archivo existente" << std::endl;
		return it->second;
	}

	// Si no lo está, la intentamos cargar
	sf::Font *font = new sf::Font();

	if(!font->loadFromFile(m_masterDir + theName))
	{
		m_app->getLog() << "[error] AssetManager::getFont() " << theName << " no se ha podido cargar" << std::endl;
		return font;
	}

	m_app->getLog() << "AssetManager::getFont() " << theName << " cargado" << std::endl;

	// La añadimos a la lista
	m_fonts[theName] = font;

	// Devolvemos el puntero
	return font;
}

void AssetManager::deleteFont(const std::string& theName)
{
	std::map<std::string, sf::Font*>::const_iterator it = m_fonts.find(theName);
	if (it != m_fonts.end())
	{
		delete it->second;
		m_fonts.erase(it);
		m_app->getLog() << "AssetManager::deleteFont() " << theName << "archivo eliminado" << std::endl;
		return;
	}

	m_app->getLog() << "AssetManager::deleteFont() " << theName << "no está cargado" << std::endl;
}

void AssetManager::deleteFont(const sf::Font* theFont)
{
	std::map<std::string, sf::Font*>::const_iterator it;
	for (it = m_fonts.begin(); it != m_fonts.end(); it++)
	{
		if (theFont == it->second)
		{
			delete it->second;
			m_app->getLog() << "AssetManager::deleteFont() " << it->first << "archivo eliminado" << std::endl;
			m_fonts.erase(it);
			return;
		}
	}

	m_app->getLog() << "AssetManager::deleteFont() La dirección no corresponde a una fuente cargada" << std::endl;
}

sf::SoundBuffer* AssetManager::getSoundBuffer(const std::string& theName)
{
	// Comprobamos si ya esta cargada
	std::map<std::string, sf::SoundBuffer*>::const_iterator it;
	it = m_sounds.find(theName);
	if (it != m_sounds.end())
	{
		m_app->getLog() << "AssetManager::getSoundBuffer() " << theName << " usando archivo existente" << std::endl;
		return it->second;
	}

	// Si no lo está, la intentamos cargar
	sf::SoundBuffer *sound = new sf::SoundBuffer();

	if(!sound->loadFromFile(m_masterDir + theName))
	{
		m_app->getLog() << "[error] AssetManager::getSoundBuffer() " << theName << " no se ha podido cargar" << std::endl;
		return sound;
	}

	m_app->getLog() << "AssetManager::getSoundBuffer() " << theName << " cargado" << std::endl;

	// La añadimos a la lista
	m_sounds[theName] = sound;

	// Devolvemos el puntero
	return sound;
}

void AssetManager::deleteSoundBuffer(const std::string& theName)
{
	std::map<std::string, sf::SoundBuffer*>::const_iterator it = m_sounds.find(theName);
	if (it != m_sounds.end())
	{
		delete it->second;
		m_sounds.erase(it);
		m_app->getLog() << "AssetManager::deleteSoundBuffer() " << theName << "archivo eliminado" << std::endl;
		return;
	}

	m_app->getLog() << "AssetManager::deleteSoundBuffer() " << theName << "no está cargado" << std::endl;
}

void AssetManager::deleteSoundBuffer(const sf::SoundBuffer* theSoundBuffer)
{
	std::map<std::string, sf::SoundBuffer*>::const_iterator it;
	for (it = m_sounds.begin(); it != m_sounds.end(); it++)
	{
		if (theSoundBuffer == it->second)
		{
			delete it->second;
			m_app->getLog() << "AssetManager::deleteSoundBuffer() " << it->first << "archivo eliminado" << std::endl;
			m_sounds.erase(it);
			return;
		}
	}

	m_app->getLog() << "AssetManager::deleteSoundBuffer() La dirección no corresponde a un sonido cargado" << std::endl;
}

sf::Music* AssetManager::getMusic(const std::string& theName)
{
	// Comprobamos si ya esta cargada
	std::map<std::string, sf::Music*>::const_iterator it;
	it = m_music.find(theName);
	if (it != m_music.end())
	{
		m_app->getLog() << "AssetManager::getMusic() " << theName << " usando archivo existente" << std::endl;
		return it->second;
	}

	// Si no lo está, la intentamos cargar
	sf::Music *music = new sf::Music();

	if(!music->openFromFile(m_masterDir + theName))
	{
		m_app->getLog() << "[error] AssetManager::getMusic() " << theName << " no se ha podido cargar" << std::endl;
		return music;
	}

	m_app->getLog() << "AssetManager::getMusic() " << theName << " cargado" << std::endl;

	// La añadimos a la lista
	m_music[theName] = music;

	// Devolvemos el puntero
	return music;
}

void AssetManager::deleteMusic(const std::string& theName)
{
	std::map<std::string, sf::Music*>::const_iterator it = m_music.find(theName);
	if (it != m_music.end())
	{
		delete it->second;
		m_music.erase(it);
		m_app->getLog() << "AssetManager::deleteMusic() " << theName << "archivo eliminado" << std::endl;
		return;
	}

	m_app->getLog() << "AssetManager::deleteMusic() " << theName << "no está cargado" << std::endl;
}

void AssetManager::deleteMusic(const sf::Music* theMusic)
{
	std::map<std::string, sf::Music*>::const_iterator it;
	for (it = m_music.begin(); it != m_music.end(); it++)
	{
		if (theMusic == it->second)
		{
			delete it->second;
			m_app->getLog() << "AssetManager::deleteMusic() " << it->first << "archivo eliminado" << std::endl;
			m_music.erase(it);
			return;
		}
	}

	m_app->getLog() << "AssetManager::deleteMusic() La dirección no corresponde a una música cargada" << std::endl;
}

ra::ConfigReader* AssetManager::getConfig(const std::string& theName)
{
	// Comprobamos si ya esta cargada
	std::map<std::string, ra::ConfigReader*>::const_iterator it;
	it = m_configs.find(theName);
	if (it != m_configs.end())
	{
		m_app->getLog() << "AssetManager::getConfig() " << theName << " usando archivo existente" << std::endl;
		return it->second;
	}

	// Si no lo está, la intentamos cargar
	ra::ConfigReader *config = new ra::ConfigReader();

	if(!config->loadFromFile(m_masterDir + theName))
	{
		m_app->getLog() << "[error] AssetManager::getConfig() " << theName << " no se ha podido cargar" << std::endl;
		return config;
	}

	m_app->getLog() << "AssetManager::getConfig() " << theName << " cargado" << std::endl;

	// La añadimos a la lista
	m_configs[theName] = config;

	// Devolvemos el puntero
	return config;
}

void AssetManager::deleteConfig(const std::string& theName)
{
	std::map<std::string, ra::ConfigReader*>::const_iterator it = m_configs.find(theName);
	if (it != m_configs.end())
	{
		delete it->second;
		m_configs.erase(it);
		m_app->getLog() << "AssetManager::deleteConfig() " << theName << "archivo eliminado" << std::endl;
		return;
	}

	m_app->getLog() << "AssetManager::deleteConfig() " << theName << "no está cargado" << std::endl;
}

void AssetManager::deleteConfig(const ra::ConfigReader* theConfig)
{
	std::map<std::string, ra::ConfigReader*>::const_iterator it;
	for (it = m_configs.begin(); it != m_configs.end(); it++)
	{
		if (theConfig == it->second)
		{
			delete it->second;
			m_app->getLog() << "AssetManager::deleteConfig() " << it->first << "archivo eliminado" << std::endl;
			m_configs.erase(it);
			return;
		}
	}

	m_app->getLog() << "AssetManager::deleteConfig() La dirección no corresponde a una configuración cargada" << std::endl;
}

ra::Tmx::Map* AssetManager::getTmxMap(const std::string& theName)
{
	// Comprobamos si ya esta cargada
	std::map<std::string, ra::Tmx::Map*>::const_iterator it;
	it = m_maps.find(theName);
	if (it != m_maps.end())
	{
		m_app->getLog() << "AssetManager::getTmxMap() " << theName << " usando archivo existente" << std::endl;
		return it->second;
	}

	// Si no lo está, la intentamos cargar
	ra::Tmx::Map *map = new ra::Tmx::Map();
	map->ParseFile(m_masterDir + theName);
	if(map->HasError())
	{
		m_app->getLog() << "[error] AssetManager::getTmxMap() " << theName << " no se ha podido cargar" << std::endl;
		return map;
	}

	m_app->getLog() << "AssetManager::getTmxMap() " << theName << " cargado" << std::endl;

	// La añadimos a la lista
	m_maps[theName] = map;

	// Devolvemos el puntero
	return map;
}

void AssetManager::deleteTmxMap(const std::string& theName)
{
	std::map<std::string, ra::Tmx::Map*>::const_iterator it = m_maps.find(theName);
	if (it != m_maps.end())
	{
		delete it->second;
		m_maps.erase(it);
		m_app->getLog() << "AssetManager::deleteTmxMap() " << theName << "archivo eliminado" << std::endl;
		return;
	}

	m_app->getLog() << "AssetManager::deleteTmxMap() " << theName << "no está cargado" << std::endl;
}

void AssetManager::deleteTmxMap(const ra::Tmx::Map* theMap)
{
	std::map<std::string, ra::Tmx::Map*>::const_iterator it;
	for (it = m_maps.begin(); it != m_maps.end(); it++)
	{
		if (theMap == it->second)
		{
			delete it->second;
			m_app->getLog() << "AssetManager::deleteTmxMap() " << it->first << "archivo eliminado" << std::endl;
			m_maps.erase(it);
			return;
		}
	}

	m_app->getLog() << "AssetManager::deleteTmxMap() La dirección no corresponde a una configuración cargada" << std::endl;
}

void AssetManager::cleanup()
{
	std::map<std::string, sf::Texture*>::const_iterator textIt;
	for (textIt = m_textures.begin(); textIt != m_textures.end(); textIt++)
	{
		delete textIt->second;
		m_app->getLog() << "AssetManager::Cleanup() Eliminado archivo " << textIt->first << std::endl;
	}
	m_textures.clear();

	std::map<std::string, sf::Image*>::const_iterator imgIt;
	for (imgIt = m_images.begin(); imgIt != m_images.end(); imgIt++)
	{
		delete imgIt->second;
		m_app->getLog() << "AssetManager::Cleanup() Eliminado archivo " << imgIt->first << std::endl;
	}
	m_images.clear();

	std::map<std::string, sf::Font*>::const_iterator fonIt;
	for (fonIt = m_fonts.begin(); fonIt != m_fonts.end(); fonIt++)
	{
		delete fonIt->second;
		m_app->getLog() << "AssetManager::Cleanup() Eliminado archivo " << fonIt->first << std::endl;
	}
	m_fonts.clear();

	std::map<std::string, sf::SoundBuffer*>::const_iterator souIT;
	for (souIT = m_sounds.begin(); souIT != m_sounds.end(); souIT++)
	{
		delete souIT->second;
		m_app->getLog() << "AssetManager::Cleanup() Eliminado archivo " << souIT->first << std::endl;
	}
	m_sounds.clear();

	std::map<std::string, sf::Music*>::const_iterator muIt;
	for (muIt = m_music.begin(); muIt != m_music.end(); muIt++)
	{
		delete muIt->second;
		m_app->getLog() << "AssetManager::Cleanup() Eliminado archivo " << muIt->first << std::endl;
	}
	m_music.clear();

	std::map<std::string, ra::ConfigReader*>::const_iterator conIt;
	for (conIt = m_configs.begin(); conIt != m_configs.end(); conIt++)
	{
		delete conIt->second;
		m_app->getLog() << "AssetManager::Cleanup() Eliminado archivo " << conIt->first << std::endl;
	}
	m_configs.clear();

	std::map<std::string, ra::Tmx::Map*>::const_iterator mapIt;
	for (mapIt = m_maps.begin(); mapIt != m_maps.end(); mapIt++)
	{
		delete mapIt->second;
		m_app->getLog() << "AssetManager::Cleanup() Eliminado archivo " << mapIt->first << std::endl;
	}
	m_configs.clear();
}

} // namespace ra