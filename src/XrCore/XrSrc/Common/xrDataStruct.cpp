#include "xrDataStruct.h"

//template <typename T>
//void CUniLinkNode<T>::VPTRHolder()
//{
//}

template <typename T>
void CUniLinkNode<T>::Append(CUniLinkNode* node)
{
    CUniLinkNode* temp = this;
    while (temp->m_pNext) {
        temp = temp->GetNext();
    }

    temp->SetNext(node);
}

template <typename T>
void CUniLinkNode<T>::InsertAfter(CUniLinkNode* node)
{
    node->SetNext(GetNext());
    SetNext(node);
}

template <typename T>
void CUniLinkNode<T>::Remove(T** head)
{
    XrASSERT(head);
    CUniLinkNode* temp = (CUniLinkNode*)*head, *prev = NULL;
    if (temp == this) {
        *head = this->GetNext();
        SetNext(0);
        return;
    }

    while (temp) {
        if (temp == this) break;
        prev = temp;
        temp = temp->GetNext();
    }
    XrASSERT(temp);
    prev->SetNext(temp->GetNext());
    SetNext(0);
    return;
}

template <typename T>
void CUniLinkNode<T>::Delete(T** head)
{
    Remove(head);
    delete this;
    return;
}

template <typename T>
void CUniLinkNode<T>::RemoveAllAfter(T** head)
{
    XrASSERT(head);
    CUniLinkNode* temp = (CUniLinkNode*)*head, *prev;
    if (temp == this) {
        *head = 0;//*head = this->GetNext();
        return;
    }

    while (temp) {
        if (temp == this) break;
        prev = temp;
        temp = temp->GetNext();
    }
    XrASSERT(temp);
    prev->SetNext(0);

    return;
}

template <typename T>
void CUniLinkNode<T>::DeleteAllAfter(T** head)
{
    XrASSERT(head);
    CUniLinkNode* temp = (CUniLinkNode*)*head, *prev = (CUniLinkNode*)*head;

    if (temp == this) {
        *head = 0;//this->GetNext();
        goto DeleteAfter;
    }

    while (temp) {
        if (temp == this) break;
        prev = temp;
        temp = temp->GetNext();
    }
    prev->SetNext(0);

DeleteAfter:

    XrASSERT(temp);

    while (temp) {
        prev = temp;
        temp = temp->GetNext();
        delete prev;
    }
    return;
}

template <typename T>
void CBiLinkNode<T>::Append(CBiLinkNode* node)
{
    CBiLinkNode* temp = this;
    while (temp->GetNext()) {
        temp = temp->GetNext();
    }

    temp->SetNext(node);
    node->SetPrev(temp);
}


template <typename T>
void CBiLinkNode<T>::InsertBefore(CBiLinkNode* node)
{
    if (GetPrev()) {
        node->SetPrev(GetPrev());
        GetPrev()->SetNext(node);
    }

    SetPrev(node);
	node->SetNext(this);
}


template <typename T>
void CBiLinkNode<T>::InsertAfter(CBiLinkNode* node)
{
    if (GetNext()) {
        node->SetNext(GetNext());
        GetNext()->SetPrev(node);
    }

    SetNext(node);
    node->SetPrev(this);

}

template <typename T>
void CBiLinkNode<T>::Remove()
{
    if (GetNext()) {
        GetNext()->SetPrev(GetPrev());
    }

    if (GetPrev()) {
        GetPrev()->SetNext(GetNext());
    }
    SetPrev(0);
    SetNext(0);
}

template <typename T>
void CBiLinkNode<T>::Remove(T** head)
{
    XrASSERT(head);
    CBiLinkNode* temp = (CBiLinkNode*)*head;
    if (temp == this) {
        *head = GetNext();
    }

    if (GetNext()) {
        GetNext()->SetPrev(GetPrev());
    }

    if (GetPrev()) {
        GetPrev()->SetNext(GetNext());
    }
    SetPrev(0);
    SetNext(0);
}


template <typename T>
void CBiLinkNode<T>::CutBefore()
{
    if (GetPrev()) GetPrev()->SetNext(0);
    SetPrev(0);
}

template <typename T>
void CBiLinkNode<T>::CutAfter()
{
    if (GetNext()) GetNext()->SetPrev(0);
    SetNext(0);
}

