package model.exp;

import customexception.MyException;
import datatypes.MyIDictionary;
import datatypes.MyIHeap;
import model.type.StringType;
import model.type.Type;
import model.value.Value;

public class VarExp implements Exp {
    private String key;
    public VarExp(String k){
        this.key = k;
    }
    public Value eval(MyIDictionary<String,Value> symbols_table, MyIHeap<Integer,Value> heap_table)throws MyException {
        return symbols_table.lookUp(key);
    }

    public Type typeCheck(MyIDictionary<String,Type>typeEnv)throws MyException{
        return typeEnv.lookUp(key);
    }
    public String toString(){
        return "key: "+key;
    }
}
