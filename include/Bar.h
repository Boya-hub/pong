#ifndef BAR_H
#define BAR_H

#define BAR_LENGHT 51
#define BAR_WIDTH 160
#define VITESSE_BAR 6
#define PX_JOUEUR_1 (FENETRE_LENGHT/10)-(BAR_LENGHT/2)
#define PX_JOUEUR_2 ((FENETRE_LENGHT*9)/10)-(BAR_LENGHT/2)

using namespace sf;

class Bar
{
    public:
        Bar(unsigned int px = 0, unsigned int py = 0, unsigned int dy = 0);
        virtual ~Bar();
        void setTexture(unsigned int joueur);
        sf::Sprite getSprite() const {return m_sprite;};
        void setPositionX(unsigned int px);
        void setPositionY(unsigned int py);
        void moveY(int my);
        unsigned int getPositionY() const {return m_py;};
        sf::IntRect getHitBox() const;
        void setFrozen(bool b);
        bool isFrozen() const;
        void setColorSprite(Color color);
        void setTimeGotFreeze(Time t);
        Time getTimeGotFreeze() const{return m_timeGotFreeze;};
        Clock getClock() const{return m_clock;};

    protected:
        unsigned int m_px;
        unsigned int m_py;
        unsigned int m_dy;
        sf::Texture m_texture;
        sf::Sprite m_sprite;
        bool m_frozen;
        Clock m_clock;
        Time m_timeGotFreeze;

    private:
};

#endif // BAR_H
