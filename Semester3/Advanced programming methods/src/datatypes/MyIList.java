package datatypes;
import java.util.List;
public interface MyIList<T>{
    void add(T element_to_be_added);
    List<T> get_all();
    void set_list(List<T> new_elements);
    T get(int index);
    public int size();

}
