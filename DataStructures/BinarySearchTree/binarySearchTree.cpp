#include <iostream>
#include <vector>
#include <string>
#include <utility>


template<typename T>
class BinarySearchTree
{
public:
    BinarySearchTree()
        :root{ nullptr } {};

    BinarySearchTree(const BinarySearchTree& other)
        :root{ nullptr }
    {
        root = clone(other.root);
    }

    ~BinarySearchTree()
    {
        clear();
    }

    bool contains(const T& key)
    {
        return contains(key, root);
    }
    void insert(const T& value)
    {
        return insert(value, root);
    }
    void remove(const T& key)
    {
        remove(key, root);
    }
    void clear()
    {
        clear(root);
    }

private:

    struct BinaryNode
    {
        T element;
        BinaryNode* left;
        BinaryNode* right;

        BinaryNode(const T& element, BinaryNode* left, BinaryNode* right)
            :element{ element }, left{ left }, right{ right } {}

        BinaryNode(const T&& element, BinaryNode* left, BinaryNode* right)
            :element{ std::move(element) }, left{ left }, right{ right } {}
    };

    BinaryNode* root;

    bool contains(const T& key, BinaryNode* node)
    {
        if (!node)
            return false;

        if (node->element > key)
            return contains(key,node->left);

        if (node->element < key)
            return contains(key,node->right);

            return true;
    }

    BinaryNode* findMin(BinaryNode* node)
    {
        if (!node)
            return nullptr;
        if (!node->left)
            return node;
        
        return findMin(node->left);
    }

    BinaryNode* findMax(BinaryNode* node)
    {
        if (!node)
            return nullptr;
        if (!node->right)
            return node;

        return findMax(node->right);
    }

    void insert(const T& value, BinaryNode*& node)
    {
        if (!node)
            node = new BinaryNode{ value,nullptr,nullptr };
        if (node->element > value)
            insert(value, node->left);
        if (node->element < value)
            insert(value, node->right);
    }
    void insert(const T&& value, BinaryNode*& node)
    {
        if (!node)
            node = new BinaryNode{ std::move(value),nullptr,nullptr};
        if (node->element > value)
            insert(value, node->left);
        if (node->element < value)
            insert(value, node->right);
    }

    void remove(const T& value, BinaryNode*& node)
    {
        if (!node)
            return;
        if (node->element > value)
            remove(value, node->left);
        if (node->element < value)
            remove(value, node->right);

        if (node->left!=nullptr && node->right!=nullptr)
        {
            node->element = findMin(node->right)->element;
            remove(node->element, node->right);
        }
        else
        {
            BinaryNode* oldNode = node;

            if (node->left!=nullptr)
            {
                node = node->left;
            }
            else
            {
                node = node->right;
            }
            delete oldNode;
        }
    }
    void clear(BinaryNode*& node)
    {
        if (node!=nullptr)
        {
            clear(node->left);
            clear(node->right);
            delete node; 
        }
        node = nullptr;
    }
    BinaryNode* clone(const BinaryNode* node) const
    {
        if (!node)
            return nullptr;
        
        return new BinaryNode{ node->element,node->left,node->right };
    }
};


int main()
{

}


