#include "MyIFDSProblem.h"
#include <iostream>
#include <phasar/PhasarLLVM/ControlFlow/LLVMBasedICFG.h>
#include <phasar/PhasarLLVM/IfdsIde/FlowFunctions/Gen.h>
#include <phasar/PhasarLLVM/IfdsIde/FlowFunctions/Identity.h>
#include <phasar/PhasarLLVM/IfdsIde/FlowFunctions/KillAll.h>
#include "llvm/Support/Debug.h"

using namespace std;
using namespace psr;
using namespace llvm;

// Factory function that is used to create an instance by the Phasar framework.
unique_ptr<IFDSTabulationProblemPlugin>
makeMyIFDSProblem(LLVMBasedICFG &I, vector<string> EntryPoints) {
  return unique_ptr<IFDSTabulationProblemPlugin>(
      new MyIFDSProblem(I, EntryPoints));
}

// Is executed on plug-in load and has to register this plug-in to Phasar.
__attribute__((constructor)) void init() {
  cout << "init - MyIFDSProblem\n";
  IFDSTabulationProblemPluginFactory["ifds_testplugin"] = &makeMyIFDSProblem;
}

// Is executed on unload, can be used to unregister the plug-in.
__attribute__((destructor)) void fini() { cout << "fini - MyIFDSProblem\n"; }

// Default constructor
MyIFDSProblem::MyIFDSProblem(LLVMBasedICFG &I, vector<string> EntryPoints)
  : IFDSTabulationProblemPlugin(I, EntryPoints), TaintedValues() {}


///////////////////////////////////////////////////////
// The flow function for intra-procedural statements //
// (Allocations, for instance)			     //
///////////////////////////////////////////////////////
shared_ptr<FlowFunction<const llvm::Value *>>
MyIFDSProblem::getNormalFlowFunction(const llvm::Instruction *curr,
                                     const llvm::Instruction *succ) {
  cout << "MyIFDSProblem::getNormalFlowFunction()\n";
  // TODO: Must be implemented to propagate tainted values through the program.
  // Tainted values may spread through loads and stores (llvm::LoadInst and
  // llvm::StoreInst). Important memberfunctions are getPointerOperand() and
  // getPointerOperand()/ getValueOperand() respectively.
  dbgs() << *curr <<  "->" <<  *succ << "\n";

  // We match with stores
  if (const StoreInst *store = dyn_cast<StoreInst>(curr)) {
    // You create a struct for returning your function
    struct StoreInfo : public FlowFunction<const Value*> {
      const StoreInst *store; // Storing the pointer because you can't capture it directly
      // Constructor
      StoreInfo(const StoreInst *store) : store(store) {}
      // Computing where the value of source will go
      std::set<const Value*> computeTargets(const Value *source) override {
	// store v [a]
        if (store->getValueOperand() == source)
	  // We're looking at v
	  // The value of v will flow into [a]
	  // and itself, v
          return {store->getPointerOperand(), source};
        else if (store->getPointerOperand() == source)
	  // We're looking at [a] instead.
	  // It will be erased (replaced by v)
          return {}; // So we return an empty set (cutting the link)
	// Otherwise, nothing changes.
        else return {source};
      }
    };
    // Printing stuff for debugging
    dbgs() << "Return store info\n";
    return make_shared<StoreInfo>(store);
  } else if (const LoadInst *load  = dyn_cast<LoadInst>(curr)) {
    // Here we have a load, we need to define a relation
    // The relation maps variables to sets of variables (targets)
    // To do that, you return a struct with the method
    // called computeTargets
    // Let's say the load is
    // v = load [a] 
    struct LoadInfo : public FlowFunction<const Value*> {
      // We will want to save the load we're looking at
      // Because we can't capture it directly
      const LoadInst *load;
      LoadInfo(const LoadInst *load) : load(load) {}
      // This is the important bit
      std::set<const Value*> computeTargets(const Value *source) override {
	// If the source is the address we're loading from
	// source = a
        if (load->getPointerOperand() == source)
	  // source flows into itself (a = a)
	  // and the register we're defining (v).
          return {source, load};
        else if (load == source) // the source is v
	  // v will be erased (replaced by a)
          return {};
	// Otherwise, we don't change anything
        else return {source};
      }
    };
    dbgs() << "Return load info\n";
    return make_shared<LoadInfo>(load);
  }
  // We match with anything else.
  return Identity<const llvm::Value *>::getInstance();
}

