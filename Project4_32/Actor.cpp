#include "Actor.h"
#include "StudentWorld.h"
#include <algorithm>

// Students:  Add code to this file (if you wish), Actor.h, StudentWorld.h, and StudentWorld.cpp




Actor::Actor(int ID, int x, int y, Direction dir, double size, unsigned int depth, StudentWorld* world):
GraphObject(ID, x, y, dir, size, depth){
    if(ID != TID_GOLD && ID != TID_BARREL)
        this->setVisible(true);
    m_world = world;
    m_ID = ID;
    m_alive = true;
}

Actor::~Actor(){
    setVisible(false);
}

bool Actor::isGoodie(){
    return false;
}

bool Actor::isProtestor(){
    return false;
}

bool Actor::isAnnoyed(){
    return false;
}

void Actor::annoy(){}

StudentWorld* Actor::getWorld(){
    return m_world;
}

int Actor::getid(){
    return m_ID;
}

bool Actor::isAlive(){
    return m_alive;
}

void Actor::die(){
    m_alive = false;
}

void Actor::decHealth(int amt){}

void Actor::bribe(){}

void Actor::moveOneCoord(int x, int y, GraphObject::Direction d){
    switch(d){
        case up:
            moveTo(getX(), getY()+1);
            break;
        case down:
            moveTo(getX(), getY()-1);
            break;
        case right:
            moveTo(getX()+1, getY());
            break;
        case left:
            moveTo(getX()-1, getY());
            break;
        default:
            break;
    }
}





Person::Person(int ID, int x, int y, Direction dir, double size, unsigned int depth,
               StudentWorld* world, int health):
Actor(ID, x, y, dir, size, depth, world)
{
    m_health = health;
}

Person::~Person(){}

void Person::die(){
    m_health = 0;
    annoy();
}

void Person::decHealth(int amt){
    m_health -= amt;
    if(m_health <= 0){
        m_health = 0;
        if(getid() == TID_PLAYER)
            getWorld()->playSound(SOUND_PLAYER_GIVE_UP);
        else
            getWorld()->playSound(SOUND_PROTESTER_GIVE_UP);
        annoy();
    }
}

int Person::getHealth(){
    return m_health;
}

void Person::annoy(){}


TunnelMan::TunnelMan(StudentWorld* world):
Person(TID_PLAYER, 30, 60, right, 1, 0, world, 10)
{
    m_water = 5;
    m_sonar = 1;
    m_gold = 0;
}

TunnelMan::~TunnelMan(){}

void TunnelMan::annoy(){
    
    Actor::die();
}

void TunnelMan::decHealth(int amt){
    Person::decHealth(amt);
}

void TunnelMan::incGold(int amt){
    m_gold += amt;
}

void TunnelMan::incSonar(int amt){
    m_sonar += amt;
}

void TunnelMan::incWater(int amt){
    m_water += amt;
}

int TunnelMan::getWater(){
    return m_water;
}

int TunnelMan::getSonar(){
    return m_sonar;
}

int TunnelMan::getGold(){
    return m_gold;
}


