#define _CRT_SECURE_NO_WARNINGS
#ifndef SENECA_BARBARIAN_H
#define SENECA_BARBARIAN_H

#include "characterTpl.h"
#include "abilities.h"
#include "weapons.h"
#include "health.h"
#include <iostream>

namespace seneca {

    template <typename T, typename Ability_t, typename Weapon_t>
    class Barbarian : public CharacterTpl<T> {
        int m_baseDefense;
        int m_baseAttack;
        Ability_t m_ability;
        Weapon_t m_weapon[2]; // �� ���� ���� ���

    public:
        // ������
        Barbarian(const char* name, int healthMax, int baseAttack, int baseDefense, Weapon_t primaryWeapon, Weapon_t secondaryWeapon)
            : CharacterTpl<T>(name, healthMax), m_baseDefense(baseDefense), m_baseAttack(baseAttack) {
            m_weapon[0] = primaryWeapon;
            m_weapon[1] = secondaryWeapon;
        }

        // ���ݷ� ��ȯ �Լ� (�������̵�)
        int getAttackAmnt() const override {
            return static_cast<int>(m_baseAttack + static_cast<double>(m_weapon[0]) / 2 + static_cast<double>(m_weapon[1]) / 2);
        }


        // ���� ��ȯ �Լ� (�������̵�)
        int getDefenseAmnt() const override {
            return m_baseDefense;
        }

        // ĳ���� ���� �Լ� (�������̵�)
        Character* clone() const override {
            return new Barbarian(*this);
        }

        // ���� �Լ� (�������̵�)
        void attack(Character* enemy) override {
            std::cout << this->getName() << " is attacking " << enemy->getName() << "." <<std::endl;

            // Ư�� �ɷ� ���
            m_ability.useAbility(this);

            // �⺻ ���ݷ� ���
            int dmg = getAttackAmnt();

            // Ư�� �ɷ����� ��ȭ�� ���ݷ� ����
            m_ability.transformDamageDealt(dmg);

            std::cout << "    Barbarian deals " << dmg << " melee damage!" << std::endl;

            // ������ ���� ����
            enemy->takeDamage(dmg);
        }

        // ���� �Ա� �Լ� (�������̵�)
        void takeDamage(int dmg) override {
            std::cout << this->getName() << " is attacked for " << dmg << " damage." << std::endl;
            std::cout << "    Barbarian has a defense of " << m_baseDefense << ". Reducing damage received." << std::endl;

            // �������� ���� ����
            dmg -= m_baseDefense;
            if (dmg < 0) {
                dmg = 0;
            }

            // Ư�� �ɷ����� ���� �߰� ����
            m_ability.transformDamageReceived(dmg);

            // �θ� Ŭ������ takeDamage() ȣ���Ͽ� ü�� ������Ʈ
            CharacterTpl<T>::takeDamage(dmg);
        }
    };

} // namespace seneca

#endif
