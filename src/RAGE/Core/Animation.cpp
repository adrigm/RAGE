#include <RAGE/Core/Animation.hpp>

namespace ra
{

Animation::Animation()
{
	this->fps = 20;
	this->firstFrame = 1;
	this->lastFrame = 1;
	this->flipX = false;
	this->flipY = false;
}

Animation::Animation(int firstFrame, int lastFrame, int fps, bool flipX, bool flipY)
{
	this->fps = fps;
	this->firstFrame = firstFrame;
	this->lastFrame = lastFrame;
	this->flipX = flipX;
	this->flipY = flipY;
}

unsigned int Animation::getFPS() const
{
	return fps;
}

void Animation::setFPS(unsigned int fps)
{
	this->fps = fps;
}

unsigned int Animation::getFirstFrame() const
{
	return firstFrame;
}

void Animation::setFirstFrame(unsigned int firstFrame)
{
	this->firstFrame = firstFrame;
}

unsigned int Animation::getLastFrame() const
{
	return lastFrame;
}

void Animation::setLastFrame(unsigned int lastFrame)
{
	this->lastFrame = lastFrame;
}

bool Animation::getFlipX() const
{
	return flipX;
}

void Animation::setFlipX(bool flipX)
{
	this->flipX = flipX;
}

bool Animation::getFlipY() const
{
	return flipY;
}

void Animation::setFlipY(bool flipY)
{
	this->flipY = flipY;
}

} // namespace ra