template <typename T>
void CTreeNode<T>::Remove()
{
    if (GetNext()) {
        GetNext()->SetPrev(GetPrev());
    }
    if (GetPrev()) {
        GetPrev()->SetNext(GetNext());
    }
    if (GetSuper() && GetSuper()->GetSub() == this) {
        GetSuper()->SetSub(GetNext());
    }
    SetPrev(0);
    SetNext(0);
    SetSuper(0);
}

template <typename T>
void CTreeNode<T>::Isolate()
{
    if (GetNext()) {
        GetNext()->SetPrev(GetPrev());
    }
    if (GetPrev()) {
        GetPrev()->SetNext(GetNext());
    }
    if (GetSuper() && GetSuper()->GetSub() == this) {
        GetSuper()->SetSub(GetNext());
    }
    SetPrev(0);
    SetNext(0);
    SetSuper(0);

    CTreeNode* temp = GetSub();
    SetSub(0);

    if (temp) {
        do {
            temp->SetSuper(0);
            temp = temp->GetNext();
        }
        while (temp);
    }
}
template <typename T>
void CTreeNode<T>::MoveToAfter(CTreeNode* node)
{
	if (node->GetNext()) {
        node->GetNext()->SetPrev(node->GetPrev());
    }
    if (node->GetPrev()) {
        node->GetPrev()->SetNext(node->GetNext());
    }
   /* if (node->GetSuper() && node->GetSuper()->GetSub() == this) {
        node->GetSuper()->SetSub(node->GetNext());
    }*/

	if (GetNext()) {
        node->SetNext(GetNext());
        GetNext()->SetPrev(node);
    }	
	else
	{
		node->SetNext(NULL);
	}
	SetNext(node);
    node->SetPrev(this);
	if(GetSuper())
    {
		node->SetSuper(GetSuper());
	}

}

template <typename T>
void CTreeNode<T>::ReLinkAsHeader(CTreeNode* header)
{
    XrASSERT(header);
    CTreeNode *prev, *temp;
    CTreeNode* prevHead = header->GetSub();

    if (prevHead == this) return;
    header->SetSub(this);

    prev = GetPrev();
    if (prev) {
        prev->SetNext(NULL);
        SetPrev(NULL);
    }

    temp = this;

    while (temp->GetNext()) {
        temp = temp->GetNext();
    }

    temp->SetNext(prevHead);
    prevHead->SetPrev(temp);
}

template <typename T>
T* CTreeNode<T>::GetRoot()
{
    CTreeNode* temp = this;
    while (temp->GetSuper()) {
        temp = temp->GetSuper();
    }

    return (T*)temp;
}

template <typename T>
void CTreeNode<T>::AppendAsChild(CTreeNode* childNode)
{
    CTreeNode* pTemp = GetSub();
    if (pTemp) {
        while (pTemp->GetNext()) {
            pTemp = pTemp->GetNext();
        }
        pTemp->SetNext(childNode);
        childNode->SetPrev(pTemp);
    }
    else {
        SetSub(childNode);
    }
    childNode->SetSuper(this);
}

template <typename T>
void CTreeNode<T>::InsertAsChild(CTreeNode* childNode)
{
    CTreeNode* pTemp = GetSub();
    if (pTemp) {
        SetSub(childNode);
        childNode->SetNext(pTemp);
        pTemp->SetPrev(childNode);
    }
    else {
        SetSub(childNode);
    }
    childNode->SetSuper(this);
}

template <typename T>
void CTreeNode<T>::InsertAfter(CTreeNode* node)
{
    if (GetNext()) {
        node->SetNext(GetNext());
        GetNext()->SetPrev(node);
    }
    SetNext(node);

    node->SetPrev(this);
    node->SetSuper(GetSuper());
}

template <typename T>
void CTreeNode<T>::InsertBefore(CTreeNode* node)
{
    if (GetPrev()) {
        node->SetPrev(GetPrev());
        GetPrev()->SetNext(node);
    }
    else {
        GetSuper()->SetSub(node);
    }
    node->SetNext(this);
    node->SetSuper(GetSuper());
    SetPrev(node);
}


template <typename T>
void CTreeNode<T>::CutBefore()
{
    if (GetPrev()) GetPrev()->SetNext(0);
    else {
        if (GetSuper()) GetSuper()->SetSub(0);
    }
    SetPrev(0);
}


