
#include <stdio.h>
#include <stdbool.h>

#define N 40

bool Solve(int board[N][N], int col);
bool IsSafe(int board[N][N], int row, int col);
void printSolution(int board[N][N]);


void clearBoard(int board[N][N])
{
    int i, j;
    
    for (i = 0; i < N; i++)
    {    
        for (j = 0; j < N; j++)
             board[i][j] = 0;
     }
} 

int main()
{
     int board[N][N];
     
     clearBoard(board);
     
     if (Solve(board, 0) == true)
        printSolution(board);
     else
        printf("Solution does not exist\n");
        
     return 0;
}

void printSolution(int board[N][N])
{
    int i, j;
    
    for (i = 0; i < N; i++)
    {    
        for (j = 0; j < N; j++)
             printf(" %d ", board[i][j]);
        printf("\n");
     }
} 

bool IsSafe(int board[N][N], int row, int col)
{
   int i, j;

   /* row */
   for (i = 0; i < col; i++)
       if (board[row][i]) return false;

   /* upper diag */
   for (i = row, j = col; i>=0 && j>=0; i--, j--)
       if (board[i][j]) return false;

   /* low diag */
   for (i = row, j = col; i<N && j>=0; i++, j--)
       if (board[i][j]) return false;

   return true;
}

bool Solve(int board[N][N], int col)
{
      int row;
       
      /* base case */
      if (col >= N)
         return true;
         
      /* try to place q in the next col */
      for (row = 0; row < N; row++)
      {
          if (IsSafe(board, row, col) == true)
          {
               board[row][col] = 1;
               
               if (Solve(board, col+1) == true)
                     return true;
               
               /* otherwise, backtrack */
               board[row][col] = 0;
           }
      }
      
      return false;
}  
