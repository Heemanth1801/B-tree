#include<bits/stdc++.h>
#define inf 10000
using namespace std;

int t,d;

class node
{
public:
    node(int a)
    {
        int i;
        code=a;
        full=false;
        occupied=0;
        children = (node**)(malloc(sizeof(node*)*(2*t+3)));
        for(i=0;i<=2*t+2;i++){
            children[i]=nullptr;
        }
        parent = nullptr;
        if(code==0){
            values = (int*)malloc((2*t+2)*sizeof(int));
            capacity=2*t+1;
            for(i=0;i<=2*t+1;i++){
                values[i]=inf;
            }
        }
        else{
            values = (int*)malloc((2*d+1)*sizeof(int));
            capacity=2*d;
            for(i=0;i<=2*d;i++){
                values[i]=inf;
            }
        }
    }
    node* get_child(int a)
    {
        return children[a];
    }
    node* get_parent()
    {
        return parent;
    }
    void put_child(node* a,int index)
    {
        children[index] = a;
    }
    void put_parent(node* a)
    {
        parent = a;
    }
    int get_value(int index)
    {
        return values[index];
    }
    void put_value(int a,int index)
    {
        values[index] = a;
    }
    bool isfull(){
        if(occupied==capacity+1){
            full=true;
        }
        else{
            full=false;
        }
        return full;
    }
    int getcode(){
        return code;
    }
    int getoccupancy(){
        return occupied;
    }
    void increase_occupancy(){
        occupied++;
    }
    void decrease_occupancy(){
        occupied--;
    }
    int get_capacity(){
        return capacity;
    }

private:
    node** children;
    node *parent;
    int* values;
    int code;//0 for indexnode and 1 for datanode.
    int occupied;
    int capacity;
    bool full;
};

void printing(){
    cout<<"testing..."<<endl;
}

void printing_node(node* head){
    int i;
    for(i=0;i<head->getoccupancy();i++){
        cout<<head->get_value(i)<<" ";
    }
    cout<<endl;
}

void splitting(node* head,node*left,node*right,int value){
    //printing();
    //cout<<head->getcode()<<endl;
    if(head==nullptr){
            node* newnode = new node(0);
            newnode->put_value(value,0);
            newnode->increase_occupancy();
            newnode->put_child(left,0);
            newnode->put_child(right,1);
            newnode->put_parent(nullptr);
            right->put_parent(newnode);
            left->put_parent(newnode);
            //head=newnode;
            /*if(head==nullptr){
                cout<<"hi"<<endl;
            }*/
            return;
    }
    if(head->getcode()==0){
        int i,j;
        node* newnode = new node(0);
        for(i=0;i<head->getoccupancy();i++){
            if(value<head->get_value(i)){
                break;
            }
        }
        for(j=head->getoccupancy();j>i;j--){
            head->put_value(head->get_value(j-1),j);
            head->put_child(head->get_child(j),j+1);
        }
        head->put_value(value,i);
        head->put_child(left,i);
        head->put_child(right,i+1);
        head->increase_occupancy();
        if(head->isfull()){
            //printing();
            int i,keyvalue;
            node* newnode = new node(0);
            keyvalue=head->get_value(t);
            //printing();
            //cout<<keyvalue<<endl;
            head->put_value(inf,t);
            //printing();
            head->decrease_occupancy();
            //printing();

            //Bug is here.

            for(i=0;i<t+1;i++){
                //cout<<head->get_value(t+i+1)<<endl;
                newnode->put_value(head->get_value(t+i+1),i);
                newnode->put_child(head->get_child(t+i+1),i);
                (head->get_child(t+i+1))[0].put_parent(newnode);
                newnode->increase_occupancy();
                head->put_value(inf,t+i+1);
                head->put_child(nullptr,t+i+1);
                head->decrease_occupancy();
            }
            newnode->put_child(head->get_child(t+i+1),i);
            (head->get_child(t+i+1))[0].put_parent(newnode);
            head->put_child(nullptr,t+i+1);
            newnode->put_parent(head->get_parent());
            splitting(head->get_parent(),head,newnode,keyvalue);
            return;
        }
    }
    else{
        //printing();
        int i;
        node* newnode = new node(1);
        for(i=0;i<=d;i++){
            newnode->put_value(head->get_value(d+i),i);
            newnode->increase_occupancy();
            head->put_value(inf,d+i);
            head->decrease_occupancy();
        }
        //printing();
        newnode->put_parent(head->get_parent());
        splitting(head->get_parent(),head,newnode,newnode->get_value(0));
        return;
    }
}

void insertion(int value,node* head){
    if(head->get_child(0)==nullptr){
        //printing();
        int i,j;
        for(i=0;i<head->getoccupancy();i++){
            if(value<head->get_value(i)){
                break;
            }
        }
        for(j=head->getoccupancy();j>i;j--){
            head->put_value(head->get_value(j-1),j);
        }
        head->put_value(value,i);
        head->increase_occupancy();
        if(head->isfull()){
            //cout<<head->get_capacity()<<endl;
            //printing();
            splitting(head,nullptr,nullptr,value);
            return;
        }
    }
    else{
        int i;
        for(i=0;i<head->getoccupancy();i++){
            if(value<=head->get_value(i)){
                head=head->get_child(i);
                insertion(value,head);
                return;
            }
        }
        insertion(value,head->get_child(i));
    }
}

void counting(int& indexnodes,int& datanodes,node*head){
    if(head==nullptr){
        return;
    }
    if(head->getcode()==0){
        indexnodes++;
    }
    else{
        datanodes++;
    }
    int i;
    for(i=0;i<=head->getoccupancy();i++){
        counting(indexnodes,datanodes,head->get_child(i));
    }
    return;
}

void displaying_status(node* head){
    //printing();
    int datanodes=0,indexnodes=0,i;
    counting(indexnodes,datanodes,head);
    cout<<indexnodes<<" "<<datanodes<<" ";
    for(i=0;i<head->getoccupancy();i++){
        cout<<head->get_value(i)<<" ";
    }

    cout<<endl;
    /*
    for(i=0;i<=head->getoccupancy();i++){
        printing_node(head->get_child(i));
    }

    cout<<endl;
    */
}

int main(){
    int code,value;
    cin>>d>>t;
    node* head=new node(1);
    while(1){
        //printing();
        cin>>code;
        //cout<<code<<endl;
        switch(code){
            case 1: //printing();
                    cin>>value;insertion(value,head);
                    //printing();
                    //displaying_status(head);
                    while(head->get_parent()!=nullptr){
                        //printing();
                        //displaying_status(head);
                        head=head->get_parent();
                        //displaying_status(head->get_child(1));
                        //cout<<head->get_value(0)<<endl;
                        //cout<<head->getcode()<<endl;
                    }
                    //displaying_status(head);
                    //printing();
                    break;
            case 2: displaying_status(head);break;
            case 3: return 0;
        }
    }
    return 0;
}