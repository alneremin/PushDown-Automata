/*! \file    int_pointer.c
 *  \brief   Создание структуры int_pointer
 */
#include <stdlib.h>
#include "pda.h"

/*!
 * \brief   Создание структуры int_pointer с массивом типа int размером size
 * \param   size Значение поля size и размер массива структуры int_pointer
 * \return  Указатель на структуру при успешном создании структуры
 *          при возникающих ошибках возвращается NULL 
 */
p_int* CreateIntPointer(int size)
{
  p_int* pointer;
  if (!(pointer = (p_int*) calloc(1, sizeof (p_int)))) 
  {
    return NULL;
  }
  if (!(pointer->p = (int*) calloc(size, sizeof (int)))) 
  {
    free(pointer);
    return NULL;
  }

  pointer->size = size;
  return pointer;
}
