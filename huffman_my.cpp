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

	for (uint32_t i = 0; i < input_txt.length(); i++) 
	{
		temp_node = *node;                
		while (temp_node && (temp_node->position.sign != input_txt[i]))
			temp_node = temp_node->next; 
		if (!temp_node)                     
		{
			temp_node = new Node;             
			temp_node->next = *node;            
			temp_node->left = NULL;            
			temp_node->right = NULL;
			temp_node->position.sign = input_txt[i];
			temp_node->position.count = 0;
			*node = temp_node;               
		}
		temp_node->position.count++;                   
	}
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

int main()
{
	Node* tree;

	string input_txt;
	getline(cin, input_txt);

	create_list( &tree, input_txt );

	Node_free( &tree );
    std::cout << "Hello World!\n";
}
