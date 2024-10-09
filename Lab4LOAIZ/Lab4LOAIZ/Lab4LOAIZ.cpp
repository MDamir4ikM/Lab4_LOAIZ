#define _CRT_SECURE_NO_WARNIGS
#include <iostream>

struct Node {
	int data;
	struct Node* left;
	struct Node* right;
};

struct Node* root;

struct Node* CreateTree(struct Node* root, struct Node* r, int data)
{
	if (r == NULL)
	{
		r = (struct Node*)malloc(sizeof(struct Node));
		if (r == NULL)
		{
			printf("Ошибка выделения памяти");
			exit(0);
		}

		r->left = NULL;
		r->right = NULL;
		r->data = data;
		if (root == NULL) return r;

		if (data == root->data) //Проверяем, есть ли такой элемент 
		{
			std::cout << "Такой элемент уже есть" << std::endl;
			return root; //Если есть, то возвращаем указатель на корень
		} 

		if (data > root->data)	root->left = r;
		else root->right = r;
		return r;
	}

	if (data > r->data)
		CreateTree(r, r->left, data);
	else
		CreateTree(r, r->right, data);

	return root;
}

void print_tree(struct Node* r, int l)
{

	if (r == NULL)
	{
		return;
	}

	print_tree(r->right, l + 1);
	for (int i = 0; i < l; i++)
	{
		printf(" ");
	}

	printf("%d\n", r->data);
	print_tree(r->left, l + 1);
}

struct Node* find(struct Node* r, int data)
{
	if (r->data == data) return r;

	else if (r->data < data && r->left != NULL)
	{
		find(r->left, data);
	}
	else if (r->data > data && data && r->right != NULL)
	{
		find(r->right, data);
	}
	else
	{
		std::cout << "Не найден";
		return NULL;
	}
}

int fcount(struct Node* r, int data, int count)
{
	if (r == NULL) return count;
	if (r->data == data) count++;
	count = fcount(r->right, data, count);
	count = fcount(r->left, data, count);
	return count;
}

int main()
{
	setlocale(LC_ALL, "");
	int D, start = 1, co;
	struct Node* r = NULL;

	root = NULL;
	printf("-1 - окончание построения дерева\n");
	while (start)
	{
		printf("Введите число: ");
		scanf_s("%d", &D);
		if (D == -1)
		{
			printf("Построение дерева окончено\n\n");
			start = 0;
		}
		else
			root = CreateTree(root, root, D);

	}

	std::cout << "Хотите вывести дерево на экран:\n1 - да\n2 - нет\nОтвет: ";
	int otvet;
	std::cin >> otvet;
	if (otvet == 1)
	{
		print_tree(root, 0);
	}

	std::cout << "Хотите произвести подсчёт вхождения элемента:\n1 - да\n2 - нет\nОтвет: ";
	std::cin >> otvet;
	if (otvet == 1)
	{
		std::cout << "Введите элемент, количество вхождений которого хотите узнать: ";
		std::cin >> D;

		r = find(root, D);
		if (r != NULL)printf("Найденный элемент = %d ", r->data);

		co = fcount(root, D, 0);
		printf("Количество = %d ", co);
	}

	return 0;
}
