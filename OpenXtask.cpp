#include <bits/stdc++.h>

using namespace std;

mt19937 gen(chrono::system_clock::now().time_since_epoch().count());

struct node {
    node *L, *R;
    int value;
    node() : L(nullptr), R(nullptr), value(-1) {};
    node(int x) : L(nullptr), R(nullptr), value(x) {};
};

int leaf_count(node *root) {
    if (!root) {
        return false;
    }
    if (root -> L == nullptr && root -> R == nullptr) {
        return true;
    }
    return leaf_count(root -> L) + leaf_count(root -> R);
}

int longest_path_to_leaf(node *root) {
    if (!root) {
        return 0;
    }
    int ans_for_left_child = 0, ans_for_right_child = 0;
    if (root -> L != nullptr) {
        ans_for_left_child = longest_path_to_leaf(root -> L) + 1;
    }
    if (root -> R != nullptr) {
        ans_for_right_child = longest_path_to_leaf(root -> R) + 1;
    }
    return max(ans_for_left_child, ans_for_right_child);
}

bool compare(node *root1, node *root2) {
    if ((!root1 && root2) || (root1 && !root2)) {
        return false;
    }
    if (root1 == nullptr && root2 == nullptr) {
        return true;
    }
    if (root1 -> value != root2 -> value) {
        return false;
    }
    if (compare(root1 -> L, root2 -> L) == false) {
        return false;
    }
    if (compare(root1 -> R, root2 -> R) == false) {
        return false;
    }
    return true;
}

void empty_tree_test() {
    //here we test case when node is empty
    node *root1 = nullptr;
    node *root2 = nullptr;
    if (leaf_count(root1) != 0) {
        cout << "ERROR IN EMPTY TREE TEST\n";
        return;
    }
    if (longest_path_to_leaf(root1) != 0) {
        cout << "ERROR IN EMPTY TREE TEST\n";
        return;
    }
    if (compare(root1, root2) != true) {
        cout << "ERROR IN EMPTY TREE TEST\n";
        return;
    }
    cout << "EMPTY TEST PASSED\n";
}

void one_node_tree_test() {
    //here we test case when whole tree is just one node
    node *root1 = new node(1);
    node *root2 = nullptr;
    if (leaf_count(root1) != 1) {
        cout << "ERROR IN ONE NODE TREE TEST\n";
        return;
    }
    if (longest_path_to_leaf(root1) != 0) {
        cout << "ERROR IN ONE NODE TREE TEST\n";
        return;
    }
    if (compare(root1, root2) != false) {
        cout << "ERROR IN ONE NODE TREE TEST\n";
        return;
    }
    root2 = new node(2);
    if (compare(root1, root2) != false) {
        cout << "ERROR IN ONE NODE TREE TEST\n";
        return;
    }
    root2 = new node(1);
     if (compare(root1, root2) != true) {
        cout << "ERROR IN ONE NODE TREE TEST\n";
        return;
    }
    cout << "ONE NODE TREE TEST PASSED\n";
}

void chain_tree_test() {
    //here we test case when our tree is chain
    node *root1 = new node(1);
    node *root2 = new node(1);
    node *last_child = root1;
    for (int length = 0; length < 10; ++length) {
        node *new_vertex = new node(length);
        last_child -> L = new_vertex;
        last_child = new_vertex;
    }
    last_child = root2;
    for (int length = 0; length < 10; ++length) {
        node *new_vertex = new node(length);
        last_child -> L = new_vertex;
        last_child = new_vertex;
    }
    if (leaf_count(root1) != 1) {
        cout << "ERROR IN CHAIN TREE TEST\n";
        return;
    }
    if (longest_path_to_leaf(root1) != 10) {
        cout << "ERROR IN CHAIN TREE TEST\n";
        return;
    }
     if (compare(root1, root2) != true) {
        cout << "ERROR IN CHAIN TREE TEST\n";
        return;
    }
    last_child -> value = 42;
     if (compare(root1, root2) != false) {
        cout << "ERROR IN CHAIN TREE TEST\n";
        return;
    }
    cout << "CHAIN TREE TEST PASSED\n";
}

void random_tree_test() {
    //very good test which test functions on random built tree.
    node* root = new node(gen() % 100);
    vector < pair < node*, int > > future_sons;
     //pair {v, f} in this vector mean, that we want to add left son to vertex v if f < -1,
     //and right son if f > 1. abs(f) will mean the depth of this son (it will help to find the answer to queries)
    future_sons.push_back({root, -1});
    future_sons.push_back({root, 1});
    int max_depth = 0, current_depth;
    int iteration_count = gen() % 100 + 1;
    for (int iteration = 0; iteration < iteration_count; ++iteration) {
        int ind = gen() % (int)(future_sons.size());
        node* new_node = new node(gen() % 100);
        current_depth = abs(future_sons[ind].second);
        max_depth = max(max_depth, current_depth);
        if (future_sons[ind].second < 0) {
            future_sons[ind].first -> L = new_node;
            future_sons.erase(future_sons.begin() + ind);
            ++current_depth;
            future_sons.push_back({new_node, -current_depth});
            future_sons.push_back({new_node, current_depth});
            continue;
        } else {
            future_sons[ind].first -> R = new_node;
            future_sons.erase(future_sons.begin() + ind);
            ++current_depth;
            future_sons.push_back({new_node, -current_depth});
            future_sons.push_back({new_node, current_depth});
        }
    }
    if (longest_path_to_leaf(root) != max_depth) {
        cout << "ERROR IN RANDOM TREE TEST\n";
        return;
    }
    int leafs_count = 0;
    for (int i = 1; i < (int)(future_sons.size()); ++i) {
        if (future_sons[i].first == future_sons[i - 1].first) {
            ++leafs_count;
        }
    }
    if (leaf_count(root) != leafs_count) {
        cout << "ERROR IN RANDOM TREE TEST\n";
        return;
    }
    cout << "RANDOM TREE TEST PASSED\n";
}

void test() {
    empty_tree_test();
    one_node_tree_test();
    chain_tree_test();
    random_tree_test();
}

main() {
        test();
        return 0;
}

