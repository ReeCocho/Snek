#pragma once

/** 
 * @file Utilities.hpp
 * @brief Utilities header file.
 * @author Connor J. Bramham (ReeCocho)
 */

/** Includes. */
#include <string>

namespace snk
{
	/**
	 * @brief Read a text file into a string
	 * @param Path to the text file.
	 * @return Contents of the text file.
	 */
	std::string readTextFile(const std::string& path);
}