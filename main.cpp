#include <bits/stdc++.h>

using namespace std;

int n;

vector< vector<int> > rows(1000);
vector< vector<int> > cols(1000);

int sol[1000][1000];

bool checkRow(int i);
void solve(int i, int j, int br);
bool verify();

bool solved = false;

void fillRow (int row, int l, int k) { 
    if(k==rows[row].size()) {
        solve(row+1,0,0);
        return;
    }

    if(l >= n) 
        return;

    fillRow(row, l+1, k);
    if(l+rows[row][k] > n) return;
    for(int i=l;i<l+rows[row][k];i++) {
        sol[row][i]=1;
    }
    fillRow(row,l+rows[row][k]+1, k+1);
    for(int i=l;i<l+rows[row][k];i++) {
        sol[row][i]=0;
    }
}

bool checkColumn(int i) {
    int br=0;
    int curTarget = 0;
    bool in = false;
    for(int j=0;j<n;j++) {
        if(!in && sol[j][i] != 1) continue;
        else {
            if(!in) {
                curTarget = cols[i][br]-1;
                br++;
                in = true;
            }
            else {
                if(sol[j][i] == 1) curTarget--;
                else {
                    if(curTarget != 0) return false;
                    in = false;
                }
            }
        }
    }
    if(curTarget != 0) return false;
    if(br!=cols[i].size()) return false;
    return true;
}

bool verify() {
    for(int i=0;i<n;i++) {
        if(!checkColumn(i)) return false;
    }
    return true;
}

void solve(int i, int j, int br) {

    if(solved) return;

    if(i == n) {
        if(verify())
            for(int i=0;i<n;i++) {
                for(int j=0;j<n;j++) {
                    cout << sol[i][j] << " ";
                }
                cout << endl;
                solved = true;
            }
        return;        
    }

    
    fillRow(i, 0, 0);
}


int main () {

    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> n;

    for(int i=0;i<n;i++) {
        string input;
        cin >> input;

        stringstream ss(input);

        ss.ignore();

        for (int j; ss >> j;) {
            if (ss.peek() == ',' || ss.peek() == '[' || ss.peek() == ']')
                ss.ignore();
            rows[i].push_back(j);
            
        }
    }

    for(int i=0;i<n;i++) {
        string input;
        cin >> input;
        
        stringstream ss(input);

        ss.ignore();

        for (int j; ss >> j;) {
            if (ss.peek() == ',' || ss.peek() == '[' || ss.peek() == ']')
                ss.ignore();
            cols[i].push_back(j);
            
        }
    }

    solve(0,0,0);


    


}