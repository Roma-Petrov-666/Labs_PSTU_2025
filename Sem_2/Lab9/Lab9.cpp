#include <iostream>
#include <fstream>
#include <string>
using namespace std;

string* readStringsFromFile(string& filename, int count) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Ошибка открытия файла" << endl;
        return nullptr;
    }

    string* strings = new string[count];

    string line;
    for (int i=0; i < count; i++) {
        if (!getline(file, line)) {
            cout << "Ошибка чтения строки" << endl;
            delete[] strings;
            count=0;
            return nullptr;
        }
        strings[i] = line;
    }
	file.close();
    return strings;
}

void writeStringsToFile(string* strings, int size, string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Ошибка открытия файла для записи" << endl;
        return;
    }

    for (int i=0; i < size; i++) {
        file<<strings[i]<<endl;
    }
    file.close();
}

int countWords(string str) {
    int counter=0;
    for (int i=1; i < str.length(); i++) {
        if (str[i] == ' ' && str[i-1] != ' ') {counter++;}
    }
    
    if (str[str.length()-1] == ' ') {
        return counter;
    }
    else {
        return counter+1;
    }
}

void Split(string arr[], string str) {
    int i=0;
    if (str[0] != ' ') { arr[i] += str[0]; }
    for (int j=1; j < str.length(); j++) {
        if (str[j] != ' ') {
            arr[i] += str[j];
        } else if (str[j-1] != ' ') {i++;}
    }
}

bool hasDuplicateWords(string& line) {
    int count_words = countWords(line);
	string* words = new string[count_words];
    Split(words, line);
	
    for (int i=0; i < count_words; i++) {
        for (int j=i+1; j < count_words; j++) {
            if (words[i] == words[j]) {
				delete[] words;
                return true;
            }
        }
    }
	delete[] words;
    return false;
}

void LinesWithoutDuplicates(string*& lines, int& size) {
    int newSize=0;
    for (int i=0; i < size; i++) {
        if (!hasDuplicateWords(lines[i])) {
            newSize++;
        }
    }

    string* newLines = new string[newSize];
    int idx=0;
    for (int i=0; i < size; i++) {
        if (!hasDuplicateWords(lines[i])) {
            newLines[idx++] = lines[i];
        }
    }

    delete[] lines;
    lines = newLines;
    size = newSize;
}

int countVowels(string line) {
	string alf = "aeiouy";
	int count=0;
	
	for (int i=0; i < line.length(); i++) {
        for (int j=0; j < 6; j++) {
            if (line[i] == alf[j]) {
                count++;
            }
        }
    }
	
	return count;
}

int main() {
	int n=10;
	string filename = "F1.txt";
	string* lines = readStringsFromFile(filename, n);
	if (lines == nullptr) {
		cout<<"Ошибка чтения";
        return 1;
    }
	
	filename = "F2.txt";
	LinesWithoutDuplicates(lines, n);
	writeStringsToFile(lines, n, filename);
	
	filename = "F2.txt";
	string* line = readStringsFromFile(filename, 1);
	cout<<countVowels(line[0]);
	
	delete[] lines;
    return 0;
}