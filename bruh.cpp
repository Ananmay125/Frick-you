#include <iostream>
#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;

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

    // Set player's initial position to be on the ground
    player.setPosition(0, windowSize.y - rectangleHeight - player.getGlobalBounds().height);

    float playerSpeed = 0.5f;

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

        // Check for collision with the ground
        if (player.getGlobalBounds().intersects(ground.getGlobalBounds())) {
            isOnGround = true;
            isJumping = false;
            velocity.y = 0;
            player.setPosition(player.getPosition().x, ground.getPosition().y - player.getGlobalBounds().height);
        }

        frame.clear(LightBlue);
        frame.draw(balls);
        frame.draw(ground);
        frame.draw(player);
        frame.display();
    }

    return 0;
}
