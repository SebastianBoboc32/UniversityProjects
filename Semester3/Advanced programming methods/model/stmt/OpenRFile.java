package model.stmt;

import customexception.MyException;
import datatypes.MyIDictionary;
import datatypes.MyIStack;
import model.PrgState;
import model.exp.Exp;
import model.type.StringType;
import model.value.StringValue;
import model.value.Value;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;

public class OpenRFile implements IStmt{

    Exp expressionToBeEvaluated;
    String fileNameForToString;
    public OpenRFile(Exp expForConstructor){
        this.expressionToBeEvaluated = expForConstructor;
    }
    public PrgState execute(PrgState state)throws MyException{
        MyIDictionary<String,Value>symTbl = state.getSymbols_table();
        MyIDictionary<String, BufferedReader>flTbl = state.getFile_table();
        Value evaluationOfExp = this.expressionToBeEvaluated.eval(symTbl);
        if(evaluationOfExp.getType().equals(new StringType())){
            StringValue nameOfFile = (StringValue) evaluationOfExp;
            String keyForFileTable = nameOfFile.getVal();
            fileNameForToString = keyForFileTable;
            if(!flTbl.isDefined(keyForFileTable)){
                try {
                    BufferedReader fileDescriptor = new BufferedReader(new FileReader(keyForFileTable));
                    flTbl.put(keyForFileTable,fileDescriptor);
                }catch(FileNotFoundException e){
                    System.out.println(e.getMessage());
                }
            }else{
                throw new MyException("There is already a file with this name");
            }
        }else{
            throw new MyException("The file name must be a string");
        }
        return state;
    }
    public String toString(){
        return "Open the file "+fileNameForToString;
    }
}
