//
//  main.cpp
//  HW4_32
//
//  Created by Dominic Loftus on 8/20/18.
//  Copyright © 2018 Dominic Loftus. All rights reserved.
//

#include <iostream>
#include "Tree.h"
#include <string>
using namespace std;

int main(void){
    WordTree k;
    
    k.add("Kim");
    k.add("Kanye");
    k.add("Kanye");
    k.add("Kanye");
    cout << k;
    k.add("Al");
    k.add("Zot");
    cout << k;
    WordTree w;
    
    w.add("Harry");
    w.add("Niall");
    w.add("Niall");
    w.add("Liam");
    w.add("Louis");
    w.add("Harry");
    w.add("Niall");
    w.add("Zayn");
    cout << w;
    cout << w;
    
    WordTree c = w;
    cout << c;
    cout << c;
    cout << k;
    k = c;
    cout << k;
    cout << k.totalWords() << endl << k.distinctWords() << endl;
    cout << w.totalWords() << endl << w.distinctWords() << endl;
}
