//
//  Past.cpp
//  Project1_32
//
//  Created by Dominic Loftus on 7/5/18.
//  Copyright © 2018 Dominic Loftus. All rights reserved.
//

#include <iostream>
#include <string>
#include "Past.h"
#include "globals.h"
using namespace std;

Past::Past(int nRows, int nCols){
    m_marks = new char*[nRows];
    for(int i = 0; i < nRows; i++)
        m_marks[i] = new char[nCols];
    
    for(int i = 0; i < nRows; i++)
        for(int j = 0; j < nCols; j++)
            m_marks[i][j] = '.';
    
    m_rows = nRows;
    m_cols = nCols;
    
}

Past::~Past(){
    for(int i = 0; i < m_rows; i++)
        delete[] m_marks[i];
    delete[] m_marks;
}

bool Past::markIt(int r, int c){
    if(r < 1 || c < 1 || r > m_rows || c > m_cols)
        return false;
    r--;
    c--;
    if(m_marks[r][c] == '.')
        m_marks[r][c] = 'A';
    else if(m_marks[r][c] != 'Z')
        m_marks[r][c]++;
    
    return true;
}

void Past::printThePast() const{
    clearScreen();
    for(int i = 0; i < m_rows; i++){
        for(int j = 0; j < m_cols; j++){
            cout << m_marks[i][j];
        }
        cout << endl;
    }
    
}
