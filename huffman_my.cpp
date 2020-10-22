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
	int a = 0;
	/*
	for (uint32_t i = 0; i < input_txt.length(); i++) 
	{
		temp_node = *node;                
		while (temp_node != NULL && (temp_node->position.sign != input_txt[i]) ) {
				temp_node = temp_node->next;
		}
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
	*/
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
