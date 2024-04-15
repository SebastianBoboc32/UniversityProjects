package model.value;

import model.type.BoolType;
import model.type.Type;
import model.value.Value;

public class BoolValue implements Value {
    private boolean value;
    public BoolValue(boolean val){
        this.value = val;
    }
    public boolean equals(BoolValue another){
        return this.value == another.getVal();
    }
    public boolean getVal(){
        return this.value;
    }
    public String toString(){
        return Boolean.toString(this.value);
    }
    public Type getType(){
        return new BoolType();
    }
}
