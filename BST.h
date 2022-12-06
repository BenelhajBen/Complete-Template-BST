#ifndef BST_H
#define BST_H
#include <iostream>

/**
* @class BST
* @brief BST template class with the required functionality to make a functional binary search tree
*
* @author Achraf Ben EL Haj
* @version 01
* @date lab9 Submission date
*
* @author Achraf Ben El Haj
* @version 02
* @date 11/25/2022
*
* @author Achraf Ben El Haj
* @version 03
* @data 12/1/2022
*
* @bug 1 bug: Search can alter data cant make value parameter a const. Had a problem with it breaking the entirity my program and I am low on time for debugging.
*/

template<class B>
struct Node
{
    B data;
    Node* right;
    Node* left;
};

//----------------------------

template<class B>
class BST
{
    public:

        /**
        * @brief constructor
        *
        * @return contructor
        */
        BST();

        /**
        * @brief constructor
        * @param B&
        * @return constructor
        */
        BST(B& data);

        /**
        * @brief copy constructor used to copy another bst
        * @param  BST<B>
        * @return copy  constructor
        */
        BST(const BST<B> &obj);

        /**
        * @brief copy assignment
        * copies another BST using the overloaded assignment operator=. Unimplemented
        * @return BST
        */
        BST& operator=(const BST<B> &obj);


        /**
        * @brief Destructor
        *
        * @return Destructor
        */
        ~BST();

        /**
         * @brief public search function
         * @param B&
         * @return void
         */
        bool Search(B& value) const;

        /**
         * @brief public Post Order Post Order traversal function
         * @param function ptr
         * @return void
         *
         */
        void PostOrder(void(*visit)(B& value))const;

         /**
         * @brief public In Order traversal function
         * @param function ptr
         * @return void
         *
         */
        void Inorder(void(*visit)(B& value))const;

          /**
         * @brief public Pre function
         * @tparam B&
         * @return void
         */
        void PreOrder(void(*visit)(B& value))const;

         /**
         * @brief public Insert function
         * @tparam B&
         * @return void
         */
        void Insert(const B& value);


         /**
         * @brief public clear tree function (deleting the tree)
         *
         * @return void
         */
        void ClearTree();

         /**
         * @brief debug function for size (IGNORE)
         * @return int
         */
        int GetSize(); // test function "ignore"

    private:
         /**
         * @brief debug function for size (IGNORE)
         * @return int
         */
        int GetSize(Node<B>* node); // test function "ignore"

        Node<B>* root;  /// Member variable root


        /**
        * @brief private search function of the bst.
        * @tparam Node<B>*, B&
        * @return bool
        */
        bool Search(Node<B>* root, B& value) const;

        /**
        * @brief private clear tree function (delete tree)
        * @tparam Node<B>*
        * @return void
        */
        void ClearTree(Node<B>* &node);

        /**
        * @brief private  insert function to insert a value to the tree
        * @tparam Node<B>* , B&
        * @return void
        */
        void Insert(Node<B>*& p, const B& value);

        /**
        * @brief  private PostOrder traversal function
        * @param Node<B>*, function  ptr
        * @return void
        */
        void PostOrder(Node<B>* p, void(*visit)(B& value))const;
        /**
        * @brief  private InOrder traversal function
        * @param Node<B>*, function  ptr
        * @return void
        */
        void Inorder(Node<B>* p, void(*visit)(B& value))const;

        /**
        * @brief  private PreOrder traversal function
        * @param Node<B>*, function  ptr
        * @return void
        */
        void PreOrder(Node<B>* p, void(*visit)(B& value))const;

        /**
        * @brief  private Copy function to copy a new tree to another tree
        * @param Node<B>*, Node<B>*
        * @return void
        */
        void Copy(Node<B>* &copyTreeRoot, Node<B>* otherTreeRoot);
};


template <class B>
int BST<B>::GetSize()
{
    return GetSize(root);
}

