#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <ctime>

using namespace std;

struct List
{
    int id;
    List *prev, *next;

    List () {}

    List(int id)
    {
        this->id=id;
    }
};
List *head;
List *tail;

void add(int *id)
{


    List *bidirectional=new List(*id);
    List *helper=head;
    if(head==NULL)
    {
        bidirectional->prev=0;
        bidirectional->next=0;
        head=bidirectional;
        tail=bidirectional;
    }
    else
    {
        while(helper!=NULL)
        {
            if(*id<=helper->id)
            {
                break;
            }
            else
            {
                helper=helper->next;
            }
        }
        if(helper==head)
        {
            bidirectional->next=helper;
            bidirectional->prev=0;
            bidirectional->next->prev=bidirectional;
            head=bidirectional;
        }
        else if(helper==NULL)
        {
            bidirectional->prev=tail;
            bidirectional->next=0;
            tail=bidirectional;
            tail->prev->next=tail;

        }
        else
        {
            bidirectional->next=helper;
            bidirectional->prev=helper->prev;
            bidirectional->prev->next=bidirectional;
            bidirectional->next->prev=bidirectional;
        }
    }

}
void search(int id)
{
    int counter=1;

    List *helper = head;
    if(helper==NULL)
        cout<<"No items in the list."<<endl;
    while(helper)
    {
        if(helper->id!=id)
        {
            helper=helper->next;
            counter++;
            if(helper==NULL)
                cout<<"There is no such ID in the list"<<endl;
        }
        else
        {
            cout<<"Your item is on "<<counter<<" position on the list"<<endl<<endl;
            break;
        }
    }
}
void search_time(int id)
{
    int licznik=1;

    List *helper = head;
    if(helper==NULL)
        cout<<"No items in the list."<<endl;
    while(helper)
    {
        if(helper->id!=id)
        {
            helper=helper->next;
            licznik++;
            if(helper==NULL)
                cout<<"There is no such ID in the list"<<endl;
        }
        else
        {
            // cout << "Your item is on " << counter << " position on the list" << endl << endl;
            break;
        }
    }
}




void deleting_item()
{
    int id;
    List *helper=head;

    cout<<" Enter ID you want to delete: "<<endl;
    cin>>id;
    if(helper==NULL)
        cout<<"No items in the list."<<endl;
    while(helper)
    {
        if(helper->id!=id)
        {
            helper=helper->next;
            if(helper==NULL)
                cout<<"There is no such ID in the list"<<endl;
        }
        else
        {
            if(helper->prev)
                helper->prev->next=helper->next;
            else
                head=helper->next;
            if(helper->next)
                helper->next->prev=helper->prev;
            else
                tail=helper->prev;
            helper=NULL;
            cout<<"Object has been deleted."<<endl<<endl;
        }
    }
    delete helper;
}
void deleting_all()
{

    List *helper=head;
    while(helper!=NULL)
    {
        head=helper->next;
        delete helper;
        helper=head;
    }
    cout<<"All objects have been deleted"<<endl;

}
void display()
{

    List *helper=head;
    if(helper==NULL)
        cout<<"No items in the list."<<endl;

    cout<<"Bidirectional list items: "<<endl;
    while(helper)
    {
        cout<<helper->id<<"\t";
        helper=helper->next;
    }
    cout<<endl<<endl;
}
void random(int tab [], int n)
{
    srand(time(NULL));
    for (int i = 0; i < n; i++)
    {
        tab[i] = rand() % 2147483647;
    }
}
/////////////////////////////////////////////////////////////////////////

struct AVL
{
    AVL *up, *left, *right;
    int id;
    int fac;
    AVL() {}
    AVL(int id, int fac)
    {
        this->id=id;
        this->fac=fac;
    }
};
void RR(AVL*&root, AVL *a)
{

    AVL *b=a->right;
    AVL *c=a->up;
    a->right=b->left;
    if(a->right)
        a->right->up=a;

    b->left=a;
    b->up=c;
    a->up=b;

    if(c)
    {
        if(c->left==a)
            c->left=b;
        else
            c->right=b;
    }
    else
        root=b;
    if(b->fac==-1)
        a->fac=b->fac=0;
    else
    {
        a->fac=-1;
        b->fac=1;
    }
}

