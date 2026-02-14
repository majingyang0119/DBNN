/* Created by Language version: 7.7.0 */
/* VECTORIZED */
#define NRN_VECTORIZED 1
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mech_api.h"
#undef PI
#define nil 0
#define _pval pval
// clang-format off
#include "md1redef.h"
#include "section_fwd.hpp"
#include "nrniv_mf.h"
#include "md2redef.h"
#include "nrnconf.h"
// clang-format on
#include "neuron/cache/mechanism_range.hpp"
static constexpr auto number_of_datum_variables = 6;
static constexpr auto number_of_floating_point_variables = 52;
namespace {
template <typename T>
using _nrn_mechanism_std_vector = std::vector<T>;
using _nrn_model_sorted_token = neuron::model_sorted_token;
using _nrn_mechanism_cache_range = neuron::cache::MechanismRange<number_of_floating_point_variables, number_of_datum_variables>;
using _nrn_mechanism_cache_instance = neuron::cache::MechanismInstance<number_of_floating_point_variables, number_of_datum_variables>;
using _nrn_non_owning_id_without_container = neuron::container::non_owning_identifier_without_container;
template <typename T>
using _nrn_mechanism_field = neuron::mechanism::field<T>;
template <typename... Args>
void _nrn_mechanism_register_data_fields(Args&&... args) {
  neuron::mechanism::register_data_fields(std::forward<Args>(args)...);
}
}
 
#if !NRNGPU
#undef exp
#define exp hoc_Exp
#if NRN_ENABLE_ARCH_INDEP_EXP_POW
#undef pow
#define pow hoc_pow
#endif
#endif
 
#define nrn_init _nrn_init__cdp5
#define _nrn_initial _nrn_initial__cdp5
#define nrn_cur _nrn_cur__cdp5
#define _nrn_current _nrn_current__cdp5
#define nrn_jacob _nrn_jacob__cdp5
#define nrn_state _nrn_state__cdp5
#define _net_receive _net_receive__cdp5 
#define factors factors__cdp5 
#define state state__cdp5 
 
#define _threadargscomma_ _ml, _iml, _ppvar, _thread, _globals, _nt,
#define _threadargsprotocomma_ Memb_list* _ml, size_t _iml, Datum* _ppvar, Datum* _thread, double* _globals, NrnThread* _nt,
#define _internalthreadargsprotocomma_ _nrn_mechanism_cache_range* _ml, size_t _iml, Datum* _ppvar, Datum* _thread, double* _globals, NrnThread* _nt,
#define _threadargs_ _ml, _iml, _ppvar, _thread, _globals, _nt
#define _threadargsproto_ Memb_list* _ml, size_t _iml, Datum* _ppvar, Datum* _thread, double* _globals, NrnThread* _nt
#define _internalthreadargsproto_ _nrn_mechanism_cache_range* _ml, size_t _iml, Datum* _ppvar, Datum* _thread, double* _globals, NrnThread* _nt
 	/*SUPPRESS 761*/
	/*SUPPRESS 762*/
	/*SUPPRESS 763*/
	/*SUPPRESS 765*/
	 extern double *hoc_getarg(int);
 
#define t _nt->_t
#define dt _nt->_dt
#define Nannuli _ml->template fpfield<0>(_iml)
#define Nannuli_columnindex 0
#define Buffnull2 _ml->template fpfield<1>(_iml)
#define Buffnull2_columnindex 1
#define rf3 _ml->template fpfield<2>(_iml)
#define rf3_columnindex 2
#define rf4 _ml->template fpfield<3>(_iml)
#define rf4_columnindex 3
#define TotalPump _ml->template fpfield<4>(_iml)
#define TotalPump_columnindex 4
#define ica_pmp _ml->template fpfield<5>(_iml)
#define ica_pmp_columnindex 5
#define vrat _ml->template fpfield<6>(_iml)
#define vrat_columnindex 6
#define ca _ml->template fpfield<7>(_iml)
#define ca_columnindex 7
#define mg _ml->template fpfield<8>(_iml)
#define mg_columnindex 8
#define Buff1 _ml->template fpfield<9>(_iml)
#define Buff1_columnindex 9
#define Buff1_ca _ml->template fpfield<10>(_iml)
#define Buff1_ca_columnindex 10
#define Buff2 _ml->template fpfield<11>(_iml)
#define Buff2_columnindex 11
#define Buff2_ca _ml->template fpfield<12>(_iml)
#define Buff2_ca_columnindex 12
#define BTC _ml->template fpfield<13>(_iml)
#define BTC_columnindex 13
#define BTC_ca _ml->template fpfield<14>(_iml)
#define BTC_ca_columnindex 14
#define DMNPE _ml->template fpfield<15>(_iml)
#define DMNPE_columnindex 15
#define DMNPE_ca _ml->template fpfield<16>(_iml)
#define DMNPE_ca_columnindex 16
#define CB _ml->template fpfield<17>(_iml)
#define CB_columnindex 17
#define CB_f_ca _ml->template fpfield<18>(_iml)
#define CB_f_ca_columnindex 18
#define CB_ca_s _ml->template fpfield<19>(_iml)
#define CB_ca_s_columnindex 19
#define CB_ca_ca _ml->template fpfield<20>(_iml)
#define CB_ca_ca_columnindex 20
#define PV _ml->template fpfield<21>(_iml)
#define PV_columnindex 21
#define PV_ca _ml->template fpfield<22>(_iml)
#define PV_ca_columnindex 22
#define PV_mg _ml->template fpfield<23>(_iml)
#define PV_mg_columnindex 23
#define pump _ml->template fpfield<24>(_iml)
#define pump_columnindex 24
#define pumpca _ml->template fpfield<25>(_iml)
#define pumpca_columnindex 25
#define ica _ml->template fpfield<26>(_iml)
#define ica_columnindex 26
#define parea _ml->template fpfield<27>(_iml)
#define parea_columnindex 27
#define parea2 _ml->template fpfield<28>(_iml)
#define parea2_columnindex 28
#define cai _ml->template fpfield<29>(_iml)
#define cai_columnindex 29
#define mgi _ml->template fpfield<30>(_iml)
#define mgi_columnindex 30
#define Dca _ml->template fpfield<31>(_iml)
#define Dca_columnindex 31
#define Dmg _ml->template fpfield<32>(_iml)
#define Dmg_columnindex 32
#define DBuff1 _ml->template fpfield<33>(_iml)
#define DBuff1_columnindex 33
#define DBuff1_ca _ml->template fpfield<34>(_iml)
#define DBuff1_ca_columnindex 34
#define DBuff2 _ml->template fpfield<35>(_iml)
#define DBuff2_columnindex 35
#define DBuff2_ca _ml->template fpfield<36>(_iml)
#define DBuff2_ca_columnindex 36
#define DBTC _ml->template fpfield<37>(_iml)
#define DBTC_columnindex 37
#define DBTC_ca _ml->template fpfield<38>(_iml)
#define DBTC_ca_columnindex 38
#define DDMNPE _ml->template fpfield<39>(_iml)
#define DDMNPE_columnindex 39
#define DDMNPE_ca _ml->template fpfield<40>(_iml)
#define DDMNPE_ca_columnindex 40
#define DCB _ml->template fpfield<41>(_iml)
#define DCB_columnindex 41
#define DCB_f_ca _ml->template fpfield<42>(_iml)
#define DCB_f_ca_columnindex 42
#define DCB_ca_s _ml->template fpfield<43>(_iml)
#define DCB_ca_s_columnindex 43
#define DCB_ca_ca _ml->template fpfield<44>(_iml)
#define DCB_ca_ca_columnindex 44
#define DPV _ml->template fpfield<45>(_iml)
#define DPV_columnindex 45
#define DPV_ca _ml->template fpfield<46>(_iml)
#define DPV_ca_columnindex 46
#define DPV_mg _ml->template fpfield<47>(_iml)
#define DPV_mg_columnindex 47
#define Dpump _ml->template fpfield<48>(_iml)
#define Dpump_columnindex 48
#define Dpumpca _ml->template fpfield<49>(_iml)
#define Dpumpca_columnindex 49
#define v _ml->template fpfield<50>(_iml)
#define v_columnindex 50
#define _g _ml->template fpfield<51>(_iml)
#define _g_columnindex 51
#define _ion_cai *(_ml->dptr_field<0>(_iml))
#define _p_ion_cai static_cast<neuron::container::data_handle<double>>(_ppvar[0])
#define _ion_ica *(_ml->dptr_field<1>(_iml))
#define _p_ion_ica static_cast<neuron::container::data_handle<double>>(_ppvar[1])
#define _ion_cao *(_ml->dptr_field<2>(_iml))
#define _p_ion_cao static_cast<neuron::container::data_handle<double>>(_ppvar[2])
#define _ion_ca_erev *_ml->dptr_field<3>(_iml)
#define _style_ca	*_ppvar[4].get<int*>()
#define diam	(*(_ml->dptr_field<5>(_iml)))
 /* Thread safe. No static _ml, _iml or _ppvar. */
 static int hoc_nrnpointerindex =  -1;
 static _nrn_mechanism_std_vector<Datum> _extcall_thread;
 static Prop* _extcall_prop;
 /* _prop_id kind of shadows _extcall_prop to allow validity checking. */
 static _nrn_non_owning_id_without_container _prop_id{};
 /* external NEURON variables */
 extern double celsius;
 /* declaration of user functions */
 static void _hoc_factors(void);
 static void _hoc_kdm(void);
 static void _hoc_kdc(void);
 static void _hoc_kds(void);
 static void _hoc_kdf(void);
 static void _hoc_ssPVmg(void);
 static void _hoc_ssPVca(void);
 static void _hoc_ssPV(void);
 static void _hoc_ssCBca(void);
 static void _hoc_ssCBslow(void);
 static void _hoc_ssCBfast(void);
 static void _hoc_ssCB(void);
 static void _hoc_ssDMNPEca(void);
 static void _hoc_ssDMNPE(void);
 static void _hoc_ssBTCca(void);
 static void _hoc_ssBTC(void);
 static void _hoc_ssBuff2ca(void);
 static void _hoc_ssBuff2(void);
 static void _hoc_ssBuff1ca(void);
 static void _hoc_ssBuff1(void);
 static int _mechtype;
extern void _nrn_cacheloop_reg(int, int);
extern void hoc_register_limits(int, HocParmLimits*);
extern void hoc_register_units(int, HocParmUnits*);
extern void nrn_promote(Prop*, int, int);
 
#define NMODL_TEXT 1
#if NMODL_TEXT
static void register_nmodl_text_and_filename(int mechtype);
#endif
 static void _hoc_setdata();
 /* connect user functions to hoc names */
 static VoidFunc hoc_intfunc[] = {
 {"setdata_cdp5", _hoc_setdata},
 {"factors_cdp5", _hoc_factors},
 {"kdm_cdp5", _hoc_kdm},
 {"kdc_cdp5", _hoc_kdc},
 {"kds_cdp5", _hoc_kds},
 {"kdf_cdp5", _hoc_kdf},
 {"ssPVmg_cdp5", _hoc_ssPVmg},
 {"ssPVca_cdp5", _hoc_ssPVca},
 {"ssPV_cdp5", _hoc_ssPV},
 {"ssCBca_cdp5", _hoc_ssCBca},
 {"ssCBslow_cdp5", _hoc_ssCBslow},
 {"ssCBfast_cdp5", _hoc_ssCBfast},
 {"ssCB_cdp5", _hoc_ssCB},
 {"ssDMNPEca_cdp5", _hoc_ssDMNPEca},
 {"ssDMNPE_cdp5", _hoc_ssDMNPE},
 {"ssBTCca_cdp5", _hoc_ssBTCca},
 {"ssBTC_cdp5", _hoc_ssBTC},
 {"ssBuff2ca_cdp5", _hoc_ssBuff2ca},
 {"ssBuff2_cdp5", _hoc_ssBuff2},
 {"ssBuff1ca_cdp5", _hoc_ssBuff1ca},
 {"ssBuff1_cdp5", _hoc_ssBuff1},
 {0, 0}
};
 
/* Direct Python call wrappers to density mechanism functions.*/
 static double _npy_factors(Prop*);
 static double _npy_kdm(Prop*);
 static double _npy_kdc(Prop*);
 static double _npy_kds(Prop*);
 static double _npy_kdf(Prop*);
 static double _npy_ssPVmg(Prop*);
 static double _npy_ssPVca(Prop*);
 static double _npy_ssPV(Prop*);
 static double _npy_ssCBca(Prop*);
 static double _npy_ssCBslow(Prop*);
 static double _npy_ssCBfast(Prop*);
 static double _npy_ssCB(Prop*);
 static double _npy_ssDMNPEca(Prop*);
 static double _npy_ssDMNPE(Prop*);
 static double _npy_ssBTCca(Prop*);
 static double _npy_ssBTC(Prop*);
 static double _npy_ssBuff2ca(Prop*);
 static double _npy_ssBuff2(Prop*);
 static double _npy_ssBuff1ca(Prop*);
 static double _npy_ssBuff1(Prop*);
 
static NPyDirectMechFunc npy_direct_func_proc[] = {
 {"factors", _npy_factors},
 {"kdm", _npy_kdm},
 {"kdc", _npy_kdc},
 {"kds", _npy_kds},
 {"kdf", _npy_kdf},
 {"ssPVmg", _npy_ssPVmg},
 {"ssPVca", _npy_ssPVca},
 {"ssPV", _npy_ssPV},
 {"ssCBca", _npy_ssCBca},
 {"ssCBslow", _npy_ssCBslow},
 {"ssCBfast", _npy_ssCBfast},
 {"ssCB", _npy_ssCB},
 {"ssDMNPEca", _npy_ssDMNPEca},
 {"ssDMNPE", _npy_ssDMNPE},
 {"ssBTCca", _npy_ssBTCca},
 {"ssBTC", _npy_ssBTC},
 {"ssBuff2ca", _npy_ssBuff2ca},
 {"ssBuff2", _npy_ssBuff2},
 {"ssBuff1ca", _npy_ssBuff1ca},
 {"ssBuff1", _npy_ssBuff1},
 {0, 0}
};
#define kdm kdm_cdp5
#define kdc kdc_cdp5
#define kds kds_cdp5
#define kdf kdf_cdp5
#define ssPVmg ssPVmg_cdp5
#define ssPVca ssPVca_cdp5
#define ssPV ssPV_cdp5
#define ssCBca ssCBca_cdp5
#define ssCBslow ssCBslow_cdp5
#define ssCBfast ssCBfast_cdp5
#define ssCB ssCB_cdp5
#define ssDMNPEca ssDMNPEca_cdp5
#define ssDMNPE ssDMNPE_cdp5
#define ssBTCca ssBTCca_cdp5
#define ssBTC ssBTC_cdp5
#define ssBuff2ca ssBuff2ca_cdp5
#define ssBuff2 ssBuff2_cdp5
#define ssBuff1ca ssBuff1ca_cdp5
#define ssBuff1 ssBuff1_cdp5
 extern double kdm( _internalthreadargsproto_ );
 extern double kdc( _internalthreadargsproto_ );
 extern double kds( _internalthreadargsproto_ );
 extern double kdf( _internalthreadargsproto_ );
 extern double ssPVmg( _internalthreadargsprotocomma_ double , double );
 extern double ssPVca( _internalthreadargsprotocomma_ double , double );
 extern double ssPV( _internalthreadargsprotocomma_ double , double );
 extern double ssCBca( _internalthreadargsprotocomma_ double , double );
 extern double ssCBslow( _internalthreadargsprotocomma_ double , double );
 extern double ssCBfast( _internalthreadargsprotocomma_ double , double );
 extern double ssCB( _internalthreadargsprotocomma_ double , double );
 extern double ssDMNPEca( _internalthreadargsproto_ );
 extern double ssDMNPE( _internalthreadargsproto_ );
 extern double ssBTCca( _internalthreadargsproto_ );
 extern double ssBTC( _internalthreadargsproto_ );
 extern double ssBuff2ca( _internalthreadargsproto_ );
 extern double ssBuff2( _internalthreadargsproto_ );
 extern double ssBuff1ca( _internalthreadargsproto_ );
 extern double ssBuff1( _internalthreadargsproto_ );
 #define _zfactors_done _thread[2].get<double*>()[0]
 #define _zdsq _thread[2].get<double*>()[1]
 #define _zdsqvol _thread[2].get<double*>()[2]
 /* declare global and static user variables */
 #define gind 0
 #define _gth 0
#define BTCnull BTCnull_cdp5
 double BTCnull = 0;
#define Buffnull1 Buffnull1_cdp5
 double Buffnull1 = 0;
#define CBnull CBnull_cdp5
 double CBnull = 0.16;
#define DMNPEnull DMNPEnull_cdp5
 double DMNPEnull = 0;
#define PVnull PVnull_cdp5
 double PVnull = 0.08;
#define b2 b2_cdp5
 double b2 = 0.08;
#define b1 b1_cdp5
 double b1 = 5.33;
#define c2 c2_cdp5
 double c2 = 0.000107;
#define c1 c1_cdp5
 double c1 = 5.63;
