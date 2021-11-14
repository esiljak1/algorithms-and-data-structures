#include <iostream>

struct ListNode{
    int val;
    ListNode *next;
};

ListNode* reverseListHelper(ListNode *current, ListNode *previous = nullptr){
    static ListNode *ret = nullptr;
    if(!current){
        return nullptr;
    }
    if(current -> next)
        reverseListHelper(current -> next, current);
    else
        ret = current;

    current -> next = previous;
    return ret;
}

ListNode* reverseList(ListNode *head){
    return reverseListHelper(head);
}

int main(){
    return 0;
}