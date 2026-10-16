#include<bits/stdc++.h>
using namespace::std;

template<typename data_type>
struct AVL {

    struct TreeNode {
        data_type data;
        int height;
        TreeNode* left;
        TreeNode* right;

        TreeNode(data_type data = data_type(), int height = 0,
                    TreeNode* left = nullptr,
                    TreeNode* right = nullptr) :
                    data(data), height(height), left(left), right(right) {}
    };

    TreeNode* root;

    AVL() {
        root = nullptr;
    }

    ~AVL() {
        destroy(root);
    }

    void destroy(TreeNode* u) {
        if (u == nullptr) return;
        destroy(u -> left);
        destroy(u -> right);
        delete u;
    }

    int h(TreeNode* u) {
        return u == nullptr ? -1 : u -> height;
    }

    void update(TreeNode* u) {
        u -> height = 1 + max(h(u -> left) , h(u -> right));
    }

    int FB(TreeNode* u) {
        return h(u -> left) - h(u -> right);
    }

    bool search(data_type key) {
        TreeNode* current = root;
        while (current != nullptr) {
            if (current -> data == key) {
                return true;
            }
            if (current -> data > key) {
                current = current -> left;
            }
            else {
                current = current -> right;
            }
        }
        return false;
    }

    TreeNode* min_element(TreeNode* u) {
        if (u == nullptr) return nullptr;
        TreeNode* current = u;
        while (current -> left != nullptr) {
            current = current -> left;
        }
        return current;
    }

    TreeNode* max_element(TreeNode* u) {
        if (u == nullptr) return nullptr;
        TreeNode* current = u;
        while (current -> right != nullptr) {
            current = current -> right;
        }
        return current;
    }

    TreeNode* min_element() {
        return min_element(root);
    }

    TreeNode* max_element() {
        return max_element(root);
    }

    TreeNode* rotate_left(TreeNode* u) {
        TreeNode* v = u -> right;
        u -> right = v -> left;
        v -> left = u;
        update(u);
        update(v);
        return v;
    }

    TreeNode* rotate_right(TreeNode* u) {
        TreeNode* v = u -> left;
        u -> left = v -> right;
        v -> right = u;
        update(u);
        update(v);
        return v;
    }

    TreeNode* rebalance(TreeNode* u) {
        update(u);
        if (FB(u) > 1) {
            // L
            if (FB(u -> left) < 0) {
                // LR
                u -> left = rotate_left(u -> left);
            }
            return rotate_right(u);
        }
        if (FB(u) < -1) {
            // R
            if (FB(u -> right) > 0) {
                // RL
                u -> right = rotate_right(u -> right);
            }
            return rotate_left(u);
        }
        return u;
    }

    TreeNode* insert(TreeNode* u, data_type value) {
        if (u == nullptr) {
            return new TreeNode(value, 0);
        }
        if (value < u -> data) {
            u -> left = insert(u -> left, value);
        }
        else {
            u -> right = insert(u -> right, value);
        }
        return rebalance(u);
    }

    void insert(data_type value) {
        root = insert(root, value);
    }

    TreeNode* erase(TreeNode* u, data_type key) {
        if (u == nullptr) return nullptr;
        if (key < u -> data) {
            u -> left = erase(u -> left, key);
        }
        else if (key > u -> data) {
            u -> right = erase(u -> right, key);
        }
        else {
            if (u -> left == nullptr) {
                TreeNode* r = u -> right;
                delete u;
                return r;
            }
            if (u -> right == nullptr) {
                TreeNode* l = u -> left;
                delete u;
                return l;
            }
            TreeNode* s = min_element(u -> right);
            u -> data = s -> data;
            u -> right = erase(u -> right, s -> data);
        }
        return rebalance(u);
    }

    void erase(data_type key) {
        root = erase(root, key);
    }

    TreeNode* successor(data_type key) {
        TreeNode* current = root;
        TreeNode* answer = nullptr;
        while (current != nullptr) {
            if (current -> data > key) {
                answer = current;
                current = current -> left;
            }
            else {
                current = current -> right;
            }
        }
        return answer;
    }

