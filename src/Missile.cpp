#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "Missile.h"

Missile::Missile(unsigned int px, unsigned int py, unsigned int dx): m_px(px), m_py(py), m_dx(dx)
{
    m_texture.loadFromFile("./data/sprites/bullets.png");
    m_texture.setSmooth(true);
    m_sprite.setTexture(m_texture);
    m_sprite.setTextureRect(sf::IntRect(62, 223, MISSILE_LENGHT, MISSILE_WIDTH));
    m_sprite.setPosition(m_px, m_py);
    //m_clock.restart();
}

Missile::~Missile()
{
    //dtor
}

Sprite Missile::getSprite() const
{
    return m_sprite;
}

void Missile::setPositionX(const float px)
{
    m_px = px;
    m_sprite.setPosition(m_px, m_py);
}

void Missile::setPositionY(const float py)
{
    m_py = py;
    m_sprite.setPosition(m_px, m_py);
}

void Missile::moveX(float mx)
{
    m_px += mx;
    m_sprite.move(mx, 0);
}

void Missile::moveY(float my)
{
    m_py += my;
    m_sprite.move(0, my);
}

void Missile::setMyTimeMissile(const Time t)
{
    m_myTimeMissile = t;
}

void Missile::resetPositionDepart()
{
    setPositionX(-40);
    setPositionY(-10);
    setDeplacementX(0);
}

IntRect Missile::getHitBox() const
{
    IntRect hitBox(m_sprite.getPosition().x, m_sprite.getPosition().y, MISSILE_LENGHT, MISSILE_WIDTH);
    return hitBox;
}

