#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

#define MAX 10
#define EMPTY_STACK_INDEX -1

class StackByArray
{
public:
    int elements[MAX];
    int top_index;
    StackByArray()
    {
        top_index = EMPTY_STACK_INDEX;
    }
    static StackByArray initStack()
    {
        StackByArray stack;
        return stack;
    }
    void push(int value)
    {
        if (!isFull())
        {
            addElement(value);
            incrementTopIndex();
        }
        else
        {
            printf("Stack is full\n");
        }
    }
    int pop()
    {
        int last_element = removeLastElement();
        decrementTopIndex();
        return last_element;
    }
    void print(std::string spacer)
    {
        printf("%s{\n", spacer.c_str());
        if (!isEmpty())
        {
            for (int i = top_index; i >= 0; i--)
            {
                printf("%s    %d : %d\n", spacer.c_str(), i, elements[i]);
            }
        }
        printf("%s}\n", spacer.c_str());
    }

private:
    bool isFull()
    {
        return top_index == MAX - 1;
    }
    void addElement(int value)
    {
        elements[top_index + 1] = value;
    }
    void incrementTopIndex()
    {
        if (!isFull())
        {
            top_index = top_index + 1;
        }
    }
    bool isEmpty()
    {
        return top_index == EMPTY_STACK_INDEX;
    }
    int removeLastElement()
    {
        if (!isEmpty())
        {
            return elements[top_index];
        }
        printf("Stack is empty\n");
        return EMPTY_STACK_INDEX;
    }
    void decrementTopIndex()
    {
        if (!isEmpty())
        {
            top_index = top_index - 1;
        }
    }
};

struct Node
{
    int value;
    Node *next;
    Node(int val) : value(val), next(nullptr) {}
};

class StackByLinkedList
{
public:
    Node *top;
    StackByLinkedList() : top(nullptr) {}
    void push(int value)
    {
        Node *new_node = new Node(value);
        new_node->next = top;
        top = new_node;
    }
    int pop()
    {
        if (top == nullptr)
        {
            printf("Stack is empty\n");
            return EMPTY_STACK_INDEX;
        }
        int value = top->value;
        Node *temp = top;
        top = top->next;
        delete temp;
        return value;
    }
    void print(std::string spacer)
    {
        printf("%s{\n", spacer.c_str());
        Node *current = top;
        while (current != nullptr)
        {
            printf("%s    %d\n", spacer.c_str(), current->value);
            current = current->next;
        }
        printf("%s}\n", spacer.c_str());
    }
};

class QueueByArray
{
public:
    int front;
    int rear;
    int elements[MAX];
    QueueByArray()
    {
        front = 1;
        rear = 0;
    }
    static QueueByArray initQueue()
    {
        QueueByArray queue;
        return queue;
    }
    void push(int value)
    {
        if (!isFull())
        {
            incrementRear();
            addElement(value);
        }
        else
        {
            printf("Queue is full\n");
        }
    }
    int pop()
    {
        int first_element = removeElement();
        incrementFront();
        return first_element;
    }

    void print(std::string spacer)
    {
        printf("%s{\n", spacer.c_str());
        if (!isEmpty())
        {
            for (int i = front; i <= rear; i++)
            {
                printf("%s    %d : %d\n", spacer.c_str(), i, elements[i]);
            }
        }
        printf("%s}\n", spacer.c_str());
    }

private:
    bool isEmpty()
    {
        return front > rear;
    }
    bool isFull()
    {
        return rear == MAX - 1;
    }
    void addElement(int value)
    {
        elements[rear] = value;
    }
    void incrementRear()
    {
        if (!isFull())
        {
            rear = rear + 1;
        }
    }
    int removeElement()
    {
        if (!isEmpty())
        {
            return elements[front];
        }
        printf("Queue is empty\n");
        return EMPTY_STACK_INDEX;
    }
    void incrementFront()
    {
        if (!isEmpty())
        {
            front = front + 1;
        }
    }
};

