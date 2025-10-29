#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "map.h" 
#include "view.h" 

/*Конструктор с параметрами(проинициализированными).*/
//-------------------------------------------------------------------------------------------------------------------
class Player // Класс Игрока.
{
public:
    Player(sf::String F, int X, int Y, float W, float H)
        : sprite(texture), speed(0.0), x(X), y(Y), dir(0), File(F), w(W), h(H)
    {
        //Имя файл с расширением. И ложим в image наше изображение. При создании оббъекта, будет задавать имя файла.
        image.loadFromFile({ "images/" + F });

        //Делаем изображение прозрачным.
        image.createMaskFromColor(sf::Color(41,33,59));

        //Заливаем спрайт текстурами.
        texture.loadFromImage(image);

        //Задаём спрайту один прямоугольник, для вывода одного льва, а не кучу львов сразу. IntRect привидение типов.
        sprite.setTextureRect(sf::IntRect({static_cast<int>(w), static_cast<int>(h)}, {static_cast<int>(w), static_cast<int>(h)}));
    }

    /*Функция оживления объекта класса. Принимает время, и от этого осущиствляет движение объекта.*/
    void update(float time)
    {
        switch (dir)//Реализует повидение в зависимости от направления.
        {
        case 0://По иксу задаём положительную скорость, по игрику зануляем. Получаем, что персонажь идёт только в право.
            dx = speed;
            dy = 0;
            break;

        case 1://По иксу задаём отрицательную скорость, по игрику зануляем. Получаем, что персонажь идёт только в влево.
            dx = -speed;
            dy = 0;
            break;

        case 2://По иксу задаём нулевое значение, по игрику положительное. Получаем, что персонажь идёт только в вниз.
            dx = 0;
            dy = speed;
            break;

        case 3://По иксу задаём нулевое значение, по игрику отрицательное. Получаем, что персонажь идёт только в верх.
            dx = 0;
            dy = -speed;
            break;

        default:
            break;
        }

        //Наше ускорение на время, получает смещение кординат, и как следствие движение.
        x += dx * time;
        y += dy * time;

        speed = 0; //Зануляем скорость, чтобы персонаж остановил после того как перестали нажимть клавиши.
        sprite.setPosition({ x, y });//Выводим изображение по середине. Безсконечно выводим в этой функции, иначе персонаж стоял бы на месте.
    }

    float getPlayerCoordinateX()
    {
        return x;
    }

    float getPlayerCoordinateY()
    {
        return y;
    } 

    float w, h, dx, dy, speed;//Кординаты игрока х и у, высота и ширина w и h, ускорение speed(сама скорость)
    int dir; //Направление (direction) движение игрока
    sf::String File; //Файл расширения
    sf::Image image;//sfml изображение
    sf::Texture texture;//Файл текстур
    sf::Sprite sprite;//sfml спрайт

private:
    float x, y = 0;
};
//-------------------------------------------------------------------------------------------------------------------
int main()
{
    // Размер игрового окна
    sf::RenderWindow window(sf::VideoMode({640, 480}), "SFML window");

    //sf::View view(sf::FloatRect({ 250, 250 }, { 640, 480 }));
    view.setSize({ 640, 480 }); // Устанавливаем размеры
    view.setCenter({250, 250}); // Устанавливаем центр (по середине)

    //Создаём объект класса Player, задаём ему картинку, далее кординаты, плюс ширину и высоту.
    Player p("hero.png", 250, 250, 96, 96);

    sf::Image map_image;
    map_image.loadFromFile("images/map.png");
    sf::Texture map;
    map.loadFromImage(map_image);
    sf::Sprite s_map(map);
    s_map.setTexture(map);

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

        //Управлние персонажем с анимацие.
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        {

            p.dir = 1;
            p.speed = 0.1;

            CurrentFrame += 0.005 * time;

            if (CurrentFrame > 3)
                CurrentFrame -= 3;

            //Через оъект класса, меняем изображение в зависимости от направления.
            p.sprite.setTextureRect(sf::IntRect({ 96 * int(CurrentFrame), 96 }, { 96, 96 }));

            getPlayerCordinateForview(p.getPlayerCoordinateX(), p.getPlayerCoordinateY());
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        {
            p.dir = 0;
            p.speed = 0.1;

            CurrentFrame += 0.005 * time;

            if (CurrentFrame > 3)
                CurrentFrame -= 3;

            p.sprite.setTextureRect(sf::IntRect({ 96 * int(CurrentFrame) , 192  }, { 96 , 96 }));

            getPlayerCordinateForview(p.getPlayerCoordinateX(), p.getPlayerCoordinateY());
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
        {
            p.dir = 3;
            p.speed = 0.1;

            CurrentFrame += 0.005 * time;

            if (CurrentFrame > 3)
                CurrentFrame -= 3;
            
            p.sprite.setTextureRect(sf::IntRect({ 96 * int(CurrentFrame), 288 }, { 96, 96 }));

            getPlayerCordinateForview(p.getPlayerCoordinateX(), p.getPlayerCoordinateY());
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
        {
            p.dir = 2;
            p.speed = 0.1;

            CurrentFrame += 0.005 * time;

            if (CurrentFrame > 3)
                CurrentFrame -= 3;

            p.sprite.setTextureRect(sf::IntRect({ 96 * int(CurrentFrame), 0 }, { 96, 96 }));

            getPlayerCordinateForview(p.getPlayerCoordinateX(), p.getPlayerCoordinateY());
        }

        p.update(time); // Сброс времени. Без этого, не будет движения.
        viewmap(time); // Сколирование карты (прокрутка)
        changeview();
        window.setView(view); // Оживляем камеру

        // Очистка окна.
        window.clear();


        for (int i = 0; i < HEIGHT_MAP; i++)
        {
            for (int j = 0; j < WIDTH_MAP; j++)
            {
                if (TileMap[i][j] == ' ')
                    s_map.setTextureRect(sf::IntRect({ 0, 0 }, { 32, 32 }));
                else if (TileMap[i][j] == 's')
                    s_map.setTextureRect(sf::IntRect({ 32, 0 }, { 32, 32 }));
                else if (TileMap[i][j] == '0')
                    s_map.setTextureRect(sf::IntRect({ 64, 0 }, { 32, 32 }));

                s_map.setPosition({ static_cast<float>(j * 32), static_cast<float>(i * 32) });
                window.draw(s_map);
            }
        }

        //Рисуем фигуры с заданными параметрами.
        window.draw(p.sprite);
        // Обновить окно.
        window.display();
    }
}
//-------------------------------------------------------------------------------------------------------------------