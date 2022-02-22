#include<bits/stdc++.h>
using namespace std;

struct Treap {
    int key, prior, accSum;
    bool revFlag;
    Treap *leftChild, *rightChild;

    Treap() {
        accSum = 0;
        revFlag = false;
    }
    Treap(int nkey, int nprior) {
        accSum = 0;
        revFlag = false;
        key = nkey;
        prior = nprior;
    }
};
typedef Treap* ptreap;
 
void trSplit(ptreap t, int sKey, ptreap & t1, ptreap & t2) {
    if(!t) {
        t1 = t2 = NULL;
    } else if(sKey > t->key) {
        trSplit(t->rightChild, sKey, t->rightChild, t2);
        t1 = t;
    } else if(sKey <= t->key) {
        trSplit(t->leftChild, sKey, t1, t->leftChild);
        t2 = t;
    }
}

void trMerge(ptreap & t, ptreap t1 , ptreap t2) {
    // t1 keys < t2 keys
    if(!t1) {
        t = t2;
    } else if(!t2) {
        t = t1;
    } else if(t1->prior >= t2->prior) {
        trMerge(t1->rightChild, t1->rightChild, t2);
        t = t1;
    } else if(t1->prior < t2->prior) {
        trMerge(t2->leftChild, t1, t2->leftChild);
        t = t2;
    }
}

void trInsert(ptreap & t, ptreap nt) {
    if(!t) {
        t = nt;
    } else if(t->prior < nt->prior) {
        trSplit(t, nt->key, nt->leftChild, nt->rightChild);
    } else if(t->key < nt->key) {
        trInsert(t->rightChild, nt);
    } else {
        trInsert(t->leftChild, nt);
    }
}

void trErase(ptreap & t, int key) {
    if(!t) {
        return;
    }
    if(t->key == key) {
        ptreap temp = t;
        trMerge(t, t->leftChild, t->rightChild);
        delete temp;
    }
}

ptreap trUnion(ptreap l, ptreap r) {
    if(!l || !r) {
        return l ? l : r;
    }
    if(l->prior < r->prior) swap(l, r);
    
    ptreap r1, r2;
    trSplit(r, l->key, r1, r2);
    l->leftChild = trUnion(l->leftChild, r1);
    l->rightChild = trUnion(l->rightChild, r2);
    return l;
}




