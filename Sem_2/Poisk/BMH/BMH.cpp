#include <iostream>
#include <std::string>

struct Shift {
	char letter;
	int shift = 0;
};

int BMHSearch(std::string str, std::string substr) {
	int size = substr.size();
	Shift* tsh = new Shift[size];

	for (int i=0; i < size - 1; i++) {
		tsh[i].letter = substr[i];
		tsh[i].shift = size-1-i;
	}
	tsh[size - 1].letter = substr[size - 1];
	tsh[size - 1].shift = size;

	int idx = 0;
	while (idx + size - 1 < str.size()) {
		for (int i=size-1; i >= 0; i--) {
			if (substr[i] == str[i + idx]) {
				if (i == 0) {
					delete[] tsh;
					return idx;
				}
			}
			else {
				for (int j=size-1; j >= -1; j--) {
					if (j == -1) {
						idx += size;
					}
					else if (str[i + idx] == tsh[j].letter) {
						idx += tsh[j].shift;
						break;
					}
				}
				break;
			}
		}
	}

	delete[] tsh;
	return -1;
}



int main() {

	std::string str = "Hello hello helo World world";
	std::string substr = "hello";

	std::cout << BMHSearch(str, substr);
}