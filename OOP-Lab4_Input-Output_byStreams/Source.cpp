#include "iostream"
#include "list"
#include "cstring"
#include "iomanip"
#include "fstream"

#define ANSI_COLOR_BLUE "\033[34m"
#define ANSI_COLOR_RESET "\033[0m"

using namespace std;

ostream& outsetup(ostream& ofs);

class Node {
private:
	Node* ptr_next;
	Node* ptr_prev;
	int data;
	friend class DoublyLinkedList;
};

class DoublyLinkedList {
private:
	Node* root_head;
	Node* root_tail;
	int n_count;
public:
	DoublyLinkedList();
	DoublyLinkedList(const DoublyLinkedList&);
	void PushBack(int);
	Node* Next(Node*);
	Node* Prev(Node*);
	void Show();
	void Clear();
	bool isFind(int);
	void DeleteSelectNode(int);
	bool isEmpty() { return this->root_head == NULL && this->root_tail == NULL; }
	int Lenght() { return this->n_count; }
	int GetValue(Node* ptr) { return ptr->data; }
	~DoublyLinkedList() { Clear(); }
};

/**
 * @brief Конструктор за замовченням двозв'язного списку
*/
DoublyLinkedList::DoublyLinkedList() {

	root_head = NULL;
	root_tail = NULL;
	n_count = 0;
}

/**
 * @brief Конструктор копії
 * @param list Об'єкт, з якого потрібно створити копію
*/
DoublyLinkedList::DoublyLinkedList(const DoublyLinkedList& list) {

	n_count = list.n_count;
	if (list.n_count == 0) {
		root_head = list.root_head;
		root_tail = list.root_tail;
	}
	else {
		Node* p = list.root_head;
		do {
			Node* node = new Node();
			node->data = p->data;
			if (isEmpty()) {
				root_head = node;
				root_tail = node;
				node->ptr_next = NULL;
				node->ptr_prev = NULL;
			}
			else {
				Node* p = root_tail;
				p->ptr_next = node;
				node->ptr_prev = root_tail;
				node->ptr_next = NULL;
				root_tail = node;
			}
			p = p->ptr_next;
		} while (p != NULL);
	}
}

/**
 * @brief Метод, який створбє вузол і заносить його в кінець списку
 * @param data Дані для внесення до списку
*/
void DoublyLinkedList::PushBack(int data) {

	Node* new_node = new Node();
	new_node->data = data;
	n_count++;

	if (this->isEmpty()) {
		this->root_head = new_node;
		this->root_tail = new_node;
		new_node->ptr_next = NULL;
		new_node->ptr_prev = NULL;
	}
	else {
		Node* p = this->root_tail;
		p->ptr_next = new_node;
		new_node->ptr_prev = this->root_tail;
		new_node->ptr_next = NULL;
		this->root_tail = new_node;
	}
}

/**
 * @brief Метод, яеий реалізує перехід на наступний вузол списку
 * @param node Поточний вузол списку
 * @return Наступного вузла списку
*/
Node* DoublyLinkedList::Next(Node* node) {

	if (node == NULL) {
		return NULL;
	}
	if (this->root_tail == node) {
		return NULL;
	}

	return node->ptr_next;
}

/**
 * @brief Метод, який реалізує перехід на попередній вузол списку
 * @param node Поточний вузол списку
 * @return Попередній вузол списку
*/
Node* DoublyLinkedList::Prev(Node* node) {

	if (node == NULL) {
		return NULL;
	}
	if (this->root_head == node) {
		return NULL;
	}

	return node->ptr_prev;
}

/**
 * @brief Метод, який реалізує пошук елементу в списку
 * @param x Елемент для пошуку
 * @return True, якщо елемент було знайдено
*/
bool DoublyLinkedList::isFind(int x) {

	Node* p = this->root_tail;
	if (p == NULL) {
		return false;
	}
	while (p != NULL) {
		if (p->data == x) return true;
		p = this->Prev(p);
	}
	return false;
}

/**
 * @brief Метод, який відображає значення, що містяться в списку
*/
void DoublyLinkedList::Show() {

	Node* p = this->root_head;

	while (p != NULL) {
		cout << p->data << " ";
		p = this->Next(p);
	} cout << endl;
}

