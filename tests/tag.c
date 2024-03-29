#include <check.h>
#include <stdlib.h>

int
main()
{
	Suite * suite = suite_create("libtag");
	
	add_node_tests(suite);
	
	SRunner *suite_runner = srunner_create(suite);
	srunner_run_all(suite_runner, CK_NORMAL);
	srunner_free(suite_runner);
	return (0 == srunner_ntests_failed(suite_runner)) ? EXIT_SUCCESS : EXIT_FAILURE;
}
