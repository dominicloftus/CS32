//
//  CoachingStaff.cpp
//  Project2_32
//
//  Created by Dominic Loftus on 7/19/18.
//  Copyright © 2018 Dominic Loftus. All rights reserved.
//

#include "CoachingStaff.h"
#include <string>
#include <iostream>
using namespace std;

CoachingStaff::CoachingStaff(){
    head = nullptr;
    tail = nullptr;
}

CoachingStaff::~CoachingStaff(){
    Coach* p = head;
    while(p != nullptr){
        Coach* temp = p->next;
        delete p;
        p = temp;
    }
}

CoachingStaff::CoachingStaff(const CoachingStaff& other){
    if(other.head == nullptr){
        head = nullptr;
        tail = nullptr;
    }
    else{
        head = new Coach;
        Coach* p = other.head;
        Coach* n = head;
        n->prev = nullptr;
        while(p->next != nullptr){          //add in all values
            n->m_last = p->m_last;
            n->m_first = p->m_first;
            n->m_value = p->m_value;
            n->next = new Coach;
            Coach* t = n;
            n = n->next;
            n->prev = t;
            p = p->next;
        }
        n->m_last = p->m_last;
        n->m_first = p->m_first;
        n->m_value = p->m_value;
        n->next = nullptr;
        tail = n;
    }
}

const CoachingStaff& CoachingStaff::operator=(const CoachingStaff& other){
    if(this == &other) return *this;
    CoachingStaff temp = other;
    changeStaff(temp);
    return *this;
}

bool CoachingStaff::noCoaches() const{
    if(head == nullptr)
        return true;
    return false;
}

int CoachingStaff::numberOfCoaches() const{
    int count = 0;
    Coach* p = head;
    while(p != nullptr){
        count++;
        p = p->next;
    }
    return count;
}

bool CoachingStaff::hireCoach(const std::string& firstName, const std::string&
                              lastName, const IType& value){
    if(head == nullptr){                //empty list
        head = new Coach;
        tail = head;
        head->m_last = lastName;
        head->m_first = firstName;
        head->m_value = value;
        head->next = nullptr;
        head->prev = nullptr;
        return true;
    }
    else if(lastName < head->m_last || (lastName == head->m_last && firstName < head->m_first)){
        Coach* p = head;                //first in list
        head = new Coach;
        head->m_last = lastName;
        head->m_first = firstName;
        head->m_value = value;
        head->next = p;
        head->prev = nullptr;
        p->prev = head;
        return true;
    }
    else if(lastName > tail->m_last || (lastName == tail->m_last && firstName > tail->m_first)){
        Coach* p = tail;                //last in list
        tail = new Coach;
        tail->m_last = lastName;
        tail->m_first = firstName;
        tail->m_value = value;
        p->next = tail;
        tail->prev = p;
        tail->next = nullptr;
        return true;
    }
    else{
        Coach* p = head;
        Coach* q = head->next;
        while(q != nullptr){
            if((lastName > p->m_last && lastName < q->m_last) ||        //different last name
               ((lastName == p->m_last && lastName == q->m_last) &&     //two same last names
                (firstName > p->m_first && firstName < q->m_first)) ||
               ((lastName > p->m_last && lastName == q->m_last) &&      //one same last name
                (firstName < q->m_first)) ||
               ((lastName == p->m_last && lastName < q->m_last) &&      //one same last name
                (firstName > p->m_first))){                             //other case
                   Coach* n = new Coach;
                   n->m_last = lastName;
                   n->m_first = firstName;
                   n->m_value = value;
                   n->next = q;
                   n->prev = p;
                   p->next = n;
                   q->prev = n;
                   return true;
                   
            }
            p = p->next;
            q = q->next;
        }
    }
    
    return false;
}

bool CoachingStaff::renameCoach(const std::string& firstName, const std::string&
                                lastName, const IType& value){
    Coach* p = head;
    while(p != nullptr){
        if(p->m_last == lastName && p->m_first == firstName){
            p->m_value = value;
            return true;
        }
        p = p->next;
    }
    return false;
}

bool CoachingStaff::hireOrRename(const std::string& firstName, const std::string&
                            lastName, const IType& value){
    if(!hireCoach(firstName, lastName, value))              //already in list
        renameCoach(firstName, lastName, value);
    return true;
}

bool CoachingStaff::fireCoach(const std::string& firstName, const std::string&
                         lastName){
    Coach* p = head;
    if(p->next == nullptr){         //only one element
        delete p;
        head = nullptr;
        tail = nullptr;
        return true;
    }
    for(; p != nullptr; p = p->next){
        if(p->m_first == firstName && p->m_last == lastName){
            if(p->prev != nullptr)              //first node
                p->prev->next = p->next;
            else{
                head = p->next;
                head->prev = nullptr;
            }
            if(p->next != nullptr){             //last node
                p->next->prev = p->prev;
            }
            else{
                tail = p->prev;
                tail->next = nullptr;
            }
            delete p;
            return true;
        }
    }
    return false;
}

bool CoachingStaff::coachOnStaff(const std::string& firstName, const std::string&
                            lastName) const{
    for(Coach* p = head; p != nullptr; p = p->next){
        if(p->m_first == firstName && p->m_last == lastName)
            return true;
    }
    return false;
}

bool CoachingStaff::findCoach(const std::string& firstName, const std::string&
                         lastName, IType& value) const{
    for(Coach* p = head; p != nullptr; p = p->next){
        if(p->m_first == firstName && p->m_last == lastName){
            value = p->m_value;
            return true;
        }
    }
    return false;
}

bool CoachingStaff::whichCoach(int i, std::string& firstName, std::string&
                          lastName, IType& value) const{
    Coach* p = head;
    for(int k = 0; k < i && p != nullptr; k++){
        p = p->next;
    }
    if(p == nullptr)
        return false;
    firstName = p->m_first;
    lastName = p->m_last;
    value = p->m_value;
    return true;
}

void CoachingStaff::changeStaff(CoachingStaff& other){
    Coach* hTemp = other.head;
    Coach* tTemp = other.tail;
    other.head = head;
    other.tail = tail;
    head = hTemp;
    tail = tTemp;
}



bool mergeStaffs(const CoachingStaff & csOne, const CoachingStaff & csTwo,
                 CoachingStaff & csMerged){
    bool ret = true;
    CoachingStaff t;
    csMerged = t;
    for(int i = 0; i < csOne.numberOfCoaches(); i++){       //add entire list
        string f, l;
        IType v;
        csOne.whichCoach(i, f, l, v);
        csMerged.hireCoach(f, l, v);
    }
    for(int i = 0; i < csTwo.numberOfCoaches(); i++){
        string f, l;
        IType v;
        csTwo.whichCoach(i, f, l, v);
        if(!csMerged.coachOnStaff(f, l))                    //check if already in list
            csMerged.hireCoach(f, l, v);
        else{
            IType val;
            csMerged.findCoach(f, l, val);
            if(v == val)
                continue;
            else{
                csMerged.fireCoach(f, l);                   //get rid of coach with different vals
                ret = false;
            }
        }
    }
    return ret;
}

void searchStaff (const std::string& fsearch, const std::string& lsearch,
                  const CoachingStaff& csOne, CoachingStaff& csResult){
    CoachingStaff t;
    csResult = t;
    for(int i = 0; i < csOne.numberOfCoaches(); i++){
        string f, l;
        IType v;
        csOne.whichCoach(i, f, l, v);
        if((f == fsearch || fsearch == "*") && (l == lsearch || lsearch == "*")){
            csResult.hireCoach(f, l, v);
        }
    }
}








