#include <iostream>
#include "map.h" 
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

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

    float x, y, w, h, dx, dy, speed;//Кординаты игрока х и у, высота и ширина w и h, ускорение speed(сама скорость)
    int dir; //Направление (direction) движение игрока
    sf::String File; //Файл расширения
    sf::Image image;//sfml изображение
    sf::Texture texture;//Файл текстур
    sf::Sprite sprite;//sfml спрайт
};
//-------------------------------------------------------------------------------------------------------------------
int main()
{
    // Размер игрового окна
    sf::RenderWindow window(sf::VideoMode({640, 480}), "SFML window");

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
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        {

            p.dir = 1;
            p.speed = 0.1;

            CurrentFrame += 0.005 * time;

            if (CurrentFrame > 3)
                CurrentFrame -= 3;

            //Через оъект класса, меняем изображение в зависимости от направления.
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

        p.update(time); // Сброс времени. Без этого, не будет движения.

        // Очистка окна.
        window.clear();


        //Ошибка - Надо прорабоать.
        for (int i = 0; i < HEIGHT_MAP; i++)
        {
            for (int j = 0; j < WIDTH_MAP; j++)
            {
                if (TileMap[i][j] == ' ')
                    s_map.setTextureRect(sf::IntRect({ static_cast<int>(0), static_cast<int>(0) }, { static_cast<int>(32), static_cast<int>(32) }));
                if (TileMap[i][j] == 's')
                    s_map.setTextureRect(sf::IntRect({ static_cast<int>(32), static_cast<int>(0) }, { static_cast<int>(32), static_cast<int>(32) }));
                if (TileMap[i][j] == '0')
                    s_map.setTextureRect(sf::IntRect({ static_cast<int>(64), static_cast<int>(0) }, { static_cast<int>(32), static_cast<int>(32) }));

                s_map.setPosition({ j * 32 ,  i * 32 });
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