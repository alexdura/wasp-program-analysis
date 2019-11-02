#ifndef CAST_CHECK_H_
#define CAST_CHECK_H_

#include <map>
#include <memory>
#include <phasar/PhasarLLVM/Plugins/Interfaces/IfdsIde/IFDSTabulationProblemPlugin.h>
#include <set>
#include <vector>

class CastCheck : public psr::IFDSTabulationProblemPlugin {
std::set<const llvm::Value*> TaintedValues;
std::map<const llvm::Instruction*, std::set<const llvm::Value*>> LeakMap;

public:
// Constructor
CastCheck(psr::LLVMBasedICFG &I, std::vector<std::string> EntryPoints);
// Destructor
~CastCheck() = default;

std::shared_ptr<psr::FlowFunction<const llvm::Value *>>
getNormalFlowFunction(const llvm::Instruction *curr,
		const llvm::Instruction *succ) override;

std::shared_ptr<psr::FlowFunction<const llvm::Value *>>
getCallFlowFunction(const llvm::Instruction *callStmt,
	    const llvm::Function *destMthd) override;

std::shared_ptr<psr::FlowFunction<const llvm::Value *>>
getRetFlowFunction(const llvm::Instruction *callSite,
	    const llvm::Function *calleeMthd,
	    const llvm::Instruction *exitStmt,
	    const llvm::Instruction *retSite) override;

std::shared_ptr<psr::FlowFunction<const llvm::Value *>>
getCallToRetFlowFunction(const llvm::Instruction *callSite,
		const llvm::Instruction *retSite,
		std::set<const llvm::Function *> callees) override;

std::shared_ptr<psr::FlowFunction<const llvm::Value *>>
getSummaryFlowFunction(const llvm::Instruction *callStmt,
		const llvm::Function *destMthd) override;

std::map<const llvm::Instruction *, std::set<const llvm::Value *>>
initialSeeds() override;

void printIFDSReport(std::ostream &os,
		psr::SolverResults<const llvm::Instruction*,
		const llvm::Value*, psr::BinaryDomain> &SR) override;
};

extern "C" std::unique_ptr<psr::IFDSTabulationProblemPlugin>
makeCastCheck(psr::LLVMBasedICFG &I, std::vector<std::string> EntryPoints);

#endif
