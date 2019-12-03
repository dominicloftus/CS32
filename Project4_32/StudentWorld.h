#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include "Actor.h"
#include <string>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <algorithm>



// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
	StudentWorld(std::string assetDir)
		: GameWorld(assetDir)
	{
	}
    ~StudentWorld();

    virtual int init();

    virtual int move();
    
    virtual void cleanUp();
    
    int max(int a, int b);
    
    int min(int a, int b);
    
    void displayScore(int numOil);
    
    void randomSpawnPoint(int& x, int &y);
    
    bool validObjectSpawn(int x, int y);
    
    bool destroyEarth(int x, int y);
    
    bool earthExists(int x, int y);
    
    bool checkOverlap(int x1, int y1, int x2, int y2);
    
    bool inRadiusOf(int x1, int y1, int x2, int y2, double r, bool incl);
    
    bool checkForEarth(int x, int y);
    
    bool checkInBounds(int x, int y);
    
    bool checkForObject(int x, int y, int ID);
    
    bool validTunnelManMove(int x, int y);
    
    bool validSquirtSpawn(int x, int y);
    
    void sonarScan(int x, int y);
    
    void addWaterSquirt(int x, int y, Actor::Direction dir);
    
    void addDroppedGold(int x, int y);
    
    bool boulderRoll(int x, int y);
    
    bool squirtShot(int x, int y);
    
    bool pickUpGoodie(int x, int y);
    
    bool setGoodieVisible(int x, int y);
    
    bool bribeProtestor(int x, int y);
    
    void incWater(int amt);
    
    void incSonar(int amt);
    
    void incGold(int amt);
    
    Actor::Direction optimalMove(int x, int y);
    
    bool shoutAtTunnelMan(int x, int y, Actor::Direction dir);
    
    Actor::Direction canSeeTunnelMan(int x, int y);
    
    Actor::Direction pickNewProtDir(int x, int y);
    
    Actor::Direction perpMove(int x, int y, Actor::Direction dir);
    
    bool inRangeOfTunnelMan(int x, int y, int r, bool incl);
    
    bool onTunnelMan(int x, int y);
    
    Actor::Direction hardCoreFindTunnelMan(int x, int y, int range);

private:
    std::vector<Actor*> m_actors;
    Earth* m_earth[VIEW_HEIGHT][VIEW_WIDTH];
    TunnelMan* m_tunnelMan;
    int m_newProtestor;
    int m_protestorTick;
    int m_maxProtestors;
    int m_hardCoreProb;
    int m_goodieProb;
    
    struct Coord{
        Actor::Direction m_dir;
        int m_x;
        int m_y;
        Coord(Actor::Direction d, int x, int y):
        m_dir(d), m_x(x), m_y(y){}
    };
};

#endif // STUDENTWORLD_H_
