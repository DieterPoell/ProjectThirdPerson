#ifndef BODY_H
#define BODY_H

#include "GameObject.hpp"
#include "Utils/glm.hpp"
#include "Shader.hpp"

namespace uGE {

	class Mesh;
	class Body
	{
		private:
			GameObject 	* _parent;
			Mesh 		* _mesh;
			Texture 	* _texture;
			Shader      * _shader;

		public:
			Body( GameObject * parent );
			virtual ~Body();
			void render( Shader * shader, glm::mat4 & transform );
			void setMesh( Mesh * mesh );
			void setTexture( Texture * texture );
			void setShader( Shader * shader );
			Shader * getShader();
	};
}
#endif // BODY_H