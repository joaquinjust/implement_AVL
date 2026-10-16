#include<bits/stdc++.h>
using namespace::std;

const int N = 200000 + 5;
int n;
int T;
int a[N];
int L[N];
int R[N];
int height[N];
int inorder[N];

void compute_h(int x) {
    if (x == 0) height[x] = -1;
    else {
        compute_h(L[x]);
        compute_h(R[x]);
        height[x] = max(height[L[x]], height[R[x]]) + 1;
    }
}

void get_inorder(int u) {
    if (u == 0) return;
    get_inorder(L[u]);
    inorder[T++] = a[u];
    get_inorder(R[u]);
}

bool is_bst() {
    T = 1;
    get_inorder(1);
    for (int i = 2; i <= n; ++i) {
        if (inorder[i - 1] > inorder[i]) return false;
    }
    return true;
}

bool is_avl() {
    for (int i = 1; i <= n; ++i) {
        int height_l = height[L[i]];
        int height_r = height[R[i]];
        if (abs(height_l - height_r) > 1) return false;
    }
    return true;
}

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--) {
        cin >> n;
        for (int i = 1; i <= n; ++i) {
            cin >> a[i] >> L[i] >> R[i];
        }
        compute_h(1);
        if (not is_bst()) {
            cout << "NINGUNO" << '\n';
            continue;
        }
        if (not is_avl()) {
            cout << "BST" << '\n';
        }
        else {
            cout << "AVL" << '\n';
        }
    }
    return 0;
}
