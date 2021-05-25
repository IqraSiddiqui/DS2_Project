#include <bits/stdc++.h>
#include <fstream>
#include<string>

using namespace std;

int roundUp(int x) {
	if ( x < 0 ) return 0;
	--x;
	x |= x >> 1;
	x |= x >> 2;
	x |= x >> 4;
	x |= x >> 8;
	x |= x >> 16;
	return x + 1;
}

float lowerSqrt(int val) {
	return pow ( 2, floor ( log2 ( val )  / 2 ) );
}

float higherSqrt(int val) {
	return pow ( 2, ceil ( log2 ( val )  / 2 ) );
}

struct veb {
	int u, min, max, sqrt_u, sqrt_high, sqrt_low;
	veb *summary, **cluster;
};

int low(veb *root, int key) {
	return key % root->sqrt_low;
}

int high(veb *root, int key) {
	return key / root->sqrt_low;
}

int index(veb *root, int i, int j) {
	return (i*root->sqrt_low)+j;
}

int veb_max(veb *root) {
	if(root == NULL) {
		return -1;
	}
	return root->max;
}

int veb_min(veb *root) {
	if(root == NULL) {
		return -1;
	}
	return root->min;
}

veb* create(veb *root, int size) {
	int temp = roundUp(size);
	root->u = temp;
	root->sqrt_u = sqrt(temp);
	root->sqrt_low = lowerSqrt(temp);
	root->sqrt_high = higherSqrt(temp);
	root->min = INT_MIN;
	root->max = INT_MIN;
	root->summary = NULL;
	if(root->u <= 2) {
		root->cluster = NULL;
	} else {
		root->cluster = new veb * [root->sqrt_high];
		for(int i = 0; i < root->sqrt_high; i++) {
			root->cluster[i] = NULL;
		}
	}
	return root;
}

void insert(veb *& root, int key, int u) {
	if(root == NULL) {
		root = new veb;
		root = create(root, u);
	}

	if(key < 0 || key >= root->u) {
		cout << "\nKey out of range";
		return;
	}

	if(key == root->min || key == root->max) {
		return;
	}

	if(root->min == INT_MIN) {
		root->min = root->max = key;
		return;
	}

	if(root->min > key) {
		int temp = key;
		key = root->min;
		root->min = temp;
	}

	if(root->max < key) {
		root->max = key;
	}

	if(root->u <= 2) {
		return;
	}

	int i = high(root, key);
	int j = low(root, key);

	if(root->cluster[i] == NULL) {
		insert(root->summary, i, root->sqrt_high);
	}

	insert(root->cluster[i], j, root->sqrt_low);
}

int successor(veb *root, int key) {
	if(root == NULL) {
		return -1;
	}

	if(root->u == 2) {
		if(key == 0 && root->max == 1) {
			return 1;
		}
		return -1;
	}

	if(key < -1 || key >= root->u) {
		return -1;
	}

	if(key < root->min) {
		return root->min;
	}

	if(root->summary == NULL) {
		if(key < root->max) {
			return root->max;
		}
		return -1;
	}

	int i = high(root, key);
	int j = INT_MIN;
	int h = high(root, key);
	int l = low(root, key);

	if(l < veb_max(root->cluster[i])) {
		j = successor(root->cluster[i], l);
		if(j == -1)
			return -1;
	} else {
		i = successor(root->summary, h);

		if(i == -1) {
			if(key < root->max) {
				return root->max;
			}
			return -1;
		}
		j = veb_min(root->cluster[i]);
		if(j == -1)
			return -1;
	}

	return index(root, i, j);
}