namespace test
{
    namespace stack_by_array
    {
        int test_initStack()
        {
            printf("Testing stack initialization\n");
            StackByArray stack = StackByArray::initStack();
            if (stack.top_index != EMPTY_STACK_INDEX)
            {
                printf("    Failed to initialize stack\n");
                printf("    Expected top_index : %d\n", EMPTY_STACK_INDEX);
                printf("    Actual top_index : %d\n", stack.top_index);
                return EXIT_FAILURE;
            }
            stack.print("    ");
            printf("Stack initialized successfully\n");
            return EXIT_SUCCESS;
        }
        namespace push
        {
            int test_regular_push()
            {
                printf("    Testing regular push operation\n");
                StackByArray stack = StackByArray::initStack();
                stack.push(1);
                if (stack.top_index != 0)
                {
                    printf("        Failed to push element to stack\n");
                    printf("        Expected top_index : %d\n", 0);
                    printf("        Actual top_index : %d\n", stack.top_index);
                    return EXIT_FAILURE;
                }
                if (stack.elements[0] != 1)
                {
                    printf("        Failed to push element to stack\n");
                    printf("        Expected element at index 0 : %d\n", 1);
                    printf("        Actual element at index 0 : %d\n", stack.elements[0]);
                    return EXIT_FAILURE;
                }
                stack.print("        ");
                printf("    Element regularly pushed successfully\n");
                return EXIT_SUCCESS;
            }
            int test_push_to_full_stack()
            {
                printf("    Testing push operation to full stack\n");
                StackByArray stack = StackByArray::initStack();
                for (int i = 0; i < MAX; i++)
                {
                    stack.push(i);
                }
                printf("        Stack after pushing %d elements :\n", MAX);
                stack.print("           ");
                printf("        Pushing element to full stack :\n");
                stack.push(100);
                if (stack.top_index != MAX - 1)
                {
                    printf("        Error: top_index changed after pushing to full stack\n");
                    return EXIT_FAILURE;
                }
                stack.print("           ");
                printf("        Push to full stack handled correctly\n");
                return EXIT_SUCCESS;
            }
        }
        int test_push()
        {
            printf("Testing push operation\n");
            int regular_push_result = push::test_regular_push();
            if (regular_push_result != EXIT_SUCCESS)
            {
                printf("    Regular push test failed, not testing push to full stack\n");
                return regular_push_result;
            }
            int push_to_full_stack_result = push::test_push_to_full_stack();
            if (push_to_full_stack_result != EXIT_SUCCESS)
            {
                return push_to_full_stack_result;
            }
            printf("    All push tests passed successfully\n");
            return EXIT_SUCCESS;
        }
        namespace pop
        {
            int test_regular_pop()
            {
                printf("    Testing regular pop operation\n");
                StackByArray stack = StackByArray::initStack();
                stack.push(1);
                stack.push(2);
                stack.push(3);
                printf("        Stack before pop operation :\n");
                stack.print("           ");
                int popped_value = stack.pop();
                if (popped_value != 3)
                {
                    printf("        Failed to pop the correct element from stack\n");
                    printf("        Expected popped value : %d\n", 3);
                    printf("        Actual popped value : %d\n", popped_value);
                    return EXIT_FAILURE;
                }
                if (stack.top_index != 1)
                {
                    printf("        Failed to update top_index after pop operation\n");
                    printf("        Expected top_index : %d\n", 1);
                    printf("        Actual top_index : %d\n", stack.top_index);
                    return EXIT_FAILURE;
                }
                printf("        Stack after pop operation :\n");
                stack.print("           ");
                printf("    Element regularly popped successfully\n");
                return EXIT_SUCCESS;
            }
            int test_pop_from_empty_stack()
            {
                printf("    Testing pop from empty stack operation\n");
                StackByArray stack = StackByArray::initStack();
                int popped_value = stack.pop();
                if (popped_value != -1)
                {
                    printf("        Failed to pop from empty stack\n");
                    printf("        Expected popped value : %d\n", -1);
                    printf("        Actual popped value : %d\n", popped_value);
                    return EXIT_FAILURE;
                }
                printf("        Pop from empty stack handled correctly\n");
                return EXIT_SUCCESS;
            }
        }
        int test_pop()
        {
            printf("Testing pop operation\n");
            int regular_pop_result = pop::test_regular_pop();
            if (regular_pop_result != EXIT_SUCCESS)
            {
                printf("    Regular pop test failed, not testing pop from empty stack\n");
                return regular_pop_result;
            }
            int pop_from_empty_stack_result = pop::test_pop_from_empty_stack();
            if (pop_from_empty_stack_result != EXIT_SUCCESS)
            {
                return pop_from_empty_stack_result;
            }
            printf("    All pop tests passed successfully\n");
            return EXIT_SUCCESS;
        }
        int test_statck_by_array()
        {
            int initStack_result = test_initStack();
            if (initStack_result != EXIT_SUCCESS)
            {
                printf("Init stack test failed, not testing push\n");
                return initStack_result;
            }
            int push_result = test_push();
            if (push_result != EXIT_SUCCESS)
            {
                printf("Push test failed, not testing pop\n");
                return push_result;
            }
            printf("    push operation tested successfully\n");
            int pop_result = test_pop(); // Call to pop tests here
            if (pop_result != EXIT_SUCCESS)
            {
                printf("Pop test failed\n");
                return pop_result;
            }
            printf("All stack by array tests passed successfully\n");
            return EXIT_SUCCESS;
        }
    }
    namespace stack_by_linked_list
    {
        int initStack()
        {
            printf("Testing stack by linked list initialization\n");
            StackByLinkedList stack;
            if (stack.top != nullptr)
            {
                printf("    Failed to initialize stack\n");
                printf("    Expected top : nullptr\n");
                printf("    Actual top : %p\n", (void *)stack.top);
                return EXIT_FAILURE;
            }
            stack.print("    ");
            printf("Stack initialized successfully\n");
            return EXIT_SUCCESS;
        }
        namespace push
        {
            int test_regular_push()
            {
                StackByLinkedList stack = StackByLinkedList();
                stack.push(1);
                if (stack.top == nullptr)
                {
                    printf("        Failed to push element to stack\n");
                    printf("        Expected top not to be nullptr\n");
                    return EXIT_FAILURE;
                }
                if (stack.top->value != 1)
                {
                    printf("        Failed to push element to stack\n");
                    printf("        Expected top value : %d\n", 1);
                    printf("        Actual top value : %d\n", stack.top->value);
                    return EXIT_FAILURE;
                }
                stack.print("        ");
                printf("    Element regularly pushed successfully\n");
                return EXIT_SUCCESS;
            }
            int test_push()
            {
                printf("Testing push operation\n");
                int regular_push_result = test_regular_push();
                if (regular_push_result != EXIT_SUCCESS)
                {
                    printf("    Regular push test failed\n");
                    return regular_push_result;
                }
                printf("    All push tests passed successfully\n");
                return EXIT_SUCCESS;
            }
        } // namespace push
        namespace pop
        {
            int test_regular_pop()
            {
                StackByLinkedList stack = StackByLinkedList();
                stack.push(0);
                stack.push(1);
                stack.push(2);
                printf("        Stack before pop operation :\n");
                stack.print("           ");
                int pop_result = stack.pop();
                if (pop_result != 2)
                {
                    printf("        Failed to pop the correct element from stack\n");
                    printf("        Expected pop value : %d\n", 2);
                    printf("        Actual pop value : %d\n", pop_result);
                    return EXIT_FAILURE;
                }
                if (stack.top == nullptr || stack.top->value != 1)
                {
                    printf("        Failed to update top after pop operation\n");
                    printf("        Expected top value : %d\n", 1);
                    if (stack.top == nullptr)
                    {
                        printf("        Actual top value : nullptr\n");
                    }
                    else
                    {
                        printf("        Actual top value : %d\n", stack.top->value);
                    }
                    return EXIT_FAILURE;
                }
                return EXIT_SUCCESS;
            }
            int test_pop_from_empty_stack()
            {
                StackByLinkedList stack = StackByLinkedList();
                int pop_result = stack.pop();
                if (pop_result != -1)
                {
                    printf("        Failed to pop from empty stack\n");
                    printf("        Expected pop value : %d\n", -1);
                    printf("        Actual pop value : %d\n", pop_result);
                    return EXIT_FAILURE;
                }
                printf("    Pop from empty stack tested successfully\n");
                return EXIT_SUCCESS;
            }
            int test_pop()
            {
                return EXIT_SUCCESS;
            }

        } // namespace pop
        int test_stack_by_linked_list()
        {
            int initStack_result = initStack();
            if (initStack_result != EXIT_SUCCESS)
            {
                printf("Init stack test failed, not testing push\n");
                return initStack_result;
            }
            // Add push and pop tests here
            printf("All stack by linked list tests passed successfully\n");
            return EXIT_SUCCESS;
        }
    }
    namespace queue_by_array
    {
        int test_initQueue()
        {
            printf("Testing queue initialization\n");
            QueueByArray queue = QueueByArray::initQueue();
            if (queue.front != 1 || queue.rear != 0)
            {
                printf("    Failed to initialize queue\n");
                printf("    Expected front : %d, rear : %d\n", 1, 0);
                printf("    Actual front : %d, rear : %d\n", queue.front, queue.rear);
                return EXIT_FAILURE;
            }
            queue.print("    ");
            printf("Queue initialized successfully\n");
            return EXIT_SUCCESS;
        }
        namespace push
        {
            int test_regular_push()
            {
                printf("    Testing regular push operation\n");
                QueueByArray queue = QueueByArray::initQueue();
                queue.push(1);
                queue.print("        ");
                if (queue.rear != 1)
                {
                    printf("        Failed to push element to queue\n");
                    printf("        Expected rear : %d\n", 0);
                    printf("        Actual rear : %d\n", queue.rear);
                    return EXIT_FAILURE;
                }
                if (queue.elements[queue.rear] != 1)
                {
                    printf("        Failed to push element to queue\n");
                    printf("        Expected element at index 0 : %d\n", 1);
                    printf("        Actual element at index 0 : %d\n", queue.elements[queue.rear]);
                    return EXIT_FAILURE;
                }

                printf("    Element regularly pushed successfully\n");
                return EXIT_SUCCESS;
            }
            int test_push_to_full_queue()
            {
                printf("    Testing push operation to full queue\n");
                QueueByArray queue = QueueByArray::initQueue();
                for (int i = 0; i < MAX; i++)
                {
                    queue.push(i);
                }
                printf("        Queue after pushing %d elements :\n", MAX);
                queue.print("            ");
                printf("        Pushing element to full queue :\n");
                queue.push(100);
                printf("        Queue after attempting to push to full queue :\n");
                queue.print("            ");
                if (queue.rear != MAX - 1)
                {
                    printf("        Error: rear changed after pushing to full queue\n");
                    return EXIT_FAILURE;
                }
                printf("        Push to full queue handled correctly\n");
                return EXIT_SUCCESS;
            }

