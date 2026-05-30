#include "Game/Player.hpp"
#include "Math/Physics.hpp"
#include "Math/Constants.hpp"

#include <cmath>

namespace Game {
    Player::Player(const Math::Vector2D<float>& pos,
                   Game::Map* mp, 
                   const float rad,
                   const float ang, 
                   const float vel, 
                   const float angVel)
        : position(pos), 
          map(mp), 
          radius(rad), 
          angle(ang), 
          velocity(vel), 
          angularVelocity(angVel)
    {}

    Player::~Player()
    {}

    const Math::Vector2D<float>& Player::getPosition() const { return position; }

    void Player::setPosition(const Math::Vector2D<float>& pos) { position = pos; }

    void Player::normalizeAngle() {
        while(angle < 0.0f)
            angle += TWO_PI;
        while(angle >= TWO_PI)
            angle -= TWO_PI;
    }


    const float Player::getAngle() const { return angle; }

    void Player::setAngle(float ang) { angle = ang; }

    void Player::handleInput() {
        const Uint8* keyState = SDL_GetKeyboardState(nullptr);

        if(keyState[SDL_SCANCODE_W])
            Math::Physics::updatePosition(position, velocity, angle, map, radius);

        if(keyState[SDL_SCANCODE_S])
            Math::Physics::updatePosition(position, -velocity, angle, map, radius);

        if(keyState[SDL_SCANCODE_A])
            Math::Physics::updateAngle(angle, -angularVelocity);
        
        if(keyState[SDL_SCANCODE_D])
            Math::Physics::updateAngle(angle, angularVelocity);
    }
}