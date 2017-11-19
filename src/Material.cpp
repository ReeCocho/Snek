#include <glm\gtc\type_ptr.hpp>
#include "Material.hpp"

namespace snk
{
	Material::Material(Shader* shader)
	{
		m_shader = shader;
	}

	Material::~Material()
	{

	}

	void Material::use()
	{
		assert(m_shader != nullptr);

		glUseProgram(m_shader->getProgram());

		// Floats
		for (auto const& iterator : m_values_float)
			glUniform1f(m_location_float[iterator.first], iterator.second);

		// Vec2
		for (auto const& iterator : m_values_vec2)
			glUniform2f(m_location_vec2[iterator.first], iterator.second.x, iterator.second.y);

		// Vec3
		for (auto const& iterator : m_values_vec3)
			glUniform3f(m_location_vec3[iterator.first], iterator.second.x, iterator.second.y, iterator.second.z);

		// Vec4
		for (auto const& iterator : m_values_vec4)
			glUniform4f(m_location_vec4[iterator.first], iterator.second.x, iterator.second.y, iterator.second.z, iterator.second.w);

		// Mat4
		for (auto const& iterator : m_values_mat4)
			glUniformMatrix4fv(m_location_mat4[iterator.first], 1, GL_FALSE, glm::value_ptr(iterator.second));

		// Int
		for (auto const& iterator : m_values_int)
			glUniform1i(m_location_int[iterator.first], iterator.second);

		// Texture
		int index = 0;

		for (auto const& iterator : m_values_sprite)
		{
			if (index < 16)
			{
				glUniform1i(m_location_sprite[iterator.first], index + 1);
				glActiveTexture(GL_TEXTURE1 + index);
				glBindTexture(GL_TEXTURE_2D, iterator.second->getTexture());
				index++;
			}
		}
	}
}