template <typename T>
void CTreeNode<T>::Append(CTreeNode* node)
{
    CTreeNode* temp = this;
    while (temp->GetNext()) {
        temp = temp->GetNext();
    }

    temp->SetNext(node);
    node->SetPrev(temp);
    node->SetSuper(GetSuper());
}

template <typename T>
void RBTree<T>::_RBRotateLeft(RBNode<T> *node)
{
    RBNode<T> *right = node->rb_right;

    int a=0,b=0,c=0;
    if(node->rb_left)
        a=node->rb_left->weight;
    if(right->rb_left)
        b=right->rb_left->weight;
    if(right->rb_right)
        c=right->rb_right->weight;
    node->weight=a+b+1;
    right->weight=a+b+c+2;

    if ((node->rb_right = right->rb_left))
        right->rb_left->rb_parent = node;
    right->rb_left = node;

    if ((right->rb_parent = node->rb_parent))
    {
        if (node == node->rb_parent->rb_left)
            node->rb_parent->rb_left = right;
        else
            node->rb_parent->rb_right = right;
    }
    else
        root = right;

    node->rb_parent = right;
}

template <typename T>
void RBTree<T>::_RBRotateRight(RBNode<T> *node)
{
    RBNode<T> *left = node->rb_left;

    int a=0,b=0,c=0;
    if(node->rb_right)
        c=node->rb_right->weight;
    if(left->rb_left)
        a=left->rb_left->weight;
    if(left->rb_right)
        b=left->rb_right->weight;
    node->weight=b+c+1;
    left->weight=a+b+c+2;

    if ((node->rb_left = left->rb_right))
        left->rb_right->rb_parent = node;
    left->rb_right = node;

    if ((left->rb_parent = node->rb_parent))
    {
        if (node == node->rb_parent->rb_right)
            node->rb_parent->rb_right = left;
        else
            node->rb_parent->rb_left = left;
    }
    else
        root = left;
    node->rb_parent = left;
}


template <typename T>
void RBTree<T>::_RBEraseColor(RBNode<T> *node, RBNode<T> *parent)
{
    RBNode<T> *other;

    while ((!node || node->rb_color == RB_BLACK) && node != root)
    {
        if (parent->rb_left == node)
        {
            other = parent->rb_right;
            if (other->rb_color == RB_RED)
            {
                other->rb_color = RB_BLACK;
                parent->rb_color = RB_RED;
                _RBRotateLeft(parent);
                other = parent->rb_right;
            }
            if ((!other->rb_left ||
                 other->rb_left->rb_color == RB_BLACK)
                && (!other->rb_right ||
                other->rb_right->rb_color == RB_BLACK))
            {
                other->rb_color = RB_RED;
                node = parent;
                parent = node->rb_parent;
            }
            else
            {
                if (!other->rb_right ||
                    other->rb_right->rb_color == RB_BLACK)
                {
                    register RBNode<T> *o_left;
                    if ((o_left = other->rb_left))
                        o_left->rb_color = RB_BLACK;
                    other->rb_color = RB_RED;
                    _RBRotateRight(other);
                    other = parent->rb_right;
                }
                other->rb_color = parent->rb_color;
                parent->rb_color = RB_BLACK;
                if (other->rb_right)
                    other->rb_right->rb_color = RB_BLACK;
                _RBRotateLeft(parent);
                node = root;
                break;
            }
        }
        else
        {
            other = parent->rb_left;
            if (other->rb_color == RB_RED)
            {
                other->rb_color = RB_BLACK;
                parent->rb_color = RB_RED;
                _RBRotateRight(parent);
                other = parent->rb_left;
            }
            if ((!other->rb_left ||
                 other->rb_left->rb_color == RB_BLACK)
                && (!other->rb_right ||
                other->rb_right->rb_color == RB_BLACK))
            {
                other->rb_color = RB_RED;
                node = parent;
                parent = node->rb_parent;
            }
            else
            {
                if (!other->rb_left ||
                    other->rb_left->rb_color == RB_BLACK)
                {
                    register RBNode<T> *o_right;
                    if ((o_right = other->rb_right))
                        o_right->rb_color = RB_BLACK;
                    other->rb_color = RB_RED;
                    _RBRotateLeft(other);
                    other = parent->rb_left;
                }
                other->rb_color = parent->rb_color;
                parent->rb_color = RB_BLACK;
                if (other->rb_left)
                    other->rb_left->rb_color = RB_BLACK;
                _RBRotateRight(parent);
                node = root;
                break;
            }
        }
    }
    if (node)
        node->rb_color = RB_BLACK;
}

