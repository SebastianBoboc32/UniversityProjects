package model.type;

import model.value.IntValue;
import model.value.Value;

public class IntType implements Type {
    public boolean equals(Object other){
        return other instanceof IntType;
    }
    public String toString(){
        return "int";
    }
    public Value defaultValue(){
        return new IntValue(0);
    }

}
