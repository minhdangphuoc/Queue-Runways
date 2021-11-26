#ifndef _queue_h_
#define _queue_h_

#include "Utility.h"
#include "Plane.hpp"

typedef Plane Queue_entry;

const int maxqueue = 10; //  small value for testing

class Queue {
public:
   Queue();
   bool empty() const;
   Error_code serve();
   Error_code append(const Queue_entry &item);
   Error_code retrieve(Queue_entry &item) const;
   

protected:
   int count;
   int front, rear;
   Queue_entry entry[maxqueue];
};

#endif // _queue_h_