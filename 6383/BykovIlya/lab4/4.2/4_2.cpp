#include <iostream>
#include <vector>
#include <string>

std::vector < size_t > prefix (const std::string & s)
{
    std::vector < size_t > p(s.length(), 0);
    for (size_t i = 1; i < s.length(); i++)
    {
        size_t j = p[i - 1];
        while (j > 0 && s[i] != s[j]) j = p[j - 1];
        if (s[i] == s[j]) j++;
        p[i] = j;
    }
    return p;
}

int findCycle (const std::string & s, const std::string & t)
{
    if (s.length() != t.length()) return -1;
    std::string new_s = s + s;
    std::vector < size_t > prefix_func = prefix(t);
    size_t j = 0;
    size_t k = 0;
    size_t findInd = -1;
    for (size_t i = 0; i < new_s.length(); i++)
    {
        while (j > 0 && t[j] != new_s[i]) j = prefix_func[j - 1];
        if (t[j] == new_s[i]) j++;
        if (j == t.length())
        {
            findInd = (i + 1 - t.length());
            break;
        }
    }
    return findInd;
}

int main()
{
    std::string s, t;
    std::cin >> t;
    std::cin >> s;
    std::cout << findCycle(t,s);
}