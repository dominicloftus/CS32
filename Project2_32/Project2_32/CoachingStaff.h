//
//  CoachingStaff.hpp
//  Project2_32
//
//  Created by Dominic Loftus on 7/19/18.
//  Copyright © 2018 Dominic Loftus. All rights reserved.
//

#ifndef CoachingStaff_h
#define CoachingStaff_h

#include <string>

typedef std::string IType;

class CoachingStaff
{
public:
    CoachingStaff(); // Create an empty CoachingStaff list
    
    ~CoachingStaff();
    
    CoachingStaff(const CoachingStaff& other);
    
    const CoachingStaff& operator=(const CoachingStaff& other);
    
    bool noCoaches() const; // Return true if the CoachingStaff list
    // is empty, otherwise false.
    
    int numberOfCoaches() const; // Return the number of elements in
    // the CoachingStaff list.
    
    bool hireCoach(const std::string& firstName, const std::string&
                   lastName, const IType& value);
    // If the full name (both the first and last name) is not equal
    // to any full name currently in the list then add it and return
    // true. Elements should be added according to their last name.
    // Elements with the same last name should be added according to
    // their first names. Otherwise, make no change to the list and
    // return false (indicating that the name is already in the
    // list).
    
    bool renameCoach(const std::string& firstName, const std::string&
                     lastName, const IType& value);
    // If the full name is equal to a full name currently in the
    // list, then make that full name no longer map to the value it
    // currently maps to, but instead map to the value of the third
    // parameter; return true in this case. Otherwise, make no
    // change to the list and return false.
    
    bool hireOrRename(const std::string& firstName, const std::string&
                      lastName, const IType& value);
    // If full name is equal to a name currently in the list, then
    // make that full name no longer map to the value it currently
    // maps to, but instead map to the value of the third parameter;
    // return true in this case. If the full name is not equal to
    // any full name currently in the list then add it and return
    // true. In fact, this function always returns true.
    
    bool fireCoach(const std::string& firstName, const std::string&
                   lastName);
    // If the full name is equal to a full name currently in the
    // list, remove the full name and value from the list and return
    // true. Otherwise, make no change to the list and return
    // false.
    
    bool coachOnStaff(const std::string& firstName, const std::string&
                      lastName) const;
    // Return true if the full name is equal to a full name
    // currently in the list, otherwise false.
    
    bool findCoach(const std::string& firstName, const std::string&
                   lastName, IType& value) const;
    // If the full name is equal to a full name currently in the
    // list, set value to the value in the list that that full name
    // maps to, and return true. Otherwise, make no change to the
    // value parameter of this function and return false.
    
    bool whichCoach(int i, std::string& firstName, std::string&
                    lastName, IType& value) const;
    // If 0 <= i < size(), copy into firstName, lastName and value
    // parameters the corresponding information of the element at
    // position i in the list and return true. Otherwise, leave the
    // parameters unchanged and return false. (See below for details
    // about this function.)
    
    void changeStaff(CoachingStaff& other);
    // Exchange the contents of this list with the other one.
    
    
private:
    struct Coach{
        std::string m_first;
        std::string m_last;
        IType m_value;
        Coach* next;
        Coach* prev;
    };
    Coach* head;
    Coach* tail;
};

bool mergeStaffs(const CoachingStaff & csOne, const CoachingStaff & csTwo,
                 CoachingStaff & csMerged);

void searchStaff (const std::string& fsearch, const std::string& lsearch,
                  const CoachingStaff& csOne, CoachingStaff& csResult);

#endif /* CoachingStaff_h */














