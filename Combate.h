//
// Created by Dell on 11/11/2025.
//
// Combate.h
#ifndef COMBATE_H
#define COMBATE_H

#include "Heroe.h"
#include "Monstruo.h"
#include <iostream>
#include <algorithm>

class Combate {
public:
    static bool pelear(Heroe& heroe, Monstruo& monstruo) {
        std::cout << "\n¡Encuentro con " << monstruo.getNombre() << "!\n";
        std::cout << "HP: " << monstruo.getHP() << " | ATK: " << monstruo.getATK()
                  << " | DEF: " << monstruo.getDEF() << "\n\n";

        int turno = 1;
        while (heroe.estaVivo() && monstruo.estaVivo()) {
            std::cout << "--- Turno " << turno << " ---\n";

            // Turno del héroe
            int danoHeroe = std::max(1, heroe.getATK() - monstruo.getDEF());
            monstruo.recibirDano(danoHeroe);
            std::cout << heroe.getNombre() << " ataca y causa " << danoHeroe
                      << " de daño. HP enemigo: " << std::max(0, monstruo.getHP()) << "\n";

            if (!monstruo.estaVivo()) break;

            // Turno del monstruo
            int danoMonstruo = std::max(1, monstruo.getATK() - heroe.getDEF());
            heroe.recibirDano(danoMonstruo);
            std::cout << monstruo.getNombre() << " ataca y causa " << danoMonstruo
                      << " de daño. Tu HP: " << std::max(0, heroe.getHP()) << "\n\n";

            turno++;
        }

        if (heroe.estaVivo()) {
            std::cout << "¡Victoria! Obtienes mejoras: +"
                      << monstruo.getRecompensaHP() << " HP, +"
                      << monstruo.getRecompensaATK() << " ATK, +"
                      << monstruo.getRecompensaDEF() << " DEF\n";
            heroe.mejorarStats(monstruo.getRecompensaHP(),
                               monstruo.getRecompensaATK(),
                               monstruo.getRecompensaDEF());
            return true;
        } else {
            std::cout << "Has sido derrotado...\n";
            return false;
        }
    }
};

#endif
