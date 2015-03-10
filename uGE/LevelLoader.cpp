#include <iostream>
#include <string>
#include <vector>

#include "Colliders/SphereCollider.hpp"
#include "Colliders/AABBcollision.hpp"

#include "utils/glm.hpp"
#include "utils/tinyxml2.h"
#include "AssetManager.hpp"
#include "Body.hpp"
#include "GameObject.hpp"
#include "LevelLoader.hpp"
#include "Material.hpp"
#include "SceneManager.hpp"
#include "Shader.hpp"

using namespace tinyxml2;

namespace uGE
{
    LevelLoader::LevelLoader() {
    }

    LevelLoader::~LevelLoader() {
    }

    void LevelLoader::parseGroup( XMLElement * group )
    {
        XMLElement * object = group->FirstChildElement( "node" );

        while( object ) {
            //Set and format the object name
            std::string objName = std::string( object->Attribute( "name" ) );
            while( isdigit( objName.at( objName.size() - 1 ) ) ) {
                objName.pop_back();
            }

            if( objName == "group" ) {
                parseGroup( object );
                object = object->NextSiblingElement( "node" );
                continue;
            }

            //Decompose the matrix into the 16 separate values
            XMLElement * objMatrix = object->FirstChildElement( "matrix" );
            const char * matrixString = objMatrix->GetText();

            std::string  word;
            std::vector< std::string > words;
            for ( unsigned int i = 0; i < std::strlen(matrixString); ++i ) {
                if(matrixString[i] == ' ') {
                    words.push_back(word);
                    word.clear();
                }
                else {
                     word += matrixString[i];
                }
            }
            words.push_back(word);

            //Push the values in an empty matrix to add to the object later
            glm::mat4 matrix;
            for (unsigned int i = 0; i < words.size(); i++) {
                float value = std::atof( words[i].c_str() );
                matrix[i%4][i/4] = value;
            }

            //Compose the GameObject
            if( objName == "water" ) {
                GameObject * obj = new GameObject( objName );
                obj->transform = matrix;

                Body * body = new Body( obj );
                body->setMesh( AssetManager::loadMesh( "Assets/Models/" + objName + ".obj" ) );
                body->setTexture( AssetManager::loadTexture( "Assets/Textures/" + objName + ".png" ) );
                body->setShader( uGE::Shader::load( "Shaders/diffuse.vs", "Shaders/water.fs" ) );
                //body->getMaterial()->setBlendMode( Material::BlendMode::ALPHA );
                //body->getMaterial()->setAlpha( 1.75f );
                obj->setBody( body );

                uGE::SceneManager::add( obj );
            }

            if( objName.compare( "group" ) != 0 ) {
                GameObject * obj = new GameObject( objName );
                obj->transform = matrix;
                //std::cout<< objName << std::endl;
                Body * body = new Body( obj );
                body->setMesh( AssetManager::loadMesh( "Assets/Models/" + objName + ".obj" ) );
                body->setTexture( AssetManager::loadTexture( "Assets/Textures/" + objName + ".png" ) );
               // if(objName == "Ground_V") body->setShader(uGE::Shader::load( "Shaders/basic.vs", "Shaders/basic.fs"));
                obj->setBody( body );
                if( body->getMesh() ) {
                    obj->setCollider( new AABBcollision( obj ) );
                }
                uGE::SceneManager::addSpawnLoc(obj->getPosition());

                uGE::SceneManager::add( obj );
                if( objName == "tree_group" ){
                    // name of spawn should be here
                    //Zombie spawn controller then randomly get a location from spot [0] to [9]
                   /* uGE::SceneManager::addSpawnLoc(glm::vec3( 0.f, 0.f, 0.f ));
                    uGE::SceneManager::addSpawnLoc(glm::vec3( 3.f, 0.f, 0.f ));
                    uGE::SceneManager::addSpawnLoc(glm::vec3( 6.f, 0.f, 0.f ));
                    uGE::SceneManager::addSpawnLoc(glm::vec3( 0.f, 0.f, 3.f ));
                    uGE::SceneManager::addSpawnLoc(glm::vec3( 3.f, 0.f, 3.f ));
                    uGE::SceneManager::addSpawnLoc(glm::vec3( 6.f, 0.f, 3.f ));
                    uGE::SceneManager::addSpawnLoc(glm::vec3( 0.f, 0.f, 6.f ));
                    uGE::SceneManager::addSpawnLoc(glm::vec3( 3.f, 0.f, 6.f ));
                    uGE::SceneManager::addSpawnLoc(glm::vec3( 6.f, 0.f, 6.f ));
                    uGE::SceneManager::addSpawnLoc(glm::vec3( 0.f, 0.f, 9.f ));
                    uGE::SceneManager::addSpawnLoc(glm::vec3( 3.f, 0.f, 9.f ));
                    uGE::SceneManager::addSpawnLoc(glm::vec3( 6.f, 0.f, 9.f ));*/
                    uGE::SceneManager::addSpawnLoc(obj->getPosition());
                }
            }

            //Next object
            object = object->NextSiblingElement( "node" );
        }
    }

    void LevelLoader::parseXML(const char* iFilename)
    {
        XMLDocument doc;
        std::cout << "Loading level " << iFilename << ", result: " << doc.LoadFile(iFilename) << std::endl;

        XMLElement * object = doc.RootElement()->FirstChildElement( "library_visual_scenes" )->FirstChildElement();
        parseGroup( object );
    }

    void LevelLoader::loadLevel(std::string iFilename)
    {
        parseXML( ( "Assets/Level/" + iFilename + ".dae" ).c_str() );
    }
}