void LL(AVL *&root, AVL *a)
{

    AVL *b=a->left;
    AVL *c=a->up;
    a->left=b->right;
    if(a->left)
        a->left->up=a;

    b->right=a;
    b->up=c;
    a->up=b;
    if(c)
    {
        if(c->left==a)
            c->left=b;
        else c->right=b;
    }
    else
        root=b;
    if(b->fac==1)
        a->fac=b->fac=0;
    else
    {
        a->fac=1;
        b->fac=-1;
    }
}
void RL(AVL * & root, AVL *a)
{

    AVL *b=a->right;
    AVL *c=b->left;
    AVL *d=a->up;
    b->left=c->right;
    if(b->left)
        b->left->up=b;

    a->right=c->left;
    if(a->right)
        a->right->up=a;

    c->left=a;
    c->right=b;
    a->up=b->up=c;
    c->up=d;

    if(d)
    {
        if(d->left==a)
            d->left=c;
        else
            d->right=c;
    }
    else
        root = c;

    if(c->fac==-1)
        a->fac=1;
    else
        a->fac=0;
    if(c->fac==1)
        b->fac=-1;
    else
        b->fac=0;
    c->fac=0;


}
void LR(AVL * & root, AVL *a)
{

    AVL *b=a->left;
    AVL *c=b->right;
    AVL *d=a->up;

    b->right=c->left;
    if(b->right)
        b->right->up=b;

    a->left=c->right;
    if(a->left)
        a->left->up=a;

    c->right=a;
    c->left=b;
    a->up=b->up=c;
    c->up=d;
    if(d)
    {
        if(d->left==a)
            d->left=c;
        else
            d->right=c;
    }
    else
        root = c;

    if(c->fac==-1)
        b->fac=1;
    else
        b->fac=0;
    if(c->fac==1)
        a->fac=-1;
    else
        a->fac=0;
    c->fac=0;

}


void addAVL(AVL*&root, int id)
{

    bool n;
    AVL *p, *r;
    AVL *new_item=new AVL(id, 0);
    new_item->up=NULL;
    new_item->left=NULL;
    new_item->right=NULL;

    p=root;

    if(p==NULL)
        root=new_item;
    else
    {
        while(true)
        {
            if(id<p->id)
            {
                if(p->left==NULL)
                {
                    p->left=new_item;
                    break;
                }
                p=p->left;
            }
            else
            {
                if(p->right==NULL)
                {
                    p->right=new_item;
                    break;
                }
                p=p->right;
            }
        }

        new_item->up=p;

        if(p->fac)
            p->fac=0;
        else
        {
            if(p->left==new_item)
            {
                p->fac=1;
            }
            else
                p->fac=-1;
            r=p->up;
            n=false;
            while(r)
            {
                if(r->fac)
                {
                    n=true;
                    break;
                }
                if(r->left==p)
                    r->fac=1;
                else
                    r->fac=-1;
                p=r;
                r=r->up;

            }
            if(n)
            {
                if(r->fac==1)
                {
                    if(r->right==p)
                        r->fac=0;
                    else if(p->fac==-1)
                        LR(root, r);
                    else
                        LL(root, r);
                }
                else
                {
                    if(r->left==p)
                        r->fac=0;
                    else if(p->fac==1)
                        RL(root, r);
                    else
                        RR(root, r);
                }
            }
        }
    }
}


int *searching_AVL (AVL*& root, int id)
{

    AVL *p=root;

    for(;;)
    {
        if(!p)
        {
            cout<<"No object"<<endl;
            //   return 0;
            break;
        }
        if(id>p->id)
            p=p->right;
        if(id<p->id)
            p=p->left;
        if (id==p->id)
        {
            //cout<<"Object found!"<<endl;
//            return 1;
            break;

        }
    }

}
AVL *predecessor(AVL *p)
{
    AVL *k;
    if(p)
    {
        if(p->left)
        {
            p=p->left;
            while(p->right)
                p=p->right;
        }
        else
            do
            {
                k=p;
                p=p->up;
            }
            while(p&&p->right!=k);
    }
    return p;
}

AVL* removeAVL(AVL * & root, AVL *p)
{

    AVL *x, *t, *z;
    bool n;

    if(p->left && p->right)
    {
        x=removeAVL(root, predecessor(p));
        n=false;
    }
    else
    {
        if(p->left)
        {
            x=p->right;
            p->left=NULL;
        }
        else
        {
            x=p->right;
            p->right=NULL;
        }
        p->fac=0;
        n=true;
    }
    if(x)
    {
        x->up=p->up;
        x->left=p->left;
        if(x->left)
            x->left->up=x;
        x->right=p->right;
        if(x->right)
            x->right->up=x;
        x->fac=p->fac;
    }
    if(p->up)
    {
        if(p->up->left==p)
            p->up->left=x;
        else
            p->up->right=x;
    }
    else
        root=x;
    if(n)
    {

        t=x;
        x=p->up;
        while(x)
        {
            if(!x->fac)
            {
                if(x->left==t)
                    x->fac=-1;
                else
                    x->fac=1;
                break;
            }
            else
            {
                if(((x->fac==1)&& (x->left==t))|| ((x->fac == -1)&&(x->right==t)))
                {
                    x->fac = 0;
                    t=x;
                    x=x->up;
                }
                else
                {
                    if(x->left==t)
                        z=x->right;
                    else
                        z=x->left;
                    if(!z->fac)
                    {
                        if(x->fac==1)
                            LL(root, x);
                        else
                            RR(root, x);
                        break;
                    }
                    else if(x->fac == z->fac)
                    {
                        if(x->fac==1)
                            LL(root, x);
                        else
                            RR(root, x);
                        t=z;
                        x=z->up;
                    }
                    else
                    {
                        if(x->fac==1)
                            LR(root, x);
                        else
                            RL(root,x);
                        t=x->up;
                        x=t->up;
                    }

                }
            }

        }
    }
    return p;

}

