package repository;
import customexception.MyException;
import datatypes.*;
import model.*;

import java.util.List;

public interface MyIRepository {
    public PrgState getPrgState();
     void addState(PrgState toBeAdded);
    List<PrgState>getPrgList();
     void setPrgList(List<PrgState> newStates);

     void logPrgStateExec(PrgState state) throws MyException;
}
