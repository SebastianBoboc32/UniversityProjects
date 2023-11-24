package model.type;

import model.value.BoolValue;
import model.value.Value;

public class BoolType implements Type {
    public boolean equals(Object other){
        return other instanceof BoolType;
    }
    public String toString(){
        return "bool";
    }
    public Value defaultValue(){
        return new BoolValue(false);
    }
}
