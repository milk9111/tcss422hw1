/*
	10/1/2017
	Authors: Connor Lundberg, Gardner Gomes
	
	In this assignment we are creating a PCB (Process Control Block), ReadyQueue, and 
	PriorityQueue. Each is made in sequence and then used to make the next one. The PCB
	is being held within the ReadyQueue, and the PriorityQueue holds 16 ReadyQueues. 
	This is going to be used for scheduling in the final OS project.
	
	In this file we are defining the functions declared in readyqueue.h. This will consist of
	a constructor, initializer, Enqueue, Dequeue, isEmpty, along
	with whatever other miscellaneous functions we may need. It also includes a main
	function to test the ReadyQueue and its functions.
*/

//includes
#include "readyqueue.h"
// #include "pcb.h"


/*
    Constructor for the readyQueueNode
*/
ReadyQueueNode rdyQueueNodeConstructor() {
    ReadyQueueNode myNode = (ReadyQueueNode) malloc(sizeof(rdyQueueNode_s));
    rdyQueueNodeInitializer(myNode);
    return myNode;
}


void rdyQueueNodeDeconstructor(ReadyQueueNode thisNode) {
    pcbDeconstructor(thisNode->myPCB);
	free(thisNode);
}


void rdyQueueNodeInitializer(ReadyQueueNode theNode) {
    theNode->next = 0;
    theNode->myPCB = 0;
}


void rdyQueueNodeSetPCB(ReadyQueueNode theNode, PCB thePCB) {
    theNode->myPCB = thePCB;
}


/* 
    Sets the Value for the next Node
*/
void rdyQueueNodeSetNext(ReadyQueueNode theNode, ReadyQueueNode nextNode) {
    theNode->next = nextNode;
}
/*
    q_isEmpty Return 1 if the queue is empty 
*/
int q_isEmpty(ReadyQueue theQueue) {
    int isEmpty = 0;
    if(!theQueue->top) {
        isEmpty = 1;
    }
    return isEmpty;
}

/*
    Constructor for the Ready Queue
*/
ReadyQueue readyQueueConstructor() {
	ReadyQueue myReadyQueue = (ReadyQueue) malloc(sizeof(readyQueue_s));
    readyQueueInitializer(myReadyQueue);
	return myReadyQueue;
}


void readyQueueDeconstructor(ReadyQueue theQueue) {
	while(!q_isEmpty(theQueue)) {
		ReadyQueueNode node = q_dequeue(theQueue);
		rdyQueueNodeDeconstructor(node);
	}
	free(theQueue);
}


/*
    The Initializer for the values of the ReadyQueue
*/
void readyQueueInitializer(ReadyQueue theQueue) {
    theQueue->top = 0;
    theQueue->bottom = 0;
}





/*
    sets the last nodes next value to the address of the node sent in as a paramater
    code 1 means it set the node properly.
*/
int q_enqueue(ReadyQueue theQueue, ReadyQueueNode theNode) {
    int success = 0;
    if(q_isEmpty(theQueue)) {
        theQueue->top = theNode;
        theQueue->bottom = theNode;
        success = 1;
        //set node to top
    } else {
        //if top has next bottom next == node
        //top next == node && bottom == node
        if(theQueue->top->next == 0) {
            theQueue->top->next = theNode;
            // printf("Enqueue top Next %x the Node %x",theQueue->top->next,theNode);
            theQueue->bottom = theNode;
            success = 1;
        } else {
			//should this be = instead of ==?
            theQueue->bottom->next = theNode;
            success = 1;
        }
    }
    return success;
}


/*
    Dequeues the first node in the queue and returns the pointer to the caller.
    then it makes the next in the queue the top of queue.
*/
ReadyQueueNode q_dequeue(ReadyQueue theQueue) {
    ReadyQueueNode theTopNode;
    if(q_isEmpty(theQueue)) {
        theTopNode = 0;
    } else {
        theTopNode = theQueue->top;
        theQueue->top = theQueue->top->next;
    }
    return theTopNode;
}

void toStringReadyQueueNode(ReadyQueueNode theNode) {
    if (theNode->myPCB == 0) {
    } else {
        printf("|%d|",theNode->myPCB->pid);//Needs to be myPCB->pid eventually.
        if(theNode->next != 0) {
            printf("--->");
        } else {
            printf("--->NULL\n");
        }
    }
}
void toStringReadyQueue(ReadyQueue theQueue) {
    // printf("TOSTRINGQUEUE\n");
    if(theQueue->top == 0) {
        printf("NULL\n");
    } else {
        ReadyQueueNode temp = theQueue->top;
        // printf("%x or %x\n",temp->next, theQueue->top->next);
        while(temp->next != 0) {
            // printf("temp next %x\n",temp->next);
            toStringReadyQueueNode(temp);
            temp = temp->next;
        } 
        if(temp->next == 0) {
            toStringReadyQueueNode(temp);
        }
    }
}

void main() {
    ReadyQueue myQueue= readyQueueConstructor();
    printf("HELLO WORLD!!!!\n");
    // printf("%x\n",&myQueue);                            //Prints location of myQueue
    // printf("%x\n",myQueue->top);                        //prints address for pointer to top
    // printf("%d\n",q_isEmpty(myQueue));                   //prints result if empty
    ReadyQueueNode myNode1 = rdyQueueNodeConstructor();
    ReadyQueueNode myNode2 = rdyQueueNodeConstructor();
    ReadyQueueNode myNode3 = rdyQueueNodeConstructor();
    PCB PCB1 = pcbConstructor();
    PCB PCB2 = pcbConstructor();
    PCB PCB3 = pcbConstructor();
    rdyQueueNodeSetPCB(myNode1,PCB1);
    rdyQueueNodeSetPCB(myNode2,PCB2);
    rdyQueueNodeSetPCB(myNode3,PCB3);
    printf("%d, %d, %d\n",&PCB1->pid,&PCB2->pid,&PCB3->pid);
    printf("node1 = %x,node2 =  %x,node3 =  %x\n",myNode1,myNode2,myNode3);
    // printf("Nodes %x %x %x\n", myNode1,myNode2,myNode3); //address of all nodes
    // printf("Node %x\n", myNode1);                        //address of first node
    // printf("Node 1 Next = %x\n", myNode1->next);           //address of node 1 next
    int x = q_enqueue(myQueue, myNode1);                //enqueue node 1 to top
    x = q_enqueue(myQueue, myNode2);
    // printf("Node 1 Next = %x\n", myNode1->next);          
    x = q_enqueue(myQueue, myNode3);
    // printf("top = %x\n",myQueue->top);                 //checking top before dequeue
    // q_dequeue(myQueue);                                //dequeing         
    // printf("top next = %x\n",myQueue->top->next);                 //checking new top

    // toStringReadyQueueNode(myNode1);
    toStringReadyQueue(myQueue);
    // printf("\n%x\n",myQueue->top);
    printf("Completed");
}