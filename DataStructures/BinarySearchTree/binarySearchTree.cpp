#include <iostream>
#include <vector>
#include <string>
#include <utility>

struct TreeNode;
template<typename T>
class BinarySearchTree
{
public:
    BinarySearchTree()
        :root{ nullptr } {};

    BinarySearchTree(const T& rootValue)
        :root{ rootValue } {}

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
    void invert()
    {
        invert(root);
    }
    void printTree(TreeNode* node)
    {
        if (node)
        {
            printTree(node->left);
            std::cout << node->element << ' ';
            printTree(node->right);
        }
    }

private:

    struct TreeNode
    {
        T element;
        TreeNode* left;
        TreeNode* right;

        TreeNode(const T& element)
            :element{ element }, left{ nullptr }, right{ nullptr } {};

        TreeNode(const T&& element)
            :element{ std::move(element) }, left{ nullptr }, right{ nullptr } {};

        TreeNode(const T& element, TreeNode* left, TreeNode* right)
            :element{ element }, left{ left }, right{ right } {}

        TreeNode(const T&& element, TreeNode* left, TreeNode* right)
            :element{ std::move(element) }, left{ left }, right{ right } {}
    };

    TreeNode* root;

    bool contains(const T& key, TreeNode* node)
    {
        if (!node)
            return false;

        if (node->element > key)
            return contains(key,node->left);

        if (node->element < key)
            return contains(key,node->right);

            return true;
    }

    TreeNode* findMin(TreeNode* node)
    {
        if (!node)
            return nullptr;
        if (!node->left)
            return node;
        
        return findMin(node->left);
    }

    TreeNode* findMax(TreeNode* node)
    {
        if (!node)
            return nullptr;
        if (!node->right)
            return node;

        return findMax(node->right);
    }

    void insert(const T& value, TreeNode*& node)
    {
        if (!node)
            node = new TreeNode{ value };
        if (node->element > value)
            insert(value, node->left);
        if (node->element < value)
            insert(value, node->right);
    }
    void insert(const T&& value, TreeNode*& node)
    {
        if (!node)
            node = new TreeNode{ std::move(value) };
        if (node->element > value)
            insert(value, node->left);
        if (node->element < value)
            insert(value, node->right);
    }

    void remove(const T& value, TreeNode*& node)
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
            TreeNode* oldNode = node;

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
    void clear(TreeNode*& node)
    {
        if (node!=nullptr)
        {
            clear(node->left);
            clear(node->right);
            delete node; 
        }
        node = nullptr;
    }
    TreeNode* clone(const TreeNode* node) const
    {
        if (!node)
            return nullptr;
        
        return new TreeNode{ node->element,node->left,node->right };
    }
    TreeNode* invert(TreeNode*& node)
    {
        if (!node)
            return node;

        if (!node->left && !node->right)
            return node;
        else
            std::swap(node->left, node->right);

        invert(node->left);
        invert(node->right);

        return node;
    }

    void printTree(TreeNode* node)
    {
        if (node)
        {
            printTree(node->left);
            std::cout << node->element << ' ';
            printTree(node->right);
        }
    }
};


int main()
{
    BinarySearchTree<int> t{ 10 };
    t.insert(12);
    t.insert(10);
    t.insert(6);
    t.insert(8);
}


