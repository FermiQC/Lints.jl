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

#ifndef _libint2_libint2iface_h_
#define _libint2_libint2iface_h_

#ifdef __cplusplus
# include <cstddef>
#else
# include <stddef.h>
#endif
#ifdef __cplusplus
LIBINT_PRAGMA_CLANG(diagnostic push)
LIBINT_PRAGMA_CLANG(diagnostic ignored "-Wunused-variable")
LIBINT_PRAGMA_GCC(diagnostic push)
LIBINT_PRAGMA_GCC(diagnostic ignored "-Wunused-variable")
extern "C" {
#endif
extern void (*libint2_build_default[7][7][7][7])(const Libint_t*);
extern void (*libint2_build_overlap[7][7])(const Libint_t*);
extern void (*libint2_build_kinetic[7][7])(const Libint_t*);
extern void (*libint2_build_elecpot[7][7])(const Libint_t*);
extern void (*libint2_build_1emultipole[7][7])(const Libint_t*);
extern void (*libint2_build_2emultipole[7][7])(const Libint_t*);
extern void (*libint2_build_3emultipole[7][7])(const Libint_t*);
extern void (*libint2_build_sphemultipole[7][7])(const Libint_t*);
extern void (*libint2_build_eri[7][7][7][7])(const Libint_t*);
extern void (*libint2_build_3eri[7][7][7])(const Libint_t*);
extern void (*libint2_build_2eri[7][7])(const Libint_t*);
void libint2_static_init();
void libint2_static_cleanup();
void libint2_init_default(Libint_t* inteval, int max_am, void* buf);
size_t libint2_need_memory_default(int max_am);
void libint2_cleanup_default(Libint_t* inteval);
void libint2_init_overlap(Libint_t* inteval, int max_am, void* buf);
size_t libint2_need_memory_overlap(int max_am);
void libint2_cleanup_overlap(Libint_t* inteval);
void libint2_init_kinetic(Libint_t* inteval, int max_am, void* buf);
size_t libint2_need_memory_kinetic(int max_am);
void libint2_cleanup_kinetic(Libint_t* inteval);
void libint2_init_elecpot(Libint_t* inteval, int max_am, void* buf);
size_t libint2_need_memory_elecpot(int max_am);
void libint2_cleanup_elecpot(Libint_t* inteval);
void libint2_init_1emultipole(Libint_t* inteval, int max_am, void* buf);
size_t libint2_need_memory_1emultipole(int max_am);
void libint2_cleanup_1emultipole(Libint_t* inteval);
void libint2_init_2emultipole(Libint_t* inteval, int max_am, void* buf);
size_t libint2_need_memory_2emultipole(int max_am);
void libint2_cleanup_2emultipole(Libint_t* inteval);
void libint2_init_3emultipole(Libint_t* inteval, int max_am, void* buf);
size_t libint2_need_memory_3emultipole(int max_am);
void libint2_cleanup_3emultipole(Libint_t* inteval);
void libint2_init_sphemultipole(Libint_t* inteval, int max_am, void* buf);
size_t libint2_need_memory_sphemultipole(int max_am);
void libint2_cleanup_sphemultipole(Libint_t* inteval);
void libint2_init_eri(Libint_t* inteval, int max_am, void* buf);
size_t libint2_need_memory_eri(int max_am);
void libint2_cleanup_eri(Libint_t* inteval);
void libint2_init_3eri(Libint_t* inteval, int max_am, void* buf);
size_t libint2_need_memory_3eri(int max_am);
void libint2_cleanup_3eri(Libint_t* inteval);
void libint2_init_2eri(Libint_t* inteval, int max_am, void* buf);
size_t libint2_need_memory_2eri(int max_am);
void libint2_cleanup_2eri(Libint_t* inteval);
#ifdef __cplusplus
};
LIBINT_PRAGMA_CLANG(diagnostic pop)
LIBINT_PRAGMA_GCC(diagnostic pop)
#endif

/** Use LIBINT2_PREFIXED_NAME(fncname) to form properly prefixed function name from LIBINT2 API */
#define LIBINT2_PREFIXED_NAME(name) __libint2_prefixed_name__(LIBINT2_API_PREFIX,name)
#define __libint2_prefixed_name__(prefix,name) __prescanned_prefixed_name__(prefix,name)
#define __prescanned_prefixed_name__(prefix,name) prefix##name
/** Use LIBINT2_PREFIXED_NAME(fncname) to form properly prefixed function name from LIBINT2 API */
#define LIBINT2_DEFINED(taskname,symbol) __prescanned_libint2_defined__(taskname,symbol)
#define __prescanned_libint2_defined__(taskname,symbol) LIBINT2_DEFINED_##symbol

#endif

