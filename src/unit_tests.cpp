#include <iostream>
#include <cassert>
#include <string>

void testBasicFunctionality() {
    int a = 2;
    int b = 3;
    assert((a + b) == 5 && "Test échoué : Addition incorrecte !");
    std::cout << "✅ Test de fonctionnalité de base réussi !" << std::endl;
}

int main() {
    std::cout << "Lancement des tests..." << std::endl;
    testBasicFunctionality();
    std::cout << "Tous les tests sont passés avec succès !" << std::endl;
    return 0;
}
