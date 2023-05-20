#include "GameObject.h"

GameObject::GameObject()
{
    symbol = '\0';
    hitbox = Hitbox({0,0},"\0");
    type = GameObjectType::Ennemy;
    //isObstacle = false;
}
 GameObject::GameObject(Hitbox htb, char smb, GameObjectType typ)
 {
    symbol=smb;
    hitbox=htb;
    type = typ;

    //isObstacle=obst;
    
 }
bool GameObject::touch(const GameObject& gameObject){
    return hitbox.touch(gameObject.hitbox);
}

bool GameObject::touch(const Coords& coords)
{
    return hitbox.touch(coords);
}


bool GameObject::move(Coords delta)
{
    return hitbox.move(delta);
}

bool GameObject::obstacle(){
    
    return type == Obstacle;
}
bool GameObject::PowerUp(){
    return type == Powerup;
}
Coords GameObject::getPosition() 
{
    return hitbox.getPosition();
}
void GameObject::display(int y, std::string& str) 
{
    if (hidden) return;
    hitbox.display(symbol, y, str);
}