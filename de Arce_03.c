#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Define a structure for the queue node
typedef struct QueueNode {
    char name[50]; // Customer's name
    float totalPayment; // Total amount to be paid
    struct QueueNode* next;
} QueueNode; // Add a semicolon here

// Define a structure for the queue
typedef struct {
    QueueNode* front;
    QueueNode* rear;
} Queue;

// Function prototypes
Queue* INIT();
bool EMPTY(Queue* queue);
QueueNode* FRONT(Queue* queue);
void ENQUEUE(char name[], float totalPayment, Queue* queue);
QueueNode DEQUEUE(Queue* queue);
void serveCustomer(Queue* queue);

int main() {
    Queue* queue = INIT();
    int choice;
    int numCustomers = 0;//Count number of customers

    do {
        printf("\nNumber of customers: %d\n", numCustomers);
        printf("\nKCC Counter 0:\n");
        printf("[1] Fall in line\n");
        printf("[2] Serve customer\n");
        printf("[3] Next customer\n");
        printf("[4] Closing time\n");
        printf("[0] Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: 
                char name[50];
                float totalPayment;
                numCustomers++;//Add customers

                printf("Enter customer's name: ");
                scanf("%s", name);
                printf("Enter total amount payable: ");
                scanf("%f", &totalPayment);
                ENQUEUE(name, totalPayment, queue);
                system("cls");
                break;
            case 2:
                numCustomers--;
                system("cls");
                serveCustomer(queue);
                break;
            case 3:
                system("cls");
                if (!EMPTY(queue)) {
                    QueueNode* nextCustomer = FRONT(queue);
                    printf("Next order: For %s with total amount payable of %.4f.\n", nextCustomer->name, nextCustomer->totalPayment);
                } else {
                    printf("The QUEUE is EMPTY. No orders to serve.\n");
                }
                break;
            case 4:
                numCustomers = 0;//Serve all customers
                system("cls");
                printf("Closing time. Serving remaining customers:\n");
                while (!EMPTY(queue)) {
                    serveCustomer(queue);
                }
                printf("All customers have been served.\n");
                break;
            case 0:
                system("cls");
                printf("Exiting the checkout system.\n");
                break;
            default:
                system("cls");
                printf("Invalid choice. Please enter a valid option.\n");
                break;
        }
    } while (choice != 0);

    return 0;
}

// Function to initialize an empty queue
Queue* INIT() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    if (queue == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}

// Function to check if the queue is empty
bool EMPTY(Queue* queue) {
    if (queue->front == NULL){
        return true;
    }
    else{
        return false;
    }
}

// Function to return a copy of the front item of the queue
QueueNode* FRONT(Queue* queue) {
    if (EMPTY(queue)) {
        printf("The QUEUE is EMPTY. No order to serve.\n");
        exit(1);
    }
    return queue->front;
}

// Function to insert an item into the queue
void ENQUEUE(char name[], float totalPayment, Queue* queue) {
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    strcpy(newNode->name, name);
    newNode->totalPayment = totalPayment;
    newNode->next = NULL;
    
    if (EMPTY(queue)) {
        queue->front = newNode;
    } else {
        queue->rear->next = newNode;
    }
    queue->rear = newNode;
}

// Function to remove and return the front item of the queue
QueueNode DEQUEUE(Queue* queue) {
    if (EMPTY(queue)) {
        printf("The QUEUE is EMPTY. No orders to serve.\n");
        exit(1);
    }
    QueueNode* temp = queue->front;
    QueueNode frontData = *temp;
    queue->front = queue->front->next;
    free(temp);
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    return frontData;
}

// Function to serve the next customer
void serveCustomer(Queue* queue) {
    if (!EMPTY(queue)) {
        QueueNode customer = DEQUEUE(queue);
        printf("Now serving %s with total amount payable of %.4f.\n", customer.name, customer.totalPayment);
    } else {
        printf("The QUEUE is EMPTY. No orders to serve.\n");
    }
}