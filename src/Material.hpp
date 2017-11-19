#pragma once

/**
 * @file Material.hpp
 * @brief Material header file.
 * @author Connor J. Bramham (ReeCocho)
 */

/** Includes. */
#include <map>
#include <glm\glm.hpp>
#include "Sprite.hpp"
#include "Shader.hpp"

namespace snk
{
	/**
	 * @class Material
	 * @brief Holds data to send to a shader.
	 * @see Shader
	 */
	class Material
	{
	public:

		/**
		 * @brief Default constructor.
		 */
		Material() = default;

		/**
		 * @brief Constructor.
		 * @param Shader the material will use.
		 */
		Material(Shader* shader);

		/**
		 * @brief Destructor.
		 */
		~Material();

		/**
		 * @brief Set a new shader for the material.
		 * @param New shader.
		 * @return New shader.
		 */
		inline Shader* setShader(Shader* shader)
		{
			m_shader = shader;

			m_values_float.clear();
			m_values_int.clear();
			m_values_mat4.clear();
			m_values_vec2.clear();
			m_values_vec3.clear();
			m_values_vec4.clear();

			m_location_float.clear();
			m_location_int.clear();
			m_location_mat4.clear();
			m_location_vec2.clear();
			m_location_vec3.clear();
			m_location_vec4.clear();

			return m_shader;
		}

		/**
		 * @brief Get shader.
		 * @return Shader.
		 */
		inline Shader* getShader() const
		{
			return m_shader;
		}

		/**
		 * @brief Set float value.
		 * @param Value name.
		 * @param Value data.
		 */
		inline void setValue(const std::string& name, float value)
		{
			assert(m_shader != nullptr);
			removeValue(name);
			m_values_float[name] = value;
			m_location_float[name] = glGetUniformLocation(m_shader->getProgram(), name.c_str());
		}

		/**
		 * @brief Set vec2 value.
		 * @param Value name.
		 * @param Value data.
		 */
		inline void setValue(const std::string& name, glm::vec2 value)
		{
			assert(m_shader != nullptr);
			removeValue(name);
			m_values_vec2[name] = value;
			m_location_vec2[name] = glGetUniformLocation(m_shader->getProgram(), name.c_str());
		}

		/**
		 * @brief Set vec3 value.
		 * @param Value name.
		 * @param Value data.
		 */
		inline void setValue(const std::string& name, glm::vec3 value)
		{
			assert(m_shader != nullptr);
			removeValue(name);
			m_values_vec3[name] = value;
			m_location_vec3[name] = glGetUniformLocation(m_shader->getProgram(), name.c_str());
		}

		/**
		 * @brief Set vec4 value.
		 * @param Value name.
		 * @param Value data.
		 */
		inline void setValue(const std::string& name, glm::vec4 value)
		{
			assert(m_shader != nullptr);
			removeValue(name);
			m_values_vec4[name] = value;
			m_location_vec4[name] = glGetUniformLocation(m_shader->getProgram(), name.c_str());
		}

		/**
		 * @brief Set mat4 value.
		 * @param Value name.
		 * @param Value data.
		 */
		inline void setValue(const std::string& name, glm::mat4 value)
		{
			assert(m_shader != nullptr);
			removeValue(name);
			m_values_mat4[name] = value;
			m_location_mat4[name] = glGetUniformLocation(m_shader->getProgram(), name.c_str());
		}

		/**
		 * @brief Set int value.
		 * @param Value name.
		 * @param Value data.
		 */
		inline void setValue(const std::string& name, int value)
		{
			assert(m_shader != nullptr);
			removeValue(name);
			m_values_int[name] = value;
			m_location_int[name] = glGetUniformLocation(m_shader->getProgram(), name.c_str());
		}

		/**
		 * @brief Set sprite value.
		 * @param Value name.
		 * @param Value data.
		 */
		inline void setValue(std::string name, Sprite* value)
		{
			assert(m_shader != nullptr);
			removeValue(name);
			m_values_sprite[name] = value;
			m_location_sprite[name] = glGetUniformLocation(m_shader->getProgram(), name.c_str());
		}

		/**
		 * @brief Use the material.
		 * @note Used internally. Do not call.
		 */
		void use();

	private:

		/** Shader the material uses. */
		Shader* m_shader;

		/**
		 * @brief Removes a value from every uniform list by name.
		 * @param Name of the value to remove.
		 */
		inline void removeValue(const std::string& name)
		{
			// Remove from values
			m_values_float.erase(name);
			m_values_vec2.erase(name);
			m_values_vec3.erase(name);
			m_values_vec4.erase(name);
			m_values_mat4.erase(name);
			m_values_int.erase(name);
			m_values_sprite.erase(name);

			// Remove from location
			m_location_float.erase(name);
			m_location_vec2.erase(name);
			m_location_vec3.erase(name);
			m_location_vec4.erase(name);
			m_location_mat4.erase(name);
			m_location_int.erase(name);
			m_location_sprite.erase(name);
		}

		/** Values. */
		std::map<std::string, float> m_values_float = {};
		std::map<std::string, glm::vec2> m_values_vec2 = {};
		std::map<std::string, glm::vec3> m_values_vec3 = {};
		std::map<std::string, glm::vec4> m_values_vec4 = {};
		std::map<std::string, glm::mat4> m_values_mat4 = {};
		std::map<std::string, int> m_values_int = {};
		std::map<std::string, Sprite*> m_values_sprite = {};

		/** Locations. */
		std::map<std::string, uint32_t> m_location_float = {};
		std::map<std::string, uint32_t> m_location_vec2 = {};
		std::map<std::string, uint32_t> m_location_vec3 = {};
		std::map<std::string, uint32_t> m_location_vec4 = {};
		std::map<std::string, uint32_t> m_location_mat4 = {};
		std::map<std::string, uint32_t> m_location_int = {};
		std::map<std::string, uint32_t> m_location_sprite = {};
	};
}