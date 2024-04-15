package model.stmt;

import customexception.MyException;
import datatypes.MyIDictionary;
import datatypes.MyIStack;
import model.PrgState;
import model.type.Type;

public class CompStmt implements IStmt {
    IStmt first;
    IStmt second;
    public CompStmt(IStmt first,IStmt second){
        this.first = first;
        this.second = second;
    }
    public PrgState execute(PrgState state)throws MyException {
        MyIStack<IStmt> stk= state.getExecution_stack();
        stk.push(this.second);
        stk.push(this.first);
        return null;
    }

    public MyIDictionary<String, Type> typeCheck(MyIDictionary<String,Type>typeEnv)throws MyException{

            return this.second.typeCheck(this.first.typeCheck(typeEnv));

    }

    public String toString(){
        return "(" + first.toString() + ";"+ second.toString() + ")";
    }
    public IStmt getFirst(){
        return first;
    }
    public IStmt getSecond(){
        return second;
    }
    public void setFirst(IStmt NewFirst){
        first = NewFirst;
    }
    public void setSecond(IStmt NewSecond){
        second = NewSecond;
    }
}
