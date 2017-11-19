/** Tell SDL not to mess with main() */
#define SDL_MAIN_HANDLED

/** Includes. */
#include <iostream>
#include <stdlib.h>
#include <time.h>   

#include "Engine.hpp"
#include "Transform.hpp"
#include "SpriteRenderer.hpp"
#include "Camera.hpp"
#include "Utilities.hpp"
#include "Snek.hpp"

const int WIDTH = 18;
const int HEIGHT = 18;

int main()
{
	// Initialize random seed
	srand(static_cast<unsigned int>(time(NULL)));

	// Unique ID's
	snk::Component::getUniqueIDs
	<
		snk::Transform, 
		snk::Snek,
		snk::SpriteRenderer,
		snk::Camera
	>();

	snk::Engine::initialize("Snek", 800, 800);

	// Setup input
	snk::Engine::get()->getInput()->registerAxis("Horizontal", { { snk::KeyCode::A, -1.0f },{ snk::KeyCode::D, 1.0f } });
	snk::Engine::get()->getInput()->registerAxis("Vertical", { { snk::KeyCode::W, 1.0f },{ snk::KeyCode::S, -1.0f } });

	{
		std::unique_ptr<snk::Mesh> mesh;
		{
			std::vector<uint32_t> indices =
			{
				0, 1, 2,
				0, 2, 3
			};

			std::vector<glm::vec2> vertices =
			{
				glm::vec2(-0.5f, -0.5f),
				glm::vec2(-0.5f,  0.5f),
				glm::vec2(0.5f,  0.5f),
				glm::vec2(0.5f, -0.5f)
			};

			std::vector<glm::vec2> uvs =
			{
				glm::vec2(1, 1),
				glm::vec2(1, 0),
				glm::vec2(0, 0),
				glm::vec2(0, 1)
			};

			// Meshes
			mesh = std::make_unique<snk::Mesh>(indices, vertices, uvs);
		}

		// Sprites
		auto box = std::make_unique<snk::Sprite>("../../src/Sprites/Box.png", snk::TextureFiltering::Linear, snk::TextureWrap::Clamp);
		auto circle = std::make_unique<snk::Sprite>("../../src/Sprites/Circle.png", snk::TextureFiltering::Linear, snk::TextureWrap::Clamp);

		// Shaders
		std::unique_ptr<snk::Shader> shader;
		{
			std::string vSource = snk::readTextFile("../../src/Shaders/standard.vert");
			std::string fSource = snk::readTextFile("../../src/Shaders/standard.frag");
			shader = std::make_unique<snk::Shader>(vSource, fSource);
		}

		// Materials
		auto empty_mat = std::make_unique<snk::Material>();
		empty_mat->setShader(shader.get());
		empty_mat->setValue("sprite", box.get());
		empty_mat->setValue("color", glm::vec4(0, 0, 0, 1));

		auto box_mat = std::make_unique<snk::Material>();
		box_mat->setShader(shader.get());
		box_mat->setValue("sprite", box.get());
		box_mat->setValue("color", glm::vec4(1, 0, 0, 1));

		auto circle_mat = std::make_unique<snk::Material>();
		circle_mat->setShader(shader.get());
		circle_mat->setValue("sprite", circle.get());
		circle_mat->setValue("color", glm::vec4(1, 1, 0, 1));

		auto border_mat = std::make_unique<snk::Material>();
		border_mat->setShader(shader.get());
		border_mat->setValue("sprite", box.get());
		border_mat->setValue("color", glm::vec4(1, 1, 1, 1));

		auto snakeOBJ = snk::Entity(snk::Engine::get()->getScene());
		auto snakeManager = snakeOBJ.addComponent<snk::Snek>();
		snakeManager->init(WIDTH, HEIGHT);
		snakeManager->m_emptyMaterial = empty_mat.get();
		snakeManager->m_snakeMaterial = box_mat.get();
		snakeManager->m_yummyMaterial = circle_mat.get();

		// Main camera
		{
			auto entity = snk::Entity(snk::Engine::get()->getScene());

			auto camera = entity.addComponent<snk::Camera>();
			camera->setSize(20);
			snk::Camera::setMainCamera(camera);

			auto transform = entity.getComponent<snk::Transform>();
			transform->setPosition(glm::vec3(0, 0, 0));
		}

		// Top border
		{
			auto entity = snk::Entity(snk::Engine::get()->getScene());

			auto transform = entity.getComponent<snk::Transform>();
			transform->setPosition(glm::vec3(0, 9.25f, 0));
			transform->setLocalScale(glm::vec2(19, 0.5f));

			auto spriteRenderer = entity.addComponent<snk::SpriteRenderer>();
			spriteRenderer->setMesh(mesh.get());
			spriteRenderer->setMaterial(border_mat.get());
		}

		// Bottom border
		{
			auto entity = snk::Entity(snk::Engine::get()->getScene());

			auto transform = entity.getComponent<snk::Transform>();
			transform->setPosition(glm::vec3(0, -9.25f, 0));
			transform->setLocalScale(glm::vec2(19, 0.5f));

			auto spriteRenderer = entity.addComponent<snk::SpriteRenderer>();
			spriteRenderer->setMesh(mesh.get());
			spriteRenderer->setMaterial(border_mat.get());
		}

		// Left border
		{
			auto entity = snk::Entity(snk::Engine::get()->getScene());

			auto transform = entity.getComponent<snk::Transform>();
			transform->setPosition(glm::vec3(9.25f, 0, 0));
			transform->setLocalScale(glm::vec2(0.5f, 19));

			auto spriteRenderer = entity.addComponent<snk::SpriteRenderer>();
			spriteRenderer->setMesh(mesh.get());
			spriteRenderer->setMaterial(border_mat.get());
		}

		// Bottom border
		{
			auto entity = snk::Entity(snk::Engine::get()->getScene());

			auto transform = entity.getComponent<snk::Transform>();
			transform->setPosition(glm::vec3(-9.25f, 0, 0));
			transform->setLocalScale(glm::vec2(0.5f, 19));

			auto spriteRenderer = entity.addComponent<snk::SpriteRenderer>();
			spriteRenderer->setMesh(mesh.get());
			spriteRenderer->setMaterial(border_mat.get());
		}

		for(int x = -WIDTH / 2; x < (WIDTH / 2); x++)
			for(int y = -HEIGHT / 2; y < (HEIGHT / 2); y++)
			{
				auto entity = snk::Entity(snk::Engine::get()->getScene());

				auto transform = entity.getComponent<snk::Transform>();
				transform->setPosition(glm::vec3(x + .5f, y + .5f, 0));

				auto spriteRenderer = entity.addComponent<snk::SpriteRenderer>();
				spriteRenderer->setMesh(mesh.get());
				spriteRenderer->setMaterial(empty_mat.get());

				snakeManager->setNode(x + (WIDTH / 2), y + (HEIGHT / 2), { spriteRenderer });
			}

		snakeManager->pickYummySpot();
		snk::Engine::start();
	}
	
	snk::Engine::stop();

	return 0;
}