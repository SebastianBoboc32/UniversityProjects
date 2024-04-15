package model.stmt;

import customexception.MyException;
import datatypes.MyDictionary;
import datatypes.MyIDictionary;
import datatypes.MyIStack;
import model.PrgState;
import model.exp.Exp;
import model.type.BoolType;
import model.type.RefType;
import model.type.Type;
import model.value.BoolValue;
import model.value.Value;

public class WhileStmt implements IStmt{
    Exp loopCondition;

    IStmt statement;

    public Exp getLoopCondition() {
        return loopCondition;
    }

    public void setLoopCondition(Exp loopCondition) {
        this.loopCondition = loopCondition;
    }

    public IStmt getStatement() {
        return statement;
    }

    public void setStatement(IStmt statement) {
        this.statement = statement;
    }
    public WhileStmt(Exp exp, IStmt stmt){
        this.loopCondition = exp;
        this.statement = stmt;
    }
    public PrgState execute(PrgState state)throws MyException{
        MyIStack<IStmt>execution_stack = state.getExecution_stack();
        Value evalOfExp = loopCondition.eval(state.getSymbols_table(), state.getHeap_table());
        if(evalOfExp.getType().equals(new BoolType())){
            BoolValue evaluationOfExp = (BoolValue) evalOfExp;
            if(evaluationOfExp.getVal()){
                execution_stack.push(this);
               execution_stack.push(statement);
            }
        }else throw new MyException("The expression is not a bool");
        return null;
    }

    public MyIDictionary<String, Type> typeCheck(MyIDictionary<String,Type>typeEnv)throws MyException{

            Type typeOfCond = loopCondition.typeCheck(typeEnv);
            if(typeOfCond.equals(new BoolType())){
                MyIDictionary<String, Type> typeEnv1 = new MyDictionary<>(typeEnv);
                statement.typeCheck(typeEnv1);
                return typeEnv;
            }else{
                throw new MyException("The condition for the loop is not a boolean");
            }

    }

    @Override
    public String toString() {
        return "While(" +
                 loopCondition +
                "){" + statement +
                '}';
    }
}
