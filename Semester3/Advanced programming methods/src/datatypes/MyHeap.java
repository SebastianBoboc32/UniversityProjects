package datatypes;

import customexception.MyException;

import java.util.HashMap;
import java.util.Map;
import java.util.Set;

public class MyHeap <K,V> implements MyIHeap<K,V>{
    private HashMap<K,V>heapElements;
    private int firstFreeLocation;
    public MyHeap(){
        this.heapElements = new HashMap<>();
        this.firstFreeLocation = 1;
    }
    @Override
    public void put(K key_to_be_added, V value_to_be_added){
        try{
            if(this.lookUp(key_to_be_added) != null)
                throw new MyException("There is already a value associated with the key");
            this.heapElements.put(key_to_be_added,value_to_be_added);
        }catch(MyException e){
            this.update(key_to_be_added,value_to_be_added);
        }
    }

    public void update(K key_to_be_updated, V new_value_for_key){
        try{
            if(this.lookUp(key_to_be_updated) == null)
                throw new MyException("Nothing to be updated");
            this.heapElements.put(key_to_be_updated,new_value_for_key);
        }catch(MyException e){
            System.out.println(e.getMessage());
        }
    }
    public V lookUp(K key_to_get_value){
        try{
            return heapElements.get(key_to_get_value);
        }catch(NullPointerException e){
            System.out.println("There isn't any value associated with this key");
            return null;
        }
    }

    public boolean isDefined(K searchKey) throws MyException {
        if(this.lookUp(searchKey) != null)
            return true;
        return false;
    }
    public boolean isEmpty(){
        return this.heapElements.isEmpty();
    }
    public int size(){
        return this.heapElements.size();
    }
    public Set<K> keySet(){
        return this.heapElements.keySet();
    }
    public void remove(K deleteKey){
        try{
            this.heapElements.remove(deleteKey);
        }catch(NullPointerException e){
            System.out.println("The key doesn't exist");

        }
    }
    public boolean lookForKey(K searchedKey){
        return this.heapElements.containsKey(searchedKey);
    }

    public void setContent(Map<K,V>heap){
        this.heapElements = new HashMap<>(heap);
    }

    public Map<K,V>getContent(){
        return heapElements;
    }

    public int getFirstFreeLocation(){
        return this.firstFreeLocation;
    }
    public void incrementFirstFreeLocation(){this.firstFreeLocation++;}

    @Override
    public String toString(){
        String output = "";
        Set<K>keys = this.heapElements.keySet();
        for(K keysIterator :keys){
            V value = this.lookUp(keysIterator);
            output += keysIterator.toString() + "->" + value.toString() + "\n";
        }
        return output;
    }
}
