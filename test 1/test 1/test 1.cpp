#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Test {

public:
    int matrix[2][2] = {{1, 2}, {3, 4}};

    void print() {
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                cout << matrix[i][j] << " ";
            }
        }
    }



};

int main()
{
  
    int test[2][2] = { {1, 2}, {3, 4} };

    test[0][0] = 4;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            cout << test[i][j] << " ";
        }
    }

}