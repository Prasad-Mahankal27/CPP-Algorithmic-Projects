#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char *argv[]) {
if (argc != 3) {
cerr << "Usage: cp <source_file> <destination_file>\n";
return 1;
}
ifstream fin(argv[1]);
if (!fin) {
cerr << "Error: Cannot open source file '" << argv[1] << "'\n";
return 1;
}
ofstream fout(argv[2]);
if (!fout) {
cerr << "Error: Cannot open destination file '" << argv[2] << "'\n";
return 1;
}
string line;
while (getline(fin, line)) {
fout << line << '\n';
}
fin.close();
fout.close();
cout << "File copied successfully!\n";
return 0;
}
