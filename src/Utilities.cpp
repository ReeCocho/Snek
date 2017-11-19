#include <fstream>
#include "Utilities.hpp"

namespace snk
{
	std::string readTextFile(const std::string& path)
	{
		std::string contents;
		std::string line;

		auto stream = std::ifstream(path);

		if (stream.fail())
			throw std::runtime_error("Unable to open file at location " + path);

		while (std::getline(stream, line))
			contents += line + '\n';

		return contents;
	}
}