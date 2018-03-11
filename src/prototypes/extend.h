/*
   10/24/2016

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
   MA 02110-1301, USA.
*/

#ifndef EXTEND_H_
#define EXTEND_H_

#if WITH_PYTHON == 1

#if WITH_PYTHON2 == 1
#define PYFON_ZTR PyString_AsString
#else
#define PYFON_ZTR PyUnicode_AsUTF8
#endif /* WITH_PYTHON2 */

#define RET_PY_STR(x) (NULL != PYFON_ZTR(x) ? PYFON_ZTR(x) : "0")

void get_python(char *, char *);
#endif /* WITH_PYTHON */

#if WITH_ECL == 1
void get_ecl(char *, char *);
#endif /* WITH_ecl */

#if WITH_LUA == 1
void get_lua(char *, char *);
#endif /* WITH_LUA */

#if WITH_OCAML == 1
void get_ocaml(char *);
#endif /* WITH_OCAML */

#if WITH_PERL == 1
void get_perl(char *, char *);
#endif /* WITH_PERL */

#if WITH_R == 1
void get_r(char *, char *);
#endif /* WITH_R */

#if WITH_RUBY == 1
void get_ruby(char *, char *);
#endif /* WITH_RUBY */

#if WITH_RUST == 1
void get_rust(char *);
#endif /* WITH_RUST */

#if WITH_SLANG == 1
void get_slang(char *, char *);
#endif /* WITH_SLANG */

#if WITH_TCL == 1
void get_tcl(char *, char *);
#endif /* WITH_TCL */

#if WITH_ASSEMBLY == 1
extern char *uzer_func3(void);
void get_assembly(char *);
#endif


#if WITH_GO == 1
void get_go(char *);

#ifndef GO_CGO_PROLOGUE_H
#define GO_CGO_PROLOGUE_H

typedef signed char GoInt8;
typedef unsigned char GoUint8;
typedef short GoInt16;
typedef unsigned short GoUint16;
typedef int GoInt32;
typedef unsigned int GoUint32;
typedef long long GoInt64;
typedef unsigned long long GoUint64;
typedef GoInt64 GoInt;
typedef GoUint64 GoUint;
typedef __SIZE_TYPE__ GoUintptr;
typedef float GoFloat32;
typedef double GoFloat64;
typedef float _Complex GoComplex64;
typedef double _Complex GoComplex128;

/*
  static assertion to make sure the file is being used on architecture
  at least with matching size of GoInt.
*/
typedef char _check_for_64_bit_pointer_matching_GoInt[sizeof(void*)==64/8 ? 1:-1];

typedef struct { const char *p; GoInt n; } GoString;
typedef void *GoMap;
typedef void *GoChan;
typedef struct { void *t; void *v; } GoInterface;
typedef struct { void *data; GoInt len; GoInt cap; } GoSlice;

#endif /* GO_CGO_PROLOGUE_H */

/* End of boilerplate cgo prologue.  */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


extern char* uzer_func4();
extern void Gfree(char* p0);

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* WITH_GO */


#endif /* EXTEND_H_ */
