#ifndef otypes_h
#define otypes_h

#define PROGRAM 1
#define DECL_ST_1 2
#define DECL_ST_2 3
#define DECL 4
#define STRUCT_DECL 5
#define VAR_DECL_ST_1 6
#define VAR_DECL_ST_2 7
#define VAR_PART_ST_1 8
#define VAR_PART_ST_2 9
#define VAR_PART_ALL_ST_1 10
#define VAR_PART_ALL_ST_2 11
#define VAR_DECL_1 12
#define VAR_DECL_2 13
#define VAR_DECL_3 14
#define VAR_DECL_4 15
#define DEF_PART 16
#define STRUCT_PART 17
#define BASE_TYPE 18
#define VAR_PART_1 19
#define VAR_PART_2 20
#define VAR_PART_ALL_1 21
#define VAR_PART_ALL_2 22
#define VAR_PART_ALL_3 23
#define VAR_IDENT 24
#define DIM_ST_1 25
#define DIM_ST_2 26
#define ARRAY_PART 27
#define DIM 28
#define INIT_PART 29
#define CONSTANT_1 30
#define CONSTANT_2 31
#define CONSTANT_3 32
#define UNSIGNED_CONSTANT 33
#define CHAR_CONSTANT 34
#define INT_CONSTANT 35
#define COMPLEX_CONSTANT_OPT 36
#define COMPLEX_CONSTANT_ST_1 37
#define COMPLEX_CONSTANT_ST_2 38
#define COMPLEX_CONSTANT_1 39
#define COMPLEX_CONSTANT_2 40
#define FUNC_DECL 41
#define PROTOTYPE_1 42
#define PROTOTYPE_2 43
#define PROTOTYPE_3 44
#define PROTOTYPE_4 45
#define PROTOTYPE_5 46
#define PROTOTYPE_6 47
#define RET_TYPE 48
#define FUNC_IDENT 49
#define PAR_TYPE_ST_1 50
#define PAR_TYPE_ST_2 51
#define PAR_TYPE_1 52
#define PAR_TYPE_2 53
#define IMPLEMENTATION_1 54
#define IMPLEMENTATION_2 55
#define IMPLEMENTATION_3 56
#define IMPLEMENTATION_4 57
#define IMPLEMENTATION_5 58
#define IMPLEMENTATION_6 59
#define PAR_DECL_ST_1 60
#define PAR_DECL_ST_2 61
#define PAR_DECL 62
#define PAR_IDENT 63
#define BLOCK 64
#define STM_ST_1 65
#define STM_ST_2 116
#define STM 66
#define EMPTY 67
#define EXPR 68
#define BREAK 69
#define RETURN_1 70
#define RETURN_2 71
#define IF_1 72
#define IF_2 73
#define COND 74
#define SWITCH 75
#define CASE_ST_1 76
#define CASE_ST_2 77
#define CASE 78
#define CASE_LABEL_1 79
#define CASE_LABEL_2 80
#define WHILE 81
#define COMPOUND 82
#define EXPRESSION_ST_1 83
#define EXPRESSION_ST_2 84
#define EXPRESSION_1 85
#define EXPRESSION_2 86
#define EQUALITY_1 87
#define EQUALITY_2 88
#define EQUALITY_3 89
#define RELATION_1 90
#define RELATION_2 91
#define RELATION_3 92
#define RELATION_4 93
#define RELATION_5 94
#define SHIFT_1 95
#define SHIFT_2 96
#define SHIFT_3 97
#define ADD_SUB_1 98
#define ADD_SUB_2 99
#define ADD_SUB_3 100
#define MULT_DIV_1 101
#define MULT_DIV_2 102
#define MULT_DIV_3 103
#define MULT_DIV_4 104
#define PRIMITIVE_1 105
#define PRIMITIVE_2 106
#define PRIMITIVE_3 107
#define PRIMITIVE_4 108
#define OPERAND 109
#define VARIABLE 110
#define QUALIFYING_1 111
#define QUALIFYING_2 112
#define QUALIFYING_3 113
#define FUNCTION_CALL_1 114
#define FUNCTION_CALL_2 115
#define EPSILON 117
#define IDENTIFIER 118
#define FLOAT_CONSTANT 119
#define FUNC_START 120 // Beschmuh-Symbol um rechtzeitig festzustellen wann eine func-decl beginnt
#define ELSE 121 // nochn Beschmuh-Symbol fuer das label beim else
#define WHILE_COND 122 // nochn Beschmuh-Symbol um festzustellen, ob das cond zu einem while gehoert