void TunnelMan::doSomething(){
    if(!isAlive())
        return;
    bool hasDug = false;
    
    for(int i = getX(); i < getX()+SPRITE_WIDTH; i++)
        for(int j = getY(); j < getY()+SPRITE_HEIGHT; j++)
            if(getWorld()->destroyEarth(i, j))
                hasDug = true;
    if(hasDug)
        getWorld()->playSound(SOUND_DIG);
    int key;
    Direction dir = getDirection();
    if(getWorld()->getKey(key)){
        if(key == KEY_PRESS_ESCAPE){
            decHealth(10);
            return;
        }
        
        if(key == KEY_PRESS_SPACE){
            if(m_water < 1)
                return;
            int potX, potY;
            if(dir == up){
                potX = getX();
                potY = getY()+SPRITE_HEIGHT;
            }
            else if(dir == down){
                potX = getX();
                potY = getY()-SPRITE_HEIGHT;
            }
            else if(dir == right){
                potX = getX()+SPRITE_WIDTH;
                potY = getY();
            }
            else{
                potX = getX()-SPRITE_WIDTH;
                potY = getY();
            }
            if(getWorld()->validSquirtSpawn(potX, potY)){
                getWorld()->addWaterSquirt(potX, potY, dir);
            }
            m_water--;
            getWorld()->playSound(SOUND_PLAYER_SQUIRT);
            return;
        }
        
        if(key == KEY_PRESS_UP){
            if(dir == up && getWorld()->validTunnelManMove(getX(), getY()+1))
                moveTo(getX(), getY()+1);
            setDirection(up);
            return;
        }
        
        if(key == KEY_PRESS_DOWN){
            if(dir == down && getWorld()->validTunnelManMove(getX(), getY()-1))
                moveTo(getX(), getY()-1);
            setDirection(down);
            return;
        }
        
        if(key == KEY_PRESS_RIGHT){
            if(dir == right && getWorld()->validTunnelManMove(getX()+1, getY()))
                moveTo(getX()+1, getY());
            setDirection(right);
            return;
        }
        
        if(key == KEY_PRESS_LEFT){
            if(dir == left && getWorld()->validTunnelManMove(getX()-1, getY()))
                moveTo(getX()-1, getY());
            setDirection(left);
            return;
        }
        
        if(key == 'Z' || key == 'z'){
            if(m_sonar > 0){
                getWorld()->sonarScan(getX(), getY());
                m_sonar--;
            }
            return;
        }
        
        if(key == KEY_PRESS_TAB){
            if(m_gold < 1)
                return;
            getWorld()->addDroppedGold(getX(), getY());
            m_gold--;
            return;
        }
        
        
        
    }
}


Protestor::Protestor(int ID, StudentWorld* world, int health):
Person(ID, 60, 60, left, 1, 0, world, health){
    m_annoyed = false;
    m_timeBetweenTicks = world->max(0, 3-world->getLevel()/4);
    m_rest = m_timeBetweenTicks;
    m_shoutRest = 0;
    m_nPerpMove = 0;
    m_nMovesInCurDir = rand() % 53 + 8;
}

Protestor::~Protestor(){
    Actor::die();
}

bool Protestor::isProtestor(){
    return true;
}

void Protestor::decHealth(int amt){
    Person::decHealth(amt);
    if(getHealth() > 0){
        getWorld()->playSound(SOUND_PROTESTER_ANNOYED);
        setRest(getWorld()->max(50, 100 - 10*getWorld()->getLevel()));
    }
    else setRest(0);
}

