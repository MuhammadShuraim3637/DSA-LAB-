#include <iostream>
using namespace std;
struct TreeNode {
    int value;
    TreeNode* leftChild;
    TreeNode* rightChild;

    TreeNode(int data) {
        value = data;
        leftChild = rightChild = nullptr;
    }
};

TreeNode* insertNode(TreeNode* currentRoot, int data) {
    if (currentRoot == nullptr)
        return new TreeNode(data);

    if (data < currentRoot->value)
        currentRoot->leftChild = insertNode(currentRoot->leftChild, data);
    else
        currentRoot->rightChild = insertNode(currentRoot->rightChild, data);

    return currentRoot;
}

// Inorder traversal (Left, Root, Right)
void traverseInorder(TreeNode* currentNode) {
    if (currentNode != nullptr) {
        traverseInorder(currentNode->leftChild);
        cout << currentNode->value << " ";
        traverseInorder(currentNode->rightChild);
    }
}

// Preorder traversal (Root, Left, Right)
void traversePreorder(TreeNode* currentNode) {
    if (currentNode != nullptr) {
        cout << currentNode->value << " ";
        traversePreorder(currentNode->leftChild);
        traversePreorder(currentNode->rightChild);
    }
}
// Postorder traversal (Left, Right, Root)
void traversePostorder(TreeNode* currentNode) {
    if (currentNode != nullptr) {
        traversePostorder(currentNode->leftChild);
        traversePostorder(currentNode->rightChild);
        cout << currentNode->value << " ";
    }
}

int main() {
    TreeNode* bstRoot = nullptr;
    int inputValues[] = { 50, 30, 70, 20, 40, 60, 80 };

    for (int item : inputValues) {
        bstRoot = insertNode(bstRoot, item);
    }

    cout << "Inorder traversal: ";
    traverseInorder(bstRoot);
    cout << "\n";

    cout << "Preorder traversal: ";
    traversePreorder(bstRoot);
    cout << "\n";

    cout << "Postorder traversal: ";
    traversePostorder(bstRoot);
    cout << "\n";

    return 0;
}