/**
 * @brief Метод, який повністю очищає список
*/
void DoublyLinkedList::Clear() {

	Node* p = this->root_tail;

	if (p == NULL) {
		return;
	}
	do
	{
		Node* d = p;
		p = this->Prev(p);
		delete d;
		this->n_count--;
	} while (p != NULL);
	this->root_head = NULL;
	this->root_tail = NULL;
}

/**
 * @brief Метод, який видаляє обраний вузол
 * @param n Обраний вузол
*/
void DoublyLinkedList::DeleteSelectNode(int n) {

	if (n < this->n_count && n >= 0) {
		Node* c = this->root_head;
		if (c == NULL) return;
		while (n != 0) {
			c = this->Next(c);
			n--;
		}
		Node* prev = this->Prev(c);
		Node* next = this->Next(c);
		if (c == this->root_head && c == this->root_tail) {
			this->root_head = NULL;
			this->root_tail = NULL;
		}
		else if (c == this->root_head) {
			this->root_head = next;
			next->ptr_prev = NULL;
		}
		else if (c == this->root_tail) {
			this->root_tail = prev;
			prev->ptr_next = NULL;
		}
		else {
			prev->ptr_next = next;
			next->ptr_prev = prev;
		}
		delete c;
		this->n_count--;
	}
	else cerr << "Error!The requested NODE was not found !" << endl;
}


class VectorBit {
private:
	unsigned char* mas;
	int n_bit;
	int size;

	static int countVector;
	//list<int> bit_changed;
	DoublyLinkedList bit_changedlist;
public:
	VectorBit();
	VectorBit(int&);
	VectorBit(const char*);
	VectorBit(const VectorBit&);
	void SetVector();
	void Set0(int);
	void Set1(int);
	void Flip(int);
	void Show();
	void WriteFile(const int&);
	int SizeFile(const string&);
	void ReadFile(const int&);
	void WriteBinaryFile(const int&);
	void ReadBinaryFile(const int& n);
	void ClearFile(const string& filename);
	pair<int, int> Size();
	~VectorBit();
};

int VectorBit::countVector = 0;

/**
 * @brief Конструктор за замовченням
*/
VectorBit::VectorBit() {

	n_bit = 0;
	mas = nullptr;
	countVector++;
}

/**
 * @brief Параметричний конструктор
 * @param bits Кількість бітів для створення бітового вектора
*/
VectorBit::VectorBit(int& bits) {

	n_bit = bits;
	size = n_bit / 8;
	if (n_bit % 8 != 0) size++;
	mas = new unsigned char[size];
	countVector++;
}

/**
 * @brief Конструктор для ініціалізації за допомогою значення наданого символьним рядком
 * @param str
*/
VectorBit::VectorBit(const char* str) {

	n_bit = strlen(str);
	size = n_bit / 8;
	if (n_bit % 8 != 0) size++;
	mas = new unsigned char[size];

	for (int i = 0; i < n_bit; i++) {
		if (str[i] == '1') mas[i / 8] |= (1 << (i % 8));
		else mas[i / 8] &= ~(1 << (i % 8));
	}
	countVector++;
}

/**
 * @brief Конструктор копії
 * @param obj Об'єкт, з якого потрібно створити копію
*/
VectorBit::VectorBit(const VectorBit& obj) {

	n_bit = obj.n_bit;
	size = n_bit / 8;
	if (n_bit % 8 != 0) size++;
	mas = new unsigned char[size];
	for (int i = 0; i < size; i++) {
		mas[i] = obj.mas[i];
	}
	//bit_changed = obj.bit_changed;
	bit_changedlist = obj.bit_changedlist;
	countVector++;
}

/**
 * @brief Метод-сеттер, заповнення бітового вектора значеннями
*/
void VectorBit::SetVector() {

	/*if (!this->bit_changed.empty()) {
		this->bit_changed.clear();
	}*/
	if (!this->bit_changedlist.isEmpty()) {
		this->bit_changedlist.Clear();
	}
	if (this->n_bit == 0 && this->mas == nullptr) {
		this->n_bit = (rand() % 65) + 1;
		this->size = this->n_bit / 8;
		if (this->n_bit % 8 != 0) this->size++;
		this->mas = new unsigned char[this->size];
	}

	for (int i = 0; i < this->n_bit; i++) {
		int x = rand() % 2;
		if (x == 0) this->mas[i / 8] &= ~(1 << (i % 8));
		else if (x == 1) this->mas[i / 8] |= (1 << (i % 8));
	}
}

