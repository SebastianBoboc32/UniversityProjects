package datatypes;
import java.util.*;

import customexception.MyException;
public class MyStack<T> implements MyIStack<T>  {
    private  Stack<T> elements;
    public MyStack(){
        this.elements = new Stack<>();
    }
    public void push(T element_to_be_added){
       try{
           if(element_to_be_added == null)
               throw new MyException("Can't add a null element");
           this.elements.push(element_to_be_added);
       }catch(MyException e){
           System.out.println("Can't add a null element to the stack");
       }
    }
    public T pop(){
        try{
            return this.elements.pop();
        }catch(EmptyStackException e){
            System.out.println("The stack is empty,nothing to pop");
            return null;
        }
    }
    public String toString(){
        String output ="";
        for( T ElementsIterator : elements)
            output +=ElementsIterator.toString()+"\n";
        return output;
    }
    public boolean isEmpty(){
        return elements.isEmpty();
    }
    public int size(){
        return elements.size();
    }

    @Override
    public List<T> getReversed() {
        List<T> list = Arrays.asList((T[]) elements.toArray());
        Collections.reverse(list);
        return list;    }
}

