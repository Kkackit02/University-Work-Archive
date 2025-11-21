package Builder;

public class House {
    private String roof;
    private String doors;
    private String windows;
    private String walls;

    public void setRoof(String roof) {
        this.roof = roof;
    }

    public void setDoors(String doors) {
        this.doors = doors;
    }

    public void setWindows(String windows) {
        this.windows = windows;
    }

    public void setWalls(String walls) {
        this.walls = walls;
    }

    @Override
    public String toString() {
        return "이집은 [" + roof + " 지붕과, " + walls + " 벽과, " + windows + " 창문과, " + doors + " 문으로 지어짐]";
    }
}