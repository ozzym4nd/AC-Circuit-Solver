#ifndef AC_H
#define AC_H

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helper_functions.h"
#include "stack.h"

#define inf 1000000000

FILE* outfile;
FILE* resultfile;

enum component_type { resistor, inductor, capacitor, voltage, current };
struct component {
  int id1, id2;
  char* name;
  char* val;
  enum component_type type;
} list[20005];  // list of all components

struct source_data {
  double freq;
  double ampl;
  double phase;
  double dcoff;
};

int numcmp;   // number of components
int numnets;  // number of nets
int numsources;
int numvoltage;
int numinductor;
int n;
int i, j;
/*--------starting and ending pixels of each net---------*/
int times[20005];
int start[20005];
int end[20005];
char* arr[20005];  // arr[id] stores netlist name corresponding to the id

struct complex {
  double real;
  double img;
};

typedef struct complex complex;

// a*result=constants

void yyerror(char* s);
int accept(char* s);
int check(int i);
int check_name_error(char*);
void invert();
void gaussian(int index[]);
complex add(complex a, complex b);
complex sub(complex a, complex b);
complex mult(complex a, complex b);
complex div_(complex a, complex b);
double abs_(complex a);
void solve_circuit();
void solve_matrix();
void print_soln();
void test();
double calc_angle(complex vec);

complex make_complex(double r, double i);

complex get_inverse(complex a);
complex get_impedance(int, double);

stack** adjlist;
complex** matrix;
complex** a;
complex** ao;
complex** inverted_mat;
complex* t;
complex* values;
complex** voltage_soln;  // array of freq_arr_len X num_nets containing voltage
                         // of net at frequency of source
double* freq_arr;
complex* answer;  // array containig soln of matrix
int freq_arr_len;

struct source_data* parsed_source;
int* sources;        // maps 0,1,2... to indices of sources in list array
int* index_cur_src;  // maps index of current through voltage_sources in list
                     // array to index in matrix
int* map_source_list;
int PRINT_DC;
#endif
