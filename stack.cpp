/**
  *@file
  * @author Philip Khristolyubov
  * @version 1.0
  * @date 01.11.2018
  * @brief Третье домашнее задание по курсу "Введение в промышленное программирование и структуры данных"
  * @todo
  */


#include "stack.h"

//-----------------------------------------------------------------------------------------------------------------------

using namespace std;

/**
 * @brief Calculates control sum of the stack
 * @param inpSt input stack
 * @return control sum
 */
long calc_stk_sum(Stack *inpSt)
{
    assert(inpSt != nullptr);
    long tmp = inpSt->stk_sum;
    inpSt->stk_sum = 0;
    long sum = 0;
    uint8_t *ptr = (uint8_t*)inpSt;
    for (long i = 1; i < static_cast<long>(sizeof(Stack)) - 2; i++)
        sum += i * ptr[i];
    inpSt->stk_sum = tmp;
    return sum;
}

/**
 * @brief Calculates control sum of the data aray
 * @param inpSt input stack
 * @return control sum
 */
int calc_dat_sum(Stack *inpSt)
{
    assert(inpSt != nullptr);
    int sum = 0;
    int *ptr = inpSt->dat_can1;
    for (int i = 0; i <= inpSt->capacity; i++)
        sum += i * ptr[i];
    return sum;
}

/**
 * @brief Writes checksum of the stack
 * @param inpSt input stack
 */
void write_stk_sum(Stack *inpSt)
{
    assert(inpSt != nullptr);
    inpSt->stk_sum = calc_stk_sum(inpSt);
}

/**
 * @brief Writes checksum of the data aray
 * @param inpSt input stack
 */
void write_dat_sum(Stack *inpSt)
{
    assert(inpSt != nullptr);
    inpSt->dat_sum = calc_dat_sum(inpSt);
}

/**
 * @brief Writes checksums of the stack and data aray
 * @param inpSt input stack
 */
void write_control_sums(Stack *inpSt)
{
    assert(inpSt != nullptr);
    write_dat_sum(inpSt);
    write_stk_sum(inpSt);
}

/**
 * @brief Quiet verification of the stack
 * @param inpSt input stack
 * @return 0 if evrething ok or error code
 */
int Stack_OK(Stack *inpSt)
{
    assert(inpSt != nullptr);
    if (inpSt->canary1 != 0xBEDA)
        return 1;
    else if (inpSt->canary2 != 0xBEDA)
        return 2;
    else if (*inpSt->dat_can1 != static_cast<int>(0xBEDABEDA))
        return 3;
    else if (*inpSt->dat_can2 != static_cast<int>(0xBEDABEDA))
        return 4;
    else if (inpSt->stk_sum != calc_stk_sum(inpSt))
        return 5;
    else if (inpSt->dat_sum != calc_dat_sum(inpSt))
        return 6;
    else if ( inpSt->count > inpSt->capacity )
        return 7;
    else if (inpSt->data == nullptr)
        return 8;
    else
        return 0;
}

/**
 * @brief Creates new data aray
 * @param inpSt input stack
 */
void create_new_data(Stack *inpSt)
{
    assert(inpSt != nullptr);

    int *ptr = static_cast<int*>(calloc(3, sizeof(unsigned)));
    assert(ptr != nullptr);

    ptr[0] = static_cast<int>(0xBEDABEDA);
    ptr[1] = 444;
    ptr[2] = static_cast<int>(0xBEDABEDA);
    inpSt->dat_can1 = &(ptr[0]);
    inpSt->data = &(ptr[1]);
    inpSt->dat_can2 = &(ptr[2]);
}

/**
 * @brief Creates new stack from inpSt
 * @param inpSt input stack
 */
void StackCtor(Stack *inpSt)
{
    assert(inpSt != nullptr);
    inpSt->capacity = 1;

    create_new_data(inpSt);

    write_control_sums(inpSt);
}

/**
 * @brief Creates new stack from nothing
 * @return new stack
 */
Stack StackNew()
{
    Stack outSt;
    StackCtor(&outSt);
    return outSt;
}

/**
 * @brief Poisons all data aray elements (assigns with 666)
 * @param inpSt input stack
 */
