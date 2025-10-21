#ifndef linked_list

#define linked_list

typedef struct Node{
    void *element;
    struct Node *nextElement;

} Node;

typedef struct List{
    Node *head;
    Node *tail;
    int length;
    void (*push_back)(struct List *, void *);
    void (*push_front)(struct List *, void *);
    void (*pop)(struct List *, int);
    void (*cleanup)(struct List *);
} List;

void push_back(List *list, void *item);

void push_front(List *list, void *item);

void pop(List *list, int index);

void cleanup(List *list);

#endif
