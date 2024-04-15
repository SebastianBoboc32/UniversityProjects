package cmd;

import controller.MyContoller;
import customexception.MyException;

public class RunExample extends Command{

    private MyContoller controller;

    public RunExample(String key,String desc,MyContoller ctrl){
        super(key,desc);
        this.controller = ctrl;
    }
    public void execute(){
        try{
            controller.allSteps();
        }catch(MyException e){
            System.out.println(e.getMessage());
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }
    }
}