            int test_push()
            {
                printf("Testing push operation\n");
                int regular_push_result = test_regular_push();
                if (regular_push_result != EXIT_SUCCESS)
                {
                    printf("    Regular push test failed, not testing push to full queue\n");
                    return regular_push_result;
                }
                int push_to_full_queue_result = test_push_to_full_queue();
                if (push_to_full_queue_result != EXIT_SUCCESS)
                {
                    return push_to_full_queue_result;
                }
                printf("    All push tests passed successfully\n");
                return EXIT_SUCCESS;
            }
        }
        namespace pop
        {
            int test_regular_pop()
            {
                printf("    Testing regular pop operation\n");
                QueueByArray queue = QueueByArray::initQueue();
                queue.push(1);
                queue.push(2);
                queue.push(3);
                printf("        Queue before pop operation :\n");
                queue.print("           ");
                int popped_value = queue.pop();
                printf("        Queue after pop operation :\n");
                queue.print("           ");
                if (popped_value != 1)
                {
                    printf("        Failed to pop the correct element from queue\n");
                    printf("        Expected popped value : %d\n", 1);
                    printf("        Actual popped value : %d\n", popped_value);
                    return EXIT_FAILURE;
                }
                if (queue.front != 2)
                {
                    printf("        Failed to update front after pop operation\n");
                    printf("        Expected front : %d\n", 2);
                    printf("        Actual front : %d\n", queue.front);
                    return EXIT_FAILURE;
                }
                
                printf("    Element regularly popped successfully\n");
                return EXIT_SUCCESS;
            }
            int test_pop_from_empty_queue()
            {
                printf("    Testing pop from empty queue operation\n");
                QueueByArray queue = QueueByArray::initQueue();
                int popped_value = queue.pop();
                printf("        Queue after pop operation :\n");
                queue.print("           ");
                if (popped_value != -1)
                {
                    printf("        Failed to pop from empty queue\n");
                    printf("        Expected popped value : %d\n", -1);
                    printf("        Actual popped value : %d\n", popped_value);
                    return EXIT_FAILURE;
                }
                printf("        Pop from empty queue handled correctly\n");
                return EXIT_SUCCESS;
            }
            int test_pop()
            {
                printf("Testing pop operation\n");
                int regular_pop_result = test_regular_pop();
                if (regular_pop_result != EXIT_SUCCESS)
                {
                    printf("    Regular pop test failed, not testing pop from empty queue\n");
                    return regular_pop_result;
                }
                int pop_from_empty_queue_result = test_pop_from_empty_queue();
                if (pop_from_empty_queue_result != EXIT_SUCCESS)
                {
                    return pop_from_empty_queue_result;
                }
                printf("    All pop tests passed successfully\n");
                return EXIT_SUCCESS;
            }
        }

