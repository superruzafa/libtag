#ifndef __LIST_H__
#define __LIST_H__

typedef struct _TagList *TagList;

TagList *
tag_list_new();

void
tag_list_free(TagList *taglist);

#endif
