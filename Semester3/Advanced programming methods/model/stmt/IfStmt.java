package model.stmt;

import customexception.MyException;
import datatypes.MyIDictionary;
import datatypes.MyIStack;
import model.*;
import model.exp.Exp;
import model.type.BoolType;
import model.type.Type;
import model.value.BoolValue;
import model.value.Value;

public class IfStmt implements IStmt {
    Exp expression;

    IStmt thenS;
    IStmt elseS;
    public IfStmt(Exp e1,IStmt statement1,IStmt statement2){
        this.expression = e1;
        this.thenS = statement1;
        this.elseS = statement2;
    }
    public String toString(){
        return "IF("+expression.toString()+")THEN("+ thenS.toString()+"ELSE("+elseS.toString()+")";
    }
    public PrgState execute(PrgState state) throws MyException{
        MyIDictionary<String, Value>symtbl = state.getSymbols_table();
        MyIStack<IStmt>stack = state.getExecution_stack();
        Value expression_eval = expression.eval(symtbl);
        Type type_of_expression_eval = expression_eval.getType();
        if(type_of_expression_eval.equals(new BoolType())){
            boolean value_of_evaluation = ((BoolValue) expression_eval).getVal();
            if(value_of_evaluation){
                stack.push(thenS);
            }
            else{
                stack.push(elseS);
            }
        }else throw new MyException("The if condition must be of type bool");
        return state;
    }
    public Exp getExpression(){
        return expression;
    }
    public IStmt getThenS(){
        return thenS;
    }
    public IStmt getElseS(){
        return elseS;
    }
    public void setExpression(Exp newExp){
        expression = newExp;
    }
    public void setThenS(IStmt newThenS){
        thenS = newThenS;
    }
    public void setElseS(IStmt newElseS){
        elseS = newElseS;
    }
}
