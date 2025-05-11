/*
===========================================================================

Copyright (c) 2010-2014 Darkstar Dev Teams

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see http://www.gnu.org/licenses/

This file is part of DarkStar-server source code, adapted for Xbox 360.

===========================================================================
*/

#include <xtl.h>
#include <xnet.h>
#include <xui.h>
#include <string>
#include <vector>

namespace xiloader
{
    // Structure pour les sockets de données
    struct datasocket {
        SOCKET s;
        ULONG LocalAddress;
        ULONG ServerAddress;
        UINT32 AccountId;
    };

    // Espace de noms pour la console (sortie des messages)
    namespace console {
        enum class color { error, info, warning, success, lightgreen };
        void output(color c, const char* format, ...) {
            // TODO: Implémenter l'affichage via XUI ou journalisation
            // Pour le moment, placeholder vide
        }
    }

    // Espace de noms pour les variables globales
    namespace globals {
        std::string g_ServerAddress = "192.168.50.133"; // Remplacer par l'adresse réelle du serveur
        std::string g_Username;
        std::string g_Password;
        char g_SessionHash[16] = { 0 };
        std::string g_Email;
        std::string g_VersionNumber = "1.0";
        std::string g_ServerPort = "54230";
        std::string g_LoginDataPort = "54231";
        std::string g_LoginViewPort = "54001";
        std::string g_LoginAuthPort = "54230";
        char* g_CharacterList = nullptr;
        bool g_IsRunning = true;
    }

    // Fonction utilitaire pour accéder aux données dans un buffer
    template<typename T> T ref(unsigned char* buffer, int offset) {
        return *(T*)(buffer + offset);
    }

    // Espace de noms pour les fonctions réseau
    namespace network
    {
        // Fonction pour saisir les entrées utilisateur via XShowKeyboardUI
        std::string getUserInput(const wchar_t* prompt, int maxLength)
        {
            XOVERLAPPED overlapped = { 0 };
            WCHAR buffer[256] = { 0 };
            HRESULT hr = XShowKeyboardUI(0, VKBD_DEFAULT, L"", prompt, L"", buffer, maxLength, &overlapped);
            if (FAILED(hr)) return "";
            while (!XHasOverlappedIoCompleted(&overlapped)) Sleep(10);
            char result[256];
            wcstombs(result, buffer, maxLength);
            return std::string(result);
        }

        bool CreateConnection(datasocket* sock, const char* port)
        {
            XNetStartupParams xsp = { sizeof(XNetStartupParams) };
            XNetStartup(&xsp);

            XNADDR xnaddr;
            if (XNetDnsLookup(globals::g_ServerAddress.c_str(), NULL, &xnaddr) != 0)
            {
                xiloader::console::output(xiloader::color::error, "Failed to resolve server address.");
                XNetCleanup();
                return false;
            }

            sock->s = XNetCreateSocket(XNET_SOCK_STREAM, XNET_PROTO_TCP, 0);
            if (sock->s == INVALID_SOCKET)
            {
                xiloader::console::output(xiloader::color::error, "Failed to create socket.");
                XNetCleanup();
                return false;
            }

            XNetConnectParams xcp = { 0 };
            xcp.xnaddr = xnaddr;
            xcp.port = atoi(port);
            if (XNetConnect(sock->s, &xcp) != 0)
            {
                xiloader::console::output(xiloader::color::error, "Failed to connect to server!");
                XNetCloseSocket(sock->s);
                sock->s = INVALID_SOCKET;
                XNetCleanup();
                return false;
            }

            xiloader::console::output(xiloader::color::info, "Connected to server!");
            sock->ServerAddress = xnaddr.ina.s_addr;
            sock->LocalAddress = XNetGetLocalAddr().ina.s_addr;

            XNetCleanup();
            return true;
        }

        bool CreateAuthConnection(datasocket* sock, const char* port)
        {
            return CreateConnection(sock, port); // Pas de TLS
        }

