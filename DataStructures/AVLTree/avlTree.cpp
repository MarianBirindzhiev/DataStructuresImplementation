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
        int height;

        AvlNode(const T& element)
            :element{ element }, left{ nullptr }, right{ nullptr }, height{ 0 } {}
        AvlNode(const T&& element)
            :element{ std::move(element) }, left{ nullptr }, right{ nullptr }, height{ 0 } {}
        AvlNode(const T& element, AvlNode* left, AvlNode* right, int height=0)
            :element{ element }, left{ left }, right{ right }, height{ height } {}
        AvlNode(const T&& element, AvlNode* left, AvlNode* right, int height = 0)
            :element{ std::move(element) }, left{ left }, right{ right }, height{ height } {}
    };

    AvlNode root;

    int height(AvlNode* node)
    {
        return node == nullptr ? -1 : node->height;
    }

    void insert(const T& value, AvlNode*& node)
    {
        if (!node)
            new AvlNode{ value };
        if (value < node->element)
            insert(value, node->left);
        if (value > node->right)
            insert(value, node->right);

        balance(node);

    }
    static const int ALLOWED_IMBALANCE = 1;

    void balance(AvlNode*& node)
    {
        if (!node)
            return;

        if (height(node->left) - height(node->right) > ALLOWED_IMBALANCE)
        {
            if (height(node->left->left) >= height(node->left->right))
                rotateWithLeftChild(node);
            else
                doubleWithLeftChild(node);
        }

        if (height(node->right) - height(node->left) > ALLOWED_IMBALANCE)
        {
            if (height(node->right->right) >= height(node->right->left))
                rotateWithRightChild(node);
            else
                doubleWithRightChild(node);
        }
        node->height = std::max(height(node->left), height(node->right)) + 1;
    }

    AvlNode* findMin(AvlNode* node)
    {
        if (!node)
            return nullptr;
        if (!node->left)
            return node;

        return findMin(node->left);
    }


    void rotateWithLeftChild(AvlNode* node)
    {
        AvlNode* tempNode = node->left;
        node->left = tempNode->right;
        tempNode->right = node;
        node->height = std::max(height(node->left), height(node->right)) + 1;
        tempNode->height = std::max(height(tempNode->left), height(tempNode->right)) + 1;
        node = tempNode;
    }

    void doubleWithLeftChild(AvlNode* node)
    {
        rotateWithLeftChild(node->left);
        rotateWithLeftChild(node);
    }

    void rotateWithRightChild(AvlNode* node)
    {
        AvlNode* tempNode = node->right;
        node->right = tempNode->left;
        tempNode->left = node;
        node->height = std::max(height(node->left), height(node->right)) + 1;
        tempNode->height = std::max(height(tempNode->left), height(tempNode->right)) + 1;
        node = tempNode;
    }

    void doubleWithRightChild(AvlNode* node)
    {
        rotateWithRightChild(node->right);
        rotateWithRightChild(node);
    }

    void remove(const T& key, AvlNode*& node)
    {
        if (!node)
            return;
        if (key < node->element)
            remove(key, node->left);
        if (key > node->element)
            remove(key, node->right);

        if (!node->left && !node->right)
        {
            node->element = findMin(node->right)->element;
            remove(node->element, node->right);
        }
        else
        {
            AvlNode* tempNode = node;
            node = node->left != nullptr ? node->left : node->right;
            delete tempNode;
        }
        balance(node);
    }

};

int main()
{
    
}


