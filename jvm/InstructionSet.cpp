
#include <array>
#include <cstddef>
using namespace std;

#include "InstructionSet.h"


InstructionSet* InstructionSet::_instance = 0;

InstructionSet* 
InstructionSet::Instance()
{
  if (!_instance)
    _instance = new InstructionSet();
  return _instance;
}

string 
InstructionSet::getMnemonic (int opCode)
{
  return byteCodeTable[opCode].mnemonic;
}

int 
InstructionSet::getOperandSize (int opCode)
{
  return byteCodeTable[opCode].operandSize;
}
	
bool 
InstructionSet::isImmOprand (int opCode)
{
  size_t i;
  array<int,2> immOpTable {BIPUSH, SIPUSH};
  for (i=0; i<immOpTable.size(); i++)
    if (opCode == immOpTable[i])
      return true;
  return false;
}

InstructionSet::InstructionSet ()
{
  int i;
  for (i=0; i<256; i++)
    byteCodeTable[i] = {0, "unknown", 0};
  
  byteCodeTable[AALOAD]      = def(AALOAD, "aaload", 0); 
  byteCodeTable[AASTORE]     = def(AASTORE, "aastore", 0); 
  byteCodeTable[ACONST_NULL] = def(ACONST_NULL, "aconst_null", 0); 
  byteCodeTable[ALOAD]       = def(ALOAD, "aload", 1); 
  byteCodeTable[ALOAD_0]     = def(ALOAD_0, "aload_0", 0);
  byteCodeTable[ALOAD_1]     = def(ALOAD_1, "aload_1", 0); 
  byteCodeTable[ALOAD_2]     = def(ALOAD_2, "aload_2", 0); 
  byteCodeTable[ALOAD_3]     = def(ALOAD_3, "aload_3", 0); 
  byteCodeTable[ANEWARRAY]   = def(ANEWARRAY, "anewarray", 2); 
  byteCodeTable[ARETURN]     = def(ARETURN, "areturn", 0); 
  byteCodeTable[ARRAYLENGTH] = def(ARRAYLENGTH, "arraylength", 0);
  byteCodeTable[ASTORE]      = def(ASTORE, "astore", 1); 
  byteCodeTable[ASTORE_0]    = def(ASTORE_0, "astore_0", 0); 
  byteCodeTable[ASTORE_1]    = def(ASTORE_1, "astore_1", 0); 
  byteCodeTable[ASTORE_2]    = def(ASTORE_2, "astore_2", 0); 
  byteCodeTable[ASTORE_3]    = def(ASTORE_3, "astore_3", 0); 
  byteCodeTable[ATHROW]      = def(ATHROW, "athrow", 0); 
  byteCodeTable[BALOAD]      = def(BALOAD, "baload", 0); 
  byteCodeTable[BASTORE]     = def(BASTORE, "bastore", 0); 
  byteCodeTable[BIPUSH]      = def(BIPUSH, "bipush", 1); 
  byteCodeTable[BREAKPOINT]  = def(BREAKPOINT, "breakpoint", 0); 
  byteCodeTable[CALOAD]      = def(CALOAD, "caload", 0); 
  byteCodeTable[CASTORE]     = def(CASTORE, "castore", 0); 
  byteCodeTable[DUP]         = def(DUP, "dup", 0); 
  byteCodeTable[DUP_X1]      = def(DUP_X1, "dup_x1", 0); 
  byteCodeTable[DUP_X2]      = def(DUP_X2, "dup_x2", 0); 
  byteCodeTable[DUP2]        = def(DUP2, "dup2", 0); 
  byteCodeTable[CHECKCAST]   = def(CHECKCAST, "checkcast", 2); 
  byteCodeTable[GETFIELD]    = def(GETFIELD, "getfield", 2); 
  byteCodeTable[GETSTATIC]   = def(GETSTATIC, "getstatic", 2); 
  byteCodeTable[GOTO]        = def(GOTO, "goto", 2); 
  byteCodeTable[GOTO_W]      = def(GOTO_W, "goto_w", 4); 
  byteCodeTable[I2B]         = def(I2B, "i2b", 0); 
  byteCodeTable[I2C]         = def(I2C, "i2c", 0); 
  byteCodeTable[I2D]         = def(I2D, "i2d", 0); 
  byteCodeTable[I2F]         = def(I2F, "i2f", 0); 
  byteCodeTable[I2L]         = def(I2L, "i2l", 0); 
  byteCodeTable[I2S]         = def(I2S, "i2s", 0); 
  byteCodeTable[IADD]        = def(IADD, "iadd", 0); 
  byteCodeTable[IALOAD]      = def(IALOAD, "iaload", 0); 
  byteCodeTable[IAND]        = def(IAND, "iand", 0); 
  byteCodeTable[IASTORE]     = def(IASTORE, "iastore", 0); 
  byteCodeTable[ICONST_M1]   = def(ICONST_M1, "iconst_m1", 0); 
  byteCodeTable[ICONST_0]    = def(ICONST_0, "iconst_0", 0); 
  byteCodeTable[ICONST_1]    = def(ICONST_1, "iconst_1", 0); 
  byteCodeTable[ICONST_2]    = def(ICONST_2, "iconst_2", 0); 
  byteCodeTable[ICONST_3]    = def(ICONST_3, "iconst_3", 0); 
  byteCodeTable[ICONST_4]    = def(ICONST_4, "iconst_4", 0); 
  byteCodeTable[ICONST_5]    = def(ICONST_5, "iconst_5", 0); 
  byteCodeTable[IDIV]        = def(IDIV, "idiv", 0); 
  byteCodeTable[IF_ACMPEQ]   = def(IF_ACMPEQ, "if_acmpeq", 2); 
  byteCodeTable[IF_ACMPNE]   = def(IF_ACMPNE, "if_acmpne", 2); 
  byteCodeTable[IF_ICMPEQ]   = def(IF_ICMPEQ, "if_icmpeq", 2); 
  byteCodeTable[IF_ICMPGE]   = def(IF_ICMPGE, "if_icmpge", 2); 
  byteCodeTable[IF_ICMPGT]   = def(IF_ICMPGT, "if_icmpgt", 2); 
  byteCodeTable[IF_ICMPLE]   = def(IF_ICMPLE, "if_icmple", 2); 
  byteCodeTable[IF_ICMPLT]   = def(IF_ICMPLT, "if_icmplt", 2); 
  byteCodeTable[IF_ICMPNE]   = def(IF_ICMPNE, "if_icmpne", 2); 
  byteCodeTable[IFEQ]        = def(IFEQ, "ifeq", 2); 
  byteCodeTable[IFGE]        = def(IFGE, "ifge", 2); 
  byteCodeTable[IFGT]        = def(IFGT, "ifgt", 2); 
  byteCodeTable[IFLE]        = def(IFLE, "ifle", 2); 
  byteCodeTable[IFLT]        = def(IFLT, "iflt", 2); 
  byteCodeTable[IFNE]        = def(IFNE, "ifne", 2); 
  byteCodeTable[IFNONNULL]   = def(IFNONNULL, "ifnonnull", 2); 
  byteCodeTable[IFNULL]      = def(IFNULL, "ifnull", 2); 
  byteCodeTable[IINC]        = def(IINC, "iinc", 2); 
  byteCodeTable[ILOAD]       = def(ILOAD, "iload", 1); 
  byteCodeTable[ILOAD_0]     = def(ILOAD_0, "iload_0", 0); 
  byteCodeTable[ILOAD_1]     = def(ILOAD_1, "iload_1", 0); 
  byteCodeTable[ILOAD_2]     = def(ILOAD_2, "iload_2", 0); 
  byteCodeTable[ILOAD_3]     = def(ILOAD_3, "iload_3", 0); 
  byteCodeTable[IMPDEP1]     = def(IMPDEP1, "impdep1", 0); 
  byteCodeTable[IMPDEP2]     = def(IMPDEP2, "impdep2", 0); 
  byteCodeTable[IMUL]        = def(IMUL, "imul", 0); 
  byteCodeTable[INEG]        = def(INEG, "ineg", 0); 
  byteCodeTable[INSTANCEOF]      = def(INSTANCEOF, "instanceof", 2); 
  byteCodeTable[INVOKEDYNAMIC]   = def(INVOKEDYNAMIC  , "invokedynamic", 4); 
  byteCodeTable[INVOKEINTERFACE] = def(INVOKEINTERFACE, "invokeinterface", 4); 
  byteCodeTable[INVOKESPECIAL]   = def(INVOKESPECIAL, "invokespecial", 2); 
  byteCodeTable[INVOKESTATIC]    = def(INVOKESTATIC, "invokestatic", 2); 
  byteCodeTable[INVOKEVIRTUAL]   = def(INVOKEVIRTUAL, "invokevirtual", 2); 
  byteCodeTable[IOR]      = def(IOR, "ior", 0); 
  byteCodeTable[IREM]     = def(IREM, "irem", 0); 
  byteCodeTable[IRETURN]  = def(IRETURN, "ireturn", 0); 
  byteCodeTable[ISHL]     = def(ISHL, "ishl", 0); 
  byteCodeTable[ISHR]     = def(ISHR, "ishr", 0); 
  byteCodeTable[ISTORE]   = def(ISTORE, "istore", 1); 
  byteCodeTable[ISTORE_0] = def(ISTORE_0, "istore_0", 0); 
  byteCodeTable[ISTORE_1] = def(ISTORE_1, "istore_1", 0); 
  byteCodeTable[ISTORE_2] = def(ISTORE_2, "istore_2", 0); 
  byteCodeTable[ISTORE_3] = def(ISTORE_3, "istore_3", 0); 
  byteCodeTable[ISUB]     = def(ISUB, "isub", 0); 
  byteCodeTable[IUSHR]    = def(IUSHR, "iushr", 0); 
  byteCodeTable[IXOR]     = def(IXOR, "ixor", 0); 
  byteCodeTable[LDC]      = def(LDC, "ldc", 1); 
  byteCodeTable[JSR]      = def(JSR, "jsr", 2); 
  byteCodeTable[JSR_W]    = def(JSR_W, "jsr_w", 4); 
  byteCodeTable[L2D]     = def(L2D, "l2d", 0); 
  byteCodeTable[L2F]     = def(L2F, "l2f", 0); 
  byteCodeTable[L2I]     = def(L2I, "l2i", 0); 
  byteCodeTable[MONITORENTER]       = def(MONITORENTER, "monitorenter", 0); 
  byteCodeTable[MONITOREXIT]        = def(MONITOREXIT, "monitorexit", 0); 
  byteCodeTable[MULTIANEWARRAY]     = def(MULTIANEWARRAY, "multianewarray", 3); 
  byteCodeTable[NEW]       = def(NEW, "new", 2); 
  byteCodeTable[NEWARRAY]  = def(NEWARRAY, "newarray", 1); 
  byteCodeTable[NOP]       = def(NOP, "nop", 0); 
  byteCodeTable[POP]       = def(POP, "pop", 0); 
  byteCodeTable[POP2]      = def(POP2, "pop2", 0); 
  byteCodeTable[PUTFIELD]  = def(PUTFIELD, "putfield", 2); 
  byteCodeTable[PUTSTATIC] = def(PUTSTATIC, "putstatic", 2); 
  byteCodeTable[RET]       = def(RET, "ret", 1); 
  byteCodeTable[RETURN]    = def(RETURN, "return", 0); 
  byteCodeTable[SALOAD]    = def(SALOAD, "saload", 0); 
  byteCodeTable[SASTORE]   = def(SASTORE, "sastore", 0); 
  byteCodeTable[SIPUSH]    = def(SIPUSH, "sipush", 2); 
  byteCodeTable[SWAP]      = def(SWAP, "swap", 0); 
};

    