        bool CreateListenServer(SOCKET* sock, int protocol, const char* port)
        {
            XNetStartupParams xsp = { sizeof(XNetStartupParams) };
            XNetStartup(&xsp);

            *sock = XNetCreateSocket(protocol == IPPROTO_UDP ? XNET_SOCK_DGRAM : XNET_SOCK_STREAM, protocol, 0);
            if (*sock == INVALID_SOCKET)
            {
                xiloader::console::output(xiloader::color::error, "Failed to create listening socket.");
                XNetCleanup();
                return false;
            }

            XNADDR xnaddr = XNetGetLocalAddr();
            struct sockaddr_in addr;
            addr.sin_family = AF_INET;
            addr.sin_addr.s_addr = xnaddr.ina.s_addr;
            addr.sin_port = htons(atoi(port));

            if (XNetBind(*sock, (struct sockaddr*)&addr, sizeof(addr)) != 0)
            {
                xiloader::console::output(xiloader::color::error, "Failed to bind to listening socket.");
                XNetCloseSocket(*sock);
                *sock = INVALID_SOCKET;
                XNetCleanup();
                return false;
            }

            if (protocol == IPPROTO_TCP)
            {
                if (XNetListen(*sock, SOMAXCONN) != 0)
                {
                    xiloader::console::output(xiloader::color::error, "Failed to listen for connections.");
                    XNetCloseSocket(*sock);
                    *sock = INVALID_SOCKET;
                    XNetCleanup();
                    return false;
                }
            }

            XNetCleanup();
            return true;
        }

        bool ResolveHostname(const char* host, PULONG lpOutput)
        {
            XNADDR xnaddr;
            if (XNetDnsLookup(host, NULL, &xnaddr) != 0)
                return false;

            *lpOutput = xnaddr.ina.s_addr;
            return true;
        }

        bool VerifyAccount(datasocket* sock)
        {
            static bool bFirstLogin = true;
            unsigned char recvBuffer[1024] = { 0 };
            unsigned char sendBuffer[1024] = { 0 };
            std::string new_password = "";

            bool bUseAutoLogin = !globals::g_Username.empty() && !globals::g_Password.empty() && bFirstLogin;
            if (bUseAutoLogin)
            {
                xiloader::console::output(xiloader::color::lightgreen, "Autologin activated!");
                sendBuffer[0x39] = 0x10;
                bFirstLogin = false;
            }
            else
            {
                // Menu simplifié : seulement login pour cet exemple
                xiloader::console::output(xiloader::color::info, "Please enter your login information.");
                globals::g_Username = getUserInput(L"Enter Username", 15);
                globals::g_Password = getUserInput(L"Enter Password", 32);
                sendBuffer[0x39] = 0x10; // Login uniquement
            }

            sendBuffer[0] = 0xFF;
            sendBuffer[1] = 0x00; // Feature flags
            sendBuffer[2] = 0x00;
            sendBuffer[3] = 0x00;
            sendBuffer[4] = 0x00;
            sendBuffer[5] = 0x00;
            sendBuffer[6] = 0x00;
            sendBuffer[7] = 0x00;
            sendBuffer[8] = 0x00;

            memcpy(sendBuffer + 0x09, globals::g_Username.c_str(), globals::g_Username.length());
            memcpy(sendBuffer + 0x19, globals::g_Password.c_str(), globals::g_Password.length());
            memcpy(sendBuffer + 0x40, new_password.c_str(), 32);
            memcpy(sendBuffer + 0x61, globals::g_VersionNumber.c_str(), 5);

            if (XNetSend(sock->s, (char*)sendBuffer, 102, 0, NULL, NULL) == SOCKET_ERROR)
            {
                xiloader::console::output(xiloader::color::error, "Failed to send login data.");
                XNetCloseSocket(sock->s);
                sock->s = INVALID_SOCKET;
                return false;
            }

            int received = XNetRecv(sock->s, (char*)recvBuffer, 21, 0, NULL, NULL);
            if (received <= 0)
            {
                xiloader::console::output(xiloader::color::error, "Failed to receive login response.");
                XNetCloseSocket(sock->s);
                sock->s = INVALID_SOCKET;
                return false;
            }

            switch (recvBuffer[0])
            {
                case 0x0001: // Success (Login)
                    xiloader::console::output(xiloader::color::success, "Successfully logged in as %s!", globals::g_Username.c_str());
                    sock->AccountId = ref<UINT32>(recvBuffer, 1);
                    std::memcpy(&globals::g_SessionHash, recvBuffer + 5, sizeof(globals::g_SessionHash));
                    XNetCloseSocket(sock->s);
                    sock->s = INVALID_SOCKET;
                    return true;
                case 0x0002: // Error (Login)
                    xiloader::console::output(xiloader::color::error, "Failed to login. Invalid username or password.");
                    XNetCloseSocket(sock->s);
                    sock->s = INVALID_SOCKET;
                    return false;
                case 0x000A: // Account already logged in
                    xiloader::console::output(xiloader::color::error, "Failed to login. Account already logged in.");
                    XNetCloseSocket(sock->s);
                    sock->s = INVALID_SOCKET;
                    return false;
                case 0x000B: // Version mismatch
                    xiloader::console::output(xiloader::color::error, "Failed to login. Version mismatch.");
                    XNetCloseSocket(sock->s);
                    sock->s = INVALID_SOCKET;
                    return false;
                default:
                    xiloader::console::output(xiloader::color::error, "Unknown login response.");
                    XNetCloseSocket(sock->s);
                    sock->s = INVALID_SOCKET;
                    return false;
            }
        }

