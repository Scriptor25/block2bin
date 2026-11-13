#include <b2b/tree.hpp>
#include <b2b/ir/builder.hpp>

b2b::ir::Builder::Builder(llvm::LLVMContext &context, llvm::Module &module)
    : m_Context(context),
      m_Module(module),
      m_Builder(context)
{
}

llvm::Value *b2b::ir::Builder::CreateAlloca(llvm::Type *type)
{
    const auto block = m_Builder.GetInsertBlock();
    m_Builder.SetInsertPointPastAllocas(block->getParent());
    const auto pointer = m_Builder.CreateAlloca(type);
    m_Builder.SetInsertPoint(block);
    return pointer;
}

llvm::Value *b2b::ir::Builder::CreateInstancePointer(llvm::Type *type)
{
}

llvm::Type *b2b::ir::Builder::CreateType(const TargetTypeT &target_type)
{
    std::vector<llvm::Type *> elements;
    for (unsigned i = 0; i < target_type.Fields.size(); ++i)
    {
        // ptr to number, string or list
        elements.emplace_back(m_Builder.getPtrTy());
    }

    return llvm::StructType::create(m_Context, elements, target_type.Name);
}

llvm::Value *b2b::ir::Builder::CreateInstance(const TargetTypeT &target_type)
{
    const auto type = CreateType(target_type);
    const auto pointer = CreateInstancePointer(type);

    // llvm::Value *initial_value = llvm::Constant::getNullValue(type);
    // for (unsigned i = 0; i < target_type.Fields.size(); ++i)
    // {
    //     auto &field = target_type.Fields.at(i);
    //     auto field_pointer = CreateFieldPointer();
    //     auto field_value = field.InitialValue->Generate();
    //     initial_value = m_Builder.CreateInsertValue(initial_value, field_value, i);
    // }

    return pointer;
}
