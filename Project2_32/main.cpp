//
//  main.cpp
//  Project2_32
//
//  Created by Dominic Loftus on 7/19/18.
//  Copyright © 2018 Dominic Loftus. All rights reserved.
//

#include <iostream>
#include "CoachingStaff.h"

int main() {
    CoachingStaff a;
    a.hireCoach("Bob", "Hope", "50");
    a.hireCoach("Sam", "Saunders", "78");
    a.hireCoach("Rob", "Abraham", "30");
    a.hireCoach("Zob", "Abraham", "12");
    a.hireCoach("Aam", "Saunders", "31");
    a.hireOrRename("Bob", "Hope", "40");
    std::cerr << a.numberOfCoaches() << std::endl;
    a.fireCoach("Zob", "Abraham");
    a.renameCoach("Sam", "Saunders", "75");
    std::cerr << a.numberOfCoaches() << std::endl;
    CoachingStaff b = a;
    b.hireCoach("Wham", "Bam", "100");
    b.hireCoach("Worst", "Nightmare", "2");
    std::cerr << b.numberOfCoaches() << std::endl;
    b.changeStaff(a);
    a.fireCoach("Wham", "Bam");
    a.hireCoach("Sammy", "Boy", "1");
    a.hireCoach("Sammy", "Girl", "1");
    a.hireCoach("Sammy", "Whirl", "1");
    CoachingStaff c;
    mergeStaffs(a,b,c);
    CoachingStaff d;
    searchStaff("Sammy", "*", c, d);
    d.fireCoach("Sammy", "Girl");
    CoachingStaff e;
    e.hireCoach("A", "B", "1");
    e.fireCoach("A", "B");
}


