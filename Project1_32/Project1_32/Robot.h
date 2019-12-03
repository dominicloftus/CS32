//
//  Robot.hpp
//  Project1_32
//
//  Created by Dominic Loftus on 7/5/18.
//  Copyright © 2018 Dominic Loftus. All rights reserved.
//

#ifndef ROBOT_H
#define ROBOT_H

class Arena;

class Robot
{
public:
    // Constructor
    Robot(Arena* ap, int r, int c);
    
    // Accessors
    int  row() const;
    int  col() const;
    
    // Mutators
    void move();
    bool takeDamageAndLive();
    
private:
    Arena* m_arena;
    int    m_row;
    int    m_col;
    int    m_health;
};


#endif 
