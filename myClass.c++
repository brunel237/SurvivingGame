#include "headerFile.h"

class Tiles{ // a tile able to contain 2 characters ( representing entities )
    public:
    char Space1, Space2;

};

class Entity{
    public:

    int ID=0;
    int Reference;
    int Position;
    char Character;
    

    void Delete(){
        Character = ' ';
    }  

    virtual void setOnTile(Tiles* T){  // polymorphic function for placing an entity on a tile T
        if (Character != ' '); {
            if (T[Position-1].Space1==' ')
                T[Position-1].Space1 = Character;
    
            else if (T[Position-1].Space2==' ')
                T[Position-1].Space2 = Character;
        }
    }
   
    Entity(int pos){
        Position = pos;
        ID = ++id_counter;
    }

};


class Maize: public Entity{

    public:
    Maize(int pos):Entity(pos){
        Character = '.';
        Reference = 3;
    }

};

class Mouse: public Entity{
    string Sex;
    int Energy;
    int PrevPosition;

    public:
    int getEnergy(){
        return Energy;
    }

    void setSex(string sex){
        Sex = sex;
        if (sex == "male"){ 
            Reference = 10;
            Character = 'M';
        }
        else{ 
            Reference = 11;
            Character = 'm';
        }
    }
    string getSex(){
        return Sex;
    }

    void eat(Maize* m){
        //if (Energy < 10){
            m->Delete();
            Energy++;
        //}
        cout<<"\nMaize eaten !!\n";
        getchar();
    }

    void move(int size){
        int i = rand()%5+1; 
        int sq = sqrt(size);

        PrevPosition = Position;

        if (i==1)  Position += sq;
        else if (i==2) Position -= sq;
        else if (i==3) Position += 1;
        else Position -= 1;

        if (((Position>size)||(Position<1))||(((PrevPosition%sq == 0)&&(Position%sq == 1))||((PrevPosition%sq == 1)&&(Position%sq == 0)))) 
            Delete(); 

        Energy -=1;
        
        if (Energy <1)
            Delete();
    }

    void setOnTile(Tiles* T,int size){
        if (Character != ' '); {
            if (T[Position-1].Space1==' ')
                T[Position-1].Space1 = Character;

            else if (T[Position-1].Space2==' ')
                T[Position-1].Space2 = Character;
            else { 
                move(size);
                setOnTile(T, size);
            }
        }
    }

    Mouse(int pos, string sex) : Entity(pos){
        setSex(sex);
        Energy = 10;
    }

};


class Cat: public Entity{
    string Sex;
    int Energy;
    int PrevPosition;

    public:

    int getEnergy(){
        return Energy;
    }

    void setSex(string sex){
        Sex = sex;
        if (sex == "male"){
            Reference = 10;
            Character = 'C';
        }
        else{
            Reference = 11;
            Character = 'c';
        }
    }
    string getSex(){
        return Sex;
    }

    void move(int size){
        int i = rand()%5+1;
        int sq = sqrt(size);

        PrevPosition = Position;

        if (i==1)  Position += sq;
        else if (i==2) Position -= sq;
        else if (i==3) Position += 1;
        else Position -= 1;

        if (((Position>size)||(Position<1))||(((PrevPosition%sq == 0)&&(Position%sq == 1))||((PrevPosition%sq == 1)&&(Position%sq == 0)))) {
            Delete();
        }

        Energy -=1;

        if (Energy <1)
            Delete();
    }

    void setOnTile(Tiles* T,int size){
        if (Character != ' '); {
            if (T[Position-1].Space1==' ')
                T[Position-1].Space1 = Character;

            else if (T[Position-1].Space2==' ')
                T[Position-1].Space2 = Character;
            else { 
                move(size);
                setOnTile(T, size);
            }
        }
    }

    void eat(Mouse* m){
        m->Delete();
        if (Energy < 10)
            Energy++;
        cout<<"\nMouse eaten !!\n";
        getchar();
    }

    Cat(int pos, string sex) : Entity(pos){
            setSex(sex);
            Energy = 10;
    }
};



class Board{
    // pivate functions for drawing the board
    void alterMinusPlus(){
    cout<<"- - + ";
    }
    void horizontalRule(int size){
    cout<<"+ ";
    for (int i=0; i<size; i++)
        alterMinusPlus();
    cout<<endl;
    }
    void ValSlash(char ch1, char ch2){
    cout<<ch1<<" "<<ch2<<" | ";
    }
    void horizontalPos(Tiles* T, int size, int index){
    cout<<"| ";
    for (int i=0; i<size; i++){
        ValSlash(T[index].Space1,T[index].Space2);
        index++;
        }
    cout<<endl;
    }

    public:
    void clearBoard(Tiles* T, int size=25){
        for(int i=0; i<size; i++){
            T[i].Space1 = ' ';
            T[i].Space2 = ' ';
        }
    }

    void display(Tiles* T, int size=25){
        //clearBoard(T, size);
        system("clear");
        for (int j=0; j<sqrt(size); j++ ){
            horizontalRule(sqrt(size));
            horizontalPos(T,sqrt(size),j*sqrt(size));
        }
        horizontalRule(sqrt(size));
    }
};

