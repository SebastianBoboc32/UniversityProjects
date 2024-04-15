package datatypes;
import customexception.MyException;

import java.util.Collection;
import java.util.HashMap;
import java.util.Map;
import java.util.Set;

public class MyDictionary <K,V> implements MyIDictionary<K,V>{
    private  HashMap<K,V> dictionary;
    public MyDictionary(){
        this.dictionary = new HashMap<>();
    }

    public MyDictionary(MyIDictionary<K,V>other) throws MyException {
        this.dictionary = new HashMap<>();
        for(K key:other.keySet())
            this.dictionary.put(key,other.lookUp(key));
    }
    public void put(K key_to_be_added,V value_to_be_added){
        try{
            if(this.lookUp(key_to_be_added) != null)
                throw new MyException("There is already a value associated with the key");
            this.dictionary.put(key_to_be_added,value_to_be_added);
        }catch(MyException e){
            this.update(key_to_be_added,value_to_be_added);
        }
    }

    public void update(K key_to_be_updated,V new_value_for_key){
        try{
            if(this.lookUp(key_to_be_updated) == null)
                throw new MyException("Nothing to be updated");
            this.dictionary.put(key_to_be_updated,new_value_for_key);
        }catch(MyException e){
            System.out.println(e.getMessage());
        }
    }
    public V lookUp(K key_to_get_value){
        try{
            return dictionary.get(key_to_get_value);
        }catch(NullPointerException e){
            System.out.println("There isn't any value associated with this key");
            return null;
        }
    }
    public boolean isEmpty(){
        return dictionary.isEmpty();
    }
    public int size(){
        return dictionary.size();
    }
    public String toString(){
        String output = "";
        Set<K>keys = this.dictionary.keySet();
        for(K keysIterator :keys){
            V value = this.lookUp(keysIterator);
            output += keysIterator.toString()+"->"+value.toString()+"\n";
        }
        return output;
    }
    public   boolean isDefined(K searchKey){
        if(this.lookUp(searchKey) != null)
            return true;
        return false;
    }
    public Set<K> keySet(){
        return this.dictionary.keySet();
    }

    @Override
    public void remove(K deleteKey) {
        try{
            this.dictionary.remove(deleteKey);
        }catch(NullPointerException e){
            System.out.println("The key doesn't exist");
        }
    }

    public Map<K,V>getContent(){
        return dictionary;
    }

    public boolean lookForKey(K searchedKey){
       return this.dictionary.containsKey(searchedKey);
    }

    @Override
    public Collection<V> values() {
        synchronized (this) {
            return this.dictionary.values();
        }
    }

    public MyIDictionary<K,V>deepCopy(){
        MyIDictionary<K,V>clone = new MyDictionary<K,V>();
        for(Map.Entry<K,V>entry:this.dictionary.entrySet())
            clone.put(entry.getKey(),entry.getValue());
        return clone;
    }

}
