#include <stdio.h>
#include "hocdec.h"
extern int nrnmpi_myid;
extern int nrn_nobanner_;
#if defined(__cplusplus)
extern "C" {
#endif

extern void _capump_reg(void);
extern void _spike_reg(void);

void modl_reg() {
  if (!nrn_nobanner_) if (nrnmpi_myid < 1) {
    fprintf(stderr, "Additional mechanisms from files\n");
    fprintf(stderr, " \"capump.mod\"");
    fprintf(stderr, " \"spike.mod\"");
    fprintf(stderr, "\n");
  }
  _capump_reg();
  _spike_reg();
}

#if defined(__cplusplus)
}
#endif
