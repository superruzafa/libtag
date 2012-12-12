#ifndef __NODE_H__
#define __NODE_H__

typedef enum
{
	TagPropType_Object,
	TagPropType_Natural,
	TagPropType_Integer,
	TagPropType_Decimal,
	TagPropType_String
}
TagPropType;

typedef struct _TagPropValue
{
	TagPropType type;
	union {
		void * object;
		unsigned int natural;
		int integer;
		float decimal;
		char *string;
	} value;
}
TagPropValue;

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

const TagPropValue *
tag_node_get_prop(TagNode *node, const char *key);

void
tag_node_set_prop(TagNode *node, const char *key, const TagPropValue *value);

int
tag_node_has_prop(TagNode *node, const char *key);

int
tag_node_get_prop_count(TagNode *node);

void
tag_node_free(TagNode *node);

#endif
