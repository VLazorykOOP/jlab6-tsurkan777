import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.util.*;

// ===== Власне виключення =====
class MyArithmeticException extends ArithmeticException {
    public MyArithmeticException(String message) {
        super(message);
    }
}

public class MatrixSumGUI extends JFrame {
    private JTable table;
    private DefaultTableModel tableModel;
    private JButton loadButton, computeButton;
    private JLabel resultLabel;

    private double[][] matrix;
    private int n;

    public MatrixSumGUI() {
        setTitle("Matrix Sum GUI");
        setSize(600, 400);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new BorderLayout());

        // Панель для кнопок
        JPanel topPanel = new JPanel();
        loadButton = new JButton("Завантажити матрицю з файлу");
        computeButton = new JButton("Обчислити суму");
        computeButton.setEnabled(false); // спочатку кнопка недоступна
        topPanel.add(loadButton);
        topPanel.add(computeButton);
        add(topPanel, BorderLayout.NORTH);

        // Таблиця для відображення матриці
        tableModel = new DefaultTableModel();
        table = new JTable(tableModel);
        JScrollPane scrollPane = new JScrollPane(table);
        add(scrollPane, BorderLayout.CENTER);

        // Панель для результату
        JPanel bottomPanel = new JPanel();
        resultLabel = new JLabel("Результат: ");
        bottomPanel.add(resultLabel);
        add(bottomPanel, BorderLayout.SOUTH);

        // Дії кнопок
        loadButton.addActionListener(e -> loadMatrixFromFile());
        computeButton.addActionListener(e -> computeSum());
    }

    private void loadMatrixFromFile() {
        JFileChooser fileChooser = new JFileChooser();
        int ret = fileChooser.showOpenDialog(this);
        if (ret == JFileChooser.APPROVE_OPTION) {
            File file = fileChooser.getSelectedFile();
            try (Scanner sc = new Scanner(file)) {
                n = sc.nextInt();
                if (n <= 0 || n > 15) throw new InputMismatchException("Неправильний розмір матриці");
                matrix = new double[n][n];
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < n; j++) {
                        if (!sc.hasNextDouble()) throw new InputMismatchException("Невірний формат числа у файлі");
                        matrix[i][j] = sc.nextDouble();
                    }
                }

                // Відображення у таблиці
                tableModel.setRowCount(n);
                tableModel.setColumnCount(n);
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < n; j++) {
                        tableModel.setValueAt(matrix[i][j], i, j);
                    }
                }
                computeButton.setEnabled(true);
                resultLabel.setText("Матриця завантажена. Натисніть 'Обчислити суму'.");

            } catch (FileNotFoundException ex) {
                JOptionPane.showMessageDialog(this, "Файл не знайдено!", "Помилка", JOptionPane.ERROR_MESSAGE);
            } catch (InputMismatchException ex) {
                JOptionPane.showMessageDialog(this, "Невірний формат даних у файлі!\n" + ex.getMessage(),
                        "Помилка", JOptionPane.ERROR_MESSAGE);
            } catch (Exception ex) {
                JOptionPane.showMessageDialog(this, "Помилка: " + ex.getMessage(), "Помилка", JOptionPane.ERROR_MESSAGE);
            }
        }
    }

    private void computeSum() {
        try {
            double maxBelow = Double.NEGATIVE_INFINITY;
            for (int i = 1; i < n; i++) {
                for (int j = 0; j < i; j++) {
                    if (matrix[i][j] > maxBelow) maxBelow = matrix[i][j];
                }
            }

            double sum = 0;
            boolean found = false;
            for (int i = 0; i < n; i++) {
                for (int j = i; j < n; j++) {
                    if (matrix[i][j] > maxBelow) {
                        sum += matrix[i][j];
                        found = true;
                    }
                }
            }

            // Генерація власного виключення, якщо сума > 1000
            if (sum > 1000) throw new MyArithmeticException("Сума занадто велика!");

            if (found) {
                resultLabel.setText("Сума елементів, більших за нижчі: " + sum);
            } else {
                resultLabel.setText("Немає елементів, більших за нижчі.");
            }

        } catch (MyArithmeticException ex) {
            JOptionPane.showMessageDialog(this, ex.getMessage(), "Власне виключення", JOptionPane.WARNING_MESSAGE);
        } catch (Exception ex) {
            JOptionPane.showMessageDialog(this, "Помилка під час обчислення: " + ex.getMessage(),
                    "Помилка", JOptionPane.ERROR_MESSAGE);
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            MatrixSumGUI gui = new MatrixSumGUI();
            gui.setVisible(true);
        });
    }
}
