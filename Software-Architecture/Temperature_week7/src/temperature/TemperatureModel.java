package temperature;

public class TemperatureModel extends java.util.Observable {
	
	public double getC() {
		return temperatureC;
	}
	
	public void setC(double tempC) {
		temperatureC = tempC;
		setChanged();
		this.notifyObservers();
	}
	
	public void notifyObservers()
	{
		super.notifyObservers();
	}
	
	private double temperatureC = 27;

}
