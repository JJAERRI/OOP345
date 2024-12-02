#ifndef SENECA_GUILD_H
#define SENECA_GUILD_H

#include <iostream>
#include <string>
#include "character.h"

namespace seneca {
    class Guild {
        std::string m_name;
        Character** m_members;
        size_t m_count;

        void copyFrom(const Guild& src);  // ���� ���� �Լ�
        void moveFrom(Guild&& src) noexcept;  // �̵� ���� �Լ�
        int findMember(const std::string& name);  // ��� ã�� �Լ�

    public:
        Guild();  // �⺻ ������
        Guild(const char* name);  // �̸����� �ʱ�ȭ�ϴ� ������
        Guild(const Guild& src);  // ���� ������
        Guild& operator=(const Guild& src);  // ���� ���� ������
        Guild(Guild&& src) noexcept;  // �̵� ������
        Guild& operator=(Guild&& src) noexcept;  // �̵� ���� ������
        ~Guild();  // �Ҹ���

        void addMember(Character* c);  // ��� �߰�
        void removeMember(const std::string& name);  // ��� ����
        Character* operator[](size_t idx) const;  // ��� ���� ������
        void showMembers() const;  // ��� ���
    };
}

#endif
