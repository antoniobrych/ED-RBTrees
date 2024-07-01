#include "RBT.hpp"


RBTreeNode* createNode(int key) {
    RBTreeNode* node = new RBTreeNode;
    node->key = key;
    node->left = node->right = node->parent = nullptr;
    node->color = RED; // Novos nós são sempre vermelhos inicialmente
    return node;
}

//rotação à esquerda
void rotateLeft(RBTreeNode *&root, RBTreeNode *&node) {
    RBTreeNode *rightChild = node->right;
    node->right = rightChild->left;
    
    if (node->right != nullptr)
        node->right->parent = node;
    
    rightChild->parent = node->parent;
    
    if (node->parent == nullptr)
        root = rightChild;
    else if (node == node->parent->left)
        node->parent->left = rightChild;
    else
        node->parent->right = rightChild;
    
    rightChild->left = node;
    node->parent = rightChild;
}

//rotação à direita
void rotateRight(RBTreeNode *&root, RBTreeNode *&node) {
    RBTreeNode *leftChild = node->left;
    node->left = leftChild->right;
    
    if (node->left != nullptr)
        node->left->parent = node;
    
    leftChild->parent = node->parent;
    
    if (node->parent == nullptr)
        root = leftChild;
    else if (node == node->parent->left)
        node->parent->left = leftChild;
    else
        node->parent->right = leftChild;
    
    leftChild->right = node;
    node->parent = leftChild;
}

//corrigindo a árvore após a inserção
void fixInsertRBTree(RBTreeNode *&root, RBTreeNode *&node) {
    RBTreeNode *parent = nullptr;
    RBTreeNode *grandparent = nullptr;
    
    while (node != root && node->color != BLACK && node->parent->color == RED) {
        parent = node->parent;
        grandparent = parent->parent;
        
        // pai do nó é filho esquerdo do avô
        if (parent == grandparent->left) {
            RBTreeNode *uncle = grandparent->right;
            
            // tio vermelho
            if (uncle != nullptr && uncle->color == RED) {
                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                node = grandparent;
            } else {
                //Caso onde nó é filho direito - rotação à esquerda
                if (node == parent->right) {
                    rotateLeft(root, parent);
                    node = parent;
                    parent = node->parent;
                }
                
                // Caso onde nó  é filho esquerdo - rotação à direita
                rotateRight(root, grandparent);
                swap(parent->color, grandparent->color);
                node = parent;
            }
        } else {
            //Caso onde pai do nó é filho direito do avô
            RBTreeNode *uncle = grandparent->left;
            
            //tio também é vermelho
            if (uncle != nullptr && uncle->color == RED) {
                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                node = grandparent;
            } else {
                //Caso onde é filho esquerdo - rotação à direita
                if (node == parent->left) {
                    rotateRight(root, parent);
                    node = parent;
                    parent = node->parent;
                }
                
                //Caso onde nó é filho direito - rotação à esquerda
                rotateLeft(root, grandparent);
                swap(parent->color, grandparent->color);
                node = parent;
            }
        }
    }
    root->color = BLACK;
}

//função para inserir um novo nó na árvore
void insertRBTree(RBTreeNode *&root, int key) {
    RBTreeNode *node = createNode(key);
    RBTreeNode *parent = nullptr;
    RBTreeNode *current = root;
    
    //encontrando posição de inserção
    while (current != nullptr) {
        parent = current;
        if (key < current->key)
            current = current->left;
        else
            current = current->right;
    }
    
    //inserindo o novo nó
    node->parent = parent;
    if (parent == nullptr)
        root = node;
    else if (key < parent->key)
        parent->left = node;
    else
        parent->right = node;
    
    //corrigindo a árvore (após as operaçoes)
    fixInsertRBTree(root, node);
}

//Realizar todo o percurso em ordem simétrica (inorder)
void inorderHelper(RBTreeNode *node,bool verbose) {
    if (node == nullptr)
        return;
    
    inorderHelper(node->left,verbose);
    if (verbose)
        cout << node->key << " ";

    inorderHelper(node->right,verbose);
}

// Função para realizar busca por um nó específico
RBTreeNode* searchRBTree(RBTreeNode* node, int key) {
    if (node == nullptr || node->key == key)
        return node;

    if (key < node->key)
        return searchRBTree(node->left, key);

    return searchRBTree(node->right, key);
}

//Função para encontrar o nó mínimo 
RBTreeNode* minimumRBTree(RBTreeNode* node) {
    RBTreeNode* current = node;
    while (current != nullptr && current->left != nullptr)
        current = current->left;
    return current;
}

// Função para encontrar o nó máximo
RBTreeNode* maximumRBTree(RBTreeNode* node) {
    RBTreeNode* current = node;
    while (current != nullptr && current->right != nullptr)
        current = current->right;
    return current;
}

// Função para calcular a altura da árvore
int heightRBTree(RBTreeNode* node) {
    if (node == nullptr)
        return 0;
    else {
        int leftHeight = heightRBTree(node->left);
        int rightHeight = heightRBTree(node->right);
        return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
    }
}

// Função para liberar a memória da árvore
void deleteRBTree(RBTreeNode* node) {
    if (node == nullptr)
        return;
    deleteRBTree(node->left);
    deleteRBTree(node->right);
    delete node;
}