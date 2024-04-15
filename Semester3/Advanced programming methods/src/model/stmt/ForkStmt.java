package model.stmt;

import customexception.MyException;
import datatypes.*;
import model.PrgState;
import model.type.RefType;
import model.type.Type;
import model.value.Value;

import java.io.BufferedReader;


public class ForkStmt implements IStmt{
    private IStmt other;
    public ForkStmt(IStmt otherStmt){
        this.other = otherStmt;
    }
    public PrgState execute(PrgState state)throws MyException{
        MyIStack<IStmt>exeStackForNewPrg = new MyStack<IStmt>();
        MyIDictionary<String, Value>symTableForNewPrg = new MyDictionary<>(state.getSymbols_table());
        MyIHeap<Integer,Value>heapForNewPrg = state.getHeap_table();
        MyIList<String>outForNewPrg = state.getOutput();
        MyIDictionary<String, BufferedReader>fileTableForNewPrg = state.getFile_table();
        MyILatchTable<Integer,Integer>latchTblForNewPRg = state.getLatchTable();
        PrgState newPrg = new PrgState(other,exeStackForNewPrg,symTableForNewPrg,outForNewPrg,fileTableForNewPrg,heapForNewPrg,latchTblForNewPRg);
        return newPrg;
    }
    public MyIDictionary<String, Type>typeCheck(MyIDictionary<String,Type>typeEnv)throws MyException{


           MyIDictionary<String,Type>typeEnv1 = other.typeCheck(typeEnv);
           return typeEnv;

    }

    public String toString(){
        return "Fork: " + this.other.toString();
    }
}
