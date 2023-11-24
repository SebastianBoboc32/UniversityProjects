package repository;
import customexception.MyException;
import datatypes.*;
import model.*;
public interface MyIRepository {
    public PrgState getPrgState();
     void addState(PrgState toBeAdded);



     void logPrgStateExec() throws MyException;
}