#define cainull cainull_cdp5
 double cainull = 4.5e-05;
#define kpmp3 kpmp3_cdp5
 double kpmp3 = 7.255e-05;
#define kpmp2 kpmp2_cdp5
 double kpmp2 = 1.75e-05;
#define kpmp1 kpmp1_cdp5
 double kpmp1 = 0.003;
#define m2 m2_cdp5
 double m2 = 0.00095;
#define m1 m1_cdp5
 double m1 = 107;
#define mginull mginull_cdp5
 double mginull = 0.59;
#define ns2 ns2_cdp5
 double ns2 = 0.0026;
#define ns1 ns1_cdp5
 double ns1 = 5.5;
#define nf2 nf2_cdp5
 double nf2 = 0.0358;
#define nf1 nf1_cdp5
 double nf1 = 43.5;
#define p2 p2_cdp5
 double p2 = 0.025;
#define p1 p1_cdp5
 double p1 = 0.8;
#define rf2 rf2_cdp5
 double rf2 = 0.0397469;
#define rf1 rf1_cdp5
 double rf1 = 0.0134329;
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 {0, 0, 0}
};
 static HocParmUnits _hoc_parm_units[] = {
 {"cainull_cdp5", "mM"},
 {"mginull_cdp5", "mM"},
 {"Buffnull1_cdp5", "mM"},
 {"rf1_cdp5", "/ms"},
 {"rf2_cdp5", "/ms"},
 {"BTCnull_cdp5", "mM"},
 {"b1_cdp5", "/ms"},
 {"b2_cdp5", "/ms"},
 {"DMNPEnull_cdp5", "mM"},
 {"c1_cdp5", "/ms"},
 {"c2_cdp5", "/ms"},
 {"CBnull_cdp5", "mM"},
 {"nf1_cdp5", "/ms"},
 {"nf2_cdp5", "/ms"},
 {"ns1_cdp5", "/ms"},
 {"ns2_cdp5", "/ms"},
 {"PVnull_cdp5", "mM"},
 {"m1_cdp5", "/ms"},
 {"m2_cdp5", "/ms"},
 {"p1_cdp5", "/ms"},
 {"p2_cdp5", "/ms"},
 {"kpmp1_cdp5", "/mM-ms"},
 {"kpmp2_cdp5", "/ms"},
 {"kpmp3_cdp5", "/ms"},
 {"Nannuli_cdp5", "1"},
 {"Buffnull2_cdp5", "mM"},
 {"rf3_cdp5", "/ms"},
 {"rf4_cdp5", "/ms"},
 {"TotalPump_cdp5", "mol/cm2"},
 {"ca_cdp5", "mM"},
 {"mg_cdp5", "mM"},
 {"Buff1_cdp5", "mM"},
 {"Buff1_ca_cdp5", "mM"},
 {"Buff2_cdp5", "mM"},
 {"Buff2_ca_cdp5", "mM"},
 {"BTC_cdp5", "mM"},
 {"BTC_ca_cdp5", "mM"},
 {"DMNPE_cdp5", "mM"},
 {"DMNPE_ca_cdp5", "mM"},
 {"CB_cdp5", "mM"},
 {"CB_f_ca_cdp5", "mM"},
 {"CB_ca_s_cdp5", "mM"},
 {"CB_ca_ca_cdp5", "mM"},
 {"PV_cdp5", "mM"},
 {"PV_ca_cdp5", "mM"},
 {"PV_mg_cdp5", "mM"},
 {"pump_cdp5", "mol/cm2"},
 {"pumpca_cdp5", "mol/cm2"},
 {"ica_pmp_cdp5", "mA/cm2"},
 {"vrat_cdp5", "1"},
 {0, 0}
};
 static double BTC_ca0 = 0;
 static double BTC0 = 0;
 static double Buff2_ca0 = 0;
 static double Buff20 = 0;
 static double Buff1_ca0 = 0;
 static double Buff10 = 0;
 static double CB_ca_ca0 = 0;
 static double CB_ca_s0 = 0;
 static double CB_f_ca0 = 0;
 static double CB0 = 0;
 static double DMNPE_ca0 = 0;
 static double DMNPE0 = 0;
 static double PV_mg0 = 0;
 static double PV_ca0 = 0;
 static double PV0 = 0;
 static double ca0 = 0;
 static double delta_t = 0.01;
 static double mg0 = 0;
 static double pumpca0 = 0;
 static double pump0 = 0;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 {"cainull_cdp5", &cainull_cdp5},
 {"mginull_cdp5", &mginull_cdp5},
 {"Buffnull1_cdp5", &Buffnull1_cdp5},
 {"rf1_cdp5", &rf1_cdp5},
 {"rf2_cdp5", &rf2_cdp5},
 {"BTCnull_cdp5", &BTCnull_cdp5},
 {"b1_cdp5", &b1_cdp5},
 {"b2_cdp5", &b2_cdp5},
 {"DMNPEnull_cdp5", &DMNPEnull_cdp5},
 {"c1_cdp5", &c1_cdp5},
 {"c2_cdp5", &c2_cdp5},
 {"CBnull_cdp5", &CBnull_cdp5},
 {"nf1_cdp5", &nf1_cdp5},
 {"nf2_cdp5", &nf2_cdp5},
 {"ns1_cdp5", &ns1_cdp5},
 {"ns2_cdp5", &ns2_cdp5},
 {"PVnull_cdp5", &PVnull_cdp5},
 {"m1_cdp5", &m1_cdp5},
 {"m2_cdp5", &m2_cdp5},
 {"p1_cdp5", &p1_cdp5},
 {"p2_cdp5", &p2_cdp5},
 {"kpmp1_cdp5", &kpmp1_cdp5},
 {"kpmp2_cdp5", &kpmp2_cdp5},
 {"kpmp3_cdp5", &kpmp3_cdp5},
 {0, 0}
};
 static DoubVec hoc_vdoub[] = {
 {0, 0, 0}
};
 static double _sav_indep;
 extern void _nrn_setdata_reg(int, void(*)(Prop*));
 static void _setdata(Prop* _prop) {
 _extcall_prop = _prop;
 _prop_id = _nrn_get_prop_id(_prop);
 }
 static void _hoc_setdata() {
 Prop *_prop, *hoc_getdata_range(int);
 _prop = hoc_getdata_range(_mechtype);
   _setdata(_prop);
 hoc_retpushx(1.);
}
 static void nrn_alloc(Prop*);
static void nrn_init(_nrn_model_sorted_token const&, NrnThread*, Memb_list*, int);
static void nrn_state(_nrn_model_sorted_token const&, NrnThread*, Memb_list*, int);
 static void nrn_cur(_nrn_model_sorted_token const&, NrnThread*, Memb_list*, int);
static void nrn_jacob(_nrn_model_sorted_token const&, NrnThread*, Memb_list*, int);
 
static int _ode_count(int);
static void _ode_map(Prop*, int, neuron::container::data_handle<double>*, neuron::container::data_handle<double>*, double*, int);
static void _ode_spec(_nrn_model_sorted_token const&, NrnThread*, Memb_list*, int);
static void _ode_matsol(_nrn_model_sorted_token const&, NrnThread*, Memb_list*, int);
 
#define _cvode_ieq _ppvar[6].literal_value<int>()
 static void _ode_synonym(_nrn_model_sorted_token const&, NrnThread&, Memb_list&, int);
 static void _ode_matsol_instance1(_internalthreadargsproto_);
 /* connect range variables in _p that hoc is supposed to know about */
 static const char *_mechanism[] = {
 "7.7.0",
"cdp5",
 "Nannuli_cdp5",
 "Buffnull2_cdp5",
 "rf3_cdp5",
 "rf4_cdp5",
 "TotalPump_cdp5",
 0,
 "ica_pmp_cdp5",
 "vrat_cdp5",
 0,
 "ca_cdp5",
 "mg_cdp5",
 "Buff1_cdp5",
 "Buff1_ca_cdp5",
 "Buff2_cdp5",
 "Buff2_ca_cdp5",
 "BTC_cdp5",
 "BTC_ca_cdp5",
 "DMNPE_cdp5",
 "DMNPE_ca_cdp5",
 "CB_cdp5",
 "CB_f_ca_cdp5",
 "CB_ca_s_cdp5",
 "CB_ca_ca_cdp5",
 "PV_cdp5",
 "PV_ca_cdp5",
 "PV_mg_cdp5",
 "pump_cdp5",
 "pumpca_cdp5",
 0,
 0};
 static Symbol* _morphology_sym;
 static Symbol* _ca_sym;
 
 /* Used by NrnProperty */
 static _nrn_mechanism_std_vector<double> _parm_default{
     10.9495, /* Nannuli */
     60.9091, /* Buffnull2 */
     0.1435, /* rf3 */
     0.0014, /* rf4 */
     1e-09, /* TotalPump */
 }; 
 
 
extern Prop* need_memb(Symbol*);
static void nrn_alloc(Prop* _prop) {
  Prop *prop_ion{};
  Datum *_ppvar{};
   _ppvar = nrn_prop_datum_alloc(_mechtype, 7, _prop);
    _nrn_mechanism_access_dparam(_prop) = _ppvar;
     _nrn_mechanism_cache_instance _ml_real{_prop};
    auto* const _ml = &_ml_real;
    size_t const _iml{};
    assert(_nrn_mechanism_get_num_vars(_prop) == 52);
 	/*initialize range parameters*/
 	Nannuli = _parm_default[0]; /* 10.9495 */
 	Buffnull2 = _parm_default[1]; /* 60.9091 */
 	rf3 = _parm_default[2]; /* 0.1435 */
 	rf4 = _parm_default[3]; /* 0.0014 */
 	TotalPump = _parm_default[4]; /* 1e-09 */
 	 assert(_nrn_mechanism_get_num_vars(_prop) == 52);
 	_nrn_mechanism_access_dparam(_prop) = _ppvar;
 	/*connect ionic variables to this model*/
 prop_ion = need_memb(_morphology_sym);
 	_ppvar[5] = _nrn_mechanism_get_param_handle(prop_ion, 0); /* diam */
 prop_ion = need_memb(_ca_sym);
 nrn_check_conc_write(_prop, prop_ion, 1);
 nrn_promote(prop_ion, 3, 0);
 	_ppvar[0] = _nrn_mechanism_get_param_handle(prop_ion, 1); /* cai */
 	_ppvar[1] = _nrn_mechanism_get_param_handle(prop_ion, 3); /* ica */
 	_ppvar[2] = _nrn_mechanism_get_param_handle(prop_ion, 2); /* cao */
 	_ppvar[3] = _nrn_mechanism_get_param_handle(prop_ion, 0); // erev ca
 	_ppvar[4] = {neuron::container::do_not_search, &(_nrn_mechanism_access_dparam(prop_ion)[0].literal_value<int>())}; /* iontype for ca */
 
}
 static void _initlists();
  /* some states have an absolute tolerance */
 static Symbol** _atollist;
 static HocStateTolerance _hoc_state_tol[] = {
 {"ca_cdp5", 0.001},
 {"mg_cdp5", 1e-06},
 {"pump_cdp5", 1e-15},
 {"pumpca_cdp5", 1e-15},
 {0, 0}
};
 static void _thread_mem_init(Datum*);
 static void _thread_cleanup(Datum*);
 extern Symbol* hoc_lookup(const char*);
