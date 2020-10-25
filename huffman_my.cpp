#include <iostream>
#include <string>
#include <stdint.h>

using namespace std;

typedef struct {
	char sign;
	uint16_t count;
}Position;

typedef struct node{
	Position position;
	struct node* next;
	struct node* left;
	struct node* right;
}Node;


//create list that stores signs and qty
void create_list(Node** node, string input_txt) {
	*node = NULL;		//init first node, set it's address to nothing
	Node* temp_node;
	uint32_t length = input_txt.length();
	uint8_t new_sign_flag = 1;
	
	for (uint32_t i = 0; i < length; i++) {		//iterate through all sings
		temp_node = *node;

		new_sign_flag = 1;			//set the flag that we have new sign
		while (temp_node != NULL) {		//iterate through all existing nodes
			if (temp_node->position.sign == input_txt[i]) {		//if sign alread exist in some node -> clear flag
				new_sign_flag = 0;		
				break;
			}
			temp_node = temp_node->next;	//if sign does not exist in node check next node
		}

		if ( new_sign_flag ) {	//if new node to create (new sign found)
			new_sign_flag = 0;
			temp_node = new Node;	//new node
			temp_node->next = NULL;
			temp_node->left = NULL;
			temp_node->right = NULL;
			temp_node->position.sign = input_txt[i];
			temp_node->position.count = 0;
			if (i == 0)
				*node = temp_node;	//set first node
			else {
				Node* find;
				find = *node;
				while (find->next != NULL)		//find end
					find = find->next;
				find->next = temp_node;
			}
		}
		temp_node->position.count++;
	}
}

void sort_list(Node** node) {
	Node* temp_node;
	temp_node = *node;
	bool t;
	char temp_sign;
	uint32_t temp_count;
	do                              // Listę sortujemy rosnąco względem count
	{
		t = true;                     // Zakładamy posortowanie listy
		temp_node = *node;                     // Sortujemy od pierwszego elementu
		while (temp_node->next)
		{
			if (temp_node->position.count > temp_node->next->position.count)
			{
				temp_sign = temp_node->position.sign;               // Wymieniamy zawartość dwóch kolejnych elementów
				temp_node->position.sign = temp_node->next->position.sign;
				temp_node->next->position.sign = temp_sign;
				temp_count = temp_node->position.count;
				temp_node->position.count = temp_node->next->position.count;
				temp_node->next->position.count = temp_count;
				t = false;                // Sygnalizujemy nieposortowanie listy
			}
			temp_node = temp_node->next;                // Przechodzimy do następnego elementu
		}
	} while (!t);
}
void Node_free(Node **list)
{
	Node* wsk;
	while ( *list != NULL )
	{
		wsk = (*list)->next;
		delete *list;
		*list = wsk;
	}
}

void generate_tree(Node** node) {
	Node* node1, * node2, * temp_node, *begin_node, *temp_begin_node;

	node1 = *node;	//init
	node2 = node1->next;	

	while ( node2 != NULL) {
		//*node = node2->next;

		begin_node = node2->next; //set first node as first from the list
		//create new node
		temp_node = new Node;
		temp_node->left = node1;
		temp_node->right = node2;
		temp_node->position.count = node1->position.count + node2->position.count;
		
		if (!begin_node || temp_node->position.count <= begin_node->position.count) {	//if the counter is smaller we add the node at the beginning
			temp_node->next = begin_node;	//set next node
			begin_node = temp_node;			//set created node as first
			temp_begin_node = begin_node;
		}
		else {
			temp_begin_node = begin_node;
			while (begin_node->position.count < temp_node->position.count && begin_node->next != NULL)
				begin_node = begin_node->next;
			temp_node->next = begin_node->next;
			begin_node->next = temp_node;
		}
		node1 = temp_begin_node;
		node2 = temp_begin_node->next;
		if (temp_begin_node->next == NULL)	//set main pointer as head of the tree
			*node = temp_begin_node;
	}
}

bool CodeT(char c, Node* p, string b){
	if (!p->left)
	{
		if (c != p->position.sign) return false;
		else
		{
			cout << b;
			return true;
		}
	}
	else return CodeT(c, p->left, b + "0") || CodeT(c, p->right, b + "1");
}

void Compress(Node* root, string input_txt){
	uint32_t i;

	for (i = 0; i < input_txt.length(); i++)  // Kodujemy poszczególne znaki
		CodeT(input_txt[i], root, "");
}
/*
void Free_tree(Node** node) {
	Node* temp_node = *node;
	if (*node)
	{
		Free_tree(&temp_node->left);          // usuwamy lewe poddrzewo
		Free_tree(&temp_node->right);         // usuwamy prawe poddrzewo
		delete temp_node;                     // usuwamy sam węzeł
	}
}
*/

int main()
{
	Node* tree;

	string input_txt;
	getline(cin, input_txt);

	create_list( &tree, input_txt );

	sort_list( &tree );

	generate_tree(&tree);

	Compress(tree, input_txt);
	//Node_free( &tree );
	//Free_tree(&tree);
    std::cout << "Hello World!\n";
}
