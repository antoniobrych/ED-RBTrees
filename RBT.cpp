#include <iostream>
#include "RBT.hpp"

using namespace std;
using namespace std::chrono;

int main() {
    RBTreeNode *root = nullptr;
    cout<<"==== TESTES ===="<<endl;
    // Inserção de alguns nós para teste e medição do tempo de execução
    int numElements = 10000; // Número de elementos para inserir na árvore
    auto start = high_resolution_clock::now();

    for (int i = 1; i <= numElements; ++i) {
        insertRBTree(root,i);
    }

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(end - start).count();
    cout << "\nTempo de inserção de " << numElements << " elementos: " << duration << " nanosegundos" << endl;

    // Exemplo de percurso em ordem simétrica (inorder)
    cout << "\nInorder traversal: ";
    inorderHelper(root,false);
    cout << endl;

    //exemplo de busca e medição do tempo de execução
    int keyToSearch = numElements / 2;
    start = high_resolution_clock::now();
    RBTreeNode *searchResult = searchRBTree(root, keyToSearch);
    end = high_resolution_clock::now();
    duration = duration_cast<nanoseconds>(end - start).count();
    //busca com elemento que está na árvore
    if (searchResult != nullptr) {
        cout << "\nNó " << keyToSearch << " encontrado." << endl;
    } else {
        cout << "\nNó " << keyToSearch << " não encontrado." << endl;
    }
    cout << "\nTempo de busca: " << duration << " nanosegundos" << endl;

    int keyToSearch2 = numElements+1;
    start = high_resolution_clock::now();
    RBTreeNode *searchResult2 = searchRBTree(root, keyToSearch2);
    end = high_resolution_clock::now();
    duration = duration_cast<nanoseconds>(end - start).count();
    //busca com elemento que não está na árvore
    if (searchResult2 != nullptr) {
        cout << "\nNó " << keyToSearch2 << " encontrado." << endl;
    } else {
        cout << "\nNó " << keyToSearch2 << " não encontrado." << endl;
    }
    cout << "\nTempo de busca: " << duration << " nanosegundos" << endl;

    //exemplo de busca do mínimo e máximo
    start = high_resolution_clock::now();
    RBTreeNode *minNode = minimumRBTree(root);
    end = high_resolution_clock::now();
    duration = duration_cast<nanoseconds>(end - start).count();
    if (minNode != nullptr) {
        cout << "\nNó mínimo: " << minNode->key << " (Tempo: " << duration << " nanosegundos)" << endl;
    }

    start = high_resolution_clock::now();
    RBTreeNode *maxNode = maximumRBTree(root);
    end = high_resolution_clock::now();
    duration = duration_cast<nanoseconds>(end - start).count();
    if (maxNode != nullptr) {
        cout << "\nNó máximo: " << maxNode->key << " (Tempo: " << duration << " nanosegundos)" << endl;
    }

    //exemplo de cálculo da altura da árvore
    start = high_resolution_clock::now();
    int treeHeight = heightRBTree(root);
    end = high_resolution_clock::now();
    duration = duration_cast<nanoseconds>(end - start).count();
    cout << "\nAltura da árvore: " << treeHeight << " (Tempo: " << duration << " nanosegundos)" << endl;

    //libera a memória alocada pela árvore
    start = high_resolution_clock::now();
    deleteRBTree(root);
    end = high_resolution_clock::now();
    duration = duration_cast<nanoseconds>(end - start).count();
    cout << "\nTempo para liberar a memória: " << duration << " nanosegundos" << endl;

    return 0;
}
