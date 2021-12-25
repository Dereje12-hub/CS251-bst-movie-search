//#pragma once

//Name Dereje Gudeta  UIN:
// Binary search tree
//

//   Dereje Gudeta 


/*bsh.h*/


// Binary search tree


#pragma once

#include <iostream>
#include <algorithm>  // std::max

using namespace std;

template<typename TKey, typename TValue>  
class binarysearchtree
{
private:
  struct NODE
  {
    TKey  Key;
	TValue* Value;
    NODE* Left;
    NODE* Right;
  };

  NODE* Root;  // pointer to root node of tree (nullptr if empty) 
  int   Size;  // # of nodes in the tree (0 if empty)


  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  
  
  /* _height does the actual work of computing height, recursively. */	
  
  int _height(NODE* cur)
  {
    if (cur == NULL)
      return -1;
    else
    {
      int heightL = _height(cur->Left);
      int heightR = _height(cur->Right);

      return 1 + std::max(heightL, heightR);
    }
  }//end height function

 //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 
 /* _inorder does the actual inorder traversal and output 
    to console.  Each key is output to the console followed
    by " ", including the last key. */
	
  void _inorder(NODE* cur)
  {
    if (cur == NULL)
      return;
    else
    {
      _inorder(cur->Left);
      cout << cur->Key << ":" << cur->Value ->Num5Stars << endl;
      _inorder(cur->Right);
    }
  } //end _inorder 
  
 //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 
 
 
 //copy helper
	void copy(NODE* temp)
	{
		if (temp != NULL)
		{
			insert(temp->Key, temp->Value);
			copy(temp->Left);
			copy(temp->Right);

		}
	}


 
public:
  
  /* default constructor: */
   
  binarysearchtree()   // Creates an empty tree.
  {
    Root = NULL;
    Size = 0;
  }
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

  /* Copy Constructor */
   //to make a complete and independent copy of the “other” tree 
  
  binarysearchtree(binarysearchtree& other)
  {
      //conditional statement that compares other roots and size
	  if (other.Root == NULL)
	  {
		  Root = NULL;
		  Size = 0;
	  }
	  
	  else  
	  {
		  NODE* node = new NODE {other.Root->Key, other.Root->Value};
		  Root = node;
		  Size = 1;
		  _buildCopy(Root, other.Root); //recursive call 
		  
	  }
  }//end binary search tree
  
 //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
   
  /* size:
   Returns the # of nodes in the tree, 0 if empty. */
  
  int size() {return Size;}
 //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  
  /* height 
      Computes and returns height of tree; height of an empty tree is
      defined as -1. */
	  
  int height()
  {
	  if (Root == NULL)
		  return -1;
	  
	  int goLeft = _height(Root->Left);
	  int goRight = _height(Root->Right);
	  
	  return goLeft > goRight ? goLeft : goRight;
  }//end the height

 //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++  
  /* search: 
   Searches the tree for the given key, returning true if found
   and false if not.  */
   
  TValue** search(TKey key)
  {
    NODE* cur = Root;
    
	/*Iterate until the new curll is not Null   */
    while (cur != NULL)
    {
      if (key == cur->Key)  // already in tree
        return &(cur->Value); 

      if (key < cur->Key)  // search left:
        cur = cur->Left;
      
      else
        cur = cur->Right;
		
    }//end while  

    // if get here, not found
    return NULL;
  } //end funciton 

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 
	// insert
	//
	// Inserts the given key into the tree; if the key has already been insert then
	// the function returns without changing the tree.
	//
	void insert(TKey key, TValue*Value)
	{
		NODE* prev = nullptr;
		NODE* cur = Root;

		//
		// 1. Search to see if tree already contains key:
		//
		while (cur != nullptr)
		{
			if (key == cur->Key)  // already in tree
				return;

        if (key < cur->Key)  // search left:
			{
				prev = cur;
				cur = cur->Left;
			}
			else
			{
				prev = cur;
				cur = cur->Right;
			}
		}//while

		//
		// 2. if we get here, key is not in tree, so allocate
		// a new node to insert:
		// 
		NODE* newNode = new NODE();
		newNode->Key = key;
		newNode->Value = *&Value;
		newNode->Left = nullptr;
		newNode->Right = nullptr;

		//
		// 3. link in the new node:
		//
		// NOTE: cur is null, and prev denotes node where
		// we fell out of the tree.  if prev is null, then
		// the tree is empty and the Root pointer needs 
		// to be updated.
		//
		if (prev == nullptr)
			Root = newNode;
		else if (key < prev->Key)
			prev->Left = newNode;
		else
			prev->Right = newNode;

		// 
		// 4. update size and we're done:
		//
		Size++;
	}




 //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

  void inorder()
  {
    cout << "Inorder: ";
    _inorder(Root);
    cout << endl;
  }


};

