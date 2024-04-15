package controller;

import customexception.MyException;
import model.PrgState;

public interface MyIController {

    void allSteps() throws MyException, InterruptedException;
}
