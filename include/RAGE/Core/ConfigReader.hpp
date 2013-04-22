#ifndef   RAGE_CORE_CONFIG_READER_HPP
#define   RAGE_CORE_CONFIG_READER_HPP

#include <map>
#include <string>
#include <vector>
#include <RAGE/Core/Export.hpp>
#include <RAGE/Core/Core_types.hpp>

namespace ra
{

/// Provides basic configuration file reading
class RAGE_CORE_API ConfigReader
{
public:
    /**
    * ConfigReader constructor
    */
    ConfigReader();

    /**
    * ConfigReader copy constructor will duplicate the configuration
    * information that has been read from theCopy.
    * @param[in] theCopy to duplicate
    */
    ConfigReader(const ConfigReader& theCopy);

    /**
    * ConfigReader deconstructor
    */
    virtual ~ConfigReader();

	std::vector<std::string> getAllNameSections() const;

    /**
    * IsSectionEmpty determines if theSection provided exists and has 1 or
    * more name, value pairs to retrieve.
    * @param[in] theSection to check
    * @return true if theSection provided exists
    */
    bool isSectionEmpty(const std::string theSection) const;

    /**
    * getBool will return the boolean value for theSection and theName
    * specified or theDefault(false) if the section or name does not
    * exist.  The value must be one of the following to return either
    * true or false (0,1,on,off,true,false).
    * @param[in] theSection to use for finding the value to return
    * @param[in] theName to use for finding the value to return
    * @param[in] theDefault to use if the value is not found (optional)
    * @return the value found or theDefault if not found or correct
    */
    bool getBool(const std::string theSection, const std::string theName,
        const bool theDefault = false) const;

    /**
    * getFloat will return a floating point number for theSection and
    * theName specified or theDefault(0.f) if theSection or theName does not
    * exist.
    * @param[in] theSection to use for finding theName
    * @param[in] theName to use for finding the value to return
    * @param[in] theDefault to use if the value is not found (optional)
    * @return the value found or theDefault if not found or correct
    */
    float getFloat(const std::string theSection, const std::string theName,
        const float theDefault = 0.f) const;

    /**
    * getString will return the string value for theSection and theName
    * specified or theDefault("") if the section or name does not exist.
    * @param[in] theSection to use for finding theName
    * @param[in] theName to use for finding the value to return
    * @param[in] theDefault to use if the value is not found (optional)
    * @return the value found or theDefault if not found
    */
    std::string getString(const std::string theSection,
        const std::string theName, const std::string theDefault = "") const;

    /**
    * getUint32 will return an unsigned 32 bit number for theSection and
    * theName specified or theDefault(0) if theSection or theName does not
    * exist.
    * @param[in] theSection to use for finding theName
    * @param[in] theName to use for finding the value to return
    * @param[in] theDefault to use if the value is not found (optional)
    * @return the value found or theDefault if not found
    */
    Uint32 getUint32(const std::string theSection, const std::string theName,
        const Uint32 theDefault = 0) const;

    /**
    * LoadFromFile will open and read the configuration file specified into
    * internal maps that can be later retrieved using the get* options above.
    * @param[in] theFilename to use as the configuration file to read
    * @result true if theFilename was found and opened successfully
    */
    bool loadFromFile(const std::string theFilename);

    /**
    * Assignment operator will duplicate the information found in theRight
    * into this ConfigReader class.
    * @param[in] theRight hand side of = operator to duplicate from
    * @return the new left hand side copy
    */
    ConfigReader& operator=(const ConfigReader& theRight);

private:
    // Constants
    ///////////////////////////////////////////////////////////////////////////
    static const unsigned short MAX_CHARS = 100;

    // Variables
    ///////////////////////////////////////////////////////////////////////////
    /// Point to app
	ra::App *m_app;
    /// Map to store all the sections and their corresponding name=value pairs
    std::map<const std::string, typeNameValue*> m_sections;

    /**
    * ParseLine will parse the line provided by the Read method above.
    * @param theLine to be parsed.
    * @param theCount is the line number currently being processed
    * @param theSection to be used if name, value pair is parsed
    * @return string representing the new section name if section name was parsed
    */
    std::string parseLine(const char* theLine, const unsigned long theCount,
        const std::string theSection);

    /**
    * StoreNameValue will store theName and theValue pair into theSection.
    * If theSection name value map doesn't yet exist, then it will be created.
    * @param theSection is used to find the name, value pair map
    * @param theName to be stored as the key for theValue below
    * @param theValue to be stored in the current section name
    */
    void storeNameValue(const std::string theSection,
        const std::string theName, const std::string theValue);

}; // class ConfigReader

} // namespace ra

#endif // RAGE_CORE_CONFIG_READER_HPP