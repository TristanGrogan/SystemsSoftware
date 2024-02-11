// Tristan B Grogan
// UCFID: 5175492
// Montague COP 3402 P-Machine
// 2/1/2024

#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 500  // Size of stack and program array.

typedef struct INSTRUCTION {
    int OP; // Operation
    int L;  // Lexicographical level
    int M;  // Modifier
} INSTRUCTION; // Instruction struct

// Global variables
int BP = 499; // Base pointer
int SP = 500; // Stack pointer, BP + 1
int PC = 0; // Program counter
INSTRUCTION IR; // Instruction register, initialized to 0 0 0
int pas[ARRAY_SIZE] = {0}; // Program address store
int arStarts[ARRAY_SIZE]; // Assuming ARRAY_SIZE is defined and large enough
int arCount = 0; // Keeps track of the number of ARs

// Function to find base L levels down
int base(int BP, int L) {
    int arb = BP; // arb = activation record base
    while (L > 0) {
        arb = pas[arb];
        L--;
    }
    return arb;
}

// Print the stack
void printStack(int SP, int BP) {
    for (int i = ARRAY_SIZE - 1; i >= SP; i--) {
        // Check if this position is an AR start
        for (int j = 0; j < arCount; j++) {
            if (i == arStarts[j]) {
                printf("| ");
                break; // Found the AR start, no need to check further
            }
        }
        printf("%d ", pas[i]); // Print the value at the current position
    }
    printf("\n"); 
}

