package datatypes;


import java.util.List;

public interface MyIStack<T> {
    void push(T element_to_be_added);
    T pop();
    boolean isEmpty();
    public int size();

    public List<T> getReversed();
}
