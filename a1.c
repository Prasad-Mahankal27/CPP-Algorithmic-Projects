#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(int argc, char *argv[]) {
if (argc != 3) {
cerr << "Usage: grep <pattern> <file>\n";
return 1;
}
string pattern = argv[1];
string filename = argv[2];
ifstream fin(filename);
if (!fin) {
cerr << "Error: Cannot open file '" << filename << "'\n";
return 1;
}

string line;
int lineNumber = 1;
bool found = false;
while (getline(fin, line)) {
if (line.find(pattern) != string::npos) {
cout << "Found at Line " << lineNumber << ": " << line << '\n';
found = true;
}
lineNumber++;
}
if (!found) {
cout << "Pattern not found in the file.\n";
}
fin.close();
return 0;
}