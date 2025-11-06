package temperature;

import java.awt.Button;
import java.awt.Frame;
import java.awt.Label;
import java.awt.Panel;
import java.awt.TextField;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.util.Observable;
import java.util.Observer;

public class TemperatureGUI implements Observer {
    private String label;
    private TemperatureModel model;
    private Frame temperatureFrame;
    private TextField display = new TextField();
    private Button upButton = new Button("Raise");
    private Button downButton = new Button("Lower");

    public TemperatureGUI(TemperatureModel model, int h, int v) {
        this.label = "Celsius Temperature";
        this.model = model;
        temperatureFrame = new Frame(label);
        temperatureFrame.add("North", new Label(label));
        temperatureFrame.add("Center", display);
        Panel buttons = new Panel();
        buttons.add(upButton);
        buttons.add(downButton);
        temperatureFrame.add("South", buttons);
        temperatureFrame.addWindowListener(new CloseListener());
        model.addObserver(this); // Connect the View to the Model
        temperatureFrame.setSize(200, 200);
        temperatureFrame.setLocation(h, v);
        temperatureFrame.setVisible(true);

        setDisplay("" + model.getC());
        addUpListener(new UpListener());
        addDownListener(new DownListener());
        addDisplayListener(new DisplayListener());
    }

    public double getDisplay() {
        double result = 0.0;
        try {
            result = Double.valueOf(display.getText()).doubleValue();
        } catch (NumberFormatException e) {
            // Handle error if text is not a valid number
        }
        return result;
    }

    public void setDisplay(String s) {
        display.setText(s);
    }

    public void addDisplayListener(ActionListener a) {
        display.addActionListener(a);
    }

    public void addUpListener(ActionListener a) {
        upButton.addActionListener(a);
    }

    public void addDownListener(ActionListener a) {
        downButton.addActionListener(a);
    }

    protected TemperatureModel model() {
        return model;
    }

    @Override
    public void update(Observable t, Object o) {
        setDisplay("" + model().getC());
    }

    class UpListener implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            model().setC(model().getC() + 1.0);
        }
    }

    class DownListener implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            model().setC(model().getC() - 1.0);
        }
    }

    class DisplayListener implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            double value = getDisplay();
            model().setC(value);
        }
    }

    public static class CloseListener extends WindowAdapter {
        @Override
        public void windowClosing(WindowEvent e) {
            e.getWindow().setVisible(false);
            System.exit(0);
        }
    }
}
