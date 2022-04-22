#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

std::string removeSpecialCharacter(std::string s)
{
    for (int i = 0; i < s.size(); i++) {
        //check if there is a space
        if (s[i] != ' '){
            //check if there are special characters
            if (s[i] < 'A' || s[i] > 'Z' && s[i] < 'a' || s[i] > 'z'){
                // erase special characters
                s.erase(i, 1);
                i--;
            }
            //converting uppercase to lowercase by icnreceasing
            //the ASCII + 32
            if (s[i] >= 'A' && s[i] <= 'Z'){
                s[i] += 32;
            }
        }
    }
    return s;
}

int main()
{
    std::string line;
    std::string wholeText;
    int counter = 0;
    std::ifstream infile("file.txt");
    while (std::getline(infile, line)){
        wholeText.append(line);
    }
    infile.close();
    cout << wholeText << endl;
    std::string fixedText;
    fixedText = removeSpecialCharacter(wholeText);

    cout << fixedText << endl;
}
