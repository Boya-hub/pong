#include <SFML/Audio/Sound.hpp>
#include <cstdlib>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "../main.h"
#include "ball.h"
#include "Bar.h"
#include "Missile.h"
#include "CollisionManager.h"

CollisionManager::CollisionManager(Ball& ball, Bar& bar1, Bar& bar2, Missile& missile1, Missile& missile2, sf::Vector2f windowSize):
    m_ball(ball), m_bar1(bar1), m_bar2(bar2), m_windowSize(windowSize), m_missile1(missile1), m_missile2(missile2)
{

}

void CollisionManager::manageCollisionX(Clock clock, std::vector<Sound> & tabSons)
{
    int ret = 0;
    float distance = 0;
    double angle = 0;
    float deplacement = 0;
    double temp = 0.0;
    IntRect hitBoxBall = m_ball.getHitBox();
    IntRect hitBoxBar1 = m_bar1.getHitBox();
    IntRect hitBoxBar2 = m_bar2.getHitBox();
    IntRect hitBoxMiss1 = m_missile1.getHitBox();
    IntRect hitBoxMiss2 = m_missile2.getHitBox();

    //Gestion collision entre balle et barre
    if(hitBoxBall.intersects(hitBoxBar1)){
        distance = getHitPoint(hitBoxBar1, hitBoxBall);
        angle = getAngle(labs(distance), hitBoxBall, hitBoxBar1);

        temp = cos((angle * M_PI)/180);
        deplacement = fabs(8 * temp);
        if(m_ball.getDeplacementX() >= 0)
            m_ball.setDeplacementX(-1 * deplacement);
        else
            m_ball.setDeplacementX(deplacement);

        temp = sin((angle * M_PI)/180);
        deplacement = fabs(8 * temp);
        if(m_ball.getDeplacementY() < 0)
            m_ball.setDeplacementY(-1 * deplacement);          //y = sqrt(8^2- x^2)        => 8 car on veut garder notre vecteur vitesse a 8
        else
            m_ball.setDeplacementY(deplacement);          //y = sqrt(8^2- x^2)        => 8 car on veut garder notre vecteur vitesse a 8

        m_ball.moveX(8);
        tabSons[1].play();
    }
    if(hitBoxBall.intersects(hitBoxBar2)){
        distance = getHitPoint(hitBoxBar2, hitBoxBall);
        angle = getAngle(labs(distance), hitBoxBall, hitBoxBar2);

        temp = cos((angle * M_PI)/180);
        deplacement = fabs(8 * temp);
        if(m_ball.getDeplacementX() >= 0)
            m_ball.setDeplacementX(-1 * deplacement);
        else
            m_ball.setDeplacementX(deplacement);

        temp = sin((angle * M_PI)/180);
        deplacement = fabs(8 * temp);
        if(m_ball.getDeplacementY() < 0)
            m_ball.setDeplacementY(-1 * deplacement);          //y = sqrt(8^2- x^2)        => 8 car on veut garder notre vecteur vitesse a 8
        else
            m_ball.setDeplacementY(deplacement);          //y = sqrt(8^2- x^2)        => 8 car on veut garder notre vecteur vitesse a 8

        m_ball.moveX(-8);
        tabSons[0].play();
    }

    //Collision bar joueur1 avec la fenetre
    ret = collisionFenetre(hitBoxBar1, m_windowSize);
    if(ret == 2)
        m_bar1.setPositionY(14);
    if(ret == 4)
        m_bar1.setPositionY(FENETRE_WIDTH - BAR_WIDTH);

    //Collision bar joueur2 avec la fenetre
    ret = collisionFenetre(hitBoxBar2, m_windowSize);
    if(ret == 2)
        m_bar2.setPositionY(14);
    if(ret == 4)
        m_bar2.setPositionY(FENETRE_WIDTH - BAR_WIDTH);

    //Collision entre la balle et la fenetre
    ret = collisionFenetre(hitBoxBall, m_windowSize);
    if(ret == 2 || ret == 4)
        m_ball.invertDY();

    //Collision entre le missile 1 et la bar 2
    if(hitBoxMiss1.intersects(hitBoxBar2)){
        m_bar2.setFrozen(true);
        m_bar2.setColorSprite(Color(252, 10, 3, 255));
        m_bar2.setTimeGotFreeze(clock.getElapsedTime());
        m_missile1.resetPositionDepart();
    }

    //Collision entre le missile 2 et la bar 1
    if(hitBoxMiss2.intersects(hitBoxBar1)){
        m_bar1.setFrozen(true);
        m_bar1.setColorSprite(Color(1, 24, 235, 255));
        m_bar1.setTimeGotFreeze(clock.getElapsedTime());
        m_missile2.resetPositionDepart();
    }
}

void CollisionManager::manageCollisionY()
{
    IntRect hitBoxBall = m_ball.getHitBox();

    //Puisque les bars sont vertical ont n'inverse jamais sur l'axe Y lors d'une collision
    //On part du principe que les tranches des bars sont d'épaisseur nul.

    int ret = 0;
    ret = collisionFenetre(hitBoxBall, m_windowSize);
    if(ret == 1 || ret == 3)
        m_ball.invertDX();
}

void CollisionManager::manageCollisionY(bool& pause)
{
    int ret = 0;
    IntRect hitBoxBall = m_ball.getHitBox();

    //Puisque les bars sont vertical ont n'inverse jamais sur l'axe Y lors d'une collision
    //On part du principe que les tranches des bars sont d'épaisseur nul.

    ret = collisionFenetre(hitBoxBall, m_windowSize);
    if(ret == 1 || ret == 3)
        pause = true;
}

void CollisionManager::manageCollisionY(bool& pause, std::vector<Sound> & tabSons)
{
    int ret = 0;
    IntRect hitBoxBall = m_ball.getHitBox();

    //Puisque les bars sont vertical ont n'inverse jamais sur l'axe Y lors d'une collision
    //On part du principe que les tranches des bars sont d'épaisseur nul.

    ret = collisionFenetre(hitBoxBall, m_windowSize);
    if(ret == 1 || ret == 3){
        tabSons[3].play();
        pause = true;
    }
}
CollisionManager::~CollisionManager()
{
    //dtor
}

int collisionFenetre(const IntRect& ball, const Vector2f& fenetre)
{
    if(ball.left <= 0)
        return 1;
    else if(ball.top <= 0)
        return 2;
    else if((ball.left + ball.width) > fenetre.x)
        return 3;
    else if((ball.top + ball.height) > fenetre.y)
        return 4;
    else
        return 0;
}

int getHitPoint(IntRect& bar, IntRect& ball)
{
    //return (bar.getPositionY() + BAR_WIDTH/2) - (ball.getPositionY() + BALL_WIDTH/2);
    return (bar.top + bar.height/2) - (ball.top + ball.height/2);
}

double getAngle(int distance, IntRect& ball, IntRect& bar)
{
    double angleMax = 60;
    double angleMin = 0;
    double distMax = (bar.height/2) + ball.height;
    double distMin = 0;

    return(((angleMax - angleMin)/((distMax/(distMin+1)+1))) * distance);
}


