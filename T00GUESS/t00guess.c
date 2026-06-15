/* Klinskikh Ilya, IK1 01.06.2026 */
#include <windows.h>

int AskQuestion(int mid) {
    char message[256];
    sprintf(message, "your number is more than %d?", mid);
    return MessageBox(NULL, message, "guess the number", MB_YESNO | MB_ICONQUESTION);
}

void WinGame(int number) {
    char message[256];
    sprintf(message, "your number is - %d!", number);
    MessageBox(NULL, message, "end", MB_OK | MB_ICONINFORMATION);
}

int main() {
    int low = 1;      
    int high = 100;   
    int mid;          
    int answer;       

    MessageBox(NULL, "change the number from 1 to 100", "guess the number", MB_OK | MB_ICONINFORMATION);

    while (low <= high) {
        mid = (low + high) / 2;  

        if (low == high) {
            WinGame(low);
            return 0;
        }

        answer = AskQuestion(mid);

        if (answer == IDYES) {
            low = mid + 1;
        } else if (answer == IDNO) {
            high = mid;
        } else {
            return 0;
        }
    }

    return 0;
}