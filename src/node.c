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



static TagLabelList *
tag_label_new(const char *label);

static void
tag_label_free(TagLabelList *label_list);

static int
tag_node_find_label(TagNode *node, const char *label,
	TagLabelList **previous_label_list, TagLabelList **current_label_list);

static TagPropList *
tag_prop_new(const char *key, TagPropValue *value);

static void
tag_prop_free(TagPropList *prop_list);

static int
tag_node_find_prop(TagNode *node, const char *key,
	TagPropList **previous_prop_list, TagPropList **current_prop_list);



TagNode *
tag_node_new()
{
	TagNode *node = (TagNode *)malloc(sizeof(TagNode));
	memset(node, 0, sizeof(TagNode));
	return node;
}

void
tag_node_free(TagNode *node)
{
	TagLabelList *label_list;
	TagPropList *prop_list;
	while (NULL != node->label_list)
	{
		label_list = node->label_list;
		node->label_list = node->label_list->next;
		tag_label_free(label_list);
	}

	while (NULL != node->prop_list)
	{
		prop_list = node->prop_list;
		node->prop_list = node->prop_list->next;
		tag_prop_free(prop_list);
	}

	free(node);
}

static TagLabelList *
tag_label_new(const char *label)
{
	TagLabelList *label_list = (TagLabelList *)malloc(sizeof(TagLabelList));
	memset(label_list, 0, sizeof(TagLabelList));
	label_list->label = strdup(label);
	return label_list;
}

static void
tag_label_free(TagLabelList *label_list)
{
	free(label_list->label);
	free(label_list);
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
		current_label_list = tag_label_new(label);
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
		tag_label_free(current_label_list);
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

static TagPropList *
tag_prop_new(const char *key, TagPropValue *value)
{
	TagPropList *prop_list = (TagPropList *)malloc(sizeof(TagPropList));
	memset(prop_list, 0, sizeof(TagPropList));
	prop_list->key = strdup(key);
	if (NULL != value)
	{
		memcpy(&prop_list->value, value, sizeof(TagPropValue));
	}
	return prop_list;
}

static void
tag_prop_free(TagPropList *prop_list)
{
	free(prop_list->key);
	free(prop_list);
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
		return &current_prop_list->value;
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
		current_prop_list = tag_prop_new(key, value);
		current_prop_list->next = node->prop_list;
		node->prop_list = current_prop_list;
		++node->prop_count;
	}
}

void
tag_node_unset_prop(TagNode *node, const char *key)
{
	TagPropList *previous_prop_list,
	            *current_prop_list;

	if (tag_node_find_prop(node, key, &previous_prop_list, &current_prop_list))
	{
		if (NULL == previous_prop_list)
		{
			node->prop_list = current_prop_list->next;
		}
		else
		{
			previous_prop_list->next = current_prop_list->next;
		}
		tag_prop_free(current_prop_list);
		--node->prop_count;
	}
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
