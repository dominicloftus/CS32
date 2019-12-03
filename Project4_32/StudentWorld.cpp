#include "StudentWorld.h"
#include <string>
#include <cmath>
#include <queue>
#include <sstream>
using namespace std;

GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}

// Students:  Add code to this file (if you wish), StudentWorld.h, Actor.h and Actor.cpp


StudentWorld::~StudentWorld(){
}


int StudentWorld::init()
{
    m_newProtestor = max(25, 200 - getLevel());
    m_protestorTick = 0;
    m_maxProtestors = min(15, 2 + getLevel() * 1.5);
    m_hardCoreProb = min(90, getLevel() * 10 + 30);
    m_goodieProb = getLevel() * 25 + 300;
    
    for(int i = 0; i < 64; i++)
        for(int j = 0; j < 64; j++)
            m_earth[i][j] = new Earth(i,j,this);
    for(int i = 63; i > 59; i--)
        for(int j = 0; j < 64; j++)
            m_earth[j][i]->destroy();
    for(int i = 59; i > 3; i--)
        for(int j = 30; j < 34; j++)
            m_earth[j][i]->destroy();
    for(int i = 0; i < 64; i++)
        for(int j = 0; j < 64; j++){
            if(!m_earth[i][j]->exists()){
                m_earth[i][j]->setVisible(false);
            }
        }
    
    m_tunnelMan = new TunnelMan(this);
    
    for(int i = 0; i < min(getLevel()/2 + 2, 9); i++){
        bool goodSpawn = false;
        while(!goodSpawn){
            int potX, potY;
            randomSpawnPoint(potX, potY);
            if(validObjectSpawn(potX, potY) && potY > 19){
                Actor* boulder = new Boulder(potX, potY, this);
                m_actors.push_back(boulder);
                for(int i = potX; i < potX+4; i++)
                    for(int j = potY; j < potY+4; j++)
                        m_earth[i][j]->destroy();
                goodSpawn = true;
            }
        }
    }
    
    for(int i = 0; i < max(5-getLevel() / 2, 2); i++){
        bool goodSpawn = false;
        while(!goodSpawn){
            int potX, potY;
            randomSpawnPoint(potX, potY);
            if(validObjectSpawn(potX, potY)){
                Actor* gold = new GoldNugget(potX, potY, this, false);
                m_actors.push_back(gold);
                goodSpawn = true;
            }
        }
    }
    
    for(int i = 0; i < min(2 + getLevel(), 21); i++){
        bool goodSpawn = false;
        while(!goodSpawn){
            int potX, potY;
            randomSpawnPoint(potX, potY);
            if(validObjectSpawn(potX, potY)){
                Actor* oil = new OilBarrel(potX, potY, this);
                m_actors.push_back(oil);
                goodSpawn = true;
            }
        }
    }
    return GWSTATUS_CONTINUE_GAME;
}


int StudentWorld::move()
{
    m_tunnelMan->doSomething();
    for(int i = 0; i < m_actors.size(); i++){
        m_actors[i]->doSomething();
    }
    
    
    for(int i = 0; i < m_actors.size(); i++){
        if(!m_actors[i]->isAlive()){
            delete m_actors[i];
            m_actors.erase(m_actors.begin() + i);
            i--;
        }
    }
    
    int numOil = 0;
    for(int i = 0; i < m_actors.size(); i++){
        if(m_actors[i]->getid() == TID_BARREL)
            numOil++;
    }
    
    if(numOil == 0)
        return GWSTATUS_FINISHED_LEVEL;
    
    displayScore(numOil);
    
    if(m_tunnelMan->getHealth() == 0){
        decLives();
        return GWSTATUS_PLAYER_DIED;
    }
    
    int numProtestors = 0;
    for(int i = 0; i < m_actors.size(); i++){
        if(m_actors[i]->isProtestor())
            numProtestors++;
    }
    
    if(m_protestorTick <= 0 && numProtestors <= m_maxProtestors){
        if((rand() % 100 + 1) <= m_hardCoreProb){
            Actor* prot = new HardCoreProtestor(this);
            m_actors.push_back(prot);
        }
        else{
            Actor* prot = new RegularProtestor(this);
            m_actors.push_back(prot);
        }
        m_protestorTick = m_newProtestor;
    }
    
    if(rand() % m_goodieProb == 0){
        if(rand() % 5 == 0){
            Actor* sonar = new SonarKit(this);
            m_actors.push_back(sonar);
        }
        else{
            bool goodSpawn = false;
            while(!goodSpawn){
                int potX, potY;
                randomSpawnPoint(potX, potY);
                if(validObjectSpawn(potX, potY) && !checkForEarth(potX, potY)){
                    Actor* water = new WaterRefill(potX, potY, this);
                    m_actors.push_back(water);
                    goodSpawn = true;
                }
            }
        }
    }
    
    
    
    m_protestorTick--;
    
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
    for(int i = 0; i < 64; i++){
        for(int j = 0; j < 64; j++){
            delete m_earth[i][j];
        }
    }
    while(m_actors.size() != 0){
        delete m_actors[0];
        m_actors.erase(m_actors.begin());
    }
    delete m_tunnelMan;
}

