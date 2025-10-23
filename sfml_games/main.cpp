#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>


//-------------------------------------------------------------------------------------------------------------------
class Player
{
public:
    Player(sf::String F, int X, int Y, float W, float H)
        : sprite(texture), speed(0.0), x(X), y(Y), dir(0), File(F), w(W), h(H)
    {
        image.loadFromFile({ "images/" + F });
        image.createMaskFromColor(sf::Color(41,33,59));
        texture.loadFromImage(image);
        sprite.setTextureRect(sf::IntRect({static_cast<int>(w), static_cast<int>(h)}, {static_cast<int>(w), static_cast<int>(h)}));
    }

    void update(float time)
    {
        switch (dir)
        {
        case 0:
            dx = speed;
            dy = 0;
            break;

        case 1:
            dx = -speed;
            dy = 0;
            break;

        case 2:
            dx = 0;
            dy = speed;
            break;

        case 3:
            dx = 0;
            dy = -speed;
            break;

        default:
            break;
        }

        x += dx * time;
        y += dy * time;

        speed = 0;
        sprite.setPosition({ x, y });
    }

    float dx, dy, x, y, w, h, speed;
    int dir; 
    sf::String File;
    sf::Image image;
    sf::Texture texture;
    sf::Sprite sprite;
};
//-------------------------------------------------------------------------------------------------------------------
int main()
{
    // Размер игрового окна
    sf::RenderWindow window(sf::VideoMode({640, 480}), "SFML window");

    Player p("hero.png", 250, 250, 96, 96);


    //Завели переменные для времени. Чтобы можно было от чего отталкиватся.
    float CurrentFrame = 0;
    sf::Clock clock;

    // Начать игровой цикл
    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asMicroseconds(); //Задаём тайменг в милисекундах.
        clock.restart(); //Делаем рестарт для сброса таймера.
        time /= 800; //Скорость игры

        // События процесса
        while (const std::optional event = window.pollEvent())
        {
            // Закрыть окно: выход
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        {
            p.dir = 1;
            p.speed = 0.1;

            CurrentFrame += 0.005 * time;

            if (CurrentFrame > 3)
                CurrentFrame -= 3;

            p.sprite.setTextureRect(sf::IntRect({ 96 * int(CurrentFrame), 96 }, { 96, 96 }));

        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        {
            p.dir = 0;
            p.speed = 0.1;

            CurrentFrame += 0.005 * time;

            if (CurrentFrame > 3)
                CurrentFrame -= 3;

            p.sprite.setTextureRect(sf::IntRect({ 96 * int(CurrentFrame) , 192  }, { 96 , 96 }));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
        {
            p.dir = 3;
            p.speed = 0.1;

            CurrentFrame += 0.005 * time;

            if (CurrentFrame > 3)
                CurrentFrame -= 3;

            p.sprite.setTextureRect(sf::IntRect({ 96 * int(CurrentFrame), 288 }, { 96, 96 }));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        {
            p.dir = 2;
            p.speed = 0.1;

            CurrentFrame += 0.005 * time;

            if (CurrentFrame > 3)
                CurrentFrame -= 3;

            p.sprite.setTextureRect(sf::IntRect({ 96 * int(CurrentFrame), 0 }, { 96, 96 }));
        }

        p.update(time);

        // Очистка окна.
        window.clear();
        //Рисуем фигуры с заданными параметрами.
        window.draw(p.sprite);
        // Обновить окно.
        window.display();
    }
}
//-------------------------------------------------------------------------------------------------------------------