#ifndef _Extended_queue_h_
#define _Extended_queue_h_

#include "queue.h"

class Extended_queue : public Queue {
public:
	bool full() const;
	int size() const;
	void clear();
	Error_code serve_and_retrieve(Queue_entry &item);

	void print();
};

#endif // _Extended_queue_h_