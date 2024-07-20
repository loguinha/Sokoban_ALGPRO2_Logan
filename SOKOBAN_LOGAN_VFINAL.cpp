#include <iostream>
#include <windows.h>
#include <conio.h>

// English commentary by: Logan Santana Fernandes.

using namespace std;

#define BLACK        0
#define RED          4
#define WHITE        7
#define GRAY         8
#define BRIGHTWHITE  15
#define LIGHTRED     12

void cor_texto (int fonte, int fundo=0) {
    SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), (WORD) (fonte | fundo<<4));
}

void Adress_Characters (int Map[17][19], int L, int C) {
    switch (Map[L][C]) {
        // SPACE TO WALK
        case 0:
            cout << " ";
        break;
        // SPOT
        case -3:
            cor_texto(8,0);
            cout << char(158);
        break;
        // HIGHER THAN THIS IS ONLY WALLS, JUST DIFFERENT PATTERNS!
        case 6: cout << char(205); break;
        case 7: cout << char(186); break;
        case 8: cout << char(201); break;
        case 9: cout << char(187); break;
        case 10: cout << char(200); break;
        case 11: cout << char(188); break;
        case 13: cout << char(185); break;
        case 14: cout << char(203); break;
        case 15: cout << char(202); break;
        case 16: cout << char(204); break;
    }
    cor_texto(7,0);
}
void Win_Verify (int Map[17][19], int ML[], bool &Continuer) {
    // WINNING PARAMETERS FOR MAP 1
    cor_texto(4,15);
    if (ML[0] == 7 && ML[1] == 7) {
        // VERIFY IF THERE'S A BOX IN EACH SPOT
        if (Map[1][4] <= -7 && Map[4][5] <= -7 && Map[5][3] <= -7) {
            system("CLS");
            // WINNING SCREEN
            cout << "\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t       YOU WON!\n\n\n\n\n\n\n\n\t\t\t\t\t";
            system("pause");
            // VARIABLE TO GET OUT OF THE MAP FUNCTION AND GO BACK TO THE MENU
            Continuer = false;
        }
    // WINNING PARAMETERS FOR MAP 2
    } else if (ML[0] == 17 && ML[1] == 19) {
        if (Map[2][3] <= -7) {
            system("CLS");
            cout << "\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t       YOU WON!\n\n\n\n\n\n\n\n\t\t\t\t\t";
            system("pause");
            Continuer = false;
        }
    // WINNING PARAMETERS FOR MAP 3
    } else {
        if (Map[6][7] <= -7 && Map[7][7] <= -7 && Map[8][7] <= -7) {
            system("CLS");
            cout << "\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t       YOU WON!\n\n\n\n\n\n\n\n\t\t\t\t\t";
            system("pause");
            Continuer = false;
        }
    }
    cor_texto(7,0);
}
void Win_restart (int ML[], int HS[], int BS[3][2]) {
    // EVERYTHING JUST GOES BACK TO ZERO
    ML[0] = 0;
    ML[1] = 0;
    HS[0] = 0; HS[1] = 0;
    BS[0][0] = 0; BS[0][1] = 0;
    BS[1][0] = 0; BS[1][1] = 0;
    BS[2][0] = 0; BS[2][1] = 0;
}
void Movement_Interpreter (int M[17][19], int HS[], int BS[3][2], int A[]) {
    // VERIFY IF THERE'S A WALL BLOCKING THE WAY
    if (M[HS[0]+A[0]][HS[1]+A[1]] > 5) {
        // NOTHING HAPPENS IF SO
    // VERIFY IF THERE'S A BOX IN THE FRONT
    } else if (M[HS[0]+A[0]][HS[1]+A[1]] < -3) {
        // VERIFY IF IN FRONT OF THIS BOX THERE'S A WALL OR ANOTHER BOX
        if (M[HS[0]+2*A[0]][HS[1]+2*A[1]] > 5 || M[HS[0]+2*A[0]][HS[1]+2*A[1]] < -3) {
            // NOTHING HAPPENS IF SO
        } else {
            //VERIFY IF IT'S BOX 1
            if (M[HS[0]+A[0]][HS[1]+A[1]] == -4 || M[HS[0]+A[0]][HS[1]+A[1]] == -7) {
                // WHAT HAPPENS IS THE SPACE/SPOT IS NOW A BOX/FILLED SPOT, AND THE PLACE WHERE THE BOX WAS BECOMES A SPACE/SPOT, SO THE HERO CAN WALK THROUGH IT NOW
                M[HS[0]+2*A[0]][HS[1]+2*A[1]] = M[HS[0]+2*A[0]][HS[1]+2*A[1]] - 4;
                BS[0][0] = HS[0]+2*A[0]; BS[0][1] = HS[1]+2*A[1];
                M[HS[0]+A[0]][HS[1]+A[1]] = M[HS[0]+A[0]][HS[1]+A[1]]+4;
            // IF NOT, VERIFY IF IT'S BOX 2
            } else if (M[HS[0]+A[0]][HS[1]+A[1]] == -5 || M[HS[0]+A[0]][HS[1]+A[1]] == -8) {
                M[HS[0]+2*A[0]][HS[1]+2*A[1]] = M[HS[0]+2*A[0]][HS[1]+2*A[1]] - 5;
                BS[1][0] = HS[0]+2*A[0]; BS[1][1] = HS[1]+2*A[1];
                M[HS[0]+A[0]][HS[1]+A[1]] = M[HS[0]+A[0]][HS[1]+A[1]]+5;
            // THEN IT GOTTA BE BOX 3
            } else {
                M[HS[0]+2*A[0]][HS[1]+2*A[1]] = M[HS[0]+2*A[0]][HS[1]+2*A[1]] - 6;
                BS[2][0] = HS[0]+2*A[0]; BS[2][1] = HS[1]+2*A[1];
                M[HS[0]+A[0]][HS[1]+A[1]] = M[HS[0]+A[0]][HS[1]+A[1]]+6;
            }
            // HERO CAN FINALLY MOVE
            HS[A[2]] = HS[A[2]]+A[1]+A[0];
        }
    // IF THERE'S NOT A BOX IN THE FRONT, IT CAN MOVE!
    } else {
        HS[A[2]] = HS[A[2]]+A[1]+A[0];
    }
}
bool Capt_Movement (int K, int M[17][19], int HS[2], int BS[3][2]) {
    // VARIABLE TO HELP THE INTERPRETER MANAGE THE PARAMETER VALUES TO THE RESPECTIVE MOVE DIRECTION
    int Add[3] = {0,0,0};
    switch(K) {
        case 72: case 'w': // UP
            Add[0] = -1; Add[1] = 0; Add[2] = 0;
            Movement_Interpreter(M, HS, BS, Add);
        break;
        case 80: case 's': // DOWN
            Add[0] = 1; Add[1] = 0; Add[2] = 0;
            Movement_Interpreter(M, HS, BS, Add);
        break;
        case 75: case 'a': // LEFT
            Add[0] = 0; Add[1] = -1; Add[2] = 1;
            Movement_Interpreter(M, HS, BS, Add);
        break;
        case 77: case 'd': // RIGHT
            Add[0] = 0; Add[1] = 1; Add[2] = 1;
            Movement_Interpreter(M, HS, BS, Add);
        break;
        case 13: // 'enter' // LEAVE
            system("CLS");
            return false;
        break;
    }
    return true;
}
void Print_Hero_Boxes (int ML[], int M[17][19], int HS[], int BS[3][2]) {
    for(int i = 0; i < ML[0]; i++) {
        for(int j = 0; j < ML[1]; j++) {
            // VERIFY IF IT'S THE HERO'S POSITION THROUGH ITS SAVED POSITION
            if (i == HS[0] && j == HS[1]) {
                cor_texto(4,0);
                // PRINTING THE HERO (HEART SYMBOL)
                cout << char(3);
            // IF NOT HERO, VERIFY IF IT MAY BE ONE OF THE BOXES THROUGH THEIR SAVED POSITIONS
            } else if (i == BS[0][0] && j == BS[0][1] || i == BS[1][0] && j == BS[1][1] || i == BS[2][0] && j == BS[2][1]) {
                // VERIFY AND PRINT FILLED SPOTS (-7 AND BACKWARDS)
                if (M[i][j] <= -7) {
                    cor_texto(12,0);
                    cout << char(111);
                // IF HIGHER, THEN IT GOTTA BE A BOX
                } else {
                    cor_texto(15,0);
                    cout << char(254);
                }
            // IF NOT HERO NOR BOXES, IT'S MAP ELEMENTS' PRINTING TIME!
            } else {
                // FUNCTION TO ALLEGE THE SYMBOL TO THE CORRESPONDING NUMBER
                Adress_Characters(M, i, j);
            }
            cor_texto(7,0);
        }
        cout<<"\n";
    }
}
bool Map_1 (int ML[], int HS[], int BS[3][2]) {
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO     cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(out, &cursorInfo);
    short int CX = 0, CY = 0;
    COORD coord;
    coord.X = CX;
    coord.Y = CY;
    int Map1[17][19] = {

        8, 6, 6, 6, 6, 6, 9,                0,0,0,0,0,0,0,0,0,0,0,0,
        7, 0, 0, 0,-3, 0, 7,                0,0,0,0,0,0,0,0,0,0,0,0,
        7, 0, 8, 0, 9, 0, 7,                0,0,0,0,0,0,0,0,0,0,0,0,
        7, 0, 0, 0, 0, 0, 7,                0,0,0,0,0,0,0,0,0,0,0,0,
        7, 0,10, 0,11,-3, 7,                0,0,0,0,0,0,0,0,0,0,0,0,
        7, 0, 0,-3, 0, 0, 7,                0,0,0,0,0,0,0,0,0,0,0,0,
       10, 6, 6, 6, 6, 6,11,                0,0,0,0,0,0,0,0,0,0,0,0,

0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
    // VARIABLE TO STORE THE PLAYER'S DIRECTIONS
    char Key;
    // FLAG TO EXIT THE PLAYING SESSION IF FALSE
    bool Continuer = true;
    // MESSAGE TO WARN ABOUT HOW TO LEAVE THE GAME
    cout << "\n\n\n\n\n\n\n\n\t\t\t\tYou can leave any time by pressing 'enter' on your keyboard!\n\t\tYour progress WON'T be erased, choose 'Continue' on the Menu screen to play from where you left!\n\n\n\n  \t\t\t\t\t";
    system("pause");
    system("CLS");
    // SET THE BOX(ES) SAVE LOCATION THROUGH SUM, LATER THE RESULT WILL DECIDE IF WILL BE A BOX(0 + -4 = -4) OR FILLED SPOT(-3 + -4 = -7)
    Map1[BS[0][0]][BS[0][1]] = Map1[BS[0][0]][BS[0][1]] -4; Map1[BS[1][0]][BS[1][1]] = Map1[BS[1][0]][BS[1][1]] -5; Map1[BS[2][0]][BS[2][1]] = Map1[BS[2][0]][BS[2][1]] -6;
    // START GAME LOOP
    while(Continuer == true) {
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        // PRINTING THE MAIN ELEMENTS (HERO AND BOXES/FILLED SPOTS) STARTS, AS A FUNCTION
        Print_Hero_Boxes(ML, Map1, HS, BS);
        // VERYFING IF THERE WAS A KEY PRESSED
        if (_kbhit()) {
            // INTERPRETING THE PLAYER'S COMMANDS
            Key = getch();
            // FUNCTION FOR INTERPRETING THE PLAYER'S COMMANDS THROUGH MOVES INSIDE THE MATRIX
            Continuer = Capt_Movement(Key, Map1, HS, BS);
            // END OF THE GAME PRINTING AND MOVES FOR THE 'ROUND'
        }
        if (Continuer) { // this if is optional, of course there's no way u could win by pressing 'enter', but putting it here may lessen the times it will call the win verifier function, it sounds like it's a good thing idk
            Win_Verify(Map1, ML, Continuer);
            if (Continuer == false) {
                return true;
            }
        }
    }
    return false;
}
bool Map_2 (int ML[], int HS[], int BS[3][2]) {
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO     cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(out, &cursorInfo);
    short int CX=0, CY=0;
    COORD coord;
    coord.X = CX;
    coord.Y = CY;
    int Map2[17][19]= {

                      0, 8, 6, 9, 0, 8, 6, 6, 9, 0, 8, 6, 6, 9, 0, 8, 6, 9, 0,
                      8,11, 0,10,14,11, 0, 0,10, 6,11, 0, 0,10,14,11, 0,10, 9,
                      7, 0, 0,-3, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 7,
                      7, 0, 0, 8,13, 0, 0, 8, 6, 6, 6, 9, 0, 0,16, 9, 0, 0, 7,
                     10, 9, 0,16,15, 9, 0, 7, 0, 0, 0, 7, 0, 8,15,13, 0, 0, 7,
                      0, 7, 0, 7, 0, 7, 0, 7, 0, 0, 0, 7, 0, 7, 0, 7, 0, 8,11,
                      0, 7, 0, 7, 0, 7, 0, 7, 0, 0, 0, 7, 0, 7, 0, 7, 0, 7, 0,
                      0, 7, 0, 7, 0, 7, 0, 7, 0, 0, 0, 7, 0, 7, 0, 7, 0, 7, 0,
                      0, 7, 0, 7, 0, 7, 0, 7, 0, 0, 0, 7, 0, 7, 0, 7, 0, 7, 0,
                      0, 7, 0, 7, 0, 7, 0, 7, 0, 0, 0, 7, 0, 7, 0, 7, 0, 7, 0,
                      0, 7, 0, 7, 0, 7, 0, 7, 0, 0, 0, 7, 0, 7, 0, 7, 0, 7, 0,
                      0, 7, 0, 7, 0, 7, 0, 7, 0, 0, 0, 7, 0, 7, 0, 7, 0, 7, 0,
                      8,11, 0, 7, 0, 7, 0,10, 9, 0, 8,11, 0, 7, 0, 7, 0,10, 9,
                      7, 0, 0,10, 6,11, 0, 0, 7, 0, 7, 0, 0,10, 6,11, 0, 0, 7,
                      7, 0, 0, 0, 0, 0, 0, 0, 7, 0, 7, 0, 0, 0, 0, 0, 0, 0, 7,
                     10, 9, 0, 0, 7, 0, 0, 8,11, 0,10, 9, 0, 0, 7, 0, 0, 8,11,
                      0,10, 6, 6,15, 6, 6,11, 0, 0, 0,10, 6, 6,15, 6, 6,11, 0, };

    char Key;
    bool Continuer = true;
    cout << "\n\n\n\n\n\n\n\n\t\t\t\tYou can leave any time by pressing 'enter' on your keyboard!\n\t\tYour progress WON'T be erased, choose 'Continue' on the Menu screen to play from where you left!\n\n\n\n  \t\t\t\t\t";
    system("pause");
    system("CLS");
    Map2[BS[0][0]][BS[0][1]] = Map2[BS[0][0]][BS[0][1]] - 4; Map2[BS[1][0]][BS[1][1]] = Map2[BS[1][0]][BS[1][1]] - 4; Map2[BS[2][0]][BS[2][1]] = Map2[BS[2][0]][BS[2][1]] - 4;
    while(Continuer == true) {
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        Print_Hero_Boxes(ML, Map2, HS, BS);
        if (_kbhit()) {
            Key = getch();
            Continuer = Capt_Movement (Key, Map2, HS, BS);
        }
        if (Continuer) {
            Win_Verify (Map2, ML, Continuer);
            if (Continuer == false) {
                return true;
            }
        }
    }
    return false;
}
bool Map_3 (int ML[], int HS[], int BS[3][2]) {
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO     cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(out, &cursorInfo);
    short int CX=0, CY=0;
    COORD coord;
    coord.X = CX;
    coord.Y = CY;
    int Map3[17][19]= {

        0, 8, 6, 6, 6, 9,             0,0,0,0,0,0,0,0,0,0,0,0,0,
        8,11, 0, 0, 0, 7,             0,0,0,0,0,0,0,0,0,0,0,0,0,
        7, 0, 0, 0, 0, 7,             0,0,0,0,0,0,0,0,0,0,0,0,0,
        7, 0, 0, 0, 0,16, 6, 6, 9,    0,0,0,0,0,0,0,0,0,0,
       10,14, 9, 0, 8,13, 0, 0, 7,    0,0,0,0,0,0,0,0,0,0,
        0,16,11, 0, 7, 7, 0, 0, 7,    0,0,0,0,0,0,0,0,0,0,
        0, 7, 0, 0,10,11, 0,-3, 7,    0,0,0,0,0,0,0,0,0,0,
        0, 7, 0, 0, 0, 0, 0,-3, 7,    0,0,0,0,0,0,0,0,0,0,
        0,10, 9, 0, 0, 7, 0,-3, 7,    0,0,0,0,0,0,0,0,0,0,
        0, 0,10, 6, 6,13, 0, 0, 7,    0,0,0,0,0,0,0,0,0,0,
        0, 0, 0, 0, 0, 7, 0, 0, 7,    0,0,0,0,0,0,0,0,0,0,
        0, 0, 0, 0, 0,10, 6, 6,11,    0,0,0,0,0,0,0,0,0,0,

                      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, };

    char Key;
    bool Continuer = true;
    cout << "\n\n\n\n\n\n\n\n\t\t\t\tYou can leave any time by pressing 'enter' on your keyboard!\n\t\tYour progress WON'T be erased, choose 'Continue' on the Menu screen to play from where you left!\n\n\n\n  \t\t\t\t\t";
    system("pause");
    system("CLS");
    Map3[BS[0][0]][BS[0][1]] = Map3[BS[0][0]][BS[0][1]] - 4; Map3[BS[1][0]][BS[1][1]] = Map3[BS[1][0]][BS[1][1]] - 5; Map3[BS[2][0]][BS[2][1]] = Map3[BS[2][0]][BS[2][1]] - 6;
    while(Continuer == true) {
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        Print_Hero_Boxes(ML, Map3, HS, BS);
        if (_kbhit()) {
            Key = getch();
            Continuer = Capt_Movement (Key, Map3, HS, BS);
        }
        if (Continuer) {
            Win_Verify (Map3, ML, Continuer);
            if (Continuer == false) {
                return true;
            }
        }
    }
    return false;
}
//----------------------------------------------------------------------------INITIALIZING THE MENU-----------------------------------------------------------------------------//
int main() {
    // VARIABLES NECESSARY FOR THE MENU(switch/case) PARTS
    int Menu = 0, Map = 0;
    // VARIABLES NECESSARY TO START A GAME
    int Map_Lenghth[2] = {0,0}, Hero_Save[2] = {0, 0}, Box_Save[3][2] = {0, 0, 0, 0, 0, 0};
    // VARIABLES OF CONTROL
    bool Procedure = true, Won = false;
    // TRAP, THE ONLY WAY OUT IS TAPPING 4 ON THE MAIN MENU SCREEN
    while (Procedure) {
        system("CLS");
        cout << "\n\n\t\tMENU\n\n \t1 - New game\n\n \t2 - Continue\n\n \t3 - Information\n\n \t4 - Close\n\n";
        cin >> Menu;
        switch (Menu) {
//----------------------------------------------------------------------------------'NEW GAME'----------------------------------------------------------------------------------//
            case 1:
                system("cls");
                cout << "\n\n\t\tCHOOSE A MAP\n\n \t1 - Tbox (50): 2 \n\n\t2 - Jcdlevels (17): 1 \n\n\t3 - Loma (60): 6 \n\n\t4 - Go back\n\n";
                cin >> Map;
                switch(Map) {
                    case 1:
                        system("CLS");
                        // DEFINE THE HERO STARTING POSITION (NOT ALTERABLE) NECESSARY TO THE 'CONTINUE' FEATURE (WILL BE USED TO DIFFERENTIATE THE MAPS)
                        Map_Lenghth[0] = 7; Map_Lenghth[1] = 7;
                        // ESTABILISH THE HERO POSITION SAVE (ALTERABLE)
                        Hero_Save[0] = 5; Hero_Save[1] = 2;
                        //ESTABILISH THE BOX(ES) POSITION SAVE (ALTERABLE)
                        Box_Save[0][0] = 1; Box_Save[0][1] = 3;
                        Box_Save[1][0] = 3; Box_Save[1][1] = 3;
                        Box_Save[2][0] = 5; Box_Save[2][1] = 3;
                        Won = Map_1(Map_Lenghth, Hero_Save, Box_Save);
                        if(Won == true) {
                            Win_restart(Map_Lenghth, Hero_Save, Box_Save);
                        }
                    break;
                    case 2:
                        system("CLS");
                        Map_Lenghth[0] = 17; Map_Lenghth[1] = 19;
                        Hero_Save[0] = 1; Hero_Save[1] = 2;
                        Box_Save[0][0] = 2; Box_Save[0][1] = 2;
                        Box_Save[1][0] = -2; Box_Save[1][1] = -2;
                        Box_Save[2][0] = -2; Box_Save[2][1] = -2;
                        Won = Map_2(Map_Lenghth, Hero_Save, Box_Save);
                        if (Won == true) {
                            Win_restart(Map_Lenghth, Hero_Save, Box_Save);
                        }
                    break;
                    case 3:
                        system("CLS");
                        Map_Lenghth[0] = 12; Map_Lenghth[1] = 9;
                        Hero_Save[0] = 4; Hero_Save[1] = 6;
                        Box_Save[0][0] = 6; Box_Save[0][1] = 6;
                        Box_Save[1][0] = 7; Box_Save[1][1] = 6;
                        Box_Save[2][0] = 8; Box_Save[2][1] = 6;
                        Won = Map_3(Map_Lenghth, Hero_Save, Box_Save);
                        if (Won == true) {
                            Win_restart(Map_Lenghth, Hero_Save, Box_Save);
                        }
                    break;
                    case 4:
                        // RETURN TO THE MENU
                    break;
                    default:
                        system("cls");
                        cout << "\n\n\n\n\n\n\t\t\t\t\t\t Invalid option!\n\t\t\t\t\t\tTry again please:\n\n\n\n\t\t\t\t    ";
                        system("pause");
                }
            break;
//----------------------------------------------------------------------------------'CONTINUE'----------------------------------------------------------------------------------//
            case 2:
                // IF NO 'SAVE DATA' THEN NOT A VALID OPTION
                if (Hero_Save[0] == 0 && Hero_Save[1] == 0) {
                    system("CLS");
                    cout << "\n\n\n\n\t\t\t\tYou CAN'T continue a game you haven't even started!\n\t\t\t\t\t Please, press 'New game' next time:\n\n\n\n\t\t\t\t     ";
                    system("pause");
                // CONTINUE MAP 1
                } else if (Map_Lenghth[0] == 7 && Map_Lenghth[1] == 7) {
                    system("CLS");
                    Won = Map_1(Map_Lenghth, Hero_Save, Box_Save);
                    // VERIFY IF THE CLOSURE WAS A PAUSE OR A WINNING SITUATION
                    if (Won == true) {
                        // FUNCTION TO RESTART THE VARIABLES / CLEAR 'SAVE DATA'
                        Win_restart(Map_Lenghth, Hero_Save, Box_Save);
                    }
                // CONTINUE MAP 2
                } else if (Map_Lenghth[0] == 17 && Map_Lenghth[1] == 19) {
                    system("CLS");
                    Won = Map_2(Map_Lenghth, Hero_Save, Box_Save);
                    if (Won == true) {
                        Win_restart(Map_Lenghth, Hero_Save, Box_Save);
                    }
                    // CONTINUE MAP 3
                } else {
                    system("CLS");
                    Won = Map_3(Map_Lenghth, Hero_Save, Box_Save);
                    if (Won == true) {
                        Win_restart(Map_Lenghth, Hero_Save, Box_Save);
                    }
                }
            break;
//--------------------------------------------------------------------------------'INFORMATION'---------------------------------------------------------------------------------//
            case 3:
                system ("CLS");
                cout << "\n\n\n\t\t\t\t\t\t\tAUTHOR\n\n\t\t\t\t\t\tLogan Santana Fernandes\n\n\t\t\t\t\t\t         DATE\n\n\t\t\t\t\t\t      April/2023";
                cout << "\n\n\n\n\t\t\t\t\t\t\tRULES\n\n\t\t\t  You are a hero (" << char(3) << ") in a dungeon filled with boxes (" << char(254) << ") and spots (" << char(158) << ")";
                cout << "\n\t You can use the keys 'w' for going UP, 's' for going DOWN, 'a' for going LEFT and 'd' for going RIGHT.\n";
                cout << "\t\t\t This is a filled spot (" << char(111) << "), it is a box (" << char(254) << ") on top of a spot (" << char(158) << ")\n";
                cout << "   Your objective is to place each (" << char(254) << ") in a different (" << char(158) << "), all that by moving your character to push them accordingly,\n";
                cout << "\t\t\t\t\tleaving only (" << char(111) << ") on the map to win.\n";
                cout << " If you try to move to a place where a box (" << char(254) << ")/filled spot (" << char(111) << ") is, the box will be pushed to the direction you are going";
                cout << "  but only if there is NOT another box/wall in front of it. Remember you can walk over spots (" << char(158) << "), but NOT over walls (" << char(205) << ")";
                cout << "\n\n\n\n\t\t\t\t       ";
                system("Pause");
            break;
//-----------------------------------------------------------------------------------'CLOSE'-----------------------------------------------------------------------------------//
            case 4:
                system("CLS");
                cout << "\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t ";
                Procedure = false;
            break;
//--------------------------------------------------------------------------------INVALID OPTION--------------------------------------------------------------------------------//
            default:
                // DENY ANY NONSENSE OPTION BY JUST LETTING THE WHILE TRAP WORK
                system("cls");
                cout << "\n\n\n\n\n\n\t\t\t\t\t\t Invalid option!\n\t\t\t\t\t\tTry again please:\n\n\n\n\t\t\t\t    ";
                system("pause");
        // SWITCH (menu) END
        }
    // WHILE (procedure) END
    }
    return 0;
}
