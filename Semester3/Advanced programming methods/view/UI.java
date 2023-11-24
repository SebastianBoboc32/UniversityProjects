package view;
import datatypes.*;
import controller.*;
import customexception.*;
import model.*;
import model.exp.*;
import model.stmt.*;
import model.type.BoolType;
import model.type.IntType;
import model.type.StringType;
import model.value.BoolValue;
import model.value.IntValue;
import model.value.StringValue;
import model.value.Value;
import repository.*;

import java.io.BufferedReader;

public class UI {
    private IStmt ex1 = new CompStmt(new VarDeclStmt("v",new IntType()),
            new CompStmt(new AssignStmt("v",new ValueExp(new IntValue(2))),
                    new PrintStmt(new VarExp("v"))));
    private IStmt ex2 = new CompStmt(new VarDeclStmt("a",new IntType()),
            new CompStmt(new VarDeclStmt("b",new IntType()),
                    new CompStmt(new AssignStmt("a",new ArithExp('+',new ValueExp(new IntValue(2)),
                            new ArithExp('*',new ValueExp(new IntValue(3)),
                                    new ValueExp(new IntValue(5))))),
                            new CompStmt(new AssignStmt("b",new ArithExp('+',new VarExp("a"),
                                    new ValueExp(new IntValue(1)))),new PrintStmt(new VarExp("b"))))));
    private IStmt ex3= new CompStmt(new VarDeclStmt("a",new BoolType()),
            new CompStmt(new VarDeclStmt("v",new IntType()),
                    new CompStmt(new AssignStmt("a",new ValueExp(new BoolValue(true))),
                            new CompStmt(new IfStmt(new VarExp("a"),new AssignStmt("v",
                                    new ValueExp(new IntValue(2))),
                                    new AssignStmt("v",new ValueExp(new IntValue(3)))),
                                    new PrintStmt(new VarExp("v"))))));
    public UI(){

    }
    private IStmt ex4 = new PrintStmt( new RelationalExp("<=",new ValueExp(new IntValue(5)),new ValueExp(new IntValue(7))));

    IStmt ex5 = new CompStmt(new VarDeclStmt("varf", new StringType()),
            new CompStmt(new AssignStmt("varf", new ValueExp(new StringValue(PathToProgram.path+"test.in"))),
                    new CompStmt(new OpenRFile(new VarExp("varf")),
                            new CompStmt(new VarDeclStmt("varc", new IntType()),
                                    new CompStmt(new readFile(new VarExp("varf"), "varc"),
                                            new CompStmt(new PrintStmt(new VarExp("varc")),
                                                    new CompStmt(new readFile(new VarExp("varf"), "varc"),
                                                            new CompStmt(new PrintStmt(new VarExp("varc")), new closeRFile(new VarExp("varf"))))))))));
    public void menu() {
        System.out.println("0. Exit");
        System.out.println("1. Example 1 " + ex1);
        System.out.println("2. Example 2 " + ex2);
        System.out.println("3.Example 3 "+ex3);
    }

    private void runEx1() {

        MyIStack<IStmt> exeStack = new MyStack<>();
        MyIDictionary<String, Value> symTable = new MyDictionary<>();
        MyIList<String> output = new MyList<>();
        MyIDictionary<String, BufferedReader>fileTable = new MyDictionary<>();

        PrgState program = new PrgState(ex1,exeStack, symTable, output,fileTable);

        MyIRepository repository = new MyMemoryRepo("C:\\Users\\Sebastian\\workspace\\APMProject\\src\\program_states.txt");
        repository.addState(program);

        MyContoller controller = new MyContoller(repository);
        try {
            controller.allSteps();
        } catch (MyException e) {
            throw new RuntimeException(e);
        }

    }
    private void runEx2() {

        MyIStack<IStmt> exeStack = new MyStack<>();
        MyIDictionary<String, Value> symTable = new MyDictionary<>();
        MyIList<String> output = new MyList<>();
        MyIDictionary<String, BufferedReader>fileTable = new MyDictionary<>();

        PrgState program = new PrgState(ex2,exeStack, symTable, output,fileTable);

        MyIRepository repository = new MyMemoryRepo(PathToProgram.path+"program_states.txt");
        repository.addState(program);

        MyContoller controller = new MyContoller(repository);
        try {
            controller.allSteps();
        } catch (MyException e) {
            throw new RuntimeException(e);
        }

    }

    private void runEx3() {

        MyIStack<IStmt> exeStack = new MyStack<>();
        MyIDictionary<String, Value> symTable = new MyDictionary<>();
        MyIList<String> output = new MyList<>();
        MyIDictionary<String, BufferedReader>fileTable = new MyDictionary<>();
        PrgState program = new PrgState(ex3,exeStack, symTable, output,fileTable);

        MyIRepository repository = new MyMemoryRepo("C:\\Users\\Sebastian\\workspace\\APMProject\\src\\program_states.txt");
        repository.addState(program);

        MyContoller controller = new MyContoller(repository);
        try {
            controller.allSteps();
        } catch (MyException e) {
            throw new RuntimeException(e);
        }

    }

    private void runEx4(){
        MyIStack<IStmt> exeStack = new MyStack<>();
        MyIDictionary<String, Value> symTable = new MyDictionary<>();
        MyIList<String> output = new MyList<>();
        MyIDictionary<String, BufferedReader>fileTable = new MyDictionary<>();
        PrgState program = new PrgState(ex4,exeStack, symTable, output,fileTable);
        MyIRepository repository = new MyMemoryRepo("C:\\Users\\Sebastian\\workspace\\APMProject\\src\\program_states.txt");
        repository.addState(program);

        MyContoller controller = new MyContoller(repository);
        try {
            controller.allSteps();
        } catch (MyException e) {
            throw new RuntimeException(e);
        }
    }

    public void runEx5(){
        MyIStack<IStmt> exeStack = new MyStack<>();
        MyIDictionary<String, Value> symTable = new MyDictionary<>();
        MyIList<String> output = new MyList<>();
        MyIDictionary<String, BufferedReader>fileTable = new MyDictionary<>();
        PrgState program = new PrgState(ex5,exeStack, symTable, output,fileTable);
        MyIRepository repository = new MyMemoryRepo("C:\\Users\\Sebastian\\workspace\\APMProject\\src\\program_states.txt");
        repository.addState(program);

        MyContoller controller = new MyContoller(repository);
        try {
            controller.allSteps();
        } catch (MyException e) {
            throw new RuntimeException(e);
        }
    }

    public static void main(String[] args) {
        UI view = new UI();
        view.runEx1();
        view.runEx2();
        view.runEx3();
        view.runEx4();
        view.runEx5();
    }
}
