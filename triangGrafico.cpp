#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <SFML/Graphics.hpp>

bool esTrianguloMagico(const std::vector<int>& numeros) {
    int suma1 = numeros[0] + numeros[1] + numeros[2];
    int suma2 = numeros[2] + numeros[3] + numeros[4];
    int suma3 = numeros[4] + numeros[5] + numeros[0];
    return (suma1 == suma2 && suma2 == suma3);
}

void encontrarCombinacionMagica(std::vector<int>& numeros) {
    std::sort(numeros.begin(), numeros.end());
    do {
        for (int i = 0; i < numeros.size(); ++i) {
            std::vector<int> rotados(numeros.begin(), numeros.end());
            std::rotate(rotados.begin(), rotados.begin() + i, rotados.end());
            if (esTrianguloMagico(rotados)) {
                std::cout << "Combinacion magica encontrada! Orden: ";
                for (int num : rotados) {
                    std::cout << num << " ";
                }
                std::cout << std::endl;
                return;
            }
        }
    } while (std::next_permutation(numeros.begin(), numeros.end()));
    std::cout << "No se encontro una combinacion magica." << std::endl;
}

void graficarTrianguloMagico(const std::vector<int>& numeros, int n) {
    sf::RenderWindow ventana(sf::VideoMode(800, 600), "Triangulo Magico");

    sf::Font fuente;
    if (!fuente.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
        std::cerr << "Error cargando la fuente" << std::endl;
        return;
    }

    sf::Text texto;
    texto.setFont(fuente);
    texto.setCharacterSize(24);
    texto.setFillColor(sf::Color::White);

    std::vector<sf::Vector2f> posiciones;
    float xCentro = 400, yCentro = 150;
    float distancia = 50;

    // Lado izquierdo
    for (int i = 0; i < n; i++) {
        posiciones.push_back({xCentro - i * distancia / 2, yCentro + i * distancia});
    }
    // Lado inferior
    for (int i = 1; i < n; i++) {
        posiciones.push_back({xCentro - (n - 1) * distancia / 2 + i * distancia, yCentro + (n - 1) * distancia});
    }
    // Lado derecho
    for (int i = 1; i < n - 1; i++) {
        posiciones.push_back({xCentro + i * distancia / 2, yCentro + (n - 1 - i) * distancia});
    }

    while (ventana.isOpen()) {
        sf::Event evento;
        while (ventana.pollEvent(evento)) {
            if (evento.type == sf::Event::Closed)
                ventana.close();
        }

        ventana.clear();

        for (size_t i = 0; i < numeros.size(); i++) {
            texto.setString(std::to_string(numeros[i]));
            texto.setPosition(posiciones[i]);
            ventana.draw(texto);
        }

        ventana.display();
    }
}

int main() {
    int numerosPorLado;
    std::cout << "Ingrese la cantidad de numeros por lado del triangulo magico (debe ser al menos 3):" << std::endl;
    std::cin >> numerosPorLado;

    int totalNumeros = numerosPorLado * 3 - 3;
    std::vector<int> numeros(totalNumeros);
    std::cout << "Ingrese " << totalNumeros << " numeros naturales diferentes:" << std::endl;
    for (int i = 0; i < totalNumeros; ++i) {
        std::cin >> numeros[i];
    }

    std::unordered_set<int> numerosUnicos(numeros.begin(), numeros.end());
    if (numerosUnicos.size() != totalNumeros) {
        std::cout << "Los numeros deben ser diferentes." << std::endl;
        return 1;
    }

    encontrarCombinacionMagica(numeros);

    if (esTrianguloMagico(numeros)) {
        graficarTrianguloMagico(numeros, numerosPorLado);
    }

    return 0;
}