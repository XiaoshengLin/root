// Author: Stefan Wunsch, Enric Tejedor CERN  06/2018
// Original PyROOT code by Wim Lavrijsen, LBL

/*************************************************************************
 * Copyright (C) 1995-2018, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

#include "CPyCppyy.h"
#include "PyROOTPythonize.h"
#include "CPPInstance.h"
#include "Utility.h"
#include "TInterpreter.h"
#include "TInterpreterValue.h"

using namespace CPyCppyy;

std::string GetCppName(const CPPInstance *self)
{
   return Cppyy::GetScopedFinalName(self->ObjectIsA());
}

PyObject *ClingPrintValue(const CPPInstance *self, PyObject * /* args */)
{
   const std::string className = GetCppName(self);
   auto printResult = gInterpreter->ToString(className.c_str(), self->GetObject());
   if (printResult.find("@0x") == 0) {
      // Fall back to __repr__ if we just get an address from cling
      auto method = PyObject_GetAttrString((PyObject*)self, "__repr__");
      auto res = PyObject_CallObject(method, nullptr);
      Py_DECREF(method);
      return res;
   } else {
      return CPyCppyy_PyUnicode_FromString(printResult.c_str());
   }
}

////////////////////////////////////////////////////////////////////////////
/// \brief Add pretty printing pythonization
/// \param[in] self Always null, since this is a module function.
/// \param[in] args Pointer to a Python tuple object containing the arguments
/// received from Python.
///
/// This function adds the following pythonizations to print the object more
/// user-friendly than cppyy by using the output of cling::printValue as the
/// return value of the special method __str__.
PyObject *PyROOT::AddPrettyPrintingPyz(PyObject * /* self */, PyObject *args)
{
   PyObject *pyclass = PyTuple_GetItem(args, 0);
   Utility::AddToClass(pyclass, "__str__", (PyCFunction)ClingPrintValue);
   Py_RETURN_NONE;
}
