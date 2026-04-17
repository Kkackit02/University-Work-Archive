package Singleton;

public class Client {
    public static void main(String[] args) {
        ChocolateBoiler boiler1 = ChocolateBoiler.getInstance();
        ChocolateBoiler boiler2 = ChocolateBoiler.getInstance();
        ChocolateBoiler boiler3 = ChocolateBoiler.getInstance();

        System.out.println("=====Check Singlton=====");
        System.out.println(boiler1.toString());
        System.out.println(boiler2.toString());
        System.out.println(boiler3.toString());

        System.out.println("\n=====Chocolate Boilor=====");
        boiler1.fill();
        boiler1.boil();
        boiler1.drain();
    }
}