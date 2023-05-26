#include <iostream>
#include <stdlib.h>
using namespace std;

struct Person
{ 
	string surname;
	string name;
	string patronumic;
	int PasportID;
};

struct Node
{
	Person info;
	Node* left;
	Node* right;
};

struct Tree
{
	Node* root;
	int count;
};

int menu(void);
void Create(Tree*&);
Person CinPerson(void);
void PushPerson(Node*&, const Person);
void ViewTree(const Node* const);
void SearchId(const Node* const, const int);
Node* PopPerson(Tree* ,Node*, const int);
void DelAll(const Node*);
int LabTask(const Node*, int);
int CountList(const Node* const, int);
Node* ListsFind( Node* , Node*& , int);
void Swap(Node*& arr, int i);
void ShakerSort(Node*& arr, int size);


int main(void)
{
	Tree* tree = NULL;
	bool work = true;
	bool CheckCreation = false;
	int FirstTime = 0;
	while (work)
	{
		switch (menu())
		{
		case 1:
		{
			system("cls");
			Create(tree);
			CheckCreation = true;
			break;
		}
		case 2:
		{
			system("cls");
			if (!CheckCreation) 
			{
				system("cls");
				printf("Create the Tree. Choose Menu-1\n");
				system("pause");
				break;
			}
			if (tree == NULL) cout << "No memory" << endl;
			else
			{
				if (FirstTime == 0)
				{
					cout << "Entering 5 elems" << endl;
					FirstTime++;
					for (int i = 0; i < 5; i++)
					{
						PushPerson(tree->root, CinPerson());
						tree->count++;
					}
					
				}
				else
				{
					PushPerson(tree->root, CinPerson());
					tree->count++;
				}
			}
			system("pause");
			break;
		}
		case 3: 
		{
			system("cls");
			if (!CheckCreation) // если не создали очередь, то просит выбрать 1й пункт меню, только потом остальные
			{
				system("cls");
				printf("Create the Tree. Choose Menu-1\n");
				system("pause");
				break;
			}
			if (tree == NULL) cout << "No memory" << endl;
			else if (tree->count > 0)
			{
				cout << "The tree is\n";
				ViewTree(tree->root);
			}
			else cout << "The tree is empty\n";
			system("\npause");
			break;
		}
		case 4:
		{
			system("cls");
			if (!CheckCreation) // если не создали очередь, то просит выбрать 1й пункт меню, только потом остальные
			{
				system("cls");
				printf("Create the Tree. Choose Menu-1\n");
				system("pause");
				break;
			}
			if (tree == NULL) cout << "No memory" << endl;
			else if (tree->count == 0) cout << "The tree is empty" << endl;
			else
			{
				cout << "Enter a passport ID to find the person: ";
				int id;
				cin >> id;
				SearchId(tree->root, id);
			}
			system("\npause");
			break;
		}
		case 5:
		{
			system("cls");
			if (!CheckCreation) // если не создали очередь, то просит выбрать 1й пункт меню, только потом остальные
			{
				system("cls");
				printf("Create the Tree. Choose Menu-1\n");
				system("pause");
				break;
			}
			if (tree == NULL) cout << "No memory" << endl;
			else if (tree->count > 0)
			{
				cout << "Enter an ID to Pop the person: ";
				int id;
				cin >> id;
				tree->root = PopPerson(tree, tree->root, id);
			}
			else cout << "The tree is empty" << endl;
			system("pause");
			break;
		}
		case 6:
		{
			system("cls");
			if (!CheckCreation) // если не создали очередь, то просит выбрать 1й пункт меню, только потом остальные
			{
				system("cls");
				printf("Create the Tree. Choose Menu-1\n");
				system("pause");
				break;
			}
			if (tree == NULL) cout << "No memory" << endl;
			else if (tree->count > 0)
			{
				int num = 0;
				num = LabTask(tree->root, num);
				cout << "Num of ancestors with one leaf: " << num << endl;
			}
			else cout << "The tree is empty" << endl;
			system("pause");
			break;
		}
		case 7:
		{
			system("cls");
			if (!CheckCreation) // если не создали очередь, то просит выбрать 1й пункт меню, только потом остальные
			{
				system("cls");
				printf("Create the Tree. Choose Menu-1\n");
				system("pause");
				break;
			}
			if (tree == NULL) cout << "No memory" << endl;
			else if (tree->count > 0)
			{
				int Lists = 0;
				Lists = CountList(tree->root, Lists);
				Node** arr = (Node**)malloc(Lists * sizeof(Node));
				int schet = 0;
				ListsFind(tree->root, *arr, schet);
				ShakerSort(*arr, Lists);
				for (int i = 0; i < Lists; i++)
				{
					cout << arr[i]->info.name << endl;
					cout << arr[i]->info.PasportID << endl;
					cout << arr[i]->info.patronumic << endl;
					cout << arr[i]->info.surname << endl;
					printf("\n");
				}
				system("pause");
			}
			else cout << "The tree is empty" << endl;
			system("pause");
			break;
		}
		case 8:
		{
			system("cls");
			if (tree != NULL) DelAll(tree->root);
			work = false;
			break;
		}
		default:
			system("cls");
			cout << "ERROR" << endl;
			system("pause");
			break;
		}
	}
}

