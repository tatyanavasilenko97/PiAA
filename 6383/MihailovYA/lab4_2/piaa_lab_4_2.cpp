#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector <int> compute_prefix_func (const string & s)
{
    vector <int> p(s.length(), 0);
    for (int i = 1; i < s.length(); i++)
    {
        int j = p[i - 1];
        while (j > 0 && s[i] != s[j]) j = p[j - 1];
        if (s[i] == s[j]) j++;
        p[i] = j;
    }
    return p;
}

int ifCycle (const string & s, const string & t)
{
    if (s.length() != t.length()) return -1;
    string temp = s + s;
    vector <int> q = compute_prefix_func(t);
    int j = 0;
    int k = 0;
    int indexCycle = -1;
    for (int i = 0; i < temp.length(); i++)
    {
        while (j > 0 && t[j] != temp[i]) j = q[j - 1];
        if (t[j] == temp[i]) j++;
        if (j == t.length())
        {
            indexCycle = (i + 1 - t.length());
            break;
        }
    }
    return indexCycle;
}

int main()
{
    string s, t;
    cin >> t;
    cin >> s;
    cout << ifCycle(t,s);
    return 0;
}
