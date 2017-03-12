#include "Socketfd.h"

Socketfd::Socketfd(){
    root = new SocketInode();
    inode = "";
}

void Socketfd::insert(string socketfd, int pid){
    cout << socketfd << "  " << pid << endl;
    SocketInode* current = root;
    for(unsigned i=0; i< socketfd.length(); i++){
        unsigned num = socketfd[i] - '0';
        if(NULL == current->trie[num]){
            current->trie[num] = new SocketInode();
        }
        current = current->trie[num];
    }

    current->count++;
    current->pid = pid;
}

void Socketfd::traverse(SocketInode* current){
    if(NULL == current){
        return;
    }

    for(int i=0; i<10; i++){
        if(NULL != current->trie[i]){
            inode += i+'0';
            if(-1 != current->trie[i]->pid){
                cout << inode << endl;
                cout <<"pid: " << current->trie[i]->pid << endl;
            }
            
            traverse(current->trie[i]);
            inode.erase(inode.length()-1);

        }
    }
}

SocketInode::SocketInode(){
    count = 0;
    pid = -1;
}
