#include <tag/list.h>
#include <malloc.h>

struct _TagList
{
	int pepe;
};

TagList *
tag_list_new()
{
	TagList *taglist = (TagList *)malloc(sizeof(struct _TagList));
}

void
tag_list_free(TagList *taglist)
{
	free(taglist);
}
