package model.stmt;

import customexception.MyException;
import datatypes.MyIDictionary;
import datatypes.MyIStack;
import model.PrgState;
import model.exp.Exp;
import model.type.IntType;
import model.type.StringType;
import model.value.IntValue;
import model.value.StringValue;
import model.value.Value;

import java.io.BufferedReader;
import java.io.IOException;

public class readFile implements IStmt{
    Exp fileName;
    String fileNameForToString;
    String varName;
    public readFile(Exp expr,String var_name){
        this.fileName = expr;
        this.varName = var_name;
    }
    public PrgState execute(PrgState state) throws MyException{

        MyIDictionary<String, BufferedReader>fileTbl = state.getFile_table();
        MyIDictionary<String, Value>symTbl = state.getSymbols_table();
        Value evalFileName = fileName.eval(symTbl);
        if(evalFileName.getType().equals(new StringType())){
            StringValue strEvalFileName= (StringValue) evalFileName;
            String nameOfFile = strEvalFileName.getVal();
            fileNameForToString = nameOfFile;
            if(fileTbl.isDefined(nameOfFile)){
                if(symTbl.isDefined(varName)){
                    Value valueOfvarName = symTbl.lookUp(varName);
                    if(valueOfvarName.getType().equals(new IntType())) {
                        BufferedReader reader = fileTbl.lookUp(nameOfFile);
                        try {
                            int varValue;
                            String varValueAsString = reader.readLine();
                            if (varValueAsString.isEmpty()) {
                                varValue = 0;
                            } else {
                                varValue = Integer.parseInt(varValueAsString);
                            }
                            symTbl.update(varName,new IntValue(varValue));
                        } catch (IOException e) {
                            System.out.println(e.getMessage());
                        }
                    }else throw new MyException("The variable exists and its not an integer");
                }else throw new MyException("The variable doesnt exist in the SymbolsTable");
            }else throw new MyException("File name not found");
        }else throw new MyException("File name must be a string");
        return state;
    }
    public String toString(){
        return "Read from file " + fileNameForToString;
    }
}
