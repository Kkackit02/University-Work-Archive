package Builder;

public class WoodHouseBuilder extends Builder {
    @Override
    public void buildWalls() {
        house.setWalls("통나무");
    }

    @Override
    public void buildDoors() {
        house.setDoors("참나무");
    }

    @Override
    public void buildRoof() {
        house.setRoof("물푸레나무");
    }

    @Override
    public void buildWindows() {
        house.setWindows("티크나무");
    }

    @Override
    public House getHouse() {
        return house;
    }
}
