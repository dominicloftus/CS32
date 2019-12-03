//
//  main.cpp
//  HW2_32
//
//  Created by Dominic Loftus on 7/27/18.
//  Copyright © 2018 Dominic Loftus. All rights reserved.
//

#include <iostream>
#include <string>
using namespace std;

int mult(unsigned int m, unsigned int n);
int countDigit(int num, int digit);
string pairStars(string n);
string subBrackets(string str);
bool comboSum(const int a[], int size, int target);
bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec);

// Returns the product of two positive integers, m and n,
// using only repeated addition.
int mult(unsigned int m, unsigned int n)
{
    if(m == 0 || n == 0)
        return 0;
    if(n == 1)
        return m;
    return m + mult(m, n-1);
}


// Returns the number of occurrences of digit in the decimal
// representation of num. digit is an int between 0 and 9
// inclusive.
//
// Pseudocode Example:
// countDigit(18838, 8) => 3
// countDigit(55555, 3) => 0
// countDigit(0, 0) => 0 or 1 (either if fine)
//
int countDigit(int num, int digit)
{
    if(num == 0)
        return 0;
    int x = num % 10;
    if(x == digit)
        return 1 + countDigit(num/10, digit);
    else
        return countDigit(num/10,digit);
}


// Returns a string where the same characters next each other in
// string n are separated by "**"
//
// Pseudocode Example:
// pairStars("goodbye") => "go**odbye"
// pairStars("yyuu") => "y**yu**u"
// pairStars("aaaa") => "a**a**a**a"
//
string pairStars(string n)
{
    if(n.size() == 0)
        return "";
    if(n.size() == 1)
        return n;
    if(n[0] != n[1])
        return n.substr(0,1) + pairStars(n.substr(1));
    else{
        string t = n.substr(0,1) + "**";
        return t + pairStars(n.substr(1));
    }
    
    
}

// str contains a single pair of brackets, return a new string
// made of only the brackets and whatever those brackets contain
//
// Pseudocode Example:
// subBrackets("abc[ghj]789") => "[ghj]"
// subBrackets("[x]7") => "[x]"
// subBrackets ("4agh[y]") => "[y]"
//
string subBrackets(string str)
{
    if(str.size() == 0)
        return "";
    if(str.substr(0,2) == "[]")
        return "[]";
    if(str[1] == ']')
        return "]";
    if(str[0] == '[')
        return "[" + subBrackets("]" + str.substr(1));
    else if(str[0] == ']')
        return str.substr(1,1) + subBrackets("]" + str.substr(2));
    else
        return subBrackets(str.substr(1));
        
}


// Return true if the sum of any combination of elements in the
// array a equals the value of the target.
//
// Pseudocode Example:
// comboSum([2, 4, 8], 3, 10) => true
// comboSum([2, 4, 8], 3, 12) => true
// comboSum([2, 4, 8], 3, 11) => false
// comboSum([], 0, 0) => true
//
bool comboSum(const int a[], int size, int target)
{
    if(size == 0){
        if(target == 0)
            return true;
        else
            return false;
    }
    if(size == 1){
        if(a[0] == target)
            return true;
        else
            return false;
    }
    if(a[size-1] == target)
        return true;
    if(comboSum(a, size-1, target-a[size-1]))
           return true;
    if(comboSum(a, size-1, target))
           return true;
    return false;
}


// Return true if there is a path from (sr,sc) to (er,ec)
// through the maze; return false otherwise
bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec){
    if(sr == er && sc == ec)
        return true;
    maze[sr][sc] = 'V';
    if(maze[sr-1][sc] == '.'){
        if(pathExists(maze, nRows, nCols, sr-1, sc, er, ec))
            return true;
    }
    if(maze[sr][sc+1] == '.'){
        if(pathExists(maze, nRows, nCols, sr, sc+1, er, ec))
            return true;
    }
    if(maze[sr+1][sc] == '.'){
        if(pathExists(maze, nRows, nCols, sr+1, sc, er, ec))
            return true;
    }
    if(maze[sr][sc-1] == '.'){
        if(pathExists(maze, nRows, nCols, sr, sc-1, er, ec))
            return true;
    }
    return false;
}



int main(){
    double d = 1600;
    cout << d << endl;
}















