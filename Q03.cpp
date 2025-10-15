/*As a software developer, you have been assigned the task of developing an application for a
busy restaurant that can handle a large volume of orders. To ensure that orders are processed in the
order they were received, what type of data structure would you choose to store the orders? Please
describe the necessary operations that would be required to add and remove orders from this data
structure, including the quantity of each item. Additionally, how would you prevent the data structure
from becoming full or empty to avoid overflow or underflow? Finally, explain your approach for
printing out all the processed orders in the order they were received to ensure that the restaurant staff
can efficiently fulfill the orders.*/

#include <iostream>
#include <string>
using namespace std;

class Order
{
    int orderId;
    string itemName;
    int quantity;
    string customerName;

public:
    Order()
    {
        orderId = 0;
        itemName = "";
        quantity = 0;
        customerName = "";
    }

    Order(int id, string item, int qty, string customer)
    {
        orderId = id;
        itemName = item;
        quantity = qty;
        customerName = customer;
    }

    void display()
    {
        cout << "Order ID: " << orderId
             << " | Customer: " << customerName
             << " | Item: " << itemName
             << " | Quantity: " << quantity << endl;
    }
};

class Queue
{
    Order *arr;
    int front;
    int rear;
    int capacity;
    int count;

public:
    Queue(int size)
    {
        capacity = size;
        arr = new Order[capacity];
        front = 0;
        rear = -1;
        count = 0;
    }

    ~Queue()
    {
        delete[] arr;
    }

    bool isFull()
    {
        return count == capacity;
    }

    bool isEmpty()
    {
        return count == 0;
    }

    int size()
    {
        return count;
    }

    void enqueue(Order order)
    {
        if (isFull())
        {
            cout << "Queue OverFlow!" << endl;
            cout << "Restaurant is Full At The Moment" << endl;
            return;
        }
        rear = (rear + 1) % capacity;
        arr[rear] = order;
        count++;
        cout << "Order added to queue!" << endl;
        order.display();
    }

    Order dequeue()
    {
        if (isEmpty())
        {
            cout << "\nQueue Underflow!" << endl;
            return Order();
        }
        Order order = arr[front];
        front = (front + 1) % capacity;
        count--;
        return order;
    }

    Order peek()
    {
        if (isEmpty())
        {
            cout << "Queue is empty!" << endl;
            return Order();
        }
        return arr[front];
    }

    void displayAllOrders()
    {
        if (isEmpty())
        {
            cout << "No orders in queue." << endl;
            return;
        }
        cout << "ALL PENDING ORDERS" << endl;
        cout << "Total Orders: " << count << endl;

        int index = front;
        for (int i = 0; i < count; i++)
        {
            cout << (i + 1) << ". ";
            arr[index].display();
            index = (index + 1) % capacity;
        }
    }

    void displayProcessedOrders(Order *processed, int processedCount)
    {
        if (processedCount == 0)
        {
            cout << "\nNo orders have been processed yet." << endl;
            return;
        }
        
        cout << "PROCESSED ORDERS" << endl;

        cout << "Total Processed: " << processedCount << endl;
       

        for (int i = 0; i < processedCount; i++)
        {
            cout << (i + 1) << ". ";
            processed[i].display();
        }
    }
};

class RestaurantOrderSystem
{
private:
    Queue orderQueue;
    Order *processedOrders;
    int processedCount;
    int maxProcessed;
    int nextOrderId;

public:
    RestaurantOrderSystem(int queueSize, int maxProcessedSize)
        : orderQueue(queueSize)
    {
        maxProcessed = maxProcessedSize;
        processedOrders = new Order[maxProcessed];
        processedCount = 0;
        nextOrderId = 1001;
    }

    ~RestaurantOrderSystem()
    {
        delete[] processedOrders;
    }

    void addOrder(string itemName, int quantity, string customerName)
    {
        Order newOrder(nextOrderId++, itemName, quantity, customerName);
        orderQueue.enqueue(newOrder);
    }

    void processNextOrder()
    {
        if (orderQueue.isEmpty())
        {
            cout << "\nNo orders to process." << endl;
            return;
        }

        Order order = orderQueue.dequeue();
        cout << "\nOrder being prepared..." << endl;
        order.display();

        if (processedCount < maxProcessed)
        {
            processedOrders[processedCount++] = order;
            cout << "Order processed successfully!" << endl;
        }
    }

    void viewPendingOrders()
    {
        orderQueue.displayAllOrders();
    }

    void viewProcessedOrders()
    {
        orderQueue.displayProcessedOrders(processedOrders, processedCount);
    }

    void displaySystemStatus()
    {
        cout << "\n========================================" << endl;
        cout << "RESTAURANT ORDER SYSTEM STATUS" << endl;

        cout << "Pending Orders: " << orderQueue.size() << endl;
        cout << "Processed Orders: " << processedCount << endl;
        cout << "Next Order ID: " << nextOrderId << endl;
    }
};

void displayMenu()
{
    cout << "\n========================================" << endl;
    cout << "RESTAURANT ORDER MANAGEMENT SYSTEM" << endl;

    cout << "1. Add New Order" << endl;
    cout << "2. Process Next Order" << endl;
    cout << "3. View Pending Orders" << endl;
    cout << "4. View Processed Orders" << endl;
    cout << "5. System Status" << endl;
    cout << "6. Exit" << endl;

    cout << "Enter your choice: ";
}

int main()
{
    RestaurantOrderSystem restaurant(10, 50);

    cout << "\n************************************************" << endl;
    cout << "   WELCOME TO RESTAURANT ORDER SYSTEM" << endl;
    cout << "************************************************" << endl;

    restaurant.addOrder("Burger", 2, "Bajwa");
    restaurant.addOrder("Pizza", 1, "Laghari");
    restaurant.addOrder("Pasta", 3, "Bohemia");
    restaurant.addOrder("Salad", 2, "Anwar");
    restaurant.addOrder("Sandwich", 1, "Ahmed");

    int choice;
    bool running = true;

    while (running)
    {
        displayMenu();
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            string item, customer;
            int qty;
            cout << "\nEnter customer name: ";
            cin.ignore();
            getline(cin, customer);
            cout << "Enter item name: ";
            getline(cin, item);
            cout << "Enter quantity: ";
            cin >> qty;
            restaurant.addOrder(item, qty, customer);
            break;
        }
        case 2:
            restaurant.processNextOrder();
            break;
        case 3:
            restaurant.viewPendingOrders();
            break;
        case 4:
            restaurant.viewProcessedOrders();
            break;
        case 5:
            restaurant.displaySystemStatus();
            break;
        case 6:
            cout << "\nThank you for using the system!" << endl;
            running = false;
            break;
        default:
            cout << "\nInvalid choice! Please try again." << endl;
        }
    }

    return 0;
}