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
        seneca::Dagger m_weapon; // 무기: Dagger

    public:
        // 생성자
        Rogue(const char* name, int healthMax, int baseAttack, int baseDefense)
            : CharacterTpl<T>(name, healthMax), m_baseDefense(baseDefense), m_baseAttack(baseAttack) {}  // 순서 수정

        // 공격력 반환 함수 (오버라이드)
        int getAttackAmnt() const override {
            return static_cast<int>(m_baseAttack + 2 * static_cast<double>(m_weapon));
        }


        // 방어력 반환 함수 (오버라이드)
        int getDefenseAmnt() const override {
            return m_baseDefense;
        }

        // 캐릭터 복제 함수 (오버라이드)
        Character* clone() const override {
            return new Rogue(*this);
        }

        // 공격 함수 (오버라이드)
        void attack(Character* enemy) override {
            std::cout << this->getName() << " is attacking " << enemy->getName() << "." << std::endl;

            // 첫 번째 특수 능력 사용
            m_firstAbility.useAbility(this);

            // 두 번째 특수 능력 사용
            m_secondAbility.useAbility(this);

            // 기본 공격력 계산
            int dmg = getAttackAmnt();

            // 첫 번째 특수 능력으로 공격력 강화
            m_firstAbility.transformDamageDealt(dmg);

            // 두 번째 특수 능력으로 공격력 강화
            m_secondAbility.transformDamageDealt(dmg);

            std::cout << "    Rogue deals " << dmg << " melee damage!" << std::endl;

            // 적에게 피해 적용
            enemy->takeDamage(dmg);
        }

        // 피해 입기 함수 (오버라이드)
        void takeDamage(int dmg) override {
            std::cout << this->getName() << " is attacked for " << dmg << " damage." << std::endl;
            std::cout << "    Rogue has a defense of " << getDefenseAmnt() << ". Reducing damage received." << std::endl;

            // 방어력으로 피해 감소
            dmg -= getDefenseAmnt();
            if (dmg < 0) {
                dmg = 0;
            }

            // 첫 번째 특수 능력으로 피해 추가 감소
            m_firstAbility.transformDamageReceived(dmg);

            // 두 번째 특수 능력으로 피해 추가 감소
            m_secondAbility.transformDamageReceived(dmg);

            // 부모 클래스의 takeDamage() 호출하여 체력 업데이트
            CharacterTpl<T>::takeDamage(dmg);
        }
    };

}

#endif
