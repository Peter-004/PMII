// Your name here: Opemipo Peter Adebayo
// Your NetID here: opa15
//
// IMPORTANT NOTE:
// In your submission, you are only allowed to make modifications where it is indicated, 
// and you must provide your implementation in those designated areas. 
// You are not permitted to make changes to the code in any other location.
//
#ifndef HW4B_H
#define HW4B_H

#include <stdexcept>
#include <vector>

template <typename T>
class TreeNode {
public:
    T data;
    TreeNode* parent;
    TreeNode* left;
    TreeNode* right;

    TreeNode(T value, TreeNode* parent = nullptr) {
        data = value;
        this->parent = parent;
        left = nullptr; // https://cplusplus.com/reference/cstring/NULL/
        right = nullptr;
    }
};

// assuming no duplicate elements in the binary search tree
template <typename T>
class BinarySearchTree {
private:
    TreeNode<T>* root;

    // replaces the subtree rooted at u by the subtree rooted at v
    void transplant(TreeNode<T>* u, TreeNode<T>* v) {
        if (u->parent == nullptr) {
            root = v;
        } else if (u == u->parent->left) {
            u->parent->left = v;
        } else {
            u->parent->right = v;
        }
        if (v != nullptr) {
            v->parent = u->parent;
        }
    }

    void destroyTree(TreeNode<T>* root) {
        if (root == nullptr) {
            return; // empty tree 
        }

        destroyTree(root->left);
        destroyTree(root->right);
        delete root; // note the keyword "delete"
    }

    // recursive version of treeSearch
    TreeNode<T>* treeSearch(TreeNode<T>* node, T value) {
        if (node == nullptr || node->data == value) {
            return node;
        }

        if (value < node->data) {
            return treeSearch(node->left, value);
        }
        else {
            return treeSearch(node->right, value);
        }
    }

    TreeNode<T>* treeMinimum(TreeNode<T>* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    TreeNode<T>* treeMaximum(TreeNode<T>* node) {
        while (node->right != nullptr) {
            node = node->right;
        }
        return node;
    }
    
    void inorderTreeWalk(TreeNode<T>* node) {
        if (node == nullptr) {
            return;
        }

        inorderTreeWalk(node->left);
        std::cout << node->data << " ";
        inorderTreeWalk(node->right);
    }
    
    void preorderTreeWalk(TreeNode<T>* node) {
        // Provide your implementation here
        if(node == nullptr)return;
        std::cout << node->data << " ";
        preorderTreeWalk(node->left);
        preorderTreeWalk(node->right);

        // End of your implementation
    }

    void postorderTreeWalk(TreeNode<T>* node) {
        // Provide your implementation here
        if(node == nullptr)return;

        postorderTreeWalk(node->left);
        postorderTreeWalk(node->right);
        std::cout << node->data << " ";
        // End of your implementation
    }
    
    int treeHeight(TreeNode<T>* node) {
        // Provide your implementation here
        if(node == nullptr)return -1;
        int leftHeight = treeHeight(node->left);
        int rightHeight = treeHeight(node->right);
        return std::max(leftHeight, rightHeight) + 1;

        // End of your implementation
    }
    
    void rangeSearch(TreeNode<T>* node, const T& min, const T& max, std::vector<T>& results) {
        // Provide your implementation here
        if (node == nullptr) return;

        if (node->data >= min && node->data <= max) {
            results.push_back(node->data);
        }

        if (node->data > min) {
            rangeSearch(node->left, min, max, results);
        }

        if (node->data < max) {
            rangeSearch(node->right, min, max, results);
        }
        // End of your implementation
    }
    
    TreeNode<T>* treeMirror(TreeNode<T>* node) {
        // Provide your implementation here
        if (node == nullptr) return nullptr;;

        TreeNode<T>* mirrored = new TreeNode(node->data);
        //Recursively mirror sub-trees
        mirrored->left = treeMirror(node->right);
        mirrored->right = treeMirror(node->left);

        return mirrored;
        // End of your implementation
    }

    
public:
    BinarySearchTree() : root(nullptr) {}

    BinarySearchTree(TreeNode<T>* root) : root(root) {}
    
    ~BinarySearchTree() {
        destroyTree(root);
    }

    // recursive treeSearch
    TreeNode<T>* treeSearch(T value) {
        return treeSearch(root, value);
    }
    
    TreeNode<T>* treeMinimum() {
        return treeMinimum(root);
    }

    TreeNode<T>* treeMaximum() {
        return treeMaximum(root);
    }

    void treeInsert(T value) {
        TreeNode<T>* newNode = new TreeNode<T>(value); // note the keyword "new"

        TreeNode<T>* current = root;
        TreeNode<T>* parent = nullptr;

        while (current != nullptr) {
            parent = current;
            if (value < current->data) {
                current = current->left;
            } else {
                current = current->right;
            }
        }

        newNode->parent = parent; // found the location -- insert newNode with parent

        if (parent == nullptr) {
            root = newNode; // Tree was empty
        } else if (value < parent->data) {
            parent->left = newNode;
        } else {
            parent->right = newNode;
        }
    }
    
    void treeDelete(T value) {
        TreeNode<T>* node = treeSearch(root, value);
        if (node == nullptr) {
            return; // value not found in the BST 
        }

        if (node->left == nullptr) {
            transplant(node, node->right);
        } else if (node->right == nullptr) {
            transplant(node, node->left);
        } else {
            TreeNode<T>* successor = treeMinimum(node->right);
            if (successor->parent != node) {
                transplant(successor, successor->right);
                successor->right = node->right;
                successor->right->parent = successor;
            }
            transplant(node, successor);
            successor->left = node->left;
            successor->left->parent = successor;
        }
        
        delete node; // note the keyword "delete"
    }

    void inorderTreeWalk() {
        inorderTreeWalk(root);
    }

    void preorderTreeWalk() {
        preorderTreeWalk(root);
    }

    void postorderTreeWalk() {
        postorderTreeWalk(root);
    }

    int treeHeight() {
        if (root == nullptr) {
            throw std::runtime_error("Tree is empty.");
        }
        return treeHeight(root);
    }

    void rangeSearch(const T& min, const T& max, std::vector<T>& results) {
        rangeSearch(root, min, max, results);
    }
    
    BinarySearchTree treeMirror() {
        return BinarySearchTree(treeMirror(root));
    }

};

#endif