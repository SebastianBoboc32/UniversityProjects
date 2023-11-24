package model.stmt;

import customexception.MyException;
import datatypes.MyIDictionary;
import model.*;
import model.type.BoolType;
import model.type.IntType;
import model.type.StringType;
import model.type.Type;
import model.value.BoolValue;
import model.value.IntValue;
import model.value.StringValue;
import model.value.Value;

public class VarDeclStmt implements IStmt {
    private Type type;
    private String name;
    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public Type getType() {
        return type;
    }

    public void setType(Type type) {
        this.type = type;
    }

    public VarDeclStmt(String name,Type type){
        this.name = name;
        this.type = type;
    }
    public PrgState execute(PrgState state)throws MyException{
        MyIDictionary<String, Value>systbl = state.getSymbols_table();
        if(!systbl.isDefined(name)){
            if(type.equals(new BoolType())){
                Value value_to_be_added = new BoolValue(false);
                systbl.put(name,value_to_be_added);
            }
            else if(type.equals(new IntType())){
                Value value_to_be_added = new IntValue(0);
                systbl.put(name,value_to_be_added);
            }
            else if(type.equals(new StringType())){
                Value value_to_be_added = new StringValue("");
                systbl.put(name,value_to_be_added);
            }
            else throw new MyException("Sorry,only integers,strings and booleans accepted as of now");
        }else throw new MyException("There is already a variable/constant with that name");
        return state;
    }
    public String toString(){
        return "name: "+ name + " type: "+type.toString();
    }
}
