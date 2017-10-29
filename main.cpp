#include <iostream>
#include <vector>
using namespace std;

enum Move
{
	UP, DOWN, LEFT, RIGHT
};

struct Node
{
	int state[9];	// 0 1 2
					// 3 4 5
					// 6 7 8
	int cost;		// ���ۺ���fn��ֵ
	Move move;
	// Node *parent;
};

vector<Node> Open;
vector<Node> Close;

const int target_state[9] = { 1,2,3,8,0,4,7,6,5 };

int IsSucceeded(Node &node)
{
	for (int i = 0; i < 9; i++)
		if (target_state[i] != node.state[i] && node.state[i] != 0)
			return 0;
	return 1;
}

int CountCost(Node &node, int depth)
{
	for (int i = 0; i < 9; i++)
		if (target_state[i] != node.state[i] && node.state[i] != 0)
			node.cost++;
	if (node.cost == 0) return 0;
	else return node.cost + depth;
}
// 1 2 3 8 0 4 7 6 5

void FindMinCost()
{
	vector<Node>::iterator iter = Open.begin() + 1, min = Open.begin();
	for (; iter < Open.end(); iter++)
		if (iter->cost < min->cost) min = iter;
	Open.erase(min);
	Close.push_back(*min);
}

void CreateExpandingNode(const Node *c_node, int depth)
{
	int index_0, temp;
	Node new_node;
	for (int i = 0; i < 9; i++)
		if (c_node->state[i] == 0) { index_0 = i; break; }

	depth += 1;

	// �ո����� ���ո�0���±�-3��Ԫ����ո񽻻�
	if (c_node->move != DOWN) {
		new_node = *c_node;
		if (index_0 >= 3) {
			new_node.state[index_0] = new_node.state[index_0 - 3];
			new_node.state[index_0 - 3] = 0;
		}
		new_node.cost = CountCost(new_node, depth);
		// new_node.parent = (Node *)c_node;
		Open.push_back(new_node);
	}

	// �ո����� ���ո�0���±�+3��Ԫ����ո񽻻�
	if (c_node->move != UP) {
		new_node = *c_node;
		if (index_0 <= 5) {
			new_node.state[index_0] = new_node.state[index_0 + 3];
			new_node.state[index_0 + 3] = 0;
		}
		new_node.cost = CountCost(new_node, depth);
		// new_node.parent = (Node *)c_node;
		Open.push_back(new_node);
	}


	// �ո����� ���ո�0���±�-1��Ԫ����ո񽻻�
	if (c_node->move != RIGHT) {

		new_node = *c_node;
		if (index_0 != 0 && index_0 != 3 && index_0 != 6) {
			new_node.state[index_0] = new_node.state[index_0 - 1];
			new_node.state[index_0 - 1] = 0;
		}
		new_node.cost = CountCost(new_node, depth);
		// new_node.parent = (Node *)c_node;
		Open.push_back(new_node);

	}

	// �ո����� ���ո�0���±�+1��Ԫ����ո񽻻�
	if (c_node->move != LEFT) {
		new_node = *c_node;
		if (index_0 != 2 && index_0 != 5 && index_0 != 8) {
			new_node.state[index_0] = new_node.state[index_0 + 1];
			new_node.state[index_0 + 1] = 0;
		}
		new_node.cost = CountCost(new_node, depth);
		// new_node.parent = (Node *)c_node;
		Open.push_back(new_node);
	}

}

int main()
{
	Node node;
	node.cost = 0;

	int depth = 0;

	// node.parent = NULL;
	cout << "�������ʼ��֣�";
	for (int i = 0; i < 9; i++)
		scanf("%d", &node.state[i]);

	if (!CountCost(node, depth)) { 
		cout << "�Ѿ�������" << endl; 
		return 0; 
	}
	else Open.push_back(node);

	while (!Open.empty())
	{
		// ��Open����ѡ��һ��fֵ��С�Ľڵ�
		FindMinCost();
		// �ѽڵ��OPEN�����Ƴ���������CLOSED����չ�ڵ����
		node = Close.back();
		// �����Ŀ��ڵ㣬��ɹ��˳������һ����
		if (IsSucceeded(node)) {
			cout << "�ɹ��ҵ�һ��·��" << endl;
			/* to do �� */ 
			return 0; 
		}
		// ��չ��ǰ��㣬����ȫ�������ڵ�

	}

	cout << "�޽�" << endl;
	return 0;
}