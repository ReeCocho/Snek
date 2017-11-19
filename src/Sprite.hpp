#pragma once

/** 
 * @file Sprite.hpp
 * @brief Sprite header file.
 * @author Connor J. Bramham (ReeCocho)
 */

/** Includes. */
#include <string>
#include <glad\glad.h>

namespace snk
{
	/**
	 * @enum TextureFiltering
	 * @brief Texture filtering mode.
	 */
	enum class TextureFiltering
	{
		Nearest = GL_NEAREST,
		Linear = GL_LINEAR
	};

	/**
	 * @enum TextureWrap
	 * @brief Texture wrapping mode.
	 */
	enum class TextureWrap
	{
		Clamp = GL_CLAMP_TO_EDGE,
		Repeat = GL_REPEAT
	};

	/**
	 * @class Sprite.
	 * @brief Stores 2D image data.
	 */
	class Sprite
	{
	public:

		/**
		 * @brief Default constructor.
		 */
		Sprite() = default;

		/**
		 * @brief Constructor.
		 * @param Path to an image file.
		 * @param Requested filtering.
		 * @param Requested tiling.
		 */
		Sprite(const std::string& path, TextureFiltering filtering, TextureWrap wrap);

		/**
		 * @brief Destructor.
		 */
		~Sprite();

		/**
		 * @brief Get texture.
		 * @return Texture.
		 */
		inline GLuint getTexture() const
		{
			return m_texID;
		}

		/**
		 * @brief Get texture filtering.
		 * @return Texture filtering.
		 */
		inline TextureFiltering getFiltering() const
		{
			return m_filtering;
		}
		
		/**
		 * @brief Get texture wrapping.
		 * @return Texture wrapping.
		 */
		inline TextureWrap getWrapping() const
		{
			return m_wrap;
		}

		/**
		 * @brief Get width.
		 * @return Width.
		 */
		inline uint32_t getWidth() const
		{
			return m_width;
		}

		/**
		 * @brief Get height.
		 * @return Height.
		 */
		inline uint32_t getHeight() const
		{
			return m_height;
		}

	private:

		/** Texture filtering. */
		TextureFiltering m_filtering = TextureFiltering::Linear;

		/** Texture wrapping. */
		TextureWrap m_wrap = TextureWrap::Repeat;

		/** Image width. */
		uint32_t m_width = 0;

		/** Image height. */
		uint32_t m_height = 0;

		/** Texture handle. */
		GLuint m_texID = 0;
	};
}