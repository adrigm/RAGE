#ifndef RAGE_CORE_ANIMATION_HPP
#define RAGE_CORE_ANIMATION_HPP

#include <RAGE/Core/Export.hpp>

namespace ra
{

class RAGE_CORE_API Animation
{
public:
	Animation();
	Animation(int firstFrame , int lastFrame, int fps = 20, bool flipX = false, bool flipY = false);

	unsigned int getFPS() const;
	void setFPS(unsigned int fps);

	unsigned int getFirstFrame() const;
	void setFirstFrame(unsigned int firstFrame);

	unsigned int getLastFrame() const;
	void setLastFrame(unsigned int lastFrame);

	bool getFlipX() const;
	void setFlipX(bool flipX);

	bool getFlipY() const;
	void setFlipY(bool flipY);

private:
	unsigned int fps;
	unsigned int firstFrame;
	unsigned int lastFrame;
	bool flipX;
	bool flipY;
}; // class Animation

} // namespace ra

#endif // RAGE_CORE_ANIMATION_HPP