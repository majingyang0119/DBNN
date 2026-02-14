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
static constexpr auto number_of_datum_variables = 4;
static constexpr auto number_of_floating_point_variables = 20;
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
 
#define nrn_init _nrn_init__Cav3_3
#define _nrn_initial _nrn_initial__Cav3_3
#define nrn_cur _nrn_cur__Cav3_3
#define _nrn_current _nrn_current__Cav3_3
#define nrn_jacob _nrn_jacob__Cav3_3
#define nrn_state _nrn_state__Cav3_3
#define _net_receive _net_receive__Cav3_3 
#define rates rates__Cav3_3 
#define states states__Cav3_3 
 
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
#define gCav3_3bar _ml->template fpfield<0>(_iml)
#define gCav3_3bar_columnindex 0
#define pcabar _ml->template fpfield<1>(_iml)
#define pcabar_columnindex 1
#define ica _ml->template fpfield<2>(_iml)
#define ica_columnindex 2
#define n_inf _ml->template fpfield<3>(_iml)
#define n_inf_columnindex 3
#define tau_n _ml->template fpfield<4>(_iml)
#define tau_n_columnindex 4
#define l_inf _ml->template fpfield<5>(_iml)
#define l_inf_columnindex 5
#define tau_l _ml->template fpfield<6>(_iml)
#define tau_l_columnindex 6
#define n _ml->template fpfield<7>(_iml)
#define n_columnindex 7
#define l _ml->template fpfield<8>(_iml)
#define l_columnindex 8
#define gCav3_3 _ml->template fpfield<9>(_iml)
#define gCav3_3_columnindex 9
#define cai _ml->template fpfield<10>(_iml)
#define cai_columnindex 10
#define cao _ml->template fpfield<11>(_iml)
#define cao_columnindex 11
#define qt _ml->template fpfield<12>(_iml)
#define qt_columnindex 12
#define T _ml->template fpfield<13>(_iml)
#define T_columnindex 13
#define ghk _ml->template fpfield<14>(_iml)
#define ghk_columnindex 14
#define w _ml->template fpfield<15>(_iml)
#define w_columnindex 15
#define Dn _ml->template fpfield<16>(_iml)
#define Dn_columnindex 16
#define Dl _ml->template fpfield<17>(_iml)
#define Dl_columnindex 17
#define v _ml->template fpfield<18>(_iml)
#define v_columnindex 18
#define _g _ml->template fpfield<19>(_iml)
#define _g_columnindex 19
#define _ion_cai *(_ml->dptr_field<0>(_iml))
#define _p_ion_cai static_cast<neuron::container::data_handle<double>>(_ppvar[0])
#define _ion_cao *(_ml->dptr_field<1>(_iml))
#define _p_ion_cao static_cast<neuron::container::data_handle<double>>(_ppvar[1])
#define _ion_ica *(_ml->dptr_field<2>(_iml))
#define _p_ion_ica static_cast<neuron::container::data_handle<double>>(_ppvar[2])
#define _ion_dicadv *(_ml->dptr_field<3>(_iml))
 /* Thread safe. No static _ml, _iml or _ppvar. */
 static int hoc_nrnpointerindex =  -1;
 static _nrn_mechanism_std_vector<Datum> _extcall_thread;
 static Prop* _extcall_prop;
 /* _prop_id kind of shadows _extcall_prop to allow validity checking. */
 static _nrn_non_owning_id_without_container _prop_id{};
 /* external NEURON variables */
 extern double celsius;
 /* declaration of user functions */
 static void _hoc_rates(void);
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
 {"setdata_Cav3_3", _hoc_setdata},
 {"rates_Cav3_3", _hoc_rates},
 {0, 0}
};
 
/* Direct Python call wrappers to density mechanism functions.*/
 static double _npy_rates(Prop*);
 
static NPyDirectMechFunc npy_direct_func_proc[] = {
 {"rates", _npy_rates},
 {0, 0}
};
 /* declare global and static user variables */
 #define gind 0
 #define _gth 0
#define F F_Cav3_3
 double F = 96520;
#define PI PI_Cav3_3
 double PI = 3.14;
#define R R_Cav3_3
 double R = 8.3134;
#define kl kl_Cav3_3
 double kl = -6.1;
#define kn kn_Cav3_3
 double kn = 6.2;
#define q10 q10_Cav3_3
 double q10 = 2.3;
#define vhalfl vhalfl_Cav3_3
 double vhalfl = -69.8;