void StudentWorld::displayScore(int numOil){
    int level = getLevel();
    int lives = getLives();
    int health = m_tunnelMan->getHealth();
    int water = m_tunnelMan->getWater();
    int gold = m_tunnelMan->getGold();
    int oil = numOil;
    int sonar = m_tunnelMan->getSonar();
    int score = getScore();
    ostringstream oss;
    oss << "Lvl: ";
    if(level < 10)
        oss << " ";
    oss << level << "  ";
    oss << "Lives: " << lives << "  ";
    oss << "Hlth: ";
    if(health < 10)
        oss << " ";
    oss << health << "0%  ";
    oss << "Wtr: ";
    if(water < 10)
        oss << " ";
    oss << water << "  ";
    oss << "Gld: ";
    if(gold < 10)
        oss << " ";
    oss << gold << "  ";
    oss << "Oil Left: ";
    if(oil < 10)
        oss << " ";
    oss << oil << "  ";
    oss << "Sonar: ";
    if(sonar < 10)
        oss << " ";
    oss << sonar << "  ";
    oss << "Scr: ";
    if(score > 999999)
        oss << "999999";
    else{
        int n = 100000;
        while(n != 1 && score/n == 0){
            oss << "0";
            n /= 10;
        }
        oss << score;
    }
    setGameStatText(oss.str());
}

void StudentWorld::randomSpawnPoint(int& potX, int& potY){
    int side = rand() % 2;
    if(side == 0){
        potX = rand() % 27;
        potY = rand() % 57;
    }
    else{
        potX = rand() % 27 + 34;
        potY = rand() % 57;
    }
}

bool StudentWorld::validObjectSpawn(int x, int y){
    for(int i = 0; i < m_actors.size(); i++){
        if(m_actors[i]->isGoodie() || m_actors[i]->getid() == TID_BOULDER)
            if(inRadiusOf(x, y, m_actors[i]->getX(), m_actors[i]->getY(), 6, false))
                return false;
    }
    return true;
}


int StudentWorld::max(int a, int b){
    if(a > b)
        return a;
    return b;
}

int StudentWorld::min(int a, int b){
    if(a < b)
        return a;
    return b;
}


bool StudentWorld::destroyEarth(int x, int y){
    return m_earth[x][y]->destroy();
}

bool StudentWorld::earthExists(int x, int y){
    return m_earth[x][y]->exists();
}

bool StudentWorld::checkOverlap(int x1, int y1, int x2, int y2){
    int diffX = x2 - x1;
    int diffY = y2 - y1;
    if(diffX < SPRITE_WIDTH && diffX > -SPRITE_WIDTH && diffY < SPRITE_HEIGHT && diffY > -SPRITE_HEIGHT)
        return true;
    return false;
}

bool StudentWorld::inRadiusOf(int x1, int y1, int x2, int y2, double r, bool inc){
    int a = x1 - x2;
    a *= a;
    int b = y1 - y2;
    b *= b;
    int rad = sqrt(a+b);
    if(inc){
        if(rad <= r)
            return true;
        return false;
    }
    if(rad < r)
        return true;
    return false;
}

bool StudentWorld::checkForEarth(int x, int y){
    for(int i = x; i < x+SPRITE_WIDTH; i++)
        for(int j = y; j < y+SPRITE_HEIGHT; j++)
            if(m_earth[i][j]->exists())
                return true;
    return false;
}

