package model.exp;

import customexception.MyException;
import datatypes.MyIDictionary;
import model.type.IntType;
import model.value.BoolValue;
import model.value.IntValue;
import model.value.Value;

public class RelationalExp implements Exp{

    Exp expression_1;
    Exp expression_2;

    int relation_id;
    public static final int LESS = 1;
    public static final int GREATER = 2;

    public static final int EQUAL = 3;

    public static final int LESS_OR_EQUAL = 4;

    public static final int GREATER_OR_EQUAL = 5;
    public static final int NOT_EQUAL = 6;

    public RelationalExp(String relation,Exp exp1,Exp exp2){
        switch(relation){
            case "<" -> relation_id = LESS;
            case ">" -> relation_id = GREATER;
            case "==" ->relation_id = EQUAL;
            case "<=" ->relation_id = LESS_OR_EQUAL;
            case ">="->relation_id = GREATER_OR_EQUAL;
            case "!="->relation_id = NOT_EQUAL;
        }
        expression_1 = exp1;
        expression_2 = exp2;
    }
    public Value eval(MyIDictionary<String, Value>SymbolsTable)throws MyException {
        BoolValue return_value = new BoolValue(false);
        Value evaluation_1 = expression_1.eval(SymbolsTable);
        if(evaluation_1.getType().equals( new IntType())){
            Value evaluation_2 = expression_2.eval(SymbolsTable);
            if(evaluation_2.getType().equals(new IntType())){
                IntValue eval_1_as_integer = (IntValue) evaluation_1;
                IntValue eval_2_as_integer = (IntValue) evaluation_2;
                int integer_1 = eval_1_as_integer.getVal();
                int integer_2 = eval_2_as_integer.getVal();
                switch(relation_id){
                    case LESS -> return_value = new BoolValue(integer_1 < integer_2);
                    case GREATER -> return_value = new BoolValue(integer_1 > integer_2);
                    case EQUAL -> return_value = new BoolValue(integer_1 == integer_2);
                    case LESS_OR_EQUAL -> return_value = new BoolValue(integer_1 <= integer_2);
                    case GREATER_OR_EQUAL -> return_value = new BoolValue(integer_1 >= integer_2);
                    case NOT_EQUAL -> return_value = new BoolValue(integer_1 != integer_2);
                }
            }else {
                throw new MyException("The second expression isn't an integer");
            }
        }else{
            throw new MyException("The first expression isn't an integer");
        }
        return return_value;
    }
    public String toString(){
        String result= new String();
        switch (relation_id){
            case LESS -> result = expression_1.toString()+"<"+expression_2.toString();
            case GREATER -> result = expression_1.toString()+">"+expression_2.toString();
            case EQUAL -> result = expression_1.toString()+"=="+expression_2.toString();
            case LESS_OR_EQUAL -> result = expression_1.toString()+"<="+expression_2.toString();
            case GREATER_OR_EQUAL -> result = expression_1.toString()+">="+expression_2.toString();
            case NOT_EQUAL -> result = expression_1.toString()+"!="+expression_2.toString();
        }
        return result;
    }
}