void Protestor::doSomething(){
    if(!isAlive())
        return;
    if(m_rest != 0){
        m_rest--;
        return;
    }
    if(m_annoyed){
        Direction dir = getWorld()->optimalMove(getX(), getY());
        setDirection(dir);
        moveOneCoord(getX(), getY(), dir);
        if(getX() == 60 && getY() == 60)
            Actor::die();
        m_rest = m_timeBetweenTicks;
        return;
    }
    if(m_shoutRest <= 0){
        if(getWorld()->shoutAtTunnelMan(getX(), getY(), getDirection())){
            m_shoutRest = 15;
            m_rest = m_timeBetweenTicks;
            m_nPerpMove--;
            return;
        }
    }
    Direction d = move();
    if(d != none){
        if(!getWorld()->onTunnelMan(getX(), getY()))
            setDirection(d);
        if(!getWorld()->inRangeOfTunnelMan(getX(), getY(), 4, true))
            moveOneCoord(getX(), getY(), d);
        m_shoutRest--;
        m_nPerpMove--;
        m_rest = m_timeBetweenTicks;
        return;
    }
    
    d = getWorld()->canSeeTunnelMan(getX(), getY());
    if(d != none){
        if(!getWorld()->onTunnelMan(getX(), getY()))
            setDirection(d);
        if(!getWorld()->inRangeOfTunnelMan(getX(), getY(), 4, true))
            moveOneCoord(getX(), getY(), d);
        m_shoutRest--;
        m_nPerpMove--;
        m_rest = m_timeBetweenTicks;
        m_nMovesInCurDir = 0;
        return;
    }
    
    m_nMovesInCurDir--;
    if(m_nMovesInCurDir <= 0){
        d = getWorld()->pickNewProtDir(getX(), getY());
        setDirection(d);
        m_nMovesInCurDir = rand() % 53 + 8;
    }
    else{
        if(m_nPerpMove <= 0){
            d = getWorld()->perpMove(getX(), getY(), getDirection());
            if(d != none){
                setDirection(d);
                m_nPerpMove = 200;
                m_nMovesInCurDir = rand() % 53 + 8;
            }
        }
    }
    
    d = getDirection();
    switch(d){
        case up:{
            if(getWorld()->validSquirtSpawn(getX(), getY()+1))
                moveOneCoord(getX(), getY(), up);
            else
                m_nMovesInCurDir = 0;
            break;
        }
        case down:{
            if(getWorld()->validSquirtSpawn(getX(), getY()-1))
                moveOneCoord(getX(), getY(), down);
            else
                m_nMovesInCurDir = 0;
            break;
        }
        case right:{
            if(getWorld()->validSquirtSpawn(getX()+1, getY()))
                moveOneCoord(getX(), getY(), right);
            else
                m_nMovesInCurDir = 0;
            break;
        }
        case left:{
            if(getWorld()->validSquirtSpawn(getX()-1, getY()))
                moveOneCoord(getX(), getY(), left);
            else
                m_nMovesInCurDir = 0;
            break;
        }
        default:
            break;
    }
    m_rest = m_timeBetweenTicks;
    m_nPerpMove--;
    m_shoutRest--;
    
    
    
    
    
}

bool Protestor::isAnnoyed(){
    return m_annoyed;
}

void Protestor::annoy(){
    if(getid() == TID_HARD_CORE_PROTESTER)
        getWorld()->increaseScore(250);
    else
        getWorld()->increaseScore(100);
    m_annoyed = true;
}

void Protestor::setRest(int amt){
    m_rest = amt;
}



RegularProtestor::RegularProtestor(StudentWorld* world):
Protestor(TID_PROTESTER, world, 5)
{
    
}

RegularProtestor::~RegularProtestor(){}

Actor::Direction RegularProtestor::move(){
    return none;
}

void RegularProtestor::bribe(){
    getWorld()->playSound(SOUND_PROTESTER_FOUND_GOLD);
    getWorld()->increaseScore(25);
    annoy();
}



HardCoreProtestor::HardCoreProtestor(StudentWorld* world):
Protestor(TID_HARD_CORE_PROTESTER, world, 20)
{
    
}

HardCoreProtestor::~HardCoreProtestor(){}

Actor::Direction HardCoreProtestor::move(){
    return getWorld()->hardCoreFindTunnelMan(getX(), getY(), 16 + getWorld()->getLevel()*2);
}

void HardCoreProtestor::bribe(){
    getWorld()->playSound(SOUND_PROTESTER_FOUND_GOLD);
    getWorld()->increaseScore(50);
    setRest(getWorld()->max(50, 100 - getWorld()->getLevel()*10));
}


WaterSquirt::WaterSquirt(int x, int y, Direction dir, StudentWorld* world):
Actor(TID_WATER_SPURT, x, y, dir, 1, 1, world)
{
    m_travelDist = 0;
}

WaterSquirt::~WaterSquirt(){}

void WaterSquirt::doSomething(){
    if(!isAlive())
        return;
    if(getWorld()->squirtShot(getX(), getY())){
        die();
        return;
    }
    if(m_travelDist == 4){
        die();
        return;
    }
    
    int potX, potY;
    Direction dir = getDirection();
    if(dir == up){
        potX = getX();
        potY = getY()+1;
    }
    else if(dir == down){
        potX = getX();
        potY = getY()-1;
    }
    else if(dir == right){
        potX = getX()+1;
        potY = getY();
    }
    else{
        potX = getX()-1;
        potY = getY();
    }
    if(!getWorld()->validSquirtSpawn(potX, potY)){
        die();
        return;
    }
    moveTo(potX, potY);
    m_travelDist++;
    return;
}

