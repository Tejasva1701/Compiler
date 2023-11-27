#include<iostream>
using namespace std;

#define max 10
#define MAX 15

char arr[max][MAX], temp[max][MAX];
int c, n, t;

void func(int, int[]);
int func2(int i, int j, int p[], int key) {
    int k;
    if (!key) {
        for (k = 0; k < n; k++)
            if (arr[i][j] == arr[k][0])
                break;
        p[0] = i;
        p[1] = j + 1;
        func(k, p);
        return 0;
    }
    else {
        for (k = 0; k <= c; k++) {
            if (arr[i][j] == temp[t][k])
                break;
        }
        if (k > c) return 1;
        else return 0;
    }
}

void func(int i, int p[]) {
    int j, k, key;
    for (j = 2; arr[i][j] != NULL; j++) {
        if (arr[i][j - 1] == '/') {
            if (arr[i][j] >= 'A' && arr[i][j] <= 'Z') {
                key = 0;
                func2(i, j, p, key);
            }
            else {
                key = 1; 
                if (func2(i, j, p, key))
                    temp[t][++c] = arr[i][j];
                if (arr[i][j] == 'ε' && p[0] != -1) {
                    if (arr[p[0]][p[1]] >= 'A' && arr[p[0]][p[1]] <= 'Z') {
                        key = 0;
                        func2(p[0], p[1], p, key);
                    }
                    else if (arr[p[0]][p[1]] != '/' && arr[p[0]][p[1]] != NULL) {
                        if (func2(p[0], p[1], p, key))
                            temp[t][++c] = arr[p[0]][p[1]];
                    }
                }
            }
        }
    }
}

int main() {
    int p[2], i, j;
    cout << "Enter the no. of productions :";
    cin >> n;
    cout << "Enter the productions :\n";
    for (i = 0; i < n; i++)
        cin >> arr[i];
    for (i = 0, t = 0; i < n; i++, t++) {
        c = 0, p[0] = -1, p[1] = -1;
        temp[t][0] = arr[i][0];
        func(i, p);
        temp[t][++c] = NULL;
        cout << "First(" << temp[t][0] << ") : { ";
        for (j = 1; j < c; j++)
            cout << temp[t][j] << ",";
        cout << "\b }\n";
    }

    return 0;
}


/* S/aBDh
B/cC
C/bC/ε   
D/E/F
E/gH
F/f/ε 
H/i/ε */