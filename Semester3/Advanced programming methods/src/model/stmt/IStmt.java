package model.stmt;

import customexception.MyException;
import datatypes.MyIDictionary;
import model.PrgState;
import model.type.Type;

public interface IStmt {
    PrgState execute(PrgState state)throws MyException;
    MyIDictionary<String, Type>typeCheck(MyIDictionary<String,Type>typeEnv)throws MyException;
}
