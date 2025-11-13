package AbstractFactory;

public abstract class ArchitectureToolkit {
    private static final EmberToolkit emberToolkit = new EmberToolkit();
    private static final EnginolaToolkit enginolaToolkit = new EnginolaToolkit();

    public abstract CPU createCPU();
    public abstract MMU createMMU();

    public static ArchitectureToolkit getFactory(String name) {
        if (name.equals("EN")) {
            return enginolaToolkit;
        } else if (name.equals("EM")) {
            return emberToolkit;
        }
        return null;
    }
}
