#ifndef RAGE_CONFIG_CREATE_HPP
#define RAGE_CONFIG_CREATE_HPP

#include <string>
#include <fstream>
#include <RAGE/Core/Export.hpp>

namespace ra
{

class RAGE_CORE_API ConfigCreate
{
public:
	ConfigCreate();

	~ConfigCreate();

	void open(const std::string& filename);

	void close();

	void putSection(const std::string& section);

	void putValue(const std::string& key, const std::string& value);
	void putValue(const std::string& key, bool value);
	void putValue(const std::string& key, float value);
	void putValue(const std::string& key, int value);
	void putValue(const std::string& key, unsigned int value);
	void putValue(const std::string& key, long value);

	void putComment(const std::string& comment);

	void putBlankLine();

private:
	std::ofstream file;

}; // class ConfigCreate

} // namespace ra

#endif // RAGE_CONFIG_CREATE_HPP