/**
 * @brief Метод, який використовується для встановлення біта з заданим номером в 0
 * @param x Місце розташування біта в бітовому векторі
*/
void VectorBit::Set0(int x) {

	if (x != 0 && x <= this->n_bit) {
		//this->bit_changed.push_back(x);
		this->bit_changedlist.PushBack(x);
		x--;
		this->mas[x / 8] &= ~(1 << (x % 8));
	}
	else cerr << "Error! The requested bit was not found " << endl;
}

/**
 * @brief Метод, який використовується для встановлення біта з заданим номером в 1
 * @param x Місце розташування біта в бітовому векторі
*/
void VectorBit::Set1(int x) {

	if (x != 0 && x <= this->n_bit) {
		//this->bit_changed.push_back(x);
		this->bit_changedlist.PushBack(x);
		x--;
		this->mas[x / 8] |= (1 << (x % 8));
	}
	else cerr << "Error! The requested bit was not found " << endl;
}

/**
 * @brief Метод, який використовується для інвертування біта з наданим номером
 * @param x Місце розташування біта в бітовому векторі
*/
void VectorBit::Flip(int x) {

	if (x != 0 && x <= this->n_bit) {
		//this->bit_changed.push_back(x);
		this->bit_changedlist.PushBack(x);
		x--;
		this->mas[x / 8] ^= (1 << (x % 8));
	}
	else cerr << "Error! The requested bit was not found " << endl;
}

/**
 * @brief Метод, який використовується для виведення бітового вектора на екран
*/
void VectorBit::Show() {
	
	pair<int, int> size = this->Size();
	cout << outsetup << size.first << " bites or " << size.second << " bytes" << " { ";
	for (int i = 0; i < this->n_bit; i++) {
		//list<int>::iterator it = find(this->bit_changed.begin(), this->bit_changed.end(), i + 1);
		cout.unsetf(ios::showpos);
		if (this->bit_changedlist.isFind(i + 1)) cout << ANSI_COLOR_BLUE << ((this->mas[i / 8] >> (i % 8)) & 1) << ANSI_COLOR_RESET;
		else cout << ((this->mas[i / 8] >> (i % 8)) & 1);
		if ((i + 1) % 8 == 0) cout << "|";
		else if ((i + 1) % 4 == 0) cout << " ";
	}
	cout << " }" << endl;
}

/**
 * @brief Метод, який повертає розмір бітового вектора у бітах
 * @return Розмір бітового вектора у бітах та кількість байтів, використанні для зберігання цього вектора
*/
pair<int, int> VectorBit::Size() {

	return make_pair(this->n_bit, this->size);
}

/**
 * @brief Деструктор
*/
VectorBit::~VectorBit() {

	cout << "\nThe VectorBit #" << countVector << " was destroyed" << endl;
	delete[] mas;
	countVector--;
}

/**
 * @brief Метод, який реалізує очіщення файлу
 * @param filename Ім'я файлу
*/
void VectorBit::ClearFile(const string& filename) {

	ofstream fclear;
	fclear.open(filename, ios::trunc);
	fclear.close();
}

/**
 * @brief Метод, який реалізує запис даних до текстового файлу
 * @param n Кількість векторів для запису 
*/
void VectorBit::WriteFile(const int& n) {

	ofstream fout;
	fout.open("data.txt", ios::out | ios::app);

	if (!fout) {
		cerr << "Cannot open file! " << endl;
	}
	if (!fout.is_open()) {
		cerr << "File is not opened! " << endl;
	}

	for (int i = 0; i < n; i++) {
		fout << this[i].n_bit << " ";
		for (int j = 0; j < this[i].n_bit; j++) {
			fout << ((this[i].mas[j / 8] >> (j % 8)) & 1);
		}
		fout << '\n';
	}
	
	if (fout.fail()) {
		cerr << "File write operation failed" << endl;
	}
	fout.close();
}