extern void _nrn_thread_reg(int, int, void(*)(Datum*));
void _nrn_thread_table_reg(int, nrn_thread_table_check_t);
extern void hoc_register_tolerance(int, HocStateTolerance*, Symbol***);
extern void _cvode_abstol( Symbol**, double*, int);

 extern "C" void _cdp5_reg() {
	int _vectorized = 1;
  _initlists();
 	ion_reg("ca", -10000.);
 	_morphology_sym = hoc_lookup("morphology");
 	_ca_sym = hoc_lookup("ca_ion");
 	register_mech(_mechanism, nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init, hoc_nrnpointerindex, 4);
  _extcall_thread.resize(3);
  _thread_mem_init(_extcall_thread.data());
 _mechtype = nrn_get_mechtype(_mechanism[1]);
 hoc_register_parm_default(_mechtype, &_parm_default);
         hoc_register_npy_direct(_mechtype, npy_direct_func_proc);
     _nrn_setdata_reg(_mechtype, _setdata);
     _nrn_thread_reg(_mechtype, 1, _thread_mem_init);
     _nrn_thread_reg(_mechtype, 0, _thread_cleanup);
 #if NMODL_TEXT
  register_nmodl_text_and_filename(_mechtype);
#endif
   _nrn_mechanism_register_data_fields(_mechtype,
                                       _nrn_mechanism_field<double>{"Nannuli"} /* 0 */,
                                       _nrn_mechanism_field<double>{"Buffnull2"} /* 1 */,
                                       _nrn_mechanism_field<double>{"rf3"} /* 2 */,
                                       _nrn_mechanism_field<double>{"rf4"} /* 3 */,
                                       _nrn_mechanism_field<double>{"TotalPump"} /* 4 */,
                                       _nrn_mechanism_field<double>{"ica_pmp"} /* 5 */,
                                       _nrn_mechanism_field<double>{"vrat"} /* 6 */,
                                       _nrn_mechanism_field<double>{"ca"} /* 7 */,
                                       _nrn_mechanism_field<double>{"mg"} /* 8 */,
                                       _nrn_mechanism_field<double>{"Buff1"} /* 9 */,
                                       _nrn_mechanism_field<double>{"Buff1_ca"} /* 10 */,
                                       _nrn_mechanism_field<double>{"Buff2"} /* 11 */,
                                       _nrn_mechanism_field<double>{"Buff2_ca"} /* 12 */,
                                       _nrn_mechanism_field<double>{"BTC"} /* 13 */,
                                       _nrn_mechanism_field<double>{"BTC_ca"} /* 14 */,
                                       _nrn_mechanism_field<double>{"DMNPE"} /* 15 */,
                                       _nrn_mechanism_field<double>{"DMNPE_ca"} /* 16 */,
                                       _nrn_mechanism_field<double>{"CB"} /* 17 */,
                                       _nrn_mechanism_field<double>{"CB_f_ca"} /* 18 */,
                                       _nrn_mechanism_field<double>{"CB_ca_s"} /* 19 */,
                                       _nrn_mechanism_field<double>{"CB_ca_ca"} /* 20 */,
                                       _nrn_mechanism_field<double>{"PV"} /* 21 */,
                                       _nrn_mechanism_field<double>{"PV_ca"} /* 22 */,
                                       _nrn_mechanism_field<double>{"PV_mg"} /* 23 */,
                                       _nrn_mechanism_field<double>{"pump"} /* 24 */,
                                       _nrn_mechanism_field<double>{"pumpca"} /* 25 */,
                                       _nrn_mechanism_field<double>{"ica"} /* 26 */,
                                       _nrn_mechanism_field<double>{"parea"} /* 27 */,
                                       _nrn_mechanism_field<double>{"parea2"} /* 28 */,
                                       _nrn_mechanism_field<double>{"cai"} /* 29 */,
                                       _nrn_mechanism_field<double>{"mgi"} /* 30 */,
                                       _nrn_mechanism_field<double>{"Dca"} /* 31 */,
                                       _nrn_mechanism_field<double>{"Dmg"} /* 32 */,
                                       _nrn_mechanism_field<double>{"DBuff1"} /* 33 */,
                                       _nrn_mechanism_field<double>{"DBuff1_ca"} /* 34 */,
                                       _nrn_mechanism_field<double>{"DBuff2"} /* 35 */,
                                       _nrn_mechanism_field<double>{"DBuff2_ca"} /* 36 */,
                                       _nrn_mechanism_field<double>{"DBTC"} /* 37 */,
                                       _nrn_mechanism_field<double>{"DBTC_ca"} /* 38 */,
                                       _nrn_mechanism_field<double>{"DDMNPE"} /* 39 */,
                                       _nrn_mechanism_field<double>{"DDMNPE_ca"} /* 40 */,
                                       _nrn_mechanism_field<double>{"DCB"} /* 41 */,
                                       _nrn_mechanism_field<double>{"DCB_f_ca"} /* 42 */,
                                       _nrn_mechanism_field<double>{"DCB_ca_s"} /* 43 */,
                                       _nrn_mechanism_field<double>{"DCB_ca_ca"} /* 44 */,
                                       _nrn_mechanism_field<double>{"DPV"} /* 45 */,
                                       _nrn_mechanism_field<double>{"DPV_ca"} /* 46 */,
                                       _nrn_mechanism_field<double>{"DPV_mg"} /* 47 */,
                                       _nrn_mechanism_field<double>{"Dpump"} /* 48 */,
                                       _nrn_mechanism_field<double>{"Dpumpca"} /* 49 */,
                                       _nrn_mechanism_field<double>{"v"} /* 50 */,
                                       _nrn_mechanism_field<double>{"_g"} /* 51 */,
                                       _nrn_mechanism_field<double*>{"_ion_cai", "ca_ion"} /* 0 */,
                                       _nrn_mechanism_field<double*>{"_ion_ica", "ca_ion"} /* 1 */,
                                       _nrn_mechanism_field<double*>{"_ion_cao", "ca_ion"} /* 2 */,
                                       _nrn_mechanism_field<double*>{"_ion_ca_erev", "ca_ion"} /* 3 */,
                                       _nrn_mechanism_field<int*>{"_style_ca", "#ca_ion"} /* 4 */,
                                       _nrn_mechanism_field<double*>{"diam", "diam"} /* 5 */,
                                       _nrn_mechanism_field<int>{"_cvode_ieq", "cvodeieq"} /* 6 */);
  hoc_register_prop_size(_mechtype, 52, 7);
  hoc_register_dparam_semantics(_mechtype, 0, "ca_ion");
  hoc_register_dparam_semantics(_mechtype, 1, "ca_ion");
  hoc_register_dparam_semantics(_mechtype, 2, "ca_ion");
  hoc_register_dparam_semantics(_mechtype, 3, "ca_ion");
  hoc_register_dparam_semantics(_mechtype, 4, "#ca_ion");
  hoc_register_dparam_semantics(_mechtype, 6, "cvodeieq");
  hoc_register_dparam_semantics(_mechtype, 5, "diam");
 	nrn_writes_conc(_mechtype, 0);
 	hoc_register_cvode(_mechtype, _ode_count, _ode_map, _ode_spec, _ode_matsol);
 	hoc_register_tolerance(_mechtype, _hoc_state_tol, &_atollist);
 	hoc_register_synonym(_mechtype, _ode_synonym);
 
    hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 cdp5 /home/mjy/project/bilinear_network/purkinje/mod_files/cdp5.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
 static double FARADAY = 0x1.34c0c8b92a9b7p+3;
 static double PI = 0x1.921fb54442d18p+1;
 /*Top LOCAL _zfactors_done */
 /*Top LOCAL _zdsq , _zdsqvol */
static int _reset;
static const char *modelname = "";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static void _modl_cleanup(){ _match_recurse=1;}
static int factors(_internalthreadargsproto_);
 
#define _MATELM1(_row,_col) *(_nrn_thread_getelm(static_cast<SparseObj*>(_so), _row + 1, _col + 1))
 
#define _RHS1(_arg) _rhs[_arg+1]
  
#define _linmat1  0
 static int _spth1 = 1;
 static int _cvspth1 = 0;
 
static int _ode_spec1(_internalthreadargsproto_);
/*static int _ode_matsol1(_internalthreadargsproto_);*/
 static neuron::container::field_index _slist1[19], _dlist1[19]; static double *_temp1;
 static int state (void* _so, double* _rhs, _internalthreadargsproto_);
 
static int  factors ( _internalthreadargsproto_ ) {
   double _lr , _ldr2 ;
 _lr = 1.0 / 2.0 ;
   _ldr2 = _lr / ( Nannuli - 1.0 ) / 2.0 ;
   vrat = PI * ( _lr - _ldr2 / 2.0 ) * 2.0 * _ldr2 ;
   _lr = _lr - _ldr2 ;
    return 0; }
 
static void _hoc_factors(void) {
  double _r;
 Datum* _ppvar; Datum* _thread; NrnThread* _nt;
 
  if(!_prop_id) {
    hoc_execerror("No data for factors_cdp5. Requires prior call to setdata_cdp5 and that the specified mechanism instance still be in existence.", NULL);
  }
  Prop* _local_prop = _extcall_prop;
  _nrn_mechanism_cache_instance _ml_real{_local_prop};
auto* const _ml = &_ml_real;
size_t const _iml{};
_ppvar = _local_prop ? _nrn_mechanism_access_dparam(_local_prop) : nullptr;
_thread = _extcall_thread.data();
double* _globals = nullptr;
if (gind != 0 && _thread != nullptr) { _globals = _thread[_gth].get<double*>(); }
_nt = nrn_threads;
 _r = 1.;
 factors ( _threadargs_ );
 hoc_retpushx(_r);
}
 
static double _npy_factors(Prop* _prop) {
    double _r{0.0};
 Datum* _ppvar; Datum* _thread; NrnThread* _nt;
 _nrn_mechanism_cache_instance _ml_real{_prop};
auto* const _ml = &_ml_real;
size_t const _iml{};
_ppvar = _nrn_mechanism_access_dparam(_prop);
_thread = _extcall_thread.data();
double* _globals = nullptr;
if (gind != 0 && _thread != nullptr) { _globals = _thread[_gth].get<double*>(); }
_nt = nrn_threads;
 _r = 1.;
 factors ( _threadargs_ );
 return(_r);
}
 
static int state (void* _so, double* _rhs, _internalthreadargsproto_)
 {int _reset=0;
 {
   double b_flux, f_flux, _term; int _i;
 {int _i; double _dt1 = 1.0/dt;
for(_i=1;_i<19;_i++){
  	_RHS1(_i) = -_dt1*(_ml->data(_iml, _slist1[_i]) - _ml->data(_iml, _dlist1[_i]));
	_MATELM1(_i, _i) = _dt1;
      
}  
_RHS1(1) *= ( diam * diam * vrat) ;
_MATELM1(1, 1) *= ( diam * diam * vrat); 
_RHS1(2) *= ( diam * diam * vrat) ;
_MATELM1(2, 2) *= ( diam * diam * vrat); 
_RHS1(3) *= ( diam * diam * vrat) ;
_MATELM1(3, 3) *= ( diam * diam * vrat); 
_RHS1(4) *= ( diam * diam * vrat) ;
_MATELM1(4, 4) *= ( diam * diam * vrat); 
_RHS1(5) *= ( diam * diam * vrat) ;
_MATELM1(5, 5) *= ( diam * diam * vrat); 
_RHS1(6) *= ( diam * diam * vrat) ;
_MATELM1(6, 6) *= ( diam * diam * vrat); 
_RHS1(7) *= ( diam * diam * vrat) ;
_MATELM1(7, 7) *= ( diam * diam * vrat); 
_RHS1(8) *= ( diam * diam * vrat) ;
_MATELM1(8, 8) *= ( diam * diam * vrat); 
_RHS1(9) *= ( diam * diam * vrat) ;
_MATELM1(9, 9) *= ( diam * diam * vrat); 
_RHS1(10) *= ( diam * diam * vrat) ;
_MATELM1(10, 10) *= ( diam * diam * vrat); 
_RHS1(11) *= ( diam * diam * vrat) ;
_MATELM1(11, 11) *= ( diam * diam * vrat); 
_RHS1(12) *= ( diam * diam * vrat) ;
_MATELM1(12, 12) *= ( diam * diam * vrat); 
_RHS1(13) *= ( diam * diam * vrat) ;
_MATELM1(13, 13) *= ( diam * diam * vrat); 
_RHS1(14) *= ( diam * diam * vrat) ;
_MATELM1(14, 14) *= ( diam * diam * vrat); 
_RHS1(15) *= ( diam * diam * vrat) ;
_MATELM1(15, 15) *= ( diam * diam * vrat); 
_RHS1(16) *= ( diam * diam * vrat) ;
_MATELM1(16, 16) *= ( diam * diam * vrat); 
_RHS1(17) *= ( diam * diam * vrat) ;
_MATELM1(17, 17) *= ( diam * diam * vrat); 
_RHS1(18) *= ( ( 1e10 ) * parea) ;
_MATELM1(18, 18) *= ( ( 1e10 ) * parea);  }
 /* COMPARTMENT diam * diam * vrat {
     ca mg Buff1 Buff1_ca Buff2 Buff2_ca BTC BTC_ca DMNPE DMNPE_ca CB CB_f_ca CB_ca_s CB_ca_ca PV PV_ca PV_mg }
   */
 /* COMPARTMENT ( 1e10 ) * parea {
     pump pumpca }
   */
 /* ~ ca + pump <-> pumpca ( kpmp1 * parea * ( 1e10 ) , kpmp2 * parea * ( 1e10 ) )*/
 f_flux =  kpmp1 * parea * ( 1e10 ) * pump * ca ;
 b_flux =  kpmp2 * parea * ( 1e10 ) * pumpca ;
 _RHS1( 18) -= (f_flux - b_flux);
 _RHS1( 16) -= (f_flux - b_flux);
 
 _term =  kpmp1 * parea * ( 1e10 ) * ca ;
 _MATELM1( 18 ,18)  += _term;
 _MATELM1( 16 ,18)  += _term;
 _term =  kpmp1 * parea * ( 1e10 ) * pump ;
 _MATELM1( 18 ,16)  += _term;
 _MATELM1( 16 ,16)  += _term;
 _term =  kpmp2 * parea * ( 1e10 ) ;
 _MATELM1( 18 ,0)  -= _term;
 _MATELM1( 16 ,0)  -= _term;
 /*REACTION*/
  /* ~ pumpca <-> pump ( kpmp3 * parea * ( 1e10 ) , 0.0 )*/
 f_flux =  kpmp3 * parea * ( 1e10 ) * pumpca ;
 b_flux =  0.0 * pump ;
 _RHS1( 18) += (f_flux - b_flux);
 
 _term =  kpmp3 * parea * ( 1e10 ) ;
 _MATELM1( 18 ,0)  -= _term;
 _term =  0.0 ;
 _MATELM1( 18 ,18)  += _term;
 /*REACTION*/
   /* pump + pumpca = TotalPump * parea * ( 1e10 ) */
 _RHS1(0) =  TotalPump * parea * ( 1e10 );
 _MATELM1(0, 0) = 1 * ( ( 1e10 ) * parea);
 _RHS1(0) -= pumpca * ( ( 1e10 ) * parea) ;
 _MATELM1(0, 18) = 1 * ( ( 1e10 ) * parea);
 _RHS1(0) -= pump * ( ( 1e10 ) * parea) ;
 /*CONSERVATION*/
 ica_pmp = 2.0 * FARADAY * ( f_flux - b_flux ) / parea ;
   /* ~ ca < < ( - ica * PI * diam / ( 2.0 * FARADAY ) )*/
 f_flux = b_flux = 0.;
 _RHS1( 16) += (b_flux =   ( - ica * PI * diam / ( 2.0 * FARADAY ) ) );
 /*FLUX*/
  _zdsq = diam * diam ;
   _zdsqvol = _zdsq * vrat ;
   /* ~ ca + Buff1 <-> Buff1_ca ( rf1 * _zdsqvol , rf2 * _zdsqvol )*/
 f_flux =  rf1 * _zdsqvol * Buff1 * ca ;
 b_flux =  rf2 * _zdsqvol * Buff1_ca ;
 _RHS1( 6) -= (f_flux - b_flux);
 _RHS1( 16) -= (f_flux - b_flux);
 _RHS1( 5) += (f_flux - b_flux);
 
 _term =  rf1 * _zdsqvol * ca ;
 _MATELM1( 6 ,6)  += _term;
 _MATELM1( 16 ,6)  += _term;
 _MATELM1( 5 ,6)  -= _term;
 _term =  rf1 * _zdsqvol * Buff1 ;
 _MATELM1( 6 ,16)  += _term;
 _MATELM1( 16 ,16)  += _term;
 _MATELM1( 5 ,16)  -= _term;
 _term =  rf2 * _zdsqvol ;
 _MATELM1( 6 ,5)  -= _term;
 _MATELM1( 16 ,5)  -= _term;
 _MATELM1( 5 ,5)  += _term;
 /*REACTION*/
  /* ~ ca + Buff2 <-> Buff2_ca ( rf3 * _zdsqvol , rf4 * _zdsqvol )*/
 f_flux =  rf3 * _zdsqvol * Buff2 * ca ;
 b_flux =  rf4 * _zdsqvol * Buff2_ca ;
 _RHS1( 4) -= (f_flux - b_flux);
 _RHS1( 16) -= (f_flux - b_flux);
 _RHS1( 3) += (f_flux - b_flux);
 
 _term =  rf3 * _zdsqvol * ca ;
 _MATELM1( 4 ,4)  += _term;
 _MATELM1( 16 ,4)  += _term;
 _MATELM1( 3 ,4)  -= _term;
 _term =  rf3 * _zdsqvol * Buff2 ;
 _MATELM1( 4 ,16)  += _term;
 _MATELM1( 16 ,16)  += _term;
 _MATELM1( 3 ,16)  -= _term;
 _term =  rf4 * _zdsqvol ;
 _MATELM1( 4 ,3)  -= _term;
 _MATELM1( 16 ,3)  -= _term;
 _MATELM1( 3 ,3)  += _term;
 /*REACTION*/
  /* ~ ca + BTC <-> BTC_ca ( b1 * _zdsqvol , b2 * _zdsqvol )*/
 f_flux =  b1 * _zdsqvol * BTC * ca ;
 b_flux =  b2 * _zdsqvol * BTC_ca ;
 _RHS1( 2) -= (f_flux - b_flux);
 _RHS1( 16) -= (f_flux - b_flux);
 _RHS1( 1) += (f_flux - b_flux);
 
 _term =  b1 * _zdsqvol * ca ;
 _MATELM1( 2 ,2)  += _term;
 _MATELM1( 16 ,2)  += _term;
 _MATELM1( 1 ,2)  -= _term;
 _term =  b1 * _zdsqvol * BTC ;
 _MATELM1( 2 ,16)  += _term;
 _MATELM1( 16 ,16)  += _term;
 _MATELM1( 1 ,16)  -= _term;
 _term =  b2 * _zdsqvol ;
 _MATELM1( 2 ,1)  -= _term;
 _MATELM1( 16 ,1)  -= _term;
 _MATELM1( 1 ,1)  += _term;
 /*REACTION*/
  /* ~ ca + DMNPE <-> DMNPE_ca ( c1 * _zdsqvol , c2 * _zdsqvol )*/
 f_flux =  c1 * _zdsqvol * DMNPE * ca ;
 b_flux =  c2 * _zdsqvol * DMNPE_ca ;
 _RHS1( 12) -= (f_flux - b_flux);
 _RHS1( 16) -= (f_flux - b_flux);
 _RHS1( 11) += (f_flux - b_flux);
 
 _term =  c1 * _zdsqvol * ca ;
 _MATELM1( 12 ,12)  += _term;
 _MATELM1( 16 ,12)  += _term;
 _MATELM1( 11 ,12)  -= _term;
 _term =  c1 * _zdsqvol * DMNPE ;
 _MATELM1( 12 ,16)  += _term;
 _MATELM1( 16 ,16)  += _term;
 _MATELM1( 11 ,16)  -= _term;
 _term =  c2 * _zdsqvol ;
 _MATELM1( 12 ,11)  -= _term;
 _MATELM1( 16 ,11)  -= _term;
 _MATELM1( 11 ,11)  += _term;
 /*REACTION*/
  /* ~ ca + CB <-> CB_ca_s ( nf1 * _zdsqvol , nf2 * _zdsqvol )*/
 f_flux =  nf1 * _zdsqvol * CB * ca ;
 b_flux =  nf2 * _zdsqvol * CB_ca_s ;
 _RHS1( 10) -= (f_flux - b_flux);
 _RHS1( 16) -= (f_flux - b_flux);
 _RHS1( 8) += (f_flux - b_flux);
 
 _term =  nf1 * _zdsqvol * ca ;
 _MATELM1( 10 ,10)  += _term;
 _MATELM1( 16 ,10)  += _term;
 _MATELM1( 8 ,10)  -= _term;
 _term =  nf1 * _zdsqvol * CB ;
 _MATELM1( 10 ,16)  += _term;
 _MATELM1( 16 ,16)  += _term;
 _MATELM1( 8 ,16)  -= _term;
 _term =  nf2 * _zdsqvol ;
 _MATELM1( 10 ,8)  -= _term;
 _MATELM1( 16 ,8)  -= _term;
 _MATELM1( 8 ,8)  += _term;
 /*REACTION*/
  /* ~ ca + CB <-> CB_f_ca ( ns1 * _zdsqvol , ns2 * _zdsqvol )*/
 f_flux =  ns1 * _zdsqvol * CB * ca ;
 b_flux =  ns2 * _zdsqvol * CB_f_ca ;
 _RHS1( 10) -= (f_flux - b_flux);
 _RHS1( 16) -= (f_flux - b_flux);
 _RHS1( 9) += (f_flux - b_flux);
 
 _term =  ns1 * _zdsqvol * ca ;
 _MATELM1( 10 ,10)  += _term;
 _MATELM1( 16 ,10)  += _term;
 _MATELM1( 9 ,10)  -= _term;
 _term =  ns1 * _zdsqvol * CB ;
 _MATELM1( 10 ,16)  += _term;
 _MATELM1( 16 ,16)  += _term;
 _MATELM1( 9 ,16)  -= _term;
 _term =  ns2 * _zdsqvol ;
 _MATELM1( 10 ,9)  -= _term;
 _MATELM1( 16 ,9)  -= _term;
 _MATELM1( 9 ,9)  += _term;
 /*REACTION*/
  /* ~ ca + CB_f_ca <-> CB_ca_ca ( nf1 * _zdsqvol , nf2 * _zdsqvol )*/
 f_flux =  nf1 * _zdsqvol * CB_f_ca * ca ;
 b_flux =  nf2 * _zdsqvol * CB_ca_ca ;
 _RHS1( 9) -= (f_flux - b_flux);
 _RHS1( 16) -= (f_flux - b_flux);
 _RHS1( 7) += (f_flux - b_flux);
 
 _term =  nf1 * _zdsqvol * ca ;
 _MATELM1( 9 ,9)  += _term;
 _MATELM1( 16 ,9)  += _term;
 _MATELM1( 7 ,9)  -= _term;
 _term =  nf1 * _zdsqvol * CB_f_ca ;
 _MATELM1( 9 ,16)  += _term;
 _MATELM1( 16 ,16)  += _term;
 _MATELM1( 7 ,16)  -= _term;
 _term =  nf2 * _zdsqvol ;
 _MATELM1( 9 ,7)  -= _term;
 _MATELM1( 16 ,7)  -= _term;
 _MATELM1( 7 ,7)  += _term;
 /*REACTION*/
  /* ~ ca + CB_ca_s <-> CB_ca_ca ( ns1 * _zdsqvol , ns2 * _zdsqvol )*/
 f_flux =  ns1 * _zdsqvol * CB_ca_s * ca ;
 b_flux =  ns2 * _zdsqvol * CB_ca_ca ;
 _RHS1( 8) -= (f_flux - b_flux);
 _RHS1( 16) -= (f_flux - b_flux);
 _RHS1( 7) += (f_flux - b_flux);
 
 _term =  ns1 * _zdsqvol * ca ;
 _MATELM1( 8 ,8)  += _term;
 _MATELM1( 16 ,8)  += _term;
 _MATELM1( 7 ,8)  -= _term;
 _term =  ns1 * _zdsqvol * CB_ca_s ;
 _MATELM1( 8 ,16)  += _term;
 _MATELM1( 16 ,16)  += _term;
 _MATELM1( 7 ,16)  -= _term;
 _term =  ns2 * _zdsqvol ;
 _MATELM1( 8 ,7)  -= _term;
 _MATELM1( 16 ,7)  -= _term;
 _MATELM1( 7 ,7)  += _term;
 /*REACTION*/
  /* ~ ca + PV <-> PV_ca ( m1 * _zdsqvol , m2 * _zdsqvol )*/
 f_flux =  m1 * _zdsqvol * PV * ca ;
 b_flux =  m2 * _zdsqvol * PV_ca ;
 _RHS1( 15) -= (f_flux - b_flux);
 _RHS1( 16) -= (f_flux - b_flux);
 _RHS1( 14) += (f_flux - b_flux);
 
 _term =  m1 * _zdsqvol * ca ;
 _MATELM1( 15 ,15)  += _term;
 _MATELM1( 16 ,15)  += _term;
 _MATELM1( 14 ,15)  -= _term;
 _term =  m1 * _zdsqvol * PV ;
 _MATELM1( 15 ,16)  += _term;
 _MATELM1( 16 ,16)  += _term;
 _MATELM1( 14 ,16)  -= _term;
 _term =  m2 * _zdsqvol ;
 _MATELM1( 15 ,14)  -= _term;
 _MATELM1( 16 ,14)  -= _term;
 _MATELM1( 14 ,14)  += _term;
 /*REACTION*/
  /* ~ mg + PV <-> PV_mg ( p1 * _zdsqvol , p2 * _zdsqvol )*/
 f_flux =  p1 * _zdsqvol * PV * mg ;
 b_flux =  p2 * _zdsqvol * PV_mg ;
 _RHS1( 15) -= (f_flux - b_flux);
 _RHS1( 17) -= (f_flux - b_flux);
 _RHS1( 13) += (f_flux - b_flux);
 
 _term =  p1 * _zdsqvol * mg ;
 _MATELM1( 15 ,15)  += _term;
 _MATELM1( 17 ,15)  += _term;
 _MATELM1( 13 ,15)  -= _term;
 _term =  p1 * _zdsqvol * PV ;
 _MATELM1( 15 ,17)  += _term;
 _MATELM1( 17 ,17)  += _term;
 _MATELM1( 13 ,17)  -= _term;
 _term =  p2 * _zdsqvol ;
 _MATELM1( 15 ,13)  -= _term;
 _MATELM1( 17 ,13)  -= _term;
 _MATELM1( 13 ,13)  += _term;
 /*REACTION*/
  cai = ca ;
   mgi = mg ;
     } return _reset;
 }
 
double ssBuff1 ( _internalthreadargsproto_ ) {
   double _lssBuff1;
 _lssBuff1 = Buffnull1 / ( 1.0 + ( ( rf1 / rf2 ) * cainull ) ) ;
   
return _lssBuff1;
 }
 
static void _hoc_ssBuff1(void) {
  double _r;
 Datum* _ppvar; Datum* _thread; NrnThread* _nt;
 
  Prop* _local_prop = _prop_id ? _extcall_prop : nullptr;
  _nrn_mechanism_cache_instance _ml_real{_local_prop};
auto* const _ml = &_ml_real;
size_t const _iml{};
_ppvar = _local_prop ? _nrn_mechanism_access_dparam(_local_prop) : nullptr;
_thread = _extcall_thread.data();
double* _globals = nullptr;
if (gind != 0 && _thread != nullptr) { _globals = _thread[_gth].get<double*>(); }
_nt = nrn_threads;
 _r =  ssBuff1 ( _threadargs_ );
 hoc_retpushx(_r);
}
 
static double _npy_ssBuff1(Prop* _prop) {
    double _r{0.0};
 Datum* _ppvar; Datum* _thread; NrnThread* _nt;
 _nrn_mechanism_cache_instance _ml_real{_prop};
auto* const _ml = &_ml_real;
size_t const _iml{};
_ppvar = _nrn_mechanism_access_dparam(_prop);
_thread = _extcall_thread.data();
double* _globals = nullptr;
if (gind != 0 && _thread != nullptr) { _globals = _thread[_gth].get<double*>(); }
_nt = nrn_threads;
 _r =  ssBuff1 ( _threadargs_ );
 return(_r);
}
 
double ssBuff1ca ( _internalthreadargsproto_ ) {
   double _lssBuff1ca;
 _lssBuff1ca = Buffnull1 / ( 1.0 + ( rf2 / ( rf1 * cainull ) ) ) ;
   
return _lssBuff1ca;
 }
 
static void _hoc_ssBuff1ca(void) {
  double _r;
 Datum* _ppvar; Datum* _thread; NrnThread* _nt;
 
  Prop* _local_prop = _prop_id ? _extcall_prop : nullptr;
  _nrn_mechanism_cache_instance _ml_real{_local_prop};
auto* const _ml = &_ml_real;
size_t const _iml{};
_ppvar = _local_prop ? _nrn_mechanism_access_dparam(_local_prop) : nullptr;
_thread = _extcall_thread.data();
double* _globals = nullptr;
if (gind != 0 && _thread != nullptr) { _globals = _thread[_gth].get<double*>(); }
_nt = nrn_threads;
 _r =  ssBuff1ca ( _threadargs_ );
 hoc_retpushx(_r);
}
 
static double _npy_ssBuff1ca(Prop* _prop) {
    double _r{0.0};
 Datum* _ppvar; Datum* _thread; NrnThread* _nt;
 _nrn_mechanism_cache_instance _ml_real{_prop};
auto* const _ml = &_ml_real;
size_t const _iml{};
_ppvar = _nrn_mechanism_access_dparam(_prop);
_thread = _extcall_thread.data();
double* _globals = nullptr;
if (gind != 0 && _thread != nullptr) { _globals = _thread[_gth].get<double*>(); }
_nt = nrn_threads;
 _r =  ssBuff1ca ( _threadargs_ );
 return(_r);
}
 
double ssBuff2 ( _internalthreadargsproto_ ) {
   double _lssBuff2;
 _lssBuff2 = Buffnull2 / ( 1.0 + ( ( rf3 / rf4 ) * cainull ) ) ;
   
return _lssBuff2;
 }
 
static void _hoc_ssBuff2(void) {
  double _r;
 Datum* _ppvar; Datum* _thread; NrnThread* _nt;
 
  if(!_prop_id) {
    hoc_execerror("No data for ssBuff2_cdp5. Requires prior call to setdata_cdp5 and that the specified mechanism instance still be in existence.", NULL);
  }
  Prop* _local_prop = _extcall_prop;
  _nrn_mechanism_cache_instance _ml_real{_local_prop};
auto* const _ml = &_ml_real;
size_t const _iml{};
_ppvar = _local_prop ? _nrn_mechanism_access_dparam(_local_prop) : nullptr;
_thread = _extcall_thread.data();
double* _globals = nullptr;
if (gind != 0 && _thread != nullptr) { _globals = _thread[_gth].get<double*>(); }
_nt = nrn_threads;
 _r =  ssBuff2 ( _threadargs_ );
 hoc_retpushx(_r);
}
 
static double _npy_ssBuff2(Prop* _prop) {
    double _r{0.0};
 Datum* _ppvar; Datum* _thread; NrnThread* _nt;
 _nrn_mechanism_cache_instance _ml_real{_prop};
auto* const _ml = &_ml_real;
size_t const _iml{};
_ppvar = _nrn_mechanism_access_dparam(_prop);
_thread = _extcall_thread.data();
double* _globals = nullptr;
if (gind != 0 && _thread != nullptr) { _globals = _thread[_gth].get<double*>(); }
_nt = nrn_threads;
 _r =  ssBuff2 ( _threadargs_ );
 return(_r);
}
 
double ssBuff2ca ( _internalthreadargsproto_ ) {
   double _lssBuff2ca;
 _lssBuff2ca = Buffnull2 / ( 1.0 + ( rf4 / ( rf3 * cainull ) ) ) ;
   
return _lssBuff2ca;
 }
 
static void _hoc_ssBuff2ca(void) {
  double _r;
 Datum* _ppvar; Datum* _thread; NrnThread* _nt;
 
  if(!_prop_id) {
    hoc_execerror("No data for ssBuff2ca_cdp5. Requires prior call to setdata_cdp5 and that the specified mechanism instance still be in existence.", NULL);
  }
  Prop* _local_prop = _extcall_prop;
  _nrn_mechanism_cache_instance _ml_real{_local_prop};
auto* const _ml = &_ml_real;
size_t const _iml{};
_ppvar = _local_prop ? _nrn_mechanism_access_dparam(_local_prop) : nullptr;
_thread = _extcall_thread.data();
double* _globals = nullptr;
if (gind != 0 && _thread != nullptr) { _globals = _thread[_gth].get<double*>(); }
_nt = nrn_threads;
 _r =  ssBuff2ca ( _threadargs_ );
 hoc_retpushx(_r);
}
 
static double _npy_ssBuff2ca(Prop* _prop) {
    double _r{0.0};
 Datum* _ppvar; Datum* _thread; NrnThread* _nt;
 _nrn_mechanism_cache_instance _ml_real{_prop};
auto* const _ml = &_ml_real;
size_t const _iml{};
_ppvar = _nrn_mechanism_access_dparam(_prop);
_thread = _extcall_thread.data();
double* _globals = nullptr;
if (gind != 0 && _thread != nullptr) { _globals = _thread[_gth].get<double*>(); }
_nt = nrn_threads;
 _r =  ssBuff2ca ( _threadargs_ );
 return(_r);
}
 
double ssBTC ( _internalthreadargsproto_ ) {
   double _lssBTC;
 _lssBTC = BTCnull / ( 1.0 + ( ( b1 / b2 ) * cainull ) ) ;
   
return _lssBTC;
 }
 
static void _hoc_ssBTC(void) {
  double _r;
 Datum* _ppvar; Datum* _thread; NrnThread* _nt;
 
  Prop* _local_prop = _prop_id ? _extcall_prop : nullptr;
  _nrn_mechanism_cache_instance _ml_real{_local_prop};
auto* const _ml = &_ml_real;
size_t const _iml{};
_ppvar = _local_prop ? _nrn_mechanism_access_dparam(_local_prop) : nullptr;
_thread = _extcall_thread.data();
double* _globals = nullptr;
if (gind != 0 && _thread != nullptr) { _globals = _thread[_gth].get<double*>(); }
_nt = nrn_threads;
 _r =  ssBTC ( _threadargs_ );
 hoc_retpushx(_r);
}
 
static double _npy_ssBTC(Prop* _prop) {
    double _r{0.0};
 Datum* _ppvar; Datum* _thread; NrnThread* _nt;
 _nrn_mechanism_cache_instance _ml_real{_prop};
auto* const _ml = &_ml_real;
size_t const _iml{};
_ppvar = _nrn_mechanism_access_dparam(_prop);
_thread = _extcall_thread.data();
double* _globals = nullptr;
if (gind != 0 && _thread != nullptr) { _globals = _thread[_gth].get<double*>(); }
_nt = nrn_threads;
 _r =  ssBTC ( _threadargs_ );
 return(_r);
}
 
double ssBTCca ( _internalthreadargsproto_ ) {
   double _lssBTCca;
 _lssBTCca = BTCnull / ( 1.0 + ( b2 / ( b1 * cainull ) ) ) ;
   
return _lssBTCca;
 }
 
static void _hoc_ssBTCca(void) {
  double _r;
 Datum* _ppvar; Datum* _thread; NrnThread* _nt;
 
  Prop* _local_prop = _prop_id ? _extcall_prop : nullptr;
  _nrn_mechanism_cache_instance _ml_real{_local_prop};
auto* const _ml = &_ml_real;
size_t const _iml{};
_ppvar = _local_prop ? _nrn_mechanism_access_dparam(_local_prop) : nullptr;
_thread = _extcall_thread.data();
double* _globals = nullptr;
if (gind != 0 && _thread != nullptr) { _globals = _thread[_gth].get<double*>(); }
_nt = nrn_threads;
 _r =  ssBTCca ( _threadargs_ );
 hoc_retpushx(_r);
}
 
static double _npy_ssBTCca(Prop* _prop) {
    double _r{0.0};
 Datum* _ppvar; Datum* _thread; NrnThread* _nt;
 _nrn_mechanism_cache_instance _ml_real{_prop};
auto* const _ml = &_ml_real;
size_t const _iml{};
_ppvar = _nrn_mechanism_access_dparam(_prop);
_thread = _extcall_thread.data();
double* _globals = nullptr;
if (gind != 0 && _thread != nullptr) { _globals = _thread[_gth].get<double*>(); }
_nt = nrn_threads;
 _r =  ssBTCca ( _threadargs_ );
 return(_r);
}
 
double ssDMNPE ( _internalthreadargsproto_ ) {
   double _lssDMNPE;
 _lssDMNPE = DMNPEnull / ( 1.0 + ( ( c1 / c2 ) * cainull ) ) ;
   
return _lssDMNPE;
 }
 
static void _hoc_ssDMNPE(void) {
  double _r;
 Datum* _ppvar; Datum* _thread; NrnThread* _nt;
 
  Prop* _local_prop = _prop_id ? _extcall_prop : nullptr;
  _nrn_mechanism_cache_instance _ml_real{_local_prop};
auto* const _ml = &_ml_real;
size_t const _iml{};
_ppvar = _local_prop ? _nrn_mechanism_access_dparam(_local_prop) : nullptr;
_thread = _extcall_thread.data();
double* _globals = nullptr;
if (gind != 0 && _thread != nullptr) { _globals = _thread[_gth].get<double*>(); }
_nt = nrn_threads;
 _r =  ssDMNPE ( _threadargs_ );
 hoc_retpushx(_r);
}
 
static double _npy_ssDMNPE(Prop* _prop) {
    double _r{0.0};
 Datum* _ppvar; Datum* _thread; NrnThread* _nt;
 _nrn_mechanism_cache_instance _ml_real{_prop};
auto* const _ml = &_ml_real;
size_t const _iml{};
_ppvar = _nrn_mechanism_access_dparam(_prop);
_thread = _extcall_thread.data();
double* _globals = nullptr;
if (gind != 0 && _thread != nullptr) { _globals = _thread[_gth].get<double*>(); }
_nt = nrn_threads;
 _r =  ssDMNPE ( _threadargs_ );
 return(_r);
}
 
double ssDMNPEca ( _internalthreadargsproto_ ) {
   double _lssDMNPEca;
 _lssDMNPEca = DMNPEnull / ( 1.0 + ( c2 / ( c1 * cainull ) ) ) ;
   
return _lssDMNPEca;
 }
 
static void _hoc_ssDMNPEca(void) {
  double _r;
 Datum* _ppvar; Datum* _thread; NrnThread* _nt;
 
  Prop* _local_prop = _prop_id ? _extcall_prop : nullptr;
  _nrn_mechanism_cache_instance _ml_real{_local_prop};
auto* const _ml = &_ml_real;
size_t const _iml{};
_ppvar = _local_prop ? _nrn_mechanism_access_dparam(_local_prop) : nullptr;
_thread = _extcall_thread.data();
double* _globals = nullptr;
if (gind != 0 && _thread != nullptr) { _globals = _thread[_gth].get<double*>(); }
_nt = nrn_threads;
 _r =  ssDMNPEca ( _threadargs_ );
 hoc_retpushx(_r);
}
 
static double _npy_ssDMNPEca(Prop* _prop) {
    double _r{0.0};
 Datum* _ppvar; Datum* _thread; NrnThread* _nt;
 _nrn_mechanism_cache_instance _ml_real{_prop};
auto* const _ml = &_ml_real;
size_t const _iml{};
_ppvar = _nrn_mechanism_access_dparam(_prop);
_thread = _extcall_thread.data();
double* _globals = nullptr;
if (gind != 0 && _thread != nullptr) { _globals = _thread[_gth].get<double*>(); }
_nt = nrn_threads;
 _r =  ssDMNPEca ( _threadargs_ );
 return(_r);
}
 
double ssCB ( _internalthreadargsprotocomma_ double _lkdf , double _lkds ) {
   double _lssCB;
 _lssCB = CBnull / ( 1.0 + kdf ( _threadargs_ ) + kds ( _threadargs_ ) + ( kdf ( _threadargs_ ) * kds ( _threadargs_ ) ) ) ;
   
return _lssCB;
 }
 
static void _hoc_ssCB(void) {
  double _r;
 Datum* _ppvar; Datum* _thread; NrnThread* _nt;
 
  Prop* _local_prop = _prop_id ? _extcall_prop : nullptr;
  _nrn_mechanism_cache_instance _ml_real{_local_prop};
auto* const _ml = &_ml_real;
size_t const _iml{};
_ppvar = _local_prop ? _nrn_mechanism_access_dparam(_local_prop) : nullptr;
_thread = _extcall_thread.data();
double* _globals = nullptr;
if (gind != 0 && _thread != nullptr) { _globals = _thread[_gth].get<double*>(); }
_nt = nrn_threads;
 _r =  ssCB ( _threadargscomma_ *getarg(1) , *getarg(2) );
 hoc_retpushx(_r);
}
 
static double _npy_ssCB(Prop* _prop) {
    double _r{0.0};
 Datum* _ppvar; Datum* _thread; NrnThread* _nt;
 _nrn_mechanism_cache_instance _ml_real{_prop};
auto* const _ml = &_ml_real;
size_t const _iml{};
_ppvar = _nrn_mechanism_access_dparam(_prop);
_thread = _extcall_thread.data();
double* _globals = nullptr;
if (gind != 0 && _thread != nullptr) { _globals = _thread[_gth].get<double*>(); }
_nt = nrn_threads;
 _r =  ssCB ( _threadargscomma_ *getarg(1) , *getarg(2) );
 return(_r);
}
 
double ssCBfast ( _internalthreadargsprotocomma_ double _lkdf , double _lkds ) {
   double _lssCBfast;
 _lssCBfast = ( CBnull * kds ( _threadargs_ ) ) / ( 1.0 + kdf ( _threadargs_ ) + kds ( _threadargs_ ) + ( kdf ( _threadargs_ ) * kds ( _threadargs_ ) ) ) ;
   
return _lssCBfast;
 }
 
static void _hoc_ssCBfast(void) {
  double _r;
 Datum* _ppvar; Datum* _thread; NrnThread* _nt;
 
  Prop* _local_prop = _prop_id ? _extcall_prop : nullptr;
  _nrn_mechanism_cache_instance _ml_real{_local_prop};
auto* const _ml = &_ml_real;
size_t const _iml{};
_ppvar = _local_prop ? _nrn_mechanism_access_dparam(_local_prop) : nullptr;
_thread = _extcall_thread.data();
double* _globals = nullptr;
if (gind != 0 && _thread != nullptr) { _globals = _thread[_gth].get<double*>(); }
_nt = nrn_threads;
 _r =  ssCBfast ( _threadargscomma_ *getarg(1) , *getarg(2) );
 hoc_retpushx(_r);
}
 
static double _npy_ssCBfast(Prop* _prop) {
    double _r{0.0};
 Datum* _ppvar; Datum* _thread; NrnThread* _nt;
 _nrn_mechanism_cache_instance _ml_real{_prop};
auto* const _ml = &_ml_real;
size_t const _iml{};
_ppvar = _nrn_mechanism_access_dparam(_prop);
_thread = _extcall_thread.data();
double* _globals = nullptr;
if (gind != 0 && _thread != nullptr) { _globals = _thread[_gth].get<double*>(); }
_nt = nrn_threads;
 _r =  ssCBfast ( _threadargscomma_ *getarg(1) , *getarg(2) );
 return(_r);
}
 
double ssCBslow ( _internalthreadargsprotocomma_ double _lkdf , double _lkds ) {
   double _lssCBslow;
 _lssCBslow = ( CBnull * kdf ( _threadargs_ ) ) / ( 1.0 + kdf ( _threadargs_ ) + kds ( _threadargs_ ) + ( kdf ( _threadargs_ ) * kds ( _threadargs_ ) ) ) ;
   
return _lssCBslow;
 }
 
static void _hoc_ssCBslow(void) {
  double _r;
 Datum* _ppvar; Datum* _thread; NrnThread* _nt;
 
  Prop* _local_prop = _prop_id ? _extcall_prop : nullptr;
  _nrn_mechanism_cache_instance _ml_real{_local_prop};
auto* const _ml = &_ml_real;
size_t const _iml{};
_ppvar = _local_prop ? _nrn_mechanism_access_dparam(_local_prop) : nullptr;
_thread = _extcall_thread.data();
double* _globals = nullptr;
if (gind != 0 && _thread != nullptr) { _globals = _thread[_gth].get<double*>(); }
_nt = nrn_threads;
 _r =  ssCBslow ( _threadargscomma_ *getarg(1) , *getarg(2) );
 hoc_retpushx(_r);
}
 
static double _npy_ssCBslow(Prop* _prop) {
    double _r{0.0};
 Datum* _ppvar; Datum* _thread; NrnThread* _nt;
 _nrn_mechanism_cache_instance _ml_real{_prop};
auto* const _ml = &_ml_real;
size_t const _iml{};
_ppvar = _nrn_mechanism_access_dparam(_prop);
_thread = _extcall_thread.data();
double* _globals = nullptr;
if (gind != 0 && _thread != nullptr) { _globals = _thread[_gth].get<double*>(); }
_nt = nrn_threads;
 _r =  ssCBslow ( _threadargscomma_ *getarg(1) , *getarg(2) );
 return(_r);
}
 
double ssCBca ( _internalthreadargsprotocomma_ double _lkdf , double _lkds ) {
   double _lssCBca;
 _lssCBca = ( CBnull * kdf ( _threadargs_ ) * kds ( _threadargs_ ) ) / ( 1.0 + kdf ( _threadargs_ ) + kds ( _threadargs_ ) + ( kdf ( _threadargs_ ) * kds ( _threadargs_ ) ) ) ;
   
return _lssCBca;
 }
 
static void _hoc_ssCBca(void) {
  double _r;
 Datum* _ppvar; Datum* _thread; NrnThread* _nt;
 
  Prop* _local_prop = _prop_id ? _extcall_prop : nullptr;
  _nrn_mechanism_cache_instance _ml_real{_local_prop};
auto* const _ml = &_ml_real;
size_t const _iml{};
_ppvar = _local_prop ? _nrn_mechanism_access_dparam(_local_prop) : nullptr;
_thread = _extcall_thread.data();
double* _globals = nullptr;
if (gind != 0 && _thread != nullptr) { _globals = _thread[_gth].get<double*>(); }
_nt = nrn_threads;
 _r =  ssCBca ( _threadargscomma_ *getarg(1) , *getarg(2) );
 hoc_retpushx(_r);
}
 
static double _npy_ssCBca(Prop* _prop) {
    double _r{0.0};
 Datum* _ppvar; Datum* _thread; NrnThread* _nt;
 _nrn_mechanism_cache_instance _ml_real{_prop};
auto* const _ml = &_ml_real;
size_t const _iml{};
_ppvar = _nrn_mechanism_access_dparam(_prop);
_thread = _extcall_thread.data();
double* _globals = nullptr;
if (gind != 0 && _thread != nullptr) { _globals = _thread[_gth].get<double*>(); }
_nt = nrn_threads;
 _r =  ssCBca ( _threadargscomma_ *getarg(1) , *getarg(2) );
 return(_r);
}
 
double kdf ( _internalthreadargsproto_ ) {
   double _lkdf;
 _lkdf = ( cainull * nf1 ) / nf2 ;
   
return _lkdf;
 }
 
static void _hoc_kdf(void) {
  double _r;
 Datum* _ppvar; Datum* _thread; NrnThread* _nt;
 
  Prop* _local_prop = _prop_id ? _extcall_prop : nullptr;
  _nrn_mechanism_cache_instance _ml_real{_local_prop};
auto* const _ml = &_ml_real;
size_t const _iml{};
_ppvar = _local_prop ? _nrn_mechanism_access_dparam(_local_prop) : nullptr;
_thread = _extcall_thread.data();
double* _globals = nullptr;
if (gind != 0 && _thread != nullptr) { _globals = _thread[_gth].get<double*>(); }
_nt = nrn_threads;
 _r =  kdf ( _threadargs_ );
 hoc_retpushx(_r);
}
 
static double _npy_kdf(Prop* _prop) {
    double _r{0.0};
 Datum* _ppvar; Datum* _thread; NrnThread* _nt;
 _nrn_mechanism_cache_instance _ml_real{_prop};
auto* const _ml = &_ml_real;
size_t const _iml{};
_ppvar = _nrn_mechanism_access_dparam(_prop);
_thread = _extcall_thread.data();
double* _globals = nullptr;
if (gind != 0 && _thread != nullptr) { _globals = _thread[_gth].get<double*>(); }
_nt = nrn_threads;
 _r =  kdf ( _threadargs_ );
 return(_r);
}
 
double kds ( _internalthreadargsproto_ ) {
   double _lkds;
 _lkds = ( cainull * ns1 ) / ns2 ;
   
return _lkds;
 }
 
static void _hoc_kds(void) {
  double _r;
 Datum* _ppvar; Datum* _thread; NrnThread* _nt;
 
  Prop* _local_prop = _prop_id ? _extcall_prop : nullptr;
  _nrn_mechanism_cache_instance _ml_real{_local_prop};
auto* const _ml = &_ml_real;
size_t const _iml{};
_ppvar = _local_prop ? _nrn_mechanism_access_dparam(_local_prop) : nullptr;
_thread = _extcall_thread.data();
double* _globals = nullptr;
if (gind != 0 && _thread != nullptr) { _globals = _thread[_gth].get<double*>(); }
_nt = nrn_threads;
 _r =  kds ( _threadargs_ );
 hoc_retpushx(_r);
}
 
static double _npy_kds(Prop* _prop) {
    double _r{0.0};
 Datum* _ppvar; Datum* _thread; NrnThread* _nt;
 _nrn_mechanism_cache_instance _ml_real{_prop};
auto* const _ml = &_ml_real;
size_t const _iml{};
_ppvar = _nrn_mechanism_access_dparam(_prop);
_thread = _extcall_thread.data();
double* _globals = nullptr;
if (gind != 0 && _thread != nullptr) { _globals = _thread[_gth].get<double*>(); }
_nt = nrn_threads;
 _r =  kds ( _threadargs_ );
 return(_r);
}
 
double kdc ( _internalthreadargsproto_ ) {
   double _lkdc;
 _lkdc = ( cainull * m1 ) / m2 ;
   
return _lkdc;
 }
 
static void _hoc_kdc(void) {
  double _r;
 Datum* _ppvar; Datum* _thread; NrnThread* _nt;
 
  Prop* _local_prop = _prop_id ? _extcall_prop : nullptr;
  _nrn_mechanism_cache_instance _ml_real{_local_prop};
auto* const _ml = &_ml_real;
size_t const _iml{};
_ppvar = _local_prop ? _nrn_mechanism_access_dparam(_local_prop) : nullptr;
_thread = _extcall_thread.data();
double* _globals = nullptr;
if (gind != 0 && _thread != nullptr) { _globals = _thread[_gth].get<double*>(); }
_nt = nrn_threads;
 _r =  kdc ( _threadargs_ );
 hoc_retpushx(_r);
}
 
static double _npy_kdc(Prop* _prop) {
    double _r{0.0};
 Datum* _ppvar; Datum* _thread; NrnThread* _nt;
 _nrn_mechanism_cache_instance _ml_real{_prop};
auto* const _ml = &_ml_real;
size_t const _iml{};
_ppvar = _nrn_mechanism_access_dparam(_prop);
_thread = _extcall_thread.data();
double* _globals = nullptr;
if (gind != 0 && _thread != nullptr) { _globals = _thread[_gth].get<double*>(); }
_nt = nrn_threads;
 _r =  kdc ( _threadargs_ );
 return(_r);
}
 
double kdm ( _internalthreadargsproto_ ) {
   double _lkdm;
 _lkdm = ( mginull * p1 ) / p2 ;
   
return _lkdm;
 }
 
static void _hoc_kdm(void) {
  double _r;
 Datum* _ppvar; Datum* _thread; NrnThread* _nt;
 
  Prop* _local_prop = _prop_id ? _extcall_prop : nullptr;
  _nrn_mechanism_cache_instance _ml_real{_local_prop};
auto* const _ml = &_ml_real;
size_t const _iml{};
_ppvar = _local_prop ? _nrn_mechanism_access_dparam(_local_prop) : nullptr;
_thread = _extcall_thread.data();
double* _globals = nullptr;
if (gind != 0 && _thread != nullptr) { _globals = _thread[_gth].get<double*>(); }
_nt = nrn_threads;
 _r =  kdm ( _threadargs_ );
 hoc_retpushx(_r);
}
 
static double _npy_kdm(Prop* _prop) {
    double _r{0.0};
 Datum* _ppvar; Datum* _thread; NrnThread* _nt;
 _nrn_mechanism_cache_instance _ml_real{_prop};
auto* const _ml = &_ml_real;
size_t const _iml{};
_ppvar = _nrn_mechanism_access_dparam(_prop);
_thread = _extcall_thread.data();
double* _globals = nullptr;
if (gind != 0 && _thread != nullptr) { _globals = _thread[_gth].get<double*>(); }
_nt = nrn_threads;
 _r =  kdm ( _threadargs_ );
 return(_r);
}
 
double ssPV ( _internalthreadargsprotocomma_ double _lkdc , double _lkdm ) {
   double _lssPV;
 _lssPV = PVnull / ( 1.0 + kdc ( _threadargs_ ) + kdm ( _threadargs_ ) ) ;
   
return _lssPV;
 }
 
static void _hoc_ssPV(void) {
  double _r;
 Datum* _ppvar; Datum* _thread; NrnThread* _nt;
 
  Prop* _local_prop = _prop_id ? _extcall_prop : nullptr;
  _nrn_mechanism_cache_instance _ml_real{_local_prop};
auto* const _ml = &_ml_real;
size_t const _iml{};
_ppvar = _local_prop ? _nrn_mechanism_access_dparam(_local_prop) : nullptr;
_thread = _extcall_thread.data();
double* _globals = nullptr;
if (gind != 0 && _thread != nullptr) { _globals = _thread[_gth].get<double*>(); }
_nt = nrn_threads;
 _r =  ssPV ( _threadargscomma_ *getarg(1) , *getarg(2) );
 hoc_retpushx(_r);
}
 
static double _npy_ssPV(Prop* _prop) {
    double _r{0.0};
 Datum* _ppvar; Datum* _thread; NrnThread* _nt;
 _nrn_mechanism_cache_instance _ml_real{_prop};
auto* const _ml = &_ml_real;
size_t const _iml{};
_ppvar = _nrn_mechanism_access_dparam(_prop);
_thread = _extcall_thread.data();
double* _globals = nullptr;
if (gind != 0 && _thread != nullptr) { _globals = _thread[_gth].get<double*>(); }
_nt = nrn_threads;
 _r =  ssPV ( _threadargscomma_ *getarg(1) , *getarg(2) );
 return(_r);
}
 
double ssPVca ( _internalthreadargsprotocomma_ double _lkdc , double _lkdm ) {
   double _lssPVca;
 _lssPVca = ( PVnull * kdc ( _threadargs_ ) ) / ( 1.0 + kdc ( _threadargs_ ) + kdm ( _threadargs_ ) ) ;
   
return _lssPVca;
 }
 
static void _hoc_ssPVca(void) {
  double _r;
 Datum* _ppvar; Datum* _thread; NrnThread* _nt;
 
  Prop* _local_prop = _prop_id ? _extcall_prop : nullptr;
  _nrn_mechanism_cache_instance _ml_real{_local_prop};
auto* const _ml = &_ml_real;
size_t const _iml{};
_ppvar = _local_prop ? _nrn_mechanism_access_dparam(_local_prop) : nullptr;
_thread = _extcall_thread.data();
double* _globals = nullptr;
if (gind != 0 && _thread != nullptr) { _globals = _thread[_gth].get<double*>(); }
_nt = nrn_threads;
 _r =  ssPVca ( _threadargscomma_ *getarg(1) , *getarg(2) );
 hoc_retpushx(_r);
}
 
static double _npy_ssPVca(Prop* _prop) {
    double _r{0.0};
 Datum* _ppvar; Datum* _thread; NrnThread* _nt;
 _nrn_mechanism_cache_instance _ml_real{_prop};
auto* const _ml = &_ml_real;
size_t const _iml{};
_ppvar = _nrn_mechanism_access_dparam(_prop);
_thread = _extcall_thread.data();
double* _globals = nullptr;
if (gind != 0 && _thread != nullptr) { _globals = _thread[_gth].get<double*>(); }
_nt = nrn_threads;
 _r =  ssPVca ( _threadargscomma_ *getarg(1) , *getarg(2) );
 return(_r);
}
 
double ssPVmg ( _internalthreadargsprotocomma_ double _lkdc , double _lkdm ) {
   double _lssPVmg;
 _lssPVmg = ( PVnull * kdm ( _threadargs_ ) ) / ( 1.0 + kdc ( _threadargs_ ) + kdm ( _threadargs_ ) ) ;
   
return _lssPVmg;
 }
 
static void _hoc_ssPVmg(void) {
  double _r;
 Datum* _ppvar; Datum* _thread; NrnThread* _nt;
 
  Prop* _local_prop = _prop_id ? _extcall_prop : nullptr;
  _nrn_mechanism_cache_instance _ml_real{_local_prop};
auto* const _ml = &_ml_real;
size_t const _iml{};
_ppvar = _local_prop ? _nrn_mechanism_access_dparam(_local_prop) : nullptr;
_thread = _extcall_thread.data();
double* _globals = nullptr;
if (gind != 0 && _thread != nullptr) { _globals = _thread[_gth].get<double*>(); }
_nt = nrn_threads;
 _r =  ssPVmg ( _threadargscomma_ *getarg(1) , *getarg(2) );
 hoc_retpushx(_r);
}
 
static double _npy_ssPVmg(Prop* _prop) {
    double _r{0.0};
 Datum* _ppvar; Datum* _thread; NrnThread* _nt;
 _nrn_mechanism_cache_instance _ml_real{_prop};
auto* const _ml = &_ml_real;
size_t const _iml{};
_ppvar = _nrn_mechanism_access_dparam(_prop);
_thread = _extcall_thread.data();
double* _globals = nullptr;
if (gind != 0 && _thread != nullptr) { _globals = _thread[_gth].get<double*>(); }
_nt = nrn_threads;
 _r =  ssPVmg ( _threadargscomma_ *getarg(1) , *getarg(2) );
 return(_r);
}
 
/*CVODE ode begin*/
 static int _ode_spec1(_internalthreadargsproto_) {
  int _reset=0;
  {
 double b_flux, f_flux, _term; int _i;
 {int _i; for(_i=0;_i<19;_i++) _ml->data(_iml, _dlist1[_i]) = 0.0;}
 /* COMPARTMENT diam * diam * vrat {
   ca mg Buff1 Buff1_ca Buff2 Buff2_ca BTC BTC_ca DMNPE DMNPE_ca CB CB_f_ca CB_ca_s CB_ca_ca PV PV_ca PV_mg }
 */
 /* COMPARTMENT ( 1e10 ) * parea {
   pump pumpca }
 */
 /* ~ ca + pump <-> pumpca ( kpmp1 * parea * ( 1e10 ) , kpmp2 * parea * ( 1e10 ) )*/
 f_flux =  kpmp1 * parea * ( 1e10 ) * pump * ca ;
 b_flux =  kpmp2 * parea * ( 1e10 ) * pumpca ;
 Dpump -= (f_flux - b_flux);
 Dca -= (f_flux - b_flux);
 Dpumpca += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ pumpca <-> pump ( kpmp3 * parea * ( 1e10 ) , 0.0 )*/
 f_flux =  kpmp3 * parea * ( 1e10 ) * pumpca ;
 b_flux =  0.0 * pump ;
 Dpumpca -= (f_flux - b_flux);
 Dpump += (f_flux - b_flux);
 
 /*REACTION*/
   /* pump + pumpca = TotalPump * parea * ( 1e10 ) */
 /*CONSERVATION*/
 ica_pmp = 2.0 * FARADAY * ( f_flux - b_flux ) / parea ;
 /* ~ ca < < ( - ica * PI * diam / ( 2.0 * FARADAY ) )*/
 f_flux = b_flux = 0.;
 Dca += (b_flux =   ( - ica * PI * diam / ( 2.0 * FARADAY ) ) );
 /*FLUX*/
  _zdsq = diam * diam ;
 _zdsqvol = _zdsq * vrat ;
 /* ~ ca + Buff1 <-> Buff1_ca ( rf1 * _zdsqvol , rf2 * _zdsqvol )*/
 f_flux =  rf1 * _zdsqvol * Buff1 * ca ;
 b_flux =  rf2 * _zdsqvol * Buff1_ca ;
 DBuff1 -= (f_flux - b_flux);
 Dca -= (f_flux - b_flux);
 DBuff1_ca += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ ca + Buff2 <-> Buff2_ca ( rf3 * _zdsqvol , rf4 * _zdsqvol )*/
 f_flux =  rf3 * _zdsqvol * Buff2 * ca ;
 b_flux =  rf4 * _zdsqvol * Buff2_ca ;
 DBuff2 -= (f_flux - b_flux);
 Dca -= (f_flux - b_flux);
 DBuff2_ca += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ ca + BTC <-> BTC_ca ( b1 * _zdsqvol , b2 * _zdsqvol )*/
 f_flux =  b1 * _zdsqvol * BTC * ca ;
 b_flux =  b2 * _zdsqvol * BTC_ca ;
 DBTC -= (f_flux - b_flux);
 Dca -= (f_flux - b_flux);
 DBTC_ca += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ ca + DMNPE <-> DMNPE_ca ( c1 * _zdsqvol , c2 * _zdsqvol )*/
 f_flux =  c1 * _zdsqvol * DMNPE * ca ;
 b_flux =  c2 * _zdsqvol * DMNPE_ca ;
 DDMNPE -= (f_flux - b_flux);
 Dca -= (f_flux - b_flux);
 DDMNPE_ca += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ ca + CB <-> CB_ca_s ( nf1 * _zdsqvol , nf2 * _zdsqvol )*/
 f_flux =  nf1 * _zdsqvol * CB * ca ;
 b_flux =  nf2 * _zdsqvol * CB_ca_s ;
 DCB -= (f_flux - b_flux);
 Dca -= (f_flux - b_flux);
 DCB_ca_s += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ ca + CB <-> CB_f_ca ( ns1 * _zdsqvol , ns2 * _zdsqvol )*/
 f_flux =  ns1 * _zdsqvol * CB * ca ;
 b_flux =  ns2 * _zdsqvol * CB_f_ca ;
 DCB -= (f_flux - b_flux);
 Dca -= (f_flux - b_flux);
 DCB_f_ca += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ ca + CB_f_ca <-> CB_ca_ca ( nf1 * _zdsqvol , nf2 * _zdsqvol )*/
 f_flux =  nf1 * _zdsqvol * CB_f_ca * ca ;
 b_flux =  nf2 * _zdsqvol * CB_ca_ca ;
 DCB_f_ca -= (f_flux - b_flux);
 Dca -= (f_flux - b_flux);
 DCB_ca_ca += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ ca + CB_ca_s <-> CB_ca_ca ( ns1 * _zdsqvol , ns2 * _zdsqvol )*/
 f_flux =  ns1 * _zdsqvol * CB_ca_s * ca ;
 b_flux =  ns2 * _zdsqvol * CB_ca_ca ;
 DCB_ca_s -= (f_flux - b_flux);
 Dca -= (f_flux - b_flux);
 DCB_ca_ca += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ ca + PV <-> PV_ca ( m1 * _zdsqvol , m2 * _zdsqvol )*/
 f_flux =  m1 * _zdsqvol * PV * ca ;
 b_flux =  m2 * _zdsqvol * PV_ca ;
 DPV -= (f_flux - b_flux);
 Dca -= (f_flux - b_flux);
 DPV_ca += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ mg + PV <-> PV_mg ( p1 * _zdsqvol , p2 * _zdsqvol )*/
 f_flux =  p1 * _zdsqvol * PV * mg ;
 b_flux =  p2 * _zdsqvol * PV_mg ;
 DPV -= (f_flux - b_flux);
 Dmg -= (f_flux - b_flux);
 DPV_mg += (f_flux - b_flux);
 
 /*REACTION*/
  cai = ca ;
 mgi = mg ;
 _ml->data(_iml, _dlist1[0]) /= ( ( 1e10 ) * parea);
 _ml->data(_iml, _dlist1[1]) /= ( diam * diam * vrat);
 _ml->data(_iml, _dlist1[2]) /= ( diam * diam * vrat);
 _ml->data(_iml, _dlist1[3]) /= ( diam * diam * vrat);
 _ml->data(_iml, _dlist1[4]) /= ( diam * diam * vrat);
 _ml->data(_iml, _dlist1[5]) /= ( diam * diam * vrat);
 _ml->data(_iml, _dlist1[6]) /= ( diam * diam * vrat);
 _ml->data(_iml, _dlist1[7]) /= ( diam * diam * vrat);
 _ml->data(_iml, _dlist1[8]) /= ( diam * diam * vrat);
 _ml->data(_iml, _dlist1[9]) /= ( diam * diam * vrat);
 _ml->data(_iml, _dlist1[10]) /= ( diam * diam * vrat);
 _ml->data(_iml, _dlist1[11]) /= ( diam * diam * vrat);
 _ml->data(_iml, _dlist1[12]) /= ( diam * diam * vrat);
 _ml->data(_iml, _dlist1[13]) /= ( diam * diam * vrat);
 _ml->data(_iml, _dlist1[14]) /= ( diam * diam * vrat);
 _ml->data(_iml, _dlist1[15]) /= ( diam * diam * vrat);
 _ml->data(_iml, _dlist1[16]) /= ( diam * diam * vrat);
 _ml->data(_iml, _dlist1[17]) /= ( diam * diam * vrat);
 _ml->data(_iml, _dlist1[18]) /= ( ( 1e10 ) * parea);
   } return _reset;
 }
 
/*CVODE matsol*/
 static int _ode_matsol1(void* _so, double* _rhs, _internalthreadargsproto_) {int _reset=0;{
 double b_flux, f_flux, _term; int _i;
   b_flux = f_flux = 0.;
 {int _i; double _dt1 = 1.0/dt;
for(_i=0;_i<19;_i++){
  	_RHS1(_i) = _dt1*(_ml->data(_iml, _dlist1[_i]));
	_MATELM1(_i, _i) = _dt1;
      
}  
_RHS1(0) *= ( ( 1e10 ) * parea) ;
_MATELM1(0, 0) *= ( ( 1e10 ) * parea); 
_RHS1(1) *= ( diam * diam * vrat) ;
_MATELM1(1, 1) *= ( diam * diam * vrat); 
_RHS1(2) *= ( diam * diam * vrat) ;
_MATELM1(2, 2) *= ( diam * diam * vrat); 
_RHS1(3) *= ( diam * diam * vrat) ;
_MATELM1(3, 3) *= ( diam * diam * vrat); 
_RHS1(4) *= ( diam * diam * vrat) ;
_MATELM1(4, 4) *= ( diam * diam * vrat); 
_RHS1(5) *= ( diam * diam * vrat) ;
_MATELM1(5, 5) *= ( diam * diam * vrat); 
_RHS1(6) *= ( diam * diam * vrat) ;
_MATELM1(6, 6) *= ( diam * diam * vrat); 
_RHS1(7) *= ( diam * diam * vrat) ;
_MATELM1(7, 7) *= ( diam * diam * vrat); 
_RHS1(8) *= ( diam * diam * vrat) ;
_MATELM1(8, 8) *= ( diam * diam * vrat); 
_RHS1(9) *= ( diam * diam * vrat) ;
_MATELM1(9, 9) *= ( diam * diam * vrat); 
_RHS1(10) *= ( diam * diam * vrat) ;
_MATELM1(10, 10) *= ( diam * diam * vrat); 
_RHS1(11) *= ( diam * diam * vrat) ;
_MATELM1(11, 11) *= ( diam * diam * vrat); 
_RHS1(12) *= ( diam * diam * vrat) ;
_MATELM1(12, 12) *= ( diam * diam * vrat); 
_RHS1(13) *= ( diam * diam * vrat) ;
_MATELM1(13, 13) *= ( diam * diam * vrat); 
_RHS1(14) *= ( diam * diam * vrat) ;
_MATELM1(14, 14) *= ( diam * diam * vrat); 
_RHS1(15) *= ( diam * diam * vrat) ;
_MATELM1(15, 15) *= ( diam * diam * vrat); 
_RHS1(16) *= ( diam * diam * vrat) ;
_MATELM1(16, 16) *= ( diam * diam * vrat); 
_RHS1(17) *= ( diam * diam * vrat) ;
_MATELM1(17, 17) *= ( diam * diam * vrat); 
_RHS1(18) *= ( ( 1e10 ) * parea) ;
_MATELM1(18, 18) *= ( ( 1e10 ) * parea);  }
 /* COMPARTMENT diam * diam * vrat {
 ca mg Buff1 Buff1_ca Buff2 Buff2_ca BTC BTC_ca DMNPE DMNPE_ca CB CB_f_ca CB_ca_s CB_ca_ca PV PV_ca PV_mg }
 */
 /* COMPARTMENT ( 1e10 ) * parea {
 pump pumpca }
 */
 /* ~ ca + pump <-> pumpca ( kpmp1 * parea * ( 1e10 ) , kpmp2 * parea * ( 1e10 ) )*/
 _term =  kpmp1 * parea * ( 1e10 ) * ca ;
 _MATELM1( 18 ,18)  += _term;
 _MATELM1( 16 ,18)  += _term;
 _MATELM1( 0 ,18)  -= _term;
 _term =  kpmp1 * parea * ( 1e10 ) * pump ;
 _MATELM1( 18 ,16)  += _term;
 _MATELM1( 16 ,16)  += _term;
 _MATELM1( 0 ,16)  -= _term;
 _term =  kpmp2 * parea * ( 1e10 ) ;
 _MATELM1( 18 ,0)  -= _term;
 _MATELM1( 16 ,0)  -= _term;
 _MATELM1( 0 ,0)  += _term;
 /*REACTION*/
  /* ~ pumpca <-> pump ( kpmp3 * parea * ( 1e10 ) , 0.0 )*/
 _term =  kpmp3 * parea * ( 1e10 ) ;
 _MATELM1( 0 ,0)  += _term;
 _MATELM1( 18 ,0)  -= _term;
 _term =  0.0 ;
 _MATELM1( 0 ,18)  -= _term;
 _MATELM1( 18 ,18)  += _term;
 /* ~ ca < < ( - ica * PI * diam / ( 2.0 * FARADAY ) )*/
 /*FLUX*/
  _zdsq = diam * diam ;
 _zdsqvol = _zdsq * vrat ;
 /* ~ ca + Buff1 <-> Buff1_ca ( rf1 * _zdsqvol , rf2 * _zdsqvol )*/
 _term =  rf1 * _zdsqvol * ca ;
 _MATELM1( 6 ,6)  += _term;
 _MATELM1( 16 ,6)  += _term;
 _MATELM1( 5 ,6)  -= _term;
 _term =  rf1 * _zdsqvol * Buff1 ;
 _MATELM1( 6 ,16)  += _term;
 _MATELM1( 16 ,16)  += _term;
 _MATELM1( 5 ,16)  -= _term;
 _term =  rf2 * _zdsqvol ;
 _MATELM1( 6 ,5)  -= _term;
 _MATELM1( 16 ,5)  -= _term;
 _MATELM1( 5 ,5)  += _term;
 /*REACTION*/
  /* ~ ca + Buff2 <-> Buff2_ca ( rf3 * _zdsqvol , rf4 * _zdsqvol )*/
 _term =  rf3 * _zdsqvol * ca ;
 _MATELM1( 4 ,4)  += _term;
 _MATELM1( 16 ,4)  += _term;
 _MATELM1( 3 ,4)  -= _term;
 _term =  rf3 * _zdsqvol * Buff2 ;
 _MATELM1( 4 ,16)  += _term;
 _MATELM1( 16 ,16)  += _term;
 _MATELM1( 3 ,16)  -= _term;
 _term =  rf4 * _zdsqvol ;
 _MATELM1( 4 ,3)  -= _term;
 _MATELM1( 16 ,3)  -= _term;
 _MATELM1( 3 ,3)  += _term;
 /*REACTION*/
  /* ~ ca + BTC <-> BTC_ca ( b1 * _zdsqvol , b2 * _zdsqvol )*/
 _term =  b1 * _zdsqvol * ca ;
 _MATELM1( 2 ,2)  += _term;
 _MATELM1( 16 ,2)  += _term;
 _MATELM1( 1 ,2)  -= _term;
 _term =  b1 * _zdsqvol * BTC ;
 _MATELM1( 2 ,16)  += _term;
 _MATELM1( 16 ,16)  += _term;
 _MATELM1( 1 ,16)  -= _term;
 _term =  b2 * _zdsqvol ;
 _MATELM1( 2 ,1)  -= _term;
 _MATELM1( 16 ,1)  -= _term;
 _MATELM1( 1 ,1)  += _term;
 /*REACTION*/
  /* ~ ca + DMNPE <-> DMNPE_ca ( c1 * _zdsqvol , c2 * _zdsqvol )*/
 _term =  c1 * _zdsqvol * ca ;
 _MATELM1( 12 ,12)  += _term;
 _MATELM1( 16 ,12)  += _term;
 _MATELM1( 11 ,12)  -= _term;
 _term =  c1 * _zdsqvol * DMNPE ;
 _MATELM1( 12 ,16)  += _term;
 _MATELM1( 16 ,16)  += _term;
 _MATELM1( 11 ,16)  -= _term;
 _term =  c2 * _zdsqvol ;
 _MATELM1( 12 ,11)  -= _term;
 _MATELM1( 16 ,11)  -= _term;
 _MATELM1( 11 ,11)  += _term;
 /*REACTION*/
  /* ~ ca + CB <-> CB_ca_s ( nf1 * _zdsqvol , nf2 * _zdsqvol )*/
 _term =  nf1 * _zdsqvol * ca ;
 _MATELM1( 10 ,10)  += _term;
 _MATELM1( 16 ,10)  += _term;
 _MATELM1( 8 ,10)  -= _term;
 _term =  nf1 * _zdsqvol * CB ;
 _MATELM1( 10 ,16)  += _term;
 _MATELM1( 16 ,16)  += _term;
 _MATELM1( 8 ,16)  -= _term;
 _term =  nf2 * _zdsqvol ;
 _MATELM1( 10 ,8)  -= _term;
 _MATELM1( 16 ,8)  -= _term;
 _MATELM1( 8 ,8)  += _term;
 /*REACTION*/
  /* ~ ca + CB <-> CB_f_ca ( ns1 * _zdsqvol , ns2 * _zdsqvol )*/
 _term =  ns1 * _zdsqvol * ca ;
 _MATELM1( 10 ,10)  += _term;
 _MATELM1( 16 ,10)  += _term;
 _MATELM1( 9 ,10)  -= _term;
 _term =  ns1 * _zdsqvol * CB ;
 _MATELM1( 10 ,16)  += _term;
 _MATELM1( 16 ,16)  += _term;
 _MATELM1( 9 ,16)  -= _term;
 _term =  ns2 * _zdsqvol ;
 _MATELM1( 10 ,9)  -= _term;
 _MATELM1( 16 ,9)  -= _term;
 _MATELM1( 9 ,9)  += _term;
 /*REACTION*/
  /* ~ ca + CB_f_ca <-> CB_ca_ca ( nf1 * _zdsqvol , nf2 * _zdsqvol )*/
 _term =  nf1 * _zdsqvol * ca ;
 _MATELM1( 9 ,9)  += _term;
 _MATELM1( 16 ,9)  += _term;
 _MATELM1( 7 ,9)  -= _term;
 _term =  nf1 * _zdsqvol * CB_f_ca ;
 _MATELM1( 9 ,16)  += _term;
 _MATELM1( 16 ,16)  += _term;
 _MATELM1( 7 ,16)  -= _term;
 _term =  nf2 * _zdsqvol ;
 _MATELM1( 9 ,7)  -= _term;
 _MATELM1( 16 ,7)  -= _term;
 _MATELM1( 7 ,7)  += _term;
 /*REACTION*/
  /* ~ ca + CB_ca_s <-> CB_ca_ca ( ns1 * _zdsqvol , ns2 * _zdsqvol )*/
 _term =  ns1 * _zdsqvol * ca ;
 _MATELM1( 8 ,8)  += _term;
 _MATELM1( 16 ,8)  += _term;
 _MATELM1( 7 ,8)  -= _term;
 _term =  ns1 * _zdsqvol * CB_ca_s ;
 _MATELM1( 8 ,16)  += _term;
 _MATELM1( 16 ,16)  += _term;
 _MATELM1( 7 ,16)  -= _term;
 _term =  ns2 * _zdsqvol ;
 _MATELM1( 8 ,7)  -= _term;
 _MATELM1( 16 ,7)  -= _term;
 _MATELM1( 7 ,7)  += _term;
 /*REACTION*/
  /* ~ ca + PV <-> PV_ca ( m1 * _zdsqvol , m2 * _zdsqvol )*/
 _term =  m1 * _zdsqvol * ca ;
 _MATELM1( 15 ,15)  += _term;
 _MATELM1( 16 ,15)  += _term;
 _MATELM1( 14 ,15)  -= _term;
 _term =  m1 * _zdsqvol * PV ;
 _MATELM1( 15 ,16)  += _term;
 _MATELM1( 16 ,16)  += _term;
 _MATELM1( 14 ,16)  -= _term;
 _term =  m2 * _zdsqvol ;
 _MATELM1( 15 ,14)  -= _term;
 _MATELM1( 16 ,14)  -= _term;
 _MATELM1( 14 ,14)  += _term;
 /*REACTION*/
  /* ~ mg + PV <-> PV_mg ( p1 * _zdsqvol , p2 * _zdsqvol )*/
 _term =  p1 * _zdsqvol * mg ;
 _MATELM1( 15 ,15)  += _term;
 _MATELM1( 17 ,15)  += _term;
 _MATELM1( 13 ,15)  -= _term;
 _term =  p1 * _zdsqvol * PV ;
 _MATELM1( 15 ,17)  += _term;
 _MATELM1( 17 ,17)  += _term;
 _MATELM1( 13 ,17)  -= _term;
 _term =  p2 * _zdsqvol ;
 _MATELM1( 15 ,13)  -= _term;
 _MATELM1( 17 ,13)  -= _term;
 _MATELM1( 13 ,13)  += _term;
 /*REACTION*/
  cai = ca ;
 mgi = mg ;
   } return _reset;
 }
 
/*CVODE end*/
 
static int _ode_count(int _type){ return 19;}
 
static void _ode_spec(_nrn_model_sorted_token const& _sorted_token, NrnThread* _nt, Memb_list* _ml_arg, int _type) {
   Datum* _ppvar;
   size_t _iml;   _nrn_mechanism_cache_range* _ml;   Node* _nd{};
  double _v{};
  int _cntml;
  _nrn_mechanism_cache_range _lmr{_sorted_token, *_nt, *_ml_arg, _type};
  _ml = &_lmr;
  _cntml = _ml_arg->_nodecount;
  Datum *_thread{_ml_arg->_thread};
  double* _globals = nullptr;
  if (gind != 0 && _thread != nullptr) { _globals = _thread[_gth].get<double*>(); }
  for (_iml = 0; _iml < _cntml; ++_iml) {
    _ppvar = _ml_arg->_pdata[_iml];
    _nd = _ml_arg->_nodelist[_iml];
    v = NODEV(_nd);
  cai = _ion_cai;
  ica = _ion_ica;
  cai = _ion_cai;
     _ode_spec1 (_threadargs_);
  _ion_cai = cai;
 }}
 
static void _ode_map(Prop* _prop, int _ieq, neuron::container::data_handle<double>* _pv, neuron::container::data_handle<double>* _pvdot, double* _atol, int _type) { 
  Datum* _ppvar;
  _ppvar = _nrn_mechanism_access_dparam(_prop);
  _cvode_ieq = _ieq;
  for (int _i=0; _i < 19; ++_i) {
    _pv[_i] = _nrn_mechanism_get_param_handle(_prop, _slist1[_i]);
    _pvdot[_i] = _nrn_mechanism_get_param_handle(_prop, _dlist1[_i]);
    _cvode_abstol(_atollist, _atol, _i);
  }
 }
 static void _ode_synonym(_nrn_model_sorted_token const& _sorted_token, NrnThread& _nt, Memb_list& _ml_arg, int _type) {
 _nrn_mechanism_cache_range _lmr{_sorted_token, _nt, _ml_arg, _type};
auto* const _ml = &_lmr;
auto const _cnt = _ml_arg._nodecount;
for (int _iml = 0; _iml < _cnt; ++_iml) {
  Datum* _ppvar = _ml_arg._pdata[_iml];
 _ion_cai =  ca ;
   }
}
 
static void _ode_matsol_instance1(_internalthreadargsproto_) {
 _cvode_sparse_thread(&(_thread[_cvspth1].literal_value<void*>()), 19, _dlist1, neuron::scopmath::row_view{_ml, _iml}, _ode_matsol1, _threadargs_);
 }
 
static void _ode_matsol(_nrn_model_sorted_token const& _sorted_token, NrnThread* _nt, Memb_list* _ml_arg, int _type) {
   Datum* _ppvar;
   size_t _iml;   _nrn_mechanism_cache_range* _ml;   Node* _nd{};
  double _v{};
  int _cntml;
  _nrn_mechanism_cache_range _lmr{_sorted_token, *_nt, *_ml_arg, _type};
  _ml = &_lmr;
  _cntml = _ml_arg->_nodecount;
  Datum *_thread{_ml_arg->_thread};
  double* _globals = nullptr;
  if (gind != 0 && _thread != nullptr) { _globals = _thread[_gth].get<double*>(); }
  for (_iml = 0; _iml < _cntml; ++_iml) {
    _ppvar = _ml_arg->_pdata[_iml];
    _nd = _ml_arg->_nodelist[_iml];
    v = NODEV(_nd);
  cai = _ion_cai;
  ica = _ion_ica;
  cai = _ion_cai;
 _ode_matsol_instance1(_threadargs_);
 }}
 
static void _thread_mem_init(Datum* _thread) {
   _thread[2] = {neuron::container::do_not_search, new double[3]{}};
 }
 
static void _thread_cleanup(Datum* _thread) {
   _nrn_destroy_sparseobj_thread(static_cast<SparseObj*>(_thread[_cvspth1].get<void*>()));
   _nrn_destroy_sparseobj_thread(static_cast<SparseObj*>(_thread[_spth1].get<void*>()));
   delete[] _thread[2].get<double*>();
 }

static void initmodel(_internalthreadargsproto_) {
  int _i; double _save;{
  BTC_ca = BTC_ca0;
  BTC = BTC0;
  Buff2_ca = Buff2_ca0;
  Buff2 = Buff20;
  Buff1_ca = Buff1_ca0;
  Buff1 = Buff10;
  CB_ca_ca = CB_ca_ca0;
  CB_ca_s = CB_ca_s0;
  CB_f_ca = CB_f_ca0;
  CB = CB0;
  DMNPE_ca = DMNPE_ca0;
  DMNPE = DMNPE0;
  PV_mg = PV_mg0;
  PV_ca = PV_ca0;
  PV = PV0;
  ca = ca0;
  mg = mg0;
  pumpca = pumpca0;
  pump = pump0;
 {
   factors ( _threadargs_ ) ;
   ca = cainull ;
   mg = mginull ;
   Buff1 = ssBuff1 ( _threadargs_ ) ;
   Buff1_ca = ssBuff1ca ( _threadargs_ ) ;
   Buff2 = ssBuff2 ( _threadargs_ ) ;
   Buff2_ca = ssBuff2ca ( _threadargs_ ) ;
   BTC = ssBTC ( _threadargs_ ) ;
   BTC_ca = ssBTCca ( _threadargs_ ) ;
   DMNPE = ssDMNPE ( _threadargs_ ) ;
   DMNPE_ca = ssDMNPEca ( _threadargs_ ) ;
   CB = ssCB ( _threadargscomma_ kdf ( _threadargs_ ) , kds ( _threadargs_ ) ) ;
   CB_f_ca = ssCBfast ( _threadargscomma_ kdf ( _threadargs_ ) , kds ( _threadargs_ ) ) ;
   CB_ca_s = ssCBslow ( _threadargscomma_ kdf ( _threadargs_ ) , kds ( _threadargs_ ) ) ;
   CB_ca_ca = ssCBca ( _threadargscomma_ kdf ( _threadargs_ ) , kds ( _threadargs_ ) ) ;
   PV = ssPV ( _threadargscomma_ kdc ( _threadargs_ ) , kdm ( _threadargs_ ) ) ;
   PV_ca = ssPVca ( _threadargscomma_ kdc ( _threadargs_ ) , kdm ( _threadargs_ ) ) ;
   PV_mg = ssPVmg ( _threadargscomma_ kdc ( _threadargs_ ) , kdm ( _threadargs_ ) ) ;
   parea = PI * diam ;
   parea2 = PI * ( diam - 0.2 ) ;
   ica = 0.0 ;
   ica_pmp = 0.0 ;
   pump = TotalPump ;
   pumpca = 0.0 ;
   cai = ca ;
   }
 
}
}

static void nrn_init(_nrn_model_sorted_token const& _sorted_token, NrnThread* _nt, Memb_list* _ml_arg, int _type){
_nrn_mechanism_cache_range _lmr{_sorted_token, *_nt, *_ml_arg, _type};
auto* const _vec_v = _nt->node_voltage_storage();
auto* const _ml = &_lmr;
Datum* _ppvar; Datum* _thread;
Node *_nd; double _v; int* _ni; int _iml, _cntml;
_ni = _ml_arg->_nodeindices;
_cntml = _ml_arg->_nodecount;
_thread = _ml_arg->_thread;
double* _globals = nullptr;
if (gind != 0 && _thread != nullptr) { _globals = _thread[_gth].get<double*>(); }
for (_iml = 0; _iml < _cntml; ++_iml) {
 _ppvar = _ml_arg->_pdata[_iml];
   _v = _vec_v[_ni[_iml]];
 v = _v;
  cai = _ion_cai;
  ica = _ion_ica;
  cai = _ion_cai;
 initmodel(_threadargs_);
  _ion_cai = cai;
  nrn_wrote_conc(_ca_sym, _ion_ca_erev, _ion_cai, _ion_cao, _style_ca);
}
}

static double _nrn_current(_internalthreadargsprotocomma_ double _v) {
double _current=0.; v=_v;
{
} return _current;
}

static void nrn_cur(_nrn_model_sorted_token const& _sorted_token, NrnThread* _nt, Memb_list* _ml_arg, int _type) {
_nrn_mechanism_cache_range _lmr{_sorted_token, *_nt, *_ml_arg, _type};
auto const _vec_rhs = _nt->node_rhs_storage();
auto const _vec_sav_rhs = _nt->node_sav_rhs_storage();
auto const _vec_v = _nt->node_voltage_storage();
auto* const _ml = &_lmr;
Datum* _ppvar; Datum* _thread;
Node *_nd; int* _ni; double _rhs, _v; int _iml, _cntml;
_ni = _ml_arg->_nodeindices;
_cntml = _ml_arg->_nodecount;
_thread = _ml_arg->_thread;
double* _globals = nullptr;
if (gind != 0 && _thread != nullptr) { _globals = _thread[_gth].get<double*>(); }
for (_iml = 0; _iml < _cntml; ++_iml) {
 _ppvar = _ml_arg->_pdata[_iml];
   _v = _vec_v[_ni[_iml]];
 
}
 
}

static void nrn_jacob(_nrn_model_sorted_token const& _sorted_token, NrnThread* _nt, Memb_list* _ml_arg, int _type) {
_nrn_mechanism_cache_range _lmr{_sorted_token, *_nt, *_ml_arg, _type};
auto const _vec_d = _nt->node_d_storage();
auto const _vec_sav_d = _nt->node_sav_d_storage();
auto* const _ml = &_lmr;
Datum* _ppvar; Datum* _thread;
Node *_nd; int* _ni; int _iml, _cntml;
_ni = _ml_arg->_nodeindices;
_cntml = _ml_arg->_nodecount;
_thread = _ml_arg->_thread;
double* _globals = nullptr;
if (gind != 0 && _thread != nullptr) { _globals = _thread[_gth].get<double*>(); }
for (_iml = 0; _iml < _cntml; ++_iml) {
  _vec_d[_ni[_iml]] += _g;
 
}
 
}

static void nrn_state(_nrn_model_sorted_token const& _sorted_token, NrnThread* _nt, Memb_list* _ml_arg, int _type) {
_nrn_mechanism_cache_range _lmr{_sorted_token, *_nt, *_ml_arg, _type};
auto* const _vec_v = _nt->node_voltage_storage();
auto* const _ml = &_lmr;
Datum* _ppvar; Datum* _thread;
Node *_nd; double _v = 0.0; int* _ni;
double _dtsav = dt;
if (secondorder) { dt *= 0.5; }
_ni = _ml_arg->_nodeindices;
size_t _cntml = _ml_arg->_nodecount;
_thread = _ml_arg->_thread;
double* _globals = nullptr;
if (gind != 0 && _thread != nullptr) { _globals = _thread[_gth].get<double*>(); }
for (size_t _iml = 0; _iml < _cntml; ++_iml) {
 _ppvar = _ml_arg->_pdata[_iml];
 _nd = _ml_arg->_nodelist[_iml];
   _v = _vec_v[_ni[_iml]];
 v=_v;
{
  cai = _ion_cai;
  ica = _ion_ica;
  cai = _ion_cai;
 {  sparse_thread(&(_thread[_spth1].literal_value<void*>()), 19, _slist1, _dlist1, neuron::scopmath::row_view{_ml, _iml}, &t, dt, state, _linmat1, _threadargs_);
     if (secondorder) {
    int _i;
    for (_i = 0; _i < 19; ++_i) {
      _ml->data(_iml, _slist1[_i]) += dt*_ml->data(_iml, _dlist1[_i]);
    }}
 } {
   }
  _ion_cai = cai;
}}
 dt = _dtsav;
}

static void terminal(){}

static void _initlists(){
 int _i; static int _first = 1;
  if (!_first) return;
 _slist1[0] = {pumpca_columnindex, 0};  _dlist1[0] = {Dpumpca_columnindex, 0};
 _slist1[1] = {BTC_ca_columnindex, 0};  _dlist1[1] = {DBTC_ca_columnindex, 0};
 _slist1[2] = {BTC_columnindex, 0};  _dlist1[2] = {DBTC_columnindex, 0};
 _slist1[3] = {Buff2_ca_columnindex, 0};  _dlist1[3] = {DBuff2_ca_columnindex, 0};
 _slist1[4] = {Buff2_columnindex, 0};  _dlist1[4] = {DBuff2_columnindex, 0};
 _slist1[5] = {Buff1_ca_columnindex, 0};  _dlist1[5] = {DBuff1_ca_columnindex, 0};
 _slist1[6] = {Buff1_columnindex, 0};  _dlist1[6] = {DBuff1_columnindex, 0};
 _slist1[7] = {CB_ca_ca_columnindex, 0};  _dlist1[7] = {DCB_ca_ca_columnindex, 0};
 _slist1[8] = {CB_ca_s_columnindex, 0};  _dlist1[8] = {DCB_ca_s_columnindex, 0};
 _slist1[9] = {CB_f_ca_columnindex, 0};  _dlist1[9] = {DCB_f_ca_columnindex, 0};
 _slist1[10] = {CB_columnindex, 0};  _dlist1[10] = {DCB_columnindex, 0};
 _slist1[11] = {DMNPE_ca_columnindex, 0};  _dlist1[11] = {DDMNPE_ca_columnindex, 0};
 _slist1[12] = {DMNPE_columnindex, 0};  _dlist1[12] = {DDMNPE_columnindex, 0};
 _slist1[13] = {PV_mg_columnindex, 0};  _dlist1[13] = {DPV_mg_columnindex, 0};
 _slist1[14] = {PV_ca_columnindex, 0};  _dlist1[14] = {DPV_ca_columnindex, 0};
 _slist1[15] = {PV_columnindex, 0};  _dlist1[15] = {DPV_columnindex, 0};
 _slist1[16] = {ca_columnindex, 0};  _dlist1[16] = {Dca_columnindex, 0};
 _slist1[17] = {mg_columnindex, 0};  _dlist1[17] = {Dmg_columnindex, 0};
 _slist1[18] = {pump_columnindex, 0};  _dlist1[18] = {Dpump_columnindex, 0};
_first = 0;
}

#if NMODL_TEXT
static void register_nmodl_text_and_filename(int mech_type) {
    const char* nmodl_filename = "/home/mjy/project/bilinear_network/purkinje/mod_files/cdp5.mod";
    const char* nmodl_file_text = 
  ": Calcium ion accumulation with endogenous buffers, DCM and pump\n"
  "\n"
  "COMMENT\n"
  "\n"
  "The basic code of Example 9.8 and Example 9.9 from NEURON book was adapted as:\n"
  "\n"
  "1) Extended using parameters from Schmidt et al. 2003.\n"
  "2) Pump rate was tuned according to data from Maeda et al. 1999\n"
  "3) DCM was introduced and tuned to approximate the effect of radial diffusion\n"
  "\n"
  "Reference: Anwar H, Hong S, De Schutter E (2010) Controlling Ca2+-activated K+ channels with models of Ca2+ buffering in Purkinje cell. Cerebellum*\n"
  "\n"
  "*Article available as Open Access\n"
  "\n"
  "PubMed link: http://www.ncbi.nlm.nih.gov/pubmed/20981513\n"
  "\n"
  "Written by Haroon Anwar, Computational Neuroscience Unit, Okinawa Institute of Science and Technology, 2010.\n"
  "Contact: Haroon Anwar (anwar@oist.jp)\n"
  "\n"
  "ENDCOMMENT\n"
  "\n"
  "\n"
  "NEURON {\n"
  "  SUFFIX cdp5\n"
  "  USEION ca READ cai, ica WRITE cai\n"
  "  RANGE ica_pmp\n"
  "  RANGE Nannuli, Buffnull2, rf3, rf4, vrat\n"
  "  RANGE TotalPump\n"
  "\n"
  "}\n"
  "\n"
  "\n"
  "UNITS {\n"
  "	(mol)   = (1)\n"
  "	(molar) = (1/liter)\n"
  "	(mM)    = (millimolar)\n"
  "	(um)    = (micron)\n"
  "	(mA)    = (milliamp)\n"
  "	FARADAY = (faraday)  (10000 coulomb)\n"
  "	PI      = (pi)       (1)\n"
  "}\n"
  "\n"
  "PARAMETER {\n"
  "	Nannuli = 10.9495 (1)\n"
  "	celsius (degC)\n"
  "        \n"
  "	cainull = 45e-6 (mM)\n"
  "        mginull =.59    (mM)\n"
  "\n"
  ":	values for a buffer compensating the diffusion\n"
  "\n"
  "	Buffnull1 = 0	(mM)\n"
  "	rf1 = 0.0134329	(/ms mM)\n"
  "	rf2 = 0.0397469	(/ms)\n"
  "\n"
  "	Buffnull2 = 60.9091	(mM)\n"
  "	rf3 = 0.1435	(/ms mM)\n"
  "	rf4 = 0.0014	(/ms)\n"
  "\n"
  ":	values for benzothiazole coumarin (BTC)\n"
  "	BTCnull = 0	(mM)\n"
  "	b1 = 5.33	(/ms mM)\n"
  "	b2 = 0.08	(/ms)\n"
  "\n"
  ":	values for caged compound DMNPE-4\n"
  "	DMNPEnull = 0	(mM)\n"
  "	c1 = 5.63	(/ms mM)\n"
  "	c2 = 0.107e-3	(/ms)\n"
  "\n"
  ":       values for Calbindin (2 high and 2 low affinity binding sites)\n"
  "\n"
  "        CBnull=	.16             (mM)\n"
  "        nf1   =43.5           (/ms mM)\n"
  "        nf2   =3.58e-2        (/ms)\n"
  "        ns1   =5.5            (/ms mM)\n"
  "        ns2   =0.26e-2        (/ms)\n"
  "\n"
  ":       values for Parvalbumin\n"
  "\n"
  "        PVnull  = .08           (mM)\n"
  "        m1    = 1.07e2        (/ms mM)\n"
  "        m2    = 9.5e-4                (/ms)\n"
  "        p1    = 0.8           (/ms mM)\n"
  "        p2    = 2.5e-2                (/ms)\n"
  "\n"
  "  	kpmp1    = 3e-3       (/mM-ms)\n"
  "  	kpmp2    = 1.75e-5   (/ms)\n"
  "  	kpmp3    = 7.255e-5  (/ms)\n"
  "	TotalPump = 1e-9	(mol/cm2)	\n"
  "\n"
  "}\n"
  "\n"
  "ASSIGNED {\n"
  "	diam      (um)\n"
  "	ica       (mA/cm2)\n"
  "	ica_pmp   (mA/cm2)\n"
  "	parea     (um)     : pump area per unit length\n"
  "	parea2	  (um)\n"
  "	cai       (mM)\n"
  "	mgi	(mM)\n"
  "	vrat	(1)	\n"
  "}\n"
  "\n"
  "\n"
  "STATE {\n"
  "	: ca[0] is equivalent to cai\n"
  "	: ca[] are very small, so specify absolute tolerance\n"
  "	: let it be ~1.5 - 2 orders of magnitude smaller than baseline level\n"
  "\n"
  "	ca		(mM)    <1e-3>\n"
  "	mg		(mM)	<1e-6>\n"
  "	\n"
  "	Buff1		(mM)	\n"
  "	Buff1_ca	(mM)\n"
  "\n"
  "	Buff2		(mM)\n"
  "	Buff2_ca	(mM)\n"
  "\n"
  "	BTC		(mM)\n"
  "	BTC_ca		(mM)\n"
  "\n"
  "	DMNPE		(mM)\n"
  "	DMNPE_ca	(mM)	\n"
  "\n"
  "        CB		(mM)\n"
  "        CB_f_ca		(mM)\n"
  "        CB_ca_s		(mM)\n"
  "        CB_ca_ca	(mM)\n"
  "\n"
  "        PV		(mM)\n"
  "        PV_ca		(mM)\n"
  "        PV_mg		(mM)\n"
  "	\n"
  "	pump		(mol/cm2) <1e-15>\n"
  "	pumpca		(mol/cm2) <1e-15>\n"
  "\n"
  "}\n"
  "\n"
  "BREAKPOINT {\n"
  "	SOLVE state METHOD sparse\n"
  "}\n"
  "\n"
  "LOCAL factors_done\n"
  "\n"
  "INITIAL {\n"
  "		factors()\n"
  "\n"
  "		ca = cainull\n"
  "		mg = mginull\n"
  "		\n"
  "		Buff1 = ssBuff1()\n"
  "		Buff1_ca = ssBuff1ca()\n"
  "\n"
  "		Buff2 = ssBuff2()\n"
  "		Buff2_ca = ssBuff2ca()\n"
  "\n"
  "		BTC = ssBTC()\n"
  "		BTC_ca = ssBTCca()		\n"
  "\n"
  "		DMNPE = ssDMNPE()\n"
  "		DMNPE_ca = ssDMNPEca()\n"
  "\n"
  "		CB = ssCB( kdf(), kds())   \n"
  "	        CB_f_ca = ssCBfast( kdf(), kds())\n"
  "       	 	CB_ca_s = ssCBslow( kdf(), kds())\n"
  "        	CB_ca_ca = ssCBca( kdf(), kds())\n"
  "\n"
  "        	PV = ssPV( kdc(), kdm())\n"
  "        	PV_ca = ssPVca(kdc(), kdm())\n"
  "        	PV_mg = ssPVmg(kdc(), kdm())\n"
  "\n"
  "		\n"
  "  	parea = PI*diam\n"
  "	parea2 = PI*(diam-0.2)\n"
  "	ica = 0\n"
  "	ica_pmp = 0\n"
  ":	ica_pmp_last = 0\n"
  "	pump = TotalPump\n"
  "	pumpca = 0\n"
  "	\n"
  "	cai = ca\n"
  "}\n"
  "\n"
  "PROCEDURE factors() {\n"
  "        LOCAL r, dr2\n"
  "        r = 1/2                : starts at edge (half diam)\n"
  "        dr2 = r/(Nannuli-1)/2  : full thickness of outermost annulus,\n"
  "        vrat = PI*(r-dr2/2)*2*dr2  : interior half\n"
  "        r = r - dr2\n"
  "}\n"
  "\n"
  "\n"
  "LOCAL dsq, dsqvol  : can't define local variable in KINETIC block\n"
  "                   :   or use in COMPARTMENT statement\n"
  "\n"
  "KINETIC state {\n"
  "  COMPARTMENT diam*diam*vrat {ca mg Buff1 Buff1_ca Buff2 Buff2_ca BTC BTC_ca DMNPE DMNPE_ca CB CB_f_ca CB_ca_s CB_ca_ca PV PV_ca PV_mg}\n"
  "  COMPARTMENT (1e10)*parea {pump pumpca}\n"
  "\n"
  "\n"
  "	:pump\n"
  "	~ ca + pump <-> pumpca  (kpmp1*parea*(1e10), kpmp2*parea*(1e10))\n"
  "	~ pumpca <-> pump   (kpmp3*parea*(1e10), 0)\n"
  "  	CONSERVE pump + pumpca = TotalPump * parea * (1e10)\n"
  "	\n"
  "	ica_pmp = 2*FARADAY*(f_flux - b_flux)/parea	\n"
  "	: all currents except pump\n"
  "	: ica is Ca efflux\n"
  "	~ ca << (-ica*PI*diam/(2*FARADAY))\n"
  "\n"
  "	:RADIAL DIFFUSION OF ca, mg and mobile buffers\n"
  "\n"
  "	dsq = diam*diam\n"
  "		dsqvol = dsq*vrat\n"
  "		~ ca + Buff1 <-> Buff1_ca (rf1*dsqvol, rf2*dsqvol)\n"
  "		~ ca + Buff2 <-> Buff2_ca (rf3*dsqvol, rf4*dsqvol)\n"
  "		~ ca + BTC <-> BTC_ca (b1*dsqvol, b2*dsqvol)\n"
  "		~ ca + DMNPE <-> DMNPE_ca (c1*dsqvol, c2*dsqvol)\n"
  "		:Calbindin	\n"
  "		~ ca + CB <-> CB_ca_s (nf1*dsqvol, nf2*dsqvol)\n"
  "	       	~ ca + CB <-> CB_f_ca (ns1*dsqvol, ns2*dsqvol)\n"
  "        	~ ca + CB_f_ca <-> CB_ca_ca (nf1*dsqvol, nf2*dsqvol)\n"
  "        	~ ca + CB_ca_s <-> CB_ca_ca (ns1*dsqvol, ns2*dsqvol)\n"
  "\n"
  "		:Paravalbumin\n"
  "        	~ ca + PV <-> PV_ca (m1*dsqvol, m2*dsqvol)\n"
  "        	~ mg + PV <-> PV_mg (p1*dsqvol, p2*dsqvol)\n"
  "\n"
  "\n"
  "  	cai = ca\n"
  "	mgi = mg\n"
  "}\n"
  "\n"
  "FUNCTION ssBuff1() (mM) {\n"
  "	ssBuff1 = Buffnull1/(1+((rf1/rf2)*cainull))\n"
  "}\n"
  "FUNCTION ssBuff1ca() (mM) {\n"
  "	ssBuff1ca = Buffnull1/(1+(rf2/(rf1*cainull)))\n"
  "}\n"
  "FUNCTION ssBuff2() (mM) {\n"
  "        ssBuff2 = Buffnull2/(1+((rf3/rf4)*cainull))\n"
  "}\n"
  "FUNCTION ssBuff2ca() (mM) {\n"
  "        ssBuff2ca = Buffnull2/(1+(rf4/(rf3*cainull)))\n"
  "}\n"
  "\n"
  "FUNCTION ssBTC() (mM) {\n"
  "	ssBTC = BTCnull/(1+((b1/b2)*cainull))\n"
  "}\n"
  "\n"
  "FUNCTION ssBTCca() (mM) {\n"
  "	ssBTCca = BTCnull/(1+(b2/(b1*cainull)))\n"
  "}\n"
  "\n"
  "FUNCTION ssDMNPE() (mM) {\n"
  "	ssDMNPE = DMNPEnull/(1+((c1/c2)*cainull))\n"
  "}\n"
  "\n"
  "FUNCTION ssDMNPEca() (mM) {\n"
  "	ssDMNPEca = DMNPEnull/(1+(c2/(c1*cainull)))\n"
  "}\n"
  "\n"
  "FUNCTION ssCB( kdf(), kds()) (mM) {\n"
  "	ssCB = CBnull/(1+kdf()+kds()+(kdf()*kds()))\n"
  "}\n"
  "FUNCTION ssCBfast( kdf(), kds()) (mM) {\n"
  "	ssCBfast = (CBnull*kds())/(1+kdf()+kds()+(kdf()*kds()))\n"
  "}\n"
  "FUNCTION ssCBslow( kdf(), kds()) (mM) {\n"
  "	ssCBslow = (CBnull*kdf())/(1+kdf()+kds()+(kdf()*kds()))\n"
  "}\n"
  "FUNCTION ssCBca(kdf(), kds()) (mM) {\n"
  "	ssCBca = (CBnull*kdf()*kds())/(1+kdf()+kds()+(kdf()*kds()))\n"
  "}\n"
  "FUNCTION kdf() (1) {\n"
  "	kdf = (cainull*nf1)/nf2\n"
  "}\n"
  "FUNCTION kds() (1) {\n"
  "	kds = (cainull*ns1)/ns2\n"
  "}\n"
  "FUNCTION kdc() (1) {\n"
  "	kdc = (cainull*m1)/m2\n"
  "}\n"
  "FUNCTION kdm() (1) {\n"
  "	kdm = (mginull*p1)/p2\n"
  "}\n"
  "FUNCTION ssPV( kdc(), kdm()) (mM) {\n"
  "	ssPV = PVnull/(1+kdc()+kdm())\n"
  "}\n"
  "FUNCTION ssPVca( kdc(), kdm()) (mM) {\n"
  "	ssPVca = (PVnull*kdc())/(1+kdc()+kdm())\n"
  "}\n"
  "FUNCTION ssPVmg( kdc(), kdm()) (mM) {\n"
  "	ssPVmg = (PVnull*kdm())/(1+kdc()+kdm())\n"
  "}\n"
  ;
    hoc_reg_nmodl_filename(mech_type, nmodl_filename);
    hoc_reg_nmodl_text(mech_type, nmodl_file_text);
}
#endif
