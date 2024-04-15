package model.stmt;

import customexception.MyException;
import datatypes.MyIDictionary;
import datatypes.MyIStack;
import model.*;
import model.exp.Exp;
import model.type.Type;
import model.value.Value;

public class AssignStmt implements IStmt {
     private String key;
     private Exp expression;
     public AssignStmt(String id,Exp exp){
         this.key = id;
         this.expression = exp;
     }
     public String toString(){
         return this.key + "="+this.expression;
     }
    public PrgState execute(PrgState state)throws MyException{
        MyIDictionary<String, Value>symbols = state.getSymbols_table();
        if(symbols.isDefined(key)){
            Value val = expression.eval(symbols,state.getHeap_table());
            Type typId = (symbols.lookUp(key)).getType();
            if(val.getType().equals(typId)){
                symbols.update(key,val);

            }
            else throw new MyException("declared type of variable " + key + " and type of the assigned expression do not match");
        }else throw new MyException("The used variable "+ key + "was not declared before");
        return null;
    }

    public MyIDictionary<String, Type>typeCheck(MyIDictionary<String,Type>typeEnv)throws MyException{

             Type typeVar = typeEnv.lookUp(key);

                 Type typeExp = this.expression.typeCheck(typeEnv);
                 if(typeExp.equals(typeVar)){
                     return typeEnv;
                 }else{
                     throw new MyException("The lhs and rhs of the assignment have different types");
                 }


    }

}
