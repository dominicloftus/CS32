//
//  Tree.cpp
//  HW4_32
//
//  Created by Dominic Loftus on 8/20/18.
//  Copyright © 2018 Dominic Loftus. All rights reserved.
//

#include "Tree.h"
using namespace std;

void WordTree::copy(WordNode*& lhs, WordNode*& rhs){
    if(rhs == nullptr)
        return;
    lhs = new WordNode(rhs->m_data);
    lhs->m_occur = rhs->m_occur;
    copy(lhs->m_left, rhs->m_left);
    copy(lhs->m_right, rhs->m_right);
}

WordTree::WordTree(const WordTree& rhs){
    if(rhs.root == nullptr){
        root = nullptr;
        return;
    }
    root = new WordNode(rhs.root->m_data);
    root->m_occur = rhs.root->m_occur;
    copy(root->m_left, rhs.root->m_left);
    copy(root->m_right, rhs.root->m_right);
}

void WordTree::freeTree(WordNode* cur){
    if(cur == nullptr)
        return;
    freeTree(cur->m_left);
    freeTree(cur->m_right);
    delete cur;
}

const WordTree& WordTree::operator=(const WordTree& rhs){
    WordTree temp = rhs;
    freeTree(root);
    root = temp.root;
    temp.root = nullptr;
    return *this;
}

void WordTree::add(IType v){
    if(root == nullptr){
        root = new WordNode(v);
        return;
    }
    WordNode* cur = root;
    while(true){
        if(cur->m_data == v){
            cur->m_occur++;
            return;
        }
        if(v < cur->m_data){
            if(cur->m_left == nullptr){
                cur->m_left = new WordNode(v);
                return;
            }
            cur = cur->m_left;
        }
        else{
            if(cur->m_right == nullptr){
                cur->m_right = new WordNode(v);
                return;
            }
            cur = cur->m_right;
        }
    }
}

int WordTree::distinctCount(WordNode* cur) const{
    if(cur == nullptr)
        return 0;
    int tot = 1;
    tot += distinctCount(cur->m_left);
    tot += distinctCount(cur->m_right);
    return tot;
}

int WordTree::distinctWords() const{
    return distinctCount(root);
}

int WordTree::totalCount(WordNode* cur) const{
    if(cur == nullptr)
        return 0;
    int tot = cur->m_occur;
    tot += totalCount(cur->m_left);
    tot += totalCount(cur->m_right);
    return tot;
}

int WordTree::totalWords() const{
    return totalCount(root);
}

void WordTree::printTree(ostream& out, WordNode* cur) const{
    if(cur == nullptr)
        return;
    printTree(out, cur->m_left);
    out << cur->m_data << " " << cur->m_occur << endl;
    printTree(out, cur->m_right);
    
}

ostream& operator<<(ostream& out, const WordTree& rhs){
    rhs.printTree(out, rhs.root);
    return out;
}

WordTree::~WordTree(){
    freeTree(root);
}










