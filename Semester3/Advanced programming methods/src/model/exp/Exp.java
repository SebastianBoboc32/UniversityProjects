package model.exp;

import customexception.MyException;
import datatypes.MyIDictionary;
import datatypes.MyIHeap;
import model.type.Type;
import model.value.Value;

public interface Exp {

    Type typeCheck(MyIDictionary<String,Type>typeEnv) throws MyException;
    Value eval(MyIDictionary<String,Value>symbols_table, MyIHeap<Integer,Value>heap_table)throws MyException;
    public String toString();
}
