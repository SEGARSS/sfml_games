#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>


//-------------------------------------------------------------------------------------------------------------------
class Player
{
public:
    Player(sf::String F, int X, int Y, float W, float H)
        : File(F), w(W), h(H), dir(0), x(X), y(Y), texture(image)
    {
        File = F;
        w = W, h = H;
        image.loadFromFile({ "images/" + File });
        image.createMaskFromColor(sf::Color({ 41, 33, 59 }));
        texture.loadFromImage(image);
        x = X, y = Y;        
    }

    float x, y, w, h, speed = 0;
    int dir; 
    sf::String File;
    sf::Image image;
    sf::Texture texture;
};
//-------------------------------------------------------------------------------------------------------------------
int main()
{
    // Размер игрового окна
    sf::RenderWindow window(sf::VideoMode({640, 480}), "SFML window");

    sf::Image heroimage;
    heroimage.loadFromFile("images/hero.png");//Загружаем файл картинки.

    sf::Texture herotexture(heroimage);
    sf::Sprite spritehero(herotexture);

    /*сделав такую запись - {0, 196}, {96, 96} - где кордината Y - 0,196 , а кордината Х - 96,96*/
    spritehero.setTextureRect(sf::IntRect({0, 196}, {96, 96})); // Выводим героя, в заданных кординеатах.
    spritehero.setPosition({ 50,25 }); //Начальные кординаты персонажа


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
            CurrentFrame += 0.005 * time;

            if (CurrentFrame > 3)
                CurrentFrame -= 3;

            /*96 * int(CurrentFrame) - Скакой переодичностью меняется картинка.*/
            spritehero.setTextureRect(sf::IntRect({ 96 * int(CurrentFrame), 96 }, { 96, 96 }));
            spritehero.move({ -0.1f * time, 0.0f });

        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        {
            CurrentFrame += 0.005 * time;

            if (CurrentFrame > 3)
                CurrentFrame -= 3;

            spritehero.setTextureRect(sf::IntRect({ 96 * int(CurrentFrame) , 192  }, { 96 , 96 }));
            spritehero.move({ 0.1f * time, 0.0f });
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
        {
            CurrentFrame += 0.005 * time;

            if (CurrentFrame > 3)
                CurrentFrame -= 3;

            spritehero.setTextureRect(sf::IntRect({ 96 * int(CurrentFrame), 288 }, { 96, 96 }));
            spritehero.move({ 0.0f, -0.1f * time });
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        {
            CurrentFrame += 0.005 * time;

            if (CurrentFrame > 3)
                CurrentFrame -= 3;

            spritehero.setTextureRect(sf::IntRect({ 96 * int(CurrentFrame), 0 }, { 96, 96 }));
            spritehero.move({ 0.0f, 0.1f * time });
        }

        // Очистка окна.
        window.clear();
        //Рисуем фигуры с заданными параметрами.
        window.draw(spritehero);
        // Обновить окно.
        window.display();
    }
}
//-------------------------------------------------------------------------------------------------------------------