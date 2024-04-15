package controller;

import customexception.MyException;
import datatypes.MyIList;
import datatypes.MyIStack;
import model.stmt.IStmt;
import model.PrgState;
import model.value.RefValue;
import model.value.Value;
import repository.MyIRepository;

import java.util.*;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class MyContoller implements MyIController{
    private MyIRepository repo;
    private MyIList<String> outputForConsole;
    private ExecutorService executor;

    public MyContoller(MyIRepository repository){
        repo = repository;
    }


    public void oneStepForAllPrg(List<PrgState>prgList) throws InterruptedException {
        prgList.forEach(prgState -> {
            try {
                repo.logPrgStateExec(prgState);
            } catch (MyException e) {
                throw new RuntimeException(e);
            }
        });
        List<Callable<PrgState>> callList = prgList.stream()
                .map((PrgState p) -> (Callable<PrgState>) (() -> {return p.oneStep();}))
                .collect(Collectors.toList());
        List<PrgState>newPrgList = executor.invokeAll(callList).stream().
                map(future -> {try{return future.get();}
                catch(InterruptedException | ExecutionException exception){
                throw new RuntimeException(exception);}
                }).filter(p->p!=null).collect(Collectors.toList());
        prgList.addAll(newPrgList);
        prgList.forEach(prg-> {
            try {
                repo.logPrgStateExec(prg);
            } catch (MyException e) {
                throw new RuntimeException(e);
            }
        });
        repo.setPrgList(prgList);
    }

    public void allSteps() throws MyException, InterruptedException {

        executor = Executors.newFixedThreadPool(2);
        List<PrgState> prgList = removeCompletedPrg(repo.getPrgList());
        while(prgList.size()>0){
            PrgState state = prgList.get(prgList.size()-1);
            state.getHeap_table().setContent(safeGarbageCollector(getAddrFromSymTable(state.getSymbols_table().getContent().values()),
                    state.getHeap_table().getContent()));
            oneStepForAllPrg(prgList);
            prgList = removeCompletedPrg(repo.getPrgList());
        }
        executor.shutdownNow();
        System.out.println(outputForConsole);
        repo.setPrgList(prgList);
    }

    private Map<Integer, Value> unsafeGarbageCollector(List<Integer> symTableAddr, Map<Integer, Value> heap) {
        return heap.entrySet().stream()
                .filter(e -> symTableAddr.contains(e.getKey()))
                .collect(Collectors.toMap(Map.Entry::getKey, Map.Entry::getValue));
    }

    private List<Integer> getAddrFromHeap(Collection<Value> heapValues) {
        return heapValues.stream()
                .filter(v -> v instanceof RefValue)
                .map(v -> {RefValue v1 = (RefValue)v; return v1.getAddress();})
                .collect(Collectors.toList());
    }

    private Map<Integer, Value> safeGarbageCollector(List<Integer> symTableAddr, Map<Integer, Value> heap) {
        List<Integer> heapAddr = getAddrFromHeap(heap.values());
        return heap.entrySet().stream()
                .filter(e -> (symTableAddr.contains(e.getKey()) || heapAddr.contains(e.getKey())))
                .collect(Collectors.toMap(Map.Entry::getKey, Map.Entry::getValue));
    }


    public void conservativeGarbageCollector(List<PrgState> programStates) {
        List<Integer> symTableAddresses = Objects.requireNonNull(programStates.stream()
                        .map(p -> getAddrFromSymTable(p.getSymbols_table().values()))
                        .map(Collection::stream)
                        .reduce(Stream::concat).orElse(null))
                .collect(Collectors.toList());
        programStates.forEach(p -> p.getHeap_table().setContent((HashMap<Integer, Value>) safeGarbageCollector(symTableAddresses, p.getHeap_table().getContent())));
    }

    private List<Integer> getAddrFromSymTable(Collection<Value> symTableValues) {
        return symTableValues.stream()
                .filter(v -> v instanceof RefValue)
                .map(v -> {RefValue v1 = (RefValue)v; return v1.getAddress();})
                .collect(Collectors.toList());
    }

    public List<PrgState>removeCompletedPrg(List<PrgState>inPrgList){
        outputForConsole = inPrgList.get(inPrgList.size()-1).getOutput();
        return inPrgList.stream().filter(p->p.isNotCompleted()).collect(Collectors.toList());
    }

    public List<PrgState>getProgramStates(){
        return this.repo.getPrgList();
    }

    public void setProgramStates(List<PrgState>states){
        this.repo.setPrgList(states);
    }

    public void oneStep() throws InterruptedException {
        executor = Executors.newFixedThreadPool(2);
        List<PrgState> programStates = removeCompletedPrg(repo.getPrgList());
        oneStepForAllPrg(programStates);
        conservativeGarbageCollector(programStates);
        executor.shutdownNow();
    }

    public String getOutputOfLastState(PrgState state){
        return state.getOutput().toString();
    }

}
