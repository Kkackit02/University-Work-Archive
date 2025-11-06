package temperature;

import java.awt.Canvas;
import java.awt.Color;
import java.awt.Frame;
import java.awt.Graphics;
import java.awt.Panel;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.util.Observable;
import java.util.Observer;

public class GraphGUI extends Frame implements Observer {
    private TemperatureModel model;
    private Canvas gauges;
    private TemperatureGauge _farenheit;

    public GraphGUI(TemperatureModel model, int h, int v) {
        super("Temperature Gauge");
        this.model = model;
        _farenheit = new TemperatureGauge(-200, 300);
        Panel Top = new Panel();
        add("North", Top);
        gauges = new TemperatureCanvas(_farenheit);
        gauges.setSize(500, 1500); // This size seems very large, might be a typo in the
       // original
        add("Center", gauges);
        setSize(280, 280);
        setLocation(h, v);
        setVisible(true);
        model.addObserver(this);
    }

    @Override
    public void update(Observable obs, Object o) {
        repaint();
    }

    @Override
    public void paint(Graphics g) {
        int farenheit = (int) model.getC();
        _farenheit.set(farenheit);
        gauges.repaint();
        super.paint(g);
    }

    class TemperatureCanvas extends Canvas {
        private TemperatureGauge _farenheit;
        private static final int width = 20;
        private static final int top = 20;
        private static final int left = 100;
        private static final int right = 250; // Not used
        private static final int height = 150;

        public TemperatureCanvas(TemperatureGauge farenheit) {
            _farenheit = farenheit;
        }

        @Override
        public void paint(Graphics g) {
            g.setColor(Color.black);
            g.drawRect(left, top, width, height);
            g.setColor(Color.red);
            g.fillOval(left + width / 2, top + height - width / 3, width * 2, width * 2); //
       // Thermometer bulb
            g.setColor(Color.black);
            g.drawOval(left + width / 2, top + height - width / 3, width * 2, width * 2); //
       // Thermometer bulb outline
            g.setColor(Color.white);
            g.fillRect(left + 1, top + 1, width - 1, height - 1); // Clear inside of
       // thermometer
            g.setColor(Color.red);
            long redtop = height * (_farenheit.get() - _farenheit.getMax()) /
       (_farenheit.getMin() - _farenheit.getMax());
            g.fillRect(left + 1, top + (int) redtop, width - 1, height - (int) redtop); //
       // Fill with red based on temperature
        }
    }

    class TemperatureGauge {
        private int Max, Min, current;

        public TemperatureGauge(int min, int max) {
            Min = min;
            Max = max;
        }

        public void set(int level) {
            current = level;
        }

        public int get() {
            return current;
        }

        public int getMax() {
            return Max;
        }

        public int getMin() {
            return Min;
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
