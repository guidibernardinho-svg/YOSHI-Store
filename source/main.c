#include <3ds.h>
#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>

#define MAX_APPS 5

const char* names[MAX_APPS] = {
    "ftpd",
    "Anemone",
    "Homebrew App",
    "Outro App",
    "Teste"
};

const char* urls[MAX_APPS] = {
    "https://github.com/mtheall/ftpd/releases/latest/download/ftpd.3dsx",
    "https://github.com/astronautlevel2/Anemone3DS/releases/latest/download/Anemone3DS.3dsx",
    "https://example.com/app.3dsx",
    "https://example.com/app2.3dsx",
    "https://example.com/test.3dsx"
};

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
    return fwrite(ptr, size, nmemb, stream);
}

void download_file(const char* url, const char* path)
{
    CURL *curl = curl_easy_init();
    FILE *fp = fopen(path, "wb");

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);

    curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    fclose(fp);
}

int main()
{
    gfxInitDefault();
    consoleInit(GFX_TOP, NULL);

    int selected = 0;

    while (aptMainLoop())
    {
        hidScanInput();
        u32 kDown = hidKeysDown();

        if (kDown & KEY_START) break;
        if (kDown & KEY_DOWN) selected = (selected + 1) % MAX_APPS;
        if (kDown & KEY_UP) selected = (selected - 1 + MAX_APPS) % MAX_APPS;

        if (kDown & KEY_A)
        {
            printf("Baixando %s...\n", names[selected]);

            char path[128];
            sprintf(path, "sdmc:/3ds/%s/%s.3dsx", names[selected], names[selected]);

            download_file(urls[selected], path);

            printf("Instalado!\n");
        }

        consoleClear();

        printf("Yoshi HB Store\n\n");

        for (int i = 0; i < MAX_APPS; i++)
        {
            if (i == selected)
                printf(" > %s\n", names[i]);
            else
                printf("   %s\n", names[i]);
        }

        printf("\nA = baixar | START = sair");

        gspWaitForVBlank();
    }

    gfxExit();
    return 0;
}
