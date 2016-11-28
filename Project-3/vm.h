#ifndef VM_H_INCLUDED
#define VM_H_INCLUDED

// Function prototypes
int vm(char *file);
void execute(int opcode, int level, int modifier, char *str, int *lcheck, int *mcheck, int *outcheck, int *out, int *inpcheck,
int *in, int *hlt, int *pc, int *bp, int *sp);
int base(int level, int b);

#endif
