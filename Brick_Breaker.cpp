#include <iostream>
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <string>
using namespace std;

int main()
{
    //Window
    const int Window_Width = 800, Window_Height = 600;
    sf::RenderWindow Window(sf::VideoMode(Window_Width, Window_Height), "Brick Breaker");
    Window.setFramerateLimit(60);
    cout << "Game started" << endl;

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //background 

    sf::Texture background;
    background.loadFromFile("Data/background.png");
    sf::Sprite spritebg;
    spritebg.setTexture(background);

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   //Slider (Platform)
    const int Slider_Width = 150, Slider_Thick = 30;
    sf::RectangleShape Slider(sf::Vector2f(Slider_Width, Slider_Thick));
    Slider.setPosition((Window_Width - Slider_Width) / 2.0, Window_Height - Slider_Thick - 25);
    //Slider Director
    bool Right_Key = false, Left_Key = false;

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //Borders
    const int Border_Thick = 25;
    //Top Border
    sf::RectangleShape Border_Top(sf::Vector2f(Window_Width, Border_Thick));
    //Left Border
    sf::RectangleShape Border_Left(sf::Vector2f(Border_Thick, Window_Height));
    //Right Border
    sf::RectangleShape Border_Right(sf::Vector2f(Border_Thick, Window_Height));
    Border_Right.setOrigin(Border_Thick, 0);
    Border_Right.setPosition(Window_Width, 0);

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //Ball
    const int Ball_Rad = 10;
    sf::CircleShape Ball(Ball_Rad);
    Ball.setOrigin(Ball_Rad, Ball_Rad);
    Ball.setPosition(Window_Width / 2.0, Window_Height / 2.0);
    //Ball Speed
    float X_BallSpeed = 0, Y_BallSpeed = 5.0;

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //Bricks
    const int Brick_Width = 100, Brick_Thick = 25;
    sf::RectangleShape Brick[10];
    bool exist[10] = {};
    for (int i = 0; i < 5; i++)
    {
        Brick[i].setSize(sf::Vector2f(Brick_Width, Brick_Thick));
        Brick[i].setPosition(Border_Thick + 25 + 150 * i, Border_Thick + 25);
        exist[i] = 1;
    }
    for (int i = 5; i < 10; i++)
    {
        Brick[i].setSize(sf::Vector2f(Brick_Width, Brick_Thick));
        Brick[i].setPosition(Border_Thick + 25 + 150 * (i - 5), Border_Thick + 25 + 50);
        exist[i] = 1;
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //Font 
    sf::Font font;
    font.loadFromFile("Data/font.TTF");
       
    sf::Text welcome_text, enter_text , Score_Text, Score_Num, WL_Text;

    //Welcome
    welcome_text.setFont(font);
    welcome_text.setCharacterSize(35);
    welcome_text.setFillColor(sf::Color(255, 255, 255));
    welcome_text.setPosition(Window_Width - 750, Window_Height - 330);
    welcome_text.setString("welcome to brick breaker");

    enter_text.setFont(font);
    enter_text.setCharacterSize(15);
    enter_text.setFillColor(sf::Color(255, 255, 255));
    enter_text.setPosition(Window_Width - 560, Window_Height - 250);
    enter_text.setString(" press 'D' for Day Mode\n or 'N' for Night Mode");
    
    //Score Text
    int Hits_Counter = 0;

    Score_Text.setFont(font);
    Score_Text.setString("score");
    Score_Text.setPosition(Window_Width - 200, Window_Height - 100);
    Score_Text.setCharacterSize(20);
    Score_Text.setFillColor(sf::Color(0, 0, 153));
    Score_Text.setOutlineThickness(2);
    Score_Text.setOutlineColor(sf::Color(255, 255, 0));

    //Score Num
    string Score_String;

    int Score_Counter = 0;

    Score_Num.setFont(font);
    Score_Num.setPosition(Window_Width - 100, Window_Height - 100);
    Score_Num.setCharacterSize(20);
    Score_Num.setFillColor(sf::Color(0, 0, 153));
    Score_Num.setOutlineThickness(2);
    Score_Num.setOutlineColor(sf::Color(255, 255, 0));

    //Win\Lose Text
    WL_Text.setFont(font);
    WL_Text.setCharacterSize(40);
    WL_Text.setPosition(Window_Width - 550, Window_Height - 330);
    WL_Text.setOutlineColor(sf::Color(255, 255, 255));
    WL_Text.setOutlineThickness(2.0f);
    bool Loser = 0;

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //Sounds
    sf::SoundBuffer(ball_buffer);
    sf::Music music;
    sf::Sound pop;
    sf::Music lose;

    pop.setBuffer(ball_buffer);

    music.openFromFile("Data/Tetris.wav");
   
    music.play();
    music.setVolume(20);
    music.setLoop(true);

    ball_buffer.loadFromFile("Data/pop.wav");

    lose.openFromFile("Data/Loss.wav") ;

    bool start = false;
    bool DAY = false, NIGHT = false;

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    while (Window.isOpen())
    {

        // events on the main game loop
        sf::Event event;
        while (Window.pollEvent(event))
        {
            //process events
            if (event.type == sf::Event::Closed)
            {
                Window.close();
            }

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::N)
                {
                    start = true;
                    NIGHT = true;
                    DAY = false;
                }
            }

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::D)
                {
                    start = true;
                    DAY = true;
                    NIGHT = false;
                }
            }

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Right)
                    Right_Key = true;
            }
            else
            {
                Right_Key = false;
            }

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Left)
                    Left_Key = true;
            }
            else
            {
                Left_Key = false;
            }
        }

        if (!start)
        {
            Window.clear(sf::Color(51, 153, 102));
            Window.draw(welcome_text);
            Window.draw(enter_text);
            Window.display();
        }
        else
        {
            if (DAY == true) {
                NIGHT == false;

                //textures
                sf::Texture ball;
                ball.loadFromFile("Data/ballNM.png");
                Ball.setTexture(&ball);

                sf::Texture Rborder_tex;
                Rborder_tex.loadFromFile("Data/RB.png");
                Border_Right.setTexture(&Rborder_tex);

                sf::Texture Lborder_tex;
                Lborder_tex.loadFromFile("Data/LB.png");
                Border_Left.setTexture(&Lborder_tex);

                sf::Texture topborder;
                topborder.loadFromFile("Data/TB.png");
                Border_Top.setTexture(&topborder);

                sf::Texture bricks;
                bricks.loadFromFile("Data/brick1.png");
                for (int i = 0; i < 10; i++)
                {
                    Brick[i].setTexture(&bricks);
                }

                sf::Texture sliderTex;
                sliderTex.loadFromFile("Data/slider.png");
                Slider.setTexture(&sliderTex);

                Window.clear();

                Window.draw(spritebg);
                Window.draw(Ball);
                Window.draw(Slider);
                Window.draw(Border_Top);
                Window.draw(Border_Left);
                Window.draw(Border_Right);
                for (int i = 0; i < 10; i++)
                {
                    if (exist[i] == 1) {
                        Window.draw(Brick[i]);
                    }
                }
            }

            if (NIGHT == true) {
                DAY == false;
                //textures
                sf::Texture ball;
                ball.loadFromFile("Data/ballNM.png");
                Ball.setTexture(&ball);

                sf::Texture Rborder_tex;
                Rborder_tex.loadFromFile("Data/RBNM.png");
                Border_Right.setTexture(&Rborder_tex);
                sf::Texture Lborder_tex;

                Lborder_tex.loadFromFile("Data/LBNM.png");
                Border_Left.setTexture(&Lborder_tex);
                sf::Texture topborder;

                topborder.loadFromFile("Data/TPNM.png");
                Border_Top.setTexture(&topborder);

                sf::Texture bricks;
                bricks.loadFromFile("Data/brickNM.png");
                for (int i = 0; i < 10; i++)
                {
                    Brick[i].setTexture(&bricks);
                }

                sf::Texture sliderTex;
                sliderTex.loadFromFile("Data/slideNM.png");
                Slider.setTexture(&sliderTex);

                Window.clear();

                Window.draw(Ball);
                Window.draw(Slider);
                Window.draw(Border_Top);
                Window.draw(Border_Left);
                Window.draw(Border_Right);
                for (int i = 0; i < 10; i++)
                {
                    if (exist[i] == 1) {
                        Window.draw(Brick[i]);
                    }
                }

            }

            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            //logic handlings
            Ball.move(1 * X_BallSpeed, 1 * Y_BallSpeed);

            //Slider Movement
            if (Right_Key == true && Slider.getGlobalBounds().intersects(Border_Right.getGlobalBounds()) == false)
            {
                Slider.move(4.0f, 0);
            }
            if (Left_Key == true && Slider.getGlobalBounds().intersects(Border_Left.getGlobalBounds()) == false)
            {
                Slider.move(-4.0f, 0);
            }

            //Ball hits Left or Right Boarder
            if (Ball.getGlobalBounds().intersects(Border_Right.getGlobalBounds()) == true || Ball.getGlobalBounds().intersects(Border_Left.getGlobalBounds()) == true)
            {
                X_BallSpeed = -X_BallSpeed;
            }
            //Ball hits Top Boarder
            if (Ball.getGlobalBounds().intersects(Border_Top.getGlobalBounds()) == true)
            {
                Y_BallSpeed = -Y_BallSpeed;
            }

            //Ball hits Slider
            if (Ball.getGlobalBounds().intersects(Slider.getGlobalBounds()) == true)
            {
                // [ 0 , 10 ] (30 deg Left)
                if (Ball.getPosition().x > (Slider.getPosition().x) + 0 && Ball.getPosition().x <= (Slider.getPosition().x) + 10)
                {
                    X_BallSpeed = -4.33 , Y_BallSpeed = -2.5;
                }
                // [ 11 , 40 ] (45 deg Left)
                else if (Ball.getPosition().x > (Slider.getPosition().x) + 11 && Ball.getPosition().x <= (Slider.getPosition().x) + 40)
                {
                    X_BallSpeed = -3.53553 , Y_BallSpeed = -3.53553;
                }
                // [ 41 , 70 ] (60 deg Left)
                else if (Ball.getPosition().x > (Slider.getPosition().x) + 41 && Ball.getPosition().x <= (Slider.getPosition().x) + 70)
                {
                    X_BallSpeed = -2.5 , Y_BallSpeed = -4.33;
                }
                // [ 71 , 80 ] (90 deg Up)
                else if (Ball.getPosition().x > (Slider.getPosition().x) + 71 && Ball.getPosition().x <= (Slider.getPosition().x) + 80)
                {
                    X_BallSpeed = 0;
                    Y_BallSpeed = -5;
                }
                // [ 81 , 110 ] (60 deg Right)
                else if (Ball.getPosition().x > (Slider.getPosition().x) + 81 && Ball.getPosition().x <= (Slider.getPosition().x) + 110)
                {
                    X_BallSpeed = 2.5;
                    Y_BallSpeed = -4.33;
                }
                // [ 111 , 140 ]  (45 deg Right)
                else if (Ball.getPosition().x > (Slider.getPosition().x) + 111 && Ball.getPosition().x <= (Slider.getPosition().x) + 140)
                {
                    X_BallSpeed = 3.53553;
                    Y_BallSpeed = -3.53553;
                }
                // [ 141 , 150 ] (30 deg Right)
                else if (Ball.getPosition().x > (Slider.getPosition().x) + 141 && Ball.getPosition().x < (Slider.getPosition().x) + 150)
                {
                    X_BallSpeed = 4.33;
                    Y_BallSpeed = -2.5;
                }
                else
                {
                    X_BallSpeed = -X_BallSpeed;
                }
            }

            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            //Ball hits Bricks

            for (int i = 0; i < 10; i++)
            {
                if (exist[i])
                {
                    if ((Ball.getPosition().x >= Brick[i].getPosition().x - Ball_Rad) && (Ball.getPosition().x <= Brick[i].getPosition().x + Brick_Width + Ball_Rad) &&
                        (Ball.getPosition().y >= Brick[i].getPosition().y - Ball_Rad) && (Ball.getPosition().y <= Brick[i].getPosition().y + Brick_Thick + Ball_Rad))
                    {
                        exist[i] = 0;

                        if ((Ball.getPosition().x >= Brick[i].getPosition().x - Ball_Rad + 1) && (Ball.getPosition().x <= Brick[i].getPosition().x + Brick_Width + Ball_Rad - 1))
                            Y_BallSpeed = -Y_BallSpeed;
                        else
                            X_BallSpeed = -X_BallSpeed;

                        Hits_Counter++;

                        pop.play();
                        pop.setPlayingOffset(sf::seconds(0.5));
                    }
                }
            }
            Score_String = to_string(Hits_Counter * 100);
            Score_Num.setString(Score_String);

            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            if (Ball.getPosition().y > Window_Height + Ball_Rad + 1 || Hits_Counter == 10)
            {
                Ball.setPosition(-2000000, -1000000);
                X_BallSpeed = 0;
                Y_BallSpeed = 0;
                Loser = 1;
                lose.play();
                music.pause();
            }

            if (Loser && Hits_Counter != 10)
            {
                WL_Text.setFillColor(sf::Color(255, 0, 0));
                WL_Text.setString("You Lost!!");
                Window.draw(WL_Text);
                break;
            }
            else if (Hits_Counter == 10)
            {
                WL_Text.setFillColor(sf::Color(0, 255, 0));
                WL_Text.setString("You won !!");
                Window.draw(WL_Text);
            }

            Window.draw(Score_Text);
            Window.draw(Score_Num);

            Window.display();
        }
        
    }
    return 0;
}
