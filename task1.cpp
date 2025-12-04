import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class SpeedControlFrame extends JFrame {
    private int x = 50;       // Поточна позиція точки
    private int y = 100;
    private int speed = 5;    // Поточна швидкість
    private final int SPEED_STEP = 2; // Зміна швидкості при натисканні кнопки

    private Timer timer;

    public SpeedControlFrame() {
        setTitle("Управління швидкістю точки");
        setSize(500, 300);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new BorderLayout());

        // Панель для кнопок
        JPanel buttonsPanel = new JPanel();
        JButton increaseBtn = new JButton("Збільшити швидкість");
        JButton decreaseBtn = new JButton("Зменшити швидкість");
        buttonsPanel.add(increaseBtn);
        buttonsPanel.add(decreaseBtn);
        add(buttonsPanel, BorderLayout.SOUTH);

        // Панель для малювання точки
        DrawPanel drawPanel = new DrawPanel();
        add(drawPanel, BorderLayout.CENTER);

        // Дії кнопок
        increaseBtn.addActionListener(e -> speed += SPEED_STEP);
        decreaseBtn.addActionListener(e -> {
            speed -= SPEED_STEP;
            if (speed < 0) speed = 0; // не дозволяємо від'ємну швидкість
        });

        // Таймер для руху точки
        timer = new Timer(30, new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                x += speed;
                if (x > drawPanel.getWidth()) x = 0; // точка повертається з початку
                drawPanel.repaint();
            }
        });
        timer.start();
    }

    // Панель для малювання
    private class DrawPanel extends JPanel {
        @Override
        protected void paintComponent(Graphics g) {
            super.paintComponent(g);
            g.setColor(Color.RED);
            g.fillOval(x, y, 20, 20); // малюємо червону точку
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            SpeedControlFrame frame = new SpeedControlFrame();
            frame.setVisible(true);
        });
    }
}
