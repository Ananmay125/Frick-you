#include <iostream>
#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>
#include<SFML/audio.hpp>

using namespace std;
using namespace sf;

sf::Music music;

int main() {

    Music music1;
    if (!music1.openFromFile("assets/greenhill.ogg")) {
        return -1;
    }

    Music music2;
    if (!music2.openFromFile("assets/Rooftop-Run-Act-1.ogg")) {
        return -1;
    }

    music1.play();

    const float gravity = 0.02f;
    const float maxSpeed = 0.5f;
    const float acceleration = 0.4f;
    const float airAcceleration = 0.2f;
    const float jumpStrength = 3.0f;
    bool isJumping = false;
    bool isOnGround = false;
    Vector2f velocity(0, 0);
    /*ing x;
    string y;
    string option;
    string rules;
    string rules2;
    string rules3;
    string rules4;
    string rules5;
    string rules6;
    string rules7;
    string rules8;
    string rules9;
    string rules10;
    string rules11;
    string understand;
    string cards1;
    string cards2;
    string cards3;
    string cards4;
    string cards5;
    string draw_card;

    rules = "Title: Frick You Showdown";
    rules2 = "Objective: Be the last player standing by avoiding picking the 'Frick You' card.";
    rules3 = "Materials: A standard deck of cards";
    rules4 = "Setup: Shuffle the deck of cards. Deal 5 cards to each player.";
    rules5 = "Gameplay:";
    rules6 = "Each player secretly selects one card from their hand to play, facedown";
    rules7 = "Once all players have chosen their cards, everyone reveals their selections simultaneously.";
    rules8 = "If both players reveal the same card the person who has the chance then would win";
    rules9 = "If both the players took different card a new round begins";
    rules11 = "Repeat steps 1 - 4 until there is only one player left.";
    cards1 = "Frick you";
    cards2 = "King";
    cards3 = "pawn";
    cards4 = "ligma";
    cards5 = "sigma";

    cout << "Hello! ";
    cin >> x;
    cout << "My name is gyatt wht is urs? ";
    cin >> y;
    cout << endl;
    cout << "Glad to meet you " + y << endl;
    cout << endl;
    cout << "Wanna play a game? ";
    cin >> option;

    if (option == "yes" || option == "yeah" || option == "yeshsir" || option == "yea" || option == "ye") {
        cout << endl;
        cout << "cool let's start!" << endl;
        cout << endl;
        cin.get();
    }
    else {
        cout << "Frick you!";
        cin.get();
        return 0;
    }*/

    Color LightBlue(173, 216, 230);
    VideoMode desktopMode = VideoMode::getDesktopMode();

    RenderWindow frame(VideoMode(desktopMode.width, desktopMode.height), "Frick you", Style::Fullscreen);

    Image icon;
    if (!icon.loadFromFile("assets/sonic2.png")) {
        return -1;
    }
    frame.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    Vector2u windowSize = frame.getSize();
    float rectangleHeight = 0.2f * windowSize.y;

    RectangleShape balls(Vector2f(150.0f, 50.0f));
    balls.setFillColor(Color::Green);
    balls.setPosition(15, 15);

    RectangleShape ground(Vector2f(windowSize.x, rectangleHeight));
    ground.setFillColor(Color::Green);
    ground.setPosition(0, windowSize.y - rectangleHeight);

    Texture texture;
    if (!texture.loadFromFile("assets/sonic-sprite.png"))
        return -1;

    Sprite player(texture);

    float scaleFactor = 50.0f / player.getGlobalBounds().width;
    player.setScale(scaleFactor, scaleFactor);

    player.setPosition(0, frame.getSize().y - rectangleHeight - player.getGlobalBounds().height);

    float playerSpeed = 0.5f;

    float aspectRatio = float(frame.getSize().x) / float(frame.getSize().y);
    sf::View view(sf::FloatRect(0, 0, 800, 600));
    view.setViewport(sf::FloatRect(0, 0, 1, 1));

    while (frame.isOpen()) {
        Event event;
        while (frame.pollEvent(event)) {
            if (event.type == Event::Closed) {
                frame.close();
            }
            else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Space && isOnGround) {
                velocity.y = -jumpStrength;
                isJumping = true;
                isOnGround = false;
            }
        }

        if (music1.getStatus() == Music::Stopped) {
            music2.play();
        }

        if (Keyboard::isKeyPressed(Keyboard::D)) {
            velocity.x += isOnGround ? acceleration : airAcceleration;
        }
        else if (Keyboard::isKeyPressed(Keyboard::A)) {
            velocity.x -= isOnGround ? acceleration : airAcceleration;
        }
        else {
            if (isOnGround) {
                if (velocity.x > 0) {
                    velocity.x -= acceleration;
                    if (velocity.x < 0) velocity.x = 0;
                }
                else if (velocity.x < 0) {
                    velocity.x += acceleration;
                    if (velocity.x > 0) velocity.x = 0;
                }
            }
        }

        if (velocity.x > maxSpeed) velocity.x = maxSpeed;
        else if (velocity.x < -maxSpeed) velocity.x = -maxSpeed;

        velocity.y += gravity;
        player.move(velocity);

        if (player.getPosition().y >= 400) {
            isOnGround = true;
            isJumping = false;
            velocity.y = 0;
            player.setPosition(player.getPosition().x, 400);
        }

        frame.clear(LightBlue);
        frame.draw(balls);
        frame.draw(ground);
        frame.draw(player);
        frame.display();
    }

    return 0;
}