bool StudentWorld::checkInBounds(int x, int y){
    if(x < 0 || x > 60 || y < 0 || y > 60)
        return false;
    return true;
}

bool StudentWorld::checkForObject(int x, int y, int ID){
    for(int i = 0; i < m_actors.size(); i++)
        if(m_actors[i]->getid() == ID)
            if(checkOverlap(x, y, m_actors[i]->getX(), m_actors[i]->getY()))
                return true;
    return false;
}

bool StudentWorld::validTunnelManMove(int x, int y){
    if(!checkInBounds(x, y))
        return false;
    if(checkForObject(x, y, TID_BOULDER))
        return false;
    return true;
}

bool StudentWorld::validSquirtSpawn(int x, int y){
    if(!checkInBounds(x, y)){
        return false;
    }
    if(checkForObject(x, y, TID_BOULDER)){
        return false;
    }
    if(checkForEarth(x, y)){
        return false;
    }
    return true;
}

void StudentWorld::sonarScan(int x, int y){
    for(int i = 0; i < m_actors.size(); i++)
        if(m_actors[i]->getid() == TID_BARREL || m_actors[i]->getid() == TID_GOLD){
            if (inRadiusOf(x, y, m_actors[i]->getX(), m_actors[i]->getY(), 12, false)) {
                m_actors[i]->setVisible(true);
            }
        }
    playSound(SOUND_SONAR);
}




void StudentWorld::addWaterSquirt(int x, int y, Actor::Direction dir){
    Actor* squirt = new WaterSquirt(x, y, dir, this);
    m_actors.push_back(squirt);
}


void StudentWorld::addDroppedGold(int x, int y){
    Actor* gold = new GoldNugget(x, y, this, true);
    gold->setVisible(true);
    m_actors.push_back(gold);
}


bool StudentWorld::boulderRoll(int x, int y){
    if(checkForEarth(x, y))
        return false;
    if(!checkInBounds(x, y))
        return false;
    for(int i = 0; i < m_actors.size(); i++){
        if(m_actors[i]->getid() == TID_BOULDER && (m_actors[i]->getX() != x ||
                                                   m_actors[i]->getY() != y+1)){
            if(checkOverlap(x, y, m_actors[i]->getX(), m_actors[i]->getY()))
                return false;
        }
    }
    
    if(checkOverlap(x, y, m_tunnelMan->getX(), m_tunnelMan->getY())){
        m_tunnelMan->decHealth(100);
        return false;
    }
    
    for(int i = 0; i < m_actors.size(); i++){
        if(m_actors[i]->isProtestor()){
            if(checkOverlap(x, y, m_actors[i]->getX(), m_actors[i]->getY()) &&
               !m_actors[i]->isAnnoyed()){
                m_actors[i]->decHealth(100);
                increaseScore(500);
            }
        }
    }
    return true;
}


bool StudentWorld::squirtShot(int x, int y){
    for(int i = 0; i < m_actors.size(); i++){
        if(m_actors[i]->isProtestor()){
            if(inRadiusOf(x, y, m_actors[i]->getX(), m_actors[i]->getY(), 3, true) &&
               !m_actors[i]->isAnnoyed()){
                m_actors[i]->decHealth(2);
                return true;
            }
        }
    }
    return false;
}


bool StudentWorld::pickUpGoodie(int x, int y){
    if(inRadiusOf(x, y, m_tunnelMan->getX(), m_tunnelMan->getY(), 3, true)){
        return true;
    }
    return false;
}

bool StudentWorld::setGoodieVisible(int x, int y){
    if(inRadiusOf(x, y, m_tunnelMan->getX(), m_tunnelMan->getY(), 4, true)){
        return true;
    }
    return false;
}

bool StudentWorld::bribeProtestor(int x, int y){
    for(int i = 0; i < m_actors.size(); i++){
        if(m_actors[i]->isProtestor()){
            if(inRadiusOf(x, y, m_actors[i]->getX(), m_actors[i]->getY(), 3, true) &&
               !m_actors[i]->isAnnoyed()){
                m_actors[i]->bribe();
                return true;
            }
        }
    }
    return false;
}

void StudentWorld::incWater(int amt){
    m_tunnelMan->incWater(amt);
}