// Меню
int menu(void)
{
	int num;
	system("cls");
	cout << "  -- MENU --  " << endl;
	cout << "1. Create the tree" << endl;
	cout << "2. Push an elem" << endl;
	cout << "3. The view of the tree" << endl;
	cout << "4. Find an elem" << endl;
	cout << "5. Pop the person by ID" << endl;
	cout << "6. Count of nodes with 1 leaf(LabTask)" << endl;
	cout << "7. Dopoln" << endl;
	cout << "8. Exit" << endl;
	cout << "\t\tYour choice: ";
	for (;;) // Проверка на ввод числа из меню
	{
		if (std::cin >> num && std::cin.good()) // Если было что-то введено и ввод - число
			return num; // Оно записывается
		else { // Иначе
			std::cout << "Choose 1-7." << std::endl;
			std::cin.clear(); std::cin.ignore(100, '\n'); // очищается поток ввода и просит ввести новое
		}
	}
}

// Создание дерева
void Create(Tree*& tree)
{
	tree = new Tree;
	tree->root = NULL;
	tree->count = 0;
}

// Ввод данных человека
Person CinPerson(void)
{
	Person person;
	cout << "Enter you surname, name, patronymic: ";
	cin >> person.surname >> person.name >> person.patronumic;
	cout << endl << "Enter you passport ID: ";
	cin >> person.PasportID;
	return person;
}

// Добавление элемента
void PushPerson(Node*& newElem, const Person person)
{
	if (newElem != NULL)
	{
		person.PasportID > newElem->info.PasportID ? PushPerson(newElem->right, person) : PushPerson(newElem->left, person);
	}
	else
	{
		newElem = new Node;
		newElem->left = NULL;
		newElem->right = NULL;
		newElem->info = person;
	}
}

// Вывести дерево
void ViewTree(const Node* const tree)
{
	if (tree != NULL)
	{
		ViewTree(tree->left);
		cout << tree->info.surname << " " << tree->info.name << " " << tree->info.patronumic << endl;
		cout << "Passport ID: " << tree->info.PasportID << "\n\n";
		ViewTree(tree->right);
	}
	else return;
}

// Поиск по айди
void SearchId(const Node* const tree, const int id)
{
	bool flag = false;
	if (tree != NULL)
	{
		if (id == tree->info.PasportID)
		{
			cout << tree->info.surname << " " << tree->info.name << " " << tree->info.patronumic << endl;
			cout << "Passport ID: " << tree->info.PasportID << "\n\n";
			flag = true;
		}
		else
		{
			id > tree->info.PasportID ? SearchId(tree->right, id) : SearchId(tree->left, id);
		}
	}
	else if (!flag)
		cout << "No such ID\n";
	else return;
}

