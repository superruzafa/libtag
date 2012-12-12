#include <tag/tag.h>
#include <malloc.h>
#include <string.h>

typedef struct _TagLabelList
{
	char *label;
	struct _TagLabelList *next;
}
TagLabelList;

struct _TagNode
{
	TagLabelList *label_list;
	int label_count;
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

void
tag_node_free(TagNode *node)
{
	free(node);
}
