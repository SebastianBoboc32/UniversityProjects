package model.stmt;

import customexception.MyException;
import model.PrgState;

public interface IStmt {
    PrgState execute(PrgState state)throws MyException;
}
