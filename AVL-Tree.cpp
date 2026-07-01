#include <iostream>
#include <stdexcept>
#include <queue>
#include <limits>
#include <algorithm>

using namespace std;

/*
----------------------------------------------------
AVL Tree IMPLEMENTATION AND ANALYSIS
Language: C++17

Major Operation Complexities:
Insert       : O(log n)
Delete       : O(log n)
Search       : O(log n)
Predecessor  : O(log n)
Successor    : O(log n)
Traversal    : O(n)
Clear        : O(n)
----------------------------------------------------
*/

class AVLTree {
private:

    struct Node {
        int key;
        int height;

        Node* left;
        Node* right;

        explicit Node(int value)
            : key(value),
              height(1),
              left(nullptr),
              right(nullptr) {}
    };

    Node* root;
    size_t nodeCount;

private:

    int getHeight(Node* node) const {
        return node ? node->height : 0;
    }

    int getBalance(Node* node) const {
        if (!node)
            return 0;

        return getHeight(node->left) -
               getHeight(node->right);
    }

    void updateHeight(Node* node) {
        node->height =
            1 + max(getHeight(node->left),
                    getHeight(node->right));
    }

    Node* rotateRight(Node* y) {

        Node* x = y->left;
        Node* t2 = x->right;

        x->right = y;
        y->left = t2;

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    Node* rotateLeft(Node* x) {

        Node* y = x->right;
        Node* t2 = y->left;

        y->left = x;
        x->right = t2;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    Node* balance(Node* node) {

        updateHeight(node);

        int bf = getBalance(node);

        // Left Left
        if (bf > 1 &&
            getBalance(node->left) >= 0)
            return rotateRight(node);

        // Left Right
        if (bf > 1 &&
            getBalance(node->left) < 0) {

            node->left =
                rotateLeft(node->left);

            return rotateRight(node);
        }

        // Right Right
        if (bf < -1 &&
            getBalance(node->right) <= 0)
            return rotateLeft(node);

        // Right Left
        if (bf < -1 &&
            getBalance(node->right) > 0) {

            node->right =
                rotateRight(node->right);

            return rotateLeft(node);
        }

        return node;
    }

    Node* insertNode(Node* node,
                     int key,
                     bool& inserted) {

        if (!node) {
            inserted = true;
            return new Node(key);
        }

        if (key < node->key)
            node->left =
                insertNode(node->left,
                           key,
                           inserted);

        else if (key > node->key)
            node->right =
                insertNode(node->right,
                           key,
                           inserted);

        else
            return node;

        return balance(node);
    }

    Node* minNode(Node* node) const {

        while (node && node->left)
            node = node->left;

        return node;
    }

    Node* maxNode(Node* node) const {

        while (node && node->right)
            node = node->right;

        return node;
    }

    Node* deleteNode(Node* node,
                     int key,
                     bool& deleted) {

        if (!node)
            return nullptr;

        if (key < node->key) {

            node->left =
                deleteNode(node->left,
                           key,
                           deleted);
        }
        else if (key > node->key) {

            node->right =
                deleteNode(node->right,
                           key,
                           deleted);
        }
        else {

            deleted = true;

            if (!node->left ||
                !node->right) {

                Node* temp =
                    node->left ?
                    node->left :
                    node->right;

                delete node;
                return temp;
            }

            Node* successor =
                minNode(node->right);

            node->key =
                successor->key;

            node->right =
                deleteNode(node->right,
                           successor->key,
                           deleted);
        }

        return balance(node);
    }

    bool searchNode(Node* node,
                    int key) const {

        if (!node)
            return false;

        if (key == node->key)
            return true;

        if (key < node->key)
            return searchNode(node->left,
                              key);

        return searchNode(node->right,
                          key);
    }

    void inorder(Node* node) const {

        if (!node)
            return;

        inorder(node->left);

        cout << node->key << " ";

        inorder(node->right);
    }

    void preorder(Node* node) const {

        if (!node)
            return;

        cout << node->key << " ";

        preorder(node->left);
        preorder(node->right);
    }

    void postorder(Node* node) const {

        if (!node)
            return;

        postorder(node->left);
        postorder(node->right);

        cout << node->key << " ";
    }

    void destroy(Node* node) {

        if (!node)
            return;

        destroy(node->left);
        destroy(node->right);

        delete node;
    }

public:

    AVLTree()
        : root(nullptr),
          nodeCount(0) {}

    ~AVLTree() {
        destroy(root);
    }

    bool insert(int key) {

        bool inserted = false;

        root = insertNode(root,
                          key,
                          inserted);

        if (inserted)
            ++nodeCount;

        return inserted;
    }

    bool remove(int key) {

        bool deleted = false;

        root = deleteNode(root,
                          key,
                          deleted);

        if (deleted)
            --nodeCount;

        return deleted;
    }

    bool search(int key) const {
        return searchNode(root, key);
    }

    bool update(int oldKey,
                int newKey) {

        if (!search(oldKey))
            return false;

        if (search(newKey))
            return false;

        remove(oldKey);
        insert(newKey);

        return true;
    }

    int minimum() const {

        Node* node = minNode(root);

        if (!node)
            throw runtime_error("Tree Empty");

        return node->key;
    }

    int maximum() const {

        Node* node = maxNode(root);

        if (!node)
            throw runtime_error("Tree Empty");

        return node->key;
    }

    bool predecessor(int key,
                     int& result) const {

        Node* current = root;
        bool found = false;

        while (current) {

            if (key > current->key) {

                result = current->key;
                found = true;
                current = current->right;
            }
            else {
                current = current->left;
            }
        }

        return found;
    }

    bool successor(int key,
                   int& result) const {

        Node* current = root;
        bool found = false;

        while (current) {

            if (key < current->key) {

                result = current->key;
                found = true;
                current = current->left;
            }
            else {
                current = current->right;
            }
        }

        return found;
    }

    size_t count() const {
        return nodeCount;
    }

    int height() const {
        return getHeight(root);
    }

    void displayInorder() const {

        cout << "\nInorder: ";

        inorder(root);

        cout << "\n";
    }

    void displayPreorder() const {

        cout << "\nPreorder: ";

        preorder(root);

        cout << "\n";
    }

    void displayPostorder() const {

        cout << "\nPostorder: ";

        postorder(root);

        cout << "\n";
    }

    void displayLevelOrder() const {

        cout << "\nLevel Order: ";

        if (!root) {
            cout << "Tree Empty\n";
            return;
        }

        queue<Node*> q;
        q.push(root);

        while (!q.empty()) {

            Node* current = q.front();
            q.pop();

            cout << current->key << " ";

            if (current->left)
                q.push(current->left);

            if (current->right)
                q.push(current->right);
        }

        cout << "\n";
    }
    void clear() {
        destroy(root);
            
        root = nullptr;
        nodeCount = 0;
    }
};

int getIntegerInput() {

    int value;

    while (!(cin >> value)) {

        cout << "Invalid input. Enter integer: ";

        cin.clear();

        cin.ignore(
            numeric_limits<streamsize>::max(),
            '\n');
    }

    return value;
}

int main() {

    AVLTree tree;

    int choice;

    while (true) {

        cout << "\n=================================\n";
        cout << " AVL TREE IMPLEMENTATION\n";
        cout << "=================================\n";

        cout << "1. Insert\n";
        cout << "2. Delete\n";
        cout << "3. Search\n";
        cout << "4. Display Inorder\n";
        cout << "5. Display Preorder\n";
        cout << "6. Display Postorder\n";
        cout << "7. Display Level Order\n";
        cout << "8. Count Elements\n";
        cout << "9. Minimum\n";
        cout << "10. Maximum\n";
        cout << "11. Predecessor\n";
        cout << "12. Successor\n";
        cout << "13. Update Value\n";
        cout << "14. Tree Statistics\n";
        cout << "15. Clear Tree\n";
        cout << "16. Exit\n";

        cout << "\nChoice: ";

        choice = getIntegerInput();

        int value;
        int result;

        switch (choice) {

        case 1:
            cout << "Enter value: ";
            value = getIntegerInput();

            if (tree.insert(value))
                cout << "Inserted Successfully\n";
            else
                cout << "Duplicate Value\n";
            break;

        case 2:
            cout << "Enter value: ";
            value = getIntegerInput();

            if (tree.remove(value))
                cout << "Deleted Successfully\n";
            else
                cout << "Value Not Found\n";
            break;

        case 3:
            cout << "Enter value: ";
            value = getIntegerInput();

            cout << (tree.search(value) ?
                "Found\n" : "Not Found\n");
            break;

        case 4:
            tree.displayInorder();
            break;

        case 5:
            tree.displayPreorder();
            break;

        case 6:
            tree.displayPostorder();
            break;

        case 7:
            tree.displayLevelOrder();
            break;

        case 8:
            cout << "Total Nodes: "
                 << tree.count()
                 << "\n";
            break;

        case 9:
            try {
                cout << "Minimum: "
                     << tree.minimum()
                     << "\n";
            }
            catch (...) {
                cout << "Tree Empty\n";
            }
            break;

        case 10:
            try {
                cout << "Maximum: "
                     << tree.maximum()
                     << "\n";
            }
            catch (...) {
                cout << "Tree Empty\n";
            }
            break;

        case 11:
            cout << "Enter key: ";
            value = getIntegerInput();

            if (tree.predecessor(value,
                                 result))
                cout << "Predecessor: "
                     << result << "\n";
            else
                cout << "No Predecessor\n";
            break;

        case 12:
            cout << "Enter key: ";
            value = getIntegerInput();

            if (tree.successor(value,
                               result))
                cout << "Successor: "
                     << result << "\n";
            else
                cout << "No Successor\n";
            break;

        case 13:
        {
            int oldValue;
            int newValue;

            cout << "Old Value: ";
            oldValue = getIntegerInput();

            cout << "New Value: ";
            newValue = getIntegerInput();

            if (tree.update(oldValue,
                            newValue))
                cout << "Updated\n";
            else
                cout << "Update Failed\n";

            break;
        }

        case 14:
            cout << "\nTree Statistics\n";
            cout << "---------------\n";
            cout << "Node Count : "
                 << tree.count()
                 << "\n";
            cout << "Height     : "
                 << tree.height()
                 << "\n";
            break;

        case 15:
            tree.clear();
            cout << "Tree cleared successfully.\n";
            break;

        case 16:
            cout << "Thank You\n";
            return 0;

        default:
            cout << "Invalid Choice\n";
        }
    }
}
