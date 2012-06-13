#include <stdlib.h>
#include <check.h>

#include "util.h"

typedef struct {
	unsigned int uint_val;
	char* string_val;
} int_string_mapping_t;

typedef struct {
	unsigned int len;
	char* str;
} string_length_t;

START_TEST(tc_uitoa)
{
	unsigned int i = 0;

	/*
	 * Set of test data
	 * for i in `jot -r 99 1 99`; do echo "{$i, \"$i\"},"; done
	 */
	int_string_mapping_t result_map[] =
	{
		{89, "89"},
		{12, "12"},
		{29, "29"},
		{52, "52"},
		{11, "11"},
		{84, "84"},
		{69, "69"},
		{48, "48"},
		{58, "58"},
		{1, "1"},
		{90, "90"},
		{89, "89"},
		{29, "29"},
		{64, "64"},
		{39, "39"},
		{95, "95"},
		{38, "38"},
		{9, "9"},
		{5, "5"},
		{22, "22"},
		{1, "1"},
		{50, "50"},
		{92, "92"},
		{98, "98"},
		{80, "80"},
		{42, "42"},
		{40, "40"},
		{97, "97"},
		{37, "37"},
		{91, "91"},
		{82, "82"},
		{26, "26"},
		{1, "1"},
		{11, "11"},
		{75, "75"},
		{9, "9"},
		{92, "92"},
		{44, "44"},
		{56, "56"},
		{48, "48"},
		{44, "44"},
		{46, "46"},
		{38, "38"},
		{70, "70"},
		{8, "8"},
		{76, "76"},
		{66, "66"},
		{45, "45"},
		{84, "84"},
		{68, "68"},
		{66, "66"},
		{83, "83"},
		{18, "18"},
		{59, "59"},
		{81, "81"},
		{95, "95"},
		{98, "98"},
		{20, "20"},
		{93, "93"},
		{35, "35"},
		{9, "9"},
		{75, "75"},
		{60, "60"},
		{9, "9"},
		{83, "83"},
		{33, "33"},
		{17, "17"},
		{75, "75"},
		{74, "74"},
		{70, "70"},
		{24, "24"},
		{16, "16"},
		{14, "14"},
		{59, "59"},
		{86, "86"},
		{21, "21"},
		{35, "35"},
		{50, "50"},
		{65, "65"},
		{17, "17"},
		{18, "18"},
		{30, "30"},
		{97, "97"},
		{35, "35"},
		{86, "86"},
		{77, "77"},
		{28, "28"},
		{84, "84"},
		{94, "94"},
		{21, "21"},
		{18, "18"},
		{3, "3"},
		{93, "93"},
		{75, "75"},
		{11, "11"},
		{74, "74"},
		{9, "9"},
		{25, "25"},
		{48, "48"},
	};

	char result[sizeof(result_map)/sizeof(int_string_mapping_t)];

	for (i = 0; i < sizeof(result_map)/sizeof(int_string_mapping_t); i++) {
		uitoa(result, result_map[i].uint_val);
		fail_if(strcmp(result, result_map[i].string_val) != 0,
			"Got %s instead of %s", result,
			    result_map[i].string_val);
	}
}
END_TEST

START_TEST(tc_slen)
{
	unsigned int i = 0;

	/* Set of test data */
	string_length_t result_map[] =
	{
		{27, "VAZGvbJTbHetVWMuTHURMNFSkEl"},
		{31, "eNpZqyWXwdwaCgoZaVuiwNqaXyOpbvg"},
		{8, "EathQhJP"},
		{16, "iyfvxZGVWansyCwy"},
		{22, "EHyCLEzcbuFaXTVSkZqBjR"},
		{25, "ZKDVfompjOPyutODiMOGMfRcc"},
		{32, "MytHHXOzNPLhvWWYKKCrCvkrgRuGTfgC"},
		{21, "WGCYpXqLKHXAoMZxtepgF"},
		{15, "nDtvwrAwZmOlcuT"},
		{19, "ZfUBbTULzfJhGKRrgoG"},
		{12, "SOBrIEeatlzH"},
		{9, "suGKJxChE"},
		{20, "bFQQCUIVoqZvTeKoSVsD"},
		{4, "jgRu"},
		{14, "DtlJFpWTrsGWVd"},
		{7, "wUmbDCY"},
		{6, "hXvcVU"},
		{5, "mEIPE"},
		{10, "UUfjgjXwsf"},
		{13, "HfxFvoXJjZRTs"},
		{24, "kLSzlVjNaOlaLBHlJJsuwrSm"},
		{17, "cndzEaryUtVfUBsmD"},
		{11, "TUJqCkIcmfy"},
		{2, "SC"},
		{28, "KWajFcDpDCdcdlldIrQIxMsdZjLX"},
		{0, ""},
		{23, "okWooyTJpkkkIPAXHUqRpFO"},
		{1, "F"},
		{3, "Imf"},
		{29, "ezWajjnoqgyZtstWlTfssZHzzxSVQ"},
		{30, "sHVWSDSUsmMEmIwXNMOzrZKUePJSOM"},
		{18, "vQkYOjPggdmUfznemV"},
		{26, "spXYlArEhVTEMrgdapYhFluYDj"},
	};

	for (i = 0; i < sizeof(result_map)/sizeof(int_string_mapping_t); i++) {
		fail_if(result_map[i].len != slen(result_map[i].str),
				"Got length of %d, expected %d",
			    result_map[i].len, slen(result_map[i].str));
	}
}
END_TEST

Suite *
test_utilSuite(void)
{
	Suite *s = suite_create("Util");
	TCase *tc_core = tcase_create("util functions");

	tcase_add_test(tc_core, tc_uitoa);
	tcase_add_test(tc_core, tc_slen);
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
