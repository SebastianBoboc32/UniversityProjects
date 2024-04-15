package model.value;

import model.type.RefType;
import model.type.Type;

public class RefValue implements Value{
    Type locationType;
    int address;
    public RefValue(int addr,Type locationType){
        this.address = addr;
        this.locationType = locationType;
    }
    public Type getType(){
        return new RefType(locationType);
    }
    public int getAddress(){
        return address;
    }
    public Type getLocationType(){
        return locationType;
    }
    public void setLocationType(Type newLocType){
        this.locationType = newLocType;
    }
    public void setAddress(int addressInHeap){
        this.address = addressInHeap;
    }

    @Override
    public String toString() {
        return
                "(" + locationType +
                "," + address +
                ')';
    }
}
