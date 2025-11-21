package AbstractFactory;

public class Client {
    public static void main(String args[]) {
        ArchitectureToolkit en = ArchitectureToolkit.getFactory("EN");
        ArchitectureToolkit em = ArchitectureToolkit.getFactory("EM");
        
        CPU cpu = en.createCPU();
        MMU mmu = em.createMMU();
    }
}