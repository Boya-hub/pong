#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "../main.h"
#include "ball.h"

Ball::Ball(unsigned int px, unsigned int py, float dx, float dy):
        m_px(px),m_py(py),m_dx(dx), m_dy(dy)
{
    m_texture.loadFromFile("./data/sprites/sprites.png");
    m_texture.setSmooth(true);
    m_sprite.setTexture(m_texture);
    m_sprite.setTextureRect(sf::IntRect(100, 5, BALL_LENGHT, BALL_WIDTH));
    m_sprite.setPosition(m_px, m_py);
    //ctor
}

Ball::~Ball()
{
    //dtor
}

Sprite Ball::getSprite() const{
    return m_sprite;
}

void Ball::moveX(float mx){
    m_px += mx;
    m_sprite.move(mx, 0);
}

void Ball::moveY(float my){
    m_py += my;
    m_sprite.move(0, my);
}

IntRect Ball::getHitBox() const
{
    //J'ai réduit la HitBox par rapport a la taille du sprite
    IntRect hitBox(m_sprite.getPosition().x + 14, m_sprite.getPosition().y + 10, 23, 22);
    return hitBox;
}

void Ball::resetPos()
{
    m_sprite.setPosition((FENETRE_LENGHT-BALL_LENGHT)/2, (FENETRE_WIDTH-BALL_WIDTH)/2);
}

void Ball::resetDeplacement()
{
    setDeplacementX(5);
    setDeplacementY(1);
}
