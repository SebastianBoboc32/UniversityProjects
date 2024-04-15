package model.stmt;

import customexception.MyException;
import datatypes.MyIDictionary;
import datatypes.MyIHeap;
import model.PrgState;
import model.exp.Exp;
import model.type.BoolType;
import model.type.Type;
import model.value.BoolValue;
import model.value.Value;

public class condAssignment implements IStmt{

    Exp exp1,exp2,exp3;
    String var;

    public condAssignment(Exp e1,Exp e2,Exp e3,String var){
        this.exp1 = e1;
        this.exp2 = e2;
        this.exp3 = e3;
        this.var = var;
    }

    public PrgState execute(PrgState state)throws MyException{
        MyIDictionary<String,Value>symTbl = state.getSymbols_table();
        MyIHeap<Integer,Value>heapTbl = state.getHeap_table();
        if(!symTbl.lookForKey(var))
            throw new MyException("Trying to assign a value to an undefined variable");
        else{
            Value evalOfExp1 = exp1.eval(symTbl,heapTbl);
            if(!evalOfExp1.getType().equals(new BoolType()))
                throw new MyException("Value must be a boolean");
            else{
                boolean condFullfiled = ((BoolValue)evalOfExp1).getVal();
                if(condFullfiled){
                    Value evalOfExp2 = exp2.eval(symTbl,heapTbl);
                    symTbl.update(var,evalOfExp2);
                }
                else{
                    Value evalOfExp3 = exp3.eval(symTbl,heapTbl);
                    symTbl.update(var,evalOfExp3);
                }
            }
        }
        return null;
    }
    public MyIDictionary<String, Type> typeCheck(MyIDictionary<String,Type>typeEnv)throws MyException{

        if(!exp1.typeCheck(typeEnv).equals(new BoolType()))
            throw new MyException("Condition doesnt evaluate to a bool");
        else if(! (typeEnv.lookUp(var).equals( exp2.typeCheck(typeEnv))) || ! (typeEnv.lookUp(var).equals(exp3.typeCheck(typeEnv))))
            throw new MyException("Trying to assign a value of different type then v");

        return typeEnv;
    }

    public String toString(){
        return var + "=" + exp1.toString()+ "?"+exp2.toString() +":"+exp3.toString();
    }
}