        int test_statck_by_array()
        {
            int initQueue_result = test_initQueue();
            if (initQueue_result != EXIT_SUCCESS)
            {
                printf("Init queue test failed, not testing push\n");
                return initQueue_result;
            }
            int push_result = push::test_push();
            if (push_result != EXIT_SUCCESS)
            {
                printf("Push test failed, not testing pop\n");
                return push_result;
            }
            printf("    push operation tested successfully\n");
            int pop_result = pop::test_pop(); // Call to pop tests here
            if (pop_result != EXIT_SUCCESS)
            {
                printf("Pop test failed\n");
                return pop_result;
            }
            printf("All queue by array tests passed successfully\n");
            return EXIT_SUCCESS;
        }
    }

    int test_all()
    {

        // int stack_by_array_tests_results = stack_by_array::test_statck_by_array();
        // if (stack_by_array_tests_results != EXIT_SUCCESS)
        // {
        //     return EXIT_FAILURE;
        // }
        // int stack_by_linked_list_tests_results = stack_by_linked_list::test_stack_by_linked_list();
        // if (stack_by_linked_list_tests_results != EXIT_SUCCESS)
        // {
        //     return EXIT_FAILURE;
        // }
        int queue_by_array_tests_results = queue_by_array::test_statck_by_array();
        if (queue_by_array_tests_results != EXIT_SUCCESS)
        {
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    }
}
int main()
{
    printf("Starting all tests\n");
    int all_tests_result = test::test_all();
    if (all_tests_result != EXIT_SUCCESS)
    {
        printf("Some tests failed\n");
    }
    else
    {
        printf("All tests passed successfully\n");
    }
    return all_tests_result;
}