        DWORD __stdcall FFXiDataComm(LPVOID lpParam)
        {
            auto sock = (xiloader::datasocket*)lpParam;
            int sendSize = 0;
            char recvBuffer[2048] = { 0 }; // Réduit pour Xbox 360
            char sendBuffer[2048] = { 0 };
            struct sockaddr_in client;
            unsigned int socksize = sizeof(client);

            sendBuffer[0] = 0xFE;
            memcpy(sendBuffer + 12, globals::g_SessionHash, 16);

            if (XNetSend(sock->s, sendBuffer, 28, 0, (struct sockaddr*)&client, socksize) == SOCKET_ERROR)
            {
                XNetCloseSocket(sock->s);
                sock->s = INVALID_SOCKET;
                xiloader::console::output(xiloader::color::error, "Failed to send session hash; disconnecting!");
                return 0;
            }
            memset(sendBuffer, 0, 28);

            while (globals::g_IsRunning)
            {
                int received = XNetRecv(sock->s, recvBuffer, sizeof(recvBuffer), 0, (struct sockaddr*)&client, &socksize);
                if (received <= 0)
                {
                    Sleep(100);
                    continue;
                }

                switch (recvBuffer[0])
                {
                case 0x0001:
                    sendBuffer[0] = 0xA1u;
                    memcpy(sendBuffer + 0x01, &sock->AccountId, 4);
                    memcpy(sendBuffer + 0x05, &sock->ServerAddress, 4);
                    memcpy(sendBuffer + 12, globals::g_SessionHash, 16);
                    xiloader::console::output(xiloader::color::warning, "Sending account id..");
                    sendSize = 28;
                    break;
                case 0x0002:
                case 0x0015:
                    memcpy(sendBuffer, (char*)"\xA2\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x58\xE0\x5D\xAD\x00\x00\x00\x00", 25);
                    xiloader::console::output(xiloader::color::warning, "Sending key..");
                    sendSize = 28;
                    break;
                case 0x0003:
                    xiloader::console::output(xiloader::color::warning, "Receiving character list..");
                    for (auto x = 0; x < recvBuffer[1]; x++)
                    {
                        globals::g_CharacterList[0x00 + (x * 0x68)] = 1;
                        globals::g_CharacterList[0x02 + (x * 0x68)] = 1;
                        globals::g_CharacterList[0x10 + (x * 0x68)] = (char)x;
                        globals::g_CharacterList[0x11 + (x * 0x68)] = 0x80u;
                        globals::g_CharacterList[0x18 + (x * 0x68)] = 0x20;
                        globals::g_CharacterList[0x28 + (x * 0x68)] = 0x20;
                        memcpy(globals::g_CharacterList + 0x04 + (x * 0x68), recvBuffer + 0x10 * (x + 1) + 0x04, 4);
                        memcpy(globals::g_CharacterList + 0x08 + (x * 0x68), recvBuffer + 0x10 * (x + 1), 4);
                    }
                    sendSize = 0;
                    break;
                }

                if (sendSize == 0)
                    continue;

                if (XNetSend(sock->s, sendBuffer, sendSize, 0, (struct sockaddr*)&client, socksize) == SOCKET_ERROR)
                {
                    XNetCloseSocket(sock->s);
                    sock->s = INVALID_SOCKET;
                    xiloader::console::output(xiloader::color::error, "Server connection done; disconnecting!");
                    return 0;
                }

                sendSize = 0;
                Sleep(100);
            }

            return 0;
        }

