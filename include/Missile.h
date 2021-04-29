#ifndef MISSILE_H
#define MISSILE_H

#define MISSILE_LENGHT 33
#define MISSILE_WIDTH 8
#define MISSILE_SPEED   8
#define COOLDOWN_MISSILE 2

using namespace sf;

class Missile
{
    public:
        Missile(unsigned int px, unsigned int py, unsigned int dx);
        virtual ~Missile();
        sf::Sprite getSprite() const;
        void moveX(float mx);
        void moveY(float my);
        void setDeplacementX(const float dx){m_dx = dx;};
        void setPositionX(const float px);
        void setPositionY(const float py);
        void setMyTimeMissile(const Time t);
        Time getMyTimeMissile() const{return m_myTimeMissile;};
        float getDeplacementX() const{return m_dx;};
        //sf::Clock getClock() const{return m_clock;};
        void resetPositionDepart();
        sf::IntRect getHitBox() const;

    protected:

    private:
        unsigned int m_px;
        unsigned int m_py;
        float m_dx;
        sf::Texture m_texture;
        sf::Sprite m_sprite;
        Time m_myTimeMissile;
};

#endif // MISSILE_H
