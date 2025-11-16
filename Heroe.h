//
// Created by Dell on 11/11/2025.
//
// Heroe.h
#ifndef HEROE_H
#define HEROE_H

#include <string>

class Heroe {
private:
    std::string nombre;
    int hp;
    int atk;
    int def;

public:
    Heroe(std::string n, int h, int a, int d)
            : nombre(n), hp(h), atk(a), def(d) {}

    std::string getNombre() const { return nombre; }
    int getHP() const { return hp; }
    int getATK() const { return atk; }
    int getDEF() const { return def; }

    void recibirDano(int dano) { hp -= dano; }
    bool estaVivo() const { return hp > 0; }

    void mejorarStats(int bonusHP, int bonusATK, int bonusDEF) {
        hp += bonusHP;
        atk += bonusATK;
        def += bonusDEF;
    }
};

#endif