// Main function
int main(int argc, char *argv[]) {
    FILE *inputfile = fopen(argv[1], "r");
    if (inputfile == NULL) {
        printf("Error: Unable to open input file.\n");
        return 1;
    }

    // Read instructions from file
    int instructionCount = 0;
    while (fscanf(inputfile, "%d %d %d", &pas[instructionCount], &pas[instructionCount + 1], &pas[instructionCount + 2]) != EOF) {
        instructionCount += 3;
    }
    fclose(inputfile);

    // Print initial values
    printf("\t\tPC\tBP\tSP\tstack\n");
    printf("Initial values:\t%d\t%d\t%d\n\n", PC, BP, SP);

    while (PC < instructionCount) {
        // Fetch instruction
        IR.OP = pas[PC];
        IR.L = pas[PC + 1];
        IR.M = pas[PC + 2];
        // Increase PC every fetch
        PC += 3;

        // Execute instruction
        switch (IR.OP) {
            case 1: // LIT
                SP--; // Decrement SP to make space for the new value
                pas[SP] = IR.M; // Store the literal value M at the new SP location
                printf("LIT  0  %d\t%d\t%d\t%d\t", IR.M, PC, BP, SP);
                printStack(SP, BP);
                break;
            case 2: // OPR
                switch (IR.M) {
                    case 0: // RTN
                        SP = BP + 1; // Set SP to the start of the current AR
                        BP = pas[SP - 2]; // Set BP to the old BP
                        PC = pas[SP - 3]; // Set PC to the old PC
                        arCount--; // Assuming you decrement arCount to remove the AR start marker
                        printf("RTN  %d  %d\t%d\t%d\t%d\t", IR.L, IR.M, PC, BP, SP);
                        printStack(SP, BP);
                        break;
                    case 1: // ADD
                        pas[SP + 1] = pas[SP + 1] + pas[SP]; // Add the top two values on the stack
                        SP++; // Increment SP to point to the new top of the stack
                        printf("ADD  %d  %d\t%d\t%d\t%d\t", IR.L, IR.M, PC, BP, SP); 
                        printStack(SP, BP);
                        break;
                    case 2: // SUB
                        pas[SP + 1] = pas[SP + 1] - pas[SP]; // Subtract the top two values on the stack
                        SP++; // Increment SP to point to the new top of the stack
                        printf("SUB  %d  %d\t%d\t%d\t%d\t", IR.L, IR.M, PC, BP, SP);
                        printStack(SP, BP);
                        break;
                    case 3: // MUL
                        pas[SP + 1] = pas[SP + 1] * pas[SP]; // Multiply the top two values on the stack
                        SP++; // Increment SP to point to the new top of the stack
                        printf("MUL  %d  %d\t%d\t%d\t%d\t", IR.L, IR.M, PC, BP, SP);
                        printStack(SP, BP);
                        break;
                    case 4: // DIV
                        if (pas[SP] == 0) {
                            printf("Error: Division by zero.\n");
                            exit(1); // Exit or handle error as appropriate
                        }
                        pas[SP + 1] = pas[SP + 1] / pas[SP]; // Divide the top two values on the stack
                        SP++; // Increment SP to point to the new top of the stack
                        printf("DIV  %d  %d\t%d\t%d\t%d\t", IR.L, IR.M, PC, BP, SP);
                        printStack(SP, BP);
                        break;
                    case 5: // EQL
                        pas[SP + 1] = (pas[SP + 1] == pas[SP]) ? 1 : 0; // Check if the top two values on the stack are equal
                        SP++; // Increment SP to point to the new top of the stack
                        printf("EQL  %d  %d\t%d\t%d\t%d\t", IR.L, IR.M, PC, BP, SP);
                        printStack(SP, BP);
                        break;
                    case 6: // NEQ
                        pas[SP + 1] = (pas[SP + 1] != pas[SP]) ? 1 : 0; // Check if the top two values on the stack are not equal
                        SP++; // Increment SP to point to the new top of the stack
                        printf("NEQ  %d  %d\t%d\t%d\t%d\t", IR.L, IR.M, PC, BP, SP);
                        printStack(SP, BP);
                        break;
                    case 7: // LSS
                        pas[SP + 1] = (pas[SP + 1] < pas[SP]) ? 1 : 0; // Check if the top two values on the stack are less than
                        SP++; // Increment SP to point to the new top of the stack
                        printf("LSS  %d  %d\t%d\t%d\t%d\t", IR.L, IR.M, PC, BP, SP);
                        printStack(SP, BP);
                        break;
                    case 8: // LEQ
                        pas[SP + 1] = (pas[SP + 1] <= pas[SP]) ? 1 : 0; // Check if the top two values on the stack are less than or equal to
                        SP++; // Increment SP to point to the new top of the stack
                        printf("LEQ  %d  %d\t%d\t%d\t%d\t", IR.L, IR.M, PC, BP, SP);
                        printStack(SP, BP);
                        break;
                    case 9: // GTR
                        pas[SP + 1] = (pas[SP + 1] > pas[SP]) ? 1 : 0; // Check if the top two values on the stack are greater than
                        SP++; // Increment SP to point to the new top of the stack
                        printf("GTR  %d  %d\t%d\t%d\t%d\t", IR.L, IR.M, PC, BP, SP);
                        printStack(SP, BP);
                        break;
                    case 10: // GEQ
                        pas[SP + 1] = (pas[SP + 1] >= pas[SP]) ? 1 : 0; // Check if the top two values on the stack are greater than or equal to
                        SP++; // Increment SP to point to the new top of the stack
                        printf("GEQ  %d  %d\t%d\t%d\t%d\t", IR.L, IR.M, PC, BP, SP);
                        printStack(SP, BP);
                        break;
                    case 11: // ODD
                        pas[SP] = pas[SP] % 2; // Check if the top value on the stack is odd
                        printf("ODD  %d  %d\t%d\t%d\t%d\t", IR.L, IR.M, PC, BP, SP);
                        printStack(SP, BP);
                        break;
                    default: 
                        // Handle error
                        printf("Error: Invalid OPR command.\n");
                        exit(1);
                }
                break;
            case 3: // LOD 
                SP = SP - 1; // Decrement SP to make space for the new value
                pas[SP] = pas[base(BP, IR.L) - IR.M]; // Load the value from the specified location to the top of the stack
                printf("LOD  %d  %d\t%d\t%d\t%d\t", IR.L, IR.M, PC, BP, SP);
                printStack(SP, BP);
                break;
            case 4: // STO
                pas[base(BP, IR.L) - IR.M] = pas[SP]; // Store the value at the top of the stack to the specified location
                SP = SP + 1; // Increment SP to point to the next free spot
                printf("STO  %d  %d\t%d\t%d\t%d\t", IR.L, IR.M, PC, BP, SP);
                printStack(SP, BP);
                break;
            case 5: // CAL
                // Before adjusting SP in CAL
                arStarts[arCount++] = SP - 1; // Assuming SP points to the next free spot   
                pas[SP - 1] = base(BP, IR.L); // Static Link (SL)
                pas[SP - 2] = BP; // Dynamic Link (DL)
                pas[SP - 3] = PC; // Return Address (RA)
                BP = SP - 1; // BP points to the start of the new AR
                PC = IR.M; // Jump to the procedure's starting address
                printf("CAL  %d\t%d\t%d\t%d\t%d\t", IR.L, IR.M, PC, BP, SP);
                printStack(SP, BP); // Assuming printStack is adjusted to handle activation record flag
                break;
            case 6: // INC
                SP -= IR.M; // Allocate m locals on the stack
                printf("INC  %d  %d\t%d\t%d\t%d\t", IR.L, IR.M, PC, BP, SP);
                printStack(SP, BP);
                break;
            case 7: // JMP
                PC = IR.M; // Jump to address a
                printf("JMP  %d  %d\t%d\t%d\t%d\n", IR.L, IR.M, PC, BP, SP);
                break;
            case 8: // JPC 0, a
                if (pas[SP] == 0) {
                    PC = IR.M; // Jump to address a if the top of the stack is 0
                }
                SP = SP + 1; // Pop the top value from the stack regardless of the jump
                printf("JPC  %d  %d\t%d\t%d\t%d\t", IR.L, IR.M, PC, BP, SP);
                printStack(SP, BP);
                break;
            case 9: // SYS instruction for reading an integer
                switch (IR.M) {
                    case 1: // Output the value in stack[SP] as a character
                        printf("Output result is: %d\n", pas[SP]);
                        SP = SP + 1; // Pop the value after printing
                        printf("SOU  %d  %d\t%d\t%d\t%d\t", IR.L, IR.M, PC, BP, SP);
                        printStack(SP, BP);
                        break;
                    case 2: // Case for reading an integer and storing it on the stack
                        printf("Please Enter an Integer: ");
                        int input;
                        scanf("%d", &input);
                        SP--; // Decrement SP first to point to the next free spot
                        pas[SP] = input; // Store the input on the stack at the new SP location
                        printf("SIN  %d  %d\t%d\t%d\t%d\t", IR.L, IR.M, PC, BP, SP);
                        printStack(SP, BP);
                        break;
                    case 3: // Halt the program
                        printf("EOP  %d  %d\t%d\t%d\t%d\t", IR.L, IR.M, PC, BP, SP);
                        printStack(SP, BP);
                        return 0; // Use return to halt the program
                    default:
                        printf("Error: Invalid SYS command.\n");
                        exit(1);
                }
                break;
        }
    }
    return 0;
}
