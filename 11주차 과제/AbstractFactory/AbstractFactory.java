package AbstractFactory;

// AbstractProduct A
abstract class CPU {}

// AbstractProduct B
abstract class MMU {}

// ConcreteProduct
class EmberCPU extends CPU {
    public EmberCPU() {
        System.out.println("Ember CPU Create!!");
    }
}

class EnginolaCPU extends CPU {
    public EnginolaCPU() {
        System.out.println("Enginola CPU Create!!");
    }
}

class EmberMMU extends MMU {
    public EmberMMU() {
        System.out.println("Ember MMUCreate!!");
    }
}

class EnginolaMMU extends MMU {
    public EnginolaMMU() {
        System.out.println("Enginola MMU Create!!");
    }
}


// AbstractFactory
abstract class ArchitectureToolkit {
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

// ConcreteFactory
class EmberToolkit extends ArchitectureToolkit {
    @Override
    public CPU createCPU() {
        return new EmberCPU();
    }

    @Override
    public MMU createMMU() {
        return new EmberMMU();
    }
}

class EnginolaToolkit extends ArchitectureToolkit {
    @Override
    public CPU createCPU() {
        return new EnginolaCPU();
    }

    @Override
    public MMU createMMU() {
        return new EnginolaMMU();
    }
}

// Client
public class AbstractFactory {
    public static void main(String args[]) {
        ArchitectureToolkit en = ArchitectureToolkit.getFactory("EN");
        ArchitectureToolkit em = ArchitectureToolkit.getFactory("EM");
        
        CPU cpu = en.createCPU();
        MMU mmu = em.createMMU();
    }
}
