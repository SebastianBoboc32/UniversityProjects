package model.value;

import model.type.IntType;
import model.type.Type;

public class IntValue implements Value {
    private int value;

    public IntValue(int val){
        this.value = val;
    }
    public boolean equals(IntValue other){
        return this.value == other.getVal();
    }
    public int getVal(){
        return this.value;
    }
    public String toString(){
        return Integer.toString(this.value);
    }
    public Type getType(){
        return new IntType();
    }
}
