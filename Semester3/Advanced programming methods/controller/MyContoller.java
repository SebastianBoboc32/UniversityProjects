package controller;

import customexception.MyException;
import datatypes.MyIList;
import datatypes.MyIStack;
import model.stmt.IStmt;
import model.PrgState;
import repository.MyIRepository;

public class MyContoller implements MyIController{
    private MyIRepository repo;


    public MyContoller(MyIRepository repository){
        repo = repository;
    }
    public PrgState oneStep(PrgState state)throws MyException{
        MyIStack<IStmt>exestk = state.getExecution_stack();
        MyIList<String> output = state.getOutput();
        if(exestk.isEmpty())
            throw new MyException("Stack is empty,nothing to execute");
        else{
            IStmt statement_to_execute = exestk.pop();
            statement_to_execute.execute(state);
        }
        return state;
    }
    public void allSteps() throws MyException{

        PrgState state = this.repo.getPrgState();
        repo.logPrgStateExec();
        MyIStack<IStmt>exestk = state.getExecution_stack();
        if(exestk.isEmpty())
            throw new MyException("Stack is empty,nothing to execute");
        else{
            while(!exestk.isEmpty()){
                oneStep(state);

                repo.logPrgStateExec();
            }
            System.out.println(getOutputOfLastState(state));
        }
    }

    public String getOutputOfLastState(PrgState state){
        return state.getOutput().toString();
    }

}
