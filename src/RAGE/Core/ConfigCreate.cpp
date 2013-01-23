#include <RAGE/Core/ConfigCreate.hpp>

namespace ra
{

ConfigCreate::ConfigCreate()
{
}

ConfigCreate::~ConfigCreate()
{
}

void ConfigCreate::Open(const std::string& filename)
{
	file.open(filename);
	file.clear();
}

void ConfigCreate::Close()
{
	file.close();
}

void ConfigCreate::PutSection(const std::string& section)
{
	file << "[" << section << "]" << std::endl;
}

void ConfigCreate::PutValue(const std::string& key, const std::string& value)
{
	file << key << "=" << value << std::endl;
}

void ConfigCreate::PutComment(const std::string& comment)
{
	file << "# " << comment << std::endl;
}

void ConfigCreate::PutBlankLine()
{
	file << std::endl;
}

} // namespace ra