#ifndef LIST_H_
# define LIST_H_

# include <stdlib.h>
# include <stdbool.h>
# include "iterator.h"

typedef struct s_list	list;
typedef bool (*Predicate)(const value_type val);
typedef bool (*Compare)(const value_type a, const value_type b);

struct		s_list
{
  iterator	content;
  size_type	size;
};

struct s_list_class
{
  void		(*constructor)(list *this);
  void		(*destructor)(list *this);

  iterator	(*begin)(list *this);
  iterator	(*end)(list *this);

  bool		(*empty)(list *this);
  size_type	(*size)(list *this);
  size_type	(*max_size)(list *this);

  void		*(*front)(list *this);
  void		*(*back)(list *this);

  void		(*assign)(list *this, iterator first, iterator last);
  void		(*push_front)(list *this, const value_type val);
  void		(*pop_front)(list *this);
  void		(*push_back)(list *this, const value_type val);
  void		(*pop_back)(list *this);
  iterator	(*insert)(list *this, iterator position, const value_type val);
  iterator	(*erase)(list *this, iterator position);
  void		(*swap)(list *this, list *x);
  void		(*resize)(list *this, size_type n);
  void		(*clear)(list *this);

  void		(*splice)(list *this, iterator position, list *x);
  void		(*remove)(list *this, const value_type val);
  void		(*remove_if)(list *this, Predicate pred);
  void		(*unique)(list *this);
  void		(*merge)(list *this, list *x);
  void		(*sort)(list *this, Compare comp);
  void		(*reverse)(list *this);
};

extern struct s_list_class	g_list;

#endif /* !LIST_H_ */
