//
//  Player.hpp
//  Project1_32
//
//  Created by Dominic Loftus on 7/5/18.
//  Copyright © 2018 Dominic Loftus. All rights reserved.
//

#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>

class Arena;

class Player
{
public:
    // Constructor
    Player(Arena *ap, int r, int c);
    
    // Accessors
    int  row() const;
    int  col() const;
    int  age() const;
    bool isDead() const;
    
    // Mutators
    std::string takeComputerChosenTurn();
    void   stand();
    void   move(int dir);
    bool   shoot(int dir);
    void   setDead();
    
private:
    Arena* m_arena;
    int    m_row;
    int    m_col;
    int    m_age;
    bool   m_dead;
    
    int    computeDanger(int r, int c) const;
};


#endif 
