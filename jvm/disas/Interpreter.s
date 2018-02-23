	.syntax unified
	.arch armv7-a
	.eabi_attribute 27, 3	@ Tag_ABI_HardFP_use
	.eabi_attribute 28, 1	@ Tag_ABI_VFP_args
	.fpu vfpv3-d16
	.eabi_attribute 20, 1	@ Tag_ABI_FP_denormal
	.eabi_attribute 21, 1	@ Tag_ABI_FP_exceptions
	.eabi_attribute 23, 3	@ Tag_ABI_FP_number_model
	.eabi_attribute 24, 1	@ Tag_ABI_align8_needed
	.eabi_attribute 25, 1	@ Tag_ABI_align8_preserved
	.eabi_attribute 26, 2	@ Tag_ABI_enum_size
	.eabi_attribute 30, 2	@ Tag_ABI_optimization_goals
	.eabi_attribute 34, 1	@ Tag_CPU_unaligned_access
	.eabi_attribute 18, 4	@ Tag_ABI_PCS_wchar_t
	.file	"Interpreter.cpp"
@ GNU C++ (Debian 4.9.2-10) version 4.9.2 (arm-linux-gnueabihf)
@	compiled by GNU C version 4.9.2, GMP version 6.0.0, MPFR version 3.1.2-p3, MPC version 1.0.2
@ GGC heuristics: --param ggc-min-expand=85 --param ggc-min-heapsize=103092
@ options passed:  -I ./include/ -imultilib .
@ -imultiarch arm-linux-gnueabihf -D_GNU_SOURCE Interpreter.cpp
@ -march=armv7-a -mfloat-abi=hard -mfpu=vfpv3-d16 -mthumb -mtls-dialect=gnu
@ -O2 -Wall -std=c++11 -fverbose-asm
@ options enabled:  -faggressive-loop-optimizations -fauto-inc-dec
@ -fbranch-count-reg -fcaller-saves -fcombine-stack-adjustments -fcommon
@ -fcompare-elim -fcprop-registers -fcrossjumping -fcse-follow-jumps
@ -fdefer-pop -fdelete-null-pointer-checks -fdevirtualize
@ -fdevirtualize-speculatively -fdwarf2-cfi-asm -fearly-inlining
@ -feliminate-unused-debug-types -fexceptions -fexpensive-optimizations
@ -fforward-propagate -ffunction-cse -fgcse -fgcse-lm -fgnu-runtime
@ -fgnu-unique -fguess-branch-probability -fhoist-adjacent-loads -fident
@ -fif-conversion -fif-conversion2 -findirect-inlining -finline
@ -finline-atomics -finline-functions-called-once -finline-small-functions
@ -fipa-cp -fipa-profile -fipa-pure-const -fipa-reference -fipa-sra
@ -fira-hoist-pressure -fira-share-save-slots -fira-share-spill-slots
@ -fisolate-erroneous-paths-dereference -fivopts -fkeep-static-consts
@ -fleading-underscore -fmath-errno -fmerge-constants -fmerge-debug-strings
@ -fmove-loop-invariants -fomit-frame-pointer -foptimize-sibling-calls
@ -foptimize-strlen -fpartial-inlining -fpeephole -fpeephole2
@ -fprefetch-loop-arrays -freg-struct-return -freorder-blocks
@ -freorder-functions -frerun-cse-after-loop
@ -fsched-critical-path-heuristic -fsched-dep-count-heuristic
@ -fsched-group-heuristic -fsched-interblock -fsched-last-insn-heuristic
@ -fsched-pressure -fsched-rank-heuristic -fsched-spec
@ -fsched-spec-insn-heuristic -fsched-stalled-insns-dep -fschedule-insns
@ -fschedule-insns2 -fsection-anchors -fshow-column -fshrink-wrap
@ -fsigned-zeros -fsplit-ivs-in-unroller -fsplit-wide-types
@ -fstrict-aliasing -fstrict-overflow -fstrict-volatile-bitfields
@ -fsync-libcalls -fthread-jumps -ftoplevel-reorder -ftrapping-math
@ -ftree-bit-ccp -ftree-builtin-call-dce -ftree-ccp -ftree-ch
@ -ftree-coalesce-vars -ftree-copy-prop -ftree-copyrename -ftree-cselim
@ -ftree-dce -ftree-dominator-opts -ftree-dse -ftree-forwprop -ftree-fre
@ -ftree-loop-if-convert -ftree-loop-im -ftree-loop-ivcanon
@ -ftree-loop-optimize -ftree-parallelize-loops= -ftree-phiprop -ftree-pre
@ -ftree-pta -ftree-reassoc -ftree-scev-cprop -ftree-sink -ftree-slsr
@ -ftree-sra -ftree-switch-conversion -ftree-tail-merge -ftree-ter
@ -ftree-vrp -funit-at-a-time -fverbose-asm -fzero-initialized-in-bss
@ -mglibc -mlittle-endian -mlra -mpic-data-is-text-relative -msched-prolog
@ -mthumb -munaligned-access -mvectorize-with-neon-quad

	.section	.text._ZNKSt5ctypeIcE8do_widenEc,"axG",%progbits,_ZNKSt5ctypeIcE8do_widenEc,comdat
	.align	2
	.weak	_ZNKSt5ctypeIcE8do_widenEc
	.thumb
	.thumb_func
	.type	_ZNKSt5ctypeIcE8do_widenEc, %function
_ZNKSt5ctypeIcE8do_widenEc:
	.fnstart
.LFB1048:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	mov	r0, r1	@, __c
	bx	lr	@
	.cantunwind
	.fnend
	.size	_ZNKSt5ctypeIcE8do_widenEc, .-_ZNKSt5ctypeIcE8do_widenEc
	.section	.text.unlikely,"ax",%progbits
	.align	2
	.thumb
	.thumb_func
	.type	_ZNSs4_Rep10_M_disposeERKSaIcE.part.1, %function
_ZNSs4_Rep10_M_disposeERKSaIcE.part.1:
	.fnstart
.LFB2621:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	movw	r3, #:lower16:_ZL28__gthrw___pthread_key_createPjPFvPvE	@ tmp117,
	movt	r3, #:upper16:_ZL28__gthrw___pthread_key_createPjPFvPvE	@ tmp117,
	push	{lr}	@
	cbz	r3, .L3	@ tmp117,
	add	r2, r0, #8	@ tmp118, this,
	dmb	sy
.L6:
	ldrex	r3, [r2]	@ D.70789,
	add	lr, r3, #-1	@ tmp120, D.70789,
	strex	ip, lr, [r2]	@ tmp121, tmp120,
	cmp	ip, #0	@ tmp121,
	bne	.L6	@,
	dmb	sy
	b	.L4	@
