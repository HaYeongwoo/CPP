#include <SFML/Graphics.hpp>
#include <SFML/System.hpp> //시간 관련 기능
#include <SFML/Window.hpp> // 마우스, 키보드 입력 이벤트 처리
#include <cstdlib> //랜덤 위치 생성
#include <ctime>   //랜덤 시드 초기화
#include <string>  //텍스트, 숫자 출력

int main()
{
    srand(static_cast<unsigned>(time(0)));

    sf::RenderWindow window(sf::VideoMode(800, 600), "Circle catch");

    sf::CircleShape circle(30);
    circle.setFillColor(sf::Color::Green);
    circle.setPosition(rand() % 740 + 30, rand() % 540 + 30); //위치 랜덤

    sf::Font font;
    if (!font.loadFromFile("C://Windows//Fonts//arial.ttf")) // 폰트 경로
        return -1;

    int score = 0;
    int mistakes = 0;
    const int maxMistakes = 3;
    const int gameTimeLimit = 30; // 30초 제한
    sf::Clock gameClock;

    sf::Text scoreText("Score: 0", font, 24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10, 10);

    sf::Text timeText("Time: 30", font, 24);
    timeText.setFillColor(sf::Color::White);
    timeText.setPosition(10, 40);

    sf::Text statusText("", font, 40);
    statusText.setFillColor(sf::Color::Red);
    statusText.setPosition(200, 250);

    bool isGameOver = false;
    // 게임 루프
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
            {
                window.close();
            }
             // 마우스 왼쪽 클릭, 원 안을 클릭했는지 확인
            if (!isGameOver && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
                if (circle.getGlobalBounds().contains(mousePos))
                {
                    score++;
                    scoreText.setString("Score: " + std::to_string(score));
                    circle.setPosition(rand() % 740 + 30, rand() % 540 + 30);
                }
                else
                {
                    mistakes++;
                    if (mistakes >= maxMistakes)
                    {
                        isGameOver = true;
                        statusText.setString("Game Over!");
                    }
                }
            }
        }

        // 시간 체크
        int remainingTime = gameTimeLimit - static_cast<int>(gameClock.getElapsedTime().asSeconds());
        if (remainingTime <= 0 && !isGameOver)
        {
            isGameOver = true;
            statusText.setString("Time's Up!");
        }
        timeText.setString("Time: " + std::to_string(std::max(0, remainingTime)));

        window.clear();
        if (!isGameOver)
        {
            window.draw(circle);
        }
        window.draw(scoreText);
        window.draw(timeText);
        if (isGameOver)
        {
            window.draw(statusText);
        }
        window.display();
    }

    return 0;
}
