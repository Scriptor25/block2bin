#pragma once

#include <llvm/IR/IRBuilder.h>

namespace b2b::ir
{
    class Builder
    {
    public:
        Builder(llvm::LLVMContext &context, llvm::Module &module);

    private:
        llvm::LLVMContext &m_Context;
        llvm::Module &m_Module;

        llvm::IRBuilder<> m_Builder;
    };
}