    TreeNode* predecessor(data_type key) {
        TreeNode* current = root;
        TreeNode* answer = nullptr;
        while (current != nullptr) {
            if (current -> data < key) {
                answer = current;
                current = current -> right;
            }
            else {
                current = current -> left;
            }
        }
        return answer;
    }

    int verify(TreeNode* u, const data_type* lo, const data_type* hi) {
        if (u == nullptr) return -1;
        if (lo != nullptr and !(*lo < u -> data)) return -2;
        if (hi != nullptr and !(u -> data < *hi)) return -2;
        int a = verify(u -> left, lo, &(u -> data));
        if (a == -2) return -2;
        int b = verify(u -> right, &(u -> data), hi);
        if (b == -2) return -2;
        if (u -> height != 1 + max(a, b)) return -2;
        if (abs(a - b) > 1) return -2;
        return u -> height;
    }

    bool verify() {
        return verify(root, nullptr, nullptr) != -2;
    }

    void print_inorder() {
        print_subtree_inorder(root);
        cout << endl;
    }

    void print_subtree_inorder(TreeNode* u) {
        if (u == nullptr) return;
        print_subtree_inorder(u -> left);
        cout << u -> data << " ";
        print_subtree_inorder(u -> right);
    }

    void print_preorder() {
        print_subtree_preorder(root);
        cout << endl;
    }

    void print_subtree_preorder(TreeNode* u) {
        if (u == nullptr) return;
        cout << u -> data << " ";
        print_subtree_preorder(u -> left);
        print_subtree_preorder(u -> right);
    }

    void print_postorder() {
        print_subtree_postorder(root);
        cout << endl;
    }

    void print_subtree_postorder(TreeNode* u) {
        if (u == nullptr) return;
        print_subtree_postorder(u -> left);
        print_subtree_postorder(u -> right);
        cout << u -> data << " ";
    }
};

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int q;
    cin >> q;
    AVL<int> T;
    while (q--) {
        string op;
        cin >> op;
        if (op == "insert") {
            int x;
            cin >> x;
            T.insert(x);
            cout << "insertado " << x << " | altura = " << T.h(T.root) << ", raiz = " << T.root -> data << '\n';
        }
        else if (op == "erase") {
            int x;
            cin >> x;
            if (!T.search(x)) {
                cout << x << " no esta en el arbol\n";
            }
            else {
                T.erase(x);
                cout << "eliminado " << x << " | altura = " << T.h(T.root);
                if (T.root != nullptr) cout << ", raiz = " << T.root -> data;
                cout << '\n';
            }
        }
        else if (op == "search") {
            int x;
            cin >> x;
            if (T.search(x)) cout << x << " esta\n";
            else cout << x << " no esta\n";
        }
        else if (op == "min") {
            if (T.root == nullptr) cout << "arbol vacio\n";
            else cout << "min = " << T.min_element() -> data << '\n';
        }
        else if (op == "max") {
            if (T.root == nullptr) cout << "arbol vacio\n";
            else cout << "max = " << T.max_element() -> data << '\n';
        }
        else if (op == "succ") {
            int x;
            cin >> x;
            auto s = T.successor(x);
            if (s == nullptr) cout << "no hay sucesor de " << x << '\n';
            else cout << "sucesor de " << x << " = " << s -> data << '\n';
        }
        else if (op == "pred") {
            int x;
            cin >> x;
            auto p = T.predecessor(x);
            if (p == nullptr) cout << "no hay predecesor de " << x << '\n';
            else cout << "predecesor de " << x << " = " << p -> data << '\n';
        }
        else if (op == "height") {
            cout << "altura = " << T.h(T.root) << '\n';
        }
        else if (op == "inorder") {
            T.print_inorder();
        }
        else if (op == "preorder") {
            T.print_preorder();
        }
        else if (op == "postorder") {
            T.print_postorder();
        }
        else if (op == "verify") {
            if (T.verify()) cout << "AVL valido\n";
            else cout << "AVL INVALIDO\n";
        }
        else {
            cout << "comando desconocido: " << op << '\n';
        }
    }
    return 0;
}