void StudentWorld::incSonar(int amt){
    m_tunnelMan->incSonar(amt);
}

void StudentWorld::incGold(int amt){
    m_tunnelMan->incGold(amt);
}


Actor::Direction StudentWorld::optimalMove(int x, int y){
    bool maze[61][61];
    for(int i = 0; i < 61; i++)
        for(int j = 0; j < 61; j++){
            if(validSquirtSpawn(i, j))
                maze[i][j] = true;
            else
                maze[i][j] = false;
        }
    queue<Coord> q;
    Coord c(Actor::none, x, y);
    q.push(c);
    maze[x][y] = false;
    bool first = true;
    while(!q.empty()){
        Coord t = q.front();
        q.pop();
        if(t.m_x == 60 && t.m_y == 60)
            return t.m_dir;
        if(maze[t.m_x][t.m_y+1]){
            if(first){
                Coord n(Actor::up, t.m_x, t.m_y+1);
                q.push(n);
            }
            else{
                Coord n(t.m_dir, t.m_x, t.m_y+1);
                q.push(n);
            }
            maze[t.m_x][t.m_y+1] = false;
        }
        if(maze[t.m_x+1][t.m_y]){
            if(first){
                Coord n(Actor::right, t.m_x+1, t.m_y);
                q.push(n);
            }
            else{
                Coord n(t.m_dir, t.m_x+1, t.m_y);
                q.push(n);
            }
            maze[t.m_x+1][t.m_y] = false;
        }
        if(maze[t.m_x][t.m_y-1]){
            if(first){
                Coord n(Actor::down, t.m_x, t.m_y-1);
                q.push(n);
            }
            else{
                Coord n(t.m_dir, t.m_x, t.m_y-1);
                q.push(n);
            }
            maze[t.m_x][t.m_y-1] = false;
        }
        if(maze[t.m_x-1][t.m_y]){
            if(first){
                Coord n(Actor::left, t.m_x-1, t.m_y);
                q.push(n);
            }
            else{
                Coord n(t.m_dir, t.m_x-1, t.m_y);
                q.push(n);
            }
            maze[t.m_x-1][t.m_y] = false;
        }
        first = false;
    }
    return Actor::none;
}


bool StudentWorld::shoutAtTunnelMan(int x, int y, Actor::Direction dir){
    if(!inRadiusOf(x, y, m_tunnelMan->getX(), m_tunnelMan->getY(), 4, true))
        return false;
    if(dir == Actor::up && y > m_tunnelMan->getY())
        return false;
    if(dir == Actor::down && y < m_tunnelMan->getY())
        return false;
    if(dir == Actor::right && x > m_tunnelMan->getX())
       return false;
    if(dir == Actor::left && x < m_tunnelMan->getX())
       return false;
    playSound(SOUND_PROTESTER_YELL);
    m_tunnelMan->decHealth(2);
    return true;
}

Actor::Direction StudentWorld::canSeeTunnelMan(int x, int y){
    for(int i = y; validSquirtSpawn(x, i); i++){
        if(x == m_tunnelMan->getX() && i == m_tunnelMan->getY())
            return Actor::up;
    }
    for(int i = y; validSquirtSpawn(x, i); i--){
        if(x == m_tunnelMan->getX() && i == m_tunnelMan->getY())
            return Actor::down;
    }
    for(int i = x; validSquirtSpawn(i, y); i++){
        if(i == m_tunnelMan->getX() && y == m_tunnelMan->getY())
            return Actor::right;
    }
    for(int i = x; validSquirtSpawn(i, y); i--){
        if(i == m_tunnelMan->getX() && y == m_tunnelMan->getY())
            return Actor::left;
    }
    return Actor::none;
}


Actor::Direction StudentWorld::pickNewProtDir(int x, int y){
    for(;;){
        int potDir = rand() % 4;
        switch(potDir){
            case 0:
                if(validSquirtSpawn(x, y+1))
                    return Actor::up;
                break;
            case 1:
                if(validSquirtSpawn(x, y-1))
                    return Actor::down;
                break;
            case 2:
                if(validSquirtSpawn(x+1, y))
                    return Actor::right;
                break;
            case 3:
                if(validSquirtSpawn(x-1, y))
                    return Actor::left;
                break;
            default:
                break;
        }
    }
}