#define vhalfn vhalfn_Cav3_3
 double vhalfn = -41.5;
#define z z_Cav3_3
 double z = 2;
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 {0, 0, 0}
};
 static HocParmUnits _hoc_parm_units[] = {
 {"gCav3_3bar_Cav3_3", "S/cm2"},
 {"ica_Cav3_3", "mA/cm2"},
 {0, 0}
};
 static double delta_t = 0.01;
 static double l0 = 0;
 static double n0 = 0;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 {"vhalfn_Cav3_3", &vhalfn_Cav3_3},
 {"vhalfl_Cav3_3", &vhalfl_Cav3_3},
 {"kn_Cav3_3", &kn_Cav3_3},
 {"kl_Cav3_3", &kl_Cav3_3},
 {"q10_Cav3_3", &q10_Cav3_3},
 {"z_Cav3_3", &z_Cav3_3},
 {"F_Cav3_3", &F_Cav3_3},
 {"R_Cav3_3", &R_Cav3_3},
 {"PI_Cav3_3", &PI_Cav3_3},
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
 
#define _cvode_ieq _ppvar[4].literal_value<int>()
 static void _ode_matsol_instance1(_internalthreadargsproto_);
 /* connect range variables in _p that hoc is supposed to know about */
 static const char *_mechanism[] = {
 "7.7.0",
"Cav3_3",
 "gCav3_3bar_Cav3_3",
 "pcabar_Cav3_3",
 0,
 "ica_Cav3_3",
 "n_inf_Cav3_3",
 "tau_n_Cav3_3",
 "l_inf_Cav3_3",
 "tau_l_Cav3_3",
 0,
 "n_Cav3_3",
 "l_Cav3_3",
 0,
 0};
 static Symbol* _ca_sym;
 
 /* Used by NrnProperty */
 static _nrn_mechanism_std_vector<double> _parm_default{
     1e-05, /* gCav3_3bar */
     0.0001, /* pcabar */
 }; 
 
 
extern Prop* need_memb(Symbol*);
static void nrn_alloc(Prop* _prop) {
  Prop *prop_ion{};
  Datum *_ppvar{};
   _ppvar = nrn_prop_datum_alloc(_mechtype, 5, _prop);
    _nrn_mechanism_access_dparam(_prop) = _ppvar;
     _nrn_mechanism_cache_instance _ml_real{_prop};
    auto* const _ml = &_ml_real;
    size_t const _iml{};
    assert(_nrn_mechanism_get_num_vars(_prop) == 20);
 	/*initialize range parameters*/
 	gCav3_3bar = _parm_default[0]; /* 1e-05 */
 	pcabar = _parm_default[1]; /* 0.0001 */
 	 assert(_nrn_mechanism_get_num_vars(_prop) == 20);
 	_nrn_mechanism_access_dparam(_prop) = _ppvar;
 	/*connect ionic variables to this model*/
 prop_ion = need_memb(_ca_sym);
 nrn_promote(prop_ion, 1, 0);
 	_ppvar[0] = _nrn_mechanism_get_param_handle(prop_ion, 1); /* cai */
 	_ppvar[1] = _nrn_mechanism_get_param_handle(prop_ion, 2); /* cao */
 	_ppvar[2] = _nrn_mechanism_get_param_handle(prop_ion, 3); /* ica */
 	_ppvar[3] = _nrn_mechanism_get_param_handle(prop_ion, 4); /* _ion_dicadv */
 
}
 static void _initlists();
  /* some states have an absolute tolerance */
 static Symbol** _atollist;
 static HocStateTolerance _hoc_state_tol[] = {
 {0, 0}
};
 extern Symbol* hoc_lookup(const char*);
