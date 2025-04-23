#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/wait.h>
using namespace std;

int main() {
int choice;
string arg1, arg2;
cout << "Choose an operation:\n";
cout << "1. Copy File (cp)\n";
cout << "2. Search Pattern (grep)\n";
cout << "Enter your choice: ";
cin >> choice;
if (choice == 1) {
cout << "Enter Source File: ";
cin >> arg1;
cout << "Enter Destination File: ";
cin >> arg2;
} else if (choice == 2) {
cout << "Enter Pattern: ";
cin >> arg1;
cout << "Enter File Name: ";
cin >> arg2;
} else {
cerr << "Invalid choice!\n";
return 1;
}

pid_t pid = fork();
if (pid < 0) {
cerr << "Fork failed!\n";
return 1;
} else if (pid == 0) {
// Child Process
if (choice == 1) {
execl("./cp", "./cp", arg1.c_str(), arg2.c_str(), nullptr);
} else if (choice == 2) {
execl("./grep", "./grep", arg1.c_str(), arg2.c_str(), nullptr);
}
// If execl fails
perror("Error executing execl");
exit(1);
} else {
// Parent Process
wait(nullptr);
}
return 0;
}
