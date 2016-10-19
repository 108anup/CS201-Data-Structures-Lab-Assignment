#include <iostream>
#include <utility>

using namespace std;

#define type 4
#define SIZE 105

struct info{

    bool has_back_edge;
    int parentx;
    int parenty;

    info(){
        parentx = -1;
        parenty = -1;
        has_back_edge = false;
    }
};

bool isinside(int x, int y, int r, int c){
    return x>=0 && x<r && y>=0 && y<c;
}

//Flood fill is just a synonym for DFS in this case.
void flood_fill(int i, int j, char a[SIZE][SIZE], info ai[SIZE][SIZE], int r, int c){
    int di[] = {0,0,1,-1};
    int dj[] = {1,-1,0,0};
    //Mark that this node is visited.
    a[i][j] = 'G'; //Gray Colour
    //we find the 4 neighbours of the node in the outer loop
    for(int k= 0; k<type; k++){
        int ii = i + di[k];
        int jj = j + dj[k];
        //if the address is inside and not visited then we recurse.

        if(isinside(ii,jj,r,c) && a[ii][jj]=='L'){
            ai[ii][jj].parentx=i;
            ai[ii][jj].parenty=j;
            flood_fill(ii,jj,a,ai,r,c);
        }
        if(isinside(ii,jj,r,c) && a[ii][jj]=='G' && !(ai[i][j].parentx==ii && ai[i][j].parenty==jj)){
            ai[ii][jj].has_back_edge = true;
            ai[i][j].has_back_edge = true;
        }

    }
    a[i][j] = 'B';
}

bool checkpath(pair<int,int> entry, pair<int,int> exit, char a[SIZE][SIZE], info ai[SIZE][SIZE]){
    int i = exit.first;
    int j = exit.second;

    int si = entry.first;
    int sj = entry.second;
    while(true){
        if(i==si && j==sj)
            break;
        if(ai[i][j].has_back_edge){
            return false;
        }
        int tempi = ai[i][j].parentx;
        j = ai[i][j].parenty;
        i = tempi;
    }
    if(ai[si][sj].has_back_edge==true)
        return false;
    return true;
}

int main()
{
    int r,c;
    char a[SIZE][SIZE];
    info ai[SIZE][SIZE];
    bool possible = true;

    cout<<"Enter Rows and Columns Separated by a space:\n";
    cin>>r>>c;
    cout<<"Enter the elements of the Jungle:\n";
    for(int i= 0; i<r; i++){
        for(int j= 0; j<c; j++){
            cin>>a[i][j];
        }
    }


    pair<int,int> entry;
    pair<int,int> exit;

    int count_boundary = 0;

    //Check Boundary Elements for entry and exit
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
        if(a[r-1][i]=='L' && r>1){
            count_boundary++;
            if(count_boundary==1){
                entry = make_pair(r-1,i);;
            }
            else if(count_boundary==2){
                exit = make_pair(r-1,i);;
            }
            else{
                possible = false;
                break;
            }
        }
    }

    //check the extreme cols
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
                else if(count_boundary==2){
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
        flood_fill(entry.first, entry.second,a,ai,r,c);
        if(a[exit.first][exit.second]!='B'){
            possible = false;
        }
        if(possible)
            if(!checkpath(entry, exit, a, ai)){
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
