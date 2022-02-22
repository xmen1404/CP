#include<bits/stdc++.h>
#include "../Implementations/Treap.hpp"

using namespace std;

#define FOR(a, b, c) for(int a = b; a <= c; ++a)
#define FORW(a, b, c) for(int a = b; a >= c; --a)
#define pb push_back
#define fi first
#define se second

typedef pair<int, int> ii;

const int N = 2e5 + 100;

int n, T;
int t[N];
map<int, int> mp;
set<int> st;

void dfs(Treap u) {
    cout << u.key << ' ' << u.prior << '\n';
    if(u.leftChild) {
        dfs(*(u.leftChild));
    }
    if(u.rightChild) {
        dfs(*(u.rightChild));
    }
}

void test01() {
    Treap node0 = Treap(1, 6);
    Treap node1 = Treap(2, 3);
    Treap node2 = Treap(3, 9);
    Treap node3 = Treap(4, 2);
    Treap node4 = Treap(5, 7);
    trInsert(&node0, &node1);
    trInsert(&node0, &node2);
    trInsert(&node0, &node3);
    trInsert(&node0, &node4);
    dfs(node0);
}

signed main() {
    // freopen("test.inp", "r", stdin);
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    test()
}