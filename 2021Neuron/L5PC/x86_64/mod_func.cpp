#include <stdio.h>
#include "hocdec.h"
extern int nrnmpi_myid;
extern int nrn_nobanner_;

extern "C" void _CaDynamics_E2_reg(void);
extern "C" void _Ca_HVA_reg(void);
extern "C" void _Ca_LVAst_reg(void);
extern "C" void _epsp_reg(void);
extern "C" void _Ih_reg(void);
extern "C" void _Im_reg(void);
extern "C" void _K_Pst_reg(void);
extern "C" void _K_Tst_reg(void);
extern "C" void _kv_reg(void);
extern "C" void _na_reg(void);
extern "C" void _Nap_Et2_reg(void);
extern "C" void _NaTa_t_reg(void);
extern "C" void _NaTs2_t_reg(void);
extern "C" void _ProbAMPA_reg(void);
extern "C" void _ProbAMPANMDA2_reg(void);
extern "C" void _ProbAMPANMDA2_ratio_reg(void);
extern "C" void _ProbAMPANMDA_EMS_reg(void);
extern "C" void _ProbGABAAB_EMS_reg(void);
extern "C" void _SK_E2_reg(void);
extern "C" void _SKv3_1_reg(void);

extern "C" void modl_reg() {
  if (!nrn_nobanner_) if (nrnmpi_myid < 1) {
    fprintf(stderr, "Additional mechanisms from files\n");
    fprintf(stderr, " \"/home/mjy/project/bilinear_network/2021Neuron/L5PC/mods/CaDynamics_E2.mod\"");
    fprintf(stderr, " \"/home/mjy/project/bilinear_network/2021Neuron/L5PC/mods/Ca_HVA.mod\"");
    fprintf(stderr, " \"/home/mjy/project/bilinear_network/2021Neuron/L5PC/mods/Ca_LVAst.mod\"");
    fprintf(stderr, " \"/home/mjy/project/bilinear_network/2021Neuron/L5PC/mods/epsp.mod\"");
    fprintf(stderr, " \"/home/mjy/project/bilinear_network/2021Neuron/L5PC/mods/Ih.mod\"");
    fprintf(stderr, " \"/home/mjy/project/bilinear_network/2021Neuron/L5PC/mods/Im.mod\"");
    fprintf(stderr, " \"/home/mjy/project/bilinear_network/2021Neuron/L5PC/mods/K_Pst.mod\"");
    fprintf(stderr, " \"/home/mjy/project/bilinear_network/2021Neuron/L5PC/mods/K_Tst.mod\"");
    fprintf(stderr, " \"/home/mjy/project/bilinear_network/2021Neuron/L5PC/mods/kv.mod\"");
    fprintf(stderr, " \"/home/mjy/project/bilinear_network/2021Neuron/L5PC/mods/na.mod\"");
    fprintf(stderr, " \"/home/mjy/project/bilinear_network/2021Neuron/L5PC/mods/Nap_Et2.mod\"");
    fprintf(stderr, " \"/home/mjy/project/bilinear_network/2021Neuron/L5PC/mods/NaTa_t.mod\"");
    fprintf(stderr, " \"/home/mjy/project/bilinear_network/2021Neuron/L5PC/mods/NaTs2_t.mod\"");
    fprintf(stderr, " \"/home/mjy/project/bilinear_network/2021Neuron/L5PC/mods/ProbAMPA.mod\"");
    fprintf(stderr, " \"/home/mjy/project/bilinear_network/2021Neuron/L5PC/mods/ProbAMPANMDA2.mod\"");
    fprintf(stderr, " \"/home/mjy/project/bilinear_network/2021Neuron/L5PC/mods/ProbAMPANMDA2_ratio.mod\"");
    fprintf(stderr, " \"/home/mjy/project/bilinear_network/2021Neuron/L5PC/mods/ProbAMPANMDA_EMS.mod\"");
    fprintf(stderr, " \"/home/mjy/project/bilinear_network/2021Neuron/L5PC/mods/ProbGABAAB_EMS.mod\"");
    fprintf(stderr, " \"/home/mjy/project/bilinear_network/2021Neuron/L5PC/mods/SK_E2.mod\"");
    fprintf(stderr, " \"/home/mjy/project/bilinear_network/2021Neuron/L5PC/mods/SKv3_1.mod\"");
    fprintf(stderr, "\n");
  }
  _CaDynamics_E2_reg();
  _Ca_HVA_reg();
  _Ca_LVAst_reg();
  _epsp_reg();
  _Ih_reg();
  _Im_reg();
  _K_Pst_reg();
  _K_Tst_reg();
  _kv_reg();
  _na_reg();
  _Nap_Et2_reg();
  _NaTa_t_reg();
  _NaTs2_t_reg();
  _ProbAMPA_reg();
  _ProbAMPANMDA2_reg();
  _ProbAMPANMDA2_ratio_reg();
  _ProbAMPANMDA_EMS_reg();
  _ProbGABAAB_EMS_reg();
  _SK_E2_reg();
  _SKv3_1_reg();
}