template <typename T>
void RBTree<T>::_RBInsertColor(RBNode<T> *node)
{
    RBNode<T> *parent, *gparent;

    while ((parent = node->rb_parent) && parent->rb_color == RB_RED)
    {
        gparent = parent->rb_parent;

        if (parent == gparent->rb_left)
        {
            {
                register RBNode<T> *uncle = gparent->rb_right;
                if (uncle && uncle->rb_color == RB_RED)
                {
                    uncle->rb_color = RB_BLACK;
                    parent->rb_color = RB_BLACK;
                    gparent->rb_color = RB_RED;
                    node = gparent;
                    continue;
                }
            }

            if (parent->rb_right == node)
            {
                register RBNode<T> *tmp;
                _RBRotateLeft(parent);
                tmp = parent;
                parent = node;
                node = tmp;
            }

            parent->rb_color = RB_BLACK;
            gparent->rb_color = RB_RED;
            _RBRotateRight(gparent);
        } else {
            {
                register RBNode<T> *uncle = gparent->rb_left;
                if (uncle && uncle->rb_color == RB_RED)
                {
                    uncle->rb_color = RB_BLACK;
                    parent->rb_color = RB_BLACK;
                    gparent->rb_color = RB_RED;
                    node = gparent;
                    continue;
                }
            }

            if (parent->rb_left == node)
            {
                register RBNode<T> *tmp;
                _RBRotateRight(parent);
                tmp = parent;
                parent = node;
                node = tmp;
            }

            parent->rb_color = RB_BLACK;
            gparent->rb_color = RB_RED;
            _RBRotateLeft(gparent);
        }
    }

    root->rb_color = RB_BLACK;
}

template <typename T>
bool RBTree<T>::Insert(T & t)
{
    RBNode<T> *node = new RBNode<T>;
    if (!node) return 0;

    node->key = t;
    RBNode<T> **p = &root;
    RBNode<T> *parent = NULL;
    int sig;

    while (*p) {
        parent = *p;
        parent->weight++;
        sig = node->key.cmp(&node->key, &parent->key);

        if (sig < 0)
            p = &(parent)->rb_left;
        else if (sig > 0)
            p = &(parent)->rb_right;
        else{
            while(parent){
                parent->weight--;
                parent=parent->rb_parent;
            }
            return 1;
        }
    }
    m_size++;
    node->rb_parent = parent;
    node->rb_color = RB_RED;
    node->rb_left = node->rb_right = NULL;
    node->weight=1;
    *p = node;
    _RBInsertColor(node);
    return 1;
}

template <typename T>
void RBTree<T>::Remove(RBNode<T> *node)
{

    RBNode<T> *child, *parent, *savedNode = node;
    int color;

    if (!node->rb_left)
        child = node->rb_right;
    else if (!node->rb_right)
        child = node->rb_left;
    else
    {
        RBNode<T> *old = node, *left;

        node = node->rb_right;
        while ((left = node->rb_left) != NULL)
            node = left;
        child = node->rb_right;
        parent = node->rb_parent;
        color = node->rb_color;

        if (child)
            child->rb_parent = parent;
        if (parent)
        {
            if (parent->rb_left == node)
                parent->rb_left = child;
            else
                parent->rb_right = child;
        }
        else
            root = child;

        if (node->rb_parent == old)
            parent = node;

        RBNode<T> * q = parent;
        while(q){
            q->weight--;
            q=q->rb_parent;
        }

        node->rb_parent = old->rb_parent;
        node->rb_color = old->rb_color;
        node->weight = old->weight;
        node->rb_right = old->rb_right;
        node->rb_left = old->rb_left;

        if (old->rb_parent)
        {
            if (old->rb_parent->rb_left == old)
                old->rb_parent->rb_left = node;
            else
                old->rb_parent->rb_right = node;
        } else
            root = node;

        old->rb_left->rb_parent = node;
        if (old->rb_right)
            old->rb_right->rb_parent = node;
        goto color;
    }

    parent = node->rb_parent;
    color = node->rb_color;

    if (child)
        child->rb_parent = parent;
    if (parent)
    {
        RBNode<T> * q = parent;
        while(q){
            q->weight--;
            q=q->rb_parent;
        }
        if (parent->rb_left == node)
            parent->rb_left = child;
        else
            parent->rb_right = child;
    }
    else
        root = child;

    m_size--;

color:
    if (color == RB_BLACK)
        _RBEraseColor(child, parent);

    delete savedNode;
}

