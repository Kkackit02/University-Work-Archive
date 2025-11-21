package Builder;

public class Main {
    public static void main(String[] args) {
        Builder concreteHouseBuilder = new ConcreteHouseBuilder();
        Director director = new Director(concreteHouseBuilder);
        director.build();
        House house1 = director.getHouse();
        System.out.println(house1);

        Builder woodHouseBuilder = new WoodHouseBuilder();
        director = new Director(woodHouseBuilder);
        director.build();
        House house2 = director.getHouse();
        System.out.println(house2);
    }
}