Boulder::Boulder(int x, int y, StudentWorld* world):
Actor(TID_BOULDER, x, y, down, 1, 1, world){
    m_stable = true;
    m_timer = 0;
}

Boulder::~Boulder(){}

void Boulder::doSomething(){
    if(!isAlive())
        return;
    if(m_timer == 30){
        if(getWorld()->boulderRoll(getX(), getY()-1)){
            moveTo(getX(), getY()-1);
            return;
        }
        die();
        return;
    }
    
    if(!m_stable){
        m_timer++;
        if(m_timer == 30)
            getWorld()->playSound(SOUND_FALLING_ROCK);
        return;
    }
    
    if(!getWorld()->checkForEarth(getX(), getY()-1)){
        m_stable = false;
        return;
    }
    
}




Goodie::Goodie(int ID, int x, int y, StudentWorld* world, bool temp, int life):
Actor(ID, x, y, right, 1, 2, world){
    m_temporary = temp;
    m_life = life;
}

Goodie::~Goodie(){}

bool Goodie::isGoodie(){
    return true;
}

bool Goodie::isTemporary(){
    return m_temporary;
}

int Goodie::getLife(){
    return m_life;
}

void Goodie::decLife(){
    m_life--;
}

void Goodie::doSomething(){
    if(!isAlive())
        return;
    if(getWorld()->setGoodieVisible(getX(), getY())){
        setVisible(true);
    }
    if(getWorld()->pickUpGoodie(getX(), getY())){
        pickUp();
    }
    if(m_life == 0){
        die();
        return;
    }
    if(isTemporary()){
        m_life--;
        return;
    }
}



OilBarrel::OilBarrel(int x, int y, StudentWorld* world):
Goodie(TID_BARREL, x, y, world, false, 1){
    
}

OilBarrel::~OilBarrel(){}

void OilBarrel::pickUp(){
    die();
    getWorld()->playSound(SOUND_FOUND_OIL);
    getWorld()->increaseScore(1000);
}

GoldNugget::GoldNugget(int x, int y, StudentWorld* world, bool dropped):
Goodie(TID_GOLD, x, y, world, dropped, 100){

}

GoldNugget::~GoldNugget(){}

void GoldNugget::doSomething(){
    if(!isAlive())
        return;
    if(!isTemporary()){
        Goodie::doSomething();
        return;
    }
    if(getWorld()->bribeProtestor(getX(), getY())){
        die();
        return;
    }
    if(getLife() == 0){
        die();
        return;
    }
    decLife();
}

void GoldNugget::pickUp(){
    if(!isTemporary()){
        die();
        getWorld()->incGold(1);
        getWorld()->playSound(SOUND_GOT_GOODIE);
        getWorld()->increaseScore(10);
    }
}

SonarKit::SonarKit(StudentWorld* world):
Goodie(TID_SONAR, 0, 60, world, true, world->max(100, 300 - 10*world->getLevel())){
    
}

SonarKit::~SonarKit(){}

void SonarKit::pickUp(){
    die();
    getWorld()->incSonar(2);
    getWorld()->playSound(SOUND_GOT_GOODIE);
    getWorld()->increaseScore(75);
}

WaterRefill::WaterRefill(int x, int y, StudentWorld* world):
Goodie(TID_WATER_POOL, x, y, world, true, world->max(100, 300 - 10*world->getLevel())){
    
}

WaterRefill::~WaterRefill(){}

void WaterRefill::pickUp(){
    die();
    getWorld()->incWater(5);
    getWorld()->playSound(SOUND_GOT_GOODIE);
    getWorld()->increaseScore(100);
}






Earth::Earth(int x, int y, StudentWorld* world):
Actor(TID_EARTH, x, y, right, 0.25, 3, world)
{
    m_earth = true;
}

Earth::~Earth(){
    setVisible(false);
}

bool Earth::exists(){
    return m_earth;
}

bool Earth::destroy(){
    if(m_earth){
        m_earth = false;
        setVisible(false);
        return true;
    }
    return false;
}

void Earth::doSomething(){}














