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
import java.io.IOException;

public class closeRFile implements IStmt{
    Exp fileName;
    String fileNameForToString;
    public closeRFile(Exp file_name){
        this.fileName = file_name;
    }
    public PrgState execute(PrgState state) throws MyException{

        MyIDictionary<String, BufferedReader>fileTbl = state.getFile_table();
        MyIDictionary<String,Value>symTbl = state.getSymbols_table();
        Value fileNameEval = fileName.eval(symTbl);
        if(fileNameEval.getType().equals(new StringType())) {
            StringValue fileNameEvalAsStr = (StringValue) fileNameEval;
            String fileStr =  fileNameEvalAsStr.getVal();
            fileNameForToString = fileStr;
            if(fileTbl.isDefined(fileNameEvalAsStr.getVal())){
                BufferedReader reader = fileTbl.lookUp(fileStr);
                try {
                    reader.close();
                    fileTbl.remove(fileStr);
                }catch(IOException e){
                    System.out.println(e.getMessage());
                }
            }else throw new MyException("File is not defined");
        }else throw new MyException("File name must be a string");
        return state;
    }
    public String toString(){

        return "CloseRfile: "+fileNameForToString;
    }
}
