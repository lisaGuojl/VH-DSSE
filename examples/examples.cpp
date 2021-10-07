#include <examples.h>
#include <iostream>
#include <limits>
#include "Client.h"
#include "Utils.h"
#include <ctime>        // std::time
#include <cstdlib>
#include <unordered_set>
using namespace std;
int main()
{
	cout << "VH-DSSE test" <<endl;
	while (true)
    	{
        cout << "+---------------------------------------------------------+" << endl;
        cout << "| The following examples should be executed while reading |" << endl;
        cout << "| comments in associated files in examples/.              |" << endl;
        cout << "+---------------------------------------------------------+" << endl;
        cout << "| Examples                   | Source Files               |" << endl;
        cout << "+----------------------------+----------------------------+" << endl;
        cout << "| 1. search test             | 1. SearchTest.cpp          |" << endl;
        cout << "| 2. update test             | 2. UpdateTest.cpp          |" << endl;
        cout << "| 3. accuracy test           | 3. AccuracyTest.cpp        |" << endl;
        cout << "+----------------------------+----------------------------+" << endl;

        int selection = 0;
        bool valid = true;
        do
        {
            cout << endl << "> Run example (1 ~ 3) or exit (0): ";
            if (!(cin >> selection))
            {
                valid = false;
            }
            else if (selection < 0 || selection > 3)
            {
                valid = false;
            }
            else
            {
                valid = true;
            }
            if (!valid)
            {
                cout << "  [Beep~~] valid option: type 0 ~ 3" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        } while (!valid);

        switch (selection)
        {
        case 1:
            SearchTest();
            break;

        case 2:
            UpdateTest();
            break;

        case 3:
            AccuracyTest();
            break;

        case 0:
            return 0;
        }

    }

    return 0;
}
