#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "Sprite.hpp"

namespace snk
{
	Sprite::Sprite(const std::string& path, TextureFiltering filtering, TextureWrap wrap) : m_filtering(filtering), m_wrap(wrap)
	{
		// Load image
		int width = 0, height = 0, nrChannels = 0;
		unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, STBI_rgb_alpha);

		m_width = static_cast<uint32_t>(width);
		m_height = static_cast<uint32_t>(height);

		// Create texture
		glGenTextures(1, &m_texID);
		glBindTexture(GL_TEXTURE_2D, m_texID);

		// Wrapping
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, static_cast<GLint>(m_wrap));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, static_cast<GLint>(m_wrap));

		// Filtering
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, static_cast<GLint>(m_filtering));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, static_cast<GLint>(m_filtering));

		// Bind data to texture
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);

		// Free memory
		stbi_image_free(data);
	}

	Sprite::~Sprite()
	{
		glDeleteTextures(1, &m_texID);
	}
}