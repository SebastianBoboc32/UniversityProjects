package model.stmt;

import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

import customexception.MyException;
import datatypes.MyIDictionary;
import datatypes.MyIHeap;
import datatypes.MyILatchTable;
import model.PrgState;
import model.exp.Exp;
import model.type.IntType;
import model.type.Type;
import model.value.IntValue;
import model.value.Value;

public class newLatch implements IStmt{

    private static Lock lock = new ReentrantLock();
    String var;
    Exp exp;

    public newLatch(String var,Exp ex1){
        this.exp = ex1;
        this.var = var;
    }

    public PrgState execute(PrgState state)throws MyException{
        lock.lock();
        MyIDictionary<String,Value>symTbl = state.getSymbols_table();
        MyILatchTable<Integer,Integer>latchTbl = state.getLatchTable();
        MyIHeap<Integer,Value>heapTbl = state.getHeap_table();
        Value evaluationOfExp = exp.eval(symTbl,heapTbl);
        if(!(evaluationOfExp.getType().equals(new IntType())))
            throw new MyException("the expression must be of type int");
        else{
            latchTbl.put(latchTbl.getFirstFreeLocation(),((IntValue)evaluationOfExp).getVal());
            if(symTbl.lookForKey(var)){
                symTbl.update(var,new IntValue(latchTbl.getFirstFreeLocation()));
            }else{
                throw new MyException("Variable not in symbols table");
            }
        }
        lock.unlock();
        return null;
    }
    public MyIDictionary<String, Type> typeCheck(MyIDictionary<String,Type>typeEnv)throws MyException{
        if(!typeEnv.lookUp(var).equals(new IntType()))
            throw new MyException("Value is not an integer");
        if(!exp.typeCheck(typeEnv).equals(new IntType()))
            throw new MyException("Expression doesnt evaluate to an integer");
        return typeEnv;
    }

    public String toString(){
        return "newLatch( "+ var +"," + exp.toString() +");";
    }
}
