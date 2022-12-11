#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef int Value;

typedef struct Node {
    Value value;
    unsigned char height;
    struct Node* left;
    struct Node* right;
} Node;

unsigned char height(Node* node); //посмотреть высоту вершины
char balance_factor(Node* node); //разница высот поддеревьев
void fixheight(Node* node); //обновление высоты
Node* LeftRotation(Node* node); //левый поворот
Node* RightRotation(Node* node); //правый поворот
Node* balance(Node* node); //балансировка 
Node* tree_add(Node* node, Node* new_node, Value data); //добавить новую вершину

int main(void) {
    int n, data;
    if (!scanf("%d", &n))
        return 0;
    if (n == 0) {
        printf("0");
        return 0;
    }
    Node* tree = malloc(sizeof(Node) * n);
    assert(tree);
    Node* root = NULL;
    for (int i = 0; i < n; ++i) {
        if (!scanf("%d", &data)) {
            free(tree);
            return 0;
        }
        root = tree_add(root, &tree[i], data);
    }
    printf("%u", root->height);
    free(tree);
    return 0;
}

unsigned char height(Node* node) {
    return (node ? node->height : 0);
}

char balance_factor(Node* node) {
    return height(node->right) - height(node->left);
}

void fixheight(Node* node) {
    unsigned char h_left = height(node->left);
    unsigned char h_right = height(node->right);
    node->height = (h_left > h_right ? h_left : h_right) + 1;
}

Node* LeftRotation(Node* node) {
    Node* q = node->right;
    node->right = q->left;
    q->left = node;
    fixheight(node);
    fixheight(q);
    return q;
}

Node* RightRotation(Node* node) {
    Node* q = node->left;
    node->left = q->right;
    q->right = node;
    fixheight(node);
    fixheight(q);
    return q;
}

Node* balance(Node* node) {
    fixheight(node);
    char bfactor;
    bfactor = balance_factor(node);
    if (bfactor == 2) {
        if (balance_factor(node->right) < 0)
            node->right = RightRotation(node->right);
        node = LeftRotation(node);
    }
    if (bfactor == -2) {
        if (balance_factor(node->left) > 0) 
            node->left = LeftRotation(node->left);
        node = RightRotation(node);
    }
    return node;
}

Node* tree_add(Node* node, Node* new_node, Value data) {
    if (node == NULL) {
        node = new_node;
        node->value = data;
        node->height = 1;
        node->left = NULL;
        node->right = NULL;
        return node;
    }
    if (data < node->value)
        node->left = tree_add(node->left, new_node, data);
    if (data >= node->value) 
        node->right = tree_add(node->right, new_node, data);
    return balance(node);
}