        DWORD __stdcall PolDataComm(LPVOID lpParam)
        {
            SOCKET client = *(SOCKET*)lpParam;
            unsigned char recvBuffer[1024] = { 0 };
            int result = 0, x = 0;
            time_t t = 0;
            bool bIsNewChar = false;

            do
            {
                result = XNetRecv(client, (char*)recvBuffer, sizeof(recvBuffer), 0, NULL, NULL);
                if (result <= 0)
                {
                    xiloader::console::output(xiloader::color::error, "Client recv failed.");
                    break;
                }

                char temp = recvBuffer[0x04];
                memset(recvBuffer, 0x00, 32);

                switch (x)
                {
                case 0:
                    recvBuffer[0] = 0x81;
                    t = time(NULL);
                    memcpy(recvBuffer + 0x14, &t, 4);
                    result = 24;
                    break;
                case 1:
                    if (temp != 0x28)
                        bIsNewChar = true;
                    recvBuffer[0x00] = 0x28;
                    recvBuffer[0x04] = 0x20;
                    recvBuffer[0x08] = 0x01;
                    recvBuffer[0x0B] = 0x7F;
                    result = bIsNewChar ? 144 : 24;
                    if (bIsNewChar) bIsNewChar = false;
                    break;
                }

                if (XNetSend(client, (char*)recvBuffer, result, 0, NULL, NULL) == SOCKET_ERROR)
                {
                    xiloader::console::output(xiloader::color::error, "Client send failed.");
                    break;
                }

                x++;
                if (x == 3)
                    break;
            } while (result > 0);

            if (XNetShutdown(client, SD_SEND) == SOCKET_ERROR)
                xiloader::console::output(xiloader::color::error, "Client shutdown failed.");
            XNetCloseSocket(client);

            return 0;
        }

        DWORD __stdcall FFXiServer(LPVOID lpParam)
        {
            if (!xiloader::network::CreateConnection((xiloader::datasocket*)lpParam, globals::g_LoginDataPort.c_str()))
                return 1;

            CreateThread(NULL, 0, xiloader::network::FFXiDataComm, lpParam, 0, NULL);
            Sleep(200);

            return 0;
        }

        DWORD __stdcall PolServer(LPVOID lpParam)
        {
            UNREFERENCED_PARAMETER(lpParam);

            SOCKET sock, client;

            if (!xiloader::network::CreateListenServer(&sock, IPPROTO_TCP, globals::g_ServerPort.c_str()))
                return 1;

            while (globals::g_IsRunning)
            {
                if ((client = XNetAccept(sock, NULL, NULL)) == INVALID_SOCKET)
                {
                    xiloader::console::output(xiloader::color::error, "Accept failed.");
                    XNetCloseSocket(sock);
                    return 1;
                }

                CreateThread(NULL, 0, xiloader::network::PolDataComm, &client, 0, NULL);
            }

            XNetCloseSocket(sock);
            return 0;
        }
    }; // namespace network
}; // namespace xiloader
