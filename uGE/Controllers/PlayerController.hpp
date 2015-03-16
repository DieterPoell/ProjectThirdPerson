#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H
#include "utils/glm.hpp"
#include "Controller.hpp"
#include "Viking.hpp"

#include "Player.hpp"

namespace uGE {

    struct CollisionResult;
    class Player;
	class PlayerController : public Controller
	{
        private:
            uGE::Player* _parent;
            float _shootTime;
            bool _isSucking;
            float _vikingTime;

            Viking * _viking;

		public:
			PlayerController( uGE::Player * parent );
			virtual ~PlayerController();

			void update();
			void shoot();
			void attack();
			void vacuum();

            void onCollision( CollisionResult * result );
	};
}
#endif // PLAYERCONTROLLER_H
