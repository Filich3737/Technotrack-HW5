#ifndef STACK_H
#define STACK_H

#include <cassert>
#include <cstring>
#include <cstdlib>
#include <iostream>


/**
 * @brief Unit test define
 * @param what expression to test
 * @param op operand to use with expression
 * @param ref reference (what should expression be?)
 */
#define UNITTEST(what, op, ref)                                                                                     \
{                                                                                                                   \
    auto result = (what);                                                                                           \
    auto r = (ref);                                                                                                 \
    if (result op r)                                                                                                \
    cout << #what << " \x1b[32m[passed]\x1b[0m: result is " << result << " and should be " #op " " << r <<endl;     \
    else                                                                                                            \
    cout << #what << " \x1b[31m[failed]\x1b[0m: result is " << result << " but should be " #op " " << r <<endl;     \
    }                                                                                                               \

/**
  * @brief Prints full stack dump
  * @param inpSt poiner to stack for dump
  * @param reason reason why do you use dump (reason will be printed before dump)
  */
#define Stack_dump(inpSt, reason)                                                                                   \
{                                                                                                                   \
    auto addr = (inpSt);                                                                                            \
    auto res = Stack_OK(inpSt);                                                                                     \
    cout << "-------------------------------------------------------" << endl;                                      \
    cout << (reason) << endl;                                                                                       \
    cout << "Stack " << #inpSt << " " << addr << " Stack_OK:" << res << endl;                                       \
    cout << "Capacity: " << inpSt->capacity << endl;                                                                \
    cout << "Count: " << inpSt->count << endl;                                                                      \
    cout << "Data: " << inpSt->data << endl;                                                                        \
    cout << "\x1b[033mCanary1:\x1b[0m ";                                                                            \
    if(*inpSt->dat_can1 == static_cast<int>(0xBEDABEDA)) cout << "\x1b[32m"; else cout << "\x1b[31m";               \
    cout << *inpSt->dat_can1 << "\x1b[0m" << endl;                                                                  \
                                                                                                                    \
    for (int i = 0; i < inpSt->capacity; i++)                                                                       \
{                                                                                                                   \
    printf("[%d] = ", i);                                                                                           \
    if(i >= inpSt->count)                                                                                           \
    printf("\x1b[33m");                                                                                             \
    if(inpSt->data[i] == 666)                                                                                       \
    printf("\x1b[31m");                                                                                             \
    printf("%d\n", inpSt->data[i]);                                                                                 \
    printf("\x1b[0m");                                                                                              \
    }                                                                                                               \
                                                                                                                    \
    cout << "\x1b[033mCanary2:\x1b[0m ";                                                                            \
    if(*inpSt->dat_can2 == static_cast<int>(0xBEDABEDA)) cout << "\x1b[32m"; else cout << "\x1b[31m";               \
    cout << *inpSt->dat_can2 << "\x1b[0m" << endl;                                                                  \
    cout << "-------------------------------------------------------" << "\n" <<endl;                               \
    }

/**
  * @brief Checks if stack is damaged
  * @param inpSt poiner to stack for dump
  * @param reason reason why do you use dump (reason will be printed before dump)
  */
#define ASSERT_OK(inpSt, reason) if(Stack_OK(inpSt) != 0) {Stack_dump(inpSt, reason); assert(0);}

/**
 * @brief Stack structure
 */
struct Stack
{
    uint16_t canary1 = 0xBEDA;                                    ///control element for penetration protection
    int count = 0;                                                ///stack count
    int capacity = 0;                                             ///stack volume
    long stk_sum = 0;                                             ///stack structure checksum
    long dat_sum = 0;                                             ///data array ckecksum
    int *data = static_cast<int*>(nullptr);                       ///data aray pointer
    int *dat_can1 = static_cast<int*>(nullptr);                   ///control element pointer
    int *dat_can2 = static_cast<int*>(nullptr);                   ///control element pointer
    uint16_t canary2 = 0xBEDA;                                    ///control element for penetration protection
};

/**
 * @brief Calculates control sum of the stack
 * @param inpSt input stack
 * @return control sum
 */
long calc_stk_sum(Stack *inpSt);

/**
 * @brief Calculates control sum of the data aray
 * @param inpSt input stack
 * @return control sum
 */
int calc_dat_sum(Stack *inpSt);

/**
 * @brief Writes checksum of the stack
 * @param inpSt input stack
 */
void write_stk_sum(Stack *inpSt);

/**
 * @brief Writes checksum of the data aray
 * @param inpSt input stack
 */
void write_dat_sum(Stack *inpSt);

/**
 * @brief Writes checksums of the stack and data aray
 * @param inpSt input stack
 */
void write_control_sums(Stack *inpSt);

/**
 * @brief Quiet verification of the stack
 * @param inpSt input stack
 * @return 0 if evrething ok or error code
 */
int Stack_OK(Stack *inpSt);


/**
 * @brief Creates new data aray
 * @param inpSt input stack
 */
void create_new_data(Stack *inpSt);

/**
 * @brief Creates new stack from inpSt
 * @param inpSt input stack
 */
void StackCtor(Stack *inpSt);

/**
 * @brief Creates new stack from nothing
 * @return new stack
 */
Stack StackNew();

/**
 * @brief Poisons all data aray elements (assigns with 666)
 * @param inpSt input stack
 */
void poison_dat(Stack *inpSt);

/**
 * @brief Poisons all stack structure members (assigns with 666)
 * @param inpSt
 */
void poison_stk(Stack *inpSt);

/**
 * @brief Destructes the stack
 * @param inpSt input stack
 */
void StackDtor(Stack *inpSt);

/**
 * @brief Expands stack (makes twice larger or twice smaller)
 * @param inpSt input stack
 * @param isExp 0 if you whant to decrease stack, else if you want to increase stack
 */
void expand_stk(Stack *inpSt, uint8_t isExp);

/**
 * @brief Pushes val to the top of the stack
 * @param inpSt input stack
 * @param val value to push
 */
void Push_back(Stack *inpSt, int val);

/**
 * @brief Pops element from the top of the stack
 * @param inpSt input stack
 */
int Pop_back(Stack *inpSt);

/**
 * @brief My version of stack dump
 * @param inpSt input stack
 */
void My_dump(Stack *inpSt);

/**
 * @brief Returns size of the stack
 * @param inpSt input stack
 * @return size of the stack
 */
int StackSize(Stack *inpSt);

/**
 * @brief Returns volume of the stack
 * @param inpSt input stack
 * @return capacity of the stack
 */
int StackCapacity(Stack *inpSt);

/**
 * @brief Returns top element of the stack without removing it
 * @param inpSt input stack
 * @return top element of the stack
 */
int StackTop(Stack *inpSt);

void dump(Stack *inpSt);

#endif // STACK_H
