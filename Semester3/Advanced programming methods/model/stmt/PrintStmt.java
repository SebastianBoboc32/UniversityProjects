package model.stmt;

import customexception.MyException;
import datatypes.MyIDictionary;
import datatypes.MyIList;
import model.exp.Exp;
import model.PrgState;
import model.value.Value;

public class PrintStmt implements IStmt {
    Exp expression;

    public PrintStmt(Exp exp_to_be_printed) {
        this.expression = exp_to_be_printed;
    }

    public String toString(){
        return "print("+expression.toString()+");";
    }
    public PrgState execute(PrgState state)throws MyException{
        MyIDictionary<String, Value>symtbl = state.getSymbols_table();
        MyIList<String>out = state.getOutput();
        out.add(expression.eval(symtbl).toString());
        return state;
    }
    public Exp getExpression(){
        return expression;
    }
    public void setExpression(Exp NewExp){
        expression = NewExp;
    }
}
