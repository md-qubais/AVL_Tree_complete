#include<bits/stdc++.h>
#define IOS ios_base::sync_with_stdio(false);  cin.tie(NULL)
#define int long long
#define endl "\n"
#define pb push_back
#define p push
#define fori(n) for(int i=0;i<n;i++)
#define ford(n) for(int i=n-1;i>=0;i--)
#define fl(x,n) for(int i=x;i<n;i++)
#define Maxheap priority_queue<int>
#define Minheap priority_queue<int,vector<int>,greater<int>>
#define qubais_judge freopen("input.txt","r",stdin); freopen("output.txt","w",stdout)
using namespace std;

class TreeNode{
public:
	int val;
	int bf;
	int height;
	TreeNode*left,*right;
	TreeNode(int val){
		this->val=val;
		left=right=nullptr;
		bf=0;
		height=1;
	}
};

int height(TreeNode*root){
	if(!root){
		return 0;
	}
	return root->height;
}

void update(TreeNode*root){
	root->height=max(height(root->left),height(root->right))+1;
	root->bf=height(root->left)-height(root->right);
}

TreeNode* right_rotation(TreeNode*root){
	TreeNode*B=root->left;
	TreeNode*B_right=B->right;
	B->right=root;
	root->left=B_right;
	update(root);
	update(B);
	return B;
}

TreeNode* left_rotation(TreeNode*root){
	TreeNode*B=root->right;
	TreeNode*B_left=B->left;
	B->left=root;
	root->right=B_left;
	update(root);
	update(B);
	return B;
}

TreeNode* get_rotation(TreeNode*root){
	root->height=max(height(root->left),height(root->right))+1;
	root->bf=height(root->left) - height(root->right);
	//left
	if(root->bf==2){
		//left - left
		if(root->left->bf==1){
			root=right_rotation(root);			
		}
		//left - right
		else if(root->left->bf==-1){
			root->left=left_rotation(root->left);
			root=right_rotation(root);
		}
	}
	//right
	else if(root->bf==-2){
		//right - right
		if(root->right->bf==-1){
			root=left_rotation(root);
		}
		//right - left
		else if(root->right->bf==1){
			root->right=right_rotation(root->right);
			root=left_rotation(root);
		}
	}
	return root;
}



TreeNode* insert(TreeNode*root,int val){
	if(!root){
		root=new TreeNode(val);
		return root;
	}
	if(root->val>val){
		root->left=insert(root->left,val);
	}else{
		root->right=insert(root->right,val);
	}
	root=get_rotation(root);
	return root;
}

TreeNode* remove(TreeNode*root,int val){
	if(!root){
		return nullptr;
	}
	if(root->val>val){
		root->left=remove(root->left,val);
	}else if(root->val<val){
		root->right=remove(root->right,val);
	}
	else{
		if(root->val==val){
		//this make four choices
			if(!root->left and !root->right){
				return nullptr;
			}
			if(!root->left and root->right){
				return root->right;
			}
			if(root->left and !root->right){
				return root->right;
			}
			if(root->left and root->right){
				TreeNode*temp=root->left;
				while(temp->right){
					temp=temp->right;
				}
				root->val=temp->val;
				root->left=remove(root->left,temp->val);
			}
		}
	}
	root=get_rotation(root);
	return root;
}



void display(TreeNode *node){
    if (node == nullptr)
        return;
    string str = "";
    str += ((node->left != nullptr ? to_string(node->left->val) : "."));
    str += (" -> " + to_string(node->val) + " <- ");
    str += ((node->right != nullptr ? to_string(node->right->val) : "."));
    cout << str << endl;
    display(node->left);
    display(node->right);
}
int32_t main(){
	qubais_judge;
	IOS;
	int n;
	cin>>n;
	TreeNode*root=nullptr;
	while(n--){
		int num;
		cin>>num;
		root=insert(root,num);
	}
	display(root);
	return 0;
}