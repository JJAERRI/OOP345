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
        Weapon_t m_weapon; // 무기 객체 (그러나 실제로 사용되지 않음)

    public:
        // 생성자
        Archer(const char* name, int healthMax, int baseAttack, int baseDefense, Weapon_t weapon)
            : CharacterTpl<seneca::SuperHealth>(name, healthMax), m_baseDefense(baseDefense), m_baseAttack(baseAttack), m_weapon(weapon) {}  // 순서 수정


        // 공격력 반환 함수 (오버라이드)
        int getAttackAmnt() const override {
            return static_cast<int>(1.3 * m_baseAttack); // 공격력은 무시하고 baseAttack만 계산
        }

        // 방어력 반환 함수 (오버라이드)
        int getDefenseAmnt() const override {
            return static_cast<int>(1.2 * m_baseDefense); // 방어력은 baseDefense만 계산
        }

        // 캐릭터 복제 함수 (오버라이드)
        Character* clone() const override {
            return new Archer(*this);
        }

        // 공격 함수 (오버라이드)
        void attack(Character* enemy) override {
            std::cout << this->getName() << " is attacking " << enemy->getName() << "." << std::endl;

            // 기본 공격력 계산
            int dmg = getAttackAmnt();

            std::cout << "    Archer deals " << dmg << " ranged damage!\n";

            // 적에게 피해 적용
            enemy->takeDamage(dmg);
        }

        // 피해 입기 함수 (오버라이드)
        void takeDamage(int dmg) override {
            std::cout << this->getName() << " is attacked for " << dmg << " damage." << std::endl;
            std::cout << "    Archer has a defense of " << getDefenseAmnt() << ". Reducing damage received." << std::endl;

            // 방어력으로 피해 감소
            dmg -= getDefenseAmnt();
            if (dmg < 0) {
                dmg = 0;
            }

            // 부모 클래스의 takeDamage() 호출하여 체력 업데이트
            CharacterTpl<seneca::SuperHealth>::takeDamage(dmg);
        }
    };

}

#endif
