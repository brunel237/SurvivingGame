#include "myFunctions.c++"


int main() {

    Board board; 

   int size; 

   while (1){
        cout<<"Enter size of Table : ";
        cin>>size;
        if (size >9 &&(round(sqrt(size))==sqrt(size)) ) break;
        else cout<<"Wrong input!"<<endl;
        cout<<endl;
   };

   Tiles T[size];

    board.clearBoard(T, size);

    Start(&board, T, size);

    return 0;
}