/**
 * @brief Метод, який реалізує запис даних до бінарного файлу
 * @param n Кількість векторів для запису 
*/
void VectorBit::WriteBinaryFile(const int& n) {

	ofstream fout;
	fout.open("data.bin", ios::out | ios::binary | ios::app);

	if (!fout) {
		cerr << "Cannot open file! " << endl;
	}
	if (!fout.is_open()) {
		cerr << "File is not opened! " << endl;
	}
	
	for (int i = 0; i < n; i++) {
		fout.write(reinterpret_cast<const char*>(&this[i].n_bit), sizeof(this[i].n_bit));
		fout.write(reinterpret_cast<const char*>(this[i].mas), this[i].size * sizeof(char));
	}
	
	if (fout.fail()) {
		cerr << "File write operation failed" << endl;
	}
	fout.close();
}

/**
 * @brief Метод, який знаходить розмір досліджуваного файлу
 * @param filename Ім'я файлу
 * @return Кількість векторів для зчитування
*/
int VectorBit::SizeFile(const string& filename) {

	int count = 0;
	ifstream famount;
	if (filename[filename.length() - 3] == 't') famount.open(filename, ios::in);
	if (filename[filename.length() - 3] == 'b') famount.open(filename, ios::in | ios::binary);
	if (!famount) {
		cerr << "Cannot open file! " << endl;
	}
	else {
		if (filename[filename.length() - 3] == 't') {
			char str;
			while (famount.get(str)) {
				if (str == '\n') {
					count++;
				}
			}
		}
		else if (filename[filename.length() - 3] == 'b') {
			int vectorsize, vectorsize_byte;
			while (famount.read(reinterpret_cast<char*>(&vectorsize), sizeof(vectorsize))) {
				vectorsize_byte = vectorsize / 8;
				if (vectorsize % 8 != 0) vectorsize_byte++;
				unsigned char* temp = new unsigned char[vectorsize_byte];
				famount.read(reinterpret_cast<char*>(temp), vectorsize_byte * sizeof(char));
				delete[] temp;
				count++;
			}
		}		
		if (famount.fail() && !famount.eof()) {
			cerr << "File read operation failed (find size)" << endl;
		}
		if (famount.bad()) {
			cerr << "Critical error of read operation" << endl;
		}
	}
	famount.close();

	return count;
}

/**
 * @brief Метод, який реалізує зчитування даних з текстового файлу
 * @param n Кількість векторів для зчитування
*/
void VectorBit::ReadFile(const int& n) {

	ifstream fin;
	fin.open("data.txt", ios::in);

	if (!fin) {
		cerr << "Cannot open file! " << endl;
	}
	if (!fin.is_open()) {
		cerr << "File is not opened! " << endl;
	}
	else {
		for (int k = 0; k < n; k++) {
			if (this[k].mas != nullptr) {
				delete[] this[k].mas;
			}
			fin >> this[k].n_bit;
			this[k].size = this[k].n_bit / 8;
			if (n_bit % 8 != 0) this[k].size++;
			this[k].mas = new unsigned char[this[k].size];
			char str;
			do { fin.get(str); } while (str != ' ');
			for (int i = 0; i < this[k].n_bit; i++) {
				fin.get(str);
				if (str == '1') this[k].mas[i / 8] |= (1 << (i % 8));
				else if (str == '0') this[k].mas[i / 8] &= ~(1 << (i % 8));
			}
			do { fin.get(str); } while (str != '\n');
			if (!fin.good()) {
				cerr << "File read operation failed" << endl;
			}
			if (fin.fail() && !fin.eof()) {
				cerr << "File read operation failed" << endl;
			}
			if (fin.bad()) {
				cerr << "Critical error of read operation" << endl;
			}
		}		
	}
	fin.close();
}

/**
 * @brief Метод, який реалізує зчитування даних з бінарного файлу
 * @param n Кількість векторів для зчитування
*/
void VectorBit::ReadBinaryFile(const int& n) {

	ifstream fin;
	fin.open("data.bin", ios::in | ios::binary);

	if (!fin) {
		cerr << "Cannot open file! " << endl;
	}
	if (!fin.is_open()) {
		cerr << "File is not opened! " << endl;
	}
	else {
		for (int i = 0; i < n; i++) {
			if (this[i].mas != nullptr) {
				delete[] this[i].mas;
			}
			fin.read(reinterpret_cast<char*>(&this[i].n_bit), sizeof(this[i].n_bit));			
			this[i].size = this[i].n_bit / 8;
			if (this[i].n_bit % 8 != 0) this[i].size++;
			this[i].mas = new unsigned char[this[i].size];
			//cout << this[i].n_bit << ':' << this[i].size << endl;
			fin.read(reinterpret_cast<char*>(this[i].mas), this[i].size * sizeof(char));
		}
		
		if (!fin.good()) {
			cerr << "File read operation failed" << endl;
		}
		if (fin.fail() && !fin.eof()) {
			cerr << "File read operation failed" << endl;
		}
		if (fin.bad()) {
			cerr << "Critical error of read operation" << endl;
		}
	}
	fin.close();
}

