#include <iostream>
using namespace std;
struct AVLNode {
    int key;
    AVLNode* leftChild;
    AVLNode* rightChild;
    int nodeHeight;

    AVLNode(int value) {
        key = value;
        leftChild = rightChild = nullptr;
        nodeHeight = 1;
    }
};
int getHeight(AVLNode* currentNode) {
    if (currentNode == nullptr)
        return 0;
    return currentNode->nodeHeight;
}
int getBalanceFactor(AVLNode* currentNode) {
    if (currentNode == nullptr)
        return 0;
    return getHeight(currentNode->leftChild) - getHeight(currentNode->rightChild);
}

void updateNodeHeight(AVLNode* currentNode) {
    currentNode->nodeHeight = 1 + max(getHeight(currentNode->leftChild), getHeight(currentNode->rightChild));
}
AVLNode* performRightRotation(AVLNode* yNode) {
    AVLNode* xNode = yNode->leftChild;
    AVLNode* subtree = xNode->rightChild;

    xNode->rightChild = yNode;
    yNode->leftChild = subtree;

    updateNodeHeight(yNode);
    updateNodeHeight(xNode);

    return xNode;
}

AVLNode* performLeftRotation(AVLNode* xNode) {
    AVLNode* yNode = xNode->rightChild;
    AVLNode* subtree = yNode->leftChild;

    yNode->leftChild = xNode;
    xNode->rightChild = subtree;

    updateNodeHeight(xNode);
    updateNodeHeight(yNode);

    return yNode;
}

AVLNode* insertIntoAVL(AVLNode* currentRoot, int newValue) {
    if (currentRoot == nullptr)
        return new AVLNode(newValue);

    if (newValue < currentRoot->key)
        currentRoot->leftChild = insertIntoAVL(currentRoot->leftChild, newValue);
    else if (newValue > currentRoot->key)
        currentRoot->rightChild = insertIntoAVL(currentRoot->rightChild, newValue);
    else
        return currentRoot;

    updateNodeHeight(currentRoot);
    int balance = getBalanceFactor(currentRoot);

    // Left Left Case
    if (balance > 1 && newValue < currentRoot->leftChild->key)
        return performRightRotation(currentRoot);

    // Right Right Case
    if (balance < -1 && newValue > currentRoot->rightChild->key)
        return performLeftRotation(currentRoot);

    // Left Right Case
    if (balance > 1 && newValue > currentRoot->leftChild->key) {
        currentRoot->leftChild = performLeftRotation(currentRoot->leftChild);
        return performRightRotation(currentRoot);
    }

    // Right Left Case
    if (balance < -1 && newValue < currentRoot->rightChild->key) {
        currentRoot->rightChild = performRightRotation(currentRoot->rightChild);
        return performLeftRotation(currentRoot);
    }

    return currentRoot;
}

// Inorder traversal
void printInorder(AVLNode* rootNode) {
    if (rootNode != nullptr) {
        printInorder(rootNode->leftChild);
        cout << rootNode->key << " ";
        printInorder(rootNode->rightChild);
    }
}

// Preorder traversal
void printPreorder(AVLNode* rootNode) {
    if (rootNode != nullptr) {
        cout << rootNode->key << " ";
        printPreorder(rootNode->leftChild);
        printPreorder(rootNode->rightChild);
    }
}

// Postorder traversal
void printPostorder(AVLNode* rootNode) {
    if (rootNode != nullptr) {
        printPostorder(rootNode->leftChild);
        printPostorder(rootNode->rightChild);
        cout << rootNode->key << " ";
    }
}
int main() {
    AVLNode* avlRoot = nullptr;
    int elements[] = { 10, 20, 30, 40, 50, 25 };
    for (int element : elements) {
        avlRoot = insertIntoAVL(avlRoot, element);
    }
    cout << "Inorder traversal: ";
    printInorder(avlRoot);
    cout << "\n";

    cout << "Preorder traversal: ";
    printPreorder(avlRoot);
    cout << "\n";

    cout << "Postorder traversal: ";
    printPostorder(avlRoot);
    cout << "\n";
    return 0;
}
