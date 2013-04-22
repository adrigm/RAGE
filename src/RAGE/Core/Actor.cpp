#include <string>
#include <RAGE/Core/App.hpp>
#include <RAGE/Core/Actor.hpp>
#include <RAGE/Core/ConfigReader.hpp>
#include <iostream> // Quitar

namespace ra
{

Actor::Actor() :
	Sprite(),
	mSelectFrame(1),
	mSelectFrameAnimation(0),
	mElapsedTime(0.0f),
	mIsFlippedX(false),
	mIsFlippedY(false)
{
	mApp = ra::App::instance();
}

Actor::~Actor()
{
}

void Actor::SetFramesBySize(ra::Uint32 theWidth, ra::Uint32 theHeight)
{
	mRectsList.clear();

	ra::Uint32 cols = this->getTexture()->getSize().x / theWidth;
	ra::Uint32 rows = this->getTexture()->getSize().y / theHeight;

	for (int r = 0; r < rows; r++)
		for (int c = 0; c < cols; c++)
			mRectsList.push_back(sf::IntRect(c*theWidth, r*theHeight, theWidth, theHeight));

	this->setTextureRect(mRectsList[0]);

	this->SelectFrame(1);
}

void Actor::SetFramesByGrid(ra::Uint32 theRows, ra::Uint32 theCols)
{
	mRectsList.clear();

	ra::Uint32 width = this->getTexture()->getSize().x / theCols;
	ra::Uint32 height = this->getTexture()->getSize().y / theRows;

	for (int r = 0; r < theRows; r++)
		for (int c = 0; c < theCols; c++)
			mRectsList.push_back(sf::IntRect(c*width, r*height, width, height));

	this->SelectFrame(1);
}

void Actor::SelectFrame(ra::Uint32 theFrame)
{
	if (!mRectsList.empty())
	{
		// Elegimos el frame de forma modular
		this->setTextureRect(mRectsList[(theFrame - 1) % mRectsList.size()]);
		// Le damos la vuelta al rect de la textura según los flips
		if (mIsFlippedX)
			this->setTextureRect(sf::IntRect(this->getTextureRect().left + this->getTextureRect().width, this->getTextureRect().top, -this->getTextureRect().width, this->getTextureRect().height));
		if (mIsFlippedY)
			this->setTextureRect(sf::IntRect(this->getTextureRect().left, this->getTextureRect().top + this->getTextureRect().height, this->getTextureRect().width, -this->getTextureRect().height));
		this->mSelectFrame = theFrame;
	}
}

ra::Uint32 Actor::GetSelectFrame() const
{
	return this->mSelectFrame;
}

void Actor::AddAnimation(const std::string theName, const ra::Animation theAnim)
{
	if (mListAnim.find(theName) == mListAnim.end())
		this->mListAnim[theName] = theAnim;
}


ra::Animation Actor::GetAnimation(std::string theName) const
{
	return mListAnim.find(theName)->second;
}

void Actor::LoadAnimationsFromConfig(const ra::ConfigReader* theConfig)
{
	std::vector<std::string>::const_iterator it;
	std::vector<std::string> names = theConfig->getAllNameSections();
	for (it = names.begin(); it != names.end(); it++)
	{
		ra::Animation anAnimation;
		anAnimation.setFPS(theConfig->getUint32(*it, "fps", 20));
		anAnimation.setFirstFrame(theConfig->getUint32(*it, "firstFrame", 1));
		anAnimation.setLastFrame(theConfig->getUint32(*it, "lastFrame", 1));
		anAnimation.setFlipX(theConfig->getBool(*it, "flipX", false));
		anAnimation.setFlipY(theConfig->getBool(*it, "flipY", false));
		this->AddAnimation(*it, anAnimation);
	}
}

void Actor::SetActiveAnimation(const std::string theName, bool reset)
{
	std::map<std::string, ra::Animation>::const_iterator it;
	it = mListAnim.find(theName);
	if (it != mListAnim.end())
	{
		mActiveAnimation = it->second;
		this->SelectFrame(this->GetActiveAnimation().getFirstFrame());
		mSelectFrameAnimation = this->GetSelectFrame();
		this->FlipX(mActiveAnimation.getFlipX());
		this->FlipY(mActiveAnimation.getFlipY());
	}
}

ra::Animation Actor::GetActiveAnimation() const
{
	return mActiveAnimation;
}

void Actor::Animate()
{
	mElapsedTime += mApp->getUpdateTime().asSeconds();

	if (mElapsedTime >= 1.0f / this->GetActiveAnimation().getFPS())
	{
		mElapsedTime = 0.0f;

		this->SelectFrame(mSelectFrameAnimation);

		if (this->GetSelectFrame() < this->GetActiveAnimation().getLastFrame())
			mSelectFrameAnimation++;
		else
			mSelectFrameAnimation = this->GetActiveAnimation().getFirstFrame();
	}
}

void Actor::FlipX(bool flippedX)
{
	mIsFlippedX = flippedX;
	this->SelectFrame(this->GetSelectFrame());
}

void Actor::FlipY(bool flippedY)
{
	mIsFlippedY = flippedY;
	this->SelectFrame(this->GetSelectFrame());
}

void Actor::SetLeftPosition(float x)
{
	this->setPosition(x + this->getOrigin().x, this->getPosition().y);
}


void Actor::SetTopPosition(float y)
{
	this->setPosition(this->getPosition().x, y + this->getOrigin().y);
}

void Actor::SetRightPosition(float x)
{
	this->setPosition(x - (this->getGlobalBounds().width - this->getOrigin().x), this->getPosition().y);
}

void Actor::SetBottomPosition(float y)
{
	this->setPosition(this->getPosition().x, y - (this->getGlobalBounds().height - this->getOrigin().y));
}

float Actor::GetLeftPosition() const
{
	return this->getGlobalBounds().left;
}

float Actor::GetTopPosition() const
{
	return this->getGlobalBounds().top;
}
float Actor::GetRightPosition() const
{
	return this->getGlobalBounds().left + this->getGlobalBounds().width;
}

float Actor::GetBottomPosition() const
{
	return this->getGlobalBounds().top + this->getGlobalBounds().height;
}

} // Namespace ra