/**
 * @brief Маніпулятивна функція для потоку введення
 * @param ifs Потоковий об'єкт введення
 * @return Потоковий об'єкт
*/
istream& insetup(istream& ifs) {

	ifs.setf(ios::skipws);

	return ifs;
}

/**
 * @brief Маніпулятивна функція для потоку виведення
 * @param ofs Потоковий об'єкт виведення
 * @return Потоковий об'єкт
*/
ostream& outsetup(ostream& ofs) {

	ofs.fill('$');
	ofs.setf(ios::showpos | ios::scientific | ios::uppercase);
	ofs << setw(5) << left;

	return ofs;
}

/**
 * @brief Функція, яка перевіряє правильність введення даних користувачем
 * @param x Данні для перевірки
*/
void CheckData(int& x) {

	cin.ignore(666, '\n');
	while (true) {
		if (cin.fail()) {
			cin.clear();
			cin.ignore(666, '\n');
			cerr << "You enter wrong data! Please enter correct data: \n";
			cout << "Enter lenght of bit vector: ";
			cin >> insetup >> x;
			cin.ignore(666, '\n');
		}
		else break;
	}
}

int main() {
	srand(time(0));
	int n = 0;
	int n_file = 0, n_filebin = 0;
	int work = 1;	
	VectorBit* vector = nullptr;	

	while (work != 0) {
		switch (work) {
		case 1:	
			if (vector != nullptr) delete[] vector;
			cout << "\nEnter amount of VectorBit: ";
			do {
				cin >> insetup >> n;
				CheckData(n);
				if (n < 1) cerr << "Min amount of VectorBit == 1! Re-entry: ";
			} while (n < 1);
			vector = new VectorBit[n];
			cout << "\nGenerate vectors..." << endl;
			for (int i = 0; i < n; i++) {
				vector[i].SetVector();
				vector[i].Show();
			}			
			break;
		case 2:
			if (vector != nullptr) { cout << "\nWriting to file .txt..." << endl; vector->WriteFile(n); }
			if (vector != nullptr) { cout << "\nWriting to file .bin..." << endl; vector->WriteBinaryFile(n); }
			break;
		case 3:
			cout << "\nReading from file .txt..." << endl;
			n_file = vector->SizeFile("data.txt");
			if (n_file == 0) cout << "File is empty!" << endl;
			else {
				if (vector != nullptr && n != n_file) { delete[] vector; n = n_file; vector = new VectorBit[n]; }
				vector->ReadFile(n); cout << endl;
				for (int i = 0; i < n; i++) { vector[i].Show(); }
			}
			cout << setw(80) << setfill('-') << " " << endl;
			cout << "\nReading from file .bin..." << endl;
			n_filebin = vector->SizeFile("data.bin");
			if (n_filebin == 0) cout << "File is empty!" << endl;
			else {
				if (vector != nullptr && n != n_filebin) { delete[] vector; n = n_filebin; vector = new VectorBit[n]; }
				vector->ReadBinaryFile(n); cout << endl;
				for (int i = 0; i < n; i++) { vector[i].Show(); }
			}			 
			break;
		case 4:
			if (vector != nullptr) { cout << "File cleared\n"; vector->ClearFile("data.txt"); vector->ClearFile("data.bin"); }
			break;
		case 5:
			if (vector != nullptr) for (int i = 0; i < n; i++) { vector[i].Show(); }
			break;
		default:
			work = 0;
			break;
		}
		cout << "\n__________Menu of action__________" << endl;
		cout << "Enter 1 - Generate new vectors"<< endl;
		cout << "Enter 2 - Writing to file" << endl;
		cout << "Enter 3 - Reading from file" << endl;
		cout << "Enter 4 - Clear file" << endl;
		cout << "Enter 5 - Show current vectors" << endl;
		cout << "Enter 0 - Exit" << endl;
		cin >> insetup >> work;
		CheckData(work);
	}

	delete[] vector;
	return 0;
}