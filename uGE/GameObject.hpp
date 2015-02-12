#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <string>
#include <vector>
#include "utils/glm.hpp"

#include "Shader.hpp"


namespace uGE {

	class Body;
	class Collider;
	class Controller;
	class Animation;
	class GameObject
	{
		public:
			glm::mat4 & transform;

		protected:
			std::string _name;
			glm::mat4 _transform;

			std::vector< GameObject * > children;

			Body 	 * _body;
			//
			std::vector<Collider * > _colliders; // for future use by students
			//
			Controller * _controller;
			Animation * _animation;

		public:
			GameObject( std::string name );
			virtual ~GameObject();

			std::string getName();

			void addChild( GameObject * child );
			void setBody( Body * body );
			Body* getBody();
			void setCollider( Collider * collider );
			void setController( Controller * controller );
			void setAnimation( Animation * animation );
			void render( Shader * shader, glm::mat4 & parentTransform );
			void update();

			void setPosition( glm::vec3 position );
			std::vector<Collider *> getCollider();
			glm::vec3 getPosition();

	};
}
#endif // GAMEOBJECT_H