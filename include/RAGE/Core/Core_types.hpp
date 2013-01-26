#ifndef   RAGE_CORE_TYPES_HPP
#define   RAGE_CORE_TYPES_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <map>
#include <string>
#include <RAGE/Config.hpp>

namespace ra
{
/// Status Enumeration for Status Return values
enum StatusType {
	// Values from -99 to 99 are common Error and Good status responses
	StatusAppMissingAsset = -4,  ///< Application failed due to missing asset file
	StatusAppStackEmpty   = -3,  ///< Application States stack is empty
	StatusAppInitFailed   = -2,  ///< Application initialization failed
	StatusError           = -1,  ///< General error status response
	StatusAppOK           =  0,  ///< Application quit without error
	StatusNoError         =  0,  ///< General no error status response
	StatusFalse           =  0,  ///< False status response
	StatusTrue            =  1,  ///< True status response
	StatusOK              =  1   ///< OK status response

	// Values from +-100 to +-199 are reserved for File status responses
};


// Forward declare RAGE Core classes provided
class ConfigReader;
class ConfigCreate;
class AssetManager;
class Scene;
class SceneManager;
class App;
class SceneGraph;
class Sprite;
class Text;
class Shape;
class CircleShape;
class RectangleShape;
class ConvexShape;
class Camera;

// Foward declare TmxMap


// Foward declare Map

/// ID único de las escenas
typedef std::string SceneID;

/// Declare NameValue typedef which is used for config section maps
typedef std::map<const std::string, const std::string> typeNameValue;

/// Declare NameValueIter typedef which is used for name,value pair maps
typedef std::map<const std::string, const std::string>::iterator typeNameValueIter;

} // namespace ra
#endif // RAGE_CORE_TYPES_HPP