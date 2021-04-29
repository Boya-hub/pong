#ifndef BALL_H
#define BALL_H

#define BALL_LENGHT 45
#define BALL_WIDTH 45

using namespace sf;

class Ball
{
    public:
        Ball(unsigned int px = (FENETRE_LENGHT-BALL_LENGHT)/2, unsigned int py = (FENETRE_WIDTH-BALL_WIDTH)/2, float dx = 5, float dy = 1);
        virtual ~Ball();
        unsigned int getPositionX() const{return m_px;};
        unsigned int getPositionY() const{return m_py;};
        void setDeplacementX(const float dx){m_dx = dx;};
        void setDeplacementY(const float dy){m_dy = dy;};
        float getDeplacementX() const{return m_dx;};
        float getDeplacementY() const{return m_dy;};
        sf::Sprite getSprite() const;
        void moveX(float mx);
        void moveY(float my);
        sf::IntRect getHitBox() const;
        void invertDX(){m_dx *= -1;};
        void invertDY(){m_dy *= -1;};
        void resetPos();
        void resetDeplacement();

    protected:
        unsigned int m_px;
        unsigned int m_py;
        float m_dx;
        float m_dy;
        sf::Texture m_texture;
        sf::Sprite m_sprite;
    private:
};

#endif // BALL_H
