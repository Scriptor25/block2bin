#include <b2b/ir/builder.hpp>

b2b::ir::Builder::Builder(llvm::LLVMContext &context, llvm::Module &module)
    : m_Context(context),
      m_Module(module),
      m_Builder(context)
{
}
