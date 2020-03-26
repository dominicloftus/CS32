//
//  main.cpp
//  HW1_32
//
//  Created by Dominic Loftus on 7/13/18.
//  Copyright © 2018 Dominic Loftus. All rights reserved.
//

#include <iostream>
#include "linkedlist.h"

int main(int argc, const char * argv[]) {
    LinkedList e1;
    e1.insertToFront("Sam");
    e1.insertToFront("Carla");
    e1.insertToFront("Cliff");
    e1.insertToFront("Norm");
    e1.reverseList(); // reverses the contents of e1
    string s;
    assert(e1.size() == 4 && e1.get(0, s) && s == "Sam");
    cout << "test passed" << endl;
    
}