extern void _nrn_thread_reg(int, int, void(*)(Datum*));
void _nrn_thread_table_reg(int, nrn_thread_table_check_t);
extern void hoc_register_tolerance(int, HocStateTolerance*, Symbol***);
extern void _cvode_abstol( Symbol**, double*, int);

 extern "C" void _Cav3_3_reg() {
	int _vectorized = 1;
  _initlists();
 	ion_reg("ca", -10000.);
 	_ca_sym = hoc_lookup("ca_ion");
 	register_mech(_mechanism, nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init, hoc_nrnpointerindex, 1);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
 hoc_register_parm_default(_mechtype, &_parm_default);
         hoc_register_npy_direct(_mechtype, npy_direct_func_proc);
     _nrn_setdata_reg(_mechtype, _setdata);
 #if NMODL_TEXT
  register_nmodl_text_and_filename(_mechtype);
#endif
   _nrn_mechanism_register_data_fields(_mechtype,
                                       _nrn_mechanism_field<double>{"gCav3_3bar"} /* 0 */,
                                       _nrn_mechanism_field<double>{"pcabar"} /* 1 */,
                                       _nrn_mechanism_field<double>{"ica"} /* 2 */,
                                       _nrn_mechanism_field<double>{"n_inf"} /* 3 */,
                                       _nrn_mechanism_field<double>{"tau_n"} /* 4 */,
                                       _nrn_mechanism_field<double>{"l_inf"} /* 5 */,
                                       _nrn_mechanism_field<double>{"tau_l"} /* 6 */,
                                       _nrn_mechanism_field<double>{"n"} /* 7 */,
                                       _nrn_mechanism_field<double>{"l"} /* 8 */,
                                       _nrn_mechanism_field<double>{"gCav3_3"} /* 9 */,
                                       _nrn_mechanism_field<double>{"cai"} /* 10 */,
                                       _nrn_mechanism_field<double>{"cao"} /* 11 */,
                                       _nrn_mechanism_field<double>{"qt"} /* 12 */,
                                       _nrn_mechanism_field<double>{"T"} /* 13 */,
                                       _nrn_mechanism_field<double>{"ghk"} /* 14 */,
                                       _nrn_mechanism_field<double>{"w"} /* 15 */,
                                       _nrn_mechanism_field<double>{"Dn"} /* 16 */,
                                       _nrn_mechanism_field<double>{"Dl"} /* 17 */,
                                       _nrn_mechanism_field<double>{"v"} /* 18 */,
                                       _nrn_mechanism_field<double>{"_g"} /* 19 */,
                                       _nrn_mechanism_field<double*>{"_ion_cai", "ca_ion"} /* 0 */,
                                       _nrn_mechanism_field<double*>{"_ion_cao", "ca_ion"} /* 1 */,
                                       _nrn_mechanism_field<double*>{"_ion_ica", "ca_ion"} /* 2 */,
                                       _nrn_mechanism_field<double*>{"_ion_dicadv", "ca_ion"} /* 3 */,
                                       _nrn_mechanism_field<int>{"_cvode_ieq", "cvodeieq"} /* 4 */);
  hoc_register_prop_size(_mechtype, 20, 5);
  hoc_register_dparam_semantics(_mechtype, 0, "ca_ion");
  hoc_register_dparam_semantics(_mechtype, 1, "ca_ion");
  hoc_register_dparam_semantics(_mechtype, 2, "ca_ion");
  hoc_register_dparam_semantics(_mechtype, 3, "ca_ion");
  hoc_register_dparam_semantics(_mechtype, 4, "cvodeieq");
 	hoc_register_cvode(_mechtype, _ode_count, _ode_map, _ode_spec, _ode_matsol);
 	hoc_register_tolerance(_mechtype, _hoc_state_tol, &_atollist);
 
    hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 Cav3_3 /home/mjy/project/bilinear_network/purkinje/mod_files/Cav3_3.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
static int _reset;
static const char *modelname = "CaV 3.3 CA3 hippocampal neuron";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static void _modl_cleanup(){ _match_recurse=1;}
static int rates(_internalthreadargsproto_);
 
static int _ode_spec1(_internalthreadargsproto_);
/*static int _ode_matsol1(_internalthreadargsproto_);*/
 static neuron::container::field_index _slist1[2], _dlist1[2];
 static int states(_internalthreadargsproto_);
 
/*CVODE*/
 static int _ode_spec1 (_internalthreadargsproto_) {int _reset = 0; {
   rates ( _threadargs_ ) ;
   Dn = ( n_inf - n ) / tau_n ;
   Dl = ( l_inf - l ) / tau_l ;
   }
 return _reset;
}
 static int _ode_matsol1 (_internalthreadargsproto_) {
 rates ( _threadargs_ ) ;
 Dn = Dn  / (1. - dt*( ( ( ( - 1.0 ) ) ) / tau_n )) ;
 Dl = Dl  / (1. - dt*( ( ( ( - 1.0 ) ) ) / tau_l )) ;
  return 0;
}
 /*END CVODE*/
 static int states (_internalthreadargsproto_) { {
   rates ( _threadargs_ ) ;
    n = n + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / tau_n)))*(- ( ( ( n_inf ) ) / tau_n ) / ( ( ( ( - 1.0 ) ) ) / tau_n ) - n) ;
    l = l + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / tau_l)))*(- ( ( ( l_inf ) ) / tau_l ) / ( ( ( ( - 1.0 ) ) ) / tau_l ) - l) ;
   }
  return 0;
}
 
