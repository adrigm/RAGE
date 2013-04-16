#ifndef RAGE_CORE_SCENE_HPP
#define RAGE_CORE_SCENE_HPP

#include <list>
#include <SFML/Graphics.hpp>
#include <RAGE/Core/Export.hpp>
#include <RAGE/Core/Core_types.hpp>

namespace ra
{

class RAGE_CORE_API Scene
{
public:
	virtual ~Scene();

	const SceneID& getID() const;

	//const bool IsPaused() const;
	
	void setBackgroundColor(const sf::Color &theColor);

	App* getApp();

	virtual void init() = 0;

	virtual void active() = 0;

	virtual void desactive() = 0;

	virtual void update() = 0;

	virtual void event(sf::Event theEvent) = 0;

	virtual void resume() = 0;

	virtual void pause() = 0;

	virtual void draw();

	virtual void cleanup() = 0;

	void addObject(SceneObject& object);
	void quitObject(SceneObject& object);
	void deleteObject(SceneObject& object);

protected:
	Scene(SceneID ID);

private:
	App* m_app;
	SceneID m_ID;
	sf::Color m_colorBack;
	std::list<SceneObject*> m_sceneObjects;
	std::list<SceneObject*>::const_iterator m_objectsIter;
};

} // namespace ra

#endif // RAGE_CORE_SCENE_HPP