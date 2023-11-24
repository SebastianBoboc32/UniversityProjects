package controller;

import customexception.MyException;
import model.PrgState;

public interface MyIController {
    PrgState oneStep(PrgState state)throws MyException;
    void allSteps()throws MyException;
}
