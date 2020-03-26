//
//  linkedlist.cpp
//  HW1_32
//
//  Created by Dominic Loftus on 7/13/18.
//  Copyright © 2018 Dominic Loftus. All rights reserved.
//

#include "linkedlist.h"
#include <iostream>

LinkedList::LinkedList(const LinkedList& rhs){
    if(rhs.head == nullptr){
        head = nullptr;
        return;
    }
    head = new Node;
    Node* n = head;
    Node* p = rhs.head;
    while(p->next != nullptr){
        n->value = p->value;
        n->next = new Node;
        n = n->next;
        p = p->next;
    }
    n->value = p->value;
    n->next = nullptr;
}

LinkedList::~LinkedList(){
    Node* p = head;
    while(p != nullptr){
        Node* n = p->next;
        delete p;
        p = n;
    }
}

const LinkedList& LinkedList::operator=(const LinkedList& rhs){
    if(this != &rhs){
        Node* p = head;
        while(p != nullptr){
            Node* n = p->next;
            delete p;
            p = n;
        }
        if(rhs.head == nullptr){
            head = nullptr;
            return *this;
        }
        head = new Node;
        Node* n = head;
        p = rhs.head;
        while(p->next != nullptr){
            n->value = p->value;
            n->next = new Node;
            n = n->next;
            p = p->next;
        }
        n->value = p->value;
        n->next = nullptr;
    }
    
    return *this;
}

void LinkedList::insertToFront(const ItemType &val){
    Node* p = new Node;
    p->value = val;
    p->next = head;
    head = p;
}

void LinkedList::printList() const{
    Node* p = head;
    while(p != nullptr){
        cout << p->value << " ";
        p = p->next;
    }
    cout << endl;
}

bool LinkedList::get(int i, ItemType& item) const{
    Node* p = head;
    for(int k = 0; k < i && p != nullptr; k++){
        p = p->next;
    }
    if(p == nullptr)
        return false;
    item = p->value;
    return true;
}

void LinkedList::reverseList(){
    if(head == nullptr)
        return;
    Node* p = head->next;
    Node* back = head;
    Node* forw;
    while(p != nullptr){
        forw = p->next;
        p->next = back;
        back = p;
        p = forw;
    }
    head->next = nullptr;
    head = back;
}

void LinkedList::printReverse() const{
    LinkedList temp(*this);
    temp.reverseList();
    temp.printList();
}



void LinkedList::append(const LinkedList &other){
    if(other.head == nullptr)
        return;
    Node* p = head;
    while(p->next != nullptr){
        p = p->next;
    }
    Node* n = other.head;
    p->next = new Node;
    p = p->next;
    while(n->next != nullptr){
        p->value = n->value;
        p->next = new Node;
        p = p->next;
        n = n->next;
    }
    p->value = n->value;
    p->next = nullptr;
}

void LinkedList::swap(LinkedList &other){
    LinkedList temp(other);
    other = *this;
    *this = temp;
}

int LinkedList::size() const{
    int count = 0;
    Node* p = head;
    while(p != nullptr){
        count++;
        p = p->next;
    }
    return count;
}













