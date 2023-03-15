#include <iostream>
#include <map>
#include <vector>
#include "bst.h"
#include "avlbst.h"

using namespace std;


int main(int argc, char *argv[])
{
    // Binary Search Tree tests
    vector<int> fuark = { -94,
                -52,
                77,
                124,
                36,
                64,
                54,
                -73,
                52,
                51,
                8,
                -81,
                -43,
                129,
                9,
                117,
                -38,
                21,
                131,
                -90,
                34,
                5,
                -131,
                45,
                -4,
                130,
                13,
                10,
                72,
                -134, 
                95};



    BinarySearchTree<int,int> bt;
    for (size_t i = 0; i < fuark.size(); ++i)
    {
        bt.insert(std::make_pair(fuark[i], fuark[i]));
    }

    bt.printTree();
/*
    // AVL Tree Tests
    AVLTree<char,int> at;
    at.insert(std::make_pair('a',1));
    at.insert(std::make_pair('b',2));

    cout << "\nAVLTree contents:" << endl;
    for(AVLTree<char,int>::iterator it = at.begin(); it != at.end(); ++it) {
        cout << it->first << " " << it->second << endl;
    }
    if(at.find('b') != at.end()) {
        cout << "Found b" << endl;
    }
    else {
        cout << "Did not find b" << endl;
    }
    cout << "Erasing b" << endl;
    at.remove('b');
*/
    return 0;
}