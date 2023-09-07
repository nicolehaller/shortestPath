//Nicole Haller 
#include<iostream>
using namespace std;
const int rows = 5;
const int cols = 6;

//create string array to store bath u came from to get to box[i][j] 
string stringRowIn[rows][cols]; 

//memo array stores the total Cost to get to that box 
int memo[rows][cols]= {0}; 

//function to find the cost to get to box [i][j]
int cost(int i, int j){ // i is the row, j is the column
    //starting weight array of each box= how much effort it takes 
    int weight[rows][cols]={
        {3,4,1,2,8,6},
        {6,1,8,2,7,4},
        {5,9,3,9,9,5},
        {8,4,1,3,2,6},
        {3,7,2,8,6,4}};

    //check to see if there is a non-zero value in my memo array
    //meaning ive already made this recursive call before so return that value
    if (memo[i][j]!=0) return memo[i][j];

    //base case- if in first column the weight is the same as the cost becuase only one box
    if(j==0){
        memo[i][0] = weight[i][0]; 
        return memo[i][0]; 
    } 

    //rowAbove can also do (i+1) %5
    int rowAbove = (i==0? 4 : (i-1)); //if i/row is 0, the row above is row 4, otherwise the row above is i-1
    int rowBelow = (i==4? 0 : (i+1)); //if i/row is 4, then row below is row 0, otherwise the row below is i+1

    //recursive call
    //if dont have memo yet, do recursive call
    int directions[3]; //creates int array to store total cost if come from left up or down
    int left=0, up=1, down=2;
    //the cost of i,j is the weight in box [i][j] plus the minimum cost it took to the col before(recursive) 
     directions[left]= weight[i][j] + cost(i, j-1);//never have to worry about going off board to left
     directions[up] = weight[i][j] + cost(rowAbove, j-1); 
     directions[down] = weight[i][j] + cost(rowBelow, j-1); 

   // find the value of the shortest path through cell (i,j)/the minimum of the directions array
    int min = directions[0];
    for (int i =1; i<=2; i++){
        if (directions[i]< min){
            min= directions[i];
        } 
     }

    //solve for what row you are currently in based on where minimum came from
    int rowIn= 0;
    if (min== directions[up])  rowIn= rowAbove; //if min was coming from up, ur in rowAbove
    else if (min== directions[left])  rowIn= i; //if min came from left, ur in the same row
    else if (min== directions[down])  rowIn= rowBelow; //if min came from down, ur in the rowBelow


    //Magoulis:
    //if (direction==left) path[i][j] = path[i][j-1] + to_string(i);
    //else if (direction ==up) path[i][j]= path[i][rowAbove] + to_string(i);
    //else if (direction ==down) path[i][j]= path[i][rowBelow] + to_string(i);


    for (int i=0; i<rows; i++){
        stringRowIn[i][0]=to_string(i); //sets first col of path taken array to be the row as a string value 
    }
    /* ex:
    "0"
    "1"
    "2"
    "3"
    "4"
    */

    // set string s equal to the path you’ve taken so far. That was if you’ve taken rows 012 so far, you append to that path the next rowIn.
    string s= stringRowIn[rowIn][j-1];   // set string s equal to the path you’ve taken so far(the value already in the box of the column one before the one ur in and in the rowIn that we stored from before)
    s= s.append(to_string(i)); //adds string value of row that you are in now to s
    stringRowIn[i][j]= s; //sets s to be the value of box[i][j] of string path taken array 
    
    //assign min to the totalCost array before returning it
    memo[i][j]=min;
    
    return min; //cheapest path to get to some location is stored in memo array
 } //end cost



int main(){

    //solve for the minimum cost by checking for the smallest value in the last col of the cost array
    int finalMin= cost(0, cols-1); //make top right box of cost array into the min
    int finalRow= 0; //finalRow is the row of the last col that has the smallest cost to get there (where we exit out of), set to 0 to start
    for (int i=1; i< rows; i++){
        if (cost(i, cols-1) < finalMin) {
            finalMin= cost(i,cols-1);
            finalRow= i;
        }
    }
    cout<<"the shortest path is of length "<<finalMin<<endl; 

    //print string path array
    cout << "string row in array: "<< endl;
    for (int r=0; r<rows; r++){
        for (int c=0; c<cols; c++){
            cout<< stringRowIn[r][c] << "\t";
        }
        cout << endl;
    }
    
    cout << endl;

    //print memo array
    cout << "memo/total cost array: "<< endl;
    for (int r=0; r<rows; r++){
        for (int c=0; c<cols; c++){
            cout << memo[r][c] << "\t";
        }
        cout << endl;
    }

    //prints the final path by finding the final string value in the finalRow of the string array and separating the numbers to print by row
    string shortestRowPath = stringRowIn[finalRow][cols-1];
    cout << "The shortest path went from row " << shortestRowPath.at(0);
    for (int i=1; i<shortestRowPath.length(); i++){
            cout << " to row " << shortestRowPath.at(i);
    }
    cout << endl;

} 