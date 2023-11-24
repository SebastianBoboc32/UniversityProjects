package model.type;

import model.value.StringValue;
import model.value.Value;

public class StringType implements Type{
    public Value defaultValue(){
        return new StringValue("");
    }
    public boolean equals(Object other){
        return other instanceof StringType;
    }
    public String toString(){
        return "string";
    }
}
