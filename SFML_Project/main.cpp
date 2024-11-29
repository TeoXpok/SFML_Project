#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

using namespace sf;
using namespace std;

struct cell {
    bool isgood = false;
    bool iscross = false;
    bool ispaint = false;
    int x;
    int y;
};


vector<vector<int>> rowIndices;
vector<vector<int>> colIndices;

RenderWindow window(sf::VideoMode(1920, 1080), "The picross Magician");
cell tab[10][10];
vector<RectangleShape> maps;
vector<RectangleShape> squares;
vector<RectangleShape> crosses;


vector<vector<int>> calculateRowIndices() {
    vector<vector<int>> indices(10);
    for (int i = 0; i < 10; i++) {
        int count = 0;
        for (int j = 0; j < 10; j++) {
            if (tab[i][j].isgood) {
                count++;
            }
            else if (count > 0) {
                indices[i].push_back(count);
                count = 0;
            }
        }
        if (count > 0) indices[i].push_back(count);

        // Inverser l'ordre des indices pour la ligne
        reverse(indices[i].begin(), indices[i].end());
    }
    return indices;
}


vector<vector<int>> calculateColIndices() {
    vector<vector<int>> indices(10);
    for (int j = 0; j < 10; j++) {
        int count = 0;
        for (int i = 0; i < 10; i++) {
            if (tab[i][j].isgood) {
                count++;
            }
            else if (count > 0) {
                indices[j].push_back(count);
                count = 0;
            }
        }
        if (count > 0) indices[j].push_back(count);

        // Inverser l'ordre des indices pour la colonne
        reverse(indices[j].begin(), indices[j].end());
    }
    return indices;
}

void generategame(){
    int x;
    int y;
    bool set = false;
    for (size_t i = 0; i < 50; i++)
    {
        while (!set) {
            x = rand() % 10;
            y = rand() % 10;
            if (!tab[y][x].isgood) {
                tab[y][x].isgood = true;
                set = true;
            }
        }
        set = false;
    }
}

void resetgame() {
    for (size_t i = 0; i < 10; i++)
    {
        for (size_t j = 0; j < 10; j++)
        {
            tab[i][j].isgood = false;
            tab[i][j].ispaint = false;
            tab[i][j].iscross = false;
        }
    }
}

void spawn() {
    RectangleShape column(Vector2f(5, 905));
    RectangleShape line(Vector2f(905, 5));
    int x = 610;
    int y = 155;
    column.setFillColor(Color(181, 181, 181));
    line.setFillColor(Color(181, 181, 181));

    for (size_t i = 0; i < 14; i++) {
        column.setPosition(Vector2f(x, 95));
        line.setPosition(Vector2f(550, y));
        maps.push_back(column);
        maps.push_back(line);
        x += 60;
        y += 60;
    }
    column.setFillColor(Color::Black);
    line.setFillColor(Color::Black);
    {
        column.setPosition(Vector2f(550, 95));
        line.setPosition(Vector2f(550, 95));
        maps.push_back(column);
        maps.push_back(line);
        column.setPosition(Vector2f(1450, 95));
        line.setPosition(Vector2f(550, 995));
        maps.push_back(column);
        maps.push_back(line);
    }
    RectangleShape square(Vector2f(55, 55));
    square.setFillColor(Color::Black);

    x = 855;
    y = 400;
    for (size_t i = 0; i < 10; i++) {
        for (size_t j = 0; j < 10; j++) {
            square.setPosition(Vector2f(x, y));
            squares.push_back(square);
            x += 60;
        }
        y += 60;
        x = 855;
    }

    x = 860;
    y = 412;
    RectangleShape cross(Vector2f(10, 55));
    cross.setFillColor(Color::Red);
    cross.setRotation(-45);
    for (size_t i = 0; i < 10; i++) {
        for (size_t j = 0; j < 10; j++) {
            cross.setPosition(Vector2f(x, y));
            crosses.push_back(cross);
            x += 60;
        }
        y += 60;
        x = 860;
    }
    generategame();
}

