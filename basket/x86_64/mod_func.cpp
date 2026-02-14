#include <stdio.h>
#include "hocdec.h"
extern int nrnmpi_myid;
extern int nrn_nobanner_;

extern "C" void _Cav1_2_reg(void);
extern "C" void _Cav1_3_reg(void);
extern "C" void _Cav2_1_reg(void);
extern "C" void _Cav3_2_reg(void);
extern "C" void _cdp5StCmod_reg(void);
extern "C" void _GOLGI_Ampa_pf_aa_det_vi_reg(void);
extern "C" void _HCN1_PC_reg(void);
extern "C" void _Kca1_1_reg(void);
extern "C" void _Kca2_2_reg(void);
extern "C" void _Kca3_1_reg(void);
extern "C" void _Kir2_3_reg(void);
extern "C" void _Kv1_1_reg(void);
extern "C" void _Kv3_4_reg(void);
extern "C" void _Kv4_3_reg(void);
extern "C" void _Leak_reg(void);
extern "C" void _Nav1_1_reg(void);
extern "C" void _Nav1_6_reg(void);
extern "C" void _PC_Gaba_det_vi_alfa1_reg(void);
extern "C" void _SC_NMDA_NR2B_reg(void);

extern "C" void modl_reg() {
  if (!nrn_nobanner_) if (nrnmpi_myid < 1) {
    fprintf(stderr, "Additional mechanisms from files\n");
    fprintf(stderr, " \"mod_files//Cav1_2.mod\"");
    fprintf(stderr, " \"mod_files//Cav1_3.mod\"");
    fprintf(stderr, " \"mod_files//Cav2_1.mod\"");
    fprintf(stderr, " \"mod_files//Cav3_2.mod\"");
    fprintf(stderr, " \"mod_files//cdp5StCmod.mod\"");
    fprintf(stderr, " \"mod_files//GOLGI_Ampa_pf_aa_det_vi.mod\"");
    fprintf(stderr, " \"mod_files//HCN1_PC.mod\"");
    fprintf(stderr, " \"mod_files//Kca1_1.mod\"");
    fprintf(stderr, " \"mod_files//Kca2_2.mod\"");
    fprintf(stderr, " \"mod_files//Kca3_1.mod\"");
    fprintf(stderr, " \"mod_files//Kir2_3.mod\"");
    fprintf(stderr, " \"mod_files//Kv1_1.mod\"");
    fprintf(stderr, " \"mod_files//Kv3_4.mod\"");
    fprintf(stderr, " \"mod_files//Kv4_3.mod\"");
    fprintf(stderr, " \"mod_files//Leak.mod\"");
    fprintf(stderr, " \"mod_files//Nav1_1.mod\"");
    fprintf(stderr, " \"mod_files//Nav1_6.mod\"");
    fprintf(stderr, " \"mod_files//PC_Gaba_det_vi_alfa1.mod\"");
    fprintf(stderr, " \"mod_files//SC_NMDA_NR2B.mod\"");
    fprintf(stderr, "\n");
  }
  _Cav1_2_reg();
  _Cav1_3_reg();
  _Cav2_1_reg();
  _Cav3_2_reg();
  _cdp5StCmod_reg();
  _GOLGI_Ampa_pf_aa_det_vi_reg();
  _HCN1_PC_reg();
  _Kca1_1_reg();
  _Kca2_2_reg();
  _Kca3_1_reg();
  _Kir2_3_reg();
  _Kv1_1_reg();
  _Kv3_4_reg();
  _Kv4_3_reg();
  _Leak_reg();
  _Nav1_1_reg();
  _Nav1_6_reg();
  _PC_Gaba_det_vi_alfa1_reg();
  _SC_NMDA_NR2B_reg();
}
