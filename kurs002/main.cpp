#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <algorithm>
#include <random>
#include <ctime>
#include <iostream>
#include <string>
#include <Windows.h>
#include <locale>
#include <codecvt>
#include <fstream>
#include <sstream>

using namespace std;

const double epsilon = 1e-6;
const int RANGE = 100;
const float CONTROL_WIDTH = 400.0f;
const float DISPLAY_WIDTH = 800.0f;
const float WINDOW_HEIGHT = 600.0f;
const float SCALE = 6.0f;
const float OFFSET_X = CONTROL_WIDTH + (DISPLAY_WIDTH - RANGE * SCALE) / 2.0f;
const float POINT_RADIUS = 3.0f;
const int NUM_RANDOM_POINTS = 50;

struct Point {
    int x, y;
    Point(int x = 0, int y = 0) : x(x), y(y) {}
};

double distance(const Point& a, const Point& b) {
    return hypot(b.x - a.x, b.y - a.y);
}

vector<Point> sortPoints(const vector<Point>& points) {
    double cx = 0, cy = 0;
    for (const auto& p : points) {
        cx += p.x;
        cy += p.y;
    }
    cx /= 4;
    cy /= 4;

    auto comparator = [&](const Point& a, const Point& b) {
        return atan2(a.y - cy, a.x - cx) < atan2(b.y - cy, b.x - cx);
        };

    vector<Point> sortedPoints = points;
    sort(sortedPoints.begin(), sortedPoints.end(), comparator);
    return sortedPoints;
}

bool isConvex(const vector<Point>& points) {
    if (points.size() != 4) return false;

    double firstCross = 0.0;
    for (int i = 0; i < 4; i++) {
        const Point& A = points[i];
        const Point& B = points[(i + 1) % 4];
        const Point& C = points[(i + 2) % 4];
        double dx1 = B.x - A.x;
        double dy1 = B.y - A.y;
        double dx2 = C.x - B.x;
        double dy2 = C.y - B.y;
        double cross = dx1 * dy2 - dy1 * dx2;

        if (abs(cross) < epsilon) return false;

        if (i == 0) {
            firstCross = cross;
        }
        else if ((cross > 0) != (firstCross > 0)) {
            return false;
        }
    }
    return true;
}

bool isIsoscelesTrapezoid(const vector<Point>& points) {
    if (!isConvex(points)) return false;

    double cross1 = (points[1].x - points[0].x) * (points[3].y - points[2].y) -
        (points[1].y - points[0].y) * (points[3].x - points[2].x);
    double cross2 = (points[2].x - points[1].x) * (points[0].y - points[3].y) -
        (points[2].y - points[1].y) * (points[0].x - points[3].x);

    bool parallel1 = abs(cross1) < epsilon;
    bool parallel2 = abs(cross2) < epsilon;

    if (parallel1 && !parallel2) {
        return abs(distance(points[1], points[2]) - distance(points[3], points[0])) < epsilon;
    }
    if (parallel2 && !parallel1) {
        return abs(distance(points[0], points[1]) - distance(points[2], points[3])) < epsilon;
    }
    return false;
}

sf::Vector2f toSFML(const Point& p) {
    return { OFFSET_X + p.x * SCALE, WINDOW_HEIGHT - p.y * SCALE };
}

void drawText(sf::RenderWindow& window, const wstring& text, float x, float y,
    const sf::Font& font, int size = 20, sf::Color color = sf::Color::White) {
    sf::Text sfText;
    sfText.setFont(font);
    sfText.setString(text);
    sfText.setCharacterSize(size);
    sfText.setPosition(x, y);
    sfText.setFillColor(color);
    window.draw(sfText);
}

void drawButton(sf::RenderWindow& window, const wstring& label, const sf::FloatRect& rect,
    bool isHovered, const sf::Font& font) {
    sf::RectangleShape button(sf::Vector2f(rect.width, rect.height));
    button.setPosition(rect.left, rect.top);
    button.setFillColor(isHovered ? sf::Color::Cyan : sf::Color::Blue);
    window.draw(button);

    sf::Color textColor = isHovered ? sf::Color::Black : sf::Color::White;
    drawText(window, label, rect.left + 10, rect.top + 10, font, 20, textColor);
}

void drawInputField(sf::RenderWindow& window, const wstring& label, const string& value,
    const sf::FloatRect& rect, const sf::Font& font, bool isActive = false) {
    sf::RectangleShape field(sf::Vector2f(rect.width, rect.height));
    field.setPosition(rect.left, rect.top);
    field.setFillColor(isActive ? sf::Color(200, 255, 200) : sf::Color::White);
    window.draw(field);

    drawText(window, label, rect.left + 10, rect.top - 20, font);

    wstring_convert<codecvt_utf8_utf16<wchar_t>> converter;
    drawText(window, converter.from_bytes(value), rect.left + 10, rect.top + 5, font, 20, sf::Color::Black);
}

void loadPointsFromFile(vector<Point>& points) {
    ifstream file("points.txt");
    if (!file.is_open()) {
        cerr << "Не удалось открыть файл points.txt" << endl;
        return;
    }

    points.clear();
    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        int x, y;
        if (iss >> x >> y) {
            if (x >= 0 && x <= RANGE && y >= 0 && y <= RANGE) {
                points.emplace_back(x, y);
            }
            else {
                cerr << "Координата вне диапазона: " << x << " " << y << endl;
            }
        }
        else {
            cerr << "Некорректная строка: " << line << endl;
        }
    }
    file.close();
    wcout << L"Загружено " << points.size() << L" точек из файла." << endl;
}

int main() {
    sf::Font font;
    if (!font.loadFromFile("arial.ttf") && !font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
        cerr << "Не удалось загрузить шрифт Arial" << endl;
        return 1;
    }

    const float WINDOW_WIDTH = CONTROL_WIDTH + DISPLAY_WIDTH;
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), L"Отображение точек и трапеций");

    enum class Mode { None, Random, Manual, File };
    Mode currentMode = Mode::None;
    vector<Point> points;
    vector<vector<Point>> trapezoids;
    bool showTrapezoids = false;

    string inputX, inputY;
    bool inputActiveX = false, inputActiveY = false;

    const sf::FloatRect buttonRandom(50, 50, 300, 50);
    const sf::FloatRect buttonFile(50, 150, 300, 50);
    const sf::FloatRect buttonManual(50, 250, 300, 50);
    const sf::FloatRect buttonAddPoint(50, 400, 300, 50);
    const sf::FloatRect buttonBuild(50, 475, 300, 50);
    const sf::FloatRect inputFieldX(50, 350, 150, 30);
    const sf::FloatRect inputFieldY(200, 350, 150, 30);

    default_random_engine generator(static_cast<unsigned>(time(nullptr)));
    uniform_int_distribution<int> distribution(0, RANGE);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                if (buttonRandom.contains(static_cast<sf::Vector2f>(mousePos))) {
                    currentMode = Mode::Random;
                    points.clear();
                    trapezoids.clear();
                    showTrapezoids = false;
                    for (int i = 0; i < NUM_RANDOM_POINTS; i++) {
                        points.emplace_back(distribution(generator), distribution(generator));
                    }
                }
                else if (buttonFile.contains(static_cast<sf::Vector2f>(mousePos))) {
                    currentMode = Mode::File;
                    loadPointsFromFile(points);
                    trapezoids.clear();
                    showTrapezoids = false;
                }
                else if (buttonManual.contains(static_cast<sf::Vector2f>(mousePos))) {
                    currentMode = Mode::Manual;
                    points.clear();
                    trapezoids.clear();
                    showTrapezoids = false;
                    inputX.clear();
                    inputY.clear();
                    inputActiveX = false;
                    inputActiveY = false;
                }
                else if (currentMode == Mode::Manual && inputFieldX.contains(static_cast<sf::Vector2f>(mousePos))) {
                    inputActiveX = true;
                    inputActiveY = false;
                }
                else if (currentMode == Mode::Manual && inputFieldY.contains(static_cast<sf::Vector2f>(mousePos))) {
                    inputActiveX = false;
                    inputActiveY = true;
                }
                else if (currentMode == Mode::Manual && buttonAddPoint.contains(static_cast<sf::Vector2f>(mousePos))) {
                    try {
                        int x = stoi(inputX);
                        int y = stoi(inputY);
                        if (x >= 0 && x <= RANGE && y >= 0 && y <= RANGE) {
                            points.emplace_back(x, y);
                            inputX.clear();
                            inputY.clear();
                            inputActiveX = true;
                            inputActiveY = false;
                        }
                    }
                    catch (const exception& e) {
                        cerr << "Ошибка ввода: " << e.what() << endl;
                    }
                }
                else if (buttonBuild.contains(static_cast<sf::Vector2f>(mousePos))) {
                    trapezoids.clear();
                    showTrapezoids = true;

                    if (points.size() >= 4) {
                        for (size_t i = 0; i < points.size(); i++) {
                            for (size_t j = i + 1; j < points.size(); j++) {
                                for (size_t k = j + 1; k < points.size(); k++) {
                                    for (size_t l = k + 1; l < points.size(); l++) {
                                        vector<Point> quad = { points[i], points[j], points[k], points[l] };
                                        vector<Point> sortedQuad = sortPoints(quad);
                                        if (isIsoscelesTrapezoid(sortedQuad)) {
                                            trapezoids.push_back(move(sortedQuad));
                                        }
                                    }
                                }
                            }
                        }
                        wcout << L"Найдено " << trapezoids.size() << L" трапеций." << endl;
                    }
                }
            }
            else if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode < 128) {
                    char ch = static_cast<char>(event.text.unicode);
                    if (ch >= '0' && ch <= '9') {
                        if (inputActiveX && inputX.size() < 3) {
                            inputX += ch;
                        }
                        else if (inputActiveY && inputY.size() < 3) {
                            inputY += ch;
                        }
                    }
                    else if (ch == '\b') {
                        if (inputActiveX && !inputX.empty()) {
                            inputX.pop_back();
                        }
                        else if (inputActiveY && !inputY.empty()) {
                            inputY.pop_back();
                        }
                    }
                }
            }
        }

        window.clear(sf::Color::Black);

        // Отрисовка контрольной панели
        drawButton(window, L"Генерировать рандомно", buttonRandom, currentMode == Mode::Random, font);
        drawButton(window, L"Загрузить из файла", buttonFile, currentMode == Mode::File, font);
        drawButton(window, L"Ввести точки вручную", buttonManual, currentMode == Mode::Manual, font);

        if (currentMode == Mode::Manual) {
            drawInputField(window, L"X:", inputX, inputFieldX, font, inputActiveX);
            drawInputField(window, L"Y:", inputY, inputFieldY, font, inputActiveY);
            drawButton(window, L"Добавить точку", buttonAddPoint, false, font);
        }

        drawButton(window, L"Построить трапеции", buttonBuild, false, font);

        // Отрисовка разделительной линии
        sf::RectangleShape separator(sf::Vector2f(2, WINDOW_HEIGHT));
        separator.setPosition(CONTROL_WIDTH, 0);
        separator.setFillColor(sf::Color::White);
        window.draw(separator);

        // Отрисовка координатной линейки
        // Ось X
        sf::VertexArray axisX(sf::Lines, 2);
        axisX[0].position = sf::Vector2f(CONTROL_WIDTH, WINDOW_HEIGHT);
        axisX[1].position = sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT);
        axisX[0].color = sf::Color::White;
        axisX[1].color = sf::Color::White;
        window.draw(axisX);

        // Метки на оси X
        for (int i = 0; i <= RANGE; i += 10) {
            float x = OFFSET_X + i * SCALE;
            wstring label = to_wstring(i);
            drawText(window, label, x - 5, WINDOW_HEIGHT - 20, font, 12);
        }

        // Ось Y
        sf::VertexArray axisY(sf::Lines, 2);
        axisY[0].position = sf::Vector2f(CONTROL_WIDTH, 0);
        axisY[1].position = sf::Vector2f(CONTROL_WIDTH, WINDOW_HEIGHT);
        axisY[0].color = sf::Color::White;
        axisY[1].color = sf::Color::White;
        window.draw(axisY);

        // Метки на оси Y
        for (int i = 0; i <= RANGE; i += 10) {
            float y = WINDOW_HEIGHT - i * SCALE;
            wstring label = to_wstring(i);
            drawText(window, label, CONTROL_WIDTH + 5, y - 10, font, 12);
        }

        // Отрисовка точек
        for (const auto& p : points) {
            sf::CircleShape circle(POINT_RADIUS);
            circle.setOrigin(POINT_RADIUS, POINT_RADIUS);
            circle.setPosition(toSFML(p));
            circle.setFillColor(sf::Color::White);
            window.draw(circle);
        }

        // Отрисовка трапеций
        if (showTrapezoids) {
            for (const auto& trap : trapezoids) {
                sf::ConvexShape convex;
                convex.setPointCount(4);
                for (int i = 0; i < 4; i++) {
                    convex.setPoint(i, toSFML(trap[i]));
                }
                convex.setOutlineColor(sf::Color::Red);
                convex.setOutlineThickness(2);
                convex.setFillColor(sf::Color(255, 0, 0, 50));
                window.draw(convex);
            }
        }

        // Отображение количества трапеций
        wstring trapezoidCountText = L"Трапеций: " + to_wstring(trapezoids.size());
        drawText(window, trapezoidCountText, CONTROL_WIDTH + 10, 10, font);

        window.display();
    }

    return 0;
}
