#include "assembler.h"
using namespace std;


int assembler(char * input_fn, char * output_fn, bool output_enable){
    /*First pre-process code*/
    pre_processor(strdup(input_fn), strdup(output_fn), 0);
    /*Then solve for macros*/
//    macro_solver(strdup(input_fn), strdup(output_fn), 0);
    /*And then finnally sinthesize code*/
    synthesizer ();
    return 0;
}
