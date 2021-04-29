#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include <SFML/Audio/Sound.hpp>

using namespace sf;

class CollisionManager
{
    public:
        CollisionManager(Ball & ball, Bar& bar1, Bar& bar2, Missile& missile1, Missile& missile2, sf::Vector2f windowSize);
        virtual ~CollisionManager();

        void manageCollisionX(Clock clock, std::vector<Sound> & tabSons);
        void manageCollisionY();
        void manageCollisionY(bool& pause);
        void manageCollisionY(bool& pause, std::vector<Sound> & tabSons);

    protected:
        Ball& m_ball;
        Bar &m_bar1, &m_bar2;
        Missile &m_missile1, &m_missile2;

        sf::Vector2f m_windowSize;
    private:
};

//Verifie si la hitbox de la balle touche la fenetre et retourne le mur en question
// return 1 = mur gauche, return 2 = mur haut, return 3 = mur droite, return 4 = mur bas
//retourn 0 si pas de collision
int collisionFenetre(const IntRect& ball,const Vector2f& fenetre);
int getHitPoint(IntRect& bar, IntRect& ball);        //Trouver la distance du point de hit depuis le milieu de la barre
double getAngle(int distance, IntRect& ball, IntRect& bar);                  //Trouver l'angle de direction de la balle d'apres une position depuis le centre de la barre
#endif // COLLISIONMANAGER_H
