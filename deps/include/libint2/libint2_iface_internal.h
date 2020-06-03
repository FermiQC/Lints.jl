/*
 *  Copyright (C) 2004-2020 Edward F. Valeev
 *
 *  This file is part of Libint.
 *
 *  Libint is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Libint is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with Libint.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef _libint2_libint2ifaceint_h_
#define _libint2_libint2ifaceint_h_

#include <./_overlap_S_P.h>

#include <./_overlap_S_P_prereq.h>

#include <./_overlap_S_D.h>

#include <./_overlap_S_D_prereq.h>

#include <./_overlap_P_S.h>

#include <./_overlap_P_S_prereq.h>

#include <./_overlap_P_P.h>

#include <./_overlap_P_P_prereq.h>

#include <./_overlap_P_D.h>

#include <./_overlap_P_D_prereq.h>

#include <./_overlap_D_S.h>

#include <./_overlap_D_S_prereq.h>

#include <./_overlap_D_P.h>

#include <./_overlap_D_P_prereq.h>

#include <./_overlap_D_D.h>

#include <./_overlap_D_D_prereq.h>

#include <./_kinetic_S_S.h>

#include <./_kinetic_S_S_prereq.h>

#include <./_kinetic_S_P.h>

#include <./_kinetic_S_P_prereq.h>

#include <./_kinetic_S_D.h>

#include <./_kinetic_S_D_prereq.h>

#include <./_kinetic_P_S.h>

#include <./_kinetic_P_S_prereq.h>

#include <./_kinetic_P_P.h>

#include <./_kinetic_P_P_prereq.h>

#include <./_kinetic_P_D.h>

#include <./_kinetic_P_D_prereq.h>

#include <./_kinetic_D_S.h>

#include <./_kinetic_D_S_prereq.h>

#include <./_kinetic_D_P.h>

#include <./_kinetic_D_P_prereq.h>

#include <./_kinetic_D_D.h>

#include <./_kinetic_D_D_prereq.h>

#include <./_elecpot_S_P.h>

#include <./_elecpot_S_P_prereq.h>

#include <./_elecpot_S_D.h>

#include <./_elecpot_S_D_prereq.h>

#include <./_elecpot_P_S.h>

#include <./_elecpot_P_S_prereq.h>

#include <./_elecpot_P_P.h>

#include <./_elecpot_P_P_prereq.h>

#include <./_elecpot_P_D.h>

#include <./_elecpot_P_D_prereq.h>

#include <./_elecpot_D_S.h>

#include <./_elecpot_D_S_prereq.h>

#include <./_elecpot_D_P.h>

#include <./_elecpot_D_P_prereq.h>

#include <./_elecpot_D_D.h>

#include <./_elecpot_D_D_prereq.h>

#include <./_1emultipole_S_S.h>

#include <./_1emultipole_S_S_prereq.h>

#include <./_1emultipole_S_P.h>

#include <./_1emultipole_S_P_prereq.h>

#include <./_1emultipole_S_D.h>

#include <./_1emultipole_S_D_prereq.h>

#include <./_1emultipole_P_S.h>

#include <./_1emultipole_P_S_prereq.h>

#include <./_1emultipole_P_P.h>

#include <./_1emultipole_P_P_prereq.h>

#include <./_1emultipole_P_D.h>

#include <./_1emultipole_P_D_prereq.h>

#include <./_1emultipole_D_S.h>

#include <./_1emultipole_D_S_prereq.h>

#include <./_1emultipole_D_P.h>

#include <./_1emultipole_D_P_prereq.h>

#include <./_1emultipole_D_D.h>

#include <./_1emultipole_D_D_prereq.h>

#include <./_2emultipole_S_S.h>

#include <./_2emultipole_S_S_prereq.h>

#include <./_2emultipole_S_P.h>

#include <./_2emultipole_S_P_prereq.h>

#include <./_2emultipole_S_D.h>

#include <./_2emultipole_S_D_prereq.h>

#include <./_2emultipole_P_S.h>

#include <./_2emultipole_P_S_prereq.h>

#include <./_2emultipole_P_P.h>

#include <./_2emultipole_P_P_prereq.h>

#include <./_2emultipole_P_D.h>

#include <./_2emultipole_P_D_prereq.h>

#include <./_2emultipole_D_S.h>

#include <./_2emultipole_D_S_prereq.h>

#include <./_2emultipole_D_P.h>

#include <./_2emultipole_D_P_prereq.h>

#include <./_2emultipole_D_D.h>

#include <./_2emultipole_D_D_prereq.h>

#include <./_3emultipole_S_S.h>

#include <./_3emultipole_S_S_prereq.h>

#include <./_3emultipole_S_P.h>

#include <./_3emultipole_S_P_prereq.h>

#include <./_3emultipole_S_D.h>

#include <./_3emultipole_S_D_prereq.h>

#include <./_3emultipole_P_S.h>

#include <./_3emultipole_P_S_prereq.h>

#include <./_3emultipole_P_P.h>

#include <./_3emultipole_P_P_prereq.h>

#include <./_3emultipole_P_D.h>

#include <./_3emultipole_P_D_prereq.h>

#include <./_3emultipole_D_S.h>

#include <./_3emultipole_D_S_prereq.h>

#include <./_3emultipole_D_P.h>

#include <./_3emultipole_D_P_prereq.h>

#include <./_3emultipole_D_D.h>

#include <./_3emultipole_D_D_prereq.h>

#include <./_sphemultipole_S_S.h>

#include <./_sphemultipole_S_S_prereq.h>

#include <./_sphemultipole_S_P.h>

#include <./_sphemultipole_S_P_prereq.h>

#include <./_sphemultipole_S_D.h>

#include <./_sphemultipole_S_D_prereq.h>

#include <./_sphemultipole_P_S.h>

#include <./_sphemultipole_P_S_prereq.h>

#include <./_sphemultipole_P_P.h>

#include <./_sphemultipole_P_P_prereq.h>

#include <./_sphemultipole_P_D.h>

#include <./_sphemultipole_P_D_prereq.h>

#include <./_sphemultipole_D_S.h>

#include <./_sphemultipole_D_S_prereq.h>

#include <./_sphemultipole_D_P.h>

#include <./_sphemultipole_D_P_prereq.h>

#include <./_sphemultipole_D_D.h>

#include <./_sphemultipole_D_D_prereq.h>

#include <./_aB_S__0__S__1___TwoPRep_S__0__S__1___Ab__up_0.h>

#include <./_aB_S__0__S__1___TwoPRep_S__0__S__1___Ab__up_0_prereq.h>

#include <./_aB_S__0__P__1___TwoPRep_S__0__S__1___Ab__up_0.h>

#include <./_aB_S__0__P__1___TwoPRep_S__0__S__1___Ab__up_0_prereq.h>

#include <./_aB_S__0__P__1___TwoPRep_S__0__P__1___Ab__up_0.h>

#include <./_aB_S__0__P__1___TwoPRep_S__0__P__1___Ab__up_0_prereq.h>

#include <./_aB_S__0__D__1___TwoPRep_S__0__S__1___Ab__up_0.h>

#include <./_aB_S__0__D__1___TwoPRep_S__0__S__1___Ab__up_0_prereq.h>

#include <./_aB_S__0__D__1___TwoPRep_S__0__P__1___Ab__up_0.h>

#include <./_aB_S__0__D__1___TwoPRep_S__0__P__1___Ab__up_0_prereq.h>

#include <./_aB_S__0__D__1___TwoPRep_S__0__D__1___Ab__up_0.h>

#include <./_aB_S__0__D__1___TwoPRep_S__0__D__1___Ab__up_0_prereq.h>

#include <./_aB_P__0__P__1___TwoPRep_S__0__S__1___Ab__up_0.h>

#include <./_aB_P__0__P__1___TwoPRep_S__0__S__1___Ab__up_0_prereq.h>

#include <./_aB_P__0__P__1___TwoPRep_S__0__P__1___Ab__up_0.h>

#include <./_aB_P__0__P__1___TwoPRep_S__0__P__1___Ab__up_0_prereq.h>

#include <./_aB_P__0__D__1___TwoPRep_S__0__S__1___Ab__up_0.h>

#include <./_aB_P__0__D__1___TwoPRep_S__0__S__1___Ab__up_0_prereq.h>

#include <./_aB_P__0__D__1___TwoPRep_S__0__P__1___Ab__up_0.h>

#include <./_aB_P__0__D__1___TwoPRep_S__0__P__1___Ab__up_0_prereq.h>

#include <./_aB_P__0__D__1___TwoPRep_S__0__D__1___Ab__up_0.h>

#include <./_aB_P__0__D__1___TwoPRep_S__0__D__1___Ab__up_0_prereq.h>

#include <./_aB_P__0__P__1___TwoPRep_P__0__P__1___Ab__up_0.h>

#include <./_aB_P__0__P__1___TwoPRep_P__0__P__1___Ab__up_0_prereq.h>

#include <./_aB_P__0__D__1___TwoPRep_P__0__S__1___Ab__up_0.h>

#include <./_aB_P__0__D__1___TwoPRep_P__0__S__1___Ab__up_0_prereq.h>

#include <./_aB_P__0__D__1___TwoPRep_P__0__P__1___Ab__up_0.h>

#include <./_aB_P__0__D__1___TwoPRep_P__0__P__1___Ab__up_0_prereq.h>

#include <./_aB_P__0__D__1___TwoPRep_P__0__D__1___Ab__up_0.h>

#include <./_aB_P__0__D__1___TwoPRep_P__0__D__1___Ab__up_0_prereq.h>

#include <./_aB_D__0__P__1___TwoPRep_S__0__P__1___Ab__up_0.h>

#include <./_aB_D__0__P__1___TwoPRep_S__0__P__1___Ab__up_0_prereq.h>

#include <./_aB_D__0__D__1___TwoPRep_S__0__S__1___Ab__up_0.h>

#include <./_aB_D__0__D__1___TwoPRep_S__0__S__1___Ab__up_0_prereq.h>

#include <./_aB_D__0__D__1___TwoPRep_S__0__P__1___Ab__up_0.h>

#include <./_aB_D__0__D__1___TwoPRep_S__0__P__1___Ab__up_0_prereq.h>

#include <./_aB_D__0__D__1___TwoPRep_S__0__D__1___Ab__up_0.h>

#include <./_aB_D__0__D__1___TwoPRep_S__0__D__1___Ab__up_0_prereq.h>

#include <./_aB_D__0__D__1___TwoPRep_P__0__P__1___Ab__up_0.h>

#include <./_aB_D__0__D__1___TwoPRep_P__0__P__1___Ab__up_0_prereq.h>

#include <./_aB_D__0__D__1___TwoPRep_P__0__D__1___Ab__up_0.h>

#include <./_aB_D__0__D__1___TwoPRep_P__0__D__1___Ab__up_0_prereq.h>

#include <./_aB_D__0__D__1___TwoPRep_D__0__D__1___Ab__up_0.h>

#include <./_aB_D__0__D__1___TwoPRep_D__0__D__1___Ab__up_0_prereq.h>

#include <./eri3_aB_S__0__S__1___TwoPRep_unit__0__S__1___Ab__up_0.h>

#include <./eri3_aB_S__0__S__1___TwoPRep_unit__0__S__1___Ab__up_0_prereq.h>

#include <./eri3_aB_S__0__P__1___TwoPRep_unit__0__S__1___Ab__up_0.h>

#include <./eri3_aB_S__0__P__1___TwoPRep_unit__0__S__1___Ab__up_0_prereq.h>

#include <./eri3_aB_S__0__P__1___TwoPRep_unit__0__P__1___Ab__up_0.h>

#include <./eri3_aB_S__0__P__1___TwoPRep_unit__0__P__1___Ab__up_0_prereq.h>

#include <./eri3_aB_S__0__D__1___TwoPRep_unit__0__S__1___Ab__up_0.h>

#include <./eri3_aB_S__0__D__1___TwoPRep_unit__0__S__1___Ab__up_0_prereq.h>

#include <./eri3_aB_S__0__D__1___TwoPRep_unit__0__P__1___Ab__up_0.h>

#include <./eri3_aB_S__0__D__1___TwoPRep_unit__0__P__1___Ab__up_0_prereq.h>

#include <./eri3_aB_S__0__D__1___TwoPRep_unit__0__D__1___Ab__up_0.h>

#include <./eri3_aB_S__0__D__1___TwoPRep_unit__0__D__1___Ab__up_0_prereq.h>

#include <./eri3_aB_WP__0__S__1___TwoPRep_unit__0__S__1___Ab__up_0.h>

#include <./eri3_aB_WP__0__S__1___TwoPRep_unit__0__S__1___Ab__up_0_prereq.h>

#include <./eri3_aB_WP__0__P__1___TwoPRep_unit__0__S__1___Ab__up_0.h>

#include <./eri3_aB_WP__0__P__1___TwoPRep_unit__0__S__1___Ab__up_0_prereq.h>

#include <./eri3_aB_WP__0__P__1___TwoPRep_unit__0__P__1___Ab__up_0.h>

#include <./eri3_aB_WP__0__P__1___TwoPRep_unit__0__P__1___Ab__up_0_prereq.h>

#include <./eri3_aB_WP__0__D__1___TwoPRep_unit__0__S__1___Ab__up_0.h>

#include <./eri3_aB_WP__0__D__1___TwoPRep_unit__0__S__1___Ab__up_0_prereq.h>

#include <./eri3_aB_WP__0__D__1___TwoPRep_unit__0__P__1___Ab__up_0.h>

#include <./eri3_aB_WP__0__D__1___TwoPRep_unit__0__P__1___Ab__up_0_prereq.h>

#include <./eri3_aB_WP__0__D__1___TwoPRep_unit__0__D__1___Ab__up_0.h>

#include <./eri3_aB_WP__0__D__1___TwoPRep_unit__0__D__1___Ab__up_0_prereq.h>

#include <./eri3_aB_WD__0__S__1___TwoPRep_unit__0__S__1___Ab__up_0.h>

#include <./eri3_aB_WD__0__S__1___TwoPRep_unit__0__S__1___Ab__up_0_prereq.h>

#include <./eri3_aB_WD__0__P__1___TwoPRep_unit__0__S__1___Ab__up_0.h>

#include <./eri3_aB_WD__0__P__1___TwoPRep_unit__0__S__1___Ab__up_0_prereq.h>

#include <./eri3_aB_WD__0__P__1___TwoPRep_unit__0__P__1___Ab__up_0.h>

#include <./eri3_aB_WD__0__P__1___TwoPRep_unit__0__P__1___Ab__up_0_prereq.h>

#include <./eri3_aB_WD__0__D__1___TwoPRep_unit__0__S__1___Ab__up_0.h>

#include <./eri3_aB_WD__0__D__1___TwoPRep_unit__0__S__1___Ab__up_0_prereq.h>

#include <./eri3_aB_WD__0__D__1___TwoPRep_unit__0__P__1___Ab__up_0.h>

#include <./eri3_aB_WD__0__D__1___TwoPRep_unit__0__P__1___Ab__up_0_prereq.h>

#include <./eri3_aB_WD__0__D__1___TwoPRep_unit__0__D__1___Ab__up_0.h>

#include <./eri3_aB_WD__0__D__1___TwoPRep_unit__0__D__1___Ab__up_0_prereq.h>

#include <./eri2_aB_S__0__S__1___TwoPRep_unit__0__unit__1___Ab__up_0.h>

#include <./eri2_aB_S__0__S__1___TwoPRep_unit__0__unit__1___Ab__up_0_prereq.h>

#include <./eri2_aB_S__0__WP__1___TwoPRep_unit__0__unit__1___Ab__up_0.h>

#include <./eri2_aB_S__0__WP__1___TwoPRep_unit__0__unit__1___Ab__up_0_prereq.h>

#include <./eri2_aB_S__0__WD__1___TwoPRep_unit__0__unit__1___Ab__up_0.h>

#include <./eri2_aB_S__0__WD__1___TwoPRep_unit__0__unit__1___Ab__up_0_prereq.h>

#include <./eri2_aB_WP__0__S__1___TwoPRep_unit__0__unit__1___Ab__up_0.h>

#include <./eri2_aB_WP__0__S__1___TwoPRep_unit__0__unit__1___Ab__up_0_prereq.h>

#include <./eri2_aB_WP__0__WP__1___TwoPRep_unit__0__unit__1___Ab__up_0.h>

#include <./eri2_aB_WP__0__WP__1___TwoPRep_unit__0__unit__1___Ab__up_0_prereq.h>

#include <./eri2_aB_WP__0__WD__1___TwoPRep_unit__0__unit__1___Ab__up_0.h>

#include <./eri2_aB_WP__0__WD__1___TwoPRep_unit__0__unit__1___Ab__up_0_prereq.h>

#include <./eri2_aB_WD__0__S__1___TwoPRep_unit__0__unit__1___Ab__up_0.h>

#include <./eri2_aB_WD__0__S__1___TwoPRep_unit__0__unit__1___Ab__up_0_prereq.h>

#include <./eri2_aB_WD__0__WP__1___TwoPRep_unit__0__unit__1___Ab__up_0.h>

#include <./eri2_aB_WD__0__WP__1___TwoPRep_unit__0__unit__1___Ab__up_0_prereq.h>

#include <./eri2_aB_WD__0__WD__1___TwoPRep_unit__0__unit__1___Ab__up_0.h>

#include <./eri2_aB_WD__0__WD__1___TwoPRep_unit__0__unit__1___Ab__up_0_prereq.h>

#endif

