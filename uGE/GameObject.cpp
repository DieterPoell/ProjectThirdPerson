#include "GameObject.hpp"
#include "Controller.hpp"
#include "Body.hpp"
#include "Collider.hpp"
#include "Animation.hpp"


namespace uGE {

	GameObject::GameObject( std::string name )
	: transform( _transform ), _name( name ), _body( 0 ), _collider( 0 ), _controller( 0 ), _animation( 0 )
	{
	}

	GameObject::~GameObject()
	{
		delete _body;
        //

		for(unsigned int i = 0; i < _colliders.size() ; i++ ){
            delete _colliders[i];
        }
        //
		delete _controller;
		delete _animation;
	}

	void GameObject::addChild( GameObject * child )
	{
		children.push_back( child );
	}

	std::string GameObject::getName()
	{
		return _name;
	}


	void GameObject::render( Shader * shader, glm::mat4 & parentTransform )
	{
		//std::cout << "Rendering " << _name << std::endl;
		glm::mat4 transform = parentTransform * _transform;
		if ( _body ) _body->render( shader, transform );

		for ( auto i = children.begin(); i != children.end(); ++i ) {
			GameObject * child = (GameObject *) *i;
			child->render( shader, transform );
		}
	}

	void GameObject::setBody( Body * body )
	{
		_body = body;
	}
    Body* GameObject::getBody()
	{
		return _body;
	}
	void GameObject::setCollider( Collider * collider )
	{
		_colliders.push_back( collider );
	}

	std::vector<Collider *> GameObject::getCollider(){

	return _colliders;
	}

	void GameObject::setController( Controller * controller )
	{
		_controller = controller;
	}

	void GameObject::setPosition( glm::vec3 position )
	{
		_transform[3] = glm::vec4( position, 1.0f );
	}

	void GameObject::setAnimation( Animation * animation )
	{
	    _animation = animation;
	}

	void GameObject::update()
	{
		if ( _controller ) _controller->update();

		for ( auto i = children.begin(); i != children.end(); ++i ) {
			GameObject * child = (GameObject *) *i;
			child->update();
		}
	}//end of update();

	glm::vec3 GameObject::getPosition(){

        glm::vec4 position = glm::vec4( _transform[3] );//rotation,rotation,rotation, position...
        return glm::vec3( position );//vec3 because we only need the position and not the transformation. (x,y,z (w = HM01));
	//;
	}



}