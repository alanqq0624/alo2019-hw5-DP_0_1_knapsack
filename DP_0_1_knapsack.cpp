#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>

using namespace std;

int itemNum, aimWeiget;
vector<int> itemValue, itemWeight;

void DP_0_1_knapsack(vector<int> &v, vector<int> &w, int n, int W);

int main(int argc, char const *argv[])
{
    cout << "Dynamic Programming 0-1 Knapsack Problem\n\n" ;

    // init variable------------------------------------------------------------------------------
    ifstream fin;
    int size, buffer;

    // open files ---------------------------------------------------------------------------------
    fin.open("input");
    if (!fin) {
        cout << "file in failed\n" << endl;
        return 0;
    }

    // get W or aimWeight---------------------------------------------------------
    if(argc != 2) {
        cout << "Usage: ./DP_0_1_knapsack W\n";
        return 1;
    }
    int k_in = atoi(argv[1]);
    aimWeiget = k_in;
    cout << "aimWeight: " << aimWeiget << "\n";

    // set item 0 to zero
    itemValue.push_back(0);
    itemWeight.push_back(0);

    // get data from input file --------------------------------------------------------------------
    fin >> size;
    itemNum = size;
    cout << "itemNum: " << itemNum << "\n\n";
    for(int i = 0; i < size; i++) {
        fin >> buffer;
        if (buffer == EOF) {
            cout << "file size error: " << buffer ;
            return 1;
        }
        itemValue.push_back(buffer);

        fin >> buffer;
        if (buffer == EOF) {
            cout << "file size error: " << buffer ;
            return 1;
        }
        itemWeight.push_back(buffer);
    }

    // print input data ---------------------------------------------------------------------------
    cout << "Print input item data:\n";
    cout << "size\tvalue\tweight\n";
    for(int i = 1; i <= size; i++) {
        cout << i << "\t" << itemValue[i] << "\t" << itemWeight[i] << endl;
    }
    cout << endl;

    // deal with 0-1 knapsack problem

    DP_0_1_knapsack(itemValue, itemWeight, itemNum, aimWeiget);

    // print answer ------------------------------------------------------------------------------------

    cout << "END\n\n";
    return 0;
}

/*
    input parameter":
        v: input item value list
        w: input item weight list
        n: input item's number
        W: weight restriction
*/
void DP_0_1_knapsack(vector<int> &v, vector<int> &w, int n, int W)
{

    // assign 2D array to save DP optimal value and init all c to 0------------------------------------------------------
    // c[item that current checking][ristric weight]

    // way 1 : use new, failed
    // cross using "new" and vector may cause some error
    // int **c = new int*[n];
    // for(int i = 0; i < W; i++){
    //     c[i] = new int[W];
    // }

    // way 2: use vector
    vector<vector<int>> c(n+1);
    for (int i = 0; i < n+1; i++) {
        c[i] = vector<int>(W+1);
        for (int j = 0; j < W+1; j++) {
            c[i][j] = 0;
            // cout << "c[" << i << "][" << j << "]: " << c[i][j] << "\n";
        }
    }

    // assign 2D array to save the pattern when DP optimal value appear ------------------------------------------------------
    // p[item that current checking][ristric weight][item pattern]
    vector<vector<vector<int>>> p(n+1);
    for (int i = 0; i < n+1; i++) {
        p[i] = vector<vector<int>>(W+1);
    }

    // compute ooptimal value ---------------------------------------------------------------------------------------------------
    // cout << "i'th\tw ris\ti'w\tway\tpattern\tfin val\n";
    for (int i = 1 ; i <= n; i++) {
        for (int j = 1; j <= W; j++) {
            // cout << i << "\t" << j << "\t" << w[i] << "\t";
            if (w[i] <= j) {
                if (v[i] + c[i-1][j-w[i]] > c[i-1][j]) {
                    // cout << "a\t";
                    c[i][j] = v[i] + c[i-1][j-w[i]];
                    p[i][j].assign( p[i-1][j-w[i]].begin(), p[i-1][j-w[i]].end());
                    p[i][j].push_back(i);
                    // for (int k = 0; k < p[i][j].size(); k++) {
                    //     cout << p[i][j][k];
                    // }
                } else {
                    // cout << "b\t";
                    c[i][j] = c[i-1][j];
                    p[i][j].assign( p[i-1][j].begin(), p[i-1][j].end());
                    // for (int k = 0; k < p[i][j].size(); k++) {
                    //     cout << p[i][j][k];
                    // }
                }
            } else {
                // cout << "c\t";
                c[i][j] = c[i-1][j];
                p[i][j].assign( p[i-1][j].begin(), p[i-1][j].end());
                // for (int k = 0; k < p[i][j].size(); k++) {
                //     cout << p[i][j][k];
                // }
            }
            // cout << "\t";
            // cout << c[i][j] << "\n";
        }
        // cout << "\n";
    }

    // Print answer
    cout << "Best value: " << c[n][W] <<  "\n";
    cout << "Best pattern:";
    for (int i = 0; i < p[n][W].size(); i++) {
        cout << " " << p[n][W][i];
    }
    cout << "\n";


}