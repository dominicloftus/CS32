//
//  Game.hpp
//  Project1_32
//
//  Created by Dominic Loftus on 7/5/18.
//  Copyright © 2018 Dominic Loftus. All rights reserved.
//

#ifndef GAME_H
#define GAME_H



class Arena;

class Game
{
public:
    // Constructor/destructor
    Game(int rows, int cols, int nRobots);
    ~Game();
    
    // Mutators
    void play();
    
private:
    Arena* m_arena;
};

#endif 
