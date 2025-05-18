#include <SFML/Graphics.hpp>
#include <vector>

int main()
{
    // â ����
    sf::RenderWindow window(sf::VideoMode(800, 600), "color change");

    // �簢�� ����
    sf::RectangleShape rectangle(sf::Vector2f(200, 150));
    rectangle.setFillColor(sf::Color(128, 128, 128)); // �ʱ� ����: ȸ��
    rectangle.setPosition(300, 225); // �߾� ����

    // ���� ����Ʈ
    std::vector<sf::Color> colors = { sf::Color::Red, sf::Color::Green, sf::Color::Blue };
    int colorIndex = -1; // ���� ���� ����

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            // â �ݱ� �Ǵ� ESC Ű�� ����
            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
            {
                window.close();
            }

            // ���콺 ���� Ŭ�� �� ���� ����
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                colorIndex = (colorIndex + 1) % colors.size();
                rectangle.setFillColor(colors[colorIndex]);
            }
        }

        // ȭ�� �׸���
        window.clear();
        window.draw(rectangle);
        window.display();
    }

    return 0;
}
