#include <iostream>
using namespace std;

template<class type>
class Linked_List
{
protected:
    struct node
    {
        type iteam;
        node * next;
        node *prev;
    };
    int length;
    node *head;
    node *tail;

public:

    Linked_List()
    {
        length = 0;
        head = tail = NULL;
    }
    Linked_List(type value, int initial_size)
    {
        length=0;
        node *newnode = new node;
        newnode->iteam = value;
        head = tail = newnode;
        length++;
        for(int i=1; i<initial_size; i++)
        {
            this->push_back(value);
        }
    }
    void push_back(type value)
    {
        node *newnode = new node;
        node * dummy = new node;
        newnode->iteam = value;
        newnode->next = dummy;
        if(length==0)
        {
            head = tail = newnode;
        }
        else
        {
            newnode->prev = tail;
            tail->next = newnode;
            tail = newnode;
        }
        dummy->prev = tail;
        length++;
    }

    int size()
    {
        return length;
    }

    type  operator [](int idx)const
    {
        if (idx>=length||idx<0)
        {
            return NULL;
        }
        if (idx==0)
            return head->iteam;
        if (idx==length-1)
            return tail->iteam;
        node* tmp=head;
        while (idx--)
        {
            tmp=tmp->next;
        }
        return tmp->iteam;
    }

    type back()
    {
        return tail->iteam;
    }
    ~Linked_List()
    {
        while(head!=NULL&&head != tail->next)
        {
            node* curr = head;
            node* nextToDelete = curr->next;
            head = nextToDelete;
            delete curr;
        }
    }
};

struct TrieNode {
    char ch;
    int id;
    Linked_List<TrieNode*>Child;
    TrieNode()
    {
        this->id = -1;
    }

    TrieNode(char c)
    {
        this->id = -1;
        this->ch = c;
    }
    TrieNode(char c, int id)
    {
        this->id = id;
        this->ch = c;
    }

};

char* substr(char arr[], int start, int len)
{
    char* res = new char[len + 1];

    for (int i = 0; i < len; i++)
        res[i] = *(arr + start + i);

    res[len] = '\0';
    return res;
}
int Size(const char str[])
{
    int size=0;
    for (int i = 0; str[i]!='\0' ; ++i)
    {
        size++;
    }
    return size;
}

class SuffixTrie {
public:
    TrieNode *Head;
    char *s;
    int size;
    SuffixTrie(char *arr)
    {
        this->s = arr;
        size=Size(s);
        Head = new TrieNode();
        insert(this->s);
    }


    int get_idx(TrieNode* tmp, char ch)
    {
        int idx=-1;
        for (int j = 0; j <tmp->Child.size() ; ++j)
        {
            if (tmp->Child[j]->ch==ch)
            {
                idx=j;
                break;
            }
        }
        return idx;
    }

    void insert(char *str)
    {
        int si=Size(str);
        if ( si==0 )
            return;

        TrieNode *tmp = Head;

        for (int i = 0; i<si; ++i)
        {
            char currch = str[i];

            if (get_idx(tmp,currch)==-1)
            {
                TrieNode *newchild = new TrieNode(currch);

                tmp->Child.push_back(newchild);
                //  cout<<currch<<'\n';
            }

            tmp = tmp->Child[get_idx(tmp,currch)];
        }

        tmp->Child.push_back( new TrieNode(str[si - 1])) ;
        tmp = tmp->Child.back();

        int idx = this->size - si;

        tmp->id = idx;

        str = substr(str,1,si);
        insert(str);
    }

    void get_ids(TrieNode *node)
    {
        if (!node)
            return;

        if (node->id != -1)
            cout << node->id << ' ';

        for (int i = 0; i < node->Child.size(); i++)
        {
            get_ids(node->Child[i]);
        }

    }

    void Search(const char *str)
    {
        TrieNode *tmp = Head;
        int si=Size(str);
        for (int i = 0; i < si; ++i)
        {
            int currch = str[i];
            int idx=get_idx(tmp,currch);
            if (idx!=-1)
            {
                tmp = tmp->Child[idx];
            }
            else
            {
                cout << "Not Found\n";
                return;
            }
        }
        get_ids(tmp);
        cout<<'\n';
    }

    void releaseSpace(TrieNode *node)
    {
        TrieNode *tmp = node;
        for (int i = 0; i < node->Child.size(); ++i)
        {
            if (tmp->Child[i] != NULL)
                releaseSpace(tmp->Child[i]);
        }
        delete tmp;
    }
    ~SuffixTrie()
    {
        releaseSpace(Head);
    }
};