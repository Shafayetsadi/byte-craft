#include <bits/stdc++.h>
using namespace std;

const int N = 3e5 + 10;
int arr[N];

struct SegmentTree {
  int tree[4 * N];
  SegmentTree() { memset(tree, 0, sizeof(tree)); }

  void build(int lo, int hi, int pos) {
    if (lo == hi) {
      tree[pos] = arr[lo];
    } else {
      int mid = (lo + hi) / 2;
      build(lo, mid, 2 * pos + 1);
      build(mid + 1, hi, 2 * pos + 2);
      tree[pos] = tree[2 * pos + 1] + tree[2 * pos + 2]; // range sum
      // tree[pos] = max(tree[2 * pos + 1], tree[2 * pos + 2]); // range max
    }
  }

  void update(int lo, int hi, int pos, int index, int val) {
    if (index < lo or index > hi) {
      return; // Out of bounds
    }

    if (lo == hi) {
      tree[pos] = val;
    } else {
      int mid = (lo + hi) / 2;
      update(lo, mid, 2 * pos + 1, index, val);
      update(mid + 1, hi, 2 * pos + 2, index, val);
      tree[pos] = tree[2 * pos + 1] + tree[2 * pos + 2];
      // tree[pos] = max(tree[2 * pos + 1], tree[2 * pos + 2]);
    }
  }

  int query(int lo, int hi, int l, int r, int pos) {
    // l (left), r (right) is given by the user
    if (l > hi or r < lo) {
      return 0; // Out of bounds
    }
    if (l <= lo and r >= hi) {
      return tree[pos]; // completely within range
    }
    int mid = (lo + hi) / 2;
    return query(lo, mid, l, r, 2 * pos + 1) +
           query(mid + 1, hi, l, r, 2 * pos + 2);
    // return max(query(lo, mid, l, r, 2 * pos + 1),
    //            query(mid + 1, hi, l, r, 2 * pos + 2));
  }
} segTree;

int32_t main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int a[5] = {10, 20, 30, 40, 50};
  int n = 5;
  for (int i = 0; i < n; i++) {
    arr[i] = a[i];
  }
  segTree.build(0, n - 1, 0);
  cout << segTree.query(0, n - 1, 1, 2, 0) << endl;
  cout << segTree.query(0, n - 1, 2, 3, 0) << endl;
  cout << segTree.query(0, n - 1, 0, n - 1, 0) << endl;
  segTree.update(0, n - 1, 0, 2, 50);
  cout << segTree.query(0, n - 1, 1, 2, 0) << endl;
  cout << "Hello World!" << endl;
  return 0;
}
