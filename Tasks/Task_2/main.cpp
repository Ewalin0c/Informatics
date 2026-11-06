#include <SFML/Graphics.hpp>
#include <functional>
#include <cmath>

// Функция для отрисовки графика
void drawGraph(sf::RenderWindow& window, std::function<float(float)> func,
    float xMin, float xMax, float scaleX, float scaleY, sf::Color color) {
    sf::VertexArray graph(sf::LinesStrip);

    for (float x = xMin; x <= xMax; x += 0.1f) {
        float y = func(x);                 // вычисление значения функции

        float screenX = 400 + x * scaleX;  // преобразование координат в экранные
        float screenY = 300 - y * scaleY;

        graph.append(sf::Vertex(sf::Vector2f(screenX, screenY), color));
    }

    window.draw(graph);
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Приложение для вывода графиков");

    sf::CircleShape userPoint(5);          // пользовательская точка, радиус 5 пикселей
    userPoint.setFillColor(sf::Color::Red);
    bool userPointExists = false;

    // 1 _ Загрузка шрифта (допишите код)
    sf::Font font;
    font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf");
    // у меня почему-то программа не видит шрифт, если я указываю не полный путь,
    // хотя он лежит с правильным названием в папке рядом с ехе. поэтому пришлось так

    // 2 _ Текст для отображения координат: размер 20, позиция (10,10), цвет белый,
    //     переменная coordinatesText (допишите код)
    sf::Text coordinatesText;
    coordinatesText.setFont(font);
    coordinatesText.setCharacterSize(20);
    coordinatesText.setPosition(10, 10);
    coordinatesText.setFillColor(sf::Color::White);

    // Оси X и Y
    sf::VertexArray xAxis(sf::Lines, 2);
    xAxis[0].position = sf::Vector2f(50, 300);   xAxis[0].color = sf::Color::White;
    xAxis[1].position = sf::Vector2f(750, 300);  xAxis[1].color = sf::Color::White;
    sf::VertexArray yAxis(sf::Lines, 2);
    yAxis[0].position = sf::Vector2f(400, 50);   yAxis[0].color = sf::Color::White;
    yAxis[1].position = sf::Vector2f(400, 550);  yAxis[1].color = sf::Color::White;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                    // Преобразование экранных координат в «математические»
                    float mathX = (mousePos.x - 400) / 30.0f;
                    float mathY = -(mousePos.y - 300) / 10.0f;

                    userPoint.setPosition(mousePos.x - userPoint.getRadius(),
                        mousePos.y - userPoint.getRadius());
                    userPointExists = true;

                    // 3 _ Допишите логику проверки точки по mathX и mathY!

                    // Вычисляем значения двух функций
                    float function1 = mathX * mathX - mathX + 4;
                    float function2 = mathX + 10;

                    // Проверяем, находится ли точка на границе графиков
                    if (std::abs(mathY - function1) < 0.3 ||
                        std::abs(mathY - function2) < 0.3) {
                        coordinatesText.setString("Point is on the graph");
                    }
                    else {
                        // Определяем область, в которой находится точка
                        int area = 0;

                        if (mathY > function1 && mathY < function2) {
                            area = 1;
                        }
                        else if (mathY > function1 && mathY > function2) {
                            area = 2;
                        }
                        else if (mathY < function1 && mathY > function2 && mathX < (1 - std::sqrt(7.0f))) {
                            area = 3;
                        }
                        else if (mathY < function1 && mathY > function2 && mathX > (1 + std::sqrt(7.0f))) {
                            area = 4;
                        }
                        else if (mathY < function1 && mathY < function2) {
                            area = 5;
                        }

                        // Выводим номер области
                        coordinatesText.setString("Coordinates: (" + std::to_string(mathX) +
                            ", " + std::to_string(mathY) + ") - Area " + std::to_string(area));
                    }
                }
            }
        }

        // 4 _ Очистка экрана (допишите код)
        window.clear(sf::Color::Black);

        window.draw(xAxis);
        window.draw(yAxis);

        // 5 _ Замените на графики вашего варианта
        drawGraph(window, [](float x) { return x * x - x + 4; }, -10, 10, 30, 10, sf::Color::Blue);
        drawGraph(window, [](float x) { return x + 10; }, -10, 10, 30, 10, sf::Color::Red);

        if (userPointExists) {
            window.draw(userPoint);
            window.draw(coordinatesText);
        }

        window.display();
    }

    return 0;
}
