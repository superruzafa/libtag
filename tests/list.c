#include <check.h>
#include <tag/tag.h>

START_TEST(test_list_create)
{
	TagList *taglist = tag_list_new();
	fail_if(NULL == taglist);
}
END_TEST

TCase *
get_list_testcase()
{
	TCase *testcase = tcase_create("List");
	
	// Add tests here
	tcase_add_test(testcase, test_list_create);
	
	return testcase;
}
