#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct BidirectionalList {
	struct Node {
		string data;
		Node* nextElementAddress = nullptr;
		Node* prevElementAddress = nullptr;
	};

	int size=0;
	Node* firstElementAddress = nullptr;
	Node* endElementAddress = nullptr;

	void print() {
		Node* node = firstElementAddress;
		if (size == 0) {
			cout<<"список пуст"<<endl;
		}
		else {
			for (int i=0; i < size; i++) {
				cout<<i<<": "<<node->data<<endl;
				node = node->nextElementAddress;
			}
		}
		cout<<endl;
	}

	string getData(int node_i) {
		if (node_i < size) {
			Node* node = firstElementAddress;
			for (int i=0; i < node_i; i++) {
				node = node->nextElementAddress;
			}
			return node->data;
		}
		else {
			cout<<"элемента с номером "<<node_i<<" не существует, так как "<<node_i<<" >= "<<size;
			return "";
		}
	}

	BidirectionalList() {};

	/////////////////// add ///////////////////
	void add(string data, int node_i) {
		if (node_i > size) {
			cout<<"номер больше размера списка, элемент будет добавлен в конец "<<node_i<<" > "<<size<<endl<<endl;
			node_i = size;
		}

		Node* newNode = new Node{ data, nullptr, nullptr };

		if (size == 0) {
			firstElementAddress = newNode;
			endElementAddress = newNode;
		}
		else if (node_i == 0) {
			newNode->nextElementAddress = firstElementAddress;
			firstElementAddress->prevElementAddress = newNode;
			firstElementAddress = newNode;
		}
		else if (node_i == size) {
			newNode->prevElementAddress = endElementAddress;
			endElementAddress->nextElementAddress = newNode;
			endElementAddress = newNode;
		}
		else {
			Node* node = firstElementAddress;
			for (int i=0; i < node_i-1; i++) {
				node = node->nextElementAddress;
			}
			newNode->nextElementAddress = node->nextElementAddress;
			newNode->prevElementAddress = node;
			node->nextElementAddress->prevElementAddress = newNode;
			node->nextElementAddress = newNode;
		}
		size++;
	}

	void addInEnd(string data) {
		add(data, size);
	}
	///////////////////////////////////////////

	/////////////////// del ///////////////////
	void del(int node_i) {
		if (size == 0) {
			cout<<"Список пуст, удаление невозможно."<<endl;
			return;
		}
		if (node_i >= size) {
			cout<<"Номер больше размера списка, будет удален последний элемент."<<endl;
			node_i = size-1;
		}

		if (node_i == 0) {
			Node* toDelete = firstElementAddress;
			firstElementAddress = firstElementAddress->nextElementAddress;
			if (firstElementAddress != nullptr)
				firstElementAddress->prevElementAddress = nullptr;
			else
				endElementAddress = nullptr;
			delete toDelete;
		}
		else if (node_i == size-1) {
			Node* toDelete = endElementAddress;
			endElementAddress = endElementAddress->prevElementAddress;
			if (endElementAddress != nullptr)
				endElementAddress->nextElementAddress = nullptr;
			else
				firstElementAddress = nullptr;
			delete toDelete;
		}
		else {
			Node* node = firstElementAddress;
			for (int i = 0; i < node_i - 1; i++) {
				node = node->nextElementAddress;
			}
			Node* toDelete = node->nextElementAddress;
			node->nextElementAddress = toDelete->nextElementAddress;
			toDelete->nextElementAddress->prevElementAddress = node;
			delete toDelete;
		}
		size--;
	}

	void delEndElement() {
		del(size-1);
	}
	///////////////////////////////////////////

	////////////////// file //////////////////
	void saveInFile(string name) {
		ofstream file(name);
		Node* node = firstElementAddress;
		for (int i=0; i < size; i++) {
			file << node->data << endl;
			node = node->nextElementAddress;
		}
		cout<<" список сохранен в файл: "<<name<<endl;
		file.close();
	}

	void loadFromFileAddInEnd(string name) {
		ifstream file(name);
		string str = " ";
		while (getline(file, str)) {
			addInEnd(str);
		}
		file.close();
		cout<<"список загружен из файла: "<<name<<endl;
	}

	void loadFromFileOverwriting(string name) {
		deleteList();
		loadFromFileAddInEnd(name);
	}
	///////////////////////////////////////////

	void deleteList() {
		while (size > 0) {
			del(0);
		}
		cout<<"Список удален"<<endl;
	}

	~BidirectionalList() {
		if (size > 0) { deleteList(); }
	}
};

int main() {
	// 1
	BidirectionalList list;

	list.addInEnd("D0");
	list.addInEnd("D1");
	list.addInEnd("D2");
	list.addInEnd("D3");
	list.addInEnd("D4");

	// 2
	cout<<"Исходный список:"<<endl;
	list.print();

	// 3
	string key = "D0";
	int index = -1;
	for (int i=0; i < list.size; i++) {
		if (list.getData(i) == key) {
			index = i;
			break;
		}
	}
	if (index != -1) {
		list.del(index);
		cout<<"Элемент с ключом \""<<key<<"\" удалён."<<endl;
	}
	else {
		cout<<"Ключ \""<<key<<"\" не найден. Удаление не выполнено."<<endl;
	}

	// 4
	cout<<endl<<"Список после удаления:"<<endl;
	list.print();

	int K=3;
	string newElem[K] = { "ND0", "ND1", "ND2" };

	for (int i=0; i < K; i++) {
		list.add(newElem[i], 0);
		cout<<"Список после добавления \""<<newElem[i]<<"\":"<<endl;
		list.print();
	}

	// 5
	string fileName = "Lab11_Bi_data.txt";
	list.saveInFile(fileName);

	// 6
	list.deleteList();

	// 7
	cout<<endl<<"Список после уничтожения:"<<endl;
	list.print();

	// 8
	list.loadFromFileOverwriting(fileName);
	cout<<endl<<"Список восстановлен из файла:"<<endl;

	// 9
	list.print();

	// 10
	list.deleteList();
	cout<<"Список окончательно уничтожен."<<endl;

	return 0;
}