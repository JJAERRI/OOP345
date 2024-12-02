#ifndef SENECA_TEAM_H
#define SENECA_TEAM_H

#include "character.h"
#include <string>

namespace seneca {

    class Team {
        std::string m_name;
        Character** m_members;
        size_t m_count;

        // �޸� ���� �Լ�
        void deallocate();
        void copyFrom(const Team& other);
        void moveFrom(Team&& other);

    public:
        // �⺻ ������
        Team();

        // �̸��� �޾� �ʱ�ȭ�ϴ� ������
        Team(const char* name);

        // Rule of 5: �Ҹ���, ���� ������, ���� ���� ������, �̵� ������, �̵� ���� ������
        ~Team();
        Team(const Team& other);
        Team(Team&& other) noexcept;
        Team& operator=(const Team& other);
        Team& operator=(Team&& other) noexcept;

        // ��� �߰�
        void addMember(const Character* c);

        // ��� ����
        void removeMember(const std::string& name);

        // ��� �˻� (�ε����� ����)
        Character* operator[](size_t idx) const;

        // ��� ���
        void showMembers() const;
    };

} // namespace seneca

#endif
