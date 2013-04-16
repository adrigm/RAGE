////////////////////////////////////////////////////////////
//
// SFML - Simple and Fast Multimedia Library
// Copyright (C) 2007-2012 Laurent Gomila (laurent.gom@gmail.com)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

#ifndef RAGE_CORE_TEXT_HPP
#define RAGE_CORE_TEXT_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/String.hpp>
#include <string>
#include <vector>
#include <RAGE/Core/Export.hpp>
#include <RAGE/Core/SceneObject.hpp>


namespace ra
{
////////////////////////////////////////////////////////////
/// \brief Graphical text that can be drawn to a render target
///
////////////////////////////////////////////////////////////
class RAGE_CORE_API Text : public SceneObject
{
public :

    ////////////////////////////////////////////////////////////
    /// \brief Enumeration of the string drawing styles
    ///
    ////////////////////////////////////////////////////////////
    enum Style
    {
        Regular    = 0,      ///< Regular characters, no style
        Bold       = 1 << 0, ///< Bold characters
        Italic     = 1 << 1, ///< Italic characters
        Underlined = 1 << 2  ///< Underlined characters
    };

    ////////////////////////////////////////////////////////////
    /// \brief Default constructor
    ///
    /// Creates an empty text.
    ///
    ////////////////////////////////////////////////////////////
    Text();

    ////////////////////////////////////////////////////////////
    /// \brief Construct the text from a string, font and size
    ///
    /// \param string         Text assigned to the string
    /// \param font           Font used to draw the string
    /// \param characterSize  Base size of characters, in pixels
    ///
    ////////////////////////////////////////////////////////////
    Text(const sf::String& string, const sf::Font& font, unsigned int characterSize = 30);

    ////////////////////////////////////////////////////////////
    /// \brief Set the text's string
    ///
    /// The \a string argument is a sf::String, which can
    /// automatically be constructed from standard string types.
    /// So, the following calls are all valid:
    /// \code
    /// text.setString("hello");
    /// text.setString(L"hello");
    /// text.setString(std::string("hello"));
    /// text.setString(std::wstring(L"hello"));
    /// \endcode
    /// A text's string is empty by default.
    ///
    /// \param string New string
    ///
    /// \see getString
    ///
    ////////////////////////////////////////////////////////////
    void setString(const sf::String& string);

    ////////////////////////////////////////////////////////////
    /// \brief Set the text's font
    ///
    /// The \a font argument refers to a font that must
    /// exist as long as the text uses it. Indeed, the text
    /// doesn't store its own copy of the font, but rather keeps
    /// a pointer to the one that you passed to this function.
    /// If the font is destroyed and the text tries to
    /// use it, the behaviour is undefined.
    ///
    /// \param font New font
    ///
    /// \see getFont
    ///
    ////////////////////////////////////////////////////////////
    void setFont(const sf::Font& font);

    ////////////////////////////////////////////////////////////
    /// \brief Set the character size
    ///
    /// The default size is 30.
    ///
    /// \param size New character size, in pixels
    ///
    /// \see getCharacterSize
    ///
    ////////////////////////////////////////////////////////////
    void setCharacterSize(unsigned int size);

    ////////////////////////////////////////////////////////////
    /// \brief Set the text's style
    ///
    /// You can pass a combination of one or more styles, for
    /// example sf::Text::Bold | sf::Text::Italic.
    /// The default style is sf::Text::Regular.
    ///
    /// \param style New style
    ///
    /// \see getStyle
    ///
    ////////////////////////////////////////////////////////////
    void setStyle(Uint32 style);

    ////////////////////////////////////////////////////////////
    /// \brief Set the global color of the text
    ///
    /// By default, the text's color is opaque white.
    ///
    /// \param color New color of the text
    ///
    /// \see getColor
    ///
    ////////////////////////////////////////////////////////////
    void setColor(const sf::Color& color);

    ////////////////////////////////////////////////////////////
    /// \brief Get the text's string
    ///
    /// The returned string is a sf::String, which can automatically
    /// be converted to standard string types. So, the following
    /// lines of code are all valid:
    /// \code
    /// sf::String   s1 = text.getString();
    /// std::string  s2 = text.getString();
    /// std::wstring s3 = text.getString();
    /// \endcode
    ///
    /// \return Text's string
    ///
    /// \see setString
    ///
    ////////////////////////////////////////////////////////////
    const sf::String& getString() const;

    ////////////////////////////////////////////////////////////
    /// \brief Get the text's font
    ///
    /// If the text has no font attached, a NULL pointer is returned.
    /// The returned reference is const, which means that you
    /// cannot modify the font when you get it from this function.
    ///
    /// \return Pointer to the text's font
    ///
    /// \see setFont
    ///
    ////////////////////////////////////////////////////////////
    const sf::Font* getFont() const;

