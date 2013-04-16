#include <RAGE/Core/SceneObject.hpp>

namespace ra
{

SceneObject::SceneObject()
	: m_ZOrder(0)
	, m_visible(true)
{
}

SceneObject::~SceneObject()
{
}

ra::Int32 SceneObject::GetZOrder() const
{
	return m_ZOrder;
}

void SceneObject::SetZOrder(int z)
{
	m_ZOrder = z;
}

bool SceneObject::IsVisible() const
{
	return m_visible;
}

void SceneObject::Show()
{
	m_visible = true;
}

void SceneObject::Hide()
{
	m_visible = false;
}

} // namespace ra