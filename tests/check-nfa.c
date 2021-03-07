/*! \file    check-nfa.c
 *  \brief   Тесты для НКА
 */
#include <check.h>

#include "../nfa.h"


int  g_Accepted_states[FINAL_STATES] = { q2, q3, q4};     // The set F
char g_alphabet[ALPHABET_CHARCTERS] = {'a', 'b'};  // The set Sigma
p_int* g_Transition_Table[TOTAL_STATES][ALPHABET_CHARCTERS] = {}; // Transition function
p_int** g_pointers = NULL;
boolean g_Current_states[TOTAL_STATES] = {T,F,F,F,F}; // Start state of NFA


START_TEST(nfatest_0)
{
    fail_unless(g_Current_states[q0] == T, "g_Current_states[q0] should be equal to T (initial state)");
}
END_TEST

START_TEST(nfatest_1)
{

    fail_unless(NFA('c') == UNKNOWN_SYMBOL_ERR, "nfa function should return UNKNOWN_SYMBOL_ERR when current_symbol='c'");
}
END_TEST

START_TEST(nfatest_2)
{
    fail_unless(NFA('a') == NOT_REACHED_FINAL_STATE, "nfa function should return NOT_REACHED_FINAL_STATE when current_symbol='a'");  
    fail_unless(g_Current_states[q1] == T, "g_Current_states[q1] should be equal to T");
}
END_TEST

START_TEST(nfatest_3)
{
    fail_unless(NFA('a') == NOT_REACHED_FINAL_STATE, "nfa function should return NOT_REACHED_FINAL_STATE when string = 'a'");  
    fail_unless(NFA('b') == REACHED_FINAL_STATE, "nfa function should return REACHED_FINAL_STATE when string = 'ab'");  
    fail_unless(g_Current_states[q2] == T, "g_Current_states[q2] should be equal to T");
    fail_unless(NFA('a') == REACHED_FINAL_STATE, "nfa function should return REACHED_FINAL_STATE when string = 'aba'");  
    fail_unless(NFA('b') == REACHED_FINAL_STATE, "nfa function should return REACHED_FINAL_STATE when string = 'abab'");  
    fail_unless(g_Current_states[q3] == T, "g_Current_states[q3] should be equal to T");
    fail_unless(g_Current_states[q2] == T, "g_Current_states[q2] should be equal to T");

    fail_unless(NFA('a') == REACHED_FINAL_STATE, "nfa function should return REACHED_FINAL_STATE when string = 'ababa'");  
    fail_unless(NFA('b') == REACHED_FINAL_STATE, "nfa function should return REACHED_FINAL_STATE when string = 'ababab'");  
    fail_unless(g_Current_states[q2] == T, "g_Current_states[q2] should be equal to T");
    fail_unless(g_Current_states[q3] == T, "g_Current_states[q3] should be equal to T");
    fail_unless(NFA('a') == REACHED_FINAL_STATE, "nfa function should return REACHED_FINAL_STATE when string = 'abababa'");  
}
END_TEST

START_TEST(nfatest_4)
{
    fail_unless(NFA('a') == NOT_REACHED_FINAL_STATE, "nfa function should return NOT_REACHED_FINAL_STATE when string = 'a'");  
    fail_unless(NFA('b') == REACHED_FINAL_STATE, "nfa function should return REACHED_FINAL_STATE when string = 'ab'");  
    fail_unless(NFA('a') == REACHED_FINAL_STATE, "nfa function should return REACHED_FINAL_STATE when string = 'aba'");  
    fail_unless(NFA('b') == REACHED_FINAL_STATE, "nfa function should return REACHED_FINAL_STATE when string = 'abab'");  
    fail_unless(NFA('b') == REACHED_FINAL_STATE, "nfa function should return REACHED_FINAL_STATE when string = 'ababb");  
    fail_unless(NFA('b') == REACHED_FINAL_STATE, "nfa function should return REACHED_FINAL_STATE when string = 'ababbb'");  
  
}
END_TEST

START_TEST(nfatest_5)
{
    fail_unless(NFA('a') == NOT_REACHED_FINAL_STATE, "nfa function should return NOT_REACHED_FINAL_STATE when string = 'a'");  
    fail_unless(NFA('b') == REACHED_FINAL_STATE, "nfa function should return REACHED_FINAL_STATE when string = 'ab'");  
    fail_unless(NFA('a') == REACHED_FINAL_STATE, "nfa function should return REACHED_FINAL_STATE when string = 'aba'");  
    fail_unless(NFA('a') == REACHED_FINAL_STATE, "nfa function should return REACHED_FINAL_STATE when string = 'abaa'");  
    fail_unless(NFA('b') == REACHED_FINAL_STATE, "nfa function should return REACHED_FINAL_STATE when string = 'abaab");  
    fail_unless(NFA('b') == NOT_REACHED_FINAL_STATE, "nfa function should return REACHED_FINAL_STATE when string = 'abaabb'");  
  
}
END_TEST

int main(void)
{
  if (SetNFA_Transitions() == F) // Fill transition table
  {
    printf("memory allocated error");
    return EXIT_FAILURE;
  }   

  Suite *s1 = suite_create("Core");
  TCase *tc1_1 = tcase_create("NFA");
  SRunner *sr = srunner_create(s1);
  int nf;

  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, nfatest_0);
  tcase_add_test(tc1_1, nfatest_1);
  tcase_add_test(tc1_1, nfatest_2);
  tcase_add_test(tc1_1, nfatest_3);
  tcase_add_test(tc1_1, nfatest_4);
  tcase_add_test(tc1_1, nfatest_5);
  srunner_run_all(sr, CK_NORMAL);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
