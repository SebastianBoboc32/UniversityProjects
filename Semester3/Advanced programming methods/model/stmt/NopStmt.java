package model.stmt;

import customexception.MyException;
import model.PrgState;

public class NopStmt implements IStmt {
    public PrgState execute(PrgState state)throws MyException{
        return state;
    }
    public String toString(){
        return "";
    }
}
