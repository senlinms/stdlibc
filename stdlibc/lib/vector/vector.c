/*
** vector.c for vector in /home/davy/Rendu/stdlibc/stdlibc
**
** Made by davy tran
** Login   <tran_y@epitech.net>
**
** Started on  Wed Feb  4 19:22:11 2015 davy tran
** Last update Wed Sep 30 17:31:30 2015 davy
*/

#include <string.h>
#include "vector.h"

/*
** Private method for link case array between them.
**
** Attributes:
**	this (vector) -- Vector instance.
*/
static void _link(vector *this)
{
  if (this->content != NULL)
    for (size_t i = 0; i + 1 < this->size && this->content[i] != NULL; ++i)
    {
      if (this->content[i] != NULL)
        this->content[i]->forward = this->content[i + 1];
      if (this->content[i + 1] != NULL)
        this->content[i + 1]->rewind = this->content[i];
    }
}

static void constructor(vector *this)
{
  if (this != NULL)
    memset(this, 0, sizeof(*this));
}

static void destructor(vector *this)
{
  if (this == NULL)
    return ;
  g_vector.clear(this);
}

static iterator begin(vector *this)
{
  return (this != NULL && this->content != NULL ? this->content[0] : NULL);
}

static iterator end(vector *this)
{
  return (this->size > 0 ? this->content[this->size - 1] : NULL);
}

static size_type  size(vector const *this)
{
  size_type       n;

  for (n = 0; this->content != NULL &&
              n < this->size && this->content[n] != NULL; ++n);
  return (n);
}

static size_type  max_size(vector *this)
{
  return ((size_type)this);
}

static void resize(vector *this, size_type n)
{
  size_type len;

  if (n < (len = size(this)))
    this->content[n] = NULL;
  for (this->size = 1; this->size < n; this->size <<= 1)
    ;
  this->content = realloc(this->content, this->size * sizeof(*this->content));
  this->size = this->content != NULL ? this->size : 0;
  for (; len < this->size; ++len)
    this->content[len] = NULL;
  _link(this);
}

static size_t capacity(vector *this)
{
  return (this->size);
}

static bool empty(vector *this)
{
  return (this->content == NULL || this->size == 0);
}

static void reserve(vector *this, size_type n)
{
  for (size_type i = n; i < this->size && this->content[i] != NULL; ++i)
  {
    free(this->content[i]);
    this->content[i] = NULL;
  }
  this->content = realloc(this->content, sizeof(*this->content) * n);
  if (this->content == NULL)
    exit(EXIT_FAILURE);
  for (; this->size < n; ++this->size)
    this->content[this->size] = NULL;
  _link(this);
}

static void *at(vector const *this, size_type n)
{
  iterator		*content;

  content = this->content;
  return (n < size(this) && content && content[n] ? content[n]->value : NULL);
}

static void *front(vector *this)
{
  return (at(this, 0));
}

static void *back(vector *this)
{
  return (this->content != NULL ? at(this, size(this) - 1) : NULL);
}

static void assign(vector *this, InputIterator first, InputIterator last)
{
  g_vector.clear(this);
  for (iterator it = first; it != last && it != NULL; next(it))
    g_vector.push_back(this, first->value);
}

static void push_back(vector *this, const value_type val)
{
  size_type len;
  iterator  it;
  size_t    i;

  len = size(this);
  if ((len + 1) > capacity(this))
    resize(this, len + 1);
  if ((it = calloc(sizeof(*it), 1)) == NULL)
    exit(EXIT_FAILURE);
  it->value = val;
  for (i = 0; this->content[i] != NULL; ++i)
    ;
  this->content[i] = it;
  _link(this);
}

static void pop_back(vector *this)
{
  iterator  it;
  size_t		n;

  if ((it = g_vector.end(this)) != NULL && it->rewind != NULL)
  {
    it->rewind->forward = NULL;
    free(it);
    if ((n = size(this)) > 0)
      this->content[n - 1] = NULL;
  }
  else if (it != NULL && it->rewind == NULL)
    it->value = NULL;
}

static iterator insert(__attribute__((unused))vector *this, __attribute__((unused))iterator position, __attribute__((unused))const value_type val)
{
  return (NULL);
}

static iterator erase(__attribute__((unused))vector *this, __attribute__((unused))iterator position)
{
  return (NULL);
}

static void swap(vector *this, vector *x)
{
  SWAP_PTR(this->content, x->content);
}

static void clear(vector *this)
{
  if (this->content == NULL)
    return ;
  for (size_t i = 0; i < this->size; ++i)
  {
    free(this->content[i]);
    this->content[i] = NULL;
  }
  free(this->content);
  this->content = NULL;
}

struct s_vector_class	g_vector = {
  &constructor,
  &destructor,
  &begin,
  &end,
  &size,
  &max_size,
  &resize,
  &capacity,
  &empty,
  &reserve,
  &at,
  &front,
  &back,
  &assign,
  &push_back,
  &pop_back,
  &insert,
  &erase,
  &swap,
  &clear
};
