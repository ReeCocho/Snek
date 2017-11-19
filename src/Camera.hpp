#pragma once

/** 
 * @file Camera.hpp
 * @brief Camera header file.
 * @author Connor J. Bramham (ReeCocho)
 */

/** Includes. */
#include "Engine.hpp"
#include "Transform.hpp"

namespace snk
{
	/**
	 * @class Camera
	 * @brief Allows for rendering to.
	 */
	class Camera : public Component
	{
	public:

		/**
		 * @brief Constructor.
		 * @param Scene the component is in.
		 * @param Entity the component belongs to.
		 * @param ID of the type of component.
		 */
		Camera(Scene* scene, Entity entity, ComponentID id);

		/**
		 * @brief Destructor.
		 */
		~Camera() = default;

		/**
		 * @brief Called when the component is added to a game object.
		 * @note Please use this for memory aquisition.
		 */
		void onBegin() override;

		/**
		 * @brief Called once per tick after onLateTick() but before presenting.
		 * @param Time in seconds since last tick.
		 */
		void onPreRender(float deltaTime) override;

		/**
		 * @brief Set main camera.
		 * @param New main camera.
		 * @return New main camera.
		 */
		static inline Camera* setMainCamera(Camera* camera)
		{
			mainCamera = camera;
			return mainCamera;
		}

		/**
		 * @brief Get main camera
		 * @return main camera.
		 */
		static inline Camera* getMainCamera()
		{
			return mainCamera;
		}

		/**
		 * @brief Get camera size.
		 * @return Camera size.
		 */
		inline float getSize() const
		{
			return m_size;
		}

		/**
		 * @brief Set camera size.
		 * @param New camera size.
		 * @return New camera size.
		 */
		inline float setSize(float size)
		{
			m_size = size;
			return m_size;
		}

	private:

		/** Main camera. */
		static Camera* mainCamera;

		/** Camera's transform. */
		Transform* m_transform = nullptr;

		/** Size of the view window. */
		float m_size = 5;
	};
}