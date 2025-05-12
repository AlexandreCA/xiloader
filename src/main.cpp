/*
===========================================================================

Copyright (c) 2010-2015 Darkstar Dev Teams
Copyright (c) 2021-2022 LandSandBoat Dev Teams
Copyright (c) 2023-2025 Fox_Mulder (adaptation Xbox 360)

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
#include <xui.h>
#include <string>
#include <ctime>

// Définitions nécessaires pour la compatibilité avec network.cpp
namespace xiloader
{
    // Structure pour les sockets de données
    struct datasocket {
        SOCKET s;
        ULONG LocalAddress;
        ULONG ServerAddress;
        UINT32 AccountId;
    };

    // Enum pour les langues
    enum class Language { Japanese, English, European };

    // Espace de noms pour la console
    namespace console {
        enum class color { error, info, warning, success, lightgreen };
        void output(color c, const char* format, ...) {
            // TODO: Implémenter l'affichage via XUI ou journalisation
        }
    }

    // Déclarations des fonctions réseau (définies dans network.cpp)
    namespace network {
        bool CreateAuthConnection(datasocket* sock, const char* port);
        bool VerifyAccount(datasocket* sock);
        DWORD __stdcall FFXiServer(LPVOID lpParam);
        DWORD __stdcall PolServer(LPVOID lpParam);
    }
}

// Variables globales
namespace globals
{
    xiloader::Language g_Language        = xiloader::Language::English; // Langue du client
    std::string        g_ServerAddress   = "38.85.167.68";             // Adresse du serveur
    std::string        g_ServerPort      = "51220";                    // Port du lobby
    std::string        g_LoginDataPort   = "54230";                    // Port de données
    std::string        g_LoginViewPort   = "54001";                    // Port de vue
    std::string        g_LoginAuthPort   = "54231";                    // Port d'authentification
    std::string        g_Username        = "";                         // Nom d'utilisateur
    std::string        g_Password        = "";                         // Mot de passe
    char               g_SessionHash[16] = {};                         // Hash de session
    std::string        g_Email           = "";                         // Email (inutilisé)
    std::string        g_VersionNumber   = "1.1.1";                    // Version du loader
    char*              g_CharacterList   = nullptr;                    // Liste des personnages
    bool               g_IsRunning       = false;                      // État des threads
    bool               g_Hide            = false;                      // Cacher la console (inutilisé sur Xbox 360)
}

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

// Point d'entrée principal
int __cdecl main()
{
    // Initialisation du réseau XNet
    XNetStartupParams xsp = { sizeof(XNetStartupParams) };
    if (XNetStartup(&xsp) != 0)
    {
        xiloader::console::output(xiloader::color::error, "Failed to initialize XNet!");
        return 1;
    }

    // Afficher la bannière
    time_t currentTime = time(NULL);
    int currentYear = localtime(&currentTime)->tm_year + 1900;
    xiloader::console::output(xiloader::color::lightred, "==========================================================");
    xiloader::console::output(xiloader::color::lightgreen, "LandSandBoat Boot Loader (c) 2021-%d LandSandBoat Team (v%s)", currentYear, globals::g_VersionNumber.c_str());
    xiloader::console::output(xiloader::color::lightgreen, "Pour serveur Vanadiel XI seulement (c) 2023-2025 Fox_Mulder");
    xiloader::console::output(xiloader::color::lightgreen, "Traduction francaise (c) 2023-2025 Fox_Mulder");
    xiloader::console::output(xiloader::color::lightred, "==========================================================");

    // Configurer les paramètres (optionnel : utiliser XUI pour saisir dynamiquement)
    if (globals::g_Username.empty() || globals::g_Password.empty())
    {
        xiloader::console::output(xiloader::color::info, "Please enter your login information.");
        globals::g_Username = getUserInput(L"Enter Username", 15);
        globals::g_Password = getUserInput(L"Enter Password", 32);
    }

    // Créer la connexion au serveur
    xiloader::datasocket sock;
    if (!xiloader::network::CreateAuthConnection(&sock, globals::g_LoginAuthPort.c_str()))
    {
        xiloader::console::output(xiloader::color::error, "Failed to connect to server!");
        XNetCleanup();
        return 1;
    }

    // Vérifier les informations du compte
    while (!xiloader::network::VerifyAccount(&sock))
        Sleep(10);

    // Lancer les threads réseau
    globals::g_IsRunning = true;
    HANDLE hFFXiServer = CreateThread(NULL, 0, xiloader::network::FFXiServer, &sock, 0, NULL);
    HANDLE hPolServer = CreateThread(NULL, 0, xiloader::network::PolServer, NULL, 0, NULL);

    // TODO: Lancer Final Fantasy XI
    // Remplacer cette section par le code spécifique à votre client Xbox 360 pour lancer le jeu.
    // Exemple : Appeler une fonction du client pour démarrer FFXI avec les paramètres réseau.
    xiloader::console::output(xiloader::color::info, "Starting Final Fantasy XI...");
    // Placeholder : Ajoutez ici le code pour lancer FFXI (par exemple, via XLaunchTitle).

    // Attendre que le jeu se termine (optionnel)
    Sleep(1000); // Simuler une attente (remplacer par une logique réelle)

    // Nettoyer les threads
    globals::g_IsRunning = false;
    TerminateThread(hFFXiServer, 0);
    TerminateThread(hPolServer, 0);
    WaitForSingleObject(hFFXiServer, 1000);
    WaitForSingleObject(hPolServer, 1000);
    CloseHandle(hFFXiServer);
    CloseHandle(hPolServer);

    // Nettoyer XNet
    XNetCleanup();

    xiloader::console::output(xiloader::color::info, "Closing...");
    Sleep(2000);

    return 0;
}
