#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <vector>
#include <SFML/Window.hpp>
#include "Utils/glm.hpp"

namespace uGE {

	class Camera;
	class GameObject;
	class Light;
	class Shader;

	class CollisionDetection;

	//empty space to add classes above
	class SceneManager
	{
		private:
			static Camera * _camera;
			static Light * _light;
			static Shader * _shader;
			static std::vector< GameObject * > _objects;
			//
			static CollisionDetection * _collision;

		public:
			SceneManager();
			virtual ~SceneManager();

			static void add( Camera * camera );
			static void add( GameObject * object );
			static void add( Light * light );
			static void add( Shader * shader );

			static bool control( sf::Window * window );

			static void render( sf::Window * window );
			static void update();

	};
}
#endif // SCENEMANAGER_H