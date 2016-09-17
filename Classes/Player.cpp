#include "Player.h"
#include "Stage.hpp"

USING_NS_CC;

Player::Player()
{

}

Player::~Player()
{

}

bool Player::init()
{
    if(!Sprite::init())
    {
        return false;
    }
    
    
    return true;
}

void Player::update(float dt)
{

}
