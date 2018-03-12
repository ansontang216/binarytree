#include <iostream>
using namespace std;

struct Node{
    int value;
    struct Node *left;
    struct Node *right;
};

struct Node* newNode(int data){
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node -> value = data;
    node -> left = NULL;
    node -> right = NULL;
    return node;
}

//implement insert and remove w/ balancing
Node* insert(struct Node* node, int data){
    if (node == NULL) {
        return newNode(data);
    }

    if (data <= node -> value) {
        struct Node *leftChild = insert(node -> left, data);
        node -> left = leftChild;

    } else if(data > node -> value) {
        struct Node *rightChild = insert(node -> right, data);
        node -> right = rightChild;

    }

    return node;
}

void printTree(struct Node *root){
    if(root == NULL) {
        return;
    }

    if(root -> left != NULL) {
        printTree(root->left);
    }

    cout << root->value << endl;

    if(root -> right != NULL) {
        printTree(root->right);
    }
}

int maxDepth(struct Node* tree){
    if(tree == NULL){
        return 0;
    }

    int leftCount = maxDepth(tree -> left);
    int rightCount = maxDepth(tree -> right);

    if(leftCount >= rightCount) {
        return leftCount + 1;
    } else {
        return rightCount + 1;
    }
}

int numberOfElements(Node* tree) {
    if(tree == NULL){
        return 0;
    }

    int leftCount = numberOfElements(tree -> left);
    int rightCount = numberOfElements(tree -> right);

    int total = leftCount + rightCount + 1;
    return total;
}

bool hasNoChild(Node* node) {
    if(node -> left == NULL or node -> right == NULL) {
        return true;
    }
    return false;
}

struct Node* getLeftSide(struct Node* node) {
    Node* rightSide = node -> right;
    Node* leftSideOnly = newNode(node->value);
    leftSideOnly -> left = node -> left;
    return leftSideOnly;
}

struct Node* mergeTree(struct Node* firstTree, struct Node* secondTree) {
    if (firstTree == NULL) {
        return secondTree;
    } else if (secondTree == NULL) {
        return firstTree;
    } else {
        Node *newTree;
        if (firstTree->value <= secondTree->value) {
            mergeTree(getLeftSide(firstTree), secondTree->left);
            if (firstTree->right->value <= secondTree->value) {//here
                mergeTree(firstTree->right, secondTree->left);
            } else {
                mergeTree(firstTree->right, secondTree->right);
            }
        }

        if (firstTree->value > secondTree->value) {
            mergeTree(firstTree, secondTree->right);
            if (firstTree->left->value <= secondTree->value) {
                mergeTree(firstTree->left, secondTree->left);
            } else {
                mergeTree(firstTree->left, secondTree->right);
            }
        }
    }
}

int main() {
    Node* treeA = insert(NULL, 3);
    treeA = insert(treeA, 1);
    treeA = insert(treeA, 5);
    treeA = insert(treeA, 7);
    printf("Tree A: ");
    printTree(treeA);
    printf("\n");
    Node* treeB = insert(NULL, 6);
    treeB = insert(treeB, 4);
    treeB = insert(treeB, 2);
    treeB = insert(treeB, 8);
    printf("Tree B: ");
    printTree(treeB);
    printf("\n");
    Node* mergedTree = mergeTree(treeA, treeB);
    printf("Merged Tree: ");
    printTree(mergedTree);
}



