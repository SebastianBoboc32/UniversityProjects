package model.exp;

import customexception.MyException;
import datatypes.MyIDictionary;
import model.type.BoolType;
import model.value.BoolValue;
import model.value.Value;

public class LogicExp implements Exp {
    Exp expression_1;
    Exp expression_2;
    int logic_op_id;
    public LogicExp(String operation,Exp e1,Exp e2){
        switch(operation){
            case "&&" -> this.logic_op_id = LOGICAL_AND;
            case "||" -> this.logic_op_id = LOGICAL_OR;
        }
    }
    public static final int LOGICAL_AND = 1;
    public static final int LOGICAL_OR = 2;
    public Value eval(MyIDictionary<String,Value> symbols_table)throws MyException{
        Value evaluation_1 = expression_1.eval(symbols_table);
        if(evaluation_1.getType().equals ((new BoolType()))){
            Value evaluation_2 = expression_2.eval(symbols_table);
            if(evaluation_2.getType().equals((new BoolType()))){
                BoolValue eval_1_as_bool = (BoolValue)evaluation_1;
                BoolValue eval_2_as_bool = (BoolValue) evaluation_2;
                boolean bool_value_1=eval_1_as_bool.getVal();
                boolean bool_value_2 = eval_2_as_bool.getVal();
                if(logic_op_id == 1)return new BoolValue(bool_value_1 && bool_value_2);
                else if(logic_op_id == 2)return new BoolValue(bool_value_1 || bool_value_2);
            }else throw new MyException("The second operand is not a boolean");
        }else throw new MyException("The first operand is not a boolean");
        return null;
    }
    public String toString(){
        if(logic_op_id == 1)
            return expression_1.toString()+" && "+ expression_2.toString();
        else if(logic_op_id ==2)
            return expression_1.toString()+"||"+ expression_2.toString();
        return "";
    }
}
