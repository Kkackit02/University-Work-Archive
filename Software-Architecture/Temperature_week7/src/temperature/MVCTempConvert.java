package temperature;

public class MVCTempConvert {
    public static void main(String args[]) {
        TemperatureModel temperature = new TemperatureModel();
        new TemperatureGUI(temperature, 100, 500);
        new SliderGUI(temperature, 500, 100);
        new GraphGUI(temperature, 100, 100);
    }
}