template <typename T>
RBNode<T> * RBTree<T>::Select(int order)
{
    if(order<=0 || order > m_size)
        return NULL;
    RBNode<T> * cn=root;
    int ls=0;
    while(cn){
        if(cn->rb_left)
            ls=cn->rb_left->weight;
        else ls=0;
        if(ls+1==order)
            return cn;
        else if(ls+1>order){
            cn=cn->rb_left;
        }else{
            order-=ls+1;
            cn=cn->rb_right;
        }
    }
    return NULL;
}

template <typename T>
int RBTree<T>::Rank(T * w)
{
    if(!root)
        return 0;

    int res=0;
    RBNode<T> * cn = root;
    int sig;
    while(cn){
        sig = cmp(&cn->key,w);
        if(sig==0)
            return res+1+(cn->rb_left?cn->rb_left->weight:0);
        else if(sig<0){
            res+=1+(cn->rb_left?cn->rb_left->weight:0);
            cn = cn->rb_right;
        }else{
            cn = cn->rb_left;
        }
    }
    return res;
}

template <typename T>
void RBTree<T>::_DeleteTree(RBNode<T>* node) {
    if(node){
        if(node ->rb_left)
            this->_DeleteTree(node->rb_left);
        if(node ->rb_right)
            this->_DeleteTree(node->rb_right);
        delete node;
    }
}

template <typename T>
bool RBTree<T>::RemoveByRank(int rank)
{
    RBNode<T>* node = Select(rank);
    if (!node) {
        return 0;
    }
    else {
        Remove(node);
        return 1;
    }
}

template <typename T>
void RBTree<T>::First()
{
    RBNode<T>* n;

    m_IsFirst = true;
    m_IsLast = true;

    n = root;
    if (!n) {
        return;
    }
    while (n->rb_left) {
        n = n->rb_left;
    }
    m_IsLast = false;
    current = n;
}

template <typename T>
void RBTree<T>::Last()
{
    RBNode<T>* n;

    m_IsFirst = true;
    m_IsLast = true;

    n = root;
    if (!n) {
        return;
    }
    while (n->rb_right) {
        n = n->rb_right;
    }
    m_IsFirst = false;
    current = n;
}

template <typename T>
void RBTree<T>::Next()
{

    /* If we have a right-hand child, go down and then left as far
       as we can. */
    if (current->rb_right) {
        current = current->rb_right;
        while (current->rb_left)
            current=current->rb_left;
        return;
    }

    while (current->rb_parent && current == current->rb_parent->rb_right)
        current = current->rb_parent;

    if (current == root) {
        m_IsLast = true;
    }

    if (current->rb_parent) {
        current = current->rb_parent;
    }
}

template <typename T>
void RBTree<T>::Prev()
{
    /* If we have a left-hand child, go down and then right as far
       as we can. */
    if (current->rb_left) {
        current = current->rb_left;
        while (current->rb_right)
            current=current->rb_right;
        return;
    }

    /* No left-hand children. Go up till we find an ancestor which
       is a right-hand child of its parent */
    while (current->rb_parent && current == current->rb_parent->rb_left)
        current = current->rb_parent;

    if (current == root) {
        m_IsFirst = true;
    }

    if (current->rb_parent) {
        current = current->rb_parent;
    }
}

template <typename T>
T* CPool<T>::Get()
{
    T* returned;
    if (FreeHeader) {
        returned = FreeHeader;
        FreeHeader->Remove(&FreeHeader);
    }
    else {
        returned = new T;
    }
	returned->Reset();
    return returned;
}

template <typename T>
void CPool<T>::Release(T* t)
{
    if (FreeHeader) {
        FreeHeader->InsertAfter(t);
    }
    else {
        FreeHeader = t;
    }
}

template <typename T>
CPool<T>::CPool()
{
	FreeHeader = 0;
}

template <typename T>
CPool<T>::~CPool()
{
    T* temp;
    while (FreeHeader) {
        temp = FreeHeader;
        FreeHeader = FreeHeader->GetNext();
        delete temp;
    }
}


