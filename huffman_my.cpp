#include <iostream>
#include <string>
#include <stdint.h>
#include <fstream>

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

string output_str;

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
//delete list
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
//function to generate tree
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

bool schearch_tree(char c, Node* root, string b) {
	if( root != NULL ){
		schearch_tree(c, root->left, b+"0");
		if (root->position.sign == c) {
			cout << b;
			return true;
		}
		schearch_tree(c, root->right, b+"1");
		if (root->position.sign == c) {
			cout << b;
			return true;
		}
	}
}

void Compress(Node* root, string input_txt){
	for (uint32_t i = 0; i < input_txt.length(); i++) { 
		schearch_tree(input_txt[i], root, "");
		cout << " ";
	}
	cout << endl;
}

//function add to string the bits that represents particular sign
bool get_compress_bits(char c, Node* root, string b ) {
	if (root != NULL) {
		get_compress_bits(c, root->left, b + "0");
		if (root->position.sign == c) {
			//cout << b;
			output_str += b;
			return true;
		}
		get_compress_bits(c, root->right, b + "1");
		if (root->position.sign == c) {
			//cout << b;
			output_str += b;
			return true;
		}
	}
}
//store text bits in the string
void get_bits(Node* node, string input_txt) {
	string bytes;
	for (uint32_t i = 0; i < input_txt.length(); i++) {  // code particular sign and store it in string variable
		get_compress_bits(input_txt[i], node, "");
	}
}

//save compress file based on the given bits
void save_compress_file(string bits) {
	ofstream File_output;
	File_output.open("output.txt", ios::binary);

	uint8_t byte = 0;
	uint8_t temp = 0;
	uint8_t index = 0;

	for (uint32_t i = 0,j = 1; i < bits.length(); i++,j++) { //compress. add following bits to byte, and when byte is full - save

		index = j % 8;
		byte = byte << 1;
		if (bits[i] == '1') {
			temp = 1;
			byte |= temp;
		}
		if (index == 0) {
			File_output.write((char*)&byte, sizeof(byte));
			byte = 0;
		}
		if (i == (bits.length() - 1) && index) {	//if last sign
			for (uint8_t it = 0; it < (8 - index); it++) //allign to 8 bits
				byte = byte << 1;

			File_output.write((char*)&byte, sizeof(byte));
		}
	}
	File_output.close();
}
void delete_tree(Node* root) {
	Node* node = root;
	if (node != NULL) {
		delete_tree(node->left);
		delete_tree(node->right);

		delete node;
	}
}

string read_compress_file(void) {
	string output_bits;
	uint8_t bit = 0;
	ifstream File_in;
	File_in.open("output.txt", ios::out | ios::binary);
	if (!File_in) {
		cout << "Cannot open file!" << endl;
		return 0;
	}

	uint8_t byte = 0;
	File_in.seekg(0, ios::end); //go to the end of the file
	int file_size = File_in.tellg(); //get bytes number
	File_in.seekg(0, ios::beg); //go back at the beginnig of the file

	if (file_size == 0) {
		cout << "nothing to read" << endl;
		return 0;
	}

	for (uint16_t i = 0; i < file_size; i++) {
		File_in.read((char*)&byte, 1); //read one byte
		for (uint8_t j = 0; j < 8; j++) {
			bit = byte & 0x80;  //0x80 1000 0000 <- mask // leave just last bit
			if (bit)
				output_bits += '1';
			else
				output_bits += '0';
			byte = byte << 1;
		}
	}
	return output_bits;
	File_in.close();
}

string get_unique_signs(Node *node) {
	string output_signs;
	Node* temp_node;
	temp_node = node;

	while (temp_node != NULL) {
		output_signs += temp_node->position.sign;
		temp_node = temp_node->next;
	}

	return output_signs;
}

bool schearch_sign(char c, Node* root, string b, string &out) {
	if (root != NULL) {
		schearch_sign(c, root->left, b + "0", out);
		if (root->position.sign == c) {
			//cout << b;
			out += b;
			return true;
		}
		schearch_sign(c, root->right, b + "1", out);
		if (root->position.sign == c) {
			//cout << b;
			out += b;
			return true;
		}
	}
}

bool save_dictonary(Node *node, string signs, string all_bits) {
	struct element {
		char sign;
		string bits;
	}el;
	
	ofstream File_dictonary;
	File_dictonary.open("dictonary.txt", ios::out | ios::binary);
	if (!File_dictonary) {
		cout << "Cannot open file!" << endl;
		return 1;
	}

	uint32_t len = all_bits.length(); //get length of the bits
	File_dictonary.write((char*)&len, 4);	//save in dictonary lenght

	string bits;
	string bit = "";
	for (uint8_t i = 0; i < signs.length(); i++) {
		schearch_sign(signs[i], node, bit, bits );
		el.sign = signs[i];
		el.bits = bits;
		bits = "";
		File_dictonary.write((char*)&el, sizeof(el));
	}
	File_dictonary.close();
}



int main()
{
	Node* tree;

	string input_txt;
	string bytes_compressed;
	string unique_signs;

	getline(cin, input_txt);

	create_list( &tree, input_txt );

	sort_list( &tree );

	unique_signs = get_unique_signs(tree);

	generate_tree(&tree);
	
	//useless function, it just print in the console the bit representation of the particular sign
	Compress(tree, input_txt);

	cout << endl;
	get_bits(tree, input_txt);
	cout << output_str;
	
	save_compress_file(output_str);

	save_dictonary(tree, unique_signs, output_str);

	read_compress_file();

	delete_tree(tree);

	//Node_free( &tree );
	//Free_tree(&tree);
    std::cout << "Have a nice day :) \n";
}
