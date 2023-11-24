package datatypes;

import java.util.ArrayList;
import java.util.List;

public class MyList <T> implements MyIList<T>{
    private List<T> elements;
    public MyList(){
        this.elements = new ArrayList<>();
    }
    public void add(T element_to_be_added){
        this.elements.add(element_to_be_added);
    }
    public List<T> get_all(){
        return this.elements;
    }
    public void set_list(List<T> new_elements){
        this.elements = new_elements;
    }
    public String toString(){
        String output ="";
        for(T ElementsIterator:elements)
            output += ElementsIterator.toString()+"\n";
        return output;
    }
    public T get(int index){
        return elements.get(index);
    }
    public int size(){
        return elements.size();
    }
}
