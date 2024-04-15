package model;
import customexception.MyException;
import datatypes.*;
import model.stmt.IStmt;
import model.value.Value;

import java.io.BufferedReader;
import java.util.AbstractMap;
import java.util.ArrayList;
import java.util.Set;



public class PrgState {
    private MyIStack<IStmt>execution_stack;

    private MyIDictionary<String, Value>symbols_table;
    private MyIHeap<Integer,Value>heap_table;

    private MyILatchTable<Integer,Integer>latchTable;

    private  int id;
    private static int currentId = 0;

    private MyIDictionary<String, BufferedReader>file_table;
    private MyIList<String>output;

    public PrgState(IStmt prg,MyIStack<IStmt>exe_stack,MyIDictionary<String,Value>symtbl,MyIList<String>out,MyIDictionary<String,BufferedReader>fltbl
    ,MyIHeap<Integer,Value>heaptbl,MyILatchTable<Integer,Integer>latchTbl){
        this.execution_stack = exe_stack;
        this.symbols_table = symtbl;
        this.output = out;
        this.file_table = fltbl;
        this.heap_table = heaptbl;
        this.latchTable = latchTbl;
        setId();
        exe_stack.push(prg);
    }

    public int getId() {
        return id;
    }

    public MyIDictionary<String, Value> getSymbols_table() {
        return symbols_table;
    }

    public MyIHeap<Integer,Value>getHeap_table(){return heap_table;}
    public void setId(){
        this.id = currentId;
        currentId++;
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
    void setHeap_table(MyIHeap<Integer,Value>heaptbl){this.heap_table = heaptbl;}

    public void setFile_table(MyIDictionary<String, BufferedReader> file_table) {
        this.file_table = file_table;
    }

    public MyILatchTable<Integer, Integer> getLatchTable() {
        return latchTable;
    }

    public void setLatchTable(MyILatchTable<Integer, Integer> latchTable) {
        this.latchTable = latchTable;
    }


    public String toString(){
        String result = "ID: "+Integer.toString(this.id)+"\n"+ "Execution Stack \n "+this.execution_stack +"Symbols Table \n"+ this.symbols_table+
                "Out\n" + this.output + "\nHeap table \n"+this.heap_table;
        result += "File Table\n";
        Set<String> keysOfFileTable = this.file_table.keySet();
        for(String currentKey : keysOfFileTable) {
            result += currentKey;
            result += "\n";
        }
        result +='\n';
        result+='\n';
        result+='\n';
        result+='\n';
        return result;
    }
    public Boolean isNotCompleted(){
        return !this.execution_stack.isEmpty();
    }


    public PrgState oneStep()throws MyException {
        if(execution_stack.isEmpty())
            throw new MyException("Stack is empty,nothing to execute");
        IStmt statement_to_execute = execution_stack.pop();
        return statement_to_execute.execute(this);
    }

}
