#include "Priority_list.hpp"

int heuristic(Vertex *x, char ch){
    if(x->getName() - ch > 0) return x->getName() - ch;
    else return ch - x->getName();
}

Priority_list::Priority_list(char ch){
    head = nullptr;
    end = ch;
}

void Priority_list::push(Vertex *ver, double prior){
    prior += heuristic(ver,end);
    if(head == nullptr){
        head = new item(prior,ver,nullptr);
    }
    else if(prior < head->priority){
        item *tmp = new item(prior,ver,head);
        head = tmp;
    }
    else{
        item *tmp = head;
        bool inserted = false;
        
        while(tmp->next != nullptr){
            if(tmp->next->priority <= prior){
                tmp = tmp->next;
                continue;
            }
            else{
                item *x = tmp->next;
                tmp->next = new item(prior,ver,nullptr);
                tmp->next->next = x;
                inserted = true;
                break;
            }
        }
        if(!inserted){
            tmp->next = new item(prior,ver,nullptr);
        }
    }
}

void Priority_list::pop(Vertex *ver){
    if(ver == head->ver){
        item *tmp = head->next;
        delete head;
        head = tmp;
    }
    if(head != nullptr){
        item *tmp = head;
        while(tmp->next != nullptr){
            if(tmp->next->ver == ver){
                item *del = tmp->next;
                tmp->next = tmp->next->next;
                delete del;
                break;
            }
            tmp = tmp->next;
        }
    }
}

Vertex* Priority_list::pop(){
    if(head != nullptr){
        Vertex *finded = head->ver;
        item* del = head;
        head = head->next;
        delete del;
        return finded;
    }
    else return nullptr;
}

