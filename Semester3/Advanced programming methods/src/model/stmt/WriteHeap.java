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

public class WriteHeap implements IStmt{

    String variable_name;
    public String getVariable_name() {
        return variable_name;
    }

    public void setVariable_name(String variable_name) {
        this.variable_name = variable_name;
    }
    Exp expression;
    public Exp getExpression() {
        return expression;
    }
    public void setExpression(Exp expression) {
        this.expression = expression;
    }

    public WriteHeap(String var_name,Exp exp){
        this.expression = exp;
        this.variable_name = var_name;
    }
    public PrgState execute(PrgState state)throws MyException{
        MyIDictionary<String, Value>sym_table = state.getSymbols_table();
        MyIHeap<Integer,Value>heap_table = state.getHeap_table();
        if(sym_table.lookForKey(variable_name)){
            Value valueAssignedToVar = sym_table.lookUp(variable_name);
            if(valueAssignedToVar.getType() instanceof RefType){
                RefValue valueAsRef = (RefValue) valueAssignedToVar;
                int keyInHeapTable = valueAsRef.getAddress();
                if(heap_table.lookForKey(keyInHeapTable)){
                    Value evaluationOfExp = expression.eval(sym_table,heap_table);
                    if(evaluationOfExp.getType().equals(((RefType)valueAsRef.getType()).getInner())){
                        heap_table.update(keyInHeapTable,evaluationOfExp);
                    }else throw new MyException("The types of the inner type of the variable and the type of the expression evaluation do not match");
                }else throw new MyException("The location inside the variable is not a key inside the heap table");
            }else throw new MyException("The variable is not of RefType inside the symbols table");
        }else throw new MyException("There isn't any variable named "+variable_name+" inside the symbols table");
        return null;
    }

    public MyIDictionary<String, Type>typeCheck(MyIDictionary<String,Type>typeEnv)throws MyException{


            Type tpExp = expression.typeCheck(typeEnv);
            Type tpVar = typeEnv.lookUp(variable_name);
            if(tpVar.equals(new RefType(tpExp))){
                return typeEnv;
            }
              else throw new MyException("The lhs and rhs arent of the same type");
    }

    @Override
    public String toString() {
        return "wH(" +
  variable_name + '\'' +
                "," + expression +
                ')';
    }
}
