//#include <SFML/Graphics.hpp>
//#include <iostream>
//
//std::vector<sf::Vector2f> getStarVertices(float radius, sf::Vector2f center, float angle)
//{
//    std::vector<sf::Vector2f> result;
//    result.reserve(7);
//
//    for (int i = 0; i < 7; ++i)
//    {
//        float alpha = 2.f * 3.1415926535f / 7.f * static_cast<float>(i);
//        float x = radius * std::cos(alpha + angle);
//        float y = radius * std::sin(alpha + angle);
//        result.push_back(center + sf::Vector2f(x, y));
//    }
//
//    return result;
//}
//
//int main()
//{
//    bool starchrono = false;
//    sf::Clock clock;
//    sf::Font font;
//    if (!font.loadFromFile("C:\\Windows\\Fonts\\Arial.ttf"))
//    {
//        std::cout << "no font load";
//    }
//    sf::Text txt;
//    sf::Text chronotxt;
//    chronotxt.setFillColor(sf::Color::Red);
//    txt.setFillColor(sf::Color::Red);
//    chronotxt.setFont(font);
//    txt.setFont(font);
//    txt.setString("hello world");
//    txt.setCharacterSize(40);
//    sf::RenderWindow window(sf::VideoMode(600, 600), "SFML works!");
//    window.setFramerateLimit(60);
//    sf::CircleShape shape(300.f, 3);
//    shape.setFillColor(sf::Color::Green);
//
//    sf::RectangleShape rectangle(sf::Vector2f(200.f, 200.f));
//    rectangle.setPosition(200.f, 200.f);
//    rectangle.setFillColor(sf::Color::Blue);
//
//    float angle = 0.f;
//
//    sf::Texture texture;
//    texture.loadFromFile("C:\\image\\Truc.bmp");
//
//    sf::Sprite sprite;
//    sprite.setTexture(texture);
//
//    while (window.isOpen())
//    {
//        sf::Event event;
//        
//        while (window.pollEvent(event))
//        {
//            if (event.type == sf::Event::Closed)
//                window.close();
//            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
//            {
//               /* starchrono = !starchrono;*/
//                  if (!starchrono)
//                      starchrono = true;
//                  else
//                      starchrono = false;
//            }
//        }
//        
//       
//
//        window.clear();  
//        //window.draw(shape);
//        //window.draw(rectangle);
//
//        auto P = getStarVertices(200.f, sf::Vector2f(300.f, 300.f), angle );
//        angle = angle + 0.1;
//
//        for (int i = 0; i < 7; ++i)
//        {
//            sf::RectangleShape rectangle(sf::Vector2f(3.f, 3.f));
//            rectangle.setPosition(P[i]);
//            rectangle.setFillColor(sf::Color::Red);
//            window.draw(rectangle);
//        }
//
//        std::vector<sf::Vertex> lines;
//        lines.reserve(14);
//
//        int startIdx = 0;
//        for (int i = 0; i < 7; ++i)
//        {
//            int endIdx = (startIdx + 3) % 7;
//            lines.push_back(P[startIdx]);
//            lines.push_back(P[endIdx]);
//            startIdx = endIdx;
//        }
//
//        window.draw(&lines[0], 14, sf::Lines);
//       
//        sprite.setRotation(angle * 180 / 3.141592654f);
//        sprite.setPosition(300.f, 300.f);
//        sprite.setOrigin(sf::Vector2f(64.f, 64.f));
//        window.draw(sprite);
//        if (starchrono)
//        {
//            sf::Time elapsed = clock.getElapsedTime();
//
//            chronotxt.setString("Time: " + std::to_string(static_cast<int>(elapsed.asSeconds())));
//            window.draw(chronotxt);
//        }
//       
//            
//        
//
//        
//         window.display();
//        
//      
//    }
//
//    return 0;
//}


#include <iostream>
#include <SFML/Graphics.hpp>

std::vector<sf::Vector2f> getStarVertices(float radius, sf::Vector2f center, float angle)
{
    std::vector<sf::Vector2f> result;
    result.reserve(7);

    for (int i = 0; i < 7; ++i)
    {
        float alpha = 2.f * 3.1415926535f / 7.f * static_cast<float>(i);
        float x = radius * std::cos(alpha + angle);
        float y = radius * std::sin(alpha + angle);
        result.push_back(center + sf::Vector2f(x, y));
    }

    return result;
}

