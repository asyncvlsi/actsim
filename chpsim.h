/*************************************************************************
 *
 *  Copyright (c) 2020 Rajit Manohar
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  as published by the Free Software Foundation; either version 2
 *  of the License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor,
 *  Boston, MA  02110-1301, USA.
 *
 **************************************************************************
 */
#ifndef __ACT_CHP_SIM_H__
#define __ACT_CHP_SIM_H__

#include <simdes.h>
#include "actsim.h"

class ChpSim : public ActSimObj {
 public:
  ChpSim (ChpSimGraph *, stateinfo_t *si, act_chp_lang_t *, ActSimCore *sim);
     /* initialize simulation, and create initial event */

  void Step (int ev_type);	/* run a step of the simulation */

  void computeFanout ();
  
 private:
  int _npc;			/* # of program counters */
  ChpSimGraph **_pc;		/* current PC state of simulation */

  int _pcused;			/* # of _pc[] slots currently being
				   used */
  int _stalled_pc;
  act_chp_lang_t *_savedc;

  stateinfo_t *_si;

  WaitForOne *_probe;
  
  int _max_program_counters (act_chp_lang_t *c);
  void _compute_used_variables (act_chp_lang_t *c);
  void _compute_used_variables_helper (act_chp_lang_t *c);
  void _compute_used_variables_helper (Expr *e);
  struct iHashtable *_tmpused;

  list_t *_statestk;
  expr_res exprEval (Expr *e);
  expr_res funcEval (Function *, int, expr_res *);
  expr_res varEval (int id, int type);
  void _run_chp (act_chp_lang_t *);
  /* type == 3 : probe */

  void varSet (int id, int type, expr_res v);
  int varSend (int pc, int wakeup, int id, expr_res v);
  int varRecv (int pc, int wakeup, int id, expr_res *v);

  int _updatepc (int pc);
  int _add_waitcond (chpsimcond *gc, int pc, int undo = 0);
  int _collect_sharedvars (Expr *e, int pc, int undo);
};



#endif /* __ACT_CHP_SIM_H__ */
