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

	else if (r->data < data && r->left != NULL) //идём вправо, если	текущее значение меньше
	{
		find(r->left, data);
	}
	else if (r->data > data && data && r->right != NULL) //идём влево, если текущее значение больше
	{
		find(r->right, data);
	}
	else
	{
		std::cout << "Не найден" << std::endl;
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

void reverse_order_traversal(struct Node* r) {
	if (r == NULL) {
		return;
	}

	// Сначала обходим правое поддерево
	reverse_order_traversal(r->right);

	// Затем обходим левое поддерево
	reverse_order_traversal(r->left);

	// Наконец, обрабатываем корень
	printf("%d ", r->data);
}

int main()
{
	setlocale(LC_ALL, "");
	int D, stare = 1, co;
	struct Node* r = NULL;

	root = NULL;
	printf("-1 - окончание построения дерева\n");
	while (stare)
	{
		printf("Введите число: ");
		scanf_s("%d", &D);
		if (D == -1)
		{
			printf("Построение дерева окончено\n\n");
			stare = 0;
		}
		else
			root = CreateTree(root, root, D);

	}

	printf("\nОбратный обход дерева:\n");
	reverse_order_traversal(root); // Вызов обратного обхода

	std::cout << std::endl;
	print_tree(root, 0);

	//std::cout << "Введите элемент, количество вхождений которого хотите узнать: ";
	//std::cin >> D;

	//r = find(root, D);
	//if (r != NULL)printf("Найденный элемент = %d ", r->data);

	//co = fcount(root, D, 0);
	//printf("Количество = %d ", co);

	return 0;
}
