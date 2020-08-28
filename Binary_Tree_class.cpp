#include<bits/stdc++.h>
using namespace std;

struct Node{
	int data;
	struct Node* left, *right;
} *root = NULL;

class BinaryTree
{
	public:
		vector<int> arr;

	struct Node* create_node( int data )
	{
		struct Node* node = new Node;
		node->data = data;
		node->right = node->left = NULL;
		return node;
	}


	struct Node* remove_null_nodes( struct Node* root)
	{
		if(root == NULL || root->data == INT_MAX)
			return NULL;

		root->left = remove_null_nodes(root->left);
		root->right = remove_null_nodes(root->right);
		return root;
	}


	struct Node* insert_node_using_queue( struct Node* root, int value, queue<struct Node*> &queue)
	{
		struct Node* new_node = create_node(value);
		if(root == NULL)
			root = new_node;
		else if(queue.front()->left == NULL)
			queue.front()->left = new_node;
		else{
			queue.front()->right = new_node;
			queue.pop();
		}
		if(value != INT_MAX)
			queue.push(new_node);
		return root;

	}


	void build_tree_using_queue( struct Node** root)
	{
		string temp;
		queue<struct Node*> queue;
		while( cin >> temp)
		{
			if(temp == "null")
				*root = insert_node_using_queue(*root, INT_MAX, queue);
			else
				*root = insert_node_using_queue(*root, stoi(temp), queue);
		}

		*root = remove_null_nodes(*root);
		return;
	}


	struct Node* build_tree_recursively(int index)
	{
		if(index >= arr.size())
			return NULL;

		struct Node* node = create_node(arr[index]);
		node->left = build_tree_recursively( 2*index + 1);
		node->right = build_tree_recursively( 2*index + 2);
		return node;
	}


	struct Node* build_tree_from_inorder_and_preorder(int start, int end, vector<int> const &pre_order, int &pre_index, unordered_map<int,int> map)
	{
		if(start > end)
			return nullptr;

		struct Node* root = create_node(pre_order[pre_index++]);
		int index = map[root->data];
		root->left = build_tree_from_inorder_and_preorder(start, index-1, pre_order, pre_index, map);
		root->right = build_tree_from_inorder_and_preorder(index+1, end, pre_order, pre_index, map);
		return root;
	}

	struct Node* build_tree_from_inorder_and_preorder(vector<int> const &in_order, vector<int> const &pre_order)
	{

		int len = in_order.size();
		unordered_map<int, int> map;
		for(int i=0; i<len; i++)
			map[in_order[i]] = i;

		int pre_index = 0;
		root = build_tree_from_inorder_and_preorder(0, len-1, pre_order, pre_index, map);
		return root;
	}


	int get_depth( struct Node* node)
	{
		int d = 0;
		while ( node != NULL)
		{
			d++;
			node = node->left;
		}
		return d;
	}


	int get_longest_path( struct Node* root, int &ans)
	{
	    if(root == NULL)
	        return 0;
	   int left = get_longest_path( root->left, ans);
	   int right = get_longest_path(root->right, ans);
	   ans = max(ans, left + right);
	   
	   return 1 + max(left, right);
	}


	int lowest_common_ancestor(struct Node *root, int M, int N, int &ans)
	{
	    if (root == NULL)
	        return 0;
	    int left = lowest_common_ancestor(root->left, M, N, ans) ? 1 : 0;
	    int right = lowest_common_ancestor(root->right, M, N, ans) ? 1 : 0;
	    int current = (root->data == M || root->data == N) ? 1 : 0;

	    if (left + right + current >= 2)
	        ans = root->data;

	    return (left + right + current > 0);
	}
    
    void get_bottom_left_most_node(struct Node *root, int curr_depth, int &max_depth, int &ans)
    {
        if (root == NULL)
            return;
    
        if (curr_depth > max_depth)
        {
            max_depth = curr_depth;
            ans = root->data;
        }
    
        get_bottom_left_most_node(root->left, curr_depth + 1, max_depth, ans);
        get_bottom_left_most_node(root->right, curr_depth + 1, max_depth, ans);
    
        return;
    }
    
    void get_right_side_view(struct Node* root, int level, vector<int> &right_side_view)
    {
        if(root == NULL)
            return;
        
        if(level == right_side_view.size())
            right_side_view.push_back(root->data);
        
        get_right_side_view(root->right, level + 1, right_side_view);
        get_right_side_view(root->left, level + 1, right_side_view);
        
        return;
    }
    
    vector<int> get_right_side_view(struct Node* root)
    {
        vector<int> right_side_view;
        get_right_side_view(root, 0, right_side_view);
        return right_side_view;
    }

	void inorder_traversal( struct Node* node)
	{
		if(node == NULL)
			return;

		inorder_traversal(node->left);
		cout << node->data << " ";
		inorder_traversal(node->right);
	}

	void post_order_traversal( struct Node* node)
	{
		if(node == NULL)
			return;
		post_order_traversal(node->left);
		post_order_traversal(node->right);
		cout << node->data << " ";
	}

	void pre_order_traversal( struct Node* node)
	{
		if(node == NULL)
			return;
		cout << node->data << " ";
		pre_order_traversal(node->left);
		pre_order_traversal(node->right);
	}
};