int main()
{
    bool inWindow = false;

    sf::RenderWindow window(sf::VideoMode(600, 600), "SFML works!");
    window.setFramerateLimit(60);
    sf::CircleShape shape(300.f, 3);
    shape.setFillColor(sf::Color::Green);

    sf::RectangleShape rectangle(sf::Vector2f(200.f, 100.f));
    rectangle.setOrigin(100, 50);
    rectangle.setPosition(300.f, 300.f);
    rectangle.setFillColor(sf::Color::Green);

    float angle = 0.f;

    sf::Texture texture;
    texture.loadFromFile("C:/Src/BeginningSFML/Truc.bmp");

    sf::Sprite sprite;
    sprite.setTexture(texture);

    sf::Font font;
    if (!font.loadFromFile("C:/Windows/Fonts/Arial.ttf"))
        std::cerr << "Failed to load font" << std::endl;

    sf::Text text;
    text.setFont(font);

    text.setString("Hello world");
    
    text.setCharacterSize(24); // in pixels, not points!
    text.setFillColor(sf::Color::White);

    const sf::Clock clock;
    const sf::Clock spawnClock;
    const sf::Time refreshTime = sf::seconds(1.f / 60.f);
    auto startSpawn = spawnClock.getElapsedTime().asMilliseconds();
    auto previous = clock.getElapsedTime().asMilliseconds();
    auto lag = 0.0;

    int counter = 0;
    bool isStopped = false;
    auto test = sf::Color::Black;
    sf::Text text1;
    sf::Text text2;

    text1.setFont(font);
    text1.setCharacterSize(24); // in pixels, not points!
    text1.setFillColor(sf::Color::White);
    text1.setPosition(sf::Vector2f(250, 0));

    text2.setFont(font);
    text2.setCharacterSize(24); // in pixels, not points!
    text2.setFillColor(sf::Color::White);
    text2.setPosition(sf::Vector2f(350, 0));
   
    while (window.isOpen())
    {
        if (const auto lastSpawnTick = spawnClock.getElapsedTime().asMilliseconds(); lastSpawnTick - startSpawn >= 1000)
        {
            if (!isStopped)
                text.setString(std::to_string(++counter));

            startSpawn = lastSpawnTick;
        }

        const auto current = clock.getElapsedTime().asMilliseconds();
        const auto elapsed = current - previous;
        previous = current;
        lag += elapsed;
        window.clear(test);

        // input
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed)
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                    isStopped = !isStopped;
            }
            if (event.type == sf::Event::MouseEntered)
            {
                test = sf::Color::Blue;
                inWindow = true;
                
            }
            if (event.type == sf::Event::MouseLeft)
            {
                test = sf::Color::Black;
                inWindow = false;
            }
          
        }

        std::vector<sf::Vertex> lines;
        auto P = getStarVertices(200.f, sf::Vector2f(300.f, 300.f), angle);
        angle = angle + 0.01f;

        for (int i = 0; i < 7; ++i)
        {
            sf::RectangleShape rectangle(sf::Vector2f(3.f, 3.f));
            rectangle.setPosition(P[i]);
            rectangle.setFillColor(sf::Color::Red);
           /* window.draw(rectangle);*/
        }

        lines.reserve(14);

        int startIdx = 0;
        for (int i = 0; i < 7; ++i)
        {
            int endIdx = (startIdx + 3) % 7;
            lines.push_back(P[startIdx]);
            lines.push_back(P[endIdx]);
            startIdx = endIdx;
        }

        sprite.setOrigin(64, 64);
        sprite.setPosition(300.f, 300.f);

        while (refreshTime.asMilliseconds() > 0.0
            && lag >= refreshTime.asMilliseconds())
        {
            // update
            sprite.setRotation(-2.f * (angle * 180 / 3.14));
            lag -= refreshTime.asMilliseconds();
       
                text1.setString("x :" + std::to_string(sf::Mouse::getPosition(window).x));
                text2.setString("y :" + std::to_string(sf::Mouse::getPosition(window).y));

                auto mousePos = sf::Mouse::getPosition(window);
                auto rectangleBounds = rectangle.getGlobalBounds();

                if (rectangleBounds.contains(mousePos.x, mousePos.y))
                {
                    rectangle.setFillColor(sf::Color::Red);
                }
                else
                {
                    rectangle.setFillColor(sf::Color::Green);
                }

                
        }

        // render
    /*    window.draw(&lines[0], 14, sf::Lines);
        window.draw(sprite);*/
        window.draw(rectangle);
        window.draw(text);

      
        if (inWindow)
        {
            window.draw(text1);
            window.draw(text2);
        }

        window.display();
    }

    return 0;
}
