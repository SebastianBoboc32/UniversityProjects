package datatypes;


public interface MyIStack<T> {
    void push(T element_to_be_added);
    T pop();
    boolean isEmpty();
    public int size();
}