Actor::Direction StudentWorld::perpMove(int x, int y, Actor::Direction dir){
    switch(dir){
        case Actor::up:
        case Actor::down:{
            bool left = validSquirtSpawn(x-1, y);
            bool right = validSquirtSpawn(x+1, y);
            if(!left && !right)
                return Actor::none;
            if(left && !right)
                return Actor::left;
            if(!left && right)
                return Actor::right;
            int t = rand() % 2;
            if(t == 0)
                return Actor::left;
            return Actor::right;
            break;
        }
        case Actor::right:
        case Actor::left:{
            bool up = validSquirtSpawn(x, y+1);
            bool down = validSquirtSpawn(x, y-1);
            if(!up && !down)
                return Actor::none;
            if(up && !down)
                return Actor::up;
            if(!up && down)
                return Actor::down;
            int t = rand() % 2;
            if(t == 0)
                return Actor::up;
            return Actor::down;
            break;
        }
            
        default:
            return Actor::none;
            break;
            
    }
    
    
    
    
    return Actor::none;
}

bool StudentWorld::inRangeOfTunnelMan(int x, int y, int r, bool incl){
    if(inRadiusOf(x, y, m_tunnelMan->getX(), m_tunnelMan->getY(), r, incl))
        return true;
    return false;
}

bool StudentWorld::onTunnelMan(int x, int y){
    if(x == m_tunnelMan->getX() && y == m_tunnelMan->getY())
        return true;
    return false;
}

Actor::Direction StudentWorld::hardCoreFindTunnelMan(int x, int y, int range){
    bool maze[61][61];
    int visit[61][61];
    for(int i = 0; i < 61; i++)
        for(int j = 0; j < 61; j++)
            visit[i][j] = 0;
    
    for(int i = 0; i < 61; i++)
        for(int j = 0; j < 61; j++){
            if(validSquirtSpawn(i, j))
                maze[i][j] = true;
            else
                maze[i][j] = false;
        }
    
    queue<Coord> q;
    Coord c(Actor::none, x, y);
    q.push(c);
    maze[x][y] = false;
    bool first = true;
    while(!q.empty()){
        Coord t = q.front();
        q.pop();
        if(t.m_x == m_tunnelMan->getX() && t.m_y == m_tunnelMan->getY()){
            if(visit[t.m_x][t.m_y] <= range)
                return t.m_dir;
            else
                return Actor::none;
        }
        if(maze[t.m_x][t.m_y+1]){
            if(first){
                Coord n(Actor::up, t.m_x, t.m_y+1);
                q.push(n);
            }
            else{
                Coord n(t.m_dir, t.m_x, t.m_y+1);
                q.push(n);
            }
            maze[t.m_x][t.m_y+1] = false;
            visit[t.m_x][t.m_y+1] = 1 + visit[t.m_x][t.m_y];
        }
        if(maze[t.m_x+1][t.m_y]){
            if(first){
                Coord n(Actor::right, t.m_x+1, t.m_y);
                q.push(n);
            }
            else{
                Coord n(t.m_dir, t.m_x+1, t.m_y);
                q.push(n);
            }
            maze[t.m_x+1][t.m_y] = false;
            visit[t.m_x+1][t.m_y] = 1 + visit[t.m_x][t.m_y];
        }
        if(maze[t.m_x][t.m_y-1]){
            if(first){
                Coord n(Actor::down, t.m_x, t.m_y-1);
                q.push(n);
            }
            else{
                Coord n(t.m_dir, t.m_x, t.m_y-1);
                q.push(n);
            }
            maze[t.m_x][t.m_y-1] = false;
            visit[t.m_x][t.m_y-1] = 1 + visit[t.m_x][t.m_y];
        }
        if(maze[t.m_x-1][t.m_y]){
            if(first){
                Coord n(Actor::left, t.m_x-1, t.m_y);
                q.push(n);
            }
            else{
                Coord n(t.m_dir, t.m_x-1, t.m_y);
                q.push(n);
            }
            maze[t.m_x-1][t.m_y] = false;
            visit[t.m_x-1][t.m_y] = 1 + visit[t.m_x][t.m_y];
        }
        first = false;
    }
    return Actor::none;
}






