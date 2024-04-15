package model.exp;

import customexception.MyException;
import datatypes.MyIDictionary;
import datatypes.MyIHeap;
import model.type.RefType;
import model.type.StringType;
import model.type.Type;
import model.value.RefValue;
import model.value.StringValue;
import model.value.Value;

public class ReadHeap implements Exp{
    private Exp expToEvaluate;
    public Exp getExpToEvaluate() {
        return expToEvaluate;
    }

    public void setExpToEvaluate(Exp expToEvaluate) {
        this.expToEvaluate = expToEvaluate;
    }

    public ReadHeap(Exp exp){
        expToEvaluate = exp;
    }
    public Value eval(MyIDictionary<String,Value> symbols_table, MyIHeap<Integer,Value> heap_table)throws MyException{
        Value valueOfExp = expToEvaluate.eval(symbols_table,heap_table);
        if(!(valueOfExp.getType() instanceof RefType)){
            throw new MyException("The evaluation of the expression doesn't return a referenced value");
        }
        else{
            RefValue valueOfExpression = (RefValue) valueOfExp;
            int addressInHeap = valueOfExpression.getAddress();
            if(!heap_table.lookForKey(addressInHeap))
                throw new MyException("Key not found");
            else {
                return heap_table.lookUp(addressInHeap);
            }
        }
    }
    public Type typeCheck(MyIDictionary<String,Type>typeEnv)throws MyException{

            Type tp1 = this.expToEvaluate.typeCheck(typeEnv);
            if(tp1 instanceof RefType){
                RefType refT = (RefType)tp1;
                return refT.getInner();
            }else{
                throw new MyException("The argument is not of type Reference");
            }

    }
    @Override
    public String toString() {
        return "rH(" +expToEvaluate +
                ')';
    }
}