static int  rates ( _internalthreadargsproto_ ) {
   n_inf = 1.0 / ( 1.0 + exp ( - ( v - vhalfn ) / kn ) ) ;
   l_inf = 1.0 / ( 1.0 + exp ( - ( v - vhalfl ) / kl ) ) ;
   if ( v > - 60.0 ) {
     tau_n = ( 7.2 + 0.02 * exp ( - v / 14.7 ) ) / qt ;
     tau_l = ( 79.5 + 2.0 * exp ( - v / 9.3 ) ) / qt ;
     }
   else {
     tau_n = ( 0.875 * exp ( ( v + 120.0 ) / 41.0 ) ) / qt ;
     tau_l = 260.0 / qt ;
     }
   w = v * 0.001 * z * F / ( R * T ) ;
   ghk = - 0.001 * z * F * ( cao - cai * exp ( w ) ) * w / ( exp ( w ) - 1.0 ) ;
    return 0; }
 
static void _hoc_rates(void) {
  double _r;
 Datum* _ppvar; Datum* _thread; NrnThread* _nt;
 
  if(!_prop_id) {
    hoc_execerror("No data for rates_Cav3_3. Requires prior call to setdata_Cav3_3 and that the specified mechanism instance still be in existence.", NULL);
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
 rates ( _threadargs_ );
 hoc_retpushx(_r);
}
 
static double _npy_rates(Prop* _prop) {
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
 rates ( _threadargs_ );
 return(_r);
}
 
static int _ode_count(int _type){ return 2;}
 
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
  cao = _ion_cao;
     _ode_spec1 (_threadargs_);
  }}
 
static void _ode_map(Prop* _prop, int _ieq, neuron::container::data_handle<double>* _pv, neuron::container::data_handle<double>* _pvdot, double* _atol, int _type) { 
  Datum* _ppvar;
  _ppvar = _nrn_mechanism_access_dparam(_prop);
  _cvode_ieq = _ieq;
  for (int _i=0; _i < 2; ++_i) {
    _pv[_i] = _nrn_mechanism_get_param_handle(_prop, _slist1[_i]);
    _pvdot[_i] = _nrn_mechanism_get_param_handle(_prop, _dlist1[_i]);
    _cvode_abstol(_atollist, _atol, _i);
  }
 }
 
static void _ode_matsol_instance1(_internalthreadargsproto_) {
 _ode_matsol1 (_threadargs_);
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
  cao = _ion_cao;
 _ode_matsol_instance1(_threadargs_);
 }}

static void initmodel(_internalthreadargsproto_) {
  int _i; double _save;{
  l = l0;
  n = n0;
 {
   T = celsius + 273.14 ;
   qt = pow ( q10 , ( celsius - 28.0 ) / 10.0 ) ;
   rates ( _threadargs_ ) ;
   n = n_inf ;
   l = l_inf ;
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
  cao = _ion_cao;
 initmodel(_threadargs_);
 }
}

static double _nrn_current(_internalthreadargsprotocomma_ double _v) {
double _current=0.; v=_v;
{ {
   ica = gCav3_3bar * pcabar * n * n * l * ghk ;
   }
 _current += ica;

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
  cai = _ion_cai;
  cao = _ion_cao;
 auto const _g_local = _nrn_current(_threadargscomma_ _v + .001);
 	{ double _dica;
  _dica = ica;
 _rhs = _nrn_current(_threadargscomma_ _v);
  _ion_dicadv += (_dica - ica)/.001 ;
 	}
 _g = (_g_local - _rhs)/.001;
  _ion_ica += ica ;
	 _vec_rhs[_ni[_iml]] -= _rhs;
 
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
  cao = _ion_cao;
 {   states(_threadargs_);
  } }}

}

static void terminal(){}

static void _initlists(){
 int _i; static int _first = 1;
  if (!_first) return;
 _slist1[0] = {n_columnindex, 0};  _dlist1[0] = {Dn_columnindex, 0};
 _slist1[1] = {l_columnindex, 0};  _dlist1[1] = {Dl_columnindex, 0};
_first = 0;
}

