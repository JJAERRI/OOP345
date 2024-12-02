#define _CRT_SECURE_NO_WARNINGS
#ifndef SENECA_ARCHER_H
#define SENECA_ARCHER_H

#include "characterTpl.h"
#include <iostream>

namespace seneca {

    template <typename Weapon_t>
    class Archer : public CharacterTpl<seneca::SuperHealth> {
        int m_baseDefense;
        int m_baseAttack;
        Weapon_t m_weapon; // ���� ��ü (�׷��� ������ ������ ����)

    public:
        // ������
        Archer(const char* name, int healthMax, int baseAttack, int baseDefense, Weapon_t weapon)
            : CharacterTpl<seneca::SuperHealth>(name, healthMax), m_baseDefense(baseDefense), m_baseAttack(baseAttack), m_weapon(weapon) {}  // ���� ����


        // ���ݷ� ��ȯ �Լ� (�������̵�)
        int getAttackAmnt() const override {
            return static_cast<int>(1.3 * m_baseAttack); // ���ݷ��� �����ϰ� baseAttack�� ���
        }

        // ���� ��ȯ �Լ� (�������̵�)
        int getDefenseAmnt() const override {
            return static_cast<int>(1.2 * m_baseDefense); // ������ baseDefense�� ���
        }

        // ĳ���� ���� �Լ� (�������̵�)
        Character* clone() const override {
            return new Archer(*this);
        }

        // ���� �Լ� (�������̵�)
        void attack(Character* enemy) override {
            std::cout << this->getName() << " is attacking " << enemy->getName() << "." << std::endl;

            // �⺻ ���ݷ� ���
            int dmg = getAttackAmnt();

            std::cout << "    Archer deals " << dmg << " ranged damage!\n";

            // ������ ���� ����
            enemy->takeDamage(dmg);
        }

        // ���� �Ա� �Լ� (�������̵�)
        void takeDamage(int dmg) override {
            std::cout << this->getName() << " is attacked for " << dmg << " damage." << std::endl;
            std::cout << "    Archer has a defense of " << getDefenseAmnt() << ". Reducing damage received." << std::endl;

            // �������� ���� ����
            dmg -= getDefenseAmnt();
            if (dmg < 0) {
                dmg = 0;
            }

            // �θ� Ŭ������ takeDamage() ȣ���Ͽ� ü�� ������Ʈ
            CharacterTpl<seneca::SuperHealth>::takeDamage(dmg);
        }
    };

}

#endif