#include <tag/tag.h>
#include <malloc.h>
#include <string.h>

typedef struct _TagLabelList
{
	char *label;
	struct _TagLabelList *next;
}
TagLabelList;

typedef struct _TagPropList
{
	char *key;
	TagPropValue value;
	struct _TagPropList *next;
}
TagPropList;

struct _TagNode
{
	TagLabelList *label_list;
	int label_count;

	TagPropList *prop_list;
	int prop_count;

	struct _TagNode *next;
};

TagNode *
tag_node_new()
{
	TagNode *node = (TagNode *)malloc(sizeof(TagNode));
	memset(node, 0, sizeof(TagNode));
	return node;
}

static int
tag_node_find_label(TagNode *node, const char *label,
	TagLabelList **previous_label_list, TagLabelList **current_label_list)
{
	*previous_label_list = NULL;
	*current_label_list = node->label_list;

	while (NULL != *current_label_list)
	{
		if (0 == strcmp((*current_label_list)->label, label))
		{
			return 1;
		}
		*previous_label_list = *current_label_list;
		*current_label_list = (*current_label_list)->next;
	}
	return 0;
}

void
tag_node_add_label(TagNode *node, const char *label)
{
	TagLabelList *previous_label_list, *current_label_list;
	if (!tag_node_find_label(node, label, &previous_label_list, &current_label_list))
	{
		current_label_list = (TagLabelList *)malloc(sizeof(TagLabelList));
		memset(current_label_list, 0, sizeof(TagLabelList));
		current_label_list->label = strdup(label);
		current_label_list->next = node->label_list;
		node->label_list = current_label_list;
		++node->label_count;
	}
}

void
tag_node_remove_label(TagNode *node, const char *label)
{
	TagLabelList *previous_label_list, *current_label_list;
	if (tag_node_find_label(node, label, &previous_label_list, &current_label_list))
	{
		if (NULL == previous_label_list)
		{
			node->label_list = current_label_list->next;
		}
		else
		{
			previous_label_list->next = current_label_list->next;
		}
		free(current_label_list->label);
		free(current_label_list);
		--node->label_count;
	}
}

int
tag_node_has_label(TagNode *node, const char *label)
{
	TagLabelList *previous_label_list, *current_label_list;
	return tag_node_find_label(node, label,
		&previous_label_list, &current_label_list);
}

int
tag_node_get_label_count(TagNode *node)
{
	return node->label_count;
}

static int
tag_node_find_prop(TagNode *node, const char *key,
	TagPropList **previous_prop_list, TagPropList **current_prop_list)
{
	*previous_prop_list = NULL;
	*current_prop_list = node->prop_list;

	while (NULL != *current_prop_list)
	{
		if (0 == strcmp((*current_prop_list)->key, key))
		{
			return 1;
		}
		*previous_prop_list = *current_prop_list;
		*current_prop_list = (*current_prop_list)->next;
	}
	return 0;
}

const TagPropValue *
tag_node_get_prop(TagNode *node, const char *key)
{
	TagPropList *previous_prop_list,
	            *current_prop_list;

	if (tag_node_find_prop(node, key, &previous_prop_list, &current_prop_list))
	{
		return & current_prop_list->value;
	}
	return NULL;
}

void
tag_node_set_prop(TagNode *node, const char *key, const TagPropValue *value)
{
	TagPropList *previous_prop_list,
	            *current_prop_list;

	if (!tag_node_find_prop(node, key, &previous_prop_list, &current_prop_list))
	{
		current_prop_list = (TagPropList *)malloc(sizeof(TagPropList));
		memset(current_prop_list, 0, sizeof(TagPropList));
		current_prop_list->next = node->prop_list;
		node->prop_list = current_prop_list;
	}
	memcpy(&current_prop_list->value, value, sizeof(TagPropValue));
}

int
tag_node_has_prop(TagNode *node, const char *key)
{
	TagPropList *previous_prop_list,
	            *current_prop_list;

	return tag_node_find_prop(node, key, &previous_prop_list, &current_prop_list);
}

int
tag_node_get_prop_count(TagNode *node)
{
	return node->prop_count;
}

void
tag_node_free(TagNode *node)
{
	free(node);
}
