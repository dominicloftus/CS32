#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
class StudentWorld;


class Actor: public GraphObject{
public:
    Actor(int ID, int x, int y, Direction dir, double size, unsigned int depth, StudentWorld* world);
    virtual ~Actor();
    virtual void doSomething() = 0;
    virtual bool isGoodie();
    virtual bool isAnnoyed();
    virtual bool isProtestor();
    
    int getid();
    StudentWorld* getWorld();
    
    bool isAlive();
    virtual void die();
    
    virtual void decHealth(int amt);
    virtual void bribe();
    virtual void annoy();
    
    void moveOneCoord(int x, int y, Direction d);
    
    
    
private:
    StudentWorld* m_world;
    int m_ID;
    bool m_alive;
          
};

class Person: public Actor{
public:
    Person(int ID, int x, int y, Direction dir, double size, unsigned int depth, StudentWorld* world,
           int health);
    virtual ~Person();
    virtual void doSomething() = 0;
    virtual void annoy();
    virtual void die();
    virtual void decHealth(int amt);
    int getHealth();
private:
    int m_health;
};

class TunnelMan: public Person{
public:
    TunnelMan(StudentWorld* world);
    virtual ~TunnelMan();
    virtual void doSomething();
    virtual void annoy();
    virtual void decHealth(int amt);
    void incWater(int amt);
    void incSonar(int amt);
    void incGold(int amt);
    int getWater();
    int getSonar();
    int getGold();
    
private:
    int m_water;
    int m_sonar;
    int m_gold;
};

class Protestor: public Person{
public:
    Protestor(int ID, StudentWorld* world, int health);
    virtual ~Protestor();
    virtual bool isProtestor();
    virtual void doSomething();
    virtual Direction move() = 0;
    virtual void annoy();
    virtual bool isAnnoyed();
    virtual void decHealth(int amt);
    int getTimeBetweenTicks();
    void setRest(int amt);
private:
    bool m_annoyed;
    int m_timeBetweenTicks;
    int m_rest;
    int m_shoutRest;
    int m_nMovesInCurDir;
    int m_nPerpMove;
};

class RegularProtestor: public Protestor{
public:
    RegularProtestor(StudentWorld* world);
    virtual ~RegularProtestor();
    virtual Direction move();
    virtual void bribe();
private:
};

class HardCoreProtestor: public Protestor{
public:
    HardCoreProtestor(StudentWorld* world);
    virtual ~HardCoreProtestor();
    virtual Direction move();
    virtual void bribe();
private:
};


class WaterSquirt: public Actor{
public:
    WaterSquirt(int x, int y, Direction dir, StudentWorld* world);
    virtual ~WaterSquirt();
    virtual void doSomething();
private:
    int m_travelDist;
};

class Boulder: public Actor{
public:
    Boulder(int x, int y, StudentWorld* world);
    virtual ~Boulder();
    virtual void doSomething();
private:
    bool m_stable;
    int m_timer;
};




class Goodie: public Actor{
public:
    Goodie(int ID, int x, int y, StudentWorld* world, bool temp, int life);
    virtual ~Goodie();
    virtual void doSomething();
    virtual void pickUp() = 0;
    virtual bool isGoodie();
    bool isTemporary();
    int getLife();
    void decLife();
private:
    bool m_temporary;
    int m_life;
};

class OilBarrel: public Goodie{
public:
    OilBarrel(int x, int y, StudentWorld* world);
    virtual ~OilBarrel();
    virtual void pickUp();
private:
};


class GoldNugget: public Goodie{
public:
    GoldNugget(int x, int y, StudentWorld* world, bool dropped);
    virtual ~GoldNugget();
    virtual void doSomething();
    virtual void pickUp();
private:
};

class SonarKit: public Goodie{
public:
    SonarKit(StudentWorld* world);
    virtual ~SonarKit();
    virtual void pickUp();
private:
};


class WaterRefill: public Goodie{
public:
    WaterRefill(int x, int y, StudentWorld* world);
    virtual ~WaterRefill();
    virtual void pickUp();
private:
};




class Earth: public Actor{
public:
    Earth(int x, int y, StudentWorld* world);
    virtual ~Earth();
    bool exists();
    bool destroy();
    virtual void doSomething();
private:
    bool m_earth;
};










#endif // ACTOR_H_
