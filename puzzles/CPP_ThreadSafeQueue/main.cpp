/**
General idea of a thread safe queue or list

write/push:
    lock the mutex
        add the event/item to the queue
        signal the condition variable
    unlock the mutex

read/pop
    lock the mutex
        while(queue is empty)
            wait on condition variable
        remove the item from the queue
    unlock the mutex
    return the item
*/

#include <iostream>
#include <mutex>
#include <condition_variable>
#include <deque>
using namespace std;

template <typename T>
class queue
{
private:
    mutex               d_mutex;
    condition_variable  d_condition;
    deque<T>            d_queue;

public:
    void push(T const& value){
        {
            unique_lock<mutex> lock(this->d_mutex);
            d_queue.push_front(value);    
        }       
        this->d_condition.notify_one();
    }

    T pop(){
        unique_lock<mutex> lock(this->d_mutex);
        this->d_condition.wait(lock, [=]{return !this->d_queue.empty();});
        T rc(move(this->d_queue.back()));
        this->d_queue.pop_back();
        return rc;
    }
};

int main(){
    
    queue<int> q;
    cout << "Pushing 10 ..." << endl;
    q.push(10);
    cout << "Popped value: " << q.pop() << endl;
    return 0;
}
