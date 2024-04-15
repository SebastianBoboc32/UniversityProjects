package model.stmt;

import customexception.MyException;
import datatypes.MyIDictionary;
import datatypes.MyILatchTable;
import datatypes.MyIStack;
import model.PrgState;
import model.type.IntType;
import model.type.Type;
import model.value.IntValue;
import model.value.Value;

import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class awaitStmt implements IStmt{

    String var;
    private static Lock lock = new ReentrantLock();
    public awaitStmt(String v){
        this.var = v;
    }

    public PrgState execute(PrgState state)throws MyException{
        lock.lock();
        MyIDictionary<String,Value>symTbl = state.getSymbols_table();
        MyILatchTable<Integer,Integer>latchTbl = state.getLatchTable();
        Value foundIndex = symTbl.lookUp(var);
        if(foundIndex == null || (!foundIndex.getType().equals(new IntType()))){
            throw new MyException("Not found or not integer index");
        }
        else{
            Integer valueOfIndex = latchTbl.lookUp(((IntValue)foundIndex).getVal());
            if(valueOfIndex == null){
                throw new MyException("Index not found in the latch table");
            }
            else{
                if(valueOfIndex != 0){
                    state.getExecution_stack().push(this);
                }
            }
        }
        lock.unlock();
        return null;
    }
    public MyIDictionary<String, Type> typeCheck(MyIDictionary<String,Type>typeEnv)throws MyException{
        if(!typeEnv.lookUp(var).equals(new IntType()))
            throw new MyException("Var must be an integer");
        return typeEnv;
    }

    public String toString(){
        return "await("+ var+ ");";
    }

}