#define SWITCH_COND 123 // nochn Beschmuh-Symbol um festzustellen, ob das cond zu einem switch gehoert

#define COND_START 124 // nochn Beschmuh-Symbol um festzustellen, wo ein cond beginnt
#define SWITCH_START 125

#define FUNCTION_CALL_INT_OUT 126
#define FUNCTION_CALL_CHAR_OUT 127
#define FUNCTION_CALL_LONG_OUT 128
#define FUNCTION_CALL_FLOAT_OUT 129
#define FUNCTION_CALL_INT_IN 130
#define FUNCTION_CALL_CHAR_IN 131
#define FUNCTION_CALL_LONG_IN 132
#define FUNCTION_CALL_FLOAT_IN 133


// maximale Bezeichnerlänge mit Block-ID
#define VAR_LENGTH_ID 64

// maximale Bezeichnerlänge ohne Block-ID
#define VAR_LENGTH 48

// maximale Anzahl Variablen
#define MAX_NO_OF_VARIABLES 4096

// maximale Anzahl Funtionen
#define MAX_NO_OF_FUNCTIONS 4096

#define MAX_NO_OF_CONSTANTS 4096

// maximale Anzahl Case-Labels
#define MAX_NO_OF_CASE_LABELS 4096

// maximale Anzahl Parameter
#define MAX_NO_OF_PARAMETERS 16




struct TNode
{
	struct TNode* n1;
	struct TNode* n2;
	struct TNode* n3;
	struct TNode* n4;
	struct TNode* n5;
	int type;
};

enum TType {
    schar,
    sint,
    slong,
    sfloat,
    svoid,
    sstruct,
    undeclared
};

enum TOperandType 
{
	temp,
	lvar,  // lokale Variable
	gvar,  // globale 
	constant,
	labelstring,
	funclabel
};

struct TOperand
{
	TOperandType type;
	TType vtype;
	union 
	{
		char* label;
		unsigned add;
	};
	unsigned no;
};

struct TOp
{
	int TOpType;
	TOperand* operand1;
	TOperand* operand2;
	TOperand* operand3;
};




enum	TOpType {
    mov_,
    jmpgr_,	// greater zero
    jmple_,	// less zero
    jmpeq_,	// equal zero
    jmpne_,	// not equal
    mult_,
    divi_,
    mod_,
    add_,
    sub_,
    shiftl_,
    shiftr_,
    sminus_,
    splus_,
    call_,
    goto_,
    label_,
    ret_,
    getret_,
    push_,
    char_,
    int_,
    long_,
    float_,
    intout,
    charout,
    longout,
    floatout,
    intin,
    charin,
    longin,
    floatin,
    stop
};

enum TJmp {
    jmpgr,
    jmple,
    jmpeq,
    jmpne,
};


enum TBinOp {
    mult,
    divi,
    mod,
    add,
    sub,
    shiftl,
    shiftr
};

enum TUnOp {
    sminus,
    splus

};


enum TReg {
	r0,
	r1,
	r2,
	r3,
	r4,
	r5,
	r6,
	r7,
	r8,
	r9,
	r10,
	r11,
	rglobal, // startadresse fuer globale Variablen
	rlb,     // lokale basis
	rnull,  // Nullregister
	rsp,  // Stackpointer
	unknown  // Fehler
};
	


#endif
