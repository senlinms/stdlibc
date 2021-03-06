/*
** deque.c for deque in /home/tran_y/Templates/C/libs/libdeque
**
** Made by davy tran
** Login   <tran_y@epitech.net>
**
** Started on  Tue Apr 29 17:01:50 2014 davy tran
** Last update Wed Sep 30 16:35:05 2015 davy
*/

#include <string.h>
#include "deque.h"

static int const  default_value = 0;

static void constructor(deque *this)
{
  if (this == NULL)
    return ;
  memset(this, 0, sizeof(*this));
  if ((this->content = calloc(sizeof(*(this->content)), 1)) == NULL)
    exit(EXIT_FAILURE);
  this->size = 0;
}

static void destructor(deque *this)
{
  if (this == NULL)
    return ;
  g_deque.clear(this);
  if (this->content != NULL)
    free(this->content);
  this->content = NULL;
}

static iterator begin(deque *this)
{
  iterator      it;

  for (it = this->content; it != NULL && it->rewind != NULL; previous(it))
    ;
  return (it);
}

static iterator end(deque *this)
{
  iterator      it;

  for (it = this->content; it != NULL && it->forward != NULL; next(it))
    ;
  return (it);
}

static size_type  size(deque *this)
{
  iterator        it;
  size_type       n;

  for (it = begin(this), n = 0; it != NULL; next(it), ++n)
    ;
  return (n);
}

static size_type  max_size(deque *this)
{
  return ((size_type)this);
}

static void resize(deque *this, size_type n)
{
  size_type i;

  if ((i = size(this)) == n)
    return ;
  else if (i < n)
  {
    for (; i < n; ++i)
      g_deque.push_back(this, (void *)(&default_value));
  }
  else
  {
    for (; i > n; --i)
      g_deque.pop_back(this);
  }
}

static bool empty(deque *this)
{
  return (this == NULL || this->content == NULL);
}

static void *at(deque *this, size_type n)
{
  iterator  it;

  for (it = begin(this); it != NULL && n != 0; next(it), --n)
    ;
  return (it != NULL ? it->value : NULL);
}

static void *front(deque *this)
{
  const iterator  it = g_deque.begin(this);

  return (it != NULL ? it->value : NULL);
}

static void *back(deque *this)
{
  const iterator  it = g_deque.end(this);

  return (it != NULL ? it->value : NULL);
}

static void assign(deque *this, InputIterator first, InputIterator last)
{
  iterator  it;

  g_deque.clear(this);
  for (it = first; it != NULL && it != last; next(it))
    g_deque.push_back(this, it->value);
}

static void push_back(deque *this, const value_type val)
{
  iterator  it;
  iterator  tmp;

  if (g_deque.end(this)->value == NULL)
  {
    g_deque.end(this)->value = val;
    return ;
  }
  if ((it = calloc(sizeof(*it), 1)) == NULL)
    exit(EXIT_FAILURE);
  it->value = val;
  it->rewind = NULL;
  it->forward = NULL;
  if ((tmp = g_deque.end(this)) != NULL)
  {
    tmp->forward = it;
    it->rewind = tmp;
  }
}

static void push_front(deque *this, const value_type val)
{
  iterator  it;

  if (g_deque.begin(this)->value == NULL)
  {
    g_deque.begin(this)->value = val;
    return ;
  }
  if ((it = calloc(sizeof(*it), 1)) == NULL)
    exit(EXIT_FAILURE);
  it->value = val;
  it->rewind = NULL;
  it->forward = NULL;
  if ((this->content = g_deque.begin(this)) != NULL)
  {
    this->content->rewind = it;
    it->forward = this->content;
    this->content = it;
  }
}

static void pop_back(deque *this)
{
  iterator  it;

  if ((it = g_deque.end(this)) != NULL && it->rewind != NULL)
  {
    it->rewind->forward = NULL;
    free(it);
  }
  else if (it != NULL && it->rewind == NULL)
    it->value = NULL;
}

static void pop_front(deque *this)
{
  if ((this->content = g_deque.begin(this)) != NULL &&
      this->content->forward != NULL)
  {
    this->content = this->content->forward;
    free(this->content->rewind);
    this->content->rewind = NULL;
  }
  else if (this->content != NULL && this->content->rewind == NULL)
    this->content->value = NULL;
}

static iterator insert(deque *this, iterator position, const value_type val)
{
  iterator      it;
  iterator      tmp;

  if ((it = calloc(sizeof(*it), 1)) == NULL)
    exit(EXIT_FAILURE);
  it->value = val;
  it->rewind = NULL;
  it->forward = NULL;
  for (tmp = g_deque.begin(this);
       tmp != NULL && tmp->forward != NULL && tmp != position; next(tmp));
  it->forward = tmp->forward;
  it->rewind = tmp;
  if (tmp->forward != NULL)
    tmp->forward->rewind = it;
  tmp->forward = it;
  return (NULL);
}

static iterator erase(deque *this, iterator position)
{
  iterator      it;
  iterator      tmp;

  it = g_deque.begin(this);
  while (it != NULL && it != position)
    next(it);
  if (it != position)
    return (NULL);
  tmp = it->forward;
  if (it->rewind != NULL)
    it->rewind->forward = it->forward;
  if (it->forward != NULL)
    it->forward->rewind = it->rewind;
  free(it);
  return (tmp);
}

static void swap(deque *this, deque *x)
{
  SWAP_PTR(this->content, x->content);
  SWAP_NBR(this->size, x->size);
}

static void clear(deque *this)
{
  iterator  it;
  iterator  forward;

  if (g_deque.size(this) == 0)
    return ;
  if (g_deque.size(this) == 1)
    return ((void)(this->content->value = NULL));
  if ((it = g_deque.begin(this))->forward != NULL)
  {
    it->value = NULL;
    next(it);
  }
  while (it != NULL)
  {
    forward = it->forward;
    free(it);
    it = forward;
  }
}

struct s_deque_class  g_deque = {
  &constructor,
  &destructor,
  &begin,
  &end,
  &size,
  &max_size,
  &resize,
  &empty,
  &at,
  &front,
  &back,
  &assign,
  &push_back,
  &push_front,
  &pop_back,
  &pop_front,
  &insert,
  &erase,
  &swap,
  &clear
};
