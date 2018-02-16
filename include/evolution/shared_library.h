/** @file shared_library.h
 *  @brief Functions that can be called from the outside when this is a shared library
 */

extern "C" void init(void);
extern "C" void cleanup(void);
extern "C" void start_generators(void);
extern "C" void set_int(int thread, int variable, int value);
extern "C" int get_int(int thread, int variable);
extern "C" void add_primitive(int thread, char *p);
extern "C" void add_terminal(int thread, char *p,int constant);
extern "C" char* get_info(int thread, int variable);


