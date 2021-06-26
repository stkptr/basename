#ifndef TRIE_H
#define TRIE_H

#include "elist.h"

// Construct an element list from a base name
// Does not include favoring rules
struct element_list_s *elist_from_base_name(const char *name);

#endif