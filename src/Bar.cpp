#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "../main.h"
#include "Bar.h"

Bar::Bar(unsigned int px, unsigned int py, unsigned int dy):m_px(px),m_py(py),m_dy(dy)
{
    m_frozen = false;
    m_clock.restart();
    //ctor
}

void Bar::setTexture(unsigned int joueur)
{
    m_texture.loadFromFile("./data/sprites/sprites.png");
    m_texture.setSmooth(true);
    m_sprite.setTexture(m_texture);
    if (joueur == 1)
        m_sprite.setTextureRect(sf::IntRect(0, 5, BAR_LENGHT, BAR_WIDTH));
    else if(joueur == 2)
        m_sprite.setTextureRect(sf::IntRect(49, 5, BAR_LENGHT, BAR_WIDTH));
}

void Bar::setPositionX(unsigned int px)
{
    m_px = px;
    m_sprite.setPosition(px, m_py);
}

void Bar::setPositionY(unsigned int py)
{
    m_py = py;
    m_sprite.setPosition(m_px, py);
}

IntRect Bar::getHitBox() const
{
    IntRect hitBox(m_sprite.getPosition().x + 18, m_sprite.getPosition().y + 14, 13, 109);      //ATTENTION PAS DE CONST ET VAL REUTILISE AUTRE PART
    return hitBox;
}

void Bar::moveY(int my)
{
    m_py += my;
    m_sprite.move(0, my);
}

void Bar::setFrozen(bool b)
{
    m_frozen = b;
}

bool Bar::isFrozen() const
{
    return(m_frozen == true);
}

void Bar::setColorSprite(Color color)
{
    m_sprite.setColor(color);
}

void Bar::setTimeGotFreeze(Time t)
{
    m_timeGotFreeze = t;
}


Bar::~Bar()
{
    //dtor
}