.L3:
	ldr	r3, [r0, #8]	@ __result, MEM[(_Atomic_word *)this_1(D) + 8B]
	subs	r2, r3, #1	@ D.70788, __result,
	str	r2, [r0, #8]	@ D.70788, MEM[(_Atomic_word *)this_1(D) + 8B]
.L4:
	cmp	r3, #0	@ D.70789,
	bgt	.L2	@,
	ldr	lr, [sp], #4	@,
	b	_ZNSs4_Rep10_M_destroyERKSaIcE	@
.L2:
	ldr	pc, [sp], #4	@
	.cantunwind
	.fnend
	.size	_ZNSs4_Rep10_M_disposeERKSaIcE.part.1, .-_ZNSs4_Rep10_M_disposeERKSaIcE.part.1
	.text
	.align	2
	.global	_ZN11Interpreter5fetchEv
	.thumb
	.thumb_func
	.type	_ZN11Interpreter5fetchEv, %function
_ZN11Interpreter5fetchEv:
	.fnstart
.LFB2065:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r2, [r0, #64]	@ this_3(D)->currentMethod, this_3(D)->currentMethod
	push	{r4, r5, r6, lr}	@
	.save {r4, r5, r6, lr}
	mov	r4, r0	@ this, this
	ldr	r6, [r2, #24]	@ D.70793, _4->codeAttribute
	ldr	r3, [r0]	@ D.70794, this_3(D)->pc
	adds	r2, r3, #1	@ D.70794, D.70794,
	str	r2, [r0]	@ D.70794, this_3(D)->pc
	ldr	r2, [r6, #32]	@ MEM[(char * *)_5 + 32B], MEM[(char * *)_5 + 32B]
	ldrb	r5, [r2, r3]	@ zero_extendqisi2	@ opCode, *_36
	str	r5, [r0, #4]	@ opCode, this_3(D)->ir
	add	r5, r5, r5, lsl #1	@, tmp142, opCode, opCode,
	bl	_ZN14InstructionSet8InstanceEv	@
	add	r0, r0, r5, lsl #2	@, tmp144,, tmp142,
	ldr	r2, [r0, #8]	@ D.70794, _15->instructionTable[opCode_12].operandSize
	cmp	r2, #1	@ D.70794,
	str	r2, [r4, #8]	@ D.70794, this_3(D)->operandSize
	beq	.L14	@,
	cmp	r2, #2	@ D.70794,
	ldr	r3, [r4]	@ D.70800, this_3(D)->pc
	itttt	eq
	ldreq	r1, [r6, #32]	@ MEM[(char * *)_5 + 32B], MEM[(char * *)_5 + 32B]
	ldrbeq	r1, [r1, r3]	@ zero_extendqisi2	@ D.70797, *_38
	strbeq	r1, [r4, #12]	@ D.70797, this_3(D)->operandByte1
	ldreq	r1, [r6, #32]	@ MEM[(char * *)_5 + 32B], MEM[(char * *)_5 + 32B]
	it	eq
	addeq	r1, r1, r3	@ tmp151, D.70800
	add	r3, r3, r2	@ D.70794, D.70794
	it	eq
	ldrbeq	r1, [r1, #1]	@ zero_extendqisi2	@ D.70797, *_39
	str	r3, [r4]	@ D.70794, this_3(D)->pc
	it	eq
	strbeq	r1, [r4, #13]	@ D.70797, this_3(D)->operandByte2
	pop	{r4, r5, r6, pc}	@
.L14:
	ldr	r1, [r6, #32]	@ MEM[(char * *)_5 + 32B], MEM[(char * *)_5 + 32B]
	ldr	r3, [r4]	@ D.70800, this_3(D)->pc
	ldrb	r1, [r1, r3]	@ zero_extendqisi2	@ D.70797, *_37
	add	r3, r3, r2	@ D.70794, D.70794
	str	r3, [r4]	@ D.70794, this_3(D)->pc
	strb	r1, [r4, #12]	@ D.70797, this_3(D)->operandByte1
	pop	{r4, r5, r6, pc}	@
	.fnend
	.size	_ZN11Interpreter5fetchEv, .-_ZN11Interpreter5fetchEv
	.align	2
	.global	_ZN11Interpreter6decodeEv
	.thumb
	.thumb_func
	.type	_ZN11Interpreter6decodeEv, %function
_ZN11Interpreter6decodeEv:
	.fnstart
.LFB2066:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	bx	lr	@
	.cantunwind
	.fnend
	.size	_ZN11Interpreter6decodeEv, .-_ZN11Interpreter6decodeEv
	.align	2
	.global	_Z13invokeVirtualP10MethodInfo
	.thumb
	.thumb_func
	.type	_Z13invokeVirtualP10MethodInfo, %function
_Z13invokeVirtualP10MethodInfo:
	.fnstart
.LFB2071:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	bx	lr	@
	.cantunwind
	.fnend
	.size	_Z13invokeVirtualP10MethodInfo, .-_Z13invokeVirtualP10MethodInfo
	.section	.text._ZNSt11_Deque_baseIP5FrameSaIS1_EED2Ev,"axG",%progbits,_ZNSt11_Deque_baseIP5FrameSaIS1_EED5Ev,comdat
	.align	2
	.weak	_ZNSt11_Deque_baseIP5FrameSaIS1_EED2Ev
	.thumb
	.thumb_func
	.type	_ZNSt11_Deque_baseIP5FrameSaIS1_EED2Ev, %function
_ZNSt11_Deque_baseIP5FrameSaIS1_EED2Ev:
	.fnstart
.LFB2309:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, lr}	@
	mov	r6, r0	@ this, this
	ldr	r0, [r0]	@ D.70816, this_3(D)->_M_impl._M_map
	cbz	r0, .L18	@ D.70816,
	ldr	r5, [r6, #36]	@ this_3(D)->_M_impl._M_finish._M_node, this_3(D)->_M_impl._M_finish._M_node
	ldr	r4, [r6, #20]	@ __nstart, this_3(D)->_M_impl._M_start._M_node
	adds	r5, r5, #4	@ D.70816, this_3(D)->_M_impl._M_finish._M_node,
	cmp	r4, r5	@ __nstart, D.70816
	bcs	.L19	@,
.L20:
	ldr	r0, [r4], #4	@, MEM[base: __nstart_23, offset: 0B]
	bl	_ZdlPv	@
	cmp	r5, r4	@ D.70816, __nstart
	bhi	.L20	@,
	ldr	r0, [r6]	@ D.70816, this_3(D)->_M_impl._M_map
.L19:
	bl	_ZdlPv	@
.L18:
	mov	r0, r6	@, this
	pop	{r4, r5, r6, pc}	@
	.cantunwind
	.fnend
	.size	_ZNSt11_Deque_baseIP5FrameSaIS1_EED2Ev, .-_ZNSt11_Deque_baseIP5FrameSaIS1_EED2Ev
	.weak	_ZNSt11_Deque_baseIP5FrameSaIS1_EED1Ev
	.thumb_set _ZNSt11_Deque_baseIP5FrameSaIS1_EED1Ev,_ZNSt11_Deque_baseIP5FrameSaIS1_EED2Ev
	.section	.text._ZNSt6vectorI13operand_valueSaIS0_EE19_M_emplace_back_auxIIRKS0_EEEvDpOT_,"axG",%progbits,_ZNSt6vectorI13operand_valueSaIS0_EE19_M_emplace_back_auxIIRKS0_EEEvDpOT_,comdat
	.align	2
	.weak	_ZNSt6vectorI13operand_valueSaIS0_EE19_M_emplace_back_auxIIRKS0_EEEvDpOT_
	.thumb
	.thumb_func
	.type	_ZNSt6vectorI13operand_valueSaIS0_EE19_M_emplace_back_auxIIRKS0_EEEvDpOT_, %function
_ZNSt6vectorI13operand_valueSaIS0_EE19_M_emplace_back_auxIIRKS0_EEEvDpOT_:
	.fnstart
.LFB2330:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, lr}	@
	.save {r4, r5, r6, r7, r8, lr}
	mov	r5, r0	@ this, this
	ldmia	r0, {r3, r4}	@ this,,
	mov	r8, r1	@ __args#0, __args#0
	subs	r4, r4, r3	@ D.70830, MEM[(struct operand_value * *)this_2(D) + 4B], D.70832
	asrs	r2, r4, #3	@ D.70830, D.70830,
	beq	.L32	@,
	lsls	r6, r2, #1	@ __len, D.70830,
	cmp	r2, r6	@ D.70830, __len
	bls	.L44	@,
.L34:
	mvn	r7, #7	@ D.70828,
	b	.L27	@
.L32:
	movs	r7, #8	@ D.70828,
.L27:
	mov	r0, r7	@, D.70828
	bl	_Znwj	@
	ldmia	r5, {r3, r4}	@ this,,
	subs	r4, r4, r3	@ D.70830, MEM[(struct operand_value * *)this_2(D) + 4B], D.70832
	asrs	r2, r4, #3	@ D.70830, D.70830,
	mov	r6, r0	@ D.70831,
.L28:
	adds	lr, r6, r4	@ D.70829, D.70831, D.70830
	itt	ne
	ldmiane	r8, {r0, r1}	@ __args#0,,
	stmiane	lr, {r0, r1}	@ D.70829,,
	mov	r0, r3	@ D.70831, D.70832
	cbnz	r2, .L45	@ D.70830,
.L30:
	adds	r4, r4, #8	@ D.70834, D.70830,
	add	r4, r4, r6	@ __new_finish, D.70831
	cbz	r0, .L31	@ D.70831,
	bl	_ZdlPv	@
.L31:
	add	r7, r7, r6	@ D.70829, D.70831
	str	r6, [r5]	@ D.70831, this_2(D)->D.59905._M_impl._M_start
	str	r7, [r5, #8]	@ D.70829, this_2(D)->D.59905._M_impl._M_end_of_storage
	str	r4, [r5, #4]	@ __new_finish, this_2(D)->D.59905._M_impl._M_finish
	pop	{r4, r5, r6, r7, r8, pc}	@
.L45:
	mov	r1, r3	@, D.70832
	mov	r0, r6	@, D.70831
	mov	r2, r4	@, D.70830
	bl	memmove	@
	ldr	r0, [r5]	@ D.70831, this_2(D)->D.59905._M_impl._M_start
	b	.L30	@
.L44:
	cmp	r6, #536870912	@ __len,
	bcs	.L34	@,
	lsls	r7, r2, #4	@ D.70828, D.70830,
	cmp	r6, #0	@ __len
	beq	.L28	@
	b	.L27	@
	.fnend
	.size	_ZNSt6vectorI13operand_valueSaIS0_EE19_M_emplace_back_auxIIRKS0_EEEvDpOT_, .-_ZNSt6vectorI13operand_valueSaIS0_EE19_M_emplace_back_auxIIRKS0_EEEvDpOT_
	.weak	_ZNSt6vectorI13operand_valueSaIS0_EE19_M_emplace_back_auxIJRKS0_EEEvDpOT_
	.thumb_set _ZNSt6vectorI13operand_valueSaIS0_EE19_M_emplace_back_auxIJRKS0_EEEvDpOT_,_ZNSt6vectorI13operand_valueSaIS0_EE19_M_emplace_back_auxIIRKS0_EEEvDpOT_
	.text
	.align	2
	.global	_ZN11Interpreter7executeEv
	.thumb
	.thumb_func
	.type	_ZN11Interpreter7executeEv, %function
_ZN11Interpreter7executeEv:
	.fnstart
.LFB2067:
	@ args = 0, pretend = 0, frame = 56
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, lr}	@
	.save {r4, r5, r6, r7, lr}
	movw	r1, #:lower16:.LC0	@,
	ldr	r4, .L142	@ tmp289,
	.pad #60
	sub	sp, sp, #60	@,,
	mov	r5, r0	@ this, this
	add	r2, sp, #32	@ tmp470,,
	movt	r1, #:upper16:.LC0	@,
	add	r0, sp, #24	@,,
	str	r4, [sp, #4]	@ tmp289, MEM[(struct _Alloc_hider *)&data]._M_p
	movs	r3, #16	@ tmp290,
	ldr	r7, [r5, #4]	@ D.70986, this_5(D)->ir
	subs	r4, r4, #12	@ tmp457, tmp289,
	str	r3, [sp, #20]	@ tmp290, D.61417.opCode
.LEHB0:
	bl	_ZNSsC1EPKcRKSaIcE	@
	ldr	r3, [sp, #24]	@ D.70985, MEM[(const struct basic_string *)&D.61417 + 4B]._M_dataplus._M_p
	movw	r4, #:lower16:_ZNSs4_Rep20_S_empty_rep_storageE	@ tmp457,
	movt	r4, #:upper16:_ZNSs4_Rep20_S_empty_rep_storageE	@ tmp457,
	movs	r2, #1	@ tmp295,
	sub	r0, r3, #12	@ D.70994, D.70985,
	str	r2, [sp, #28]	@ tmp295, D.61417.operandSize
	cmp	r0, r4	@ D.70994, tmp457
	ldr	r6, [sp, #20]	@ D.70986, D.61417.opCode
	bne	.L132	@,
.L48:
	cmp	r7, r6	@ D.70986, D.70986
	beq	.L133	@,
	movw	r1, #:lower16:.LC2	@,
	add	r0, sp, #36	@,,
	movt	r1, #:upper16:.LC2	@,
	add	r2, sp, #20	@ tmp471,,
	movs	r3, #182	@ tmp331,
	ldr	r7, [r5, #4]	@ D.70986, this_5(D)->ir
	str	r3, [sp, #32]	@ tmp331, D.61595.opCode
	bl	_ZNSsC1EPKcRKSaIcE	@
	ldr	r3, [sp, #36]	@ D.70985, MEM[(const struct basic_string *)&D.61595 + 4B]._M_dataplus._M_p
	movs	r2, #2	@ tmp336,
	ldr	r6, [sp, #32]	@ D.70986, D.61595.opCode
	sub	r0, r3, #12	@ D.70994, D.70985,
	str	r2, [sp, #40]	@ tmp336, D.61595.operandSize
	cmp	r0, r4	@ D.70994, tmp457
	bne	.L134	@,
.L61:
	cmp	r7, r6	@ D.70986, D.70986
	beq	.L135	@,
	movw	r1, #:lower16:.LC3	@,
	add	r2, sp, #20	@ tmp472,,
	movt	r1, #:upper16:.LC3	@,
	add	r0, sp, #48	@,,
	movs	r3, #18	@ tmp366,
	ldr	r7, [r5, #4]	@ D.70986, this_5(D)->ir
	str	r3, [sp, #44]	@ tmp366, D.61600.opCode
	bl	_ZNSsC1EPKcRKSaIcE	@
	ldr	r3, [sp, #48]	@ D.70985, MEM[(const struct basic_string *)&D.61600 + 4B]._M_dataplus._M_p
	movs	r2, #1	@ tmp371,
	ldr	r6, [sp, #44]	@ D.70986, D.61600.opCode
	sub	r0, r3, #12	@ D.70994, D.70985,
	str	r2, [sp, #52]	@ tmp371, D.61600.operandSize
	cmp	r0, r4	@ D.70994, tmp457
	bne	.L136	@,
.L71:
	cmp	r7, r6	@ D.70986, D.70986
	beq	.L137	@,
	movw	r0, #:lower16:_ZSt4cout	@,
	movw	r1, #:lower16:.LC6	@,
	movt	r0, #:upper16:_ZSt4cout	@,
	movt	r1, #:upper16:.LC6	@,
	movs	r2, #14	@,
	bl	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_i	@
	movw	r3, #:lower16:_ZSt4cout	@ tmp415,
	ldr	r1, [r5, #4]	@, this_5(D)->ir
	movt	r3, #:upper16:_ZSt4cout	@ tmp415,
	ldr	r2, [r3]	@ cout._vptr.basic_ostream, cout._vptr.basic_ostream
	mov	r0, r3	@, tmp415
	ldr	r2, [r2, #-12]	@ MEM[(int *)_142 + 4294967284B], MEM[(int *)_142 + 4294967284B]
	add	r3, r3, r2	@ D.70998, MEM[(int *)_142 + 4294967284B]
	ldr	r2, [r3, #12]	@ _145->_M_flags, _145->_M_flags
	bic	r2, r2, #74	@ D.70986, _145->_M_flags,
	orr	r2, r2, #8	@ D.70986, D.70986,
	str	r2, [r3, #12]	@ D.70986, MEM[(_Ios_Fmtflags &)_145 + 12]
	bl	_ZNSolsEi	@
	movw	r1, #:lower16:.LC7	@,
	movs	r2, #1	@,
	movt	r1, #:upper16:.LC7	@,
	mov	r6, r0	@ D.70993,
	bl	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_i	@
	bl	_ZN14InstructionSet8InstanceEv	@
	ldr	r3, [r5, #4]	@ this_5(D)->ir, this_5(D)->ir
	add	r3, r3, r3, lsl #1	@, tmp428, this_5(D)->ir, this_5(D)->ir,
	add	r3, r0, r3, lsl #2	@, tmp430,, tmp428,
	mov	r0, r6	@, D.70993
	ldr	r1, [r3, #4]	@ D.70985, MEM[(const struct basic_string *)_97].instructionTable[_98].mnemonic._M_dataplus._M_p
	ldr	r2, [r1, #-12]	@, MEM[(struct _Rep *)_90 + 4294967284B].D.23039._M_length
	bl	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_i	@
	ldr	r3, [r0]	@ _148->_vptr.basic_ostream, _148->_vptr.basic_ostream
	mov	r7, r0	@ D.70993,
	ldr	r3, [r3, #-12]	@ MEM[(int *)_94 + 4294967284B], MEM[(int *)_94 + 4294967284B]
	add	r3, r3, r0	@ tmp434, D.70993
	ldr	r6, [r3, #124]	@ D.71005, MEM[(const struct __ctype_type * *)_366 + 124B]
	cmp	r6, #0	@ D.71005
	beq	.L138	@
.L86:
	ldrb	r3, [r6, #28]	@ zero_extendqisi2	@ MEM[(const struct ctype *)_367]._M_widen_ok,
	cbz	r3, .L87	@ MEM[(const struct ctype *)_367]._M_widen_ok,
	ldrb	r1, [r6, #39]	@ zero_extendqisi2	@ D.71006,
.L88:
	mov	r0, r7	@, D.70993
	bl	_ZNSo3putEc	@
	bl	_ZNSo5flushEv	@
.L116:
	ldr	r3, [r5, #56]	@ this_5(D)->currentFrame, this_5(D)->currentFrame
.L59:
	mov	r0, r3	@, this_5(D)->currentFrame
	bl	_ZN5Frame4dumpEv	@
	ldr	r3, [sp, #4]	@ D.70985, data._M_dataplus._M_p
	sub	r0, r3, #12	@ D.70994, D.70985,
	cmp	r0, r4	@ D.70994, tmp457
	bne	.L139	@,
.L46:
	add	sp, sp, #60	@,,
	@ sp needed	@
	pop	{r4, r5, r6, r7, pc}	@
.L87:
	mov	r0, r6	@, D.71005
	bl	_ZNKSt5ctypeIcE13_M_widen_initEv	@
	ldr	r2, [r6]	@ MEM[(const struct ctype *)_367].D.26430._vptr.facet,* D.71005
	movw	r3, #:lower16:_ZNKSt5ctypeIcE8do_widenEc	@ tmp437,
	movt	r3, #:upper16:_ZNKSt5ctypeIcE8do_widenEc	@ tmp437,
	ldr	r2, [r2, #24]	@ D.71007,
	cmp	r2, r3	@ D.71007, tmp437
	it	eq
	moveq	r1, #10	@ D.71006,
	beq	.L88	@,
	mov	r0, r6	@, D.71005
	movs	r1, #10	@,
	blx	r2	@ D.71007
	mov	r1, r0	@ D.71006,
	b	.L88	@
.L133:
	ldr	r2, [r5, #56]	@ D.70989, this_5(D)->currentFrame
	movs	r3, #1	@ tmp301,
	str	r3, [sp, #12]	@ tmp301, operandValue.tag
	ldrb	r0, [r5, #12]	@ zero_extendqisi2	@ this_5(D)->operandByte1, this_5(D)->operandByte1
	ldr	r3, [r2, #20]	@ D.70999, MEM[(struct vector *)_19 + 16B].D.59905._M_impl._M_finish
	ldr	r1, [r2, #24]	@ MEM[(struct vector *)_19 + 16B].D.59905._M_impl._M_end_of_storage, MEM[(struct vector *)_19 + 16B].D.59905._M_impl._M_end_of_storage
	str	r0, [sp, #16]	@ this_5(D)->operandByte1, operandValue.D.56760.int_v
	cmp	r3, r1	@ D.70999, MEM[(struct vector *)_19 + 16B].D.59905._M_impl._M_end_of_storage
	beq	.L53	@,
	cbz	r3, .L54	@ D.70999,
	add	r1, sp, #12	@ tmp305,,
	ldmia	r1, {r0, r1}	@ tmp305,,
	stmia	r3, {r0, r1}	@ D.70999,,
.L54:
	adds	r3, r3, #8	@ D.70999, D.70999,
	str	r3, [r2, #20]	@ D.70999, MEM[(struct vector *)_19 + 16B].D.59905._M_impl._M_finish
.L55:
	bl	_ZN14InstructionSet8InstanceEv	@
	ldr	r3, [r5, #4]	@ this_5(D)->ir, this_5(D)->ir
	add	r3, r3, r3, lsl #1	@, tmp312, this_5(D)->ir, this_5(D)->ir,
	add	r3, r0, r3, lsl #2	@, tmp314,, tmp312,
	movw	r0, #:lower16:_ZSt4cout	@,
	movt	r0, #:upper16:_ZSt4cout	@,
	ldr	r1, [r3, #4]	@ D.70985, MEM[(const struct basic_string *)_23].instructionTable[_24].mnemonic._M_dataplus._M_p
	ldr	r2, [r1, #-12]	@, MEM[(struct _Rep *)_13 + 4294967284B].D.23039._M_length
	bl	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_i	@
	movw	r1, #:lower16:.LC1	@,
	movs	r2, #2	@,
	movt	r1, #:upper16:.LC1	@,
	mov	r6, r0	@ D.70993,
	bl	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_i	@
	ldr	r3, [r6]	@ _117->_vptr.basic_ostream, _117->_vptr.basic_ostream
	mov	r0, r6	@, D.70993
	ldr	r1, [sp, #16]	@, operandValue.D.56760.int_v
	ldr	r3, [r3, #-12]	@ MEM[(int *)_25 + 4294967284B], MEM[(int *)_25 + 4294967284B]
	adds	r2, r6, r3	@ D.70998, D.70993, MEM[(int *)_25 + 4294967284B]
	ldr	r3, [r2, #12]	@ _120->_M_flags, _120->_M_flags
	bic	r3, r3, #74	@ D.70986, _120->_M_flags,
	orr	r3, r3, #2	@ D.70986, D.70986,
	str	r3, [r2, #12]	@ D.70986, MEM[(_Ios_Fmtflags &)_120 + 12]
	bl	_ZNSolsEi	@
	ldr	r3, [r0]	@ _30->_vptr.basic_ostream, _30->_vptr.basic_ostream
	mov	r7, r0	@ D.70993,
	ldr	r3, [r3, #-12]	@ MEM[(int *)_177 + 4294967284B], MEM[(int *)_177 + 4294967284B]
	add	r3, r3, r0	@ tmp326, D.70993
	ldr	r6, [r3, #124]	@ D.71005, MEM[(const struct __ctype_type * *)_266 + 124B]
	cmp	r6, #0	@ D.71005
	bne	.L86	@
	bl	_ZSt16__throw_bad_castv	@
.L135:
	ldrb	r7, [r5, #12]	@ zero_extendqisi2	@ D.70986, this_5(D)->operandByte1
	ldrb	r3, [r5, #13]	@ zero_extendqisi2	@ D.70986, this_5(D)->operandByte2
	add	r7, r3, r7, lsl #8	@, D.70986, D.70986, D.70986,
	bl	_ZN14InstructionSet8InstanceEv	@
	ldr	r3, [r5, #4]	@ this_5(D)->ir, this_5(D)->ir
	add	r3, r3, r3, lsl #1	@, tmp348, this_5(D)->ir, this_5(D)->ir,
	add	r3, r0, r3, lsl #2	@, tmp350,, tmp348,
	movw	r0, #:lower16:_ZSt4cout	@,
	movt	r0, #:upper16:_ZSt4cout	@,
	ldr	r1, [r3, #4]	@ D.70985, MEM[(const struct basic_string *)_48].instructionTable[_49].mnemonic._M_dataplus._M_p
	ldr	r2, [r1, #-12]	@, MEM[(struct _Rep *)_39 + 4294967284B].D.23039._M_length
	bl	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_i	@
	movw	r1, #:lower16:.LC1	@,
	movs	r2, #2	@,
	movt	r1, #:upper16:.LC1	@,
	mov	r6, r0	@ D.70993,
	bl	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_i	@
	ldr	r3, [r6]	@ _126->_vptr.basic_ostream, _126->_vptr.basic_ostream
	mov	r1, r7	@, D.70986
	mov	r0, r6	@, D.70993
	ldr	r3, [r3, #-12]	@ MEM[(int *)_50 + 4294967284B], MEM[(int *)_50 + 4294967284B]
	adds	r2, r6, r3	@ D.70998, D.70993, MEM[(int *)_50 + 4294967284B]
	ldr	r3, [r2, #12]	@ _129->_M_flags, _129->_M_flags
	bic	r3, r3, #74	@ D.70986, _129->_M_flags,
	orr	r3, r3, #2	@ D.70986, D.70986,
	str	r3, [r2, #12]	@ D.70986, MEM[(_Ios_Fmtflags &)_129 + 12]
	bl	_ZNSolsEi	@
	ldr	r3, [r0]	@ _54->_vptr.basic_ostream, _54->_vptr.basic_ostream
	mov	r7, r0	@ D.70993,
	ldr	r3, [r3, #-12]	@ MEM[(int *)_191 + 4294967284B], MEM[(int *)_191 + 4294967284B]
	add	r3, r3, r0	@ tmp361, D.70993
	ldr	r6, [r3, #124]	@ D.71005, MEM[(const struct __ctype_type * *)_298 + 124B]
	cmp	r6, #0	@ D.71005
	bne	.L86	@
	bl	_ZSt16__throw_bad_castv	@
.L137:
	ldrb	r6, [r5, #12]	@ zero_extendqisi2	@ index, this_5(D)->operandByte1
	add	r0, sp, #8	@ tmp474,,
	ldr	r1, [r5, #60]	@, this_5(D)->currentClass
	mov	r2, r6	@, index
	bl	_ZN9JavaClass16getConstantValueEi	@
.LEHE0:
	add	r1, sp, #8	@ tmp475,,
	add	r0, sp, #4	@,,
.LEHB1:
	bl	_ZNSs4swapERSs	@
.LEHE1:
	ldr	r3, [sp, #8]	@ D.70985, D.61601._M_dataplus._M_p
	sub	r0, r3, #12	@ D.70994, D.70985,
	cmp	r0, r4	@ D.70994, tmp457
	bne	.L140	@,
.L77:
	movw	r0, #:lower16:_ZSt4cout	@,
	movw	r1, #:lower16:.LC4	@,
	movt	r0, #:upper16:_ZSt4cout	@,
	movt	r1, #:upper16:.LC4	@,
	movs	r2, #5	@,
.LEHB2:
	bl	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_i	@
	movw	r3, #:lower16:_ZSt4cout	@ tmp388,
	mov	r1, r6	@, index
	movt	r3, #:upper16:_ZSt4cout	@ tmp388,
	ldr	r2, [r3]	@ cout._vptr.basic_ostream, cout._vptr.basic_ostream
	mov	r0, r3	@, tmp388
	ldr	r2, [r2, #-12]	@ MEM[(int *)_71 + 4294967284B], MEM[(int *)_71 + 4294967284B]
	add	r3, r3, r2	@ D.70998, MEM[(int *)_71 + 4294967284B]
	ldr	r2, [r3, #12]	@ _138->_M_flags, _138->_M_flags
	bic	r2, r2, #74	@ D.70986, _138->_M_flags,
	orr	r2, r2, #2	@ D.70986, D.70986,
	str	r2, [r3, #12]	@ D.70986, MEM[(_Ios_Fmtflags &)_138 + 12]
	bl	_ZNSo9_M_insertImEERSoT_	@
	movw	r1, #:lower16:.LC5	@,
	movs	r2, #7	@,
	movt	r1, #:upper16:.LC5	@,
	mov	r6, r0	@ D.70996,
	bl	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_i	@
	ldr	r1, [sp, #4]	@ D.70985, data._M_dataplus._M_p
	mov	r0, r6	@, D.70996
	ldr	r2, [r1, #-12]	@, MEM[(struct _Rep *)_76 + 4294967284B].D.23039._M_length
	bl	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_i	@
	ldr	r3, [r0]	@ _141->_vptr.basic_ostream, _141->_vptr.basic_ostream
	mov	r7, r0	@ D.70993,
	ldr	r3, [r3, #-12]	@ MEM[(int *)_77 + 4294967284B], MEM[(int *)_77 + 4294967284B]
	add	r3, r3, r0	@ tmp400, D.70993
	ldr	r6, [r3, #124]	@ D.71005, MEM[(const struct __ctype_type * *)_336 + 124B]
	cmp	r6, #0	@ D.71005
	beq	.L141	@
	ldrb	r3, [r6, #28]	@ zero_extendqisi2	@ MEM[(const struct ctype *)_337]._M_widen_ok, MEM[(const struct ctype *)_337]._M_widen_ok
	cmp	r3, #0	@ MEM[(const struct ctype *)_337]._M_widen_ok
	beq	.L82	@
	ldrb	r1, [r6, #39]	@ zero_extendqisi2	@ D.71006, MEM[(const struct ctype *)_337]._M_widen
.L83:
	mov	r0, r7	@, D.70993
	bl	_ZNSo3putEc	@
	bl	_ZNSo5flushEv	@
	ldr	r3, [r5, #56]	@ this_5(D)->currentFrame, this_5(D)->currentFrame
	movs	r2, #3	@ tmp405,
	str	r2, [sp, #12]	@ tmp405, operandValue.tag
	ldr	r0, [sp, #4]	@ data._M_dataplus._M_p, data._M_dataplus._M_p
	ldr	r2, [r3, #20]	@ D.70999, MEM[(struct vector *)_83 + 16B].D.59905._M_impl._M_finish
	ldr	r1, [r3, #24]	@ MEM[(struct vector *)_83 + 16B].D.59905._M_impl._M_end_of_storage, MEM[(struct vector *)_83 + 16B].D.59905._M_impl._M_end_of_storage
	str	r0, [sp, #16]	@ data._M_dataplus._M_p, operandValue.D.56760.objectref
	cmp	r2, r1	@ D.70999, MEM[(struct vector *)_83 + 16B].D.59905._M_impl._M_end_of_storage
	beq	.L84	@,
	cbz	r2, .L85	@ D.70999,
	add	r1, sp, #12	@ tmp409,,
	ldmia	r1, {r0, r1}	@ tmp409,,
	stmia	r2, {r0, r1}	@ D.70999,,
.L85:
	adds	r2, r2, #8	@ D.70999, D.70999,
	str	r2, [r3, #20]	@ D.70999, MEM[(struct vector *)_83 + 16B].D.59905._M_impl._M_finish
	b	.L59	@
.L143:
	.align	2
.L142:
	.word	_ZNSs4_Rep20_S_empty_rep_storageE+12
.L136:
	movw	r2, #:lower16:_ZL28__gthrw___pthread_key_createPjPFvPvE	@ tmp373,
	movt	r2, #:upper16:_ZL28__gthrw___pthread_key_createPjPFvPvE	@ tmp373,
	cmp	r2, #0	@ tmp373
	beq	.L72	@
	subs	r3, r3, #4	@ tmp374, D.70985,
	dmb	sy
.L112:
	ldrex	r2, [r3]	@ D.71002,
	subs	r1, r2, #1	@ tmp464, D.71002,
	strex	lr, r1, [r3]	@ tmp465, tmp464,
	cmp	lr, #0	@ tmp465,
	bne	.L112	@,
	dmb	sy
.L73:
	cmp	r2, #0	@ D.71002,
	bgt	.L71	@,
	add	r1, sp, #32	@ tmp473,,
	bl	_ZNSs4_Rep10_M_destroyERKSaIcE	@
	b	.L71	@
.L132:
	movw	r2, #:lower16:_ZL28__gthrw___pthread_key_createPjPFvPvE	@ tmp297,
	movt	r2, #:upper16:_ZL28__gthrw___pthread_key_createPjPFvPvE	@ tmp297,
	cmp	r2, #0	@ tmp297
	beq	.L49	@
	subs	r3, r3, #4	@ tmp298, D.70985,
	dmb	sy
.L114:
	ldrex	r2, [r3]	@ D.71002,
	subs	r1, r2, #1	@ tmp460, D.71002,
	strex	lr, r1, [r3]	@ tmp461, tmp460,
	cmp	lr, #0	@ tmp461,
	bne	.L114	@,
	dmb	sy
.L50:
	cmp	r2, #0	@ D.71002,
	bgt	.L48	@,
	add	r1, sp, #44	@,,
	bl	_ZNSs4_Rep10_M_destroyERKSaIcE	@
	b	.L48	@
.L139:
	movw	r2, #:lower16:_ZL28__gthrw___pthread_key_createPjPFvPvE	@ tmp441,
	movt	r2, #:upper16:_ZL28__gthrw___pthread_key_createPjPFvPvE	@ tmp441,
	cmp	r2, #0	@ tmp441
	beq	.L91	@
	subs	r3, r3, #4	@ tmp442, D.70985,
	dmb	sy
.L110:
	ldrex	r2, [r3]	@ D.71002,
	subs	r1, r2, #1	@ tmp468, D.71002,
	strex	r4, r1, [r3]	@ tmp469, tmp468,
	cmp	r4, #0	@ tmp469,
	bne	.L110	@,
	dmb	sy
.L92:
	cmp	r2, #0	@ D.71002,
	bgt	.L46	@,
	add	r1, sp, #44	@,,
	bl	_ZNSs4_Rep10_M_destroyERKSaIcE	@
	b	.L46	@
.L134:
	movw	r2, #:lower16:_ZL28__gthrw___pthread_key_createPjPFvPvE	@ tmp338,
	movt	r2, #:upper16:_ZL28__gthrw___pthread_key_createPjPFvPvE	@ tmp338,
	cmp	r2, #0	@ tmp338
	beq	.L62	@
	subs	r3, r3, #4	@ tmp339, D.70985,
	dmb	sy
.L113:
	ldrex	r2, [r3]	@ D.71002,
	subs	r1, r2, #1	@ tmp462, D.71002,
	strex	lr, r1, [r3]	@ tmp463, tmp462,
	cmp	lr, #0	@ tmp463,
	bne	.L113	@,
	dmb	sy
.L63:
	cmp	r2, #0	@ D.71002,
	bgt	.L61	@,
	add	r1, sp, #44	@,,
	bl	_ZNSs4_Rep10_M_destroyERKSaIcE	@
	b	.L61	@
.L82:
	mov	r0, r6	@, D.71005
	bl	_ZNKSt5ctypeIcE13_M_widen_initEv	@
	ldr	r2, [r6]	@ MEM[(const struct ctype *)_337].D.26430._vptr.facet, MEM[(const struct ctype *)_337].D.26430._vptr.facet
	movw	r3, #:lower16:_ZNKSt5ctypeIcE8do_widenEc	@ tmp403,
	movt	r3, #:upper16:_ZNKSt5ctypeIcE8do_widenEc	@ tmp403,
	ldr	r2, [r2, #24]	@ D.71007, MEM[(int (*__vtbl_ptr_type) () *)_346 + 24B]
	cmp	r2, r3	@ D.71007, tmp403
	it	eq
	moveq	r1, #10	@ D.71006,
	beq	.L83	@,
	mov	r0, r6	@, D.71005
	movs	r1, #10	@,
	blx	r2	@ D.71007
.LEHE2:
	mov	r1, r0	@ D.71006,
	b	.L83	@
.L72:
	ldr	r2, [r3, #-4]	@ __result, MEM[(_Atomic_word *)_55 + 4294967292B]
	subs	r1, r2, #1	@ D.70986, __result,
	str	r1, [r3, #-4]	@ D.70986, MEM[(_Atomic_word *)_55 + 4294967292B]
	b	.L73	@
.L102:
.L96:
	ldr	r0, [sp, #4]	@ data._M_dataplus._M_p, data._M_dataplus._M_p
	subs	r0, r0, #12	@ D.70994, data._M_dataplus._M_p,
	cmp	r0, r4	@ D.70994, tmp457
	beq	.L97	@,
	mov	r1, sp	@,
	bl	_ZNSs4_Rep10_M_disposeERKSaIcE.part.1	@
.L97:
.LEHB3:
	bl	__cxa_end_cleanup	@
.LEHE3:
.L91:
	ldr	r2, [r3, #-4]	@ __result, MEM[(_Atomic_word *)_99 + 4294967292B]
	subs	r1, r2, #1	@ D.70986, __result,
	str	r1, [r3, #-4]	@ D.70986, MEM[(_Atomic_word *)_99 + 4294967292B]
	b	.L92	@
.L49:
	ldr	r2, [r3, #-4]	@ __result, MEM[(_Atomic_word *)_4 + 4294967292B]
	subs	r1, r2, #1	@ D.70986, __result,
	str	r1, [r3, #-4]	@ D.70986, MEM[(_Atomic_word *)_4 + 4294967292B]
	b	.L50	@
.L62:
	ldr	r2, [r3, #-4]	@ __result, MEM[(_Atomic_word *)_31 + 4294967292B]
	subs	r1, r2, #1	@ D.70986, __result,
	str	r1, [r3, #-4]	@ D.70986, MEM[(_Atomic_word *)_31 + 4294967292B]
	b	.L63	@
.L53:
	add	r0, r2, #16	@, D.70989,
	add	r1, sp, #12	@,,
.LEHB4:
	bl	_ZNSt6vectorI13operand_valueSaIS0_EE19_M_emplace_back_auxIIRKS0_EEEvDpOT_	@
	b	.L55	@
.L140:
	movw	r2, #:lower16:_ZL28__gthrw___pthread_key_createPjPFvPvE	@ tmp382,
	movt	r2, #:upper16:_ZL28__gthrw___pthread_key_createPjPFvPvE	@ tmp382,
	cbz	r2, .L78	@ tmp382,
	subs	r3, r3, #4	@ tmp383, D.70985,
	dmb	sy
.L111:
	ldrex	r2, [r3]	@ D.71002,
	subs	r1, r2, #1	@ tmp466, D.71002,
	strex	r7, r1, [r3]	@ tmp467, tmp466,
	cmp	r7, #0	@ tmp467,
	bne	.L111	@,
	dmb	sy
.L79:
	cmp	r2, #0	@ D.71002,
	bgt	.L77	@,
	add	r1, sp, #44	@,,
	bl	_ZNSs4_Rep10_M_destroyERKSaIcE	@
	b	.L77	@
.L84:
	add	r0, r3, #16	@, this_5(D)->currentFrame,
	add	r1, sp, #12	@,,
	bl	_ZNSt6vectorI13operand_valueSaIS0_EE19_M_emplace_back_auxIIRKS0_EEEvDpOT_	@
	b	.L116	@
.L78:
	ldr	r2, [r3, #-4]	@ __result, MEM[(_Atomic_word *)_70 + 4294967292B]
	subs	r1, r2, #1	@ D.70986, __result,
	str	r1, [r3, #-4]	@ D.70986, MEM[(_Atomic_word *)_70 + 4294967292B]
	b	.L79	@
.L141:
	bl	_ZSt16__throw_bad_castv	@
.L138:
	bl	_ZSt16__throw_bad_castv	@
.LEHE4:
.L103:
	ldr	r0, [sp, #8]	@ D.61601._M_dataplus._M_p, D.61601._M_dataplus._M_p
	subs	r0, r0, #12	@ D.70994, D.61601._M_dataplus._M_p,
	cmp	r0, r4	@ D.70994, tmp457
	beq	.L96	@,
	add	r1, sp, #44	@,,
	bl	_ZNSs4_Rep10_M_disposeERKSaIcE.part.1	@
	b	.L96	@
	.global	__gxx_personality_v0
	.personality	__gxx_personality_v0
	.handlerdata
.LLSDA2067:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2067-.LLSDACSB2067
.LLSDACSB2067:
	.uleb128 .LEHB0-.LFB2067
	.uleb128 .LEHE0-.LEHB0
	.uleb128 .L102-.LFB2067
	.uleb128 0
	.uleb128 .LEHB1-.LFB2067
	.uleb128 .LEHE1-.LEHB1
	.uleb128 .L103-.LFB2067
	.uleb128 0
	.uleb128 .LEHB2-.LFB2067
	.uleb128 .LEHE2-.LEHB2
	.uleb128 .L102-.LFB2067
	.uleb128 0
	.uleb128 .LEHB3-.LFB2067
	.uleb128 .LEHE3-.LEHB3
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB4-.LFB2067
	.uleb128 .LEHE4-.LEHB4
	.uleb128 .L102-.LFB2067
	.uleb128 0
.LLSDACSE2067:
	.text
	.fnend
	.size	_ZN11Interpreter7executeEv, .-_ZN11Interpreter7executeEv
	.align	2
	.global	_ZN11Interpreter10runCurrentEv
	.thumb
	.thumb_func
	.type	_ZN11Interpreter10runCurrentEv, %function
_ZN11Interpreter10runCurrentEv:
	.fnstart
.LFB2064:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, lr}	@
	.save {r4, lr}
	mov	r4, r0	@ this, this
	b	.L150	@
.L151:
	mov	r0, r4	@, this
	bl	_ZN11Interpreter5fetchEv	@
	mov	r0, r4	@, this
	bl	_ZN11Interpreter7executeEv	@
.L150:
	ldr	r3, [r4, #64]	@ this_3(D)->currentMethod, this_3(D)->currentMethod
	ldr	r2, [r4]	@ this_3(D)->pc, this_3(D)->pc
	ldr	r3, [r3, #24]	@ _14->codeAttribute,
	ldr	r3, [r3, #28]	@ _15->codeLength,
	cmp	r2, r3	@ this_3(D)->pc, _15->codeLength
	bcc	.L151	@,
	pop	{r4, pc}	@
	.fnend
	.size	_ZN11Interpreter10runCurrentEv, .-_ZN11Interpreter10runCurrentEv
	.section	.text._ZNSt11_Deque_baseIP5FrameSaIS1_EE17_M_initialize_mapEj,"axG",%progbits,_ZNSt11_Deque_baseIP5FrameSaIS1_EE17_M_initialize_mapEj,comdat
	.align	2
	.weak	_ZNSt11_Deque_baseIP5FrameSaIS1_EE17_M_initialize_mapEj
	.thumb
	.thumb_func
	.type	_ZNSt11_Deque_baseIP5FrameSaIS1_EE17_M_initialize_mapEj, %function
_ZNSt11_Deque_baseIP5FrameSaIS1_EE17_M_initialize_mapEj:
	.fnstart
.LFB2412:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, r9, r10, lr}	@
	.save {r4, r5, r6, r7, r8, r9, r10, lr}
	lsrs	r5, r1, #7	@ D.71054, __num_elements,
	mov	r7, r0	@ this, this
	adds	r0, r5, #3	@ D.71054, D.71054,
	cmp	r0, #8	@ D.71054,
	mov	r8, r1	@ __num_elements, __num_elements
	add	r5, r5, #1	@ __num_nodes, D.71054,
	it	cc
	movcc	r0, #8	@ D.71054,
	str	r0, [r7, #4]	@ D.71054, this_9(D)->_M_impl._M_map_size
	lsls	r0, r0, #2	@, D.71054,
.LEHB5:
	bl	_Znwj	@
.LEHE5:
	ldr	r6, [r7, #4]	@ this_9(D)->_M_impl._M_map_size, this_9(D)->_M_impl._M_map_size
	subs	r6, r6, r5	@ D.71054, this_9(D)->_M_impl._M_map_size, __num_nodes
	lsrs	r6, r6, #1	@ D.71054, D.71054,
	add	r9, r0, r6, lsl #2	@, __nstart, D.71058, D.71054,
	mov	r10, r0	@ D.71058,
	add	r5, r9, r5, lsl #2	@, __nfinish, __nstart, __num_nodes,
	str	r0, [r7]	@ D.71058, this_9(D)->_M_impl._M_map
	cmp	r9, r5	@ __nstart, __nfinish
	bcs	.L153	@,
	mov	r4, r9	@ __nstart, __nstart
.L154:
	mov	r0, #512	@,
.LEHB6:
	bl	_Znwj	@
.LEHE6:
	str	r0, [r4], #4	@, MEM[base: __nstart_72, offset: 0B]
	cmp	r5, r4	@ __nfinish, __nstart
	bhi	.L154	@,
.L153:
	str	r9, [r7, #20]	@ __nstart, MEM[(struct _Deque_iterator *)this_9(D) + 8B]._M_node
	subs	r2, r5, #4	@ D.71056, __nfinish,
	ldr	r1, [r10, r6, lsl #2]	@ D.71055, *__nstart_19
	and	r3, r8, #127	@ D.71054, __num_elements,
	str	r2, [r7, #36]	@ D.71056, MEM[(struct _Deque_iterator *)this_9(D) + 24B]._M_node
	add	r2, r1, #512	@ D.71055, D.71055,
	str	r2, [r7, #16]	@ D.71055, MEM[(struct _Deque_iterator *)this_9(D) + 8B]._M_last
	str	r1, [r7, #12]	@ D.71055, MEM[(struct _Deque_iterator *)this_9(D) + 8B]._M_first
	ldr	r2, [r5, #-4]	@ D.71055, MEM[(struct Frame * * *)__nfinish_21 + 4294967292B]
	str	r1, [r7, #8]	@ D.71055, this_9(D)->_M_impl._M_start._M_cur
	add	r3, r2, r3, lsl #2	@, D.71055, D.71055, D.71054,
	add	r1, r2, #512	@ D.71055, D.71055,
	str	r3, [r7, #24]	@ D.71055, this_9(D)->_M_impl._M_finish._M_cur
	str	r2, [r7, #28]	@ D.71055, MEM[(struct _Deque_iterator *)this_9(D) + 24B]._M_first
	str	r1, [r7, #32]	@ D.71055, MEM[(struct _Deque_iterator *)this_9(D) + 24B]._M_last
	pop	{r4, r5, r6, r7, r8, r9, r10, pc}	@
.L162:
	bl	__cxa_begin_catch	@
	cmp	r4, r9	@ __nstart, __nstart
	bls	.L159	@,
.L158:
	ldr	r0, [r9], #4	@, MEM[base: __nstart_73, offset: 0B]
	bl	_ZdlPv	@
	cmp	r4, r9	@ __nstart, __nstart
	bhi	.L158	@,
.L159:
.LEHB7:
	bl	__cxa_rethrow	@
.LEHE7:
.L163:
	mov	r4, r0	@ tmp146,
	bl	__cxa_end_catch	@
	mov	r0, r4	@, tmp146
	bl	__cxa_begin_catch	@
	ldr	r0, [r7]	@, this_9(D)->_M_impl._M_map
	bl	_ZdlPv	@
	movs	r3, #0	@ tmp150,
	str	r3, [r7]	@ tmp150, this_9(D)->_M_impl._M_map
	str	r3, [r7, #4]	@ tmp150, this_9(D)->_M_impl._M_map_size
.LEHB8:
	bl	__cxa_rethrow	@
.LEHE8:
.L161:
	bl	__cxa_end_catch	@
.LEHB9:
	bl	__cxa_end_cleanup	@
.LEHE9:
	.personality	__gxx_personality_v0
	.handlerdata
	.align	2
.LLSDA2412:
	.byte	0xff
	.byte	0x90
	.uleb128 .LLSDATT2412-.LLSDATTD2412
.LLSDATTD2412:
	.byte	0x1
	.uleb128 .LLSDACSE2412-.LLSDACSB2412
.LLSDACSB2412:
	.uleb128 .LEHB5-.LFB2412
	.uleb128 .LEHE5-.LEHB5
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB6-.LFB2412
	.uleb128 .LEHE6-.LEHB6
	.uleb128 .L162-.LFB2412
	.uleb128 0x1
	.uleb128 .LEHB7-.LFB2412
	.uleb128 .LEHE7-.LEHB7
	.uleb128 .L163-.LFB2412
	.uleb128 0x3
	.uleb128 .LEHB8-.LFB2412
	.uleb128 .LEHE8-.LEHB8
	.uleb128 .L161-.LFB2412
	.uleb128 0
	.uleb128 .LEHB9-.LFB2412
	.uleb128 .LEHE9-.LEHB9
	.uleb128 0
	.uleb128 0
.LLSDACSE2412:
	.byte	0x1
	.byte	0
	.byte	0
	.byte	0x7d
	.align	2
	.word	0
.LLSDATT2412:
	.section	.text._ZNSt11_Deque_baseIP5FrameSaIS1_EE17_M_initialize_mapEj,"axG",%progbits,_ZNSt11_Deque_baseIP5FrameSaIS1_EE17_M_initialize_mapEj,comdat
	.fnend
	.size	_ZNSt11_Deque_baseIP5FrameSaIS1_EE17_M_initialize_mapEj, .-_ZNSt11_Deque_baseIP5FrameSaIS1_EE17_M_initialize_mapEj
	.text
	.align	2
	.global	_ZN11InterpreterC2EP9JavaClass
	.thumb
	.thumb_func
	.type	_ZN11InterpreterC2EP9JavaClass, %function
_ZN11InterpreterC2EP9JavaClass:
	.fnstart
.LFB2060:
	@ args = 0, pretend = 0, frame = 40
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, lr}	@
	.save {r4, r5, r6, r7, r8, lr}
	.pad #40
	sub	sp, sp, #40	@,,
	movs	r4, #0	@ tmp126,
	mov	r8, r0	@ this, this
	mov	r5, r1	@ mainClass, mainClass
	mov	r0, sp	@,
	mov	r1, r4	@, tmp126
	str	r4, [sp]	@ tmp126, MEM[(struct _Deque_impl *)&D.61320]._M_map
	str	r4, [sp, #4]	@ tmp126, MEM[(struct _Deque_impl *)&D.61320]._M_map_size
	str	r4, [sp, #8]	@ tmp126, MEM[(struct _Deque_iterator *)&D.61320 + 8B]._M_cur
	str	r4, [sp, #12]	@ tmp126, MEM[(struct _Deque_iterator *)&D.61320 + 8B]._M_first
	str	r4, [sp, #16]	@ tmp126, MEM[(struct _Deque_iterator *)&D.61320 + 8B]._M_last
	str	r4, [sp, #20]	@ tmp126, MEM[(struct _Deque_iterator *)&D.61320 + 8B]._M_node
	str	r4, [sp, #24]	@ tmp126, MEM[(struct _Deque_iterator *)&D.61320 + 24B]._M_cur
	str	r4, [sp, #28]	@ tmp126, MEM[(struct _Deque_iterator *)&D.61320 + 24B]._M_first
	str	r4, [sp, #32]	@ tmp126, MEM[(struct _Deque_iterator *)&D.61320 + 24B]._M_last
	str	r4, [sp, #36]	@ tmp126, MEM[(struct _Deque_iterator *)&D.61320 + 24B]._M_node
.LEHB10:
	bl	_ZNSt11_Deque_baseIP5FrameSaIS1_EE17_M_initialize_mapEj	@
.LEHE10:
	str	r4, [r8, #16]	@ tmp126, MEM[(struct _Deque_impl *)this_1(D) + 16B]._M_map
	mov	r1, r4	@, tmp126
	str	r4, [r8, #20]	@ tmp126, MEM[(struct _Deque_impl *)this_1(D) + 16B]._M_map_size
	add	r0, r8, #16	@, this,
	str	r4, [r8, #24]	@ tmp126, MEM[(struct _Deque_iterator *)this_1(D) + 24B]._M_cur
	str	r4, [r8, #28]	@ tmp126, MEM[(struct _Deque_iterator *)this_1(D) + 24B]._M_first
	str	r4, [r8, #32]	@ tmp126, MEM[(struct _Deque_iterator *)this_1(D) + 24B]._M_last
	str	r4, [r8, #36]	@ tmp126, MEM[(struct _Deque_iterator *)this_1(D) + 24B]._M_node
	str	r4, [r8, #40]	@ tmp126, MEM[(struct _Deque_iterator *)this_1(D) + 40B]._M_cur
	str	r4, [r8, #44]	@ tmp126, MEM[(struct _Deque_iterator *)this_1(D) + 40B]._M_first
	str	r4, [r8, #48]	@ tmp126, MEM[(struct _Deque_iterator *)this_1(D) + 40B]._M_last
	str	r4, [r8, #52]	@ tmp126, MEM[(struct _Deque_iterator *)this_1(D) + 40B]._M_node
.LEHB11:
	bl	_ZNSt11_Deque_baseIP5FrameSaIS1_EE17_M_initialize_mapEj	@
.LEHE11:
	ldr	r6, [sp]	@ D.71069, MEM[(struct _Deque_base &)&D.61320]._M_impl._M_map
	cbz	r6, .L169	@ D.71069,
	ldr	r4, [r8, #28]	@ tmp162, MEM[(const struct iterator &)this_1(D) + 24]._M_first
	add	r3, sp, #8	@ tmp149,,
	add	ip, r8, #24	@ tmp148, this,
	ldr	r7, [r8, #24]	@ D.71070, MEM[(const struct iterator &)this_1(D) + 24]._M_cur
	ldmia	r3, {r0, r1, r2, r3}	@ tmp149,,,,
	add	lr, r8, #40	@ tmp150, this,
	str	r4, [sp, #12]	@ tmp162, MEM[(struct _Deque_iterator *)&D.61320 + 12B]
	ldr	r4, [r8, #32]	@ tmp163, MEM[(const struct iterator &)this_1(D) + 24]._M_last
	str	r7, [sp, #8]	@ D.71070, MEM[(struct _Deque_iterator *)&D.61320 + 8B]
	str	r4, [sp, #16]	@ tmp163, MEM[(struct _Deque_iterator *)&D.61320 + 16B]
	ldr	r4, [r8, #36]	@ tmp164, MEM[(const struct iterator &)this_1(D) + 24]._M_node
	stmia	ip, {r0, r1, r2, r3}	@ tmp148,,,,
	add	r3, sp, #40	@ tmp165,,
	str	r4, [sp, #20]	@ tmp164, MEM[(struct _Deque_iterator *)&D.61320 + 20B]
	ldr	r4, [r8, #40]	@ D.71070, MEM[(const struct iterator &)this_1(D) + 40]._M_cur
	ldmdb	r3, {r0, r1, r2, r3}	@ tmp165,,,,
	str	r4, [sp, #24]	@ D.71070, MEM[(struct _Deque_iterator *)&D.61320 + 24B]
	ldr	r4, [r8, #44]	@ tmp166, MEM[(const struct iterator &)this_1(D) + 40]._M_first
	ldr	r7, [r8, #52]	@ D.71069, MEM[(const struct iterator &)this_1(D) + 40]._M_node
	str	r4, [sp, #28]	@ tmp166, MEM[(struct _Deque_iterator *)&D.61320 + 28B]
	ldr	r4, [r8, #48]	@ tmp167, MEM[(const struct iterator &)this_1(D) + 40]._M_last
	str	r7, [sp, #36]	@ D.71069, MEM[(struct _Deque_iterator *)&D.61320 + 36B]
	stmia	lr, {r0, r1, r2, r3}	@ tmp150,,,,
	str	r4, [sp, #32]	@ tmp167, MEM[(struct _Deque_iterator *)&D.61320 + 32B]
	ldr	r1, [r8, #16]	@ D.71069, MEM[(struct Frame * * * &)this_1(D) + 16]
	str	r6, [r8, #16]	@ D.71069, MEM[(struct Frame * * * &)this_1(D) + 16]
	ldr	r2, [r8, #20]	@ D.71071, MEM[(type &)this_1(D) + 20]
	ldr	r3, [sp, #4]	@ MEM[(type &)&D.61320 + 4], MEM[(type &)&D.61320 + 4]
	stmia	sp, {r1, r2}	@,,
	str	r3, [r8, #20]	@ MEM[(type &)&D.61320 + 4], MEM[(unsigned int &)this_1(D) + 20]
.L169:
	mov	r0, sp	@,
	bl	_ZNSt11_Deque_baseIP5FrameSaIS1_EED2Ev	@
	movs	r3, #0	@ tmp154,
	mov	r0, r8	@, this
	str	r5, [r8, #68]	@ mainClass, this_1(D)->mainClass
	str	r3, [r8, #72]	@ tmp154, this_1(D)->mainMethod
	str	r3, [r8]	@ tmp154, this_1(D)->pc
	str	r3, [r8, #4]	@ tmp154, this_1(D)->ir
	add	sp, sp, #40	@,,
	@ sp needed	@
	pop	{r4, r5, r6, r7, r8, pc}	@
.L171:
	mov	r0, sp	@,
	bl	_ZNSt11_Deque_baseIP5FrameSaIS1_EED2Ev	@
.LEHB12:
	bl	__cxa_end_cleanup	@
.LEHE12:
	.personality	__gxx_personality_v0
	.handlerdata
.LLSDA2060:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2060-.LLSDACSB2060
.LLSDACSB2060:
	.uleb128 .LEHB10-.LFB2060
	.uleb128 .LEHE10-.LEHB10
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB11-.LFB2060
	.uleb128 .LEHE11-.LEHB11
	.uleb128 .L171-.LFB2060
	.uleb128 0
	.uleb128 .LEHB12-.LFB2060
	.uleb128 .LEHE12-.LEHB12
	.uleb128 0
	.uleb128 0
.LLSDACSE2060:
	.text
	.fnend
	.size	_ZN11InterpreterC2EP9JavaClass, .-_ZN11InterpreterC2EP9JavaClass
	.global	_ZN11InterpreterC1EP9JavaClass
	.thumb_set _ZN11InterpreterC1EP9JavaClass,_ZN11InterpreterC2EP9JavaClass
	.section	.text._ZNSt5dequeIP5FrameSaIS1_EE16_M_push_back_auxIIRKS1_EEEvDpOT_,"axG",%progbits,_ZNSt5dequeIP5FrameSaIS1_EE16_M_push_back_auxIIRKS1_EEEvDpOT_,comdat
	.align	2
	.weak	_ZNSt5dequeIP5FrameSaIS1_EE16_M_push_back_auxIIRKS1_EEEvDpOT_
	.thumb
	.thumb_func
	.type	_ZNSt5dequeIP5FrameSaIS1_EE16_M_push_back_auxIIRKS1_EEEvDpOT_, %function
_ZNSt5dequeIP5FrameSaIS1_EE16_M_push_back_auxIIRKS1_EEEvDpOT_:
	.fnstart
.LFB2422:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, r9, r10, lr}	@
	.save {r4, r5, r6, r7, r8, r9, r10, lr}
	mov	r4, r0	@ this, this
	ldr	r5, [r0, #36]	@ D.71100, this_2(D)->D.61103._M_impl._M_finish._M_node
	mov	r7, r1	@ __args#0, __args#0
	ldr	r6, [r0]	@ D.71099, this_2(D)->D.61103._M_impl._M_map
	ldr	r2, [r0, #4]	@ D.71101, this_2(D)->D.61103._M_impl._M_map_size
	subs	r3, r5, r6	@ D.71102, D.71100, D.71099
	sub	r3, r2, r3, asr #2	@ D.71101, D.71101, D.71102,
	cmp	r3, #1	@ D.71101,
	bls	.L199	@,
.L178:
	mov	r0, #512	@,
	bl	_Znwj	@
	str	r0, [r5, #4]	@, MEM[(struct Frame * * *)_14 + 4B]
	ldr	r3, [r4, #24]	@ D.71098, this_2(D)->D.61103._M_impl._M_finish._M_cur
	ldr	r2, [r7]	@ D.71097, *__args#0_8(D)
	cbz	r3, .L184	@ D.71098,
	str	r2, [r3]	@ D.71097, *_7
.L184:
	ldr	r3, [r4, #36]	@ D.71099, this_2(D)->D.61103._M_impl._M_finish._M_node
	adds	r2, r3, #4	@ D.71099, D.71099,
	str	r2, [r4, #36]	@ D.71099, MEM[(struct _Deque_iterator *)this_2(D) + 24B]._M_node
	ldr	r3, [r3, #4]	@ D.71098, MEM[(struct Frame * * *)_10 + 4B]
	add	r2, r3, #512	@ D.71098, D.71098,
	str	r2, [r4, #32]	@ D.71098, MEM[(struct _Deque_iterator *)this_2(D) + 24B]._M_last
	str	r3, [r4, #28]	@ D.71098, MEM[(struct _Deque_iterator *)this_2(D) + 24B]._M_first
	str	r3, [r4, #24]	@ D.71098, this_2(D)->D.61103._M_impl._M_finish._M_cur
	pop	{r4, r5, r6, r7, r8, r9, r10, pc}	@
.L199:
	ldr	r1, [r0, #20]	@ D.71099, this_2(D)->D.61103._M_impl._M_start._M_node
	subs	r3, r5, r1	@ D.71102, D.71100, D.71099
	asrs	r3, r3, #2	@ D.71102, D.71102,
	add	r8, r3, #1	@ __old_num_nodes, D.71102,
	add	r9, r8, #1	@ __new_num_nodes, __old_num_nodes,
	cmp	r2, r9, lsl #1	@ D.71101, __new_num_nodes,
	bhi	.L200	@,
	cmp	r2, #0	@ D.71101
	beq	.L185	@
	lsls	r5, r2, #1	@ D.71101, D.71101,
	adds	r5, r5, #2	@ __new_map_size, D.71101,
	cmp	r5, #1073741824	@ __new_map_size,
	bcs	.L201	@,
.L182:
	lsls	r0, r5, #2	@, __new_map_size,
	rsb	r6, r9, r5	@ D.71101, __new_num_nodes, __new_map_size
	bl	_Znwj	@
	ldr	r2, [r4, #36]	@ this_2(D)->D.61103._M_impl._M_finish._M_node, this_2(D)->D.61103._M_impl._M_finish._M_node
	ldr	r1, [r4, #20]	@ D.71099, this_2(D)->D.61103._M_impl._M_start._M_node
	lsrs	r6, r6, #1	@ D.71101, D.71101,
	adds	r2, r2, #4	@ D.71099, this_2(D)->D.61103._M_impl._M_finish._M_node,
	subs	r2, r2, r1	@ D.71102, D.71099, D.71099
	lsrs	r3, r2, #2	@ tmp217, D.71102,
	mov	r10, r0	@ D.71104,
	add	r6, r0, r6, lsl #2	@, __new_nstart, D.71104, D.71101,
	bne	.L202	@,
.L183:
	ldr	r0, [r4]	@, this_2(D)->D.61103._M_impl._M_map
	bl	_ZdlPv	@
	str	r10, [r4]	@ D.71104, this_2(D)->D.61103._M_impl._M_map
	str	r5, [r4, #4]	@ __new_map_size, this_2(D)->D.61103._M_impl._M_map_size
.L181:
	str	r6, [r4, #20]	@ __new_nstart, MEM[(struct _Deque_iterator *)this_2(D) + 8B]._M_node
	add	r3, r8, #1073741824	@ D.71103, __old_num_nodes,
	ldr	r2, [r6]	@ D.71098, MEM[(struct Frame * * *)__new_nstart_80]
	subs	r3, r3, #1	@ D.71103, D.71103,
	add	r1, r2, #512	@ D.71098, D.71098,
	add	r5, r6, r3, lsl #2	@, D.71100, __new_nstart, D.71103,
	str	r2, [r4, #12]	@ D.71098, MEM[(struct _Deque_iterator *)this_2(D) + 8B]._M_first
	str	r5, [r4, #36]	@ D.71100, MEM[(struct _Deque_iterator *)this_2(D) + 24B]._M_node
	str	r1, [r4, #16]	@ D.71098, MEM[(struct _Deque_iterator *)this_2(D) + 8B]._M_last
	ldr	r3, [r6, r3, lsl #2]	@ D.71098, *_85
	add	r2, r3, #512	@ D.71098, D.71098,
	str	r2, [r4, #32]	@ D.71098, MEM[(struct _Deque_iterator *)this_2(D) + 24B]._M_last
	str	r3, [r4, #28]	@ D.71098, MEM[(struct _Deque_iterator *)this_2(D) + 24B]._M_first
	b	.L178	@
.L200:
	rsb	r2, r9, r2	@ D.71101, __new_num_nodes, D.71101
	lsrs	r2, r2, #1	@ D.71101, D.71101,
	add	r6, r6, r2, lsl #2	@, __new_nstart, D.71099, D.71101,
	adds	r2, r5, #4	@ D.71099, D.71100,
	cmp	r1, r6	@ D.71099, __new_nstart
	sub	r2, r2, r1	@ D.71102, D.71099, D.71099
	bls	.L180	@,
	lsrs	r3, r2, #2	@ tmp215, D.71102,
	beq	.L181	@,
	mov	r0, r6	@, __new_nstart
	bl	memmove	@
	b	.L181	@
.L185:
	movs	r5, #3	@ __new_map_size,
	b	.L182	@
.L202:
	mov	r0, r6	@, __new_nstart
	bl	memmove	@
	b	.L183	@
.L180:
	lsrs	r3, r2, #2	@ tmp216, D.71102,
	beq	.L181	@,
	rsb	r0, r2, r8, lsl #2	@, D.71103, D.71102, __old_num_nodes,
	add	r0, r0, r6	@, __new_nstart
	bl	memmove	@
	b	.L181	@
.L201:
	bl	_ZSt17__throw_bad_allocv	@
	.fnend
	.size	_ZNSt5dequeIP5FrameSaIS1_EE16_M_push_back_auxIIRKS1_EEEvDpOT_, .-_ZNSt5dequeIP5FrameSaIS1_EE16_M_push_back_auxIIRKS1_EEEvDpOT_
	.weak	_ZNSt5dequeIP5FrameSaIS1_EE16_M_push_back_auxIJRKS1_EEEvDpOT_
	.thumb_set _ZNSt5dequeIP5FrameSaIS1_EE16_M_push_back_auxIJRKS1_EEEvDpOT_,_ZNSt5dequeIP5FrameSaIS1_EE16_M_push_back_auxIIRKS1_EEEvDpOT_
	.text
	.align	2
	.global	_ZN11Interpreter8switchToEP10MethodInfo
	.thumb
	.thumb_func
	.type	_ZN11Interpreter8switchToEP10MethodInfo, %function
_ZN11Interpreter8switchToEP10MethodInfo:
	.fnstart
.LFB2063:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r2, [r0, #48]	@ MEM[(struct deque *)this_2(D) + 16B].D.61103._M_impl._M_finish._M_last, MEM[(struct deque *)this_2(D) + 16B].D.61103._M_impl._M_finish._M_last
	ldr	r3, [r0, #40]	@ D.71165, MEM[(struct deque *)this_2(D) + 16B].D.61103._M_impl._M_finish._M_cur
	push	{r4, r5, r6, r7, r8, r9, lr}	@
	.save {r4, r5, r6, r7, r8, r9, lr}
	subs	r2, r2, #4	@ D.71165, MEM[(struct deque *)this_2(D) + 16B].D.61103._M_impl._M_finish._M_last,
	mov	r4, r1	@ method, method
	ldr	r1, [r0, #56]	@ D.71160, this_2(D)->currentFrame
	.pad #12
	sub	sp, sp, #12	@,,
	cmp	r3, r2	@ D.71165, D.71165
	mov	r5, r0	@ this, this
	str	r1, [sp, #4]	@ D.71160, oldFrame
	beq	.L204	@,
	cbz	r3, .L205	@ D.71165,
	str	r1, [r3]	@ D.71160, *_19
	ldr	r3, [r0, #40]	@ D.71165, MEM[(struct deque *)this_2(D) + 16B].D.61103._M_impl._M_finish._M_cur
.L205:
	adds	r3, r3, #4	@ D.71165, D.71165,
	str	r3, [r5, #40]	@ D.71165, MEM[(struct deque *)this_2(D) + 16B].D.61103._M_impl._M_finish._M_cur
.L206:
	ldr	r3, [r4, #28]	@ method_6(D)->clazz, method_6(D)->clazz
	movs	r0, #32	@,
	str	r4, [r5, #64]	@ method, this_2(D)->currentMethod
	str	r3, [r5, #60]	@ method_6(D)->clazz, this_2(D)->currentClass
.LEHB13:
	bl	_Znwj	@
.LEHE13:
	ldr	r2, [r5, #60]	@ this_2(D)->currentClass, this_2(D)->currentClass
	movs	r3, #0	@ tmp150,
	adds	r2, r2, #12	@ D.71163, this_2(D)->currentClass,
	mov	r4, r0	@ D.71162,
	movs	r0, #20	@,
	str	r3, [r4, #4]	@ tmp150, MEM[(struct _Vector_impl *)_11 + 4B]._M_start
	str	r3, [r4, #8]	@ tmp150, MEM[(struct _Vector_impl *)_11 + 4B]._M_finish
	str	r2, [r4, #28]	@ D.71163, MEM[(struct Frame *)_11].constantPool
	str	r3, [r4, #12]	@ tmp150, MEM[(struct _Vector_impl *)_11 + 4B]._M_end_of_storage
	str	r3, [r4, #16]	@ tmp150, MEM[(struct _Vector_impl *)_11 + 16B]._M_start
	str	r3, [r4, #20]	@ tmp150, MEM[(struct _Vector_impl *)_11 + 16B]._M_finish
	str	r3, [r4, #24]	@ tmp150, MEM[(struct _Vector_impl *)_11 + 16B]._M_end_of_storage
.LEHB14:
	bl	_Znwj	@
	mov	r6, r0	@ D.71169,
	ldr	r0, [r4, #4]	@ D.71167, MEM[(struct vector *)_11 + 4B].D.58354._M_impl._M_start
	cbz	r0, .L207	@ D.71167,
	bl	_ZdlPv	@
.L207:
	ldr	r8, [r4, #16]	@ D.71170, MEM[(struct operand_value * *)_11 + 16B]
	add	r2, r6, #20	@ D.71167, D.71169,
	ldr	r3, [r4, #24]	@ MEM[(struct operand_value * *)_11 + 24B], MEM[(struct operand_value * *)_11 + 24B]
	str	r6, [r4, #4]	@ D.71169, MEM[(struct vector *)_11 + 4B].D.58354._M_impl._M_start
	rsb	r3, r8, r3	@ D.71171, D.71170, MEM[(struct operand_value * *)_11 + 24B]
	str	r6, [r4, #8]	@ D.71169, MEM[(struct vector *)_11 + 4B].D.58354._M_impl._M_finish
	cmp	r3, #39	@ D.71171,
	str	r2, [r4, #12]	@ D.71167, MEM[(struct vector *)_11 + 4B].D.58354._M_impl._M_end_of_storage
	bls	.L233	@,
	str	r4, [r5, #56]	@ D.71162, this_2(D)->currentFrame
	add	sp, sp, #12	@,,
	@ sp needed	@
	pop	{r4, r5, r6, r7, r8, r9, pc}	@
.L233:
	ldr	r6, [r4, #20]	@ MEM[(struct operand_value * *)_11 + 20B], MEM[(struct operand_value * *)_11 + 20B]
	movs	r0, #40	@,
	rsb	r6, r8, r6	@ D.71171, D.71170, MEM[(struct operand_value * *)_11 + 20B]
	asr	r9, r6, #3	@ D.71171, D.71171,
	bl	_Znwj	@
.LEHE14:
	mov	r7, r0	@ D.71173,
	cmp	r9, #0	@ D.71171
	beq	.L210	@
	mov	r1, r8	@, D.71170
	mov	r2, r6	@, D.71171
	bl	memmove	@
.L210:
	ldr	r0, [r4, #16]	@ D.71166, MEM[(struct vector *)_11 + 16B].D.59905._M_impl._M_start
	cbz	r0, .L211	@ D.71166,
	bl	_ZdlPv	@
.L211:
	add	r6, r6, r7	@ D.71166, D.71173
	str	r7, [r4, #16]	@ D.71173, MEM[(struct vector *)_11 + 16B].D.59905._M_impl._M_start
	str	r6, [r4, #20]	@ D.71166, MEM[(struct vector *)_11 + 16B].D.59905._M_impl._M_finish
	adds	r7, r7, #40	@ D.71166, D.71173,
	str	r7, [r4, #24]	@ D.71166, MEM[(struct vector *)_11 + 16B].D.59905._M_impl._M_end_of_storage
	str	r4, [r5, #56]	@ D.71162, this_2(D)->currentFrame
	add	sp, sp, #12	@,,
	@ sp needed	@
	pop	{r4, r5, r6, r7, r8, r9, pc}	@
.L204:
	adds	r0, r0, #16	@, this,
	add	r1, sp, #4	@,,
.LEHB15:
	bl	_ZNSt5dequeIP5FrameSaIS1_EE16_M_push_back_auxIIRKS1_EEEvDpOT_	@
	b	.L206	@
.L215:
	ldr	r0, [r4, #16]	@ D.71166, MEM[(struct _Vector_base *)_11 + 16B]._M_impl._M_start
	cbz	r0, .L213	@ D.71166,
	bl	_ZdlPv	@
.L213:
	ldr	r0, [r4, #4]	@ D.71167, MEM[(struct _Vector_base *)_11 + 4B]._M_impl._M_start
	cbz	r0, .L214	@ D.71167,
	bl	_ZdlPv	@
.L214:
	mov	r0, r4	@, D.71162
	bl	_ZdlPv	@
	bl	__cxa_end_cleanup	@
.LEHE15:
	.personality	__gxx_personality_v0
	.handlerdata
.LLSDA2063:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2063-.LLSDACSB2063
.LLSDACSB2063:
	.uleb128 .LEHB13-.LFB2063
	.uleb128 .LEHE13-.LEHB13
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB14-.LFB2063
	.uleb128 .LEHE14-.LEHB14
	.uleb128 .L215-.LFB2063
	.uleb128 0
	.uleb128 .LEHB15-.LFB2063
	.uleb128 .LEHE15-.LEHB15
	.uleb128 0
	.uleb128 0
.LLSDACSE2063:
	.text
	.fnend
	.size	_ZN11Interpreter8switchToEP10MethodInfo, .-_ZN11Interpreter8switchToEP10MethodInfo
	.align	2
	.global	_ZN11Interpreter3runEv
	.thumb
	.thumb_func
	.type	_ZN11Interpreter3runEv, %function
_ZN11Interpreter3runEv:
	.fnstart
.LFB2062:
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, [r0, #68]	@ D.71184, this_6(D)->mainClass
	push	{r4, r5, r6, r7, r8, lr}	@
	.save {r4, r5, r6, r7, r8, lr}
	mov	r5, r0	@ this, this
	ldrh	r2, [r3, #60]	@ _52->methodCount, _52->methodCount
	.pad #16
	sub	sp, sp, #16	@,,
	cmp	r2, #0	@ _52->methodCount
	beq	.L236	@
	movw	r6, #:lower16:_ZNSs4_Rep20_S_empty_rep_storageE	@ tmp169,
	movs	r4, #0	@ i,
	movt	r6, #:upper16:_ZNSs4_Rep20_S_empty_rep_storageE	@ tmp169,
	b	.L244	@
.L239:
	ldr	r3, [r5, #68]	@ this_6(D)->mainClass, this_6(D)->mainClass
	cmp	r8, #0	@ D.71186
	beq	.L254	@
	ldrh	r2, [r3, #60]	@ D.71186, _7->methodCount
	adds	r4, r4, #1	@ i, i,
	cmp	r2, r4	@ D.71186, i
	ble	.L236	@,
.L244:
	ldr	r2, [r3, #64]	@ MEM[(struct MethodInfo * * *)_46 + 64B], MEM[(struct MethodInfo * * *)_46 + 64B]
	lsls	r7, r4, #2	@ D.71189, i,
	ldr	r3, [r3, #12]	@ MEM[(struct ConstantInfo * * *)_46 + 12B], MEM[(struct ConstantInfo * * *)_46 + 12B]
	ldr	r2, [r2, r4, lsl #2]	@ *_39, *_39
	ldrh	r2, [r2, #6]	@ D.71189, _12->nameIndex
	ldr	r0, [r3, r2, lsl #2]	@ D.71191, *_41
	cbz	r0, .L237	@ D.71191,
	movw	r1, #:lower16:_ZTI12ConstantInfo	@,
	movw	r2, #:lower16:_ZTI16ConstantUtf8Info	@,
	movt	r1, #:upper16:_ZTI12ConstantInfo	@,
	movt	r2, #:upper16:_ZTI16ConstantUtf8Info	@,
	movs	r3, #0	@,
	bl	__dynamic_cast	@
.L237:
	ldr	r1, [r0, #8]	@, MEM[(char * *)nameUtf8_2 + 8B]
	add	r2, sp, #4	@ tmp177,,
	add	r0, sp, #12	@ tmp176,,
.LEHB16:
	bl	_ZNSsC1EPKcRKSaIcE	@
.LEHE16:
	movw	r1, #:lower16:.LC8	@,
	add	r0, sp, #12	@ tmp178,,
	movt	r1, #:upper16:.LC8	@,
.LEHB17:
	bl	_ZNKSs7compareEPKc	@
.LEHE17:
	ldr	r3, [sp, #12]	@ D.71193, D.61334._M_dataplus._M_p
	mov	r8, r0	@ D.71186,
	sub	r2, r3, #12	@ D.71196, D.71193,
	cmp	r2, r6	@ D.71196, tmp169
	beq	.L239	@,
	movw	r1, #:lower16:_ZL28__gthrw___pthread_key_createPjPFvPvE	@ tmp157,
	movt	r1, #:upper16:_ZL28__gthrw___pthread_key_createPjPFvPvE	@ tmp157,
	cbz	r1, .L240	@ tmp157,
	subs	r3, r3, #4	@ tmp158, D.71193,
	dmb	sy
.L252:
	ldrex	r1, [r3]	@ D.71198,
	subs	r0, r1, #1	@ tmp174, D.71198,
	strex	lr, r0, [r3]	@ tmp175, tmp174,
	cmp	lr, #0	@ tmp175,
	bne	.L252	@,
	dmb	sy
.L241:
	cmp	r1, #0	@ D.71198,
	bgt	.L239	@,
	mov	r0, r2	@, D.71196
	add	r1, sp, #8	@,,
	bl	_ZNSs4_Rep10_M_destroyERKSaIcE	@
	b	.L239	@
.L254:
	ldr	r3, [r3, #64]	@ MEM[(struct MethodInfo * * *)_25 + 64B], MEM[(struct MethodInfo * * *)_25 + 64B]
	ldr	r3, [r3, r7]	@ D.71188, *_47
	str	r3, [r5, #72]	@ D.71188, this_6(D)->mainMethod
.L236:
	ldr	r1, [r5, #72]	@ D.71188, this_6(D)->mainMethod
	cbz	r1, .L255	@ D.71188,
	mov	r0, r5	@, this
.LEHB18:
	bl	_ZN11Interpreter8switchToEP10MethodInfo	@
	mov	r0, r5	@, this
	bl	_ZN11Interpreter10runCurrentEv	@
	movs	r0, #0	@,
	bl	exit	@
.L240:
	ldr	r1, [r3, #-4]	@ __result, MEM[(_Atomic_word *)_20 + 4294967292B]
	subs	r0, r1, #1	@ D.71186, __result,
	str	r0, [r3, #-4]	@ D.71186, MEM[(_Atomic_word *)_20 + 4294967292B]
	b	.L241	@
.L255:
	movw	r0, #:lower16:.LC9	@,
	movt	r0, #:upper16:.LC9	@,
	bl	perror	@
	movs	r0, #1	@,
	bl	exit	@
.L250:
	ldr	r0, [sp, #12]	@ D.61334._M_dataplus._M_p, D.61334._M_dataplus._M_p
	subs	r0, r0, #12	@ D.71196, D.61334._M_dataplus._M_p,
	cmp	r0, r6	@ D.71196, tmp169
	beq	.L248	@,
	add	r1, sp, #8	@,,
	bl	_ZNSs4_Rep10_M_disposeERKSaIcE.part.1	@
.L248:
	bl	__cxa_end_cleanup	@
.LEHE18:
	.personality	__gxx_personality_v0
	.handlerdata
.LLSDA2062:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2062-.LLSDACSB2062
.LLSDACSB2062:
	.uleb128 .LEHB16-.LFB2062
	.uleb128 .LEHE16-.LEHB16
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB17-.LFB2062
	.uleb128 .LEHE17-.LEHB17
	.uleb128 .L250-.LFB2062
	.uleb128 0
	.uleb128 .LEHB18-.LFB2062
	.uleb128 .LEHE18-.LEHB18
	.uleb128 0
	.uleb128 0
.LLSDACSE2062:
	.text
	.fnend
	.size	_ZN11Interpreter3runEv, .-_ZN11Interpreter3runEv
	.section	.text.startup,"ax",%progbits
	.align	2
	.thumb
	.thumb_func
	.type	_GLOBAL__sub_I__ZN11InterpreterC2EP9JavaClass, %function
_GLOBAL__sub_I__ZN11InterpreterC2EP9JavaClass:
	.fnstart
.LFB2619:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, lr}	@
	movw	r4, #:lower16:.LANCHOR0	@ tmp110,
	movt	r4, #:upper16:.LANCHOR0	@ tmp110,
	mov	r0, r4	@, tmp110
	bl	_ZNSt8ios_base4InitC1Ev	@
	movw	r1, #:lower16:_ZNSt8ios_base4InitD1Ev	@,
	movw	r2, #:lower16:__dso_handle	@,
	mov	r0, r4	@, tmp110
	movt	r1, #:upper16:_ZNSt8ios_base4InitD1Ev	@,
	movt	r2, #:upper16:__dso_handle	@,
	pop	{r4, lr}	@
	b	__aeabi_atexit	@
	.cantunwind
	.fnend
	.size	_GLOBAL__sub_I__ZN11InterpreterC2EP9JavaClass, .-_GLOBAL__sub_I__ZN11InterpreterC2EP9JavaClass
	.section	.init_array,"aw"
	.align	2
	.word	_GLOBAL__sub_I__ZN11InterpreterC2EP9JavaClass
	.weakref	_ZL28__gthrw___pthread_key_createPjPFvPvE,__pthread_key_create
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	.ascii	"bipush\000"
	.space	1
.LC1:
	.ascii	" #\000"
	.space	1
.LC2:
	.ascii	"invokevirtual\000"
	.space	2
.LC3:
	.ascii	"ldc\000"
.LC4:
	.ascii	"ldc #\000"
	.space	2
.LC5:
	.ascii	", data=\000"
.LC6:
	.ascii	"cannot decode \000"
	.space	1
.LC7:
	.ascii	" \000"
	.space	2
.LC8:
	.ascii	"main\000"
	.space	3
.LC9:
	.ascii	"Main method not fount\000"
	.bss
	.align	2
.LANCHOR0 = . + 0
	.type	_ZStL8__ioinit, %object
	.size	_ZStL8__ioinit, 1
_ZStL8__ioinit:
	.space	1
	.hidden	__dso_handle
	.ident	"GCC: (Debian 4.9.2-10) 4.9.2"
	.section	.note.GNU-stack,"",%progbits
