#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

int* prefix(const string& input);

int main() {
    string P, T;
    getline(cin, P);
    getline(cin, T);
    int size = P.length();
    if(P.length() != T.length()) {
        cout << "-1";
        return 0;
    }
    T += "@" + P + P;
    auto result = prefix(T);
    for(size_t i = 0; i < T.length(); i++) {
        if(result[i] == size) {
            cout << i - 2 * size;
            return 0;
        }
    }
    cout << "-1";
    return 0;
}

int* prefix(const string& input) {
    size_t n = input.length();
    auto sub_size = new int[n];
    for(int i = 0; i < n; i++) {
        sub_size[i] = 0;
    }
    for(size_t i = 1; i < n; i++) {
        size_t j = sub_size[i - 1];
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