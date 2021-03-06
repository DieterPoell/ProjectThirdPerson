#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <GL/glew.h>
#include "Utils/glm.hpp"


namespace uGE {


	class Mesh;
	class Texture;
	class Shader
	{
		private:
			GLuint _program;
		public:
			Shader( GLuint program = 0 );
			virtual ~Shader();

//			enum Locations {
//				vertex = 0, normal = 1, uv = 2,
//				projection = 10, view = 11, model = 12,
//				colorMap = 20, // room for more maps
//				lightCount = 30, light = 31,
//				time = 40
//			};
				GLuint vertex;
				GLuint normal;
				GLuint uv;
				GLuint projection;
				GLuint view;
				GLuint model;
				GLuint colorMap;
				GLuint normalMap;
				GLuint lightCount;
				GLuint light;
				GLuint camera;
				GLuint outlineColor;
				GLuint time;
				GLuint alpha;

			void use();

			void render( GLuint size );

			void setAttrib( GLuint buffer );
			void setAttrib( GLuint location, GLuint elements, GLuint buffer );
			void setTexture( GLuint location, Texture * texture );
			void setNormTex( GLuint location, Texture * texture );
			void setUniform( GLuint location, float value );
			void setUniform( GLuint location, glm::mat4 matrix );
			void setUniform( GLuint location, glm::vec3 vector );
			void setUniform( GLuint location, glm::vec4 color );

			static Shader * load( std::string vs, std::string fs );


		private:
			static GLuint compileShader( GLenum type, std::string name );
			static GLuint linkProgram ( std::string vertexShaderFileName, std::string fragmentShaderFileName );
	};
}
#endif // SHADER_H

