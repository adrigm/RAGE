#include <RAGE/Core/ConfigCreate.hpp>

namespace ra
{

ConfigCreate::ConfigCreate()
{
}

ConfigCreate::~ConfigCreate()
{
}

void ConfigCreate::open(const std::string& filename)
{
	file.open(filename.c_str());
	file.clear();
}

void ConfigCreate::close()
{
	file.close();
}

void ConfigCreate::putSection(const std::string& section)
{
	file << "[" << section << "]" << std::endl;
}

void ConfigCreate::putValue(const std::string& key, const std::string& value)
{
	file << key << "=" << value << std::endl;
}

void ConfigCreate::putValue(const std::string& key, bool value)
{
	file << key << "=" << value << std::endl;
}
void ConfigCreate::putValue(const std::string& key, float value)
{
	file << key << "=" << value << std::endl;
}

void ConfigCreate::putValue(const std::string& key, int value)
{
	file << key << "=" << value << std::endl;
}

void ConfigCreate::putValue(const std::string& key, unsigned int value)
{
	file << key << "=" << value << std::endl;
}

void ConfigCreate::putValue(const std::string& key, long value)
{
	file << key << "=" << value << std::endl;
}

void ConfigCreate::putComment(const std::string& comment)
{
	file << "# " << comment << std::endl;
}

void ConfigCreate::putBlankLine()
{
	file << std::endl;
}

} // namespace ra