    ////////////////////////////////////////////////////////////
    /// \brief Get the character size
    ///
    /// \return Size of the characters, in pixels
    ///
    /// \see setCharacterSize
    ///
    ////////////////////////////////////////////////////////////
    unsigned int getCharacterSize() const;

    ////////////////////////////////////////////////////////////
    /// \brief Get the text's style
    ///
    /// \return Text's style
    ///
    /// \see setStyle
    ///
    ////////////////////////////////////////////////////////////
    Uint32 getStyle() const;

    ////////////////////////////////////////////////////////////
    /// \brief Get the global color of the text
    ///
    /// \return Global color of the text
    ///
    /// \see setColor
    ///
    ////////////////////////////////////////////////////////////
    const sf::Color& getColor() const;

    ////////////////////////////////////////////////////////////
    /// \brief Return the position of the \a index-th character
    ///
    /// This function computes the visual position of a character
    /// from its index in the string. The returned position is
    /// in global coordinates (translation, rotation, scale and
    /// origin are applied).
    /// If \a index is out of range, the position of the end of
    /// the string is returned.
    ///
    /// \param index Index of the character
    ///
    /// \return Position of the character
    ///
    ////////////////////////////////////////////////////////////
    sf::Vector2f findCharacterPos(std::size_t index) const;

    ////////////////////////////////////////////////////////////
    /// \brief Get the local bounding rectangle of the entity
    ///
    /// The returned rectangle is in local coordinates, which means
    /// that it ignores the transformations (translation, rotation,
    /// scale, ...) that are applied to the entity.
    /// In other words, this function returns the bounds of the
    /// entity in the entity's coordinate system.
    ///
    /// \return Local bounding rectangle of the entity
    ///
    ////////////////////////////////////////////////////////////
    sf::FloatRect getLocalBounds() const;

    ////////////////////////////////////////////////////////////
    /// \brief Get the global bounding rectangle of the entity
    ///
    /// The returned rectangle is in global coordinates, which means
    /// that it takes in account the transformations (translation,
    /// rotation, scale, ...) that are applied to the entity.
    /// In other words, this function returns the bounds of the
    /// sprite in the global 2D world's coordinate system.
    ///
    /// \return Global bounding rectangle of the entity
    ///
    ////////////////////////////////////////////////////////////
    sf::FloatRect getGlobalBounds() const;

private :

    ////////////////////////////////////////////////////////////
    /// \brief Draw the text to a render target
    ///
    /// \param target Render target to draw to
    /// \param states Current render states
    ///
    ////////////////////////////////////////////////////////////
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    ////////////////////////////////////////////////////////////
    /// \brief Update the text's geometry
    ///
    ////////////////////////////////////////////////////////////
    void updateGeometry();

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    sf::String        m_string;        ///< String to display
    const sf::Font*   m_font;          ///< Font used to display the string
    unsigned int  m_characterSize; ///< Base size of characters, in pixels
    Uint32        m_style;         ///< Text style (see Style enum)
    sf::Color         m_color;         ///< Text color
    sf::VertexArray   m_vertices;      ///< Vertex array containing the text's geometry
    sf::FloatRect     m_bounds;        ///< Bounding rectangle of the text (in local coordinates)
};

} // namespace ra


#endif // RAGE_CORE_TEXT_HPP


////////////////////////////////////////////////////////////
/// \class ra::Text
/// \ingroup graphics
///
/// sf::Text is a drawable class that allows to easily display
/// some text with custom style and color on a render target.
///
/// It inherits all the functions from sf::Transformable:
/// position, rotation, scale, origin. It also adds text-specific
/// properties such as the font to use, the character size,
/// the font style (bold, italic, underlined), the global color
/// and the text to display of course.
/// It also provides convenience functions to calculate the
/// graphical size of the text, or to get the global position
/// of a given character.
///
/// sf::Text works in combination with the sf::Font class, which
/// loads and provides the glyphs (visual characters) of a given font.
///
/// The separation of sf::Font and sf::Text allows more flexibility
/// and better performances: indeed a sf::Font is a heavy resource,
/// and any operation on it is slow (often too slow for real-time
/// applications). On the other side, a sf::Text is a lightweight
/// object which can combine the glyphs data and metrics of a sf::Font
/// to display any text on a render target.
///
/// It is important to note that the sf::Text instance doesn't
/// copy the font that it uses, it only keeps a reference to it.
/// Thus, a sf::Font must not be destructed while it is
/// used by a sf::Text (i.e. never write a function that
/// uses a local sf::Font instance for creating a text).
///
/// Usage example:
/// \code
/// // Declare and load a font
/// sf::Font font;
/// font.loadFromFile("arial.ttf");
/// 
/// // Create a text
/// sf::Text text("hello", font);
/// text.setCharacterSize(30);
/// text.setStyle(sf::Text::Bold);
/// text.setColor(sf::Color::Red);
///
/// // Draw it
/// window.draw(text);
/// \endcode
///
/// \see sf::Font, sf::Transformable
///
////////////////////////////////////////////////////////////
