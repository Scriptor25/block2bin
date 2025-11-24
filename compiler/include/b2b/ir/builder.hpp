#pragma once

#include <b2b/tree_fwd.hpp>
#include <llvm/IR/IRBuilder.h>

namespace b2b::ir
{
    class Builder
    {
    public:
        Builder(llvm::LLVMContext &context, llvm::Module &module);

        llvm::Value *CreateAlloca(llvm::Type *type);
        llvm::Value *CreateInstancePointer(llvm::Type *type);

        llvm::Type *CreateType(const TargetTypeT &target_type);
        llvm::Value *CreateInstance(const TargetTypeT &target_type);

    private:
        llvm::LLVMContext &m_Context;
        llvm::Module &m_Module;

        llvm::IRBuilder<> m_Builder;
    };
}