template <typename T>
xr_state CXrBiLinkList<T>::AddNode(T*  targetNode, T* node, InsertFlag flag)
{
	if (!node) return XR_FAILED;

	if (!m_pHead) {
		m_pTail = m_pHead = node;
		return XR_OK;
	}

	if (flag == InsertFlag_Default) {
		m_pTail->InsertAfter(node);
		m_pTail = node;
		return XR_OK;
	}

	if (targetNode) {
		if (flag == InsertFlag_SiblingBefore) {
			targetNode->InsertBefore(node);
			if (m_pHead == targetNode) {
				m_pHead = node;
			}
			return XR_OK;
		}
		if (flag == InsertFlag_SiblingAfter) {
			targetNode->InsertAfter(node);
			if (m_pTail == targetNode) {
				m_pTail = node;
			}
			return XR_OK;
		}
		return XR_OK;
	}
	else return XR_FAILED;
}

template <typename T>
T* CXrBiLinkList<T>::Extract()
{
	if (!m_pHead) return NULL;
	T* returned = m_pHead;
	m_pHead = returned->GetNext();
	if (m_pHead) m_pHead->SetPrev(NULL);
	else {
		m_pTail = NULL;
	}
	returned->SetNext(NULL);
	return returned;
}

template <typename T>
xr_state CXrBiLinkList<T>::removeNode(T* node)
{
	if (!node) return XR_FAILED;

	if (m_pHead == node) {
		m_pHead = node->GetNext();
	}
	if (m_pTail == node) {
		m_pTail = node->GetPrev();
	}
	node->CBiLinkNode<T>::Remove();
	return XR_OK;
}
template <typename T>
xr_state CXrBiLinkList<T>::MoveToAfter(T*  targetNode, T* node, InsertFlag flag)
{
	if (!node) return XR_FAILED;

	if(targetNode)
	{
		if (flag == InsertFlag_SiblingAfter) 
		{
			targetNode->MoveToAfter(node);
			if (m_pTail == targetNode) {
				m_pTail = node;
			}

			return XR_OK;
		}
		return XR_OK;
	}
	else
	{
		return XR_FAILED;
	}
}

template <typename T>
xr_state CXrTree<T>::AddNode(T*  targetNode, T* node, InsertFlag flag)
{
	if (!node) return XR_FAILED;


	if (!CXrBiLinkList<T>::m_pHead) {
		CXrBiLinkList<T>::m_pTail = CXrBiLinkList<T>::m_pHead = node;
		return XR_OK;
	}

	if (flag == InsertFlag_Default) {
		CXrBiLinkList<T>::m_pTail->InsertAfter(node);
		CXrBiLinkList<T>::m_pTail = node;
		return XR_OK;
	}

	if (targetNode) {
		if (flag == InsertFlag_Child) {
			targetNode->AppendAsChild(node);
			return XR_OK;
		}
		if (flag == InsertFlag_SiblingBefore) {
			targetNode->InsertBefore(node);
			if (CXrBiLinkList<T>::m_pHead == targetNode) {
				CXrBiLinkList<T>::m_pHead = node;
			}
			return XR_OK;
		}
		if (flag == InsertFlag_SiblingAfter) {
			targetNode->InsertAfter(node);
			if (CXrBiLinkList<T>::m_pTail == targetNode) {
				CXrBiLinkList<T>::m_pTail = node;
			}
			return XR_OK;
		}
		return XR_OK;
	}
	else return XR_FAILED;
}

template <typename T>
xr_state CXrTree<T>::IsolateNode(T* node)
{
	if (!node) return XR_FAILED;
	if (CXrBiLinkList<T>::m_pHead == node) {
		CXrBiLinkList<T>::m_pHead = node->GetNext();
	}
	if (CXrBiLinkList<T>::m_pTail == node) {
		CXrBiLinkList<T>::m_pTail = node->GetPrev();
	}
	node->Isolate();
	return XR_OK;
}

//template <typename T>
//xr_state CXrTree<T>::RemoveNode(T* node)
//{
//	if (!node) return XR_FAILED;
//	if (CXrBiLinkList<T>::m_pHead == node) {
//		CXrBiLinkList<T>::m_pHead = node->GetNext();
//	}
//	if (CXrBiLinkList<T>::m_pTail == node) {
//		CXrBiLinkList<T>::m_pTail = node->GetPrev();
//	}
//	node->Remove();
//	return XR_OK;
//}
