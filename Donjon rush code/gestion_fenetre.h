#ifndef gest_fen_h
#define gest_fen_h

#include <iostream>
#define _WIN32_WINNT 0x0500
#include "windows.h"
#include <stdio.h>

using namespace std ;

int setConsoleScreenBufferInfo(COORD);

int modif_fenetre()  // int argc, char *argv[]
{
    HWND consoleWindow = GetConsoleWindow();

	SetWindowPos( consoleWindow, 0, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOZORDER );

    COORD dwSize = {168 , 57} ;  //178 , 68

    SetConsoleTitle("Donjon Rush") ;	// Réglage du titre
    if(setConsoleScreenBufferInfo(dwSize)) {	// Réglage des coordonnées
        printf("setConsoleScreenBufferInfo %ld\n", GetLastError());
        return EXIT_FAILURE ;
    }

    return EXIT_SUCCESS ;
}

int setConsoleScreenBufferInfo(COORD dwSize)
{   HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE) ;
    COORD bakDwSize = dwSize ;
    SMALL_RECT srctWindow ;
    CONSOLE_SCREEN_BUFFER_INFO csbiInfo ;

    // Obtenir les informations de la console
    if(!GetConsoleScreenBufferInfo(hConsoleOutput, &csbiInfo)) return EXIT_FAILURE ;

    // Adapter le buffer de la console en fonction des tailles maximales
    dwSize.X = (dwSize.X>csbiInfo.srWindow.Right)?dwSize.X:csbiInfo.dwSize.X ;
    dwSize.Y = (dwSize.Y>csbiInfo.srWindow.Bottom)?dwSize.Y:csbiInfo.dwSize.Y ;
    if(!SetConsoleScreenBufferSize(hConsoleOutput, dwSize)) return EXIT_FAILURE ;

    // Modifier la taille de la console
    dwSize = bakDwSize ;
    srctWindow = csbiInfo.srWindow ;
    srctWindow.Right = dwSize.X - 1 ;
    srctWindow.Bottom = dwSize.Y - 1 ;
    if(!SetConsoleWindowInfo(hConsoleOutput, TRUE, &srctWindow)) return EXIT_FAILURE ;

    // Adapter la taille du buffer de la console à sa taille (pas d'ascenseurs)
    dwSize = bakDwSize ;
    if(!SetConsoleScreenBufferSize(hConsoleOutput, dwSize)) return EXIT_FAILURE ;

    return EXIT_SUCCESS ;
}


#endif // gest_fen_h
