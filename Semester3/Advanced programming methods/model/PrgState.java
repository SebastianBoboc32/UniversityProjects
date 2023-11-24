package model;
import datatypes.*;
import model.stmt.IStmt;
import model.value.Value;

import java.io.BufferedReader;
import java.util.Set;

public class PrgState {
    private MyIStack<IStmt>execution_stack;
    private MyIDictionary<String, Value>symbols_table;



    private MyIDictionary<String, BufferedReader>file_table;
    private MyIList<String>output;

    public PrgState(IStmt prg,MyIStack<IStmt>exe_stack,MyIDictionary<String,Value>symtbl,MyIList<String>out,MyIDictionary<String,BufferedReader>fltbl){
        this.execution_stack = exe_stack;
        this.symbols_table = symtbl;
        this.output = out;
        this.file_table = fltbl;
        exe_stack.push(prg);
    }

    public MyIDictionary<String, Value> getSymbols_table() {
        return symbols_table;
    }

    public MyIList<String> getOutput() {
        return output;
    }

    public MyIDictionary<String,BufferedReader>getFile_table(){
        return this.file_table;
    }

    public MyIStack<IStmt> getExecution_stack() {
        return execution_stack;
    }
    void setSymbols_table(MyDictionary<String,Value>sym_table){
        this.symbols_table = sym_table;
    }
    void setExecution_stack(MyStack<IStmt>exe_stack){
        this.execution_stack = exe_stack;
    }
    void setOutput(MyList<String> out){
        this.output = out;
    }

    public void setFile_table(MyIDictionary<String, BufferedReader> file_table) {
        this.file_table = file_table;
    }

    public String toString(){
        String result = "Execution Stack \n "+this.execution_stack +"Symbols Table \n"+ this.symbols_table+
                "Out\n" + this.output;
        result += "File Table\n";
        Set<String> keysOfFileTable = this.file_table.keySet();
        for(String currentKey : keysOfFileTable) {
            result += currentKey;
            result += "\n";
        }
        return result;
    }
}
