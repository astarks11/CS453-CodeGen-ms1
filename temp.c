/* File: compile.c
Author: Alex Starks
Path:export LD_LIBRARY_PATH=/home/cs453/spring18/stlib-a/lib*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <libstree.h>
// create struct for 3 address code
enum threeAddrType {
	Param,
	Call,
	Retrieve,
	Enter,
	Leave
};

typedef struct addrCode {
	enum threeAddrType type;
	int flag; // 1 for const
	symtabnode * src1;
	symtabnode * src2;
	symtabnode * dest;
	int num;
	char * string;
	char ch;
	struct addrCode * next;
	char * functionName;
} addrCode;

/* Function Definition */
void getMethodBody(tnode * t);
void traverseFunctionBody(tnode * t, enum threeAddrType type);
void addrCode_methodEnter(tnode * t);
void addrCode_arguments(tnode * t);
void appendToInstructionList(addrCode * newInstr);
void print_threeInstruction(addrCode * head);
addrCode * newInstr(enum threeAddrType type, symtabnode * src1, symtabnode * src2, symtabnode * dest);
addrCode * newInstrNum(enum threeAddrType type, int val);
addrCode * newInstrChar(enum threeAddrType type, char val);
addrCode * newInstrString(enum threeAddrType type, char * val);
addrCode * newInstrEnter(enum threeAddrType type, symtabnode * t);
addrCode * newInstrLeave(enum threeAddrType type, symtabnode * t);
addrCode * newInstrCall(enum threeAddrType type, symtabnode * t);
/* Variables */
struct addrCode * head = NULL;


void funCallArguments(tnode * t);
/* Function: Main
Purpose: initializes the parser. Traverses methods in the given program */
int main() {
	parser_info * curr_parse;
	int err_occurred = init_parser();
	printf("error:%d\n",err_occurred);

	for (curr_parse = next_fun(); curr_parse != NULL; curr_parse = next_fun()) {
		// create 3 address code for function call
		// get method body
		if (stree_Get_TreeNodeType(curr_parse->syntax_tree) == FunDef) {
			getMethodBody(curr_parse->syntax_tree);
		}
	}	
	return err_occurred;
} // main




/* Function: getMethodBody
Purpose: Gets the function definition body node of the given syntax tree*/
void getMethodBody(tnode * t) {
	if (stree_Get_TreeNodeType(t) == FunDef) {
		printf("Function:%s()\n",sym_Get_Name(stree_Get_FunDef_SymTabEntry(t)));

		tnode * method_body = stree_Get_FunDef_Body(t);
		// method_body is pointer to top node in method syntax tree
		// add proper 3addr code to enter method (callee)
		//addrCode_methodEnter(t);
		appendToInstructionList(newInstrEnter(Enter,stree_Get_FunDef_SymTabEntry(t)));
		traverseFunctionBody(method_body,Enter);
		appendToInstructionList(newInstrLeave(Leave,stree_Get_FunDef_SymTabEntry(t)));
		print_threeInstruction(head);
	}
} // getMethodBody

void traverseFunctionBody(tnode * t,enum threeAddrType type) {
	if (t == NULL)
		return;

	switch (stree_Get_TreeNodeType(t)) {
		case Error:
			return;
		/* Constants*/
		case Intcon:
			return;
		case Charcon:
			return;
		case Stringcon:
			return;
		/* Variables and array references */
		case Var:
			return;
		case ArraySubscript:
			return;
		/* Arithmetic operators */
		case Plus:
			return;
		case BinaryMinus:
			return;
		case Mult:
			return;
		case Div:
			return;
		case UnaryMinus:
			return;
		/* Comparison operators */
		case Equals:
			return;
		case Neq: 
			return;
		case Leq:
			return;
		case Lt:
			return;
		case Geq:
			return;
		case Gt:
			return;
		/* Logical operators */
		case LogicalAnd:
			return;
		case LogicalOr:
			return;
		case LogicalNot:
			return;
		/* Functions */
		case FunCall:
			// find/set arguments through recursion
			funCallArguments(stree_Get_FunCall_Args(t));
			// set 3addr code for function call
			printf("Fun:%s\n",sym_Get_Name(stree_Get_FunCall_Fun(t)));
			appendToInstructionList(newInstrCall(Call,stree_Get_FunCall_Fun(t)));
			return;
		/* Statements */
		case Assg:
			return;			
		case Return:
			return;
		case For:
			return;
		case While:
			return;
		case If:
			return;
		case STnodeList:
			while (t != NULL) {
				traverseFunctionBody(stree_Get_List_Head(t),type);
				t = stree_Get_List_Rest(t);
			}
			return;
		default: 
			return;
	}
} // 


