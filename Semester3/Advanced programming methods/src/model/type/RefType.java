package model.type;

import model.value.Value;
import model.value.RefValue;

public class RefType implements Type{
    public void setInner(Type inner) {
        this.inner = inner;
    }

    Type inner;
    public RefType(Type inner){
        this.inner = inner;
    }
    public Type getInner(){
        return this.inner;
    }
    public Value defaultValue(){
        return new RefValue(0,inner);
    }
    public boolean equals(Object other){
        if(other instanceof  RefType)
            return inner.equals(((RefType) other).getInner());
        else
            return false;
    }
    public String toString(){
        return "Ref("+inner.toString()+")";
    }
}
