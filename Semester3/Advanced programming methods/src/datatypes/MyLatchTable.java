package datatypes;

import customexception.MyException;

import java.util.HashMap;
import java.util.Map;
import java.util.Set;

public class MyLatchTable<K,V>implements MyILatchTable<K,V>{
    private HashMap<K,V> latchTableElements;
    private int firstFreeLocation;
    public MyLatchTable(){
        this.latchTableElements = new HashMap<>();
        this.firstFreeLocation = 1;
    }
    @Override
    public void put(K key_to_be_added, V value_to_be_added){
        synchronized (this) {
            try {
                if (this.lookUp(key_to_be_added) != null)
                    throw new MyException("There is already a value associated with the key");
                this.latchTableElements.put(key_to_be_added, value_to_be_added);
            } catch (MyException e) {
                this.update(key_to_be_added, value_to_be_added);
            }
        }
    }

    public void update(K key_to_be_updated, V new_value_for_key){
        synchronized (this) {
            try {
                if (this.lookUp(key_to_be_updated) == null)
                    throw new MyException("Nothing to be updated");
                this.latchTableElements.put(key_to_be_updated, new_value_for_key);
            } catch (MyException e) {
                System.out.println(e.getMessage());
            }
        }
    }
    public V lookUp(K key_to_get_value){
        synchronized (this) {
            try {
                return latchTableElements.get(key_to_get_value);
            } catch (NullPointerException e) {
                System.out.println("There isn't any value associated with this key");
                return null;
            }
        }
    }

    public boolean isDefined(K searchKey) throws MyException {
        synchronized (this) {
            if (this.lookUp(searchKey) != null)
                return true;
            return false;
        }
    }
    public boolean isEmpty(){
        synchronized (this) {
            return this.latchTableElements.isEmpty();
        }
    }
    public int size(){
        synchronized (this) {
            return this.latchTableElements.size();
        }
    }
    public Set<K> keySet(){
        synchronized (this) {
            return this.latchTableElements.keySet();
        }
    }
    public void remove(K deleteKey){
        synchronized (this) {
            try {
                this.latchTableElements.remove(deleteKey);
            } catch (NullPointerException e) {
                System.out.println("The key doesn't exist");

            }
        }
    }
    public boolean lookForKey(K searchedKey){
        synchronized (this) {
            return this.latchTableElements.containsKey(searchedKey);
        }
    }

    public void setContent(Map<K,V> heap){
        synchronized (this) {
            this.latchTableElements = new HashMap<>(heap);
        }
    }

    public Map<K,V>getContent(){
        synchronized (this) {
            return latchTableElements;
        }
    }

    public int getFirstFreeLocation(){
        synchronized (this) {
            return this.firstFreeLocation;
        }
    }
    public void incrementFirstFreeLocation(){ synchronized (this) {this.firstFreeLocation++;}}

    @Override
    public String toString(){
        synchronized (this) {
            String output = "";
            Set<K> keys = this.latchTableElements.keySet();
            for (K keysIterator : keys) {
                V value = this.lookUp(keysIterator);
                output += keysIterator.toString() + "->" + value.toString() + "\n";
            }
            return output;
        }
    }
}
