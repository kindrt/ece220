// public methods

template <class T>
List<T>::List() : head_(NULL), length_(0) { }

template <class T>
List<T>::List(List<T> const& other) {
    copy(other);
}

template <class T>
List<T>& List<T>::operator=(List<T> const& rhs) {
    if (this != &rhs) {
        clear();
        copy(rhs);
    }
    return *this;
}

template <class T>
List<T>::~List() {
    clear();
}

template <class T>
int List<T>::size() const {
    return length_;
}

template <class T>
bool List<T>::empty() const {
    return head_ == NULL && length_ == 0;
}


template <class T>
void List<T>::insertFront(T const& ndata) {
    ListNode* newnode = new ListNode(ndata);
    length_++;
    if (head_ == NULL) {
        head_ = newnode;
        return;
    }
    newnode->next = head_;
    head_ = newnode;
}


template <class T>
void List<T>::removeFront() {
    ListNode* deletor;
    if (head_ != NULL) {
        deletor = head_;
        head_ = head_->next;
        delete deletor;
    }
}

// private methods

template <class T>
void List<T>::copy(List<T> const& other) {
    // set up the default, empty list
    head_ = NULL;
    length_ = 0;
    ListNode* tmp_head = NULL;

    // if we have things to copy
    if (!other.empty()) {
        ListNode* curr = other.head_;

        // iterate down the parameter list
        while (curr != NULL) {
            ListNode* node = new ListNode(curr->data);

            if (head_ == NULL) {
                head_ = node;
                tmp_head = head_;
            }
            else {
                tmp_head->next = node;
                tmp_head = tmp_head->next;
            }
                
            curr = curr->next;
        }

        length_ = other.length_;
    }
}


template <class T>
void List<T>::clear() {
    ListNode* deletor;
    while (head_ != NULL) {
        deletor = head_;
        head_ = head_->next;
        delete deletor;
    }
}

template <class T>
void List<T>::print(ostream& os) const {
    os << "<";
    ListNode* curr = head_;
    while (curr != NULL) {
        os << " " << curr->data;
        curr = curr->next;
    }
    os << " >";
}


// overloaded operator<<
template <class T>
ostream& operator<<(ostream& os, const List<T>& list) {
    list.print(os);
    return os;
}
