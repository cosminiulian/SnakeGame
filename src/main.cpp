#include <iostream>
#include <conio.h> // Pentru "_kbhit()" si "_getch()".
#include <windows.h> // Pentru "Sleep()".
using namespace std;

bool gameOver; // Variabila globala care determina sau nu sfarsitul jocului.
const int width = 20;   // Dimensiunea
const int height = 20; //            mapei.
int x, y; // Coordonatele pozitiei capului.
int tailX[100],tailY[100]; // Vectori de coordonate pentru fiecare lungime a cozii.Cu cat lungimea cozii creste mai mult cu atat devin si vectorii mai "ocupati",utilizati pt implementare.
int nTail; // Lungimea cozii.
int fruitX,fruitY; // Coordonatele pozitiei fructului.
int score; // Scorul jocului.

enum Direction {STOP = 0, LEFT, RIGHT, UP, DOWN};
Direction dir; // Variabila care retine directia sarpelui.


void Setup() // Setarile initiale.
{

    gameOver = false;
    dir = STOP; // initial nu se misca de pe mapa.
    x = width / 2;   // Capul va fi
    y = height / 2; //           pozitionat in centru la inceput.
    fruitX = rand() % width;   // Va genera o pozitie random
    fruitY = rand() % height; //                        pentru fruct.
    score = 0; // Initial scorul este zero.
    nTail = 0; // Coada  nu exista la inceput.
}


void Draw() // Functia care desenaza mapa cu totul.
{

    system("cls"); // Curata ecranul.
    for(int i = 0; i < width + 2; ++i) // Zidul de sus. (width+2 deoarece trebuie sa acopere si marginile laterale).
        cout << "#";
    cout << endl; // Se trece pe randul urmator.

    for(int i = 0; i < width; ++i)
    {
        for (int j = 0; j < height; ++j)
        {
            if (j == 0)       //  Zidul
                cout << "#"; //       din stanga.

            if (i == y && j == x) // Verificam daca coordonatele corespundul cu cele ale capului si apoi afisam.
                cout << "O";
            else if(i == fruitY && j == fruitX) // Alfel verificam daca coordonatele corespund cu cele ale fructului si afisam.
                cout << "F";
            else
            {
                bool print = false;
                for(int k = 0; k < nTail; ++k) // Afisam coada.
                    if(tailX[k] == j && tailY[k] == i)
                    {
                        cout << "o";
                        print = true;
                    }
                if(!print) // Daca exista coada in zona respectiva atunci nu afisam spatiu. Cum e logic daca exista ceva in acel spatiu atunci nu mai este un spatiu liber.
                    cout << " "; // Interiorul mapei.
            }
            if (j == width - 1) // Zidul
                cout << "#";   //      din dreapta.
        }
        cout << endl; // Se trece cu urmatoarea linie pe randul urmator.
    }

    for(int i = 0; i < width + 2; ++i) // Zidul de jos.
        cout << "#";
    cout << endl; // Se trece pe randul urmator.
    cout << "Score:" << score << endl; // Afiseaza jos scorul de fiecare data cand functia e apelata.
}


void Input()
{
    if(_kbhit()) // Daca se apasa tastatura atunci returneaza o val poz. altfel returneaza zero. Verifica practic daca se introduc date de la tastatura. Daca tastatura este apasata.
        switch(_getch()) // Returneaza codul ASCII tastat de la tastatura.
        {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'x':
            gameOver = true;
            break;
        }

}


void Logic()
{
    int prevX = tailX[0];  // Retinem
    int prevY = tailY[0]; //
    int prev2X,prev2Y;
    tailX[0] = x;  // Vectorul de coordonate tailX si tailY
    tailY[0] = y; //                                    retin coordonatele capului.Inclusiv cea curenta si cele in care a fost inainte ,de lungimea cozii.
    for(int i = 1; i < nTail; ++i)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch(dir)
    {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    }

    // if(x > width || x < 0 || y > height || y < 0 ) // Acesta era cazul in care intra intr-un perete atunci era gameOver.
    //   gameOver = true;

    if(x >= width)
        x = 0;
    else if(x < 0)
        x = width-1;    // In cazul in care intra intr-un perete atunci
    if(y >= height)
        y = 0;
    else if(y < 0)
        y = height-1; //                                             o sa iasa din  peretele paralel.

    for(int i = 0; i < nTail; ++i) // Daca intram in propria coasa atunci gameOver.
        if(tailX[i] == x && tailY[i] == y)
            gameOver = true;

    if(x == fruitX && y == fruitY)
    {
        score+=10;
        fruitX = rand() % width;   // Va genera o pozitie random pentru fruct
        fruitY = rand() % height; //                                       de fiecare data cand acesta este "mancat".
        nTail++; // Crestem coada cu o unitate.
    }
}

void DisplayGameOver()
{

    if (gameOver == true)

        cout << endl << " G A M E   O V E R   !" << endl;

}

int main()
{
    Setup();
    while(!gameOver)
    {

        Draw();
        Input();
        Logic();
        Sleep(100); // Incetineste procesul de rulare in command prompt.
        DisplayGameOver();
    }


    return 0;
}
