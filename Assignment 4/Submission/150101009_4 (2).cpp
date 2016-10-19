/**
*
*   Assignment 3 - Binary Tree - Q1
*   CS 210 - Data Structures
*
*   Written By:
*
*   Anup Agarwal (150101009)
*   anup.agarwal@iitg.ernet.in
*   +91 9711794321
*
*   Department of Computer Science and Engineering
*
*   A - 222 Barak Hostel,
*   Guwahati, Assam - 781039
*
*   All O (Big-Oh) signify time complexity unless mentioned otherwise
*
**/
#include <iostream>

using namespace std;

int const SIZE = 1005;
int r,c;
char a[SIZE][SIZE];

int di[] = {0,0,1,-1};
int dj[] = {1,-1,0,0};

pair<int,int> entry;
pair<int,int> exit;
bool possible = true;

#define type 4

bool isinside(int x, int y){
    return x>=0 && x<r && y>=0 && y<c;
}

//Flood fill is just a synonym for DFS in this case.
void flood_fill(int i, int j){
    //Mark that this node is visited.
    a[i][j] = 'X';
    //we find the 4 neighbours of the node in the outer loop
    for(int k= 0; k<type; k++){
        int ii = i + di[k];
        int jj = j + dj[k];
        //if the address is inside and not visited then we recurse.
        if(isinside(ii,jj) && a[ii][jj]=='L')
            flood_fill(ii,jj);
//        else if(isinside(ii,jj) && a[ii][jj]=='X'){
//            a[ii][jj]='Y';
//        }
//        else if(isinside(ii,jj) && a[ii][jj]=='Y'){
//            possible = false;
//        }
    }
    //If at the end of this procedure if the exit node becomes 'X'
    //then we have a path between entry and exit nodes.
}

int main()
{
    cout<<"Enter Rows and Columns Separated by a space:\n";
    cin>>r>>c;
    cout<<"Enter the elements of the Jungle:\n";
    for(int i= 0; i<r; i++){
        for(int j= 0; j<c; j++){
            cin>>a[i][j];
        }
    }




    int count_boundary = 0;

    //Check Boundary Elements for entry and exit nodes

    //check top and bottom rows
    for(int i= 0; i<c; i++){
        if(a[0][i]=='L'){
            count_boundary++;
            if(count_boundary==1){
                entry = make_pair(0,i);
            }
            else if(count_boundary==2){
                exit = make_pair(0,i);
            }
            else{
                possible = false;
                break;
            }
        }

        if(a[r-1][i]=='L' && r>1){ // if r == 1 then only one row so need to check only once. as r-1 = 0.
            count_boundary++;
            if(count_boundary==1){
                entry = make_pair(r-1,i);
            }
            else if(count_boundary==2){
                exit = make_pair(r-1,i);
            }
            else{
                possible = false;
                break;
            }
        }
    }

    //check the extreme cols (leftmost and rightmost)
    if(possible){
        for(int i= 1; i<r-1; i++){
            if(a[i][0]=='L'){
                count_boundary++;
                if(count_boundary==1){
                    entry = make_pair(i,0);
                }
                else if(count_boundary==2){
                    exit = make_pair(i,0);
                }
                else{
                    possible = false;
                    break;
                }
            }
            if(a[i][c-1]=='L' &&c>1){
                count_boundary++;
                if(count_boundary==1){
                    entry = make_pair(i,c-1);
                }
                else if(count_boundary==2){ // if c == 1 then only one column so need to check only once. as c-1 = 0.
                    exit = make_pair(i,c-1);
                }
                else{
                    possible = false;
                    break;
                }
            }
        }
    }
    //if Boundary Elements are not 2 then Bad Luck!
    if(count_boundary!=2)
        possible = false;
    //If boundary elements are 2 then check for path between entry and exit using dfs a.k.a flood_fill
    if(possible){
        flood_fill(entry.first, entry.second);
        if(a[exit.first][exit.second]!='X'){
            possible = false;
        }
    }

    if(possible){
        cout<<"\nSubmitted!";
    }
    else{
        cout<<"\nBad Luck!";
    }

    return 0;
}