void preorder(AVL *p)
{
    if(p)
    {
        cout<<p->id<<" ,";
        preorder(p->left);
        preorder(p->right);
    }
}
void inorder(AVL *p)
{
    if(p)
    {
        inorder(p->left);
        cout<<p->id<<" ,";
        inorder(p->right);
    }

}
AVL *remove_p(AVL *& root, AVL *p)
{
    AVL *d;
    if(p!=NULL)
    {
        remove_p(root, p->left);
        remove_p(root, p->right);
        delete p;
    }

}


void binary_tree(int tab[],int n, AVL*&root)
{

    int t, l, p;
    t=n/2;
    l=t-1;
    p=n-1;
    if(n%2==0)
    {
        addAVL(root, tab[t]);
        while(l>0)
        {

            addAVL(root, tab[l/2]);
            l--;
            addAVL(root,tab[p/2]);
            p++;
        }
    }
    else
    {
        addAVL(root, tab[t]);
        while(l>=0)
        {
            addAVL(root, tab[l]);
            l--;
            addAVL(root,tab[p]);
            p++;
        }
    }


}

void path_display(AVL*& root, int id)
{

    AVL *p=root;
    while(p && (p->id!=id))
    {
        if(id<p->id)
        {
            cout<<p->id<<"  ";
            p=p->left;
        }
        if(id>p->id)
        {
            cout<<p->id<<"  ";
            p=p->right;
        }
    }

    if(id==p->id)
        cout<<p->id<<endl<<endl;
}