void poison_dat(Stack *inpSt)
{
    assert(inpSt != nullptr);
    for (int i = 0; i < inpSt->capacity + 2; i++)
        inpSt->dat_can1[i] = 666;
}

/**
 * @brief Poisons all stack structure members (assigns with 666)
 * @param inpSt
 */
void poison_stk(Stack *inpSt)
{
    assert(inpSt != nullptr);
    uint32_t *ptr = (uint32_t*)inpSt;
    for (unsigned i = 0; i < sizeof(Stack)/4; i++)
        ptr[i] = 666;
}

/**
 * @brief Destructes the stack
 * @param inpSt input stack
 */
void StackDtor(Stack *inpSt)
{
    poison_dat(inpSt);
    free(inpSt->dat_can1);
    poison_stk(inpSt);
}

/**
 * @brief Expands stack (makes twice larger or twice smaller)
 * @param inpSt input stack
 * @param isExp 0 if you whant to decrease stack, else if you want to increase stack
 */
void expand_stk(Stack *inpSt, uint8_t isExp)
{
    assert(inpSt != nullptr);

    if(isExp)
        inpSt->capacity *= 2;
    else
        inpSt->capacity /= 2;

    void *tmp = realloc(inpSt->dat_can1, static_cast<size_t>(inpSt->capacity + 2) * sizeof(unsigned));
    assert(tmp != nullptr);

    int *ptr = static_cast<int*>(tmp);
    if(isExp)
    {
        for (int i = 0; i < inpSt->capacity/2; i++)
            *(ptr + inpSt->capacity/2 + 1 +i) = 444;
    }
    ptr[inpSt->capacity + 1] = static_cast<int>(0xBEDABEDA);

    inpSt->dat_can1 = ptr;
    inpSt->data = ptr+1;
    inpSt->dat_can2 = &ptr[inpSt->capacity + 1];
}

/**
 * @brief Pushes val to the top of the stack
 * @param inpSt input stack
 * @param val value to push
 */
void Push_back(Stack *inpSt, int val)
{
    assert(inpSt != nullptr);
    ASSERT_OK(inpSt, "Push_back_before");
    if(inpSt->count == inpSt->capacity)
        expand_stk(inpSt, 1);
    inpSt->data[inpSt->count] = val;
    inpSt->count++;
    write_control_sums(inpSt);
    ASSERT_OK(inpSt, "Push_back_after");
}

/**
 * @brief Pops element from the top of the stack
 * @param inpSt input stack
 */
int Pop_back(Stack *inpSt)
{
    assert(inpSt != nullptr);
    ASSERT_OK(inpSt, "Pop_back_before");
    assert(inpSt->count != 0);

    int tmp = inpSt->data[--inpSt->count];
    inpSt->data[inpSt->count] = 555;
    if( (inpSt->capacity != 1) && (inpSt->count == inpSt->capacity/2) )
        expand_stk(inpSt, 0);

    write_control_sums(inpSt);
    ASSERT_OK(inpSt, "Pop_back_after");
    return tmp;
}

/**
 * @brief My version of stack dump
 * @param inpSt input stack
 */
void My_dump(Stack *inpSt)
{
    //printf("cap= %d,    count= %d\n", inpSt->capacity, inpSt->count);
    for (int i = 0; i <= inpSt->count-1; i++)
        printf("%d ", inpSt->data[i]);
    puts("");
    puts("");
}

/**
 * @brief Returns size of the stack
 * @param inpSt input stack
 * @return size of the stack
 */
int StackSize(Stack *inpSt)
{
    assert(inpSt != nullptr);
    return inpSt->count;
}

/**
 * @brief Returns volume of the stack
 * @param inpSt input stack
 * @return capacity of the stack
 */
int StackCapacity(Stack *inpSt)
{
    assert(inpSt != nullptr);
    return inpSt->capacity;
}

/**
 * @brief Returns top element of the stack without removing it
 * @param inpSt input stack
 * @return top element of the stack
 */
int StackTop(Stack *inpSt)
{
    assert(inpSt != nullptr);
    return inpSt->data[inpSt->count-1];
}

void dump(Stack *inpSt)
{
    Stack_dump(inpSt, "My Dump");
}
