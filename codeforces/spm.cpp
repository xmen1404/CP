#include<bits/stdc++.h>
// #include "../Implementations/Treap.hpp"
    
using namespace std;
    
#define FOR(a, b, c) for(int a = b; a <= c; ++a)
#define FORW(a, b, c) for(int a = b; a >= c; --a)
#define pb push_back
#define fi first
#define se second
#define int long long
    
typedef pair<int, int> ii;
    
struct Treap {
    int value, prior, sz;
    bool revFlag;
    Treap *leftChild, *rightChild;
    
    Treap() {
        revFlag = false;
    }
    Treap(int nVal, int nprior) {
        revFlag = false;
        value = nVal;
        prior = nprior;
        leftChild = NULL;
        rightChild = NULL;
        sz = 1;
    }
};
typedef Treap* ptreap;
    
void trSwap(ptreap &x, ptreap &y) {
    if(x == NULL && y == NULL) return;
    // return;
    
    if(x == NULL) {
        x = y;
        y = NULL;
    } else if(y == NULL) {
        y = x;
        x = NULL;
    } else {
        swap(x, y);
    }
}
    
void pushLazy(ptreap u) {
    if(u == NULL) return;
    
    if(u->revFlag) {
        trSwap(u->leftChild, u->rightChild);
        if((u->leftChild) != NULL) {
            ptreap v = u->leftChild;
            v->revFlag = 1-v->revFlag;
        }
        if((u->rightChild) != NULL) {
            ptreap v = u->rightChild;
            v->revFlag = 1-v->revFlag;
        }
        u->revFlag = false;
    }
}
    
int getSize(ptreap t) {
    return (t == NULL) ? 0 : t->sz; 
}
    
void trUpd(ptreap t) {
    if(!t) return;
    t->sz = getSize(t->leftChild) + getSize(t->rightChild) + 1;
}
    
void trSplit(ptreap t, int sKey, ptreap & t1, ptreap & t2, int prevSize) {
    pushLazy(t);
    if(!t) {
        t1 = t2 = NULL;
        return;
    }
    int key = getSize(t->leftChild) + prevSize + 1;
    // keys = distinct
    if(key <= sKey) { 
        trSplit(t->rightChild, sKey, t->rightChild, t2, key);
        t1 = t;
    }
    else { // key > sKey
        trSplit(t->leftChild, sKey, t1, t->leftChild, prevSize);
        t2 = t;
    }
    trUpd(t);
}
    
void trMerge(ptreap &t, ptreap t1 , ptreap t2) {
    // t1 keys < t2 keys
    pushLazy(t1);
    pushLazy(t2);
    if((t1 == NULL) || (t2 == NULL)) {
        t = (t1) ? t1 : t2;
    } 
    else if(t1->prior >= t2->prior) {
        trMerge(t1->rightChild, t1->rightChild, t2);
        t = t1;
    } else if(t1->prior < t2->prior) {
        trMerge(t2->leftChild, t1, t2->leftChild);
        t = t2;
    }
    trUpd(t);
}
    
void trInsert(ptreap & t, ptreap nt, int key, int prevSize) {
    pushLazy(t);
    if(!t) {
        t = nt;
        return;
    }
    int tKey = prevSize + getSize(t->leftChild) + 1;
    if(t->prior < nt->prior) {
        trSplit(t, key - 1, nt->leftChild, nt->rightChild, prevSize);
        t = nt;
    } else if(tKey < key) {
        trInsert(t->rightChild, nt, key, tKey);
    } else {
        trInsert(t->leftChild, nt, key, prevSize);
    }
    trUpd(t);
}
    
ptreap trErase(ptreap & t, int key, int prevSize) {
    pushLazy(t);
    if(t == NULL) {
        return NULL;
    }
    int tKey = prevSize + getSize(t->leftChild) + 1;
    if(tKey == key) {
        ptreap temp = t;
        trMerge(t, t->leftChild, t->rightChild);
        temp->leftChild = NULL;
        temp->rightChild = NULL;
        temp->sz = 1;
        return temp;
    } else if(tKey < key) {
        trErase(t->rightChild, key, tKey);
    } else if(tKey > key) {
        trErase(t->leftChild, key, prevSize);
    } else {
        cerr << "key not exists" << '\n';
        return NULL;
    }
}
    
const int N = 2e5 + 100;
    
int n, q, m;
int a[N], ans[N];
Treap tr[N];
ptreap ptr[N];
    
void trTravel(ptreap t, int prevSize) {
    pushLazy(t);
    if(!t) return;
    trTravel(t->leftChild, prevSize);
    int tKey = prevSize + getSize(t->leftChild) + 1;
    ans[tKey] = t->value;
    trTravel(t->rightChild, tKey);
}
    
void dfs(ptreap t, int prev) {
    if(!t) return;
    dfs(t->leftChild, prev);
    cout << "check dfs " << getSize(t->leftChild) + 1 +prev << ' ' << t->prior << '\n';
    dfs(t->rightChild, getSize(t->leftChild) + 1 +prev);
}
    
signed main() {
    // freopen("test.inp", "r", stdin);
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    
    mt19937 mt;
    mt.seed(9187234);
    
    cin >> n >> q >> m;
    FOR(i, 1, n) {
        cin >> a[i];
    }
    
    // Build Treap
    Treap root = Treap(a[1], mt());
    ptreap proot = &root; 
    FOR(i, 2, n)  {
        int prior = mt();
        tr[i] = Treap(a[i], prior);
        ptr[i] = &tr[i];
        trInsert(proot, ptr[i], i, 0);
    }
    
    FOR(i, 1, q) {
        int t, l, r; cin >> t >> l >> r;
        
        if(l == r) continue;
        if(t == 1) {
            // ptreap trRight = trErase(proot, r, 0);
            // trInsert(proot, trRight, l, 0);
            ptreap p1, p2, p3, p4;
            trSplit(proot, r, p3, p4, 0);
            trSplit(p3, r-1, p2, p3, 0);
            trSplit(p2, l-1, p1, p2, 0);
            trMerge(proot, p1, p3);
            trMerge(proot, proot, p2);
            trMerge(proot, proot, p4);
        } else {
            ptreap p1, p2, p3;
            trSplit(proot, r, p2, p3, 0);
            trSplit(p2, l - 1, p1, p2, 0);     
            p2->revFlag = 1 - p2->revFlag;
            trMerge(proot, p1, p2);
            trMerge(proot, proot, p3);
        }
    }
    trTravel(proot, 0);
    // FOR(i, 1, n) cout << ans[i] << ' '; cout << '\n';
    FOR(i, 1, m) {
        int idx; cin >> idx; 
        cout << ans[idx] << ' ';
    }
    return 0;
}