void funCallArguments(tnode * t) {
	while (t != NULL) {
		tnode * tmp = stree_Get_List_Head(t);
		switch(stree_Get_TreeNodeType(tmp)) {
			case Intcon:
				printf("param Intcon:%d\n",stree_Get_Intcon(tmp)); 
				appendToInstructionList(newInstrNum(Param,stree_Get_Intcon(tmp)));
			break;
			case Stringcon:
				printf("param Stringcon:%s\n",stree_Get_Stringcon(tmp));
				appendToInstructionList(newInstrString(Param,stree_Get_Stringcon(tmp)));
			break;
			case Charcon:
				printf("param Charcon:%c\n",stree_Get_Charcon(tmp));
				appendToInstructionList(newInstrChar(Param,stree_Get_Charcon(tmp)));
			default:
				return;
		}
		t = stree_Get_List_Rest(t);
	}
} // funCallArguments

void appendToInstructionList(addrCode * newInstr) {
	addrCode * curr = head;
	addrCode ** ref = &head;
	if (curr == NULL) {
		curr = newInstr;
		*(ref) = curr;
		printf("created new instr head\n");
	} else {
		while (curr->next != NULL) {
			curr = curr->next;
		}
		curr->next = newInstr;
		printf("appended new instr\n");
	}
} // appendToInstructionList

void addrCode_functionCall(tnode * t) {

} // addrCode_functionCall
	
void addrCode_arguments(tnode * args) {
	if (stree_Get_TreeNodeType(args) == STnodeList) {
		while (args != NULL) {
			//printf("args:%s\n",stree);
			args = stree_Get_List_Rest(args);
		}
	}
} // addrCode_arguments
// NOTE: ASSUMES THIS IS THE FIRST TIME WE HAVE SEEN THIS FUNCTION
void addrCode_methodEnter(tnode * t) {
	struct addrCode * newCode = (addrCode *)malloc(sizeof(addrCode));
	newCode->type = stree_Get_TreeNodeType(t);
	newCode->dest = stree_Get_FunDef_SymTabEntry(t);
	stree_Set_AuxInfo(t,newCode);
	printf("Set: (%s)'s aux info - FunDef\n",sym_Get_Name(stree_Get_FunDef_SymTabEntry(t)));
} // addrCode_methodEnter


















addrCode * newInstr(enum threeAddrType type, symtabnode * src1, symtabnode * src2, symtabnode * dest) {
	struct addrCode * newCode = (addrCode*)malloc(sizeof(addrCode));
	newCode->type = type;
	newCode->flag = 0;
	newCode->src1 = src1;
	newCode->src2 = src2;
	newCode->dest = dest;
	newCode->next = NULL;
	return newCode;

} // newInstr
addrCode * newInstrNum(enum threeAddrType type, int val) {
	struct addrCode * newCode = (addrCode*)malloc(sizeof(addrCode));
	newCode->type = type;
	newCode->flag = 1;
	newCode->num = val;
	newCode->next = NULL;
	return newCode;
}
addrCode * newInstrChar(enum threeAddrType type, char val) {
	struct addrCode * newCode = (addrCode*)malloc(sizeof(addrCode));
	newCode->type = type;
	newCode->flag = 2;
	newCode->ch = val;
	newCode->next = NULL;
	return newCode;
}
addrCode * newInstrString(enum threeAddrType type, char * val) {
	struct addrCode * newCode = (addrCode*)malloc(sizeof(addrCode));
	newCode->type = type;
	newCode->flag = 3;
	newCode->string = val;
	newCode->next = NULL;
	return newCode;
}
addrCode * newInstrEnter(enum threeAddrType type, symtabnode * functionSymbolTable) {
	struct addrCode * newCode = (addrCode*)malloc(sizeof(addrCode));
	newCode->type = type;
	newCode->functionName = sym_Get_Name(functionSymbolTable);
	newCode->next = NULL;
	return newCode;	
}
addrCode * newInstrLeave(enum threeAddrType type, symtabnode * functionSymbolTable) {
	struct addrCode * newCode = (addrCode*)malloc(sizeof(addrCode));
	newCode->type = type;
	newCode->functionName = sym_Get_Name(functionSymbolTable);
	newCode->next = NULL;
	return newCode;	
}
addrCode * newInstrCall(enum threeAddrType type, symtabnode * t) {
	struct addrCode * newCode = (addrCode*)malloc(sizeof(addrCode));
	newCode->type = type;
	newCode->functionName = sym_Get_Name(t);
	newCode->next = NULL;
	return newCode;		
}





void print_threeInstruction(addrCode * code) {
	printf("\n----------------------- 3 addr code -----------------------\n");
	while (code != NULL) {
		switch(code->type) {
			case Enter:
				printf("Enter _%s\n",code->functionName);
				break;
			case Leave:
				printf("Leave _%s\n",code->functionName);
				break;
			case Call:
				printf("Call _%s\n",code->functionName);
				break;
			case Param:
				if (code->flag == 1) {
					printf("Param %d\n",code->num);
				} else if (code->flag == 2) {
					printf("Param %c\n",code->ch);
				} else if (code->flag == 3) {
					printf("Param %s\n",code->string);
				} else {}
			break;
			default:
			return;
		}
		code = code->next;
	}
} // print_threeInstruction