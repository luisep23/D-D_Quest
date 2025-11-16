//
// Created by Dell on 11/11/2025.
//
// Monstruo.h
#ifndef MONSTRUO_H
#define MONSTRUO_H

#include <string>

class Monstruo {
private:
    int id;
    std::string nombre;
    int hp;
    int atk;
    int def;
    double probabilidad;
    int recompensaHP;
    int recompensaATK;
    int recompensaDEF;

public:
    Monstruo(int id, std::string n, int h, int a, int d, double prob,
             int rHP, int rATK, int rDEF)
            : id(id), nombre(n), hp(h), atk(a), def(d), probabilidad(prob),
              recompensaHP(rHP), recompensaATK(rATK), recompensaDEF(rDEF) {}

    // Getters
    std::string getNombre() const { return nombre; }
    int getHP() const { return hp; }
    int getATK() const { return atk; }
    int getDEF() const { return def; }
    double getProbabilidad() const { return probabilidad; }

    void recibirDano(int dano) { hp -= dano; }
    bool estaVivo() const { return hp > 0; }

    int getRecompensaHP() const { return recompensaHP; }
    int getRecompensaATK() const { return recompensaATK; }
    int getRecompensaDEF() const { return recompensaDEF; }
};

#endif
