#include<iostream>
using namespace std;

#define max 10
#define MAX 15

void ffunc(int, int);
void func(int, int[]);
void follow(int i);

char arr[max][MAX], temp[max][MAX];
int c, n, t;
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

char fol[max][MAX], ff[max];
int f, l, ff0;

void follow(int i) {
    int j, k;
    for (j = 0; j <= ff0; j++)
        if (arr[i][0] == ff[j])
            return;
    if (j > ff0) ff[++ff0] = arr[i][0];
    if (i == 0) fol[l][++f] = '$';
    for (j = 0; j < n; j++)
        for (k = 2; arr[j][k] != NULL; k++)
            if (arr[j][k] == arr[i][0])
                ffunc(j, k);
}

void ffunc(int j, int k) {
    int ii, null = 0, tt, cc;
    if (arr[j][k + 1] == '/' || arr[j][k + 1] == NULL)
        null = 1;
    for (ii = k + 1; arr[j][ii] != '/' && arr[j][ii] != NULL; ii++) {
        if (arr[j][ii] <= 'Z' && arr[j][ii] >= 'A') {
            for (tt = 0; tt < n; tt++)
                if (temp[tt][0] == arr[j][ii]) break;
            for (cc = 1; temp[tt][cc] != NULL; cc++) {
                if (temp[tt][cc] == 'ε') null = 1;
                else fol[l][++f] = temp[tt][cc];
            }
        }
        else fol[l][++f] = arr[j][ii];
    }
    if (null) follow(j);
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
        for (j = 1; j < c; j++)
            temp[t][j];
    }
    
    /* Follow Finding */
    for (i = 0, l = 0; i < n; i++, l++) {
        f = -1; ff0 = -1;
        fol[l][++f] = arr[i][0];
        follow(i);
        fol[l][++f] = NULL;
    }
    for (i = 0; i < n; i++) {
        cout << "\nFollow(" << fol[i][0] << ") : { ";
        for (j = 1; fol[i][j] != NULL; j++)
            cout << fol[i][j] << ",";
        cout << "\b }";
    }
    return 0;
}