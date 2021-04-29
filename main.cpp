#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "main.h"
#include "ball.h"
#include "Bar.h"
#include "Missile.h"
#include "DynamicMenu.h"
#include "CollisionManager.h"
#include <SFML/Audio/Music.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

/*NOTES
Très peu de commentaire.
J'ai confondu les height avec les lenghts du coup c'est un peu n'importe quoi entre tout ça.
*/

using namespace sf;

const Vector2f WINDOW_SIZE(FENETRE_LENGHT, FENETRE_WIDTH);

int main()
{
    Event event;
    Clock clock;
    Music musicFond;
    std::vector<SoundBuffer> buffers(4); //0 = ping, 1 = pong, 2 = pew, 3 = bim
    std::vector<Sound> sounds(4);

    DynamicMenu splashScreen(FENETRE_LENGHT, FENETRE_WIDTH, 32, "Pong !");
    splashScreen.setFramerateLimit(100);
    splashScreen.setVerticalSyncEnabled(true);
    Font font;
    int scoreJoueur1 = 0;
    int scoreJoueur2 = 0;
    int i = 0;
    Text textScore("0 - 0", font, 30);
    Text textCooldownJoueur1("0", font, 25);
    textCooldownJoueur1.setFillColor(sf::Color::Red);
    Text textCooldownJoueur2("0", font, 25);
    textCooldownJoueur2.setFillColor(sf::Color::Blue);
    char scores[15] = "";
    char cooldownJoueur1 = '0';
    char cooldownJoueur2 = '0';
    bool lockScore = false;
    textScore.setPosition(FENETRE_LENGHT / 2 - 50, FENETRE_WIDTH/10);
    textCooldownJoueur1.setPosition(40, FENETRE_WIDTH-50);
    textCooldownJoueur2.setPosition(FENETRE_LENGHT - 65, FENETRE_WIDTH - 50);

    if(!font.loadFromFile("./data/fonts/Sunday Best.ttf"))
       return -2;
    Text text1("P", font, 30);
    Text text2("O", font, 30);
    Text text3("N", font, 30);
    Text text4("G", font, 30);
    text1.setFillColor(Color::Magenta);
    text2.setFillColor(Color::Cyan);
    text3.setFillColor(Color::Yellow);
    text4.setFillColor(Color::Green);

    text1.setPosition(-30,FENETRE_WIDTH/3);
    text2.setPosition(FENETRE_LENGHT/2 - 20,-30);
    text3.setPosition(FENETRE_LENGHT + 1,FENETRE_WIDTH/3);
    text4.setPosition(FENETRE_LENGHT/2 + 20,FENETRE_WIDTH + 1);

    //Gestion de la musique
    if (!musicFond.openFromFile("./data/musics/Pr_kliq.ogg"))
        return -1; // error
    musicFond.setLoop(true);
    musicFond.setVolume(5);
    musicFond.play();
    if (!buffers[0].loadFromFile("./data/musics/ping.wav"))
        return -1; // error
    if (!buffers[1].loadFromFile("./data/musics/pong.wav"))
        return -1; // error
    if (!buffers[2].loadFromFile("./data/musics/pew.wav"))
        return -1; // error
    if (!buffers[3].loadFromFile("./data/musics/bim_bam_boum.wav"))
        return -1; // error
    sounds[3].setVolume(25);
    for(i = 0; i < 4; i++)
        sounds[i].setBuffer(buffers[i]);

    while(splashScreen.isOpen()){
        while (splashScreen.pollEvent(event))
        {
            if(event.type == Event::Closed){
                splashScreen.close();
                return EXIT_SUCCESS;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                splashScreen.close();
        }
        if(text1.getPosition().x < FENETRE_LENGHT/2 - 40)
            text1.move(4,0);
        if(text2.getPosition().y < FENETRE_WIDTH/3)
            text2.move(0,4);
        if(text3.getPosition().x >= FENETRE_LENGHT/2)
            text3.move(-4,0);
        if(text4.getPosition().y >= FENETRE_WIDTH/3)
            text4.move(0,-4);
        splashScreen.clear();
        splashScreen.draw(text1);
        splashScreen.draw(text2);
        splashScreen.draw(text3);
        splashScreen.draw(text4);
        splashScreen.display();
    }

    RenderWindow app(VideoMode(FENETRE_LENGHT, FENETRE_WIDTH, 32), "Pong !");
    // Boucle principale
    app.setFramerateLimit(100);
    app.setVerticalSyncEnabled(true);
    app.setKeyRepeatEnabled(false);

    bool gamePaused = false;
    bool premierTirJoueur1 = false;
    bool premierTirJoueur2 = false;

    Ball ball;
    Bar joueur1;
    Bar joueur2;
    Missile missileJoueur1(-40, -10, 0);
    Missile missileJoueur2(-40, -10, 0);

    CollisionManager collisionManager(ball, joueur1, joueur2, missileJoueur1, missileJoueur2, WINDOW_SIZE);

    joueur1.setTexture(1);
    joueur1.setPositionX(PX_JOUEUR_1);
    joueur1.setPositionY((FENETRE_WIDTH-BAR_WIDTH)/2);
    joueur2.setTexture(2);
    joueur2.setPositionX(PX_JOUEUR_2);
    joueur2.setPositionY((FENETRE_WIDTH-BAR_WIDTH)/2);
    while (app.isOpen())
    {
        while (app.pollEvent(event))
        {
            if(event.type == Event::Closed)
                app.close();
        }

        //Gestion des evenements
        if(gamePaused && sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
           gamePaused = false;
           lockScore = false;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)
           && ((clock.getElapsedTime().asSeconds() - missileJoueur1.getMyTimeMissile().asSeconds() > COOLDOWN_MISSILE) || !premierTirJoueur1) && !(joueur1.isFrozen())){        //Joueur1
            sounds[2].play();
            premierTirJoueur1 = true;
            missileJoueur1.setMyTimeMissile(clock.getElapsedTime());
            missileJoueur1.setPositionX(PX_JOUEUR_1 + BAR_LENGHT);
            missileJoueur1.setPositionY(joueur1.getPositionY() + BAR_WIDTH/2 - MISSILE_WIDTH/2);
            missileJoueur1.setDeplacementX(MISSILE_SPEED);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad0)
           && ((clock.getElapsedTime().asSeconds() - missileJoueur2.getMyTimeMissile().asSeconds() > COOLDOWN_MISSILE) || !premierTirJoueur2) && !(joueur2.isFrozen())){        //Joueur2
            sounds[2].play();
            premierTirJoueur2 = true;
            missileJoueur2.setMyTimeMissile(clock.getElapsedTime());
            missileJoueur2.setPositionX(PX_JOUEUR_2 - BAR_LENGHT + 15);
            missileJoueur2.setPositionY(joueur2.getPositionY()+ BAR_WIDTH/2 - MISSILE_WIDTH/2);
            missileJoueur2.setDeplacementX(-MISSILE_SPEED);
        }

        //Gestion de l'affichage du cooldown du missile
        if((COOLDOWN_MISSILE - ((int)(clock.getElapsedTime().asSeconds() - missileJoueur1.getMyTimeMissile().asSeconds())) > 0) && premierTirJoueur1)
            sprintf(&cooldownJoueur1, "%d", (COOLDOWN_MISSILE - ((int)(clock.getElapsedTime().asSeconds() - missileJoueur1.getMyTimeMissile().asSeconds()))));
        else
            cooldownJoueur1 = '0';
        textCooldownJoueur1.setString(cooldownJoueur1);
        if((COOLDOWN_MISSILE - ((int)(clock.getElapsedTime().asSeconds() - missileJoueur2.getMyTimeMissile().asSeconds())) > 0) && premierTirJoueur1)
            sprintf(&cooldownJoueur2, "%d", (COOLDOWN_MISSILE - ((int)(clock.getElapsedTime().asSeconds() - missileJoueur2.getMyTimeMissile().asSeconds()))));
        else
            cooldownJoueur2 = '0';
        textCooldownJoueur2.setString(cooldownJoueur2);

        //Gestion des deplacements/collisions/affichages
        if(!gamePaused)
            collisionManager.manageCollisionY(gamePaused, sounds);
        if(!gamePaused){        //Si le jeu en pause, on gèle tout
            // Remplissage de l'écran (couleur noire par défaut)
            app.clear();

            //Manage/Collision X
            collisionManager.manageCollisionX(clock, sounds);
            //---------------------------Gestion du frozen------------------------------------
            if(joueur1.isFrozen()){
                if(clock.getElapsedTime().asSeconds() - joueur1.getTimeGotFreeze().asSeconds() > 2){
                    joueur1.setFrozen(false);
                    joueur1.setColorSprite(sf::Color::White);
                }
            }
            else{
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
                    joueur1.moveY(-VITESSE_BAR);
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                    joueur1.moveY(VITESSE_BAR);
            }
            if(joueur2.isFrozen()){
                if(clock.getElapsedTime().asSeconds() - joueur2.getTimeGotFreeze().asSeconds() > 2){
                    joueur2.setFrozen(false);
                    joueur2.setColorSprite(sf::Color::White);
                }
            }
            else{
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                    joueur2.moveY(-VITESSE_BAR);
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                    joueur2.moveY(VITESSE_BAR);
            }

            missileJoueur1.moveX(missileJoueur1.getDeplacementX());
            missileJoueur2.moveX(missileJoueur2.getDeplacementX());

            ball.moveX(ball.getDeplacementX());
            ball.moveY(ball.getDeplacementY());
        }
        else{
            app.clear();
            if(!lockScore){
                lockScore = true;       //On évite de changer en boucle
                if(ball.getPositionX() > FENETRE_LENGHT/2)
                    scoreJoueur1++;
                else
                    scoreJoueur2++;
            }
            sprintf(scores, "%d - %d", scoreJoueur1, scoreJoueur2);
            textScore.setString(scores);

            //Ball
            ball.resetPos();
            ball.resetDeplacement();

            //Joueur1
            joueur1.setPositionX((FENETRE_LENGHT/10)-(BAR_LENGHT/2));
            joueur1.setPositionY((FENETRE_WIDTH-BAR_WIDTH)/2);
            joueur1.setFrozen(false);
            joueur1.setColorSprite(sf::Color::White);

            //Joueur2
            joueur2.setPositionX(((FENETRE_LENGHT*9)/10)-(BAR_LENGHT/2));
            joueur2.setPositionY((FENETRE_WIDTH-BAR_WIDTH)/2);
            joueur2.setFrozen(false);
            joueur2.setColorSprite(sf::Color::White);

            //Missile
            missileJoueur1.resetPositionDepart();
            missileJoueur2.resetPositionDepart();
            premierTirJoueur1 = false;
            premierTirJoueur2 = false;
        }

        app.draw(joueur1.getSprite());
        app.draw(joueur2.getSprite());
        app.draw(ball.getSprite());
        app.draw(textScore);
        app.draw(textCooldownJoueur1);
        app.draw(textCooldownJoueur2);
        app.draw(missileJoueur1.getSprite());
        app.draw(missileJoueur2.getSprite());
        // Affichage de la fenêtre à l'écran
        app.display();
    }

    return EXIT_SUCCESS;
}
