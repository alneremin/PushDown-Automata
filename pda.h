
#ifndef dfa_h
#define dfa_h

#include <stdio.h> 
#include <string.h>
#include <assert.h>

#define TOTAL_STATES                   2
#define FINAL_STATES                   1
#define DIFF_TRANSITION_COUNT          13       /* кол-во различных дуг (с разными символами)*/ 
#define ALPHABET_CHARCTERS             3
#define MAGAZINE_CHARCTERS             5
#define AUTOMATIC_MAGAZINE_MAX_COUNT   100

#define UNKNOWN_SYMBOL_ERR             0
#define NOT_REACHED_FINAL_STATE        1
#define REACHED_FINAL_STATE            2

#define EXIT_SUCCESS                   0
#define EXIT_FAILURE                   1

enum PDA_STATES {q0, q2};   // The set Q
enum alphabet {a, b, c, e};
enum magazine_alphabet {_a, _b, _c, _e, _Z};

typedef enum { F, T } boolean; 

struct int_pointer 
{
    size_t size;
    int    peak[2];
    int*   p;
};

typedef struct int_pointer p_int;

extern int      g_Accepted_states[FINAL_STATES];     // The set F
extern int      g_automatic_magazine[TOTAL_STATES][AUTOMATIC_MAGAZINE_MAX_COUNT];
extern int      g_current_peak_indexes[TOTAL_STATES];
extern int      g_magazine_alphabet[MAGAZINE_CHARCTERS];  // The set Sigma
extern char     g_alphabet[ALPHABET_CHARCTERS];  // The set Sigma
extern struct   int_pointer* g_Transition_Table[TOTAL_STATES][ALPHABET_CHARCTERS + 1][MAGAZINE_CHARCTERS]; // Transition function
extern struct   int_pointer** g_pointers;
extern boolean  g_Current_states[TOTAL_STATES]; // Start state of DFA

int     PDA(const char current_symbol);
boolean SetPDA_Transitions();
void    FreePointers();
p_int*  CreateIntPointer(int size);
int     run(const char string[], int count);
#endif // dfa_h