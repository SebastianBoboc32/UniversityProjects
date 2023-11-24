package model.exp;

import customexception.MyException;
import datatypes.MyIDictionary;
import model.value.Value;

public class VarExp implements Exp {
    private String key;
    public VarExp(String k){
        this.key = k;
    }
    public Value eval(MyIDictionary<String,Value> symbols_table)throws MyException {
        return symbols_table.lookUp(key);
    }
    public String toString(){
        return "key: "+key;
    }
}
