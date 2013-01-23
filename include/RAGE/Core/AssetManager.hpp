#ifndef RAGE_CORE_ASSET_MANAGER_HPP
#define RAGE_CORE_ASSET_MANAGER_HPP

#include <map>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <RAGE/Core/Export.hpp>
#include <RAGE/Core/ConfigReader.hpp>
#include <RAGE/Core/AssetManager.hpp>

namespace ra
{

class RAGE_CORE_API AssetManager
{
	static AssetManager* ms_instance;

public:
	/**
	 * Devuelve un puntero a la instancia única de la clase si existe,
	 * si no, la crea y duevuelve el puntero.
	 * 
	 * @return Puntero a la instancia única de AssetManager
	 */
	static AssetManager* Instance();
	 
	/**
	 * Elimina la instancia única de la clase.
	 */
	static void Release();

	void SetPath(const std::string& thePath);

	sf::Texture* GetTexture(const std::string& theName);
	sf::Texture* GetTextureFromImage(const std::string& theName, const sf::Image* theImage, const sf::IntRect& theRect = sf::IntRect());

	void DeleteTexture(const std::string& theName);
	void DeleteTexture(const sf::Texture* theTexture);

	sf::Image* GetImage(const std::string& theName);
	sf::Image* GetImageFromTexture(const std::string& theName, const sf::Texture* theTexture);

	void DeleteImage(const std::string& theName);
	void DeleteImage(const sf::Image* theImage);

	sf::Font* GetFont(const std::string& theName);

	void DeleteFont(const std::string& theName);
	void DeleteFont(const sf::Font* theFont);

	sf::SoundBuffer* GetSoundBuffer(const std::string& theName);

	void DeleteSoundBuffer(const std::string& theName);
	void DeleteSoundBuffer(const sf::SoundBuffer* theSoundBuffer);

	sf::Music* GetMusic(const std::string& theName);

	void DeleteMusic(const std::string& theName);
	void DeleteMusic(const sf::Music* theMusic);

	ra::ConfigReader* GetConfig(const std::string& theName);

	void DeleteConfig(const std::string& theName);
	void DeleteConfig(const ra::ConfigReader* theConfig);

	void Cleanup();

private:
	// Variables
	///////////////////////////////////////////////////////////////////////////
	/// Puntero a app
	App* app;
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
	//std::map<std::string, ra::TmxMap*> m_maps;

	AssetManager();

	virtual ~AssetManager();

	/**
	 * AssetManager copy constructor is private because we do not allow copies of
	 * our Singleton class
	*/
	AssetManager(const AssetManager&);               // Intentionally undefined

	/**
	 * Our assignment operator is private because we do not allow copies
	 * of our Singleton class
	 */
	AssetManager& operator=(const AssetManager&);    // Intentionally undefined
}; // class AssetManager

} // namespace ra

#endif // RAGE_CORE_ASSET_MANAGER_HPP