package model.exp;

import customexception.MyException;
import datatypes.MyIDictionary;
import datatypes.MyIHeap;
import model.type.Type;
import model.value.Value;

public class ValueExp implements Exp {
    private Value value_of_exp;

    public Type typeCheck(MyIDictionary<String,Type>typeEnv)throws MyException{
        return value_of_exp.getType();
    }
    public ValueExp(Value value_to_be_assigned){
        this.value_of_exp = value_to_be_assigned;
    }
    public Value eval(MyIDictionary<String,Value> symbols_table, MyIHeap<Integer,Value> heap_table)throws MyException{
        return value_of_exp;
    }
    public String toString(){
        return value_of_exp.toString();
    }
}
