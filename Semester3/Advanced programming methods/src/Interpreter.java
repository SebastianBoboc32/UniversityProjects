/*
import cmd.Command;
import cmd.ExitCommand;
import cmd.RunExample;
import controller.MyContoller;
import customexception.MyException;
import datatypes.*;
import model.PathToProgram;
import model.PrgState;
import model.exp.*;
import model.stmt.*;
import model.type.*;
import model.value.BoolValue;
import model.value.IntValue;
import model.value.StringValue;
import model.value.Value;
import repository.MyIRepository;
import repository.MyMemoryRepo;
import view.TextMenu;

import java.io.BufferedReader;

public class Interpreter {






    public static void main(String[]args){

         IStmt ex1 = new CompStmt(new VarDeclStmt("v",new IntType()),
                new CompStmt(new AssignStmt("v",new ValueExp(new IntValue(2))),
                        new PrintStmt(new VarExp("v"))));
         IStmt ex2 = new CompStmt(new VarDeclStmt("a",new IntType()),
                new CompStmt(new VarDeclStmt("b",new IntType()),
                        new CompStmt(new AssignStmt("a",new ArithExp('+',new ValueExp(new IntValue(2)),
                                new ArithExp('*',new ValueExp(new IntValue(3)),
                                        new ValueExp(new IntValue(5))))),
                                new CompStmt(new AssignStmt("b",new ArithExp('+',new VarExp("a"),
                                        new ValueExp(new IntValue(1)))),new PrintStmt(new VarExp("b"))))));
        IStmt ex3= new CompStmt(new VarDeclStmt("a",new BoolType()),
                new CompStmt(new VarDeclStmt("v",new IntType()),
                        new CompStmt(new AssignStmt("a",new ValueExp(new BoolValue(true))),
                                new CompStmt(new IfStmt(new VarExp("a"),new AssignStmt("v",
                                        new ValueExp(new IntValue(2))),
                                        new AssignStmt("v",new ValueExp(new IntValue(3)))),
                                        new PrintStmt(new VarExp("v"))))));

         IStmt ex4 = new PrintStmt( new RelationalExp("<=",new ValueExp(new IntValue(5)),new ValueExp(new BoolValue(false))));

        IStmt ex5 = new CompStmt(new VarDeclStmt("varf", new StringType()),
                new CompStmt(new AssignStmt("varf", new ValueExp(new StringValue(PathToProgram.path+"test.in"))),
                        new CompStmt(new OpenRFile(new VarExp("varf")),
                                new CompStmt(new VarDeclStmt("varc", new IntType()),
                                        new CompStmt(new readFile(new VarExp("varf"), "varc"),
                                                new CompStmt(new PrintStmt(new VarExp("varc")),
                                                        new CompStmt(new readFile(new VarExp("varf"), "varc"),
                                                                new CompStmt(new PrintStmt(new VarExp("varc")), new closeRFile(new VarExp("varf"))))))))));

        IStmt ex6 = new CompStmt(new VarDeclStmt("v", new IntType()),
                new CompStmt(new AssignStmt("v", new ValueExp(new IntValue(4))),
                        new CompStmt(new WhileStmt(new RelationalExp(">", new VarExp("v"), new ValueExp(new IntValue(0))),
                                new CompStmt(new PrintStmt(new VarExp("v")), new AssignStmt("v", new ArithExp('-', new VarExp("v"), new ValueExp(new StringValue("1")))))),
                                new PrintStmt(new VarExp("v")))));

        IStmt ex7 = new CompStmt(new VarDeclStmt("v", new RefType(new IntType())),
                new CompStmt(new NewStmt("v", new ValueExp(new IntValue(20))),
                        new CompStmt(new VarDeclStmt("a", new RefType(new RefType(new IntType()))),
                                new CompStmt(new NewStmt("a", new VarExp("v")),
                                        new CompStmt(new NewStmt("v", new ValueExp(new IntValue(30))),
                                                new PrintStmt(new ReadHeap(new ReadHeap(new VarExp("a")))))))));

        IStmt ex8 = new CompStmt(new VarDeclStmt("v", new IntType()),
                new CompStmt(new VarDeclStmt("a", new RefType(new IntType())),
                        new CompStmt(new AssignStmt("v", new ValueExp(new IntValue(10))),
                                new CompStmt(new NewStmt("a", new ValueExp(new IntValue(22))),
                                        new CompStmt(new ForkStmt(new CompStmt(new WriteHeap("a", new ValueExp(new IntValue(30))),
                                                new CompStmt(new AssignStmt("v", new ValueExp(new IntValue(32))),
                                                        new CompStmt(new PrintStmt(new VarExp("v")), new PrintStmt(new ReadHeap(new VarExp("a")))
                                                        )))),
                                                new CompStmt(new PrintStmt(new VarExp("v")), new PrintStmt(new ReadHeap(new VarExp("a")))))))));




        TextMenu menu = new TextMenu();
        menu.addCommand(new ExitCommand("0","exit"));



        try {
            ex1.typeCheck(new MyDictionary<String, Type>());
            MyIStack<IStmt> exeStack1 = new MyStack<>();
            MyIDictionary<String, Value> symTable1 = new MyDictionary<>();
            MyIList<String> output1 = new MyList<>();
            MyIDictionary<String, BufferedReader> fileTable1 = new MyDictionary<>();
            MyIHeap<Integer, Value> heapTable1 = new MyHeap<>();

            PrgState program1 = new PrgState(ex1, exeStack1, symTable1, output1, fileTable1, heapTable1);
            MyIRepository repository1 = new MyMemoryRepo("log1.txt");
            repository1.addState(program1);
            MyContoller controller1 = new MyContoller(repository1);
            menu.addCommand(new RunExample("1",ex1.toString(),controller1));
        }catch(MyException e){
            System.out.println(e.getMessage());
        }

        try {
            ex2.typeCheck(new MyDictionary<String,Type>());
            MyIStack<IStmt> exeStack2 = new MyStack<>();
            MyIDictionary<String, Value> symTable2 = new MyDictionary<>();
            MyIList<String> output2 = new MyList<>();
            MyIDictionary<String, BufferedReader> fileTable2 = new MyDictionary<>();
            MyIHeap<Integer, Value> heapTable2 = new MyHeap<>();
            PrgState program2 = new PrgState(ex2, exeStack2, symTable2, output2, fileTable2, heapTable2);

            MyIRepository repository2 = new MyMemoryRepo("log2.txt");
            repository2.addState(program2);

            MyContoller controller2 = new MyContoller(repository2);
            menu.addCommand(new RunExample("2",ex2.toString(),controller2));
        }catch(MyException e){
            System.out.println(e.getMessage());
        }

        try {
            ex3.typeCheck(new MyDictionary<String, Type>());
            MyIStack<IStmt> exeStack3 = new MyStack<>();
            MyIDictionary<String, Value> symTable3 = new MyDictionary<>();
            MyIList<String> output3 = new MyList<>();
            MyIDictionary<String, BufferedReader> fileTable3 = new MyDictionary<>();
            MyIHeap<Integer, Value> heapTable3 = new MyHeap<>();
            PrgState program3 = new PrgState(ex3, exeStack3, symTable3, output3, fileTable3, heapTable3);
            MyIRepository repository3 = new MyMemoryRepo("log3.txt");
            repository3.addState(program3);
            MyContoller controller3 = new MyContoller(repository3);
            menu.addCommand(new RunExample("3",ex3.toString(),controller3));
        }catch(MyException e){
            System.out.println(e.getMessage());
        }
        try {
            ex4.typeCheck(new MyDictionary<String, Type>());
            MyIStack<IStmt> exeStack4 = new MyStack<>();
            MyIDictionary<String, Value> symTable4 = new MyDictionary<>();
            MyIList<String> output4 = new MyList<>();
            MyIDictionary<String, BufferedReader> fileTable4 = new MyDictionary<>();
            MyIHeap<Integer, Value> heapTable4 = new MyHeap<>();
            PrgState program4 = new PrgState(ex4, exeStack4, symTable4, output4, fileTable4, heapTable4);
            MyIRepository repository4 = new MyMemoryRepo("log4.txt");
            repository4.addState(program4);
            MyContoller controller4 = new MyContoller(repository4);
            menu.addCommand(new RunExample("4",ex4.toString(),controller4));
        }catch(MyException e){
            System.out.println(e.getMessage());
        }

        try {
            ex5.typeCheck(new MyDictionary<String, Type>());
            MyIStack<IStmt> exeStack5 = new MyStack<>();
            MyIDictionary<String, Value> symTable5 = new MyDictionary<>();
            MyIList<String> output5 = new MyList<>();
            MyIDictionary<String, BufferedReader> fileTable5 = new MyDictionary<>();
            MyIHeap<Integer, Value> heapTable5 = new MyHeap<>();

            PrgState program5 = new PrgState(ex5, exeStack5, symTable5, output5, fileTable5, heapTable5);
            MyIRepository repository5 = new MyMemoryRepo("log5.txt");
            repository5.addState(program5);
            MyContoller controller5 = new MyContoller(repository5);
            menu.addCommand(new RunExample("5",ex5.toString(),controller5));
        }catch(MyException e){
            System.out.println(e.getMessage());
        }

        try {
            ex6.typeCheck(new MyDictionary<String, Type>());
            MyIStack<IStmt> exeStack6 = new MyStack<>();
            MyIDictionary<String, Value> symTable6 = new MyDictionary<>();
            MyIList<String> output6 = new MyList<>();
            MyIDictionary<String, BufferedReader> fileTable6 = new MyDictionary<>();
            MyIHeap<Integer, Value> heapTable6 = new MyHeap<>();
            PrgState program6 = new PrgState(ex6, exeStack6, symTable6, output6, fileTable6, heapTable6);
            MyIRepository repository6 = new MyMemoryRepo("log6.txt");
            repository6.addState(program6);
            MyContoller controller6 = new MyContoller(repository6);
            menu.addCommand(new RunExample("6",ex6.toString(),controller6));
        }catch(MyException e){
            System.out.println(e.getMessage());
        }

        try {
            ex7.typeCheck(new MyDictionary<String, Type>());
            MyIStack<IStmt> exeStack7 = new MyStack<>();
            MyIDictionary<String, Value> symTable7 = new MyDictionary<>();
            MyIList<String> output7 = new MyList<>();
            MyIDictionary<String, BufferedReader> fileTable7 = new MyDictionary<>();
            MyIHeap<Integer, Value> heapTable7 = new MyHeap<>();
            PrgState program7 = new PrgState(ex7, exeStack7, symTable7, output7, fileTable7, heapTable7);
            MyIRepository repository7 = new MyMemoryRepo("log7.txt");
            repository7.addState(program7);
            MyContoller controller7 = new MyContoller(repository7);
            menu.addCommand(new RunExample("7",ex7.toString(),controller7));
        }catch(MyException e){
            System.out.println(e.getMessage());
        }

        try {
            ex8.typeCheck(new MyDictionary<String, Type>());
            MyIStack<IStmt> exeStack8 = new MyStack<>();
            MyIDictionary<String, Value> symTable8 = new MyDictionary<>();
            MyIList<String> output8 = new MyList<>();
            MyIDictionary<String, BufferedReader> fileTable8 = new MyDictionary<>();
            MyIHeap<Integer, Value> heapTable8 = new MyHeap<>();
            PrgState program8 = new PrgState(ex8, exeStack8, symTable8, output8, fileTable8, heapTable8);
            MyIRepository repository8 = new MyMemoryRepo("log8.txt");
            repository8.addState(program8);
            MyContoller controller8 = new MyContoller(repository8);
            menu.addCommand(new RunExample("8",ex8.toString(),controller8));
        }catch(MyException e){
            System.out.println(e.getMessage());
        }
        menu.show();
    }
}
*/