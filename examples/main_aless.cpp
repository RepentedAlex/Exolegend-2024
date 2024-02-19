#include "gladiator.h"
Gladiator* gladiator;
void reset();

void setup() {
    //instanciation de l'objet gladiator
    gladiator = new Gladiator();
    //enregistrement de la fonction de reset qui s'éxecute à chaque fois avant qu'une partie commence
    gladiator->game->onReset(&reset); // GFA 4.4.1
}

//Fait tourner le robot sur la gauche jusqu'à un angle `target` grâce à `rotate_left`
void get_rotate_left(double target)
{
    double actual = gladiator->robot->getData().position.a;
    //rotate_left
    while (gladiator->robot->getData().position.a )
}

//Fait pivoter le robot sur la gauche
void rotate_left()
{  
    gladiator->control->setWheelSpeed(WheelAxis::LEFT, -0.1);
    gladiator->control->setWheelSpeed(WheelAxis::RIGHT, 0.1);
}

//Fait pivoter le robot sur la droite
void rotate_right()
{  
    gladiator->control->setWheelSpeed(WheelAxis::LEFT, 0.1);
    gladiator->control->setWheelSpeed(WheelAxis::RIGHT, -0.1);
}

void move_forward()
{
    gladiator->control->setWheelSpeed(WheelAxis::LEFT, 0.6);
    gladiator->control->setWheelSpeed(WheelAxis::RIGHT, 0.6);
}

void reset() {
    //fonction de reset:
    //initialisation de toutes vos variables avant le début d'un match
    gladiator->log("Call of reset function"); // GFA 4.5.1
}

void loop() {
    if(gladiator->game->isStarted()) { //tester si un match à déjà commencer
        //code de votre stratégie
        // move_forward();
        get_rotate_left(gladiator->robot->getData().position.a);
        // gladiator->log("Hello world - Game Started"); // GFA 4.5.1
        RobotData data = gladiator->robot->getData();
       // gladiator->log("%f\n", gladiator->robot->getData().position.a);
        //Position position = data.position;
    }else {
        gladiator->log("Hello world - Game not Startd yet"); // GFA 4.5.1
    }
    delay(300);
}