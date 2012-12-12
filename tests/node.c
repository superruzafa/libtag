#include <check.h>
#include <tag/tag.h>

TagNode *node;

void
node_setup()
{
	node = tag_node_new();
}

void
node_teardown (void)
{
	tag_node_free(node);
}

START_TEST(test_node_empty)
{
	fail_unless(0 == tag_node_get_label_count(node));
	fail_unless(0 == tag_node_get_prop_count(node));
}
END_TEST

START_TEST(test_node_add_label_to_empty_node)
{
	tag_node_add_label(node, "foo");
	fail_unless(1 == tag_node_get_label_count(node));
	fail_unless(0 != tag_node_has_label(node, "foo"));
}
END_TEST

START_TEST(test_node_add_labels)
{
	tag_node_add_label(node, "foo");
	tag_node_add_label(node, "bar");
	fail_unless(2 == tag_node_get_label_count(node));
	fail_unless(0 != tag_node_has_label(node, "foo"));
	fail_unless(0 != tag_node_has_label(node, "bar"));
}
END_TEST

START_TEST(test_node_add_label_twice)
{
	tag_node_add_label(node, "foo");
	tag_node_add_label(node, "bar");
	tag_node_add_label(node, "foo");
	fail_unless(2 == tag_node_get_label_count(node));
	fail_unless(0 != tag_node_has_label(node, "foo"));
	fail_unless(0 != tag_node_has_label(node, "bar"));
}
END_TEST

START_TEST(test_node_remove_label_from_empty_node)
{
	tag_node_remove_label(node, "foo");
	fail_unless(0 == tag_node_get_label_count(node));
	fail_unless(0 == tag_node_has_label(node, "foo"));
}
END_TEST

START_TEST(test_node_remove_label)
{
	tag_node_add_label(node, "foo");
	tag_node_add_label(node, "bar");
	tag_node_remove_label(node, "foo");
	fail_unless(1 == tag_node_get_label_count(node));
	fail_unless(0 == tag_node_has_label(node, "foo"));
	fail_unless(0 != tag_node_has_label(node, "bar"));
}
END_TEST

START_TEST(test_node_remove_label_twice)
{
	tag_node_add_label(node, "foo");
	tag_node_add_label(node, "bar");
	tag_node_remove_label(node, "foo");
	tag_node_remove_label(node, "foo");
	fail_unless(1 == tag_node_get_label_count(node));
	fail_unless(0 == tag_node_has_label(node, "foo"));
	fail_unless(0 != tag_node_has_label(node, "bar"));
}
END_TEST

START_TEST(test_node_add_and_remove_labels)
{
	tag_node_add_label(node, "foo");
	tag_node_add_label(node, "bar");
	tag_node_add_label(node, "baz");
	tag_node_remove_label(node, "bar");
	tag_node_remove_label(node, "baz");
	tag_node_remove_label(node, "foo");
	fail_unless(0 == tag_node_get_label_count(node));
	fail_unless(0 == tag_node_has_label(node, "foo"));
	fail_unless(0 == tag_node_has_label(node, "bar"));
	fail_unless(0 == tag_node_has_label(node, "baz"));
}
END_TEST



START_TEST(test_node_set_null_property)
{
	tag_node_set_prop(node, "foo", NULL);
	const TagPropValue *value = tag_node_get_prop(node, "foo");
	fail_unless(TagPropType_Object == value->type);
	fail_unless(NULL == value->value.object);
}
END_TEST

START_TEST(test_node_set_property)
{
	TagPropValue value = {TagPropType_Integer, 123},
	             *value2;
	tag_node_set_prop(node, "foo", & value);
	value2 = tag_node_get_prop(node, "foo");
	fail_unless(TagPropType_Integer == value2->type);
	fail_unless(123 == value2->value.integer);

}
END_TEST



void
add_node_tests(Suite *suite)
{
	TCase *tcase = tcase_create("labels");
	tcase_add_checked_fixture (tcase, node_setup, node_teardown);

	tcase_add_test(tcase, test_node_empty);
	tcase_add_test(tcase, test_node_add_label_to_empty_node);
	tcase_add_test(tcase, test_node_add_labels);
	tcase_add_test(tcase, test_node_add_label_twice);
	tcase_add_test(tcase, test_node_remove_label_from_empty_node);
	tcase_add_test(tcase, test_node_remove_label);
	tcase_add_test(tcase, test_node_remove_label_twice);
	tcase_add_test(tcase, test_node_add_and_remove_labels);

	suite_add_tcase(suite, tcase);

	tcase = tcase_create("properties");
	tcase_add_checked_fixture (tcase, node_setup, node_teardown);

	tcase_add_test(tcase, test_node_empty);
	tcase_add_test(tcase, test_node_set_null_property);
	tcase_add_test(tcase, test_node_set_property);

	suite_add_tcase(suite, tcase);
}

