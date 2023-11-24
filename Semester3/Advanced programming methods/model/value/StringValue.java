package model.value;

import model.type.StringType;
import model.type.Type;

public class StringValue implements Value{
    public String val;
    public StringValue(String str_val){
        this.val = str_val;
    }
    public boolean equals(StringValue other){
        return this.val.equals(other.getVal());
    }
    public Type getType(){
        return new StringType();
    }
    public String getVal(){
        return this.val;
    }
    public String toString(){
        return this.val;
    }
}