template<class B>
int BST<B>::GetSize(Node<B>* n)
{
    if(n == nullptr)
    {
        return 0;
    }else
    {
        return(GetSize(n->left) +1 + GetSize(n->right));
    }
}

template<class B>
BST<B>::BST()
{
    root = nullptr;
}


template<class B>
BST<B>::~BST()
{
    ClearTree(root); // private clear tree call
}

template<class B>
BST<B>::BST(const BST<B>& other)
{
    if(other.root == nullptr)
    {
        root=nullptr;
    }
    else
    {
        Copy(root, other.root); // recursively copying another bst.
    }
}

template<class B>
void BST<B>::Copy(Node<B>* &copyTreeRoot, Node<B> *otherTreeRoot)
{
    if(otherTreeRoot == nullptr)
    {
        copyTreeRoot == nullptr;
    }else
    {
        copyTreeRoot = new Node<B>;
        copyTreeRoot->data = otherTreeRoot->data;
        Copy(copyTreeRoot->left,otherTreeRoot->left); // copying  left  side of the tree
        Copy(copyTreeRoot->right,otherTreeRoot->right);  // copying right side of the tree
    }
}

template<class B>
BST<B>& BST<B>::operator=(const BST<B>& other)
{
    if(this != &other)
    {
        if(other.root  == nullptr)
        {
            root = nullptr;
        }else
        {
            Copy(root, other.root);
        }
    }
    return *this;
}


//recursively clearing the tree. Will only be called in destructor. Have set to private to assume we will never want to delete a tree ever until run time is over.
template<class B>
void BST<B>::ClearTree(Node<B>* &p)
{
    if(p!=nullptr)
    {
        ClearTree(p->left);
        ClearTree(p->right);
        delete p;
        p = nullptr;
    }
}

template<class B>
void BST<B>::ClearTree()
{
    ClearTree(root);
}




template<class B>
void BST<B>::Insert(const B& value)
{
    Insert(root, value);
}


template<class B>
void BST<B>::Insert(Node<B>*& node, const B& value)
{
    if(node == nullptr)
    {
        node = new Node<B>;
        node->data = value;
        node->left = nullptr;
        node->right = nullptr;
    }else if(value < node->data)
    {
        Insert(node->left, value);
    }else
    {
        Insert(node->right, value);
    }
}


template<class B>
bool BST<B>::Search(Node<B>* p, B& value) const
{
    if(p == nullptr)
    {
        return false;
    }

    else if(value == p->data)
    {
        return true;
    }

    else if(value < p->data)
    {
        return Search(p->left, value);
    }

    else
    {
        return Search(p->right, value);
    }
}

template<class B>
bool BST<B>::Search(B& value) const
{
    return Search(root,value);
}

template<class B>
void BST<B>::Inorder(Node<B>* p, void(*visit)(B& value)) const
{
    if(p != nullptr)
    {
        Inorder(p->left,*visit);
        (*visit)(p->data);
        Inorder(p->right,*visit);
    }
}

template<class B>
void BST<B>::PostOrder(Node<B>* p, void(*visit) (B& value)) const
{
    if(p!=nullptr)
    {
        PostOrder(p->left,*visit);
        PostOrder(p->right,*visit);
        (*visit)(p->data);
    }
}

template<class B>
void BST<B>::PreOrder(Node<B>* p, void(*visit)(B& value)) const
{
    if(p!=nullptr)
    {
        (*visit)(p->data);
        PreOrder(p->left,*visit);
        PreOrder(p->right,*visit);
    }
}

template<class B>
void BST<B>::Inorder(void(*visit)(B& value)) const
{
    Inorder(root, visit);
}

template<class B>
void BST<B>::PostOrder(void(*visit)(B& value)) const
{
    PostOrder(root, visit);
}

template<class B>
void BST<B>::PreOrder(void(*visit)(B& value)) const
{
    PreOrder(root, visit);
}




#endif // BST_H
