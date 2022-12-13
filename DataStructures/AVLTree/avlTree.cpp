#include <iostream>
#include <vector>
#include <string>
#include <utility>


template <typename T>
class Tree
{


private:
    struct AvlNode
    {
        T element;
        AvlNode* left;
        AvlNode* right;

        AvlNode(const T& element, AvlNode* left = nullptr, AvlNode* right = nullptr)
            :element{ element }, left{ left }, right{ right }{}
    };

    AvlNode* root;

    AvlNode* lRotation()
    {
        AvlNode* temp = root->right;
        temp->right = temp->left;
        temp->left = root;
        return temp;
    }
    AvlNode* rRotation()
    {
        AvlNode* temp = root->left;
        temp->left = temp->right;
        temp->right = root;
        return temp;
    }

};

int main()
{
    
}