void drawmap(Font& font) {
    for (const auto& border : maps) {
        window.draw(border);
    }

    for (size_t i = 0; i < 10; i++) {
        for (size_t j = 0; j < 10; j++) {
            if (tab[i][j].ispaint) {
                window.draw(squares[i * 10 + j]);
            }
            else if (tab[i][j].iscross) {
                window.draw(crosses[i * 10 + j]);
            }
        }
    }


    for (size_t i = 0; i < rowIndices.size(); i++) {
        int x = 812;
        int y = 412 + i * 60;
        for (int num : rowIndices[i]) {
            Text text;
            text.setFont(font);
            text.setString(to_string(num));
            text.setCharacterSize(20);
            text.setFillColor(Color::Black);
            text.setPosition(x, y);
            window.draw(text);
            x -= 60;
        }
    }


    for (size_t j = 0; j < colIndices.size(); j++) {
        int x = 872 + j * 60;
        int y = 352;
        for (int num : colIndices[j]) {
            Text text;
            text.setFont(font);
            text.setString(to_string(num));
            text.setCharacterSize(20);
            text.setFillColor(Color::Black);
            text.setPosition(x, y);
            window.draw(text);
            y -= 60;
        }
    }
}

bool win() {
    for (size_t i = 0; i < 10; i++)
    {
        for (size_t j = 0; j < 10; j++)
        {
            if (tab[i][j].isgood && !tab[i][j].ispaint) return false;
            if (!tab[i][j].isgood && tab[i][j].ispaint) return false;
        }
    }
    return true;
}

void reset() {
    for (size_t i = 0; i < 10; i++)
    {
        for (size_t j = 0; j < 10; j++)
        {
            tab[i][j].ispaint = false;
            tab[i][j].iscross = false;
        }
    }
}

void cheat() {
    for (size_t i = 0; i < 10; i++)
    {
        for (size_t j = 0; j < 10; j++)
        {
            if (!tab[i][j].isgood) {
                tab[i][j].ispaint = false;
                tab[i][j].iscross = true;
            }

        }
    }

}
void drawWin(Font& font) {
    Text winText;
    winText.setFont(font);
    winText.setString("Bravo vous avez gagne !!");
    winText.setCharacterSize(30);
    winText.setFillColor(Color::Black);
    winText.setPosition(825, 300);
    window.draw(winText);
}

void drawEndMenu(Font& font) {
    Text endText;
    endText.setFont(font);
    endText.setString("Appuyez sur 'R' pour recommencer ou 'Q' pour quitter.");
    endText.setCharacterSize(30);
    endText.setFillColor(Color::Black);
    endText.setPosition(650, 400);
    window.draw(endText);
}

void drawControle(Font& font) {
    Text Text;
    Text.setFont(font);
    Text.setString("Utilisez 'Z' 'Q' 'S' 'D' \npour vous deplacer   \n\nUtilisez le clic gauche \npour dessiner    \n\nUtilisez le clic droit \npour mettre des croix    \n\nUtilisez le clic molette \npour gommer    \n\nBon courage !");
    Text.setCharacterSize(30);
    Text.setFillColor(Color::Black);
    Text.setPosition(50, 250);
    window.draw(Text);
}

