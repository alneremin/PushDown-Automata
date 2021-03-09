/*! \file    main.c
 *  \brief   Построение НКА с количеством состояний, не превышающим 5, 
 *           для языка {aba(b^n) : n ≥ 0} U {ab(a^n) : n ≥ 0}
 */
#include "pda.h"

#define assert__(x) for ( ; !(x) ; assert(x) )

int     g_Accepted_states[FINAL_STATES] = { q2 };     // The set F
char    g_alphabet[ALPHABET_CHARCTERS] = {'a', 'b', 'c'};  // The set Sigma
int     g_current_peak_indexes[TOTAL_STATES] = { 0, 0 };
p_int*  g_Transition_Table[TOTAL_STATES][ALPHABET_CHARCTERS + 1][MAGAZINE_CHARCTERS] = {}; // Transition function
int     g_automatic_magazine[TOTAL_STATES][AUTOMATIC_MAGAZINE_MAX_COUNT] = {};
p_int** g_pointers = NULL;
boolean g_Current_states[TOTAL_STATES] = {T,F}; /* Массив состояний, T(true) - состояние текущее
                                                       при старте программы текущее состояние имеет initial state
                                                       F(false) - состояние нетекущее */

/*!
 * \brief   Точка входа в программу
 * \return  EXIT_SUCCESS (0) при успешном завершении
 *          EXIT_FAILURE (1) при наличии ошибок
 */
int main(int argc, const char* argv[])
{

  assert__(argc == 2) {
    printf("Please enter a string with 'a' s and 'b's as parameter\n"); 
  }
  
  int result = run(argv[1], strlen(argv[1]));

  if (EXIT_SUCCESS == result)  
  {
    printf("Accepted");
  }
  else
  {
    printf("Rejected");
  }
  printf("\n\n");

  return EXIT_SUCCESS;
}

/*!
 * \brief   Функция вычисления принадлежности цепочки языку
 * \return  EXIT_SUCCESS (0) при успешном завершении
 *          EXIT_FAILURE (1) при наличии ошибок
 */
int run(const char string[], int count)
{ 
  char current_symbol;
  for (size_t i = 0; i < TOTAL_STATES; ++i)
  {
    g_current_peak_indexes[i] = 0;
    g_automatic_magazine[i][g_current_peak_indexes[i]] = _Z;
    g_automatic_magazine[i][g_current_peak_indexes[i] + 1] = _e;
  }
  
  int result = REACHED_FINAL_STATE; // для нашего случая начальное состояние - недопустимое
  
  if (SetPDA_Transitions() == F) // Fill transition table
  {
    printf("memory allocated error");
    return EXIT_FAILURE;
  }    

  if (count > 0)
  {
    for (size_t i = 0; i < count; ++i)
    {
      current_symbol = string[i];
      result = PDA(current_symbol);
      if (REACHED_FINAL_STATE != result && NOT_REACHED_FINAL_STATE != result)
      {
        break;
      }
    }
  }
  

  if (REACHED_FINAL_STATE == result)  
  {
    return EXIT_SUCCESS;
  }
  else
  {
    return EXIT_FAILURE;
  }

}