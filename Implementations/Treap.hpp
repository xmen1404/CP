#include<bits/stdc++.h>
using namespace std;

// tested with CF863D (excluding Union function)
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

// ptreap trUnion(ptreap l, ptreap r) { // not tested
//     if(!l || !r) {
//         return l ? l : r;
//     }
//     if(l->prior < r->prior) swap(l, r);
    
//     ptreap r1, r2;
//     trSplit(r, l->key, r1, r2);
//     l->leftChild = trUnion(l->leftChild, r1);
//     l->rightChild = trUnion(l->rightChild, r2);
//     return l;
// }




