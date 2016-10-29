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

#include "config.h" /* Auto-generated */

#if WITH_PYTHON == 1

#include <Python.h>
#include "include/headers.h"

#endif /* WITH_PYTHON */

#include "prototypes/python.h"

#if WITH_PYTHON == 1
/*
 * Huge thanks to:
 *  https://wiki.blender.org/index.php/Dev:2.5/Source/Python/API/Py3.1_Migration
*/
void
get_python(char *str1, char *str2) {
  PyObject *pName = NULL, *pModule = NULL;
  PyObject *pFunc = NULL, *pValue = NULL;

  FILL_STR_ARR(1, str1, "0");
  if (NULL == (char *)Py_GetPath()) {
    return;
  }

  Py_Initialize();

#if WITH_PYTHON2 == 1
  pName = PyString_FromString(str2);
#else
  pName = PyUnicode_DecodeFSDefault(str2);
#endif /* WITH_PYTHON2 */

  if (NULL == pName) {
    goto error;
  }

  pModule = PyImport_Import(pName);
  Py_DECREF(pName);
  if (NULL == pModule) {
    goto error;
  }

  pFunc = PyObject_GetAttrString(pModule, (char *)"uzer_func");
  if (NULL == pFunc || 0 == PyCallable_Check(pFunc)) {
    goto error;
  }

  pValue = PyObject_CallObject(pFunc, NULL);
  if (NULL != pValue) {
    FILL_STR_ARR(1, str1, RET_PY_STR(pValue));
  }

error:
  if (NULL != pValue) {
    Py_XDECREF(pValue);
  }
  if (NULL != pFunc) {
    Py_XDECREF(pFunc);
  }
  if (NULL != pModule) {
    Py_XDECREF(pModule);
  }

  Py_Finalize();
  return;
}
#else
char *py7h0n;
#endif /* WITH_PYTHON */