// Удаление по айди
Node* PopPerson(Tree* tree, Node* root, const int id)
{
	Node* Del, * PrevDel, * RightNode, * PrevRight;
	Del = root;
	PrevDel = NULL;
	while (Del != NULL && Del->info.PasportID != id)
	{
		PrevDel = Del;
		if (id > Del->info.PasportID)
			Del = Del->right;
		else
			Del = Del->left;
	}
	// Нет этого id
	if (Del == NULL)
	{
		cout << "No such id in the Tree" << endl;
		system("pause");
		return root;
	}
	// Нет правого поддерева
	if (Del->right == NULL)
		RightNode = Del->left;
	else
	{
		// Нет левого поддерева
		if (Del->left == NULL)
			RightNode = Del->right;
		else
		{
			// Ищем самый правый элемент в левом поддереве
			PrevRight = Del;
			RightNode = Del->left;
			while (RightNode->right != NULL)
			{
				PrevRight = RightNode;
				RightNode = RightNode->right;
			}
			// Нашли элемент для замены RightNode и его родителя PrevRight
			if (PrevRight == Del) RightNode->right = Del->right;
			else
			{
				RightNode->right = Del->right;
				PrevRight->right = RightNode->left;
				RightNode->left = PrevRight;
			}
		}
	}
	if (Del == root)
		root = RightNode; // Удаляя корень, заменяем его на RightNode
	// Поддерево RightNode присоеденяем к родителю удаляемого узла
	else if (Del->info.PasportID < PrevDel->info.PasportID) PrevDel->left = RightNode; // на левую ветвь
	else PrevDel->right = RightNode; // на правую
	delete Del;
	tree->count--;
	return root;
}
//							Before Pop 12     (0 anc w 1 l)
//							12 (Del)
//						  /	   \
//						 6      14 
//							   /  \
//							 13    20
//						


//                         After Pop 12       (1 anc w 1 l)
//							6 
//						  /	  \
//					   NULL     14
//							   /  \
//						     13    20
//						

// Удалить и очистить память
void DelAll(const Node* a)
{
	if (a == NULL)
	{
		return;
	}
	else
	{
		DelAll(a->left);
		DelAll(a->right);
		delete a;
		return;
	}
}

// Количество узлов имеющих одного потомка
int LabTask(const Node* a, int count)
{
	if (a != NULL)
	{
		count = LabTask(a->left, count);
		if (((a->left != NULL) && (a->right == NULL)) || ((a->left == NULL) && (a->right != NULL)))
			count++;
		count = LabTask(a->right, count);
	}
	return count;
}

int CountList(const Node* const a, int count)
{
	if (a != NULL)
	{
		count = CountList(a->left, count);
		if ((a->left == NULL) && (a->right == NULL)) 
			count++;
		count = CountList(a->right, count);
	}
	return count;
}

Node* ListsFind( Node*  a, Node*& mass, int counter)
{
	if (a != NULL)
	{
		ListsFind(a->left, mass, counter);
		if ((a->left == NULL) && (a->right == NULL))
		{
			mass[counter].info = a->info;
			counter++;
		}
		ListsFind(a->right, mass, counter);
	}
	return mass;
}

void Swap(Node*& arr, int i)
{
	int buff; // пузырек, временная переменная
	buff = arr[i].info.PasportID;  // в пузырек кладется X значение
	arr[i] = arr[i - 1]; // на место X значения кладется Y
	arr[i - 1].info.PasportID = buff; // на место Y кладется X
	// в итоге X и Y поменялись местами
	// сделать arr[i] = arr[i-1] 
	//         arr[i-1] = arr[i] НЕЛЬЗЯ 
	// тк при первом действии мы в двух местах будем иметь одинаковое значение
}

//ф-ция "шейкер"-сортировки // улучшение для buble sort - движение с двух сторон за одну итерацию
void ShakerSort(Node*& arr, int size)
{
	int leftMark = 1; // тк сравнивается [i-1] и [i] 
	int rightMark = size - 1; // тк массив начинается с 0
	while (leftMark <= rightMark) // цикл выполняется до соединения в центре
	{
		for (int i = rightMark; i >= leftMark; i--) // движение справа налево
			if (arr[i - 1].info.PasportID > arr[i].info.PasportID) Swap(arr, i); // если условие выполняется => элементы меняются местами
		leftMark++; // границы с каждой итерацией сближаются от краев к центру для увеличения скорости


		for (int i = leftMark; i <= rightMark; i++) // все то же самое но слева направо 
			if (arr[i - 1].info.PasportID > arr[i].info.PasportID) Swap(arr, i);
		rightMark--;
	}
}