#if NMODL_TEXT
static void register_nmodl_text_and_filename(int mech_type) {
    const char* nmodl_filename = "/home/mjy/project/bilinear_network/purkinje/mod_files/Cav3_3.mod";
    const char* nmodl_file_text = 
  "TITLE CaV 3.3 CA3 hippocampal neuron\n"
  "\n"
  "COMMENT\n"
  "    Cell model: CA3 hippocampal neuron\n"
  "    \n"
  "    Created by jun xu @ Clancy Lab of Cornell University Medical College on 3/27/05\n"
  "    \n"
  "    Geometry: single-compartment model modified on 04/19/07 \n"
  "    Xu J, Clancy CE (2008) Ionic mechanisms of endogenous bursting in CA3 hippocampal pyramidal neurons: \n"
  "        a model study. PLoS ONE 3:e2056- [PubMed]\n"
  "\n"
  "ENDCOMMENT \n"
  " \n"
  " \n"
  " NEURON	{\n"
  "        : CaT--alpha 1I CaV3.3\n"
  "	SUFFIX Cav3_3\n"
  "	USEION ca READ cai, cao WRITE ica\n"
  "	RANGE gCav3_3bar, pcabar, ica, tau_l, tau_n, n_inf, l_inf\n"
  "}\n"
  "\n"
  "UNITS	{\n"
  "	(S) = (siemens)\n"
  "	(mV) = (millivolt)\n"
  "	(mA) = (milliamp)\n"
  "}\n"
  "\n"
  "PARAMETER	{\n"
  "    gCav3_3bar = 0.00001 (S/cm2)\n"
  "    vhalfn = -41.5  :mv\n"
  "    vhalfl = -69.8\n"
  "    kn = 6.2\n"
  "    kl = -6.1\n"
  "    q10 = 2.3\n"
  "    pcabar = 0.0001 : cm/s to check!!!\n"
  "    z= 2\n"
  "    F = 96520 : Farady constant (coulomb/mol)\n"
  "    R = 8.3134 : gas constant (J/K.mol)\n"
  "    PI = 3.14    \n"
  "}\n"
  "\n"
  "ASSIGNED	{\n"
  "	v	(mV)\n"
  "	ica	(mA/cm2)\n"
  "	gCav3_3	(S/cm2)\n"
  "	n_inf\n"
  "	tau_n\n"
  "	l_inf\n"
  "	tau_l\n"
  "	cai     (mM)\n"
  "	cao     (mM)\n"
  "	qt \n"
  "	T  : absolute temperature (K)\n"
  "	ghk\n"
  "	w\n"
  "}\n"
  "\n"
  "STATE	{ \n"
  "	n\n"
  "	l\n"
  "}\n"
  "\n"
  "BREAKPOINT	{\n"
  "    SOLVE states METHOD cnexp\n"
  "    ica = gCav3_3bar*pcabar*n*n*l*ghk\n"
  "}\n"
  "\n"
  "DERIVATIVE states	{\n"
  "	rates()\n"
  "	n' = (n_inf-n)/tau_n\n"
  "	l' = (l_inf-l)/tau_l\n"
  "    }\n"
  "    \n"
  "INITIAL{\n"
  "	T = celsius+273.14\n"
  "	qt = pow(q10,(celsius-28)/10)\n"
  "	rates()\n"
  "	n = n_inf\n"
  "	l = l_inf\n"
  "}\n"
  "\n"
  "PROCEDURE rates(){\n"
  "	n_inf = 1/(1+exp(-(v-vhalfn)/kn))\n"
  "	l_inf = 1/(1+exp(-(v-vhalfl)/kl))\n"
  "	\n"
  "        if (v > -60) {\n"
  "            tau_n = (7.2+0.02*exp(-v/14.7))/qt\n"
  "	    tau_l = (79.5+2.0*exp(-v/9.3))/qt\n"
  "        }else{\n"
  "            tau_n = (0.875*exp((v+120)/41))/qt\n"
  "	    tau_l = 260/qt\n"
  "        }\n"
  "	\n"
  "      w = v*0.001*z*F/(R*T)\n"
  "      ghk = -0.001*z*F*(cao-cai*exp(w))*w/(exp(w)-1)	\n"
  "}\n"
  ;
    hoc_reg_nmodl_filename(mech_type, nmodl_filename);
    hoc_reg_nmodl_text(mech_type, nmodl_file_text);
}
#endif
