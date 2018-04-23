#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

int* prefix(string input);

int main() {
    string P, T, positions;
    stringstream output;
    getline(cin, P);
    getline(cin, T);
    int size = P.length();
    P += "@" + T;
    auto result = prefix(P);
    for(int i = 0; i < P.length(); i++) {
        if(result[i] == size) {
            output << i - 2*size << ",";
        }
    }
    positions = output.str();
    if(positions.length() == 0) {
        cout << "-1";
    } else {
        positions = positions.substr(0, positions.length() - 1);
        cout << positions;
    }
    return 0;
}

int* prefix(string input) {
    int n = input.length();
    auto sub_size = new int[n];
    for(int i = 0; i < n; i++) {
        sub_size[i] = 0;
    }
    for(int i = 1; i < n; i++) {
        int j = sub_size[i - 1];
        while((j > 0) && (input[i] != input[j])) {
            j = sub_size[j - 1];
        }
        if(input[i] == input[j]) {
            j++;
        }
        sub_size[i] = j;
    }
    return sub_size;
}