#ifndef ACTOR_HPP
#define ACTOR_HPP

#include <vector>
#include <map>
#include <SFML/Graphics.hpp>
#include <RAGE/Core/Core_types.hpp>
#include <RAGE/Core/Sprite.hpp>
#include <RAGE/Core/Animation.hpp>

namespace ra
{

class Actor : public ra::Sprite
{
public:
	Actor();
	virtual ~Actor();

	/**
	 * Define el número de frames del Actor en base al tamaño de cada
	 * frame.
	 *
	 * @param theWidth Ancho de cada frame
	 * @param theHeight Alto de cada frame
	 */
	void SetFramesBySize(ra::Uint32 theWidth, ra::Uint32 theHeight);


	/**
	 * Define el número de frames del Actor en base al número de
	 * filas y columnas.
	 *
	 * @param theRows Filas de la imagen
	 * @param theCols Columnas de la imagen
	 */
	void SetFramesByGrid(ra::Uint32 theRows, ra::Uint32 theCols);

	/**
	 * Selecciona un frame del Actor
	 *
	 * @param theFrame numero del frame seleccionado (comienza en 1)
	 */
	void SelectFrame(ra::Uint32 theFrame);

	/**
	 * Devuelve el frame seleccionado
	 *
	 * @return Devuelve el frame seleccionado
	 */
	ra::Uint32 GetSelectFrame() const;

	void AddAnimation(const std::string theName, const ra::Animation theAnim);
	ra::Animation GetAnimation(std::string theName) const;

	void LoadAnimationsFromConfig(const ra::ConfigReader* theConfig);

	void SetActiveAnimation(const std::string theName, bool reset = true);
	ra::Animation GetActiveAnimation() const;

	virtual void Animate();

	void FlipX(bool flippedX);
	void FlipY(bool flippedY);

	void SetLeftPosition(float x);
	void SetTopPosition(float y);
	void SetRightPosition(float x);
	void SetBottomPosition(float y);

	float GetLeftPosition() const;
	float GetTopPosition() const;
	float GetRightPosition() const;
	float GetBottomPosition() const;

private:
	/// Puntero a App
	ra::App* mApp;
	/// Lista de rects del Sprite (frames)
	std::vector<sf::IntRect> mRectsList;
	/// Frame seleccionado (Rect)
	ra::Uint32 mSelectFrame;
	ra::Uint32 mSelectFrameAnimation;
	/// Lista de animaciones
	std::map<std::string, ra::Animation> mListAnim;
	/// Animación activa
	ra::Animation mActiveAnimation;
	/// Tiempo que transcurre entre cada frame
	float mElapsedTime;
	/// Verdadero si la imagen tiene Flip en el eje X
	bool mIsFlippedX;
	/// Verdadero si la imagen tiene Flip en el eje Y
	bool mIsFlippedY;

}; // Class Actor

} // Namepace ra

#endif // ACTOR_HPP