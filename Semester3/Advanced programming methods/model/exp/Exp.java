package model.exp;

import customexception.MyException;
import datatypes.MyIDictionary;
import model.value.Value;

public interface Exp {
    Value eval(MyIDictionary<String,Value>symbols_table)throws MyException;
    public String toString();
}
