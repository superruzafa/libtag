#ifndef __NODE_H__
#define __NODE_H__

typedef struct _TagNode TagNode;

TagNode *
tag_node_new();

void
tag_node_add_label(TagNode *node, const char *label);

void
tag_node_remove_label(TagNode *node, const char *label);

int
tag_node_has_label(TagNode *node, const char *label);

int
tag_node_get_label_count(TagNode *node);

void
tag_node_free(TagNode *node);

#endif
