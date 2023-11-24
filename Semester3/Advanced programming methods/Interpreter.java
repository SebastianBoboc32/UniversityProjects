import cmd.Command;
import cmd.ExitCommand;
import cmd.RunExample;
import controller.MyContoller;
import customexception.MyException;
import datatypes.*;
import model.PathToProgram;
import model.PrgState;
import model.exp.ArithExp;
import model.exp.RelationalExp;
import model.exp.ValueExp;
import model.exp.VarExp;
import model.stmt.*;
import model.type.BoolType;
import model.type.IntType;
import model.type.StringType;
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

         IStmt ex4 = new PrintStmt( new RelationalExp("<=",new ValueExp(new IntValue(5)),new ValueExp(new IntValue(7))));

        IStmt ex5 = new CompStmt(new VarDeclStmt("varf", new StringType()),
                new CompStmt(new AssignStmt("varf", new ValueExp(new StringValue(PathToProgram.path+"test.in"))),
                        new CompStmt(new OpenRFile(new VarExp("varf")),
                                new CompStmt(new VarDeclStmt("varc", new IntType()),
                                        new CompStmt(new readFile(new VarExp("varf"), "varc"),
                                                new CompStmt(new PrintStmt(new VarExp("varc")),
                                                        new CompStmt(new readFile(new VarExp("varf"), "varc"),
                                                                new CompStmt(new PrintStmt(new VarExp("varc")), new closeRFile(new VarExp("varf"))))))))));


            MyIStack<IStmt> exeStack1 = new MyStack<>();
            MyIDictionary<String, Value> symTable1 = new MyDictionary<>();
            MyIList<String> output1 = new MyList<>();
            MyIDictionary<String, BufferedReader>fileTable1 = new MyDictionary<>();

            PrgState program1 = new PrgState(ex1,exeStack1, symTable1, output1,fileTable1);

            MyIRepository repository1 = new MyMemoryRepo("log1.txt");
            repository1.addState(program1);

            MyContoller controller1 = new MyContoller(repository1);



            MyIStack<IStmt> exeStack2 = new MyStack<>();
            MyIDictionary<String, Value> symTable2 = new MyDictionary<>();
            MyIList<String> output2 = new MyList<>();
            MyIDictionary<String, BufferedReader>fileTable2 = new MyDictionary<>();

            PrgState program2 = new PrgState(ex2,exeStack2, symTable2, output2,fileTable2);

            MyIRepository repository2 = new MyMemoryRepo("log2.txt");
            repository2.addState(program2);

            MyContoller controller2 = new MyContoller(repository2);


            MyIStack<IStmt> exeStack3 = new MyStack<>();
            MyIDictionary<String, Value> symTable3 = new MyDictionary<>();
            MyIList<String> output3 = new MyList<>();
            MyIDictionary<String, BufferedReader>fileTable3 = new MyDictionary<>();
            PrgState program3 = new PrgState(ex3,exeStack3, symTable3, output3,fileTable3);

            MyIRepository repository3 = new MyMemoryRepo("log3.txt");
            repository3.addState(program3);

            MyContoller controller3 = new MyContoller(repository3);


            MyIStack<IStmt> exeStack4 = new MyStack<>();
            MyIDictionary<String, Value> symTable4 = new MyDictionary<>();
            MyIList<String> output4 = new MyList<>();
            MyIDictionary<String, BufferedReader>fileTable4 = new MyDictionary<>();
            PrgState program4 = new PrgState(ex4,exeStack4, symTable4, output4,fileTable4);
            MyIRepository repository4 = new MyMemoryRepo("log4.txt");
            repository4.addState(program4);

            MyContoller controller4 = new MyContoller(repository4);

            MyIStack<IStmt> exeStack5 = new MyStack<>();
            MyIDictionary<String, Value> symTable5 = new MyDictionary<>();
            MyIList<String> output5 = new MyList<>();
            MyIDictionary<String, BufferedReader>fileTable5 = new MyDictionary<>();
            PrgState program5 = new PrgState(ex5,exeStack5, symTable5, output5,fileTable5);
            MyIRepository repository5 = new MyMemoryRepo("log5.txt");
            repository5.addState(program5);

            MyContoller controller5 = new MyContoller(repository5);

        TextMenu menu = new TextMenu();
        menu.addCommand(new ExitCommand("0","exit"));
        menu.addCommand(new RunExample("1",ex1.toString(),controller1));
        menu.addCommand(new RunExample("2",ex2.toString(),controller2));
        menu.addCommand(new RunExample("3",ex3.toString(),controller3));
        menu.addCommand(new RunExample("4",ex4.toString(),controller4));
        menu.addCommand(new RunExample("5",ex5.toString(),controller5));
        menu.show();
    }
}
