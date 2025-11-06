package Singleton;

public class ChocolateBoiler {
    private boolean empty;
    private boolean boiled;
    private static ChocolateBoiler uniqueInstance;

    private ChocolateBoiler() {
        empty = true;
        boiled = false;
    }

    public static synchronized ChocolateBoiler getInstance() {
        if (uniqueInstance == null) {
            uniqueInstance = new ChocolateBoiler();
        }
        return uniqueInstance;
    }

    public void fill() {
        if (isEmpty()) {
            System.out.println("Fill ChocolateBoiler");
            empty = false;
            boiled = false;
            System.out.println("-Empty:" + empty + ", boiled:" + boiled);
        }
    }

    public void drain() {
        if (!isEmpty() && isBoiled()) {
            System.out.println("Drain ChocolateBoiler");
            empty = true;
            System.out.println("-Empty:" + empty + ", boiled:" + boiled);
        }
    }

    public void boil() {
        if (!isEmpty() && !isBoiled()) {
            System.out.println("Boil ChocolateBoiler");
            boiled = true;
            System.out.println("-Empty:" + empty + ", boiled:" + boiled);
        }
    }

    public boolean isEmpty() {
        return empty;
    }

    public boolean isBoiled() {
        return boiled;
    }
}