int main() {
    srand(time(0));
    Font font;
    if (!font.loadFromFile("Arimo.ttf")) {
        cerr << "Impossible de charger la police !" << endl;
        return -1;
    }

    Clock moveClock;
    float moveDelay = 0.2f;

    spawn();
    rowIndices = calculateRowIndices();
    colIndices = calculateColIndices();

    RectangleShape player(Vector2f(60, 60));
    player.setFillColor(Color::Yellow);
    player.setPosition(Vector2f(855, 400));
    int playerx = 0;
    int playery = 0;
    int mousex = 0;
    int mousey = 0;
    bool run = true;
    bool victory = false;
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }
        if(run)
        {

            if (Mouse::isButtonPressed(Mouse::Left) && Mouse::getPosition().y > 430 && Mouse::getPosition().y < 1030 && Mouse::getPosition().x > 860 && Mouse::getPosition().x < 1457) {
                mousey = (Mouse::getPosition().y - 430) / 60;
                mousex = (Mouse::getPosition().x - 860) / 60;
                if ((mousey - playery == 1 || mousey - playery == 0 || mousey - playery == -1) && (mousex - playerx == 1 || mousex - playerx == 0 || mousex - playerx == -1))
                {
                    if (mousey - playery == 0 && mousex - playerx == 0) {}
                    else tab[mousey][mousex].ispaint = true;
                }
            }
            if (Mouse::isButtonPressed(Mouse::Right) && Mouse::getPosition().y > 430 && Mouse::getPosition().y < 1030 && Mouse::getPosition().x > 860 && Mouse::getPosition().x < 1457) {
                mousey = (Mouse::getPosition().y - 430) / 60;
                mousex = (Mouse::getPosition().x - 860) / 60;
                if ((mousey - playery == 1 || mousey - playery == 0 || mousey - playery == -1) && (mousex - playerx == 1 || mousex - playerx == 0 || mousex - playerx == -1))
                {
                    if (mousey - playery == 0 && mousex - playerx == 0) {}
                    else tab[mousey][mousex].iscross = true;
                }
            }
            if (Mouse::isButtonPressed(Mouse::Middle) && Mouse::getPosition().y > 430 && Mouse::getPosition().y < 1030 && Mouse::getPosition().x > 860 && Mouse::getPosition().x < 1457) {
                tab[(Mouse::getPosition().y - 430) / 60][(Mouse::getPosition().x - 860) / 60].ispaint = false;
                tab[(Mouse::getPosition().y - 430) / 60][(Mouse::getPosition().x - 860) / 60].iscross = false;
            }
            if (moveClock.getElapsedTime().asSeconds() >= moveDelay) {
                if (Keyboard::isKeyPressed(Keyboard::Z) && playery > 0 && !tab[playery - 1][playerx].ispaint && !tab[playery - 1][playerx].iscross) {
                    player.move(Vector2f(0, -60)); playery -= 1; moveClock.restart();
                }
                if (Keyboard::isKeyPressed(Keyboard::S) && playery < 9 && !tab[playery + 1][playerx].ispaint && !tab[playery + 1][playerx].iscross) {
                    player.move(Vector2f(0, 60)); playery += 1;moveClock.restart();
                }
                if (Keyboard::isKeyPressed(Keyboard::D) && playerx < 9 && !tab[playery][playerx + 1].ispaint && !tab[playery][playerx + 1].iscross) {
                    player.move(Vector2f(60, 0)); playerx += 1;moveClock.restart();
                }
                if (Keyboard::isKeyPressed(Keyboard::Q) && playerx > 0 && !tab[playery][playerx - 1].ispaint && !tab[playery][playerx - 1].iscross) {
                    player.move(Vector2f(-60, 0)); playerx -= 1;moveClock.restart();
                }
                if (Keyboard::isKeyPressed(Keyboard::Escape)) run = false;
                if (Keyboard::isKeyPressed(Keyboard::K)) cheat();
                if (Keyboard::isKeyPressed(Keyboard::R)) reset();
                if (win()) { run = false; victory = true; }

            }
            window.clear(Color(55, 225, 225));
            window.draw(player);
            drawmap(font);
            drawControle(font);
            window.display();
        }
        else {
            window.clear(Color(55, 225, 225));

           
            if (Keyboard::isKeyPressed(Keyboard::R)) {
                resetgame();
                reset();
                spawn();
                rowIndices = calculateRowIndices();
                colIndices = calculateColIndices();
                player.setPosition(Vector2f(855, 400));
                playerx = 0;
                playery = 0;
                run = true; 
                victory = false;
            }

           
            if (Keyboard::isKeyPressed(Keyboard::Q)) {
                window.close();
            }
            if (victory) drawWin(font);
            
            drawEndMenu(font);

            window.display();
        }


    }

    return 0;
}
