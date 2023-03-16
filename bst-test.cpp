#include <iostream>
#include <map>
#include <vector>
#include "bst.h"
#include "avlbst.h"

using namespace std;


int main(int argc, char *argv[])
{
    // Binary Search Tree tests

    // Binary Search Tree tests
		vector<int> hi = {0, -5, -10};

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



    AVLTree<int,int> at;
    for (size_t i = 0; i < fuark.size(); ++i)
    {
        at.insert(std::make_pair(fuark[i], fuark[i]));
    }

    cout << "\nAVLTree contents:" << endl;
    at.printTree();

    return 0;
}