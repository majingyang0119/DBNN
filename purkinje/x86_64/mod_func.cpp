#include <stdio.h>
#include "hocdec.h"
extern int nrnmpi_myid;
extern int nrn_nobanner_;

extern "C" void _Cav2_1_reg(void);
extern "C" void _Cav3_1_reg(void);
extern "C" void _Cav3_2_reg(void);
extern "C" void _Cav3_3_reg(void);
extern "C" void _cdp5_reg(void);
extern "C" void _HCN1_Angeloetal2007_reg(void);
extern "C" void _Kca11_reg(void);
extern "C" void _Kca22_reg(void);
extern "C" void _Kca31_reg(void);
extern "C" void _Kir23_reg(void);
extern "C" void _Kv11_reg(void);
extern "C" void _Kv15_reg(void);
extern "C" void _Kv33_reg(void);
extern "C" void _Kv34_reg(void);
extern "C" void _Kv43_reg(void);
extern "C" void _Leak_reg(void);
extern "C" void _Nav16_reg(void);

extern "C" void modl_reg() {
  if (!nrn_nobanner_) if (nrnmpi_myid < 1) {
    fprintf(stderr, "Additional mechanisms from files\n");
    fprintf(stderr, " \"mod_files/Cav2_1.mod\"");
    fprintf(stderr, " \"mod_files/Cav3_1.mod\"");
    fprintf(stderr, " \"mod_files/Cav3_2.mod\"");
    fprintf(stderr, " \"mod_files/Cav3_3.mod\"");
    fprintf(stderr, " \"mod_files/cdp5.mod\"");
    fprintf(stderr, " \"mod_files/HCN1_Angeloetal2007.mod\"");
    fprintf(stderr, " \"mod_files/Kca11.mod\"");
    fprintf(stderr, " \"mod_files/Kca22.mod\"");
    fprintf(stderr, " \"mod_files/Kca31.mod\"");
    fprintf(stderr, " \"mod_files/Kir23.mod\"");
    fprintf(stderr, " \"mod_files/Kv11.mod\"");
    fprintf(stderr, " \"mod_files/Kv15.mod\"");
    fprintf(stderr, " \"mod_files/Kv33.mod\"");
    fprintf(stderr, " \"mod_files/Kv34.mod\"");
    fprintf(stderr, " \"mod_files/Kv43.mod\"");
    fprintf(stderr, " \"mod_files/Leak.mod\"");
    fprintf(stderr, " \"mod_files/Nav16.mod\"");
    fprintf(stderr, "\n");
  }
  _Cav2_1_reg();
  _Cav3_1_reg();
  _Cav3_2_reg();
  _Cav3_3_reg();
  _cdp5_reg();
  _HCN1_Angeloetal2007_reg();
  _Kca11_reg();
  _Kca22_reg();
  _Kca31_reg();
  _Kir23_reg();
  _Kv11_reg();
  _Kv15_reg();
  _Kv33_reg();
  _Kv34_reg();
  _Kv43_reg();
  _Leak_reg();
  _Nav16_reg();
}
