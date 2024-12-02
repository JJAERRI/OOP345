#ifndef SENECA_CHARACTERTPL_H
#define SENECA_CHARACTERTPL_H
#include "character.h"

namespace seneca
{
    template<typename T>
    class CharacterTpl : public Character
    {
        int m_healthMax;
        T m_health;

    public:
        CharacterTpl(const char* name, int healthMax)
            : Character(name), m_healthMax(healthMax)
        {
            if constexpr (!std::is_same<T, seneca::InfiniteHealth>::value)
            {
                m_health = healthMax;  // InfiniteHealth�� �ƴ� ��쿡�� �ʱ�ȭ
            }
            else
            {
                m_health = 1;  // InfiniteHealth�� ��� 1�� ���� (�ʿ��� ��� �ٸ� ������ ���� ����)
            }
        }

        void takeDamage(int dmg) override
        {
            m_health -= dmg;
            if (static_cast<int>(m_health) <= 0)
            {
                m_health = 0;
                std::cout << "    " << getName() << " has been defeated!" << std::endl;
            }
            else
            {
                std::cout << "    " << getName() << " took " << dmg << " damage, " << static_cast<int>(m_health) << " health remaining." << std::endl;
            }
        }

        int getHealth() const override
        {
            return static_cast<int>(m_health);
        }

        int getHealthMax() const override
        {
            return m_healthMax;
        }

        void setHealth(int health) override
        {
            if constexpr (!std::is_same<T, seneca::InfiniteHealth>::value)
            {
                m_health = health;
            }
        }

        void setHealthMax(int health) override
        {
            m_healthMax = health;
            if constexpr (!std::is_same<T, seneca::InfiniteHealth>::value)
            {
                m_health = health;
            }
        }
    };
}
#endif
