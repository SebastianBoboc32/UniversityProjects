package model.stmt;

import customexception.MyException;
import datatypes.MyIDictionary;
import datatypes.MyILatchTable;
import model.PrgState;
import model.type.IntType;
import model.type.Type;
import model.value.IntValue;
import model.value.Value;

import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class countDown implements IStmt{

    String var;
    private static Lock lock = new ReentrantLock();

    public countDown(String s){
        this.var = s;
    }
    public PrgState execute(PrgState state)throws MyException{
        lock.lock();
        MyIDictionary<String, Value>symTbl = state.getSymbols_table();
        MyILatchTable<Integer,Integer>latchTbl = state.getLatchTable();
        Value foundIndex = symTbl.lookUp(var);
        if(foundIndex == null || !(foundIndex.getType().equals(new IntType()))){
            throw new MyException("Variable not integer or not defined");
        }
        else{
            if(!latchTbl.lookForKey(((IntValue)foundIndex).getVal()))
                throw new MyException("Variable is not an index in the latch table");
            Integer valueInLatchTbl = latchTbl.lookUp(((IntValue)foundIndex).getVal());
            if(valueInLatchTbl > 0){
                latchTbl.update(((IntValue)foundIndex).getVal(),valueInLatchTbl-1);
                state.getOutput().add(((Integer)state.getId()).toString());
            }
            else{
                state.getOutput().add(((Integer)state.getId()).toString());
            }
        }
        lock.unlock();
        return null;
    }
    public MyIDictionary<String, Type> typeCheck(MyIDictionary<String,Type>typeEnv)throws MyException{
        if(!typeEnv.lookUp(var).equals(new IntType()))
            throw new MyException("Var must be of type int");
        return typeEnv;
    }

    public String toString(){
        return "countdown("+var+");";
    }
}
