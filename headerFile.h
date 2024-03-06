#ifndef HEADERFILE_H
#define HEADERFILE_H
    #include<iostream>
    #include<cstdlib>
    // #include <crtdbg.h>
    #include<cmath>
    #include<time.h>
    #include <vector>

    #ifdef _WIN32
    #include<Windows.h>
    #else
    #include<unistd.h>
    #endif

    using namespace std;
    using std::string;

    int id_counter = 0;
    int newCat_counter = 0;
    int newCat_position = 0;
    int newMouse_counter = 0;
    int newMouse_position = 0;
    bool game_over = false;
    
#endif 