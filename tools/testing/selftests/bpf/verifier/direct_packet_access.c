{
	"pkt_end - pkt_start is allowed",
	.insns = {
		BPF_LDX_MEM(BPF_W, BPF_REG_0, BPF_REG_1,
			    offsetof(struct __sk_buff, data_end)),
		BPF_LDX_MEM(BPF_W, BPF_REG_2, BPF_REG_1,
			    offsetof(struct __sk_buff, data)),
		BPF_ALU64_REG(BPF_SUB, BPF_REG_0, BPF_REG_2),
		BPF_EXIT_INSN(),
	},
	.result = ACCEPT,
	.retval = TEST_DATA_LEN,
	.prog_type = BPF_PROG_TYPE_SCHED_CLS,
},
{
	"direct packet access: test1",
	.insns = {
	BPF_LDX_MEM(BPF_W, BPF_REG_2, BPF_REG_1,
		    offsetof(struct __sk_buff, data)),
	BPF_LDX_MEM(BPF_W, BPF_REG_3, BPF_REG_1,
		    offsetof(struct __sk_buff, data_end)),
	BPF_MOV64_REG(BPF_REG_0, BPF_REG_2),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_0, 8),
	BPF_JMP_REG(BPF_JGT, BPF_REG_0, BPF_REG_3, 1),
	BPF_LDX_MEM(BPF_B, BPF_REG_0, BPF_REG_2, 0),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),
	},
	.result = ACCEPT,
	.prog_type = BPF_PROG_TYPE_SCHED_CLS,
},
{
	"direct packet access: test2",
	.insns = {
	BPF_MOV64_IMM(BPF_REG_0, 1),
	BPF_LDX_MEM(BPF_W, BPF_REG_4, BPF_REG_1,
		    offsetof(struct __sk_buff, data_end)),
	BPF_LDX_MEM(BPF_W, BPF_REG_3, BPF_REG_1,
		    offsetof(struct __sk_buff, data)),
	BPF_MOV64_REG(BPF_REG_5, BPF_REG_3),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_5, 14),
	BPF_JMP_REG(BPF_JGT, BPF_REG_5, BPF_REG_4, 15),
	BPF_LDX_MEM(BPF_B, BPF_REG_0, BPF_REG_3, 7),
	BPF_LDX_MEM(BPF_B, BPF_REG_4, BPF_REG_3, 12),
	BPF_ALU64_IMM(BPF_MUL, BPF_REG_4, 14),
	BPF_LDX_MEM(BPF_W, BPF_REG_3, BPF_REG_1,
		    offsetof(struct __sk_buff, data)),
	BPF_ALU64_REG(BPF_ADD, BPF_REG_3, BPF_REG_4),
	BPF_LDX_MEM(BPF_W, BPF_REG_2, BPF_REG_1,
		    offsetof(struct __sk_buff, len)),
	BPF_ALU64_IMM(BPF_LSH, BPF_REG_2, 49),
	BPF_ALU64_IMM(BPF_RSH, BPF_REG_2, 49),
	BPF_ALU64_REG(BPF_ADD, BPF_REG_3, BPF_REG_2),
	BPF_MOV64_REG(BPF_REG_2, BPF_REG_3),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_2, 8),
	BPF_LDX_MEM(BPF_W, BPF_REG_1, BPF_REG_1,
		    offsetof(struct __sk_buff, data_end)),
	BPF_JMP_REG(BPF_JGT, BPF_REG_2, BPF_REG_1, 1),
	BPF_LDX_MEM(BPF_B, BPF_REG_1, BPF_REG_3, 4),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),
	},
	.result = ACCEPT,
	.prog_type = BPF_PROG_TYPE_SCHED_CLS,
},
{
	"direct packet access: test3",
	.insns = {
	BPF_LDX_MEM(BPF_W, BPF_REG_2, BPF_REG_1,
		    offsetof(struct __sk_buff, data)),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),
	},
	.errstr = "invalid bpf_context access off=76",
	.result = REJECT,
	.prog_type = BPF_PROG_TYPE_SOCKET_FILTER,
},
{
	"direct packet access: test4 (write)",
	.insns = {
	BPF_LDX_MEM(BPF_W, BPF_REG_2, BPF_REG_1,
		    offsetof(struct __sk_buff, data)),
	BPF_LDX_MEM(BPF_W, BPF_REG_3, BPF_REG_1,
		    offsetof(struct __sk_buff, data_end)),
	BPF_MOV64_REG(BPF_REG_0, BPF_REG_2),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_0, 8),
	BPF_JMP_REG(BPF_JGT, BPF_REG_0, BPF_REG_3, 1),
	BPF_STX_MEM(BPF_B, BPF_REG_2, BPF_REG_2, 0),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),
	},
	.result = ACCEPT,
	.prog_type = BPF_PROG_TYPE_SCHED_CLS,
},
{
	"direct packet access: test5 (pkt_end >= reg, good access)",
	.insns = {
	BPF_LDX_MEM(BPF_W, BPF_REG_2, BPF_REG_1,
		    offsetof(struct __sk_buff, data)),
	BPF_LDX_MEM(BPF_W, BPF_REG_3, BPF_REG_1,
		    offsetof(struct __sk_buff, data_end)),
	BPF_MOV64_REG(BPF_REG_0, BPF_REG_2),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_0, 8),
	BPF_JMP_REG(BPF_JGE, BPF_REG_3, BPF_REG_0, 2),
	BPF_MOV64_IMM(BPF_REG_0, 1),
	BPF_EXIT_INSN(),
	BPF_LDX_MEM(BPF_B, BPF_REG_0, BPF_REG_2, 0),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),
	},
	.result = ACCEPT,
	.prog_type = BPF_PROG_TYPE_SCHED_CLS,
},
{
	"direct packet access: test6 (pkt_end >= reg, bad access)",
	.insns = {
	BPF_LDX_MEM(BPF_W, BPF_REG_2, BPF_REG_1,
		    offsetof(struct __sk_buff, data)),
	BPF_LDX_MEM(BPF_W, BPF_REG_3, BPF_REG_1,
		    offsetof(struct __sk_buff, data_end)),
	BPF_MOV64_REG(BPF_REG_0, BPF_REG_2),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_0, 8),
	BPF_JMP_REG(BPF_JGE, BPF_REG_3, BPF_REG_0, 3),
	BPF_LDX_MEM(BPF_B, BPF_REG_0, BPF_REG_2, 0),
	BPF_MOV64_IMM(BPF_REG_0, 1),
	BPF_EXIT_INSN(),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),
	},
	.errstr = "invalid access to packet",
	.result = REJECT,
	.prog_type = BPF_PROG_TYPE_SCHED_CLS,
},
{
	"direct packet access: test7 (pkt_end >= reg, both accesses)",
	.insns = {
	BPF_LDX_MEM(BPF_W, BPF_REG_2, BPF_REG_1,
		    offsetof(struct __sk_buff, data)),
	BPF_LDX_MEM(BPF_W, BPF_REG_3, BPF_REG_1,
		    offsetof(struct __sk_buff, data_end)),
	BPF_MOV64_REG(BPF_REG_0, BPF_REG_2),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_0, 8),
	BPF_JMP_REG(BPF_JGE, BPF_REG_3, BPF_REG_0, 3),
	BPF_LDX_MEM(BPF_B, BPF_REG_0, BPF_REG_2, 0),
	BPF_MOV64_IMM(BPF_REG_0, 1),
	BPF_EXIT_INSN(),
	BPF_LDX_MEM(BPF_B, BPF_REG_0, BPF_REG_2, 0),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),
	},
	.errstr = "invalid access to packet",
	.result = REJECT,
	.prog_type = BPF_PROG_TYPE_SCHED_CLS,
},
{
	"direct packet access: test8 (double test, variant 1)",
	.insns = {
	BPF_LDX_MEM(BPF_W, BPF_REG_2, BPF_REG_1,
		    offsetof(struct __sk_buff, data)),
	BPF_LDX_MEM(BPF_W, BPF_REG_3, BPF_REG_1,
		    offsetof(struct __sk_buff, data_end)),
	BPF_MOV64_REG(BPF_REG_0, BPF_REG_2),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_0, 8),
	BPF_JMP_REG(BPF_JGE, BPF_REG_3, BPF_REG_0, 4),
	BPF_JMP_REG(BPF_JGT, BPF_REG_0, BPF_REG_3, 1),
	BPF_LDX_MEM(BPF_B, BPF_REG_0, BPF_REG_2, 0),
	BPF_MOV64_IMM(BPF_REG_0, 1),
	BPF_EXIT_INSN(),
	BPF_LDX_MEM(BPF_B, BPF_REG_0, BPF_REG_2, 0),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),
	},
	.result = ACCEPT,
	.prog_type = BPF_PROG_TYPE_SCHED_CLS,
},
{
	"direct packet access: test9 (double test, variant 2)",
	.insns = {
	BPF_LDX_MEM(BPF_W, BPF_REG_2, BPF_REG_1,
		    offsetof(struct __sk_buff, data)),
	BPF_LDX_MEM(BPF_W, BPF_REG_3, BPF_REG_1,
		    offsetof(struct __sk_buff, data_end)),
	BPF_MOV64_REG(BPF_REG_0, BPF_REG_2),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_0, 8),
	BPF_JMP_REG(BPF_JGE, BPF_REG_3, BPF_REG_0, 2),
	BPF_MOV64_IMM(BPF_REG_0, 1),
	BPF_EXIT_INSN(),
	BPF_JMP_REG(BPF_JGT, BPF_REG_0, BPF_REG_3, 1),
	BPF_LDX_MEM(BPF_B, BPF_REG_0, BPF_REG_2, 0),
	BPF_LDX_MEM(BPF_B, BPF_REG_0, BPF_REG_2, 0),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),
	},
	.result = ACCEPT,
	.prog_type = BPF_PROG_TYPE_SCHED_CLS,
},
{
	"direct packet access: test10 (write invalid)",
	.insns = {
	BPF_LDX_MEM(BPF_W, BPF_REG_2, BPF_REG_1,
		    offsetof(struct __sk_buff, data)),
	BPF_LDX_MEM(BPF_W, BPF_REG_3, BPF_REG_1,
		    offsetof(struct __sk_buff, data_end)),
	BPF_MOV64_REG(BPF_REG_0, BPF_REG_2),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_0, 8),
	BPF_JMP_REG(BPF_JGT, BPF_REG_0, BPF_REG_3, 2),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),
	BPF_STX_MEM(BPF_B, BPF_REG_2, BPF_REG_2, 0),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),
	},
	.errstr = "invalid access to packet",
	.result = REJECT,
	.prog_type = BPF_PROG_TYPE_SCHED_CLS,
},
{
	"direct packet access: test11 (shift, good access)",
	.insns = {
	BPF_LDX_MEM(BPF_W, BPF_REG_2, BPF_REG_1,
		    offsetof(struct __sk_buff, data)),
	BPF_LDX_MEM(BPF_W, BPF_REG_3, BPF_REG_1,
		    offsetof(struct __sk_buff, data_end)),
	BPF_MOV64_REG(BPF_REG_0, BPF_REG_2),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_0, 22),
	BPF_JMP_REG(BPF_JGT, BPF_REG_0, BPF_REG_3, 8),
	BPF_MOV64_IMM(BPF_REG_3, 144),
	BPF_MOV64_REG(BPF_REG_5, BPF_REG_3),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_5, 23),
	BPF_ALU64_IMM(BPF_RSH, BPF_REG_5, 3),
	BPF_MOV64_REG(BPF_REG_6, BPF_REG_2),
	BPF_ALU64_REG(BPF_ADD, BPF_REG_6, BPF_REG_5),
	BPF_MOV64_IMM(BPF_REG_0, 1),
	BPF_EXIT_INSN(),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),
	},
	.result = ACCEPT,
	.prog_type = BPF_PROG_TYPE_SCHED_CLS,
	.retval = 1,
},
{
	"direct packet access: test12 (and, good access)",
	.insns = {
	BPF_LDX_MEM(BPF_W, BPF_REG_2, BPF_REG_1,
		    offsetof(struct __sk_buff, data)),
	BPF_LDX_MEM(BPF_W, BPF_REG_3, BPF_REG_1,
		    offsetof(struct __sk_buff, data_end)),
	BPF_MOV64_REG(BPF_REG_0, BPF_REG_2),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_0, 22),
	BPF_JMP_REG(BPF_JGT, BPF_REG_0, BPF_REG_3, 8),
	BPF_MOV64_IMM(BPF_REG_3, 144),
	BPF_MOV64_REG(BPF_REG_5, BPF_REG_3),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_5, 23),
	BPF_ALU64_IMM(BPF_AND, BPF_REG_5, 15),
	BPF_MOV64_REG(BPF_REG_6, BPF_REG_2),
	BPF_ALU64_REG(BPF_ADD, BPF_REG_6, BPF_REG_5),
	BPF_MOV64_IMM(BPF_REG_0, 1),
	BPF_EXIT_INSN(),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),
	},
	.result = ACCEPT,
	.prog_type = BPF_PROG_TYPE_SCHED_CLS,
	.retval = 1,
},
{
	"direct packet access: test13 (branches, good access)",
	.insns = {
	BPF_LDX_MEM(BPF_W, BPF_REG_2, BPF_REG_1,
		    offsetof(struct __sk_buff, data)),
	BPF_LDX_MEM(BPF_W, BPF_REG_3, BPF_REG_1,
		    offsetof(struct __sk_buff, data_end)),
	BPF_MOV64_REG(BPF_REG_0, BPF_REG_2),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_0, 22),
	BPF_JMP_REG(BPF_JGT, BPF_REG_0, BPF_REG_3, 13),
	BPF_LDX_MEM(BPF_W, BPF_REG_3, BPF_REG_1,
		    offsetof(struct __sk_buff, mark)),
	BPF_MOV64_IMM(BPF_REG_4, 1),
	BPF_JMP_REG(BPF_JGT, BPF_REG_3, BPF_REG_4, 2),
	BPF_MOV64_IMM(BPF_REG_3, 14),
	BPF_JMP_IMM(BPF_JA, 0, 0, 1),
	BPF_MOV64_IMM(BPF_REG_3, 24),
	BPF_MOV64_REG(BPF_REG_5, BPF_REG_3),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_5, 23),
	BPF_ALU64_IMM(BPF_AND, BPF_REG_5, 15),
	BPF_MOV64_REG(BPF_REG_6, BPF_REG_2),
	BPF_ALU64_REG(BPF_ADD, BPF_REG_6, BPF_REG_5),
	BPF_MOV64_IMM(BPF_REG_0, 1),
	BPF_EXIT_INSN(),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),
	},
	.result = ACCEPT,
	.prog_type = BPF_PROG_TYPE_SCHED_CLS,
	.retval = 1,
},
{
	"direct packet access: test14 (pkt_ptr += 0, CONST_IMM, good access)",
	.insns = {
	BPF_LDX_MEM(BPF_W, BPF_REG_2, BPF_REG_1,
		    offsetof(struct __sk_buff, data)),
	BPF_LDX_MEM(BPF_W, BPF_REG_3, BPF_REG_1,
		    offsetof(struct __sk_buff, data_end)),
	BPF_MOV64_REG(BPF_REG_0, BPF_REG_2),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_0, 22),
	BPF_JMP_REG(BPF_JGT, BPF_REG_0, BPF_REG_3, 7),
	BPF_MOV64_IMM(BPF_REG_5, 12),
	BPF_ALU64_IMM(BPF_RSH, BPF_REG_5, 4),
	BPF_MOV64_REG(BPF_REG_6, BPF_REG_2),
	BPF_ALU64_REG(BPF_ADD, BPF_REG_6, BPF_REG_5),
	BPF_LDX_MEM(BPF_B, BPF_REG_0, BPF_REG_6, 0),
	BPF_MOV64_IMM(BPF_REG_0, 1),
	BPF_EXIT_INSN(),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),
	},
	.result = ACCEPT,
	.prog_type = BPF_PROG_TYPE_SCHED_CLS,
	.retval = 1,
},
{
	"direct packet access: test15 (spill with xadd)",
	.insns = {
	BPF_LDX_MEM(BPF_W, BPF_REG_2, BPF_REG_1,
		    offsetof(struct __sk_buff, data)),
	BPF_LDX_MEM(BPF_W, BPF_REG_3, BPF_REG_1,
		    offsetof(struct __sk_buff, data_end)),
	BPF_MOV64_REG(BPF_REG_0, BPF_REG_2),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_0, 8),
	BPF_JMP_REG(BPF_JGT, BPF_REG_0, BPF_REG_3, 8),
	BPF_MOV64_IMM(BPF_REG_5, 4096),
	BPF_MOV64_REG(BPF_REG_4, BPF_REG_10),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_4, -8),
	BPF_STX_MEM(BPF_DW, BPF_REG_4, BPF_REG_2, 0),
	BPF_ATOMIC_OP(BPF_DW, BPF_ADD, BPF_REG_4, BPF_REG_5, 0),
	BPF_LDX_MEM(BPF_DW, BPF_REG_2, BPF_REG_4, 0),
	BPF_STX_MEM(BPF_W, BPF_REG_2, BPF_REG_5, 0),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),
	},
	.errstr = "R2 invalid mem access 'inv'",
	.result = REJECT,
	.prog_type = BPF_PROG_TYPE_SCHED_CLS,
	.flags = F_NEEDS_EFFICIENT_UNALIGNED_ACCESS,
},
{
	"direct packet access: test16 (arith on data_end)",
	.insns = {
	BPF_LDX_MEM(BPF_W, BPF_REG_2, BPF_REG_1,
		    offsetof(struct __sk_buff, data)),
	BPF_LDX_MEM(BPF_W, BPF_REG_3, BPF_REG_1,
		    offsetof(struct __sk_buff, data_end)),
	BPF_MOV64_REG(BPF_REG_0, BPF_REG_2),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_0, 8),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_3, 16),
	BPF_JMP_REG(BPF_JGT, BPF_REG_0, BPF_REG_3, 1),
	BPF_STX_MEM(BPF_B, BPF_REG_2, BPF_REG_2, 0),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),
	},
	.errstr = "R3 pointer arithmetic on pkt_end",
	.result = REJECT,
	.prog_type = BPF_PROG_TYPE_SCHED_CLS,
},
{
	"direct packet access: test17 (pruning, alignment)",
	.insns = {
	BPF_LDX_MEM(BPF_W, BPF_REG_2, BPF_REG_1,
		    offsetof(struct __sk_buff, data)),
	BPF_LDX_MEM(BPF_W, BPF_REG_3, BPF_REG_1,
		    offsetof(struct __sk_buff, data_end)),
	BPF_LDX_MEM(BPF_W, BPF_REG_7, BPF_REG_1,
		    offsetof(struct __sk_buff, mark)),
	BPF_MOV64_REG(BPF_REG_0, BPF_REG_2),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_0, 14),
	BPF_JMP_IMM(BPF_JGT, BPF_REG_7, 1, 4),
	BPF_JMP_REG(BPF_JGT, BPF_REG_0, BPF_REG_3, 1),
	BPF_STX_MEM(BPF_W, BPF_REG_0, BPF_REG_0, -4),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_0, 1),
	BPF_JMP_A(-6),
	},
	.errstr = "misaligned packet access off 2+(0x0; 0x0)+15+-4 size 4",
	.result = REJECT,
	.prog_type = BPF_PROG_TYPE_SCHED_CLS,
	.flags = F_LOAD_WITH_STRICT_ALIGNMENT,
},
{
	"direct packet access: test18 (imm += pkt_ptr, 1)",
	.insns = {
	BPF_LDX_MEM(BPF_W, BPF_REG_2, BPF_REG_1,
		    offsetof(struct __sk_buff, data)),
	BPF_LDX_MEM(BPF_W, BPF_REG_3, BPF_REG_1,
		    offsetof(struct __sk_buff, data_end)),
	BPF_MOV64_IMM(BPF_REG_0, 8),
	BPF_ALU64_REG(BPF_ADD, BPF_REG_0, BPF_REG_2),
	BPF_JMP_REG(BPF_JGT, BPF_REG_0, BPF_REG_3, 1),
	BPF_STX_MEM(BPF_B, BPF_REG_2, BPF_REG_2, 0),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),
	},
	.result = ACCEPT,
	.prog_type = BPF_PROG_TYPE_SCHED_CLS,
},
{
	"direct packet access: test19 (imm += pkt_ptr, 2)",
	.insns = {
	BPF_LDX_MEM(BPF_W, BPF_REG_2, BPF_REG_1,
		    offsetof(struct __sk_buff, data)),
	BPF_LDX_MEM(BPF_W, BPF_REG_3, BPF_REG_1,
		    offsetof(struct __sk_buff, data_end)),
	BPF_MOV64_REG(BPF_REG_0, BPF_REG_2),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_0, 8),
	BPF_JMP_REG(BPF_JGT, BPF_REG_0, BPF_REG_3, 3),
	BPF_MOV64_IMM(BPF_REG_4, 4),
	BPF_ALU64_REG(BPF_ADD, BPF_REG_4, BPF_REG_2),
	BPF_STX_MEM(BPF_B, BPF_REG_4, BPF_REG_4, 0),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),
	},
	.result = ACCEPT,
	.prog_type = BPF_PROG_TYPE_SCHED_CLS,
},
{
	"direct packet access: test20 (x += pkt_ptr, 1)",
	.insns = {
	BPF_LDX_MEM(BPF_W, BPF_REG_2, BPF_REG_1,
		    offsetof(struct __sk_buff, data)),
	BPF_LDX_MEM(BPF_W, BPF_REG_3, BPF_REG_1,
		    offsetof(struct __sk_buff, data_end)),
	BPF_MOV64_IMM(BPF_REG_0, 0xffffffff),
	BPF_STX_MEM(BPF_DW, BPF_REG_10, BPF_REG_0, -8),
	BPF_LDX_MEM(BPF_DW, BPF_REG_0, BPF_REG_10, -8),
	BPF_ALU64_IMM(BPF_AND, BPF_REG_0, 0x7fff),
	BPF_MOV64_REG(BPF_REG_4, BPF_REG_0),
	BPF_ALU64_REG(BPF_ADD, BPF_REG_4, BPF_REG_2),
	BPF_MOV64_REG(BPF_REG_5, BPF_REG_4),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_4, 0x7fff - 1),
	BPF_JMP_REG(BPF_JGT, BPF_REG_4, BPF_REG_3, 1),
	BPF_STX_MEM(BPF_DW, BPF_REG_5, BPF_REG_4, 0),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),
	},
	.prog_type = BPF_PROG_TYPE_SCHED_CLS,
	.result = ACCEPT,
	.flags = F_NEEDS_EFFICIENT_UNALIGNED_ACCESS,
},
{
	"direct packet access: test21 (x += pkt_ptr, 2)",
	.insns = {
	BPF_LDX_MEM(BPF_W, BPF_REG_2, BPF_REG_1,
		    offsetof(struct __sk_buff, data)),
	BPF_LDX_MEM(BPF_W, BPF_REG_3, BPF_REG_1,
		    offsetof(struct __sk_buff, data_end)),
	BPF_MOV64_REG(BPF_REG_0, BPF_REG_2),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_0, 8),
	BPF_JMP_REG(BPF_JGT, BPF_REG_0, BPF_REG_3, 9),
	BPF_MOV64_IMM(BPF_REG_4, 0xffffffff),
	BPF_STX_MEM(BPF_DW, BPF_REG_10, BPF_REG_4, -8),
	BPF_LDX_MEM(BPF_DW, BPF_REG_4, BPF_REG_10, -8),
	BPF_ALU64_IMM(BPF_AND, BPF_REG_4, 0x7fff),
	BPF_ALU64_REG(BPF_ADD, BPF_REG_4, BPF_REG_2),
	BPF_MOV64_REG(BPF_REG_5, BPF_REG_4),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_4, 0x7fff - 1),
	BPF_JMP_REG(BPF_JGT, BPF_REG_4, BPF_REG_3, 1),
	BPF_STX_MEM(BPF_DW, BPF_REG_5, BPF_REG_4, 0),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),
	},
	.prog_type = BPF_PROG_TYPE_SCHED_CLS,
	.result = ACCEPT,
	.flags = F_NEEDS_EFFICIENT_UNALIGNED_ACCESS,
},
{
	"direct packet access: test22 (x += pkt_ptr, 3)",
	.insns = {
	BPF_LDX_MEM(BPF_W, BPF_REG_2, BPF_REG_1,
		    offsetof(struct __sk_buff, data)),
	BPF_LDX_MEM(BPF_W, BPF_REG_3, BPF_REG_1,
		    offsetof(struct __sk_buff, data_end)),
	BPF_MOV64_REG(BPF_REG_0, BPF_REG_2),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_0, 8),
	BPF_STX_MEM(BPF_DW, BPF_REG_10, BPF_REG_2, -8),
	BPF_STX_MEM(BPF_DW, BPF_REG_10, BPF_REG_3, -16),
	BPF_LDX_MEM(BPF_DW, BPF_REG_3, BPF_REG_10, -16),
	BPF_JMP_REG(BPF_JGT, BPF_REG_0, BPF_REG_3, 11),
	BPF_LDX_MEM(BPF_DW, BPF_REG_2, BPF_REG_10, -8),
	BPF_MOV64_IMM(BPF_REG_4, 0xffffffff),
	BPF_ATOMIC_OP(BPF_DW, BPF_ADD, BPF_REG_10, BPF_REG_4, -8),
	BPF_LDX_MEM(BPF_DW, BPF_REG_4, BPF_REG_10, -8),
	BPF_ALU64_IMM(BPF_RSH, BPF_REG_4, 49),
	BPF_ALU64_REG(BPF_ADD, BPF_REG_4, BPF_REG_2),
	BPF_MOV64_REG(BPF_REG_0, BPF_REG_4),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_0, 2),
	BPF_JMP_REG(BPF_JGT, BPF_REG_0, BPF_REG_3, 2),
	BPF_MOV64_IMM(BPF_REG_2, 1),
	BPF_STX_MEM(BPF_H, BPF_REG_4, BPF_REG_2, 0),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),
	},
	.prog_type = BPF_PROG_TYPE_SCHED_CLS,
	.result = ACCEPT,
	.flags = F_NEEDS_EFFICIENT_UNALIGNED_ACCESS,
},
{
	"direct packet access: test23 (x += pkt_ptr, 4)",
	.insns = {
	BPF_LDX_MEM(BPF_W, BPF_REG_2, BPF_REG_1,
		    offsetof(struct __sk_buff, data)),
	BPF_LDX_MEM(BPF_W, BPF_REG_3, BPF_REG_1,
		    offsetof(struct __sk_buff, data_end)),
	BPF_LDX_MEM(BPF_W, BPF_REG_0, BPF_REG_1,
		    offsetof(struct __sk_buff, mark)),
	BPF_STX_MEM(BPF_DW, BPF_REG_10, BPF_REG_0, -8),
	BPF_LDX_MEM(BPF_DW, BPF_REG_0, BPF_REG_10, -8),
	BPF_ALU64_IMM(BPF_AND, BPF_REG_0, 0xffff),
	BPF_MOV64_REG(BPF_REG_4, BPF_REG_0),
	BPF_MOV64_IMM(BPF_REG_0, 31),
	BPF_ALU64_REG(BPF_ADD, BPF_REG_0, BPF_REG_4),
	BPF_ALU64_REG(BPF_ADD, BPF_REG_0, BPF_REG_2),
	BPF_MOV64_REG(BPF_REG_5, BPF_REG_0),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_0, 0xffff - 1),
	BPF_JMP_REG(BPF_JGT, BPF_REG_0, BPF_REG_3, 1),
	BPF_STX_MEM(BPF_DW, BPF_REG_5, BPF_REG_0, 0),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),
	},
	.prog_type = BPF_PROG_TYPE_SCHED_CLS,
	.result = REJECT,
	.errstr = "invalid access to packet, off=0 size=8, R5(id=2,off=0,r=0)",
	.flags = F_NEEDS_EFFICIENT_UNALIGNED_ACCESS,
},
{
	"direct packet access: test24 (x += pkt_ptr, 5)",
	.insns = {
	BPF_LDX_MEM(BPF_W, BPF_REG_2, BPF_REG_1,
		    offsetof(struct __sk_buff, data)),
	BPF_LDX_MEM(BPF_W, BPF_REG_3, BPF_REG_1,
		    offsetof(struct __sk_buff, data_end)),
	BPF_MOV64_IMM(BPF_REG_0, 0xffffffff),
	BPF_STX_MEM(BPF_DW, BPF_REG_10, BPF_REG_0, -8),
	BPF_LDX_MEM(BPF_DW, BPF_REG_0, BPF_REG_10, -8),
	BPF_ALU64_IMM(BPF_AND, BPF_REG_0, 0xff),
	BPF_MOV64_REG(BPF_REG_4, BPF_REG_0),
	BPF_MOV64_IMM(BPF_REG_0, 64),
	BPF_ALU64_REG(BPF_ADD, BPF_REG_0, BPF_REG_4),
	BPF_ALU64_REG(BPF_ADD, BPF_REG_0, BPF_REG_2),
	BPF_MOV64_REG(BPF_REG_5, BPF_REG_0),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_0, 0x7fff - 1),
	BPF_JMP_REG(BPF_JGT, BPF_REG_0, BPF_REG_3, 1),
	BPF_STX_MEM(BPF_DW, BPF_REG_5, BPF_REG_0, 0),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),
	},
	.prog_type = BPF_PROG_TYPE_SCHED_CLS,
	.result = ACCEPT,
	.flags = F_NEEDS_EFFICIENT_UNALIGNED_ACCESS,
},
{
	"direct packet access: test25 (marking on <, good access)",
	.insns = {
	BPF_LDX_MEM(BPF_W, BPF_REG_2, BPF_REG_1,
		    offsetof(struct __sk_buff, data)),
	BPF_LDX_MEM(BPF_W, BPF_REG_3, BPF_REG_1,
		    offsetof(struct __sk_buff, data_end)),
	BPF_MOV64_REG(BPF_REG_0, BPF_REG_2),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_0, 8),
	BPF_JMP_REG(BPF_JLT, BPF_REG_0, BPF_REG_3, 2),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),
	BPF_LDX_MEM(BPF_B, BPF_REG_0, BPF_REG_2, 0),
	BPF_JMP_IMM(BPF_JA, 0, 0, -4),
	},
	.result = ACCEPT,
	.prog_type = BPF_PROG_TYPE_SCHED_CLS,
},
{
	"direct packet access: test26 (marking on <, bad access)",
	.insns = {
	BPF_LDX_MEM(BPF_W, BPF_REG_2, BPF_REG_1,
		    offsetof(struct __sk_buff, data)),
	BPF_LDX_MEM(BPF_W, BPF_REG_3, BPF_REG_1,
		    offsetof(struct __sk_buff, data_end)),
	BPF_MOV64_REG(BPF_REG_0, BPF_REG_2),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_0, 8),
	BPF_JMP_REG(BPF_JLT, BPF_REG_0, BPF_REG_3, 3),
	BPF_LDX_MEM(BPF_B, BPF_REG_0, BPF_REG_2, 0),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),
	BPF_JMP_IMM(BPF_JA, 0, 0, -3),
	},
	.result = REJECT,
	.errstr = "invalid access to packet",
	.prog_type = BPF_PROG_TYPE_SCHED_CLS,
},
{
	"direct packet access: test27 (marking on <=, good access)",
	.insns = {
	BPF_LDX_MEM(BPF_W, BPF_REG_2, BPF_REG_1,
		    offsetof(struct __sk_buff, data)),
	BPF_LDX_MEM(BPF_W, BPF_REG_3, BPF_REG_1,
		    offsetof(struct __sk_buff, data_end)),
	BPF_MOV64_REG(BPF_REG_0, BPF_REG_2),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_0, 8),
	BPF_JMP_REG(BPF_JLE, BPF_REG_3, BPF_REG_0, 1),
	BPF_LDX_MEM(BPF_B, BPF_REG_0, BPF_REG_2, 0),
	BPF_MOV64_IMM(BPF_REG_0, 1),
	BPF_EXIT_INSN(),
	},
	.result = ACCEPT,
	.prog_type = BPF_PROG_TYPE_SCHED_CLS,
	.retval = 1,
},
{
	"direct packet access: test28 (marking on <=, bad access)",
	.insns = {
	BPF_LDX_MEM(BPF_W, BPF_REG_2, BPF_REG_1,
		    offsetof(struct __sk_buff, data)),
	BPF_LDX_MEM(BPF_W, BPF_REG_3, BPF_REG_1,
		    offsetof(struct __sk_buff, data_end)),
	BPF_MOV64_REG(BPF_REG_0, BPF_REG_2),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_0, 8),
	BPF_JMP_REG(BPF_JLE, BPF_REG_3, BPF_REG_0, 2),
	BPF_MOV64_IMM(BPF_REG_0, 1),
	BPF_EXIT_INSN(),
	BPF_LDX_MEM(BPF_B, BPF_REG_0, BPF_REG_2, 0),
	BPF_JMP_IMM(BPF_JA, 0, 0, -4),
	},
	.result = REJECT,
	.errstr = "invalid access to packet",
	.prog_type = BPF_PROG_TYPE_SCHED_CLS,
},
{
	"direct packet access: test29 (reg > pkt_end in subprog)",
	.insns = {
	BPF_LDX_MEM(BPF_W, BPF_REG_6, BPF_REG_1,
		    offsetof(struct __sk_buff, data)),
	BPF_LDX_MEM(BPF_W, BPF_REG_2, BPF_REG_1,
		    offsetof(struct __sk_buff, data_end)),
	BPF_MOV64_REG(BPF_REG_3, BPF_REG_6),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_3, 8),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, 0, 4),
	BPF_JMP_IMM(BPF_JEQ, BPF_REG_0, 0, 1),
	BPF_LDX_MEM(BPF_B, BPF_REG_0, BPF_REG_6, 0),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_JMP_REG(BPF_JGT, BPF_REG_3, BPF_REG_2, 1),
	BPF_MOV64_IMM(BPF_REG_0, 1),
	BPF_EXIT_INSN(),
	},
	.result = ACCEPT,
	.prog_type = BPF_PROG_TYPE_SCHED_CLS,
},
