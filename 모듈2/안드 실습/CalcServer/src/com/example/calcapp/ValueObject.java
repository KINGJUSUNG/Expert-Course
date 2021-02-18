package com.example.calcapp;

import java.io.Serializable;

public class ValueObject implements Serializable {
    public final static int ADD = 0;
    public final static int SUB = 1;
    public final static int MUL = 2;
    public final static int DIV = 3;

    private int op1;
    private int op2;
    private int opcode;

    public ValueObject(int op1, int op2, int opcode) {
        this.op1 = op1;
        this.op2 = op2;
        this.opcode = opcode;
    }

    public int getOp1() { return op1; }
    public int getOp2() { return op2; }
    public int getOpcode() { return opcode; }
}

