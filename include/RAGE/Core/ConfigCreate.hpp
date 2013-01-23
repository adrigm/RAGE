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

	void Open(const std::string& filename);

	void Close();

	void PutSection(const std::string& section);

	void PutValue(const std::string& key, const std::string& value);

	void PutComment(const std::string& comment);

	void PutBlankLine();

private:
	std::ofstream file;

}; // class ConfigCreate

} // namespace ra

#endif // RAGE_CONFIG_CREATE_HPP