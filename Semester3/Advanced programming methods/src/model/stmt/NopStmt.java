package model.stmt;

import customexception.MyException;
import datatypes.MyIDictionary;
import model.PrgState;
import model.type.RefType;
import model.type.Type;

public class NopStmt implements IStmt {
    public PrgState execute(PrgState state)throws MyException{
        return null;
    }

    public MyIDictionary<String, Type> typeCheck(MyIDictionary<String,Type>typeEnv)throws MyException{
        return typeEnv;
    }

    public String toString(){
        return "";
    }
}
