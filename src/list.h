/*******************************************************************************
** list.h (list macros)
*******************************************************************************/

#ifndef LIST_H
#define LIST_H

#define SLIST_DESTROY(type, head, iterator)                                    \
  iterator = head;                                                             \
                                                                               \
  while (head != NULL)                                                         \
  {                                                                            \
    iterator = head->next;                                                     \
    type##_destroy(head);                                                      \
    head = iterator;                                                           \
  }

#define SLIST_ADD_TO_END(head, iterator, element)                              \
  iterator = head;                                                             \
                                                                               \
  if (iterator == NULL)                                                        \
  {                                                                            \
    head = element;                                                            \
    element->next = NULL;                                                      \
  }                                                                            \
  else                                                                         \
  {                                                                            \
    while (iterator->next != NULL)                                             \
      iterator = iterator->next;                                               \
                                                                               \
    iterator->next = element;                                                  \
    element->next = NULL;                                                      \
  }

#define SLIST_ADD_TO_FRONT(head, element)                                      \
  if (head == NULL)                                                            \
  {                                                                            \
    head = element;                                                            \
    element->next = NULL;                                                      \
  }                                                                            \
  else                                                                         \
  {                                                                            \
    element->next = head;                                                      \
    head = element;                                                            \
  }

#define DLIST_ADD_TO_END(head, tail, element)                                  \
  if (tail == NULL)                                                            \
  {                                                                            \
    head = element;                                                            \
    tail = element;                                                            \
    element->next = NULL;                                                      \
    element->prev = NULL;                                                      \
  }                                                                            \
  else                                                                         \
  {                                                                            \
    element->next = NULL;                                                      \
    element->prev = tail;                                                      \
    tail = element;                                                            \
  }

#define DLIST_ADD_TO_FRONT(head, tail, element)                                \
  if (head == NULL)                                                            \
  {                                                                            \
    head = element;                                                            \
    tail = element;                                                            \
    element->next = NULL;                                                      \
    element->prev = NULL;                                                      \
  }                                                                            \
  else                                                                         \
  {                                                                            \
    element->next = head;                                                      \
    element->prev = NULL;                                                      \
    head = element;                                                            \
  }

#endif
