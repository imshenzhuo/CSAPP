/* 
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q =  malloc(sizeof(queue_t));
    if (!q) return NULL;
    /* What if malloc returned NULL? */
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    if (!q) return;
    /* How about freeing the list elements and the strings? */
    /* Free queue structure */
    list_ele_t *head = q->head;
    list_ele_t *follow = head;
    while (head)
    {
        free(head->value);
        follow = head;
        head = head->next;
        free(follow);
    }
    free(q);
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    list_ele_t *newh;
    /* What should you do if the q is NULL? */
    if (!q) return false;
    newh = malloc(sizeof(list_ele_t));
    if (!newh)  return false;
    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */
    
    char *str = malloc(strlen(s)+1);
    if (!str) {
        free(newh);
        return false;
    }
    memcpy(str, s, strlen(s)+1);
    newh->value = str;

    if (!q->head) {
        q->tail = newh;
    }
    newh->next = q->head;
    q->head = newh;
    q->size++;
    return true;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    list_ele_t *newh;
    /* What should you do if the q is NULL? */
    if (!q) return false;
    newh = malloc(sizeof(list_ele_t));
    if (!newh)  return false;
    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */
    
    char *str = malloc(strlen(s)+1);
    if (!str) {
        free(newh);
        return false;
    }
    memcpy(str, s, strlen(s)+1);
    newh->value = str;

    newh->next = NULL;
    q->tail->next = newh;
    q->tail = newh;
    q->size++;
    return true;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    if (!q || q_size(q) <= 0) return false;
    list_ele_t *li = q->head;
    if (sp) {
        strncpy(sp,li->value,bufsize-1);
        if (strlen(li->value) > bufsize)
            sp[bufsize-1] = '\0';
    }
    /* You need to fix up this code. */
    q->size--;
    if (q_size(q) == 0) {
        q->head = NULL;
        q->tail = NULL;
    } else  {
        q->head = q->head->next;
    }
    
    free(li->value);
    free(li);
    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    if (!q) return 0;
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    return q->size;
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    // 指针数组 
    // if (!q) return;
    // list_ele_t *head = q->head;
    // size_t size = q_size(q);
    // list_ele_t **arr = malloc(size * sizeof(list_ele_t *));
    // for(int i=0; head; i++)
    // {
    //     arr[i] = head;
    //     head = head->next;
    // }
    // int i=0, j=size-1;
    // while (i<j)
    // {

    //     char *tmp = arr[i]->value;
    //     arr[i]->value = arr[j]->value;
    //     arr[j]->value = tmp;
    //     i++;
    //     j--;
    // }
    // free(arr);
    
    /* You need to write the code for this function */
    // gracefully
	if (q == NULL||q->size==0) {
		return;
	}
	list_ele_t* bef = NULL;
	list_ele_t* tem = q->head;
	list_ele_t* next = NULL;
	while (tem->next != NULL) {
		next = tem->next;
		tem->next = bef;
		bef = tem;
		tem = next;
	}
	tem->next = bef;
	q->tail = q->head;
	q->head = tem;
	return;
}

