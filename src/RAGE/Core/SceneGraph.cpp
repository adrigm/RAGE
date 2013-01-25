#include <RAGE/Core/SceneGraph.hpp>

namespace ra
{

SceneGraph::SceneGraph()
	: m_ZOrder(0)
	, m_visible(true)
{
}

SceneGraph::~SceneGraph()
{
}

ra::Int32 SceneGraph::GetZOrder() const
{
	return m_ZOrder;
}

void SceneGraph::SetZOrder(int z)
{
	m_ZOrder = z;
}

bool SceneGraph::IsVisible() const
{
	return m_visible;
}

void SceneGraph::Show()
{
	m_visible = true;
}

void SceneGraph::Hide()
{
	m_visible = false;
}

} // namespace ra