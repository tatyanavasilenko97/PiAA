#include <iostream>
#include <vector>
#include <string>

std::vector < size_t > prefix (std::string s)
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

std::vector < size_t > kmp (std::string s, std::string t)
{
    std::vector < size_t > prefix_func = prefix(t);
    size_t j = 0;
    size_t k = 0;
    std::vector < size_t > findInd;
    for (size_t i = 0; i < s.length(); i++)
    {
        while (j > 0 && t[j] != s[i]) j = prefix_func[j - 1];
        if (t[j] == s[i]) j++;
        if (j == t.length())
        {
            findInd.push_back(i + 1 - t.length());
        }
    }
    return findInd;
}

int main()
{
    std::string s, t;
    std::cin >> t;
    std::cin >> s;
    std::vector < size_t > res = kmp(s,t);
    if (res.size() > 0)
    {
        for (size_t i = 0; i < res.size() - 1; i++)
            std::cout << res[i] << ",";
        std::cout << res[res.size() - 1];
    }
    else std::cout << -1;
}
