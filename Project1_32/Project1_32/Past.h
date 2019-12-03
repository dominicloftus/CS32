//
//  Past.hpp
//  Project1_32
//
//  Created by Dominic Loftus on 7/5/18.
//  Copyright © 2018 Dominic Loftus. All rights reserved.
//

#ifndef PAST_H
#define PAST_H

class Past{
public:
    Past(int nRows, int nCols);
    ~Past();
    bool markIt(int r, int c);
    void printThePast() const;
private:
    char** m_marks;
    int m_rows;
    int m_cols;
};

#endif 
