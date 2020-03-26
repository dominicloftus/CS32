//
//  Tree.hpp
//  HW4_32
//
//  Created by Dominic Loftus on 8/20/18.
//  Copyright © 2018 Dominic Loftus. All rights reserved.
//

#ifndef Tree_h
#define Tree_h

#include <iostream>
#include <string>

typedef std::string IType;

struct WordNode {
    IType m_data;
    WordNode *m_left;
    WordNode *m_right;
    int m_occur;
    WordNode(IType data){
        m_data = data;
        m_left = nullptr;
        m_right = nullptr;
        m_occur = 1;
    }
};

class WordTree {
private:
    WordNode *root;
    void copy(WordNode*& lhs, WordNode*& rhs);
    void freeTree(WordNode* cur);
    int distinctCount(WordNode* cur) const;
    int totalCount(WordNode* cur) const;
    void printTree(std::ostream& out,WordNode* cur) const;
public:
    // default constructor
    WordTree() : root(nullptr) { };
    
    // copy constructor
    WordTree(const WordTree& rhs);
    
    // assignment operator
    const WordTree& operator=(const WordTree& rhs);
    
    // Inserts v into the WordTree
    void add(IType v);
    
    // Returns the number of distinct words / nodes
    int distinctWords() const;
    
    // Returns the total number of words inserted, including
    // duplicate values
    int totalWords() const;
    
    // Prints the LinkedList
    friend std::ostream& operator<<(std::ostream &out, const WordTree& rhs);
    
    // Destroys all the dynamically allocated memory in the
    // tree
    ~WordTree();
};

#endif /* Tree_h */