int main()
{
    int menu=0;
    int a, id;
    int listy=0;
    int b,n;
    int randomL;
    int help;
    double stoper;
    long time;
    clock_t start, stop;

    do
    {
        cout<<"If you want to work on lists, select 1"<<endl;
        cout<<"if you want to work on a AVL-tree, select 2"<<endl;
        cout<<"If you want to disable the program, select 3"<<endl;
        cin>>a;
        switch (a)
        {
        case 1:
            system("cls");
            do
            {
                cout<<"You work on lists now :)."<<endl;
                cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
                cout<<"1. Adding an item to the list"<<endl;
                cout<<"2. Item search"<<endl;
                cout<<"3. Deleting an item."<<endl;
                cout<<"4. Delete the entire list"<<endl;
                cout<<"5. Creating a list from a random array of elements"<<endl;
                cout<<"6. Displaying objects in the list"<<endl;
                cout<<"7. Adding n-elements to the list and searching n / 10."<<endl;
                cout<<"8. Return to main menu."<<endl;

                cin>>b;
                switch(b)
                {
                case 1:
                    system("cls");
                    cout<<"Enter the ID you want to add to the list."<<endl;
                    cin>>id;
                    add(&id);
                    display();
                    break;
                case 2:
                    system("cls");
                    cout<<"Enter the ID you want to find"<<endl;
                    cin>>id;
                    search(id);
                    break;
                case 3:
                    system("cls");
                    deleting_item();
                    break;
                case 4:
                {
                    system("cls");
                    start= clock();
                    deleting_all();
                    stop = clock();
                    time=(long)(stop-start);
                    cout<<"The time to delete the entire list is: "<<time<<"ms"<<endl;
                    break;
                }
                case 5:
                {
                    system("cls");
                    cout << "Enter the size of the array: " << endl;
                    cin >> n;
                    int *tab=new int [n];
                    random(tab, n);
                    for(int i=0; i<n; i++)
                    {
                        add(&tab[i]);
                    }
                    break;
                }
                case 6:
                    system("cls");
                    display();
                    break;
                case 8:
                    system("cls");
                    listy=1;
                    break;
                case 7:
                {
                    system("cls");
                    cout<<"Enter n:"<<endl;
                    cin>>n;
                    int *tab=new int[n];
                    random(tab,n);
                    start=clock();
                    for(int i=0; i<n; i++)
                    {
                        add(&tab[i]);
                    }
                    stop = clock();
                    long czas=(long)(stop-start);
                    cout<<"Addition time is: "<<czas<<"ms"<<endl;
                    start=clock();
                    for(int i=0; i<n/10; i++)
                    {
                        randomL=rand()%n;
                        search_time(tab[randomL]);
                    }
                    stop = clock();
                    czas=(long)(stop-start);
                    cout<<"Search time is: "<<czas<<"ms"<<endl;
                    break;
                }

                default:
                    system("cls");
                    cout<<"No options in the menu. Choose again"<<endl;
                    break;
                }
            }
            while(listy==0);
            break;
        case 2:
        {
            system("cls");
            listy=0;
            AVL *root=NULL;
            do
            {
                cout<<"You are now working on the AVL tree :)."<<endl;
                cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
                cout<<"1. Adding an item."<<endl;
                cout<<"2. Deleting an item."<<endl;
                cout<<"3. Item search with path display."<<endl;
                cout<<"4. Tree browsing: inorder and preorder."<<endl;
                cout<<"5. Creating a tree from a sorted array of elements - bisection method<<endl;
                cout<<"6. Tree removal - postorder."<<endl;
                cout<<"7. Adding n-elements to the tree and searching n/10"<<endl;
                cout<<"8 Return to main menu."<<endl;
                cin>>b;
                switch(b)
                {

                case 1:
                    system("cls");
                    cout<<"Enter the element you want to add to tree:"<<endl;
                    cin>>id;
                    addAVL(root, id);

                    break;
                case 2:
                {
                    system("cls");
                    cout<<"Enter the element you want to delete to tree "<<endl;
                    cin>>id;
                    AVL *p=root;
                    help=0;

                    while(p)
                    {
                        if(p==NULL)
                        {
                            cout<<"No item found"<<endl;
                            break;
                        }
                        if (p->id==id)
                        {
                            cout<<"Found object<<endl;
                            tak=1;
                            break;

                        }
                        else if(id>p->id)
                            p=p->right;
                        else if(id<p->id)
                            p=p->left;


                    }
                    if(help==1)
                        removeAVL(root, p);
                    else
                        cout<<"Nothing"<<endl;
                    break;
                }
                case 3:
                {

                    system("cls");
                    AVL *p=root;
                    cout<<"Enter ID you want to found:"<<endl;
                    cin>>id;
                    for(;;)
                    {
                        if(!p)
                        {
                            cout<<"No object."<<endl;
                            help=0;
                            break;
                        }
                        if(id>p->id)
                            p=p->right;
                        if(id<p->id)
                            p=p->left;
                        if (id==p->id)
                        {
                            cout<<"Found object"<<endl;
                            help=1;
                            break;

                        }
                    }

                    if(help==1)
                    {
                        path_display(root, id);
                    }

                    break;
                }
                case 4:
                    system ("cls");
                    cout<<"Preorder: "<<endl;
                    preorder(root);
                    cout<<endl<<endl;
                    cout<<"Inorder: "<<endl;
                    inorder(root);
                    cout<<endl<<endl;
                    break;
                case 5:
                {
                    system("cls");
                    cout<<"Enter the size of array:"<<endl;
                    cin>>n;
                    int *tab=new int [n];
                    for(int i=0; i<n; i++)
                    {
                        tab[i]=i;
                    }
                    binary_tree(tab, n, root);
                    break;
                }
                case 6:
                {
                    system("cls");
                    AVL *p=root;
                    start=clock();
                    remove_p(root,root);
                    root =NULL;
                    stop = clock();
                    time=(long)(stop-start);
                    cout<<"The whole tree has been removed"<<endl;
                    cout<<"Removal time is: "<<time<<"ms"<<endl;
                    break;
                }
                case 8:
                    system("cls");
                    listy=1;
                    break;

                case 7:
                {
                    system("cls");
                    cout<<"Enter n: "<<endl;
                    cin>>n;
                    int *tab=new int [n];
                    random(tab, n);
                    start=clock();
                    for(int i=0; i<n; i++)
                    {
                        addAVL(root, tab[i]);
                    }
                    stop = clock();
                    time=(long)(stop-start);
                    cout<<"Adding time is: "<<time<<"ms"<<endl;

                    start=clock();
                    for(int i=0; i<n/10; i++)
                    {
                        randomL=rand()%n;
                        searching_AVL(root, tab[randomL]);
                    }
                    stop = clock();
                    time=(long)(stop-start);
                    cout<<"Searching time is: "<<time<<"ms"<<endl;



                    break;
                }
                default:
                    system("cls");
                    cout<<"No options in the menu. Choose again"<<endl;
                    break;
                }
            }
            while(listy==0);
        }
        break;
        case 3:
            system("cls");
            cout<<"Thank you for using the program.Good night : )" <<endl;
            menu=1;
            break;

        default:
            system("cls");
            cout<< "Wrong option, choose again. "<<endl;
            break;
        }
    }
    while(menu==0);
    return 0;
}
