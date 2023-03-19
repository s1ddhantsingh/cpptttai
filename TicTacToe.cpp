#include <string>
#include <cstdio>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

void board_init();
void board_init(string);
/*
0 ==> no winner
1 ==> player 1 wins: X
2 ==> player 2 wins: O
-1 => draw
 */
int calcwinner(string);

int main(int argc, char **arg)
{
    string board = string(9, ' ');
    string used = string(9, '*');
    int winner = 0; // 0 ==> no winner
                    // 1 ==> player 1 wins: X
                    // 2 ==> player 2 wins: O
                    // -1 => draw

    int move = 1; // 1 ==> player 1: X
                  // -1 ==> player 2: O

    board_init();

    while (!winner) // 0 ==> false in C++
    {
        int x;
        cout << (move == 1 ? "X's" : "O's") << " move: ";
        cin >> x;
        while (!cin || x > 9 || x < 1 || used[x - 1] != '*')
        {
            if (!cin)
            {
                cin.clear();
                cin.ignore(200, '\n');
            }

            cout << "Please choose a valid move: ";
            cin >> x;
        }
        cout << "\n";

        used[x - 1] = '|';
        board[x - 1] = (move == 1 ? 'X' : 'O');
        move *= -1;

        board_init(board);
        winner = calcwinner(board);
        cout << "Winner: " << winner << endl;
        // check boards for winners...
    }
}

void board_init()
{
    string board = "";
    for (int i = 1; i < 10; i++)
        board.append(to_string(i));
    board_init(board);
}

void board_init(string pos)
{
    // iterate over positions
    int start = 0;

    // top of board
    cout << string(13, '-') << "\n";
    for (int i = 0; i < 3; i++)
    {
        // i
        /*
        0 --> 0, 1, 2
        1 --> 3, 4, 5
        2 --> 6, 7, 8
        */

        // specific row layout
        cout << left << "| " << pos[start++];
        cout << setw(2) << right << "|"
             << " " << pos[start++];
        cout << setw(2) << right << "|"
             << " " << pos[start++];
        cout << setw(3) << right << "|\n";

        cout << string(13, '-') << "\n";
    }
}

/*
0 ==> no winner
1 ==> player 1 wins: X
2 ==> player 2 wins: O
-1 => draw
 */
int calcwinner(string pos)
{
    string s = "012345678036147258048246";
    for (int i = 0; i < s.length(); i++)
    {
        // cout << i << endl;
        // cout << ++i << endl;
        // cout << ++i << endl;
        if (pos[s[i]] == pos[s[++i]] && pos[s[i]] == pos[s[++i]])
        {
            if (pos[s[i]] == ' ')
                continue;
            else
                return (pos[s[i]] == 'X') ? 1 : 2;
        }
        // cout << i << endl;
    }
    // at this point we can have either a draw or a no-winner condition
    /*
    find all blank spaces in the string --> if it is possible to get a match then return 0
    otherwise return -1 eventually
    */
    for (int i = 0; i < pos.length(); i++)
    {
        if (pos[i] == ' ')
        {
            pos[i] = 'X';
            int temp1 = calcwinner(pos); // potentially recursively fixed?
            if (temp1 != -1)
                return 0;
            pos[i] = 'Y';
            int temp2 = calcwinner(pos);
            if (temp2 != -1)
                return 0;
            pos[i] = ' ';
            int temp3 = calcwinner(pos);
            if (temp1 != -1 || temp2 != -1 || temp3 != -1)
                return 0;
        }
    }
    return -1;
    /*
    // horizontal checks
    pos[0] == pos[1] && pos[1] == pos[2]
    pos[3] == pos[4] && pos[4] == pos[5]
    pos[6] == pos[7] && pos[7] == pos[8]

    // vertical checks
    pos[0] == pos[3] && pos[3] == pos[6]
    pos[1] == pos[4] && pos[4] == pos[7]
    pos[2] == pos[5] && pos[5] == pos[8]

    // diagonal checks
    pos[0] == pos[4] && pos[4] == pos[8]
    pos[2] == pos[4] && pos[4] == pos[6]
    */
}