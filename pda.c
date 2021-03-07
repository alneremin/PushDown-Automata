/*! \file    nfa.c
 *  \brief   Определение состояния КА
 */
#include <stdlib.h>
#include "pda.h"

/*!
 * \brief   Инициализация дуг между состояниями
 * \return  F - при возникновения ошибок выделения памяти
 *          T - если дуги успещно созданы 
 */
boolean SetPDA_Transitions()
{

  if (!(g_pointers = (p_int**) calloc(DIFF_TRANSITION_COUNT, sizeof(p_int*)))) 
  {
    return F;
  }
  int sizes[DIFF_TRANSITION_COUNT] = {1,1,1,1,1,1,1,1,1,1,1,1,1};
  for (size_t i = 0; i < DIFF_TRANSITION_COUNT; ++i)
  {
    g_pointers[i] = CreateIntPointer(sizes[i]);
    if (g_pointers[i] == NULL)
    {
      FreePointers();
      return F;
    }
  }

  g_Transition_Table[q0][b][_a] = g_pointers[0];
  g_Transition_Table[q0][b][_a]->p[0] = q0;
  g_Transition_Table[q0][b][_a]->peak[0] = _b;
  g_Transition_Table[q0][b][_a]->peak[1] = _a;

  g_Transition_Table[q0][c][_Z] = g_pointers[1];
  g_Transition_Table[q0][c][_Z]->p[0] = q0;
  g_Transition_Table[q0][c][_Z]->peak[0] = _c;
  g_Transition_Table[q0][c][_Z]->peak[1] = _Z;

  g_Transition_Table[q0][a][_b] = g_pointers[2];
  g_Transition_Table[q0][a][_b]->p[0] = q0;
  g_Transition_Table[q0][a][_b]->peak[0] = _a;
  g_Transition_Table[q0][a][_b]->peak[1] = _b;

  g_Transition_Table[q0][a][_Z] = g_pointers[3];
  g_Transition_Table[q0][a][_Z]->p[0] = q0;
  g_Transition_Table[q0][a][_Z]->peak[0] = _a;
  g_Transition_Table[q0][a][_Z]->peak[1] = _Z;

  g_Transition_Table[q0][a][_c] = g_pointers[4];
  g_Transition_Table[q0][a][_c]->p[0] = q0;
  g_Transition_Table[q0][a][_c]->peak[0] = _e;
  g_Transition_Table[q0][a][_c]->peak[1] = _e;

  g_Transition_Table[q0][c][_a] = g_pointers[5];
  g_Transition_Table[q0][c][_a]->p[0] = q0;
  g_Transition_Table[q0][c][_a]->peak[0] = _e;
  g_Transition_Table[q0][c][_a]->peak[1] = _e;

  g_Transition_Table[q0][b][_c] = g_pointers[6];
  g_Transition_Table[q0][b][_c]->p[0] = q0;
  g_Transition_Table[q0][b][_c]->peak[0] = _e;
  g_Transition_Table[q0][b][_c]->peak[1] = _e;

  g_Transition_Table[q0][c][_b] = g_pointers[7];
  g_Transition_Table[q0][c][_b]->p[0] = q0;
  g_Transition_Table[q0][c][_b]->peak[0] = _e;
  g_Transition_Table[q0][c][_b]->peak[1] = _e;

  g_Transition_Table[q0][c][_c] = g_pointers[8];
  g_Transition_Table[q0][c][_c]->p[0] = q0;
  g_Transition_Table[q0][c][_c]->peak[0] = _c;
  g_Transition_Table[q0][c][_c]->peak[1] = _c;

  g_Transition_Table[q0][a][_a] = g_pointers[9];
  g_Transition_Table[q0][a][_a]->p[0] = q0;
  g_Transition_Table[q0][a][_a]->peak[0] = _a;
  g_Transition_Table[q0][a][_a]->peak[1] = _a;

  g_Transition_Table[q0][b][_b] = g_pointers[10];
  g_Transition_Table[q0][b][_b]->p[0] = q0;
  g_Transition_Table[q0][b][_b]->peak[0] = _b;
  g_Transition_Table[q0][b][_b]->peak[1] = _b;

  g_Transition_Table[q0][b][_Z] = g_pointers[11];
  g_Transition_Table[q0][b][_Z]->p[0] = q0;
  g_Transition_Table[q0][b][_Z]->peak[0] = _b;
  g_Transition_Table[q0][b][_Z]->peak[1] = _Z;

  g_Transition_Table[q0][e][_Z] = g_pointers[12];
  g_Transition_Table[q0][e][_Z]->p[0] = q2;
  g_Transition_Table[q0][e][_Z]->peak[0] = _Z;
  g_Transition_Table[q0][e][_Z]->peak[1] = _e;

  return T;
}


void FreePointers() 
{
  for (size_t i = 0; i < DIFF_TRANSITION_COUNT; ++i)
  {
    free(g_pointers[i]->p); 
    free(g_pointers[i]);
  }
  free(g_pointers);
}


/*!
 * \brief Определение нового состояния системы
 * \param current_symbol Сигнал для перехода 
 * \return int Состояние системы
 */
int PDA(const char current_symbol)
{
  // задаем буфер состояний, чтобы в него вписать все изменения
  boolean current_states_buffer[TOTAL_STATES] = {F,F};  
  int i, pos, state, current_peak;
  for (pos = 0; pos < ALPHABET_CHARCTERS; ++pos)
    if (current_symbol == g_alphabet[pos])   
      break;     // stops if any character other than 0 or 1
  if (ALPHABET_CHARCTERS == pos)
    return UNKNOWN_SYMBOL_ERR;

  // производим спонтанные переходы
  for (size_t j = 0; j < TOTAL_STATES; ++j)
  {
    // если состояние является текущим 
    if (g_Current_states[j] == T)
    {

      // сохраняем текущий пик магазина состояния j
      current_peak = g_automatic_magazine[j][g_current_peak_indexes[j]];

      // если от состояния j есть спонтанный переход до какого-либо состояния
      if (g_Transition_Table[j][e][current_peak] != NULL)
      {
        // делаем текущими каждое из таких состояний
        for (i = 0; i < g_Transition_Table[j][e][current_peak]->size; ++i)
        {
          state = g_Transition_Table[j][e][current_peak]->p[i];

          g_Current_states[state] = T;

          // копируем наш магазин в новое состояние
          for (size_t k = 0; k < (g_current_peak_indexes[j] + 1); ++k)
          {
            g_automatic_magazine[state][k] = g_automatic_magazine[j][k];
          }

          // копируем индекс текущей вершины в состояние state
          g_current_peak_indexes[state] = g_current_peak_indexes[j];

          // заполняем символы замены в соответствии с таблицей g_Transition_Table
          g_automatic_magazine[state][g_current_peak_indexes[state]] = g_Transition_Table[j][e][current_peak]->peak[1];
          g_automatic_magazine[state][g_current_peak_indexes[state] + 1] = g_Transition_Table[j][e][current_peak]->peak[0];

          // изменяем индекс текущей вершины в зависимости от замены
          if (g_Transition_Table[j][e][current_peak]->peak[1] == _e) 
          {
            // если у нас не переход по пустому магазину
            if (current_peak != _e)
              g_current_peak_indexes[state]--;
          }
          else if (g_Transition_Table[j][e][current_peak]->peak[0] != _e)
          {
            g_current_peak_indexes[state]++;
          }
        }
        
      } 
    }
  }

  // производим неспонтанные переходы
  for (size_t j = 0; j < TOTAL_STATES; ++j)
  {
    // если состояние является текущим 
    if (g_Current_states[j] == T)
    {

      // делаем его нетекущим
      g_Current_states[j] = F;

      // сохраняем текущий пик магазина состояния j
      current_peak = g_automatic_magazine[j][g_current_peak_indexes[j]];

      // если от состояния j есть переход до какого-либо состояния
      if (g_Transition_Table[j][pos][current_peak] != NULL)
      {
        // делаем текущими каждое из таких состояний
        for (i = 0; i < g_Transition_Table[j][pos][current_peak]->size; ++i)
        {
          state = g_Transition_Table[j][pos][current_peak]->p[i];
          /* записываем, что состояние стало текущим в буфер
             чтобы не перекрыть старые значения состояний
             которые мы еще не прошли в цикле [j;TOTAL_STATES) */
          current_states_buffer[state] = T;

          if (state != j)
          {
            // копируем наш магазин в новое состояние
            for (size_t k = 0; k < (g_current_peak_indexes[j] + 1); ++k)
            {
              g_automatic_magazine[state][k] = g_automatic_magazine[j][k];
            }

            // копируем индекс текущей вершины в состояние state
            g_current_peak_indexes[state] = g_current_peak_indexes[j];

          }

          // заполняем символы замены в соответствии с таблицей g_Transition_Table
          g_automatic_magazine[state][g_current_peak_indexes[state]] = g_Transition_Table[j][pos][current_peak]->peak[1];
          g_automatic_magazine[state][g_current_peak_indexes[state] + 1] = g_Transition_Table[j][pos][current_peak]->peak[0];

          // изменяем индекс текущей вершины в зависимости от замены
          if (g_Transition_Table[j][pos][current_peak]->peak[1] == _e) 
          {
            // если у нас не переход по пустому магазину
            if (current_peak != _e)
              g_current_peak_indexes[state]--;
          }
          else if (g_Transition_Table[j][pos][current_peak]->peak[0] != _e)
          {
            g_current_peak_indexes[state]++;
          }
        }
        
      } 

    }
  }

  for (size_t j = 0; j < TOTAL_STATES; ++j)
  {
    g_Current_states[j] = current_states_buffer[j];
  }

  // опять производим спонтанные переходы
  for (size_t j = 0; j < TOTAL_STATES; ++j)
  {
    // если состояние является текущим 
    if (g_Current_states[j] == T)
    {

      // сохраняем текущий пик магазина состояния j
      current_peak = g_automatic_magazine[j][g_current_peak_indexes[j]];
      //printf(">%d\n", current_peak);
      // если от состояния j есть спонтанный переход до какого-либо состояния
      if (g_Transition_Table[j][e][current_peak] != NULL)
      {
        // делаем текущими каждое из таких состояний
        for (i = 0; i < g_Transition_Table[j][e][current_peak]->size; ++i)
        {
          state = g_Transition_Table[j][e][current_peak]->p[i];
          /* записываем, что состояние стало текущим в буфер
             чтобы не перекрыть старые значения состояний
             которые мы еще не прошли в цикле [j;TOTAL_STATES) */
          g_Current_states[state] = T;

          // копируем наш магазин в новое состояние
          for (size_t k = 0; k < (g_current_peak_indexes[j] + 1); ++k)
          {
            g_automatic_magazine[state][k] = g_automatic_magazine[j][k];
          }

          // копируем индекс текущей вершины в состояние state
          g_current_peak_indexes[state] = g_current_peak_indexes[j];

          // заполняем символы замены в соответствии с таблицей g_Transition_Table
          g_automatic_magazine[state][g_current_peak_indexes[state]] = g_Transition_Table[j][e][current_peak]->peak[1];
          g_automatic_magazine[state][g_current_peak_indexes[state] + 1] = g_Transition_Table[j][e][current_peak]->peak[0];

          // изменяем индекс текущей вершины в зависимости от замены
          if (g_Transition_Table[j][e][current_peak]->peak[1] == _e) 
          {
            // если у нас не переход по пустому магазину
            if (current_peak != _e)
              g_current_peak_indexes[state]--;
          }
          else if (g_Transition_Table[j][e][current_peak]->peak[0] != _e)
          {
            g_current_peak_indexes[state]++;
          }
        }
        
      } 
    }
  }

  for (i = 0; i < FINAL_STATES; ++i)
  {

    /* если хотя бы одно из допускаюших состояний
       является текущим, возвращаем REACHED_FINAL_STATE */    
    if (g_Current_states[g_Accepted_states[i]] == T)
      return REACHED_FINAL_STATE;
  }
  return NOT_REACHED_FINAL_STATE;
}