//////////////////////////////////////////////////
// The flow function for mapping the parameters //
// To the formal parameters of the function     //
//////////////////////////////////////////////////
shared_ptr<FlowFunction<const llvm::Value *>>
MyIFDSProblem::getCallFlowFunction(const llvm::Instruction *callStmt,
                                   const llvm::Function *destMthd) {
  cout << "MyIFDSProblem::getCallFlowFunction()\n";
  // TODO: Must be modeled to perform parameter passing:
  // actuals at caller-side must be mapped into formals at callee-side.
  // LLVM distinguishes between a ordinary function call and a function call
  // that might throw (llvm::CallInst, llvm::InvokeInst). To be able to easily
  // inspect both, a variable of type llvm::ImmutableCallSite may be
  // constructed using 'callStmt'.
  // Important: getCallFlowFunction() can also be used in combination with
  // getCallToRetFlowFunction() in order to model a function's effect without
  // actually following call targets. This must be used to model sources and
  // sinks of the taint analysis. It works by killing all flow facts at the
  // call-site and generating the desired facts within the
  // getCallToRetFlowFunction.
  return Identity<const llvm::Value *>::getInstance();
}

///////////////////////////////////////////////
// The function for mapping the return value //
// back into the scope			     //
///////////////////////////////////////////////
shared_ptr<FlowFunction<const llvm::Value *>> MyIFDSProblem::getRetFlowFunction(
    const llvm::Instruction *callSite, const llvm::Function *calleeMthd,
    const llvm::Instruction *exitStmt, const llvm::Instruction *retSite) {
  cout << "MyIFDSProblem::getRetFlowFunction()\n";
  // TODO: Must be modeled to map the return value back into the caller's
  // context. When dealing with pointer parameters one must also map the
  // formals at callee-side back into the actuals at caller-side. All other
  // facts that do not influence the caller must be killed.
  // 'callSite' can be handled by using llvm::ImmutableCallSite, 'exitStmt' is
  // the function's return instruction - llvm::ReturnInst may be used.
  // The 'retSite' is - in case of LLVM - the call-site and it is possible
  // to wrap it into an llvm::ImmutableCallSite.
  dbgs() << *callSite->getParent()->getParent();
  dbgs() << "CallSite: " << *callSite << "\n"
         << "RetSite: " << *retSite << "\n";

  if (calleeMthd->getName().equals("taint")) {
    dbgs() << "Matched taint function\n";
    return std::make_shared<Gen<const llvm::Value*>>(retSite, zeroValue());
  }

  return Identity<const llvm::Value *>::getInstance();
}

/////////////////////////////////////////////////////////////////////
// Modeling flow through a call site. Apparently, this is often an //
// identity flow function					   //
/////////////////////////////////////////////////////////////////////
shared_ptr<FlowFunction<const llvm::Value *>>
MyIFDSProblem::getCallToRetFlowFunction(const llvm::Instruction *callSite,
                                        const llvm::Instruction *retSite,
                                        set<const llvm::Function *> callees) {
  cout << "MyIFDSProblem::getCallToRetFlowFunction()\n";
  // TODO: Use in combination with getCallFlowFunction to model the effects of
  // source and sink functions. It most analyses flow facts can be passed as
  // identity.
  return Identity<const llvm::Value *>::getInstance();
}

// May be used to model function calls to libc or llvm.intrinsic functions
// for which no implementation is accessible. If nullptr is returned it applies
// identity on all flow facts that are present.
shared_ptr<FlowFunction<const llvm::Value *>>
MyIFDSProblem::getSummaryFlowFunction(const llvm::Instruction *callStmt,
                                      const llvm::Function *destMthd) {
  cout << "MyIFDSProblem::getSummaryFlowFunction()\n";
  return nullptr;
}

// Return(s) set(s) of flow fact(s) that hold(s) initially at a corresponding
// statement. The analysis will start at these instructions and propagate the
// flow facts according to the analysis description.
map<const llvm::Instruction *, set<const llvm::Value *>>
MyIFDSProblem::initialSeeds() {
  cout << "MyIFDSProblem::initialSeeds()\n";
  map<const llvm::Instruction *, set<const llvm::Value *>> SeedMap;
  for (auto &EntryPoint : EntryPoints) {
    SeedMap.insert(std::make_pair(&icfg.getMethod(EntryPoint)->front().front(),
                                  set<const llvm::Value *>({zeroValue()})));
  }
  return SeedMap;
}
