#pragma once

//left handed coordinates
template<typename X, typename T>
class TreeNode
{

	X x, y;
	X radius;
	T object;
	
	public:
	
	TreeNode<X,T>* topLeftChild;
	TreeNode<X,T>* bottomLeftChild;
	TreeNode<X,T>* bottomRightChild;
	TreeNode<X,T>* topRightChild;
	
	TreeNode<X,T>* parent;
	
	TreeNode( X x, X y, X radius, const T& object )
	{
		this->x = x;
		this->y = y;
		this->object = object;
		this->radius = radius;
		this->topLeftChild = 0;
		this->bottomLeftChild = 0;
		this->bottomRightChild = 0;
		this->topRightChild = 0;
		this->parent = 0;
	};
	
	void insert( X x, X y, X radius, const T& object )
	{
		if( x <= this->x && y => this->y )
		{
			if( this->topLeftChild ) this->topLeftChild->insert( x, y, radius, object );
			else this->topLeftChild = new TreeNode<X,T>( x, y, radius, object );
		}
		if( x <= this->x && y < this->y )
		{
			if( this->bottomLeftChild ) this->bottomLeftChild->insert( x, y, radius, object );
			else this->bottomLeftChild = new TreeNode<X,T>( x, y, radius, object );
		}
		if( x > this->x && y < this->y )
		{
			if( this->bottomRightChild ) this->bottomRightChild->insert( x, y, radius, object );
			else this->bottomRightChild = new TreeNode<X,T>( x, y, radius, object );
		}
		if( x > this->x && y >= this->y )
		{
			if( this->topRightChild ) this->topRightChild->insert( x, y, radius, object );
			else this->topRightChild = new TreeNode<X,T>( x, y, radius, object );
		}
	};
};

template<typename X, typename T>
class QuadTree
{

	TreeNode<X,T>* root;

	public:
	
	QuadTree( X x, X y, X radius, const T& object )
	{
		this->root = new TreeNode<X,T>( x, y, radius, object );
	}
	
	void insert( X x, X y, X radius, const T& object )
	{
		if( this->root ) this->root->insert( x, y, radius, object );	
	}
	
};