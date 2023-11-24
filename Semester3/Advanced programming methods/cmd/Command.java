package cmd;

public abstract class Command {
    private String key;
    private String description;
    public Command(String constructorKey,String constructorDesc){
        this.key = constructorKey;
        this.description = constructorDesc;
    }
    public abstract void execute();
    public String getKey(){
        return this.key;
    }
    public String getDescription(){
        return this.description;
    }
}
