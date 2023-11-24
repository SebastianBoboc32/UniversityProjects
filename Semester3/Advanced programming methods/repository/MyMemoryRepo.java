package repository;

import customexception.MyException;
import datatypes.MyIDictionary;
import datatypes.MyIList;
import datatypes.MyIStack;
import datatypes.MyList;
import model.PrgState;
import model.stmt.IStmt;
import model.value.Value;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Set;

public class MyMemoryRepo implements MyIRepository{
    MyIList<PrgState>states;

    String logFilePath;

    public String getLogFilePath() {
        return logFilePath;
    }

    public void setLogFilePath(String logFilePath) {
        this.logFilePath = logFilePath;
    }

    public MyMemoryRepo(String filePath){

        states = new MyList<>();
        this.logFilePath = filePath;
    }
    public void addState(PrgState toBeAdded){
        this.states.add(toBeAdded);
    }
    public PrgState getPrgState(){
        return this.states.get(0);
    }

    public String getOutput(){
        return this.states.get(0).getOutput().toString();
    }

    public String toString(){
        return states.toString();
    }
    public void logPrgStateExec() throws MyException{
        try {
            PrintWriter logFile = new PrintWriter(new BufferedWriter(new FileWriter(logFilePath, true)));
            logFile.write(getPrgState().toString());
            logFile.close();
        }catch(IOException e) {
            System.out.println(e.getMessage());
        }

    }
}
