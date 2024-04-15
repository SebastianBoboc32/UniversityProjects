package model.stmt;

import customexception.MyException;
import datatypes.MyIDictionary;
import datatypes.MyIHeap;
import model.PrgState;
import model.exp.Exp;
import model.type.RefType;
import model.type.Type;
import model.value.RefValue;
import model.value.Value;

public class NewStmt implements IStmt{

    String var_name;
    Exp expression;
    public String getVar_name() {
        return var_name;
    }

    public void setVar_name(String var_name) {
        this.var_name = var_name;
    }

    public Exp getExpression() {
        return expression;
    }

    public void setExpression(Exp expression) {
        this.expression = expression;
    }
    public NewStmt(String variable_name,Exp exp){
        this.var_name = variable_name;
        this.expression = exp;
    }
    public PrgState execute(PrgState state)throws MyException{
        MyIDictionary<String, Value>sym_table = state.getSymbols_table();
        MyIHeap<Integer,Value> heap_tbl = state.getHeap_table();
        boolean isDefined = sym_table.lookForKey(var_name);
        if(!isDefined)
            throw new MyException("Undefined key");
        else{
            Value valueOfAssignedKey = sym_table.lookUp(var_name);
            Type typeOfValue = valueOfAssignedKey.getType();
            if(!(typeOfValue instanceof RefType))
                throw new MyException("The variable exists but its type is not RefType");
            else{
                Value evaluationOfExp = expression.eval(sym_table,heap_tbl);
                if(!(evaluationOfExp.getType().equals(((RefType)sym_table.lookUp(var_name).getType()).getInner())))
                    throw new MyException("The variable and the expression aren't of the same type");
                else{
                    int firstFreeLocation = heap_tbl.getFirstFreeLocation();
                    if(firstFreeLocation == 0)
                        throw new MyException("Invalid location");
                    else{
                        heap_tbl.put(firstFreeLocation,evaluationOfExp);
                        heap_tbl.incrementFirstFreeLocation();
                        RefValue newRefv = (RefValue)valueOfAssignedKey;
                        sym_table.update(var_name,new RefValue(firstFreeLocation,((RefType)newRefv.getType()).getInner()));
                    }
                }
            }
        }
        return null;
    }

    public MyIDictionary<String, Type>typeCheck(MyIDictionary<String,Type>typeEnv)throws MyException{

                Type typevar = typeEnv.lookUp(this.var_name);
                Type typeExp = expression.typeCheck(typeEnv);
                if(typevar.equals(new RefType(typeExp))){
                    return typeEnv;
                }
                else {
                    throw new MyException("The lhs and rhs have different types");
                }

    }



    @Override
    public String toString() {
        return "NewStmt(" + var_name + '\'' +
                ", " + expression +
                ')';
    }
}
