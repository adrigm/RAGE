#ifndef RAGE_CORE_ASSETMANAGER_HPP
#define RAGE_CORE_ASSETMANAGER_HPP

#include <map>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <RAGE/Core/Core_types.hpp>
#include <RAGE/Core/ConfigReader.hpp>
#include <RAGE/Core/tmx/Tmx.hpp>
#include <RAGE/Core/Export.hpp>

namespace ra
{

class RAGE_CORE_API AssetManager
{
public:
	void setPath(const std::string& thePath);

	sf::Texture* getTexture(const std::string& theName);
	sf::Texture* getTexture(const std::string& theName, sf::Texture* theTexture);
	sf::Texture* getTextureFromImage(const std::string& theName, const sf::Image* theImage, const sf::IntRect& theRect = sf::IntRect());

	void deleteTexture(const std::string& theName);
	void deleteTexture(const sf::Texture* theTexture);

	sf::Image* getImage(const std::string& theName);
	sf::Image* getImageFromTexture(const std::string& theName, const sf::Texture* theTexture);

	void deleteImage(const std::string& theName);
	void deleteImage(const sf::Image* theImage);

	sf::Font* getFont(const std::string& theName);

	void deleteFont(const std::string& theName);
	void deleteFont(const sf::Font* theFont);

	sf::SoundBuffer* getSoundBuffer(const std::string& theName);

	void deleteSoundBuffer(const std::string& theName);
	void deleteSoundBuffer(const sf::SoundBuffer* theSoundBuffer);

	sf::Music* getMusic(const std::string& theName);

	void deleteMusic(const std::string& theName);
	void deleteMusic(const sf::Music* theMusic);

	ra::ConfigReader* getConfig(const std::string& theName);

	void deleteConfig(const std::string& theName);
	void deleteConfig(const ra::ConfigReader* theConfig);

	ra::Tmx::Map* getTmxMap(const std::string& theName);

	void deleteTmxMap(const std::string& theName);
	void deleteTmxMap(const ra::Tmx::Map* theMap);

	void cleanup();

private:
	// Variables
	///////////////////////////////////////////////////////////////////////////
	/// Puntero a app
	App* m_app;
	friend class App;
	/// Directorio maestro donde buscar recursos
	std::string m_masterDir;
	/// Mapa de registro de todas las texturas
	std::map<std::string, sf::Texture*> m_textures;
	/// Mapa de registro de todas las imágenes
	std::map<std::string, sf::Image*> m_images;
	/// Mapa de registro de todas las fuentes
	std::map<std::string, sf::Font*> m_fonts;
	/// Mapa de registro de todos los buffers de sonido
	std::map<std::string, sf::SoundBuffer*> m_sounds;
	/// Mapa de registro de toda la música
	std::map<std::string, sf::Music*> m_music;
	/// Mapa de registro de todos los archivos de configuraciones
	std::map<std::string, ra::ConfigReader*> m_configs;
	/// Mapa de registro de todos los Tmx Maps
	std::map<std::string, ra::Tmx::Map*> m_maps;


	AssetManager();
	AssetManager(const AssetManager&);
	AssetManager& operator=(const AssetManager&);
	~AssetManager();
}; // class AssetManager

} // namespace ra

#endif // RAGE_CORE_ASSETMANAGER_HPP