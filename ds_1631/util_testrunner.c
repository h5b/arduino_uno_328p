#include <stdlib.h>
#include <check.h>

#include "util.h"

START_TEST(tc_uitoa)
{
	unsigned int i = 0;
	char result[CHAR_BUFFER_SIZE];

	/* Set of test data */
	const unsigned int intValues [] = {3, 8, 10, 19, 20, 31, 40};
	const char *stringValues [] = {"3", "8", "10", "19", "20", "31", "40"};

	for (i = 0; i < sizeof(intValues) / sizeof(intValues[0]); i++) {
		uitoa(result, intValues[i]);
		fail_if(strcmp(result, stringValues[i]) != 0,
			"Got %s instead of %s", result, stringValues[i]);
	}
}
END_TEST

Suite *
test_utilSuite(void)
{
	Suite *s = suite_create("Util");

	TCase *tc_core = tcase_create("uitoa()");
	tcase_add_test(tc_core, tc_uitoa);
	suite_add_tcase(s, tc_core);

	return s;
}

int
main (void)
{
	int number_failed;

	Suite *s = test_utilSuite();
	SRunner *sr = srunner_create(s);

	srunner_run_all(sr, CK_NORMAL);
	number_failed = srunner_ntests_failed(sr);
	srunner_free (sr);

	return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
