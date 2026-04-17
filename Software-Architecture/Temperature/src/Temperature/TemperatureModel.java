package Temperature;

public class TemperatureModel extends java.util.Observable {
    private double temperatureC = 27;

    public double getC() {
        return temperatureC;
    }

    public void setC(double tempC) {
        temperatureC = tempC;
        setChanged();
        this.notifyObservers();
    }

    public void notifyObservers() {
        super.notifyObservers();
    }
}
