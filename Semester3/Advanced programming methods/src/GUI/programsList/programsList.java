package GUI.programsList;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.*;

import GUI.programController.*;
import controller.MyContoller;
import datatypes.*;
import customexception.MyException;
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

import java.io.BufferedReader;
import java.util.ArrayList;
import java.util.List;
public class programsList {
    private programController programExecutorController;

    public void setProgramExecutorController(programController programExecutorController) {
        this.programExecutorController = programExecutorController;
    }
    @FXML
    private ListView<IStmt> programsListView;

    @FXML
    private Button displayButton;

    @FXML
    public void initialize() {
        programsListView.setItems(getAllStatements());
        programsListView.getSelectionModel().setSelectionMode(SelectionMode.SINGLE);
    }

    @FXML
    private void displayProgram(ActionEvent actionEvent) {
        IStmt selectedStatement = programsListView.getSelectionModel().getSelectedItem();
        if (selectedStatement == null) {
            Alert alert = new Alert(Alert.AlertType.ERROR);
            alert.setTitle("Error encountered!");
            alert.setContentText("No statement selected!");
            alert.showAndWait();
        } else {
            int id = programsListView.getSelectionModel().getSelectedIndex();
            try {
                selectedStatement.typeCheck(new MyDictionary<String, Type>());
                PrgState prg1 = new PrgState(selectedStatement,new MyStack<IStmt>(), new MyDictionary<String, Value>(), new MyList<String>(),
                                        new MyDictionary<String, BufferedReader>(), new MyHeap(),new MyLatchTable<>());
                ArrayList<PrgState> l1 = new ArrayList<PrgState>();
                l1.add(prg1);
                MyIRepository repo1 = new MyMemoryRepo(l1, "log1.txt");
                MyContoller controller = new MyContoller(repo1);
                programExecutorController.setController(controller);
            } catch (MyException exception) {
                Alert alert = new Alert(Alert.AlertType.ERROR);
                alert.setTitle("Error encountered!");
                alert.setContentText(exception.getMessage());
                alert.showAndWait();
            }
        }
    }

    @FXML
    private ObservableList<IStmt> getAllStatements() {
        List<IStmt> allStatements = new ArrayList<>();

        IStmt ex1 = new CompStmt(new VarDeclStmt("v", new IntType()),
                new CompStmt(new AssignStmt("v", new ValueExp(new IntValue(2))), new PrintStmt(new VarExp("v"))));
        allStatements.add(ex1);

        IStmt ex2 = new CompStmt(new VarDeclStmt("a", new IntType()),
                new CompStmt(new VarDeclStmt("b", new IntType()),
                        new CompStmt(new AssignStmt("a", new ArithExp('+', new ValueExp(new IntValue(2)),
                                new ArithExp('*', new ValueExp(new IntValue(3)), new ValueExp(new IntValue(5))))),
                                new CompStmt(new AssignStmt("b", new ArithExp('+', new VarExp("a"),
                                        new ValueExp(new IntValue(1)))), new PrintStmt(new VarExp("b"))))));
        allStatements.add(ex2);

        IStmt ex3 = new CompStmt(new VarDeclStmt("a", new BoolType()),
                new CompStmt(new VarDeclStmt("v", new IntType()),
                        new CompStmt(new AssignStmt("a", new ValueExp(new BoolValue(true))),
                                new CompStmt(new IfStmt(new VarExp("a"), new AssignStmt("v", new ValueExp(new IntValue(2))),
                                        new AssignStmt("v", new ValueExp(new IntValue(3)))), new PrintStmt(new VarExp("v"))))));
        allStatements.add(ex3);

        IStmt ex4 = new CompStmt(new VarDeclStmt("varf", new StringType()),
                new CompStmt(new AssignStmt("varf", new ValueExp(new StringValue(PathToProgram.path+"test.in"))),
                        new CompStmt(new OpenRFile(new VarExp("varf")),
                                new CompStmt(new VarDeclStmt("varc", new IntType()),
                                        new CompStmt(new readFile(new VarExp("varf"), "varc"),
                                                new CompStmt(new PrintStmt(new VarExp("varc")),
                                                        new CompStmt(new readFile(new VarExp("varf"), "varc"),
                                                                new CompStmt(new PrintStmt(new VarExp("varc")), new closeRFile(new VarExp("varf"))))))))));
        allStatements.add(ex4);

        IStmt ex5 = new CompStmt(new VarDeclStmt("v", new IntType()),
                new CompStmt(new AssignStmt("v", new ValueExp(new IntValue(4))),
                        new CompStmt(new WhileStmt(new RelationalExp(">", new VarExp("v"), new ValueExp(new IntValue(0))),
                                new CompStmt(new PrintStmt(new VarExp("v")), new AssignStmt("v", new ArithExp('-', new VarExp("v"), new ValueExp(new IntValue(1)))))),
                                new PrintStmt(new VarExp("v")))));
        allStatements.add(ex5);

        IStmt ex6 = new CompStmt(new VarDeclStmt("v", new RefType(new IntType())),
                new CompStmt(new NewStmt("v", new ValueExp(new IntValue(20))),
                        new CompStmt(new VarDeclStmt("a", new RefType(new RefType(new IntType()))),
                                new CompStmt(new NewStmt("a", new VarExp("v")),
                                        new CompStmt(new NewStmt("v", new ValueExp(new IntValue(30))),
                                                new PrintStmt(new ReadHeap(new ReadHeap(new VarExp("a")))))))));
        allStatements.add(ex6);

        IStmt ex7 = new CompStmt(new VarDeclStmt("v", new IntType()),
                new CompStmt(new VarDeclStmt("a", new RefType(new IntType())),
                        new CompStmt(new AssignStmt("v", new ValueExp(new IntValue(10))),
                                new CompStmt(new NewStmt("a", new ValueExp(new IntValue(22))),
                                        new CompStmt(new ForkStmt(new CompStmt(new WriteHeap("a", new ValueExp(new IntValue(30))),
                                                new CompStmt(new AssignStmt("v", new ValueExp(new IntValue(32))),
                                                        new CompStmt(new PrintStmt(new VarExp("v")), new PrintStmt(new ReadHeap(new VarExp("a")))
                                                        )))),
                                                new CompStmt(new PrintStmt(new VarExp("v")), new PrintStmt(new ReadHeap(new VarExp("a")))))))));
        allStatements.add(ex7);

        IStmt ex8 = new CompStmt(new VarDeclStmt("v", new BoolType()),
                new CompStmt(new AssignStmt("v", new ValueExp(new IntValue(2))), new PrintStmt(new VarExp("v"))));

        allStatements.add(ex8);

        IStmt ex9 = new CompStmt(new VarDeclStmt("a",new RefType(new IntType())),
                new CompStmt(new VarDeclStmt("b",new RefType(new IntType())),
                        new CompStmt(new VarDeclStmt("v",new IntType()),
                                new CompStmt(new NewStmt("a",new ValueExp(new IntValue(0))),
                                        new CompStmt(new NewStmt("b",new ValueExp(new IntValue(0))),
                                                new CompStmt(new WriteHeap("a",new ValueExp(new IntValue(1))),
                                                        new CompStmt(new WriteHeap("b",new ValueExp(new IntValue(2))),
                                                                new CompStmt(new condAssignment(new RelationalExp("<",new ReadHeap(new VarExp("a")),
                                                                        new ReadHeap(new VarExp("b"))),new ValueExp(new IntValue(100)),new ValueExp(new IntValue(200)),
                                                                        "v"
                                                                        ),new CompStmt(new PrintStmt(new VarExp("v")),
                                                                        new CompStmt(new condAssignment(new RelationalExp(">",
                                                                                new ArithExp('-',new ReadHeap(new VarExp("b")),new ValueExp(new IntValue(2))),
                                                                                new ReadHeap(new VarExp("a"))),
                                                                                new ValueExp(new IntValue(100)),new ValueExp(new IntValue(200)),"v"),
                                                                                new PrintStmt(new VarExp("v"))))))))))));
        allStatements.add(ex9);

        IStmt ex10 = new CompStmt(
                new VarDeclStmt("v1", new RefType(new IntType())),
                new CompStmt(new VarDeclStmt("v2", new RefType(new IntType())),
                        new CompStmt(new VarDeclStmt("v3", new RefType(new IntType())),
                                new CompStmt(new VarDeclStmt("cnt", new IntType()),
                                        new CompStmt(new NewStmt("v1", new ValueExp(new IntValue(2))),
                                                new CompStmt(new NewStmt("v2", new ValueExp(new IntValue(3))),
                                                        new CompStmt(new NewStmt("v3", new ValueExp(new IntValue(4))),
                                                                new CompStmt(new newLatch("cnt", new ReadHeap(new VarExp("v2"))),
                                                                        new CompStmt(new ForkStmt(new CompStmt(new WriteHeap("v1", new ArithExp('*', new ReadHeap(new VarExp("v1")), new ValueExp(new IntValue(10)))),
                                                                                                new CompStmt(new PrintStmt(new ReadHeap(new VarExp("v1"))), new countDown("cnt")
                                                                                                ))),
                                                                                new CompStmt(new ForkStmt(new CompStmt(new WriteHeap("v2", new ArithExp('*', new ReadHeap(new VarExp("v2")), new ValueExp(new IntValue(10)))),
                                                                                                        new CompStmt(new PrintStmt(new ReadHeap(new VarExp("v2"))), new countDown("cnt")
                                                                                                        ))),
                                                                                        new CompStmt(
                                                                                                new ForkStmt(new CompStmt(new WriteHeap("v3", new ArithExp('*', new ReadHeap(new VarExp("v3")), new ValueExp(new IntValue(10)))),
                                                                                                                new CompStmt(new PrintStmt(new ReadHeap(new VarExp("v3"))), new countDown("cnt")
                                                                                                                ))),
                                                                                                new CompStmt(new awaitStmt("cnt"), new CompStmt(new PrintStmt(new ValueExp(new IntValue(100))), new CompStmt(
                                                                                                        new countDown("cnt"), new PrintStmt(new ValueExp(new IntValue(100)))
                                                                                                                ))))))))))))));
       allStatements.add(ex10);
        return FXCollections.observableArrayList(allStatements);
    }
}