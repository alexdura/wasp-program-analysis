#include "CastCheck.h"
#include <iostream>
#include <iterator>
#include <phasar/PhasarLLVM/ControlFlow/LLVMBasedICFG.h>
#include <phasar/PhasarLLVM/IfdsIde/FlowFunctions/Gen.h>
#include <phasar/PhasarLLVM/IfdsIde/FlowFunctions/Identity.h>
#include <phasar/PhasarLLVM/IfdsIde/FlowFunctions/KillAll.h>
#include <phasar/PhasarLLVM/IfdsIde/FlowFunctions/LambdaFlow.h>

using namespace std;
using namespace psr; // Phasar
using namespace llvm;

// CONSTRUCTION, REGISTRATION, DESTRUCTION
// Factory function that is used to create an instance by the Phasar framework.
unique_ptr<IFDSTabulationProblemPlugin>
makeCastCheck(LLVMBasedICFG &I, vector<string> EntryPoints) {
    return unique_ptr<IFDSTabulationProblemPlugin>(
    new CastCheck(I, EntryPoints));
}

// Is executed on plug-in load and has to register this plug-in to Phasar.
__attribute__((constructor)) void init() {
   cout << "init - Cast check plugin\n";
   IFDSTabulationProblemPluginFactory["ifds_testplugin"] = &makeCastCheck;
}

// Is executed on unload, can be used to unregister the plug-in.
__attribute__((destructor)) void fini() { cout << "fini - Cast check plugin\n"; }

// Default constructor
CastCheck::CastCheck(LLVMBasedICFG &I, vector<string> EntryPoints)
   : IFDSTabulationProblemPlugin(I, EntryPoints), TaintedValues() {}
//
//
//
