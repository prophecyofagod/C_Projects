/*	Mario Saiz
	Project 3: ProducerConsumer
	OS: Professor Gallmeier
*/


//#include <iostream>
#include "ProducerConsumer.h"
#define BUFFER_SIZE 5
#include <stdlib.h>
#include <stdio.h>
#include "buffer.h"
#include <pthread.h>
#include <semaphore.h>
#define RAND_DIVISOR 100000000
#define TRUE 1

static int Buffer[BUFFER_SIZE]; 
	static int In  = 0;                             
		static int Out = 0;                             
static Semaphore NotFull("NotFull", BUFFER_SIZE);
	static Semaphore NotEmpty("NotEmpty", 0);
		static Semaphore BufferLock("BufferLock", 1);   
strstream *Filler(int n) {
	int  i;
		strstream *Space;
			Space = new strstream;
	for (i = 0; i < n; i++)
		(*Space) << ' ';
			(*Space) << '\0';
				return Space;
} 
ProducerThread::ProducerThread(int No, int numberofdata)
               : Number(No), NumberOfData(numberofdata) {
     ThreadName.seekp(0, ios::beg);
     ThreadName << "Producer" << No << '\0';
};
ConsumerThread::ConsumerThread(int No)
				: Number(No) {
	ThreadName.seekp(0, ios::beg);
	ThreadName << "Consumer" << No << '\0';
} 
void ProducerThread::ThreadFunc() {
	Thread::ThreadFunc();
		int data;
			strstream *Space; 
				Space=Filler(4);
     for (int i = 1; i <= NumberOfData; i++) {
          Delay();
          NotFull.Wait();     
          BufferLock.Wait();       
          data = rand() % 100 + 1000 * Number;  
          Buffer[In] = data;       
          cout << Space->str() << ThreadName.str() << " deposited "
               << data << " to the buffer" << endl;
          In = (In + 1) % BUFFER_SIZE;    
          BufferLock.Signal();     
          NotEmpty.Signal();  
     }

 
     Delay();                      
     NotFull.Wait();               
     BufferLock.Wait();        
     Buffer[In] = END;             
     cout << Space->str() << ThreadName.str()
          << " deposited END and Exit" << endl;
     In = (In + 1) % BUFFER_SIZE;  
     BufferLock.Signal();       
     NotEmpty.Signal();          
     Exit();
}

 
void ConsumerThread::ThreadFunc()
{
     Thread::ThreadFunc();
     int data = 0 ;
     strstream *Space;

 
     Space=Filler(2);
     while (true) {
          Delay();
          NotEmpty.Wait();             
          BufferLock.Wait();            
          data = Buffer[Out];          
          if (data != END) {            
               cout << Space->str() << ThreadName.str()<< " received "
                    << data << " from the buffer" << endl;
               Out = (Out + 1) % BUFFER_SIZE;  
               BufferLock.Signal();            
               NotFull.Signal();        
          }
          else {
               cout << Space->str() << ThreadName.str()
                    << " received END and exits" << endl;
               Out = (Out + 1) % BUFFER_SIZE;
               BufferLock.Signal();
               NotFull.Signal();
               break;
        }
    }
    Exit();
}
