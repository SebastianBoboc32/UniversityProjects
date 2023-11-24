package datatypes;

import customexception.MyException;

import java.util.Set;

public interface MyIDictionary<K,V> {
    void put(K key_to_be_added, V value_to_be_added);

    void update(K key_to_be_updated, V new_value_for_key);
    V lookUp(K key_to_get_value) throws MyException;

    boolean isDefined(K searchKey);
    boolean isEmpty();
    int size();
    Set<K> keySet();
    void remove(K deleteKey);
    boolean lookForKey(K searchedKey);
}
