#include <iostream>
#include <string>

using namespace std;

typedef struct {
	char sign;
	uint16_t count;
}Position;

typedef struct {
	Position position;
	struct Node* next;
	struct Node* left;
	struct Node* right;
}Node;



int main()
{
	Node* tree;

	string input_txt;
	getline(cin, input_txt);


    std::cout << "Hello World!\n";
}
