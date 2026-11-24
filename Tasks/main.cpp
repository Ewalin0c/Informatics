
#include <SFML/Graphics.hpp>

int main()
{
    // Создаём графическое окно 500×500
    sf::RenderWindow window(sf::VideoMode(500, 500), "Laboratornaya 3");

    // Размеры сетки и ячеек
    const int N = 10;
    const int cellSize = 500 / N;

    // Массив для хранения ячеек
    sf::RectangleShape cells[N][N];

    // Инициализируем ячейки вложенными циклами
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            // Устанавливаем размер ячейки
            cells[i][j].setSize(sf::Vector2f(cellSize, cellSize));

            // Устанавливаем положение ячейки
            cells[i][j].setPosition(j * cellSize, i * cellSize);

            // Проверяем, должна ли ячейка быть закрашенной
            if (i >= 1 && i <= N / 2 && j >= N / 2 - i && j < N / 2 + i)
            {
                cells[i][j].setFillColor(sf::Color::Green);
            }
            else
            {
                cells[i][j].setFillColor(sf::Color::White);
            }

            // Устанавливаем цвет границы
            cells[i][j].setOutlineColor(sf::Color::Black);
            cells[i][j].setOutlineThickness(-1);
        }
    }

    // Основной цикл программы
    while (window.isOpen())
    {
        sf::Event event;

        // Обрабатываем события
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Очищаем окно
        window.clear(sf::Color::White);

        // Отрисовываем все ячейки
        for (int i = 0; i < N; ++i)
        {
            for (int j = 0; j < N; ++j)
            {
                window.draw(cells[i][j]);
            }
        }

        // Отображаем результат
        window.display();
    }

    return 0;
}
