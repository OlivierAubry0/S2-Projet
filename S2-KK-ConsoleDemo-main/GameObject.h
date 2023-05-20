#include "Hitbox.h"
#include <string>
#include <iostream>
#include "coords.h"

#pragma once

enum GameObjectType {
    Obstacle, Ennemy, Player, Powerup
};
class GameObject {
private:
    Hitbox hitbox;
    char symbol;
    GameObjectType type;
    //bool isObstacle;
public:
    bool hidden = false;
    GameObject();
    //GameObject(Hitbox htb, char smb, bool obst = false);
    GameObject(Hitbox htb, char smb, GameObjectType typ = GameObjectType::Ennemy);
    bool touch(const GameObject& gameObject);
    bool touch(const Coords&);
    bool obstacle();
    bool PowerUp();
    bool move(Coords delta);
    Coords getPosition();
    void display(int y, std::string&);
};