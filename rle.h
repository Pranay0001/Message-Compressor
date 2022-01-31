#include <bits/stdc++.h>
using namespace std;

string RunLengthEncoding(string str)
{
    string ans = "";
    int n = str.length();
    for (int i = 0; i < n; i++) {
 
        // Count occurrences of current character
        int count = 1;
        while (i < n - 1 && str[i] == str[i + 1]) {
            count++;
            i++;
        }

        ans.push_back(str[i]);
        if(count > 1) ans.push_back(count);
    }
    
    return ans;
}