
#include <array>
#include <cstddef>
using namespace std;

#include "InstructionSet.h"

#define OP_NR 256 /*number of jvm instructions*/

byte_code byte_code_table[OP_NR] = {
                   [AALOAD]      = def_op(AALOAD, "aaload", 0),
                   [AASTORE]     = def_op(AASTORE, "aastore", 0), 
                   [ACONST_NULL] = def_op(ACONST_NULL, "aconst_null", 0), 
                   [ALOAD]       = def_op(ALOAD, "aload", 1), 
                   [ALOAD_0]     = def_op(ALOAD_0, "aload_0", 0),
                   [ALOAD_1]     = def_op(ALOAD_1, "aload_1", 0), 
                   [ALOAD_2]     = def_op(ALOAD_2, "aload_2", 0), 
                   [ALOAD_3]     = def_op(ALOAD_3, "aload_3", 0), 
                   [ANEWARRAY]   = def_op(ANEWARRAY, "anewarray", 2), 
                   [ARETURN]     = def_op(ARETURN, "areturn", 0), 
                   [ARRAYLENGTH] = def_op(ARRAYLENGTH, "arraylength", 0),
                   [ASTORE]      = def_op(ASTORE, "astore", 1), 
                   [ASTORE_0]    = def_op(ASTORE_0, "astore_0", 0), 
                   [ASTORE_1]    = def_op(ASTORE_1, "astore_1", 0), 
                   [ASTORE_2]    = def_op(ASTORE_2, "astore_2", 0), 
                   [ASTORE_3]    = def_op(ASTORE_3, "astore_3", 0), 
                   [ATHROW]      = def_op(ATHROW, "athrow", 0), 
                   [BALOAD]      = def_op(BALOAD, "baload", 0), 
                   [BASTORE]     = def_op(BASTORE, "bastore", 0), 
                   [BIPUSH]      = def_op(BIPUSH, "bipush", 1), 
                   [BREAKPOINT]  = def_op(BREAKPOINT, "breakpoint", 0), 
                   [CALOAD]      = def_op(CALOAD, "caload", 0), 
                   [CASTORE]     = def_op(CASTORE, "castore", 0), 
                   [DUP]         = def_op(DUP, "dup", 0), 
                   [DUP_X1]      = def_op(DUP_X1, "dup_x1", 0), 
                   [DUP_X2]      = def_op(DUP_X2, "dup_x2", 0), 
                   [DUP2]        = def_op(DUP2, "dup2", 0), 
                   [CHECKCAST]   = def_op(CHECKCAST, "checkcast", 2), 
                   [GETFIELD]    = def_op(GETFIELD, "getfield", 2), 
                   [GETSTATIC]   = def_op(GETSTATIC, "getstatic", 2), 
                   [GOTO]        = def_op(GOTO, "goto", 2), 
                   [GOTO_W]      = def_op(GOTO_W, "goto_w", 4), 
                   [I2B]         = def_op(I2B, "i2b", 0), 
                   [I2C]         = def_op(I2C, "i2c", 0), 
                   [I2D]         = def_op(I2D, "i2d", 0), 
                   [I2F]         = def_op(I2F, "i2f", 0), 
                   [I2L]         = def_op(I2L, "i2l", 0), 
                   [I2S]         = def_op(I2S, "i2s", 0), 
                   [IADD]        = def_op(IADD, "iadd", 0), 
                   [IALOAD]      = def_op(IALOAD, "iaload", 0), 
                   [IAND]        = def_op(IAND, "iand", 0), 
                   [IASTORE]     = def_op(IASTORE, "iastore", 0), 
                   [ICONST_M1]   = def_op(ICONST_M1, "iconst_m1", 0), 
                   [ICONST_0]    = def_op(ICONST_0, "iconst_0", 0), 
                   [ICONST_1]    = def_op(ICONST_1, "iconst_1", 0), 
                   [ICONST_2]    = def_op(ICONST_2, "iconst_2", 0), 
                   [ICONST_3]    = def_op(ICONST_3, "iconst_3", 0), 
                   [ICONST_4]    = def_op(ICONST_4, "iconst_4", 0), 
                   [ICONST_5]    = def_op(ICONST_5, "iconst_5", 0), 
                   [IDIV]        = def_op(IDIV, "idiv", 0), 
                   [IF_ACMPEQ]   = def_op(IF_ACMPEQ, "if_acmpeq", 2), 
                   [IF_ACMPNE]   = def_op(IF_ACMPNE, "if_acmpne", 2), 
                   [IF_ICMPEQ]   = def_op(IF_ICMPEQ, "if_icmpeq", 2), 
                   [IF_ICMPGE]   = def_op(IF_ICMPGE, "if_icmpge", 2), 
                   [IF_ICMPGT]   = def_op(IF_ICMPGT, "if_icmpgt", 2), 
                   [IF_ICMPLE]   = def_op(IF_ICMPLE, "if_icmple", 2), 
                   [IF_ICMPLT]   = def_op(IF_ICMPLT, "if_icmplt", 2), 
                   [IF_ICMPNE]   = def_op(IF_ICMPNE, "if_icmpne", 2), 
                   [IFEQ]        = def_op(IFEQ, "ifeq", 2), 
                   [IFGE]        = def_op(IFGE, "ifge", 2), 
                   [IFGT]        = def_op(IFGT, "ifgt", 2), 
                   [IFLE]        = def_op(IFLE, "ifle", 2), 
                   [IFLT]        = def_op(IFLT, "iflt", 2), 
                   [IFNE]        = def_op(IFNE, "ifne", 2), 
                   [IFNONNULL]   = def_op(IFNONNULL, "ifnonnull", 2), 
                   [IFNULL]      = def_op(IFNULL, "ifnull", 2), 
                   [IINC]        = def_op(IINC, "iinc", 2), 
                   [ILOAD]       = def_op(ILOAD, "iload", 1), 
                   [ILOAD_0]     = def_op(ILOAD_0, "iload_0", 0), 
                   [ILOAD_1]     = def_op(ILOAD_1, "iload_1", 0), 
                   [ILOAD_2]     = def_op(ILOAD_2, "iload_2", 0), 
                   [ILOAD_3]     = def_op(ILOAD_3, "iload_3", 0), 
                   [IMPDEP1]     = def_op(IMPDEP1, "impdep1", 0), 
                   [IMPDEP2]     = def_op(IMPDEP2, "impdep2", 0), 
                   [IMUL]        = def_op(IMUL, "imul", 0), 
                   [INEG]        = def_op(INEG, "ineg", 0), 
                   [INSTANCEOF]      = def_op(INSTANCEOF, "instanceof", 2), 
                   [INVOKEDYNAMIC]   = def_op(INVOKEDYNAMIC  , "invokedynamic", 4), 
                   [INVOKEINTERFACE] = def_op(INVOKEINTERFACE, "invokeinterface", 4), 
                   [INVOKESPECIAL]   = def_op(INVOKESPECIAL, "invokespecial", 2), 
                   [INVOKESTATIC]    = def_op(INVOKESTATIC, "invokestatic", 2), 
                   [INVOKEVIRTUAL]   = def_op(INVOKEVIRTUAL, "invokevirtual", 2), 
                   [IOR]      = def_op(IOR, "ior", 0), 
                   [IREM]     = def_op(IREM, "irem", 0), 
                   [IRETURN]  = def_op(IRETURN, "ireturn", 0), 
                   [ISHL]     = def_op(ISHL, "ishl", 0), 
                   [ISHR]     = def_op(ISHR, "ishr", 0), 
                   [ISTORE]   = def_op(ISTORE, "istore", 1), 
                   [ISTORE_0] = def_op(ISTORE_0, "istore_0", 0), 
                   [ISTORE_1] = def_op(ISTORE_1, "istore_1", 0), 
                   [ISTORE_2] = def_op(ISTORE_2, "istore_2", 0), 
                   [ISTORE_3] = def_op(ISTORE_3, "istore_3", 0), 
                   [ISUB]     = def_op(ISUB, "isub", 0), 
                   [IUSHR]    = def_op(IUSHR, "iushr", 0), 
                   [IXOR]     = def_op(IXOR, "ixor", 0), 
                   [LDC]      = def_op(LDC, "ldc", 1), 
                   [JSR]      = def_op(JSR, "jsr", 2),
                   [JSR_W]    = def_op(JSR_W, "jsr_w", 4), 
                   [L2D]     = def_op(L2D, "l2d", 0), 
                   [L2F]     = def_op(L2F, "l2f", 0), 
                   [L2I]     = def_op(L2I, "l2i", 0), 
                   [MONITORENTER]       = def_op(MONITORENTER, "monitorenter", 0), 
                   [MONITOREXIT]        = def_op(MONITOREXIT, "monitorexit", 0), 
                   [MULTIANEWARRAY]     = def_op(MULTIANEWARRAY, "multianewarray", 3), 
                   [NEW]       = def_op(NEW, "new", 2), 
                   [NEWARRAY]  = def_op(NEWARRAY, "newarray", 1), 
                   [NOP]       = def_op(NOP, "nop", 0), 
                   [POP]       = def_op(POP, "pop", 0), 
                   [POP2]      = def_op(POP2, "pop2", 0), 
                   [PUTFIELD]  = def_op(PUTFIELD, "putfield", 2), 
                   [PUTSTATIC] = def_op(PUTSTATIC, "putstatic", 2), 
                   [RET]       = def_op(RET, "ret", 1), 
                   [RETURN]    = def_op(RETURN, "return", 0), 
                   [SALOAD]    = def_op(SALOAD, "saload", 0), 
                   [SASTORE]   = def_op(SASTORE, "sastore", 0), 
                   [SIPUSH]    = def_op(SIPUSH, "sipush", 2), 
                   [SWAP]      = def_op(SWAP, "swap", 0), 
                   /*else {0, "unknown", 0},*/
                   };
InstructionSet* InstructionSet::_instance = 0;

InstructionSet* 
InstructionSet::instance()
{
  if (!_instance)
    _instance = new InstructionSet();
  return _instance;
}

string 
InstructionSet::get_mnemonic (int op_code)
{
  return byte_code_table[op_code].mnemonic;
}

int 
InstructionSet::get_operand_size (int op_code)
{
  return byte_code_table[op_code].operand_size;
}
	
bool 
InstructionSet::is_imm_oprand (int op_code)
{
  switch(op_code) {
  case BIPUSH: case SIPUSH:
  default: return true;
  }
  return false; 
}

InstructionSet::InstructionSet ()
{
  int i;
  for (i=0; i<256; i++)
    if (byte_code_table[i].op_code == 0)
      byte_code_table[i] = {0, "unknown", 0};
};








    