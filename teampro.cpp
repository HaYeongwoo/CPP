#include <SFML/Graphics.hpp>
#include <vector>

int main()
{
    // 창 생성
    sf::RenderWindow window(sf::VideoMode(800, 600), "color change");

    // 사각형 생성
    sf::RectangleShape rectangle(sf::Vector2f(200, 150));
    rectangle.setFillColor(sf::Color(128, 128, 128)); // 초기 색상: 회색
    rectangle.setPosition(300, 225); // 중앙 정렬

    // 색상 리스트
    std::vector<sf::Color> colors = { sf::Color::Red, sf::Color::Green, sf::Color::Blue };
    int colorIndex = -1; // 시작 색상 없음

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            // 창 닫기 또는 ESC 키로 종료
            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
            {
                window.close();
            }

            // 마우스 왼쪽 클릭 시 색상 변경
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                colorIndex = (colorIndex + 1) % colors.size();
                rectangle.setFillColor(colors[colorIndex]);
            }
        }

        // 화면 그리기
        window.clear();
        window.draw(rectangle);
        window.display();
    }

    return 0;
}
