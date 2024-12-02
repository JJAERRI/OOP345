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
        Weapon_t m_weapon[2]; // 두 개의 무기 사용

    public:
        // 생성자
        Barbarian(const char* name, int healthMax, int baseAttack, int baseDefense, Weapon_t primaryWeapon, Weapon_t secondaryWeapon)
            : CharacterTpl<T>(name, healthMax), m_baseDefense(baseDefense), m_baseAttack(baseAttack) {
            m_weapon[0] = primaryWeapon;
            m_weapon[1] = secondaryWeapon;
        }

        // 공격력 반환 함수 (오버라이드)
        int getAttackAmnt() const override {
            return static_cast<int>(m_baseAttack + static_cast<double>(m_weapon[0]) / 2 + static_cast<double>(m_weapon[1]) / 2);
        }


        // 방어력 반환 함수 (오버라이드)
        int getDefenseAmnt() const override {
            return m_baseDefense;
        }

        // 캐릭터 복제 함수 (오버라이드)
        Character* clone() const override {
            return new Barbarian(*this);
        }

        // 공격 함수 (오버라이드)
        void attack(Character* enemy) override {
            std::cout << this->getName() << " is attacking " << enemy->getName() << "." <<std::endl;

            // 특수 능력 사용
            m_ability.useAbility(this);

            // 기본 공격력 계산
            int dmg = getAttackAmnt();

            // 특수 능력으로 강화된 공격력 적용
            m_ability.transformDamageDealt(dmg);

            std::cout << "    Barbarian deals " << dmg << " melee damage!" << std::endl;

            // 적에게 피해 적용
            enemy->takeDamage(dmg);
        }

        // 피해 입기 함수 (오버라이드)
        void takeDamage(int dmg) override {
            std::cout << this->getName() << " is attacked for " << dmg << " damage." << std::endl;
            std::cout << "    Barbarian has a defense of " << m_baseDefense << ". Reducing damage received." << std::endl;

            // 방어력으로 피해 감소
            dmg -= m_baseDefense;
            if (dmg < 0) {
                dmg = 0;
            }

            // 특수 능력으로 피해 추가 감소
            m_ability.transformDamageReceived(dmg);

            // 부모 클래스의 takeDamage() 호출하여 체력 업데이트
            CharacterTpl<T>::takeDamage(dmg);
        }
    };

} // namespace seneca

#endif
