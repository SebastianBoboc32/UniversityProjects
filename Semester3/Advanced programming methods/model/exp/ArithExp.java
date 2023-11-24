package model.exp;

import customexception.MyException;
import datatypes.MyIDictionary;
import model.type.IntType;
import model.value.IntValue;
import model.value.Value;


public class ArithExp implements Exp {
    Exp expression_1;
    Exp expression_2;
    int operation_id;
    public static final int ADD = 1;
    public static final int SUBTRACT = 2;
    public static final int MULTIPLY = 3;
    public static final int DIVIDE = 4;
    public ArithExp(char operation,Exp e1,Exp e2){
        switch(operation){
            case '+' -> this.operation_id = ADD;
            case '-' -> this.operation_id = SUBTRACT;
            case '*' -> this.operation_id = MULTIPLY;
            case '/' -> this.operation_id = DIVIDE;
        }
        this.expression_1 = e1;
        this.expression_2 = e2;
    }
    public Value eval(MyIDictionary<String,Value>symbols_table)throws MyException{
        Value evaluation_1,evaluation_2;
        evaluation_1 = expression_1.eval(symbols_table);
        if(evaluation_1.getType().equals(new IntType())){
            evaluation_2 = expression_2.eval(symbols_table);
            if(evaluation_2.getType().equals((new IntType()))){
                IntValue evaluation_1_as_int = (IntValue) evaluation_1;
                IntValue evaluation_2_as_int = (IntValue) evaluation_2;
                int integer_value_1,integer_value_2;
                integer_value_1 = evaluation_1_as_int.getVal();
                integer_value_2 = evaluation_2_as_int.getVal();
                if(operation_id == 1)return new IntValue(integer_value_1+integer_value_2);
                else if(operation_id == 2)return new IntValue(integer_value_1-integer_value_2);
                else if(operation_id == 3)return new IntValue(integer_value_1*integer_value_2);
                else if(operation_id == 4){
                    if(integer_value_2 == 0)
                        throw new MyException("Division by zero");
                    else return new IntValue(integer_value_1/integer_value_2);
                }
            }else throw new MyException("Second operand is not an integer");
        }else throw new MyException("First operand is not an integer");
        return null;
    }
    public String toString(){
        if(operation_id == 1)
            return expression_1.toString()+"+"+ expression_2.toString();
        else if(operation_id == 2)
            return expression_1.toString()+"-"+ expression_2.toString();
        else if(operation_id == 3)
            return expression_1.toString()+"*"+ expression_2.toString();
        else if(operation_id == 4)
            return expression_1.toString()+"/"+ expression_2.toString();
        return "";
    }
}
