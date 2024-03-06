#include "myClass.c++"

typedef struct element{
    Cat* cat;
    Mouse* mouse;
    Maize* maize;
    bool is_cat = false;
    bool is_mouse = false;
    bool is_maize = false;
    int* pos;
}element;

vector<element> mainList; //list of entities present on the board

string sexDecision(int num){ // explicitly for reproducition. an entity gives birth to another entity of random sex
    if (num == 1) return "male";
    else return "female";
}

void check_list(){ //check status of all elements to see which ones can get out
    if (mainList.size() <=1 || game_over) game_over = true; 
    vector<element>::iterator temp = mainList.begin();
    
    int i= 0; 

    while (i < mainList.size()){
        if ( (mainList.at(i).is_cat && mainList.at(i).cat->Character == ' ')||(mainList.at(i).is_mouse && mainList.at(i).mouse->Character == ' ')||(mainList.at(i).is_maize && mainList.at(i).maize->Character == ' ') )
            mainList.erase(temp+i);
        else i++;

        
    }

    if (mainList.size() <=1) game_over = true;

}


void check_elements(){
    /*A function that at checks the position of all elements on the board and see whether any action can be perform like: eating or reproducing*/

    if (mainList.size() <2 || game_over) { game_over = true; return; }

    int cnt1=0, cnt2 = 0;
    
    vector<element>:: iterator pointer, ptr, temp;

    temp = mainList.begin();

    vector<element> new_list;

    pointer = mainList.begin() ;
    
    do {
        ptr = mainList.begin()+ cnt1+1;
        cnt2 = 0;
        do{
            cnt2 +=1;
            if (*pointer->pos == *ptr->pos){
                if (pointer->is_cat){
                    if (ptr->is_cat){
                        if ( pointer->cat->getSex() != ptr->cat->getSex() ){
                            newCat_position = *pointer->pos;
                            pointer->cat->Position--;
                            ptr->cat->Position++;

                            ++newCat_counter;
                        }
                    }
                    else if (ptr->is_mouse)
                        pointer->cat->eat(ptr->mouse);
                }
                else if (pointer->is_mouse){
                    if (ptr->is_cat)
                        ptr->cat->eat(pointer->mouse);                   
                    else if (ptr->is_mouse){
                        if ( pointer->mouse->getSex() != ptr->mouse->getSex() ){
                            newMouse_position = *pointer->pos;
                            pointer->mouse->Position--;
                            ptr->mouse->Position++;
        
                            ++newMouse_counter;
                        }
                    }
                    else if (ptr->is_maize)                     
                        pointer->mouse->eat(ptr->maize);
                    
                }
                else if (pointer->is_maize){
                    if (ptr->is_mouse)
                        ptr->mouse->eat(pointer->maize);
                }
            
            }

            ptr +=1;
        } while (ptr != mainList.end());

        cnt1 ++; pointer++;
    } while (pointer != mainList.end()-1 );
    

}

void place_elements(Board* B, Tiles* T, int size){ // place all entities on board of given size
    B->clearBoard(T, size);
    int i=0;
    while (i < mainList.size()){
        element e = mainList.at(i); 
        if (e.is_cat) e.cat->setOnTile(T, size);
        else if (e.is_mouse) e.mouse->setOnTile(T, size); 
        if (e.is_maize) e.maize->setOnTile(T);
        //getchar();
        i++;
    }
}

void move_elements(int size){ // move entities on board relative to to the board's size 
    for (const element& e: mainList){
        if (e.is_cat){ 
            e.cat->move(size);
            
            if (e.cat->getEnergy() == 0){cout<<"\nCat ( Entity number "<<e.cat
            ->ID<<") exhausted !!\n";
            getchar();}
            else if (e.cat->Character == ' '){cout<<"\nCat ( Entity number "<<e.cat
            ->ID<<") moves out !!\n";
            getchar();}
        }
        else if (e.is_mouse){ 
            e.mouse->move(size);

            if (e.mouse->getEnergy() == 0) {cout<<"\nMouse (Entity number "<<e.mouse->ID
            <<") exhausted !!\n";
            getchar();}
            else if (e.mouse->Character == ' ') {cout<<"\nMouse (Entity number "<<e.mouse->ID<<") moves out !!\n";
            getchar();}
        }
    }
}

void Start(Board* B, Tiles* T, int size=25){
    time_t t;
    srand((unsigned) time(&t));

    /*  we create cats, mice and maize and place them on the board using previous functions*/

    element c1;
    Cat cat1 = Cat(size/2 -sqrt(size), "male"); //placed relatively to the size of board
    c1.cat = &cat1;
    c1.is_cat = true;
    c1.pos = &cat1.Position;
    mainList.push_back(c1);

    element c2;
    Cat cat2 = Cat(size/2 +sqrt(size), "female");
    c2.cat = &cat2;
    c2.is_cat = true;
    c2.pos = &cat2.Position;
    mainList.push_back(c2);

    element c3;
    Cat cat3 = Cat(size/2, "female");
    c3.cat = &cat3;
    c3.is_cat = true;
    c3.pos = &cat3.Position;
    mainList.push_back(c3);

    
    element m1;
    Mouse mouse1 = Mouse(size/2 -sqrt(size)/2, "female");
    m1.mouse = &mouse1;
    m1.is_mouse = true;
    m1.pos = &mouse1.Position;
    mainList.push_back(m1);

    element m2;
    Mouse mouse2 = Mouse(size/2 +sqrt(size)/2, "male");
    m2.mouse = &mouse2;
    m2.is_mouse = true;
    m2.pos = &mouse2.Position;
    mainList.push_back(m2);

    element mz;
    Maize maize = Maize(size/2 +2);
    mz.maize = &maize;
    mz.is_maize = true;
    mz.pos = &maize.Position;
    mainList.push_back(mz);

    place_elements(B, T, size);
    B->display(T, size); //Sleep(2000);


    /*A continuous loop that will stop only when condition(s) of gameover is/are fulfilled*/

    do{ 
        check_list();
        check_elements();  
        //cout<<"\n";
        if (newCat_counter){
            for (int i=0; i< newCat_counter; i++){
                element new_elt;
                Cat child = Cat(newCat_position, sexDecision(rand()%2+1));
                new_elt.cat = &child;
                new_elt.is_cat = true;
                new_elt.pos = &child.Position;

                mainList.push_back(new_elt);

                cout<<"\nnew Entity (cat) number "<<new_elt.cat->ID<<" in\n"; 
                getchar();
            }
            newCat_counter =0;
        }
        if (newMouse_counter){
            for (int i=0; i< newMouse_counter; i++){
                element new_elt2;
                Mouse child2 = Mouse(newMouse_position, sexDecision(rand()%2+1));
                new_elt2.mouse = &child2;
                new_elt2.is_mouse = true;
                new_elt2.pos = &child2.Position;

                mainList.push_back(new_elt2);

                cout<<"\nnew Entity (Mouse) number "<<new_elt2.mouse->ID<<" in\n"; 
                getchar();
            }
            newMouse_counter =0;
        }

        place_elements(B, T, size);

        B->display(T, size);
        
        // Sleep(1500);
        
        if (game_over) break;

        move_elements(size);

        place_elements(B, T, size);

        B->display(T, size);

        // Sleep(1500);
      
    } while (not game_over);

    //system("clear");
    cout<<"\n--------------GAME OVER !!!-------------\n\n";

}