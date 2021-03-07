/*! \file    check-PDA.c
 *  \brief   Тесты для НКА
 */
#include <check.h>

#include "../pda.h"


int     g_Accepted_states[FINAL_STATES] = { q2 };     // The set F
char    g_alphabet[ALPHABET_CHARCTERS] = {'a', 'b', 'c'};  // The set Sigma
int     g_current_peak_indexes[TOTAL_STATES] = { 0, 0 };
p_int*  g_Transition_Table[TOTAL_STATES][ALPHABET_CHARCTERS + 1][MAGAZINE_CHARCTERS] = {}; // Transition function
int     g_automatic_magazine[TOTAL_STATES][AUTOMATIC_MAGAZINE_MAX_COUNT] = {};
p_int** g_pointers = NULL;
boolean g_Current_states[TOTAL_STATES] = {T,F}; /* Массив состояний, T(true) - состояние текущее
                                                       при старте программы текущее состояние имеет initial state
                                                       F(false) - состояние нетекущее */


START_TEST(pdatest_0)
{
    fail_unless(g_Current_states[q0] == T, "g_Current_states[q0] should be equal to T (initial state)");
}
END_TEST

START_TEST(pdatest_1)
{

    fail_unless(PDA('d') == UNKNOWN_SYMBOL_ERR, "PDA function should return UNKNOWN_SYMBOL_ERR when current_symbol='d'");
}
END_TEST

START_TEST(pdatest_2)
{
    fail_unless(PDA('a') == NOT_REACHED_FINAL_STATE, "PDA function should return NOT_REACHED_FINAL_STATE when current_symbol='a'");  
    fail_unless(g_Current_states[q0] == T, "g_Current_states[q0] should be equal to T");
}
END_TEST

START_TEST(pdatest_3)
{
    fail_unless(PDA('a') == NOT_REACHED_FINAL_STATE, "PDA function should return NOT_REACHED_FINAL_STATE when string = 'a'");  
    fail_unless(PDA('c') == REACHED_FINAL_STATE, "PDA function should return REACHED_FINAL_STATE when string = 'ac'");  
    fail_unless(g_Current_states[q2] == T, "g_Current_states[q2] should be equal to T");
    fail_unless(PDA('b') == NOT_REACHED_FINAL_STATE, "PDA function should return NOT_REACHED_FINAL_STATE when string = 'acb'");  
    fail_unless(PDA('b') == NOT_REACHED_FINAL_STATE, "PDA function should return NOT_REACHED_FINAL_STATE when string = 'acbb'");  
    fail_unless(g_Current_states[q0] == T, "g_Current_states[q0] should be equal to T");

    fail_unless(PDA('c') == NOT_REACHED_FINAL_STATE, "PDA function should return NOT_REACHED_FINAL_STATE when string = 'acbbc'");  
    fail_unless(PDA('c') == REACHED_FINAL_STATE, "PDA function should return REACHED_FINAL_STATE when string = 'acbbcc'");  
}
END_TEST

START_TEST(pdatest_4)
{
    fail_unless(PDA('a') == NOT_REACHED_FINAL_STATE, "PDA function should return NOT_REACHED_FINAL_STATE when string = 'a'");  
    fail_unless(PDA('b') == NOT_REACHED_FINAL_STATE, "PDA function should return NOT_REACHED_FINAL_STATE when string = 'ab'");  
    fail_unless(PDA('c') == NOT_REACHED_FINAL_STATE, "PDA function should return NOT_REACHED_FINAL_STATE when string = 'abc'");  
  
}
END_TEST

START_TEST(pdatest_5)
{
    fail_unless(PDA('c') == NOT_REACHED_FINAL_STATE, "PDA function should return NOT_REACHED_FINAL_STATE when string = 'c'");  
    fail_unless(PDA('c') == NOT_REACHED_FINAL_STATE, "PDA function should return NOT_REACHED_FINAL_STATE when string = 'cc'");  
    fail_unless(PDA('c') == NOT_REACHED_FINAL_STATE, "PDA function should return NOT_REACHED_FINAL_STATE when string = 'ccc'");  
    fail_unless(PDA('a') == NOT_REACHED_FINAL_STATE, "PDA function should return NOT_REACHED_FINAL_STATE when string = 'ccca'");  
    fail_unless(PDA('b') == NOT_REACHED_FINAL_STATE, "PDA function should return NOT_REACHED_FINAL_STATE when string = 'cccab");  
    fail_unless(PDA('b') == REACHED_FINAL_STATE, "PDA function should return REACHED_FINAL_STATE when string = 'cccabb'");  
  
}
END_TEST

int main(void)
{
  for (size_t i = 0; i < TOTAL_STATES; ++i)
  {
    g_automatic_magazine[i][g_current_peak_indexes[i]] = _Z;
    g_automatic_magazine[i][g_current_peak_indexes[i] + 1] = _e;
  }

  if (SetPDA_Transitions() == F) // Fill transition table
  {
    printf("memory allocated error");
    return EXIT_FAILURE;
  }   

  Suite *s1 = suite_create("Core");
  TCase *tc1_1 = tcase_create("PDA");
  SRunner *sr = srunner_create(s1);
  int nf;

  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, pdatest_0);
  tcase_add_test(tc1_1, pdatest_1);
  tcase_add_test(tc1_1, pdatest_2);
  tcase_add_test(tc1_1, pdatest_3);
  tcase_add_test(tc1_1, pdatest_4);
  tcase_add_test(tc1_1, pdatest_5);
  srunner_run_all(sr, CK_NORMAL);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
