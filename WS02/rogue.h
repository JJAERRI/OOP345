#define _CRT_SECURE_NO_WARNINGS
#ifndef SENECA_ROGUE_H
#define SENECA_ROGUE_H

#include "characterTpl.h"
#include "weapons.h"
#include <iostream>

namespace seneca {

    template <typename T, typename FirstAbility_t, typename SecondAbility_t>
    class Rogue : public CharacterTpl<T> {
        int m_baseDefense;
        int m_baseAttack;
        FirstAbility_t m_firstAbility;
        SecondAbility_t m_secondAbility;
        seneca::Dagger m_weapon; // ����: Dagger

    public:
        // ������
        Rogue(const char* name, int healthMax, int baseAttack, int baseDefense)
            : CharacterTpl<T>(name, healthMax), m_baseDefense(baseDefense), m_baseAttack(baseAttack) {}  // ���� ����

        // ���ݷ� ��ȯ �Լ� (�������̵�)
        int getAttackAmnt() const override {
            return static_cast<int>(m_baseAttack + 2 * static_cast<double>(m_weapon));
        }


        // ���� ��ȯ �Լ� (�������̵�)
        int getDefenseAmnt() const override {
            return m_baseDefense;
        }

        // ĳ���� ���� �Լ� (�������̵�)
        Character* clone() const override {
            return new Rogue(*this);
        }

        // ���� �Լ� (�������̵�)
        void attack(Character* enemy) override {
            std::cout << this->getName() << " is attacking " << enemy->getName() << "." << std::endl;

            // ù ��° Ư�� �ɷ� ���
            m_firstAbility.useAbility(this);

            // �� ��° Ư�� �ɷ� ���
            m_secondAbility.useAbility(this);

            // �⺻ ���ݷ� ���
            int dmg = getAttackAmnt();

            // ù ��° Ư�� �ɷ����� ���ݷ� ��ȭ
            m_firstAbility.transformDamageDealt(dmg);

            // �� ��° Ư�� �ɷ����� ���ݷ� ��ȭ
            m_secondAbility.transformDamageDealt(dmg);

            std::cout << "    Rogue deals " << dmg << " melee damage!" << std::endl;

            // ������ ���� ����
            enemy->takeDamage(dmg);
        }

        // ���� �Ա� �Լ� (�������̵�)
        void takeDamage(int dmg) override {
            std::cout << this->getName() << " is attacked for " << dmg << " damage." << std::endl;
            std::cout << "    Rogue has a defense of " << getDefenseAmnt() << ". Reducing damage received." << std::endl;

            // �������� ���� ����
            dmg -= getDefenseAmnt();
            if (dmg < 0) {
                dmg = 0;
            }

            // ù ��° Ư�� �ɷ����� ���� �߰� ����
            m_firstAbility.transformDamageReceived(dmg);

            // �� ��° Ư�� �ɷ����� ���� �߰� ����
            m_secondAbility.transformDamageReceived(dmg);

            // �θ� Ŭ������ takeDamage() ȣ���Ͽ� ü�� ������Ʈ
            CharacterTpl<T>::takeDamage(dmg);
        }
    };

}

#endif
