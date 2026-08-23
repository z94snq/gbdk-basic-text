#include <gb/gb.h>
#include <stdint.h>
#include "graphics/Font.h"

uint8_t GetCharacterVRamTile(char character) {
    uint8_t vramTile = 0;

    // Char's can be interpreted as integers
    // We don't need to map every alpha-numeric character
    // We can use basic math to simplify A-Z and 0-9

    if(character >= 'a' && character <= 'z') vramTile = (character - 'a') + 1;
    else if(character >= 'A' && character <= 'Z') vramTile = (character - 'A') + 1;
    else if(character >= '0' && character <= '9') vramTile = (character - '0') + 27;
    else {
        switch(character) {
            case '!': vramTile = 37; break;
            case ':': vramTile = 38; break;
            case '?': vramTile = 39; break;
            case '\\': vramTile = 40; break;
            case '=': vramTile = 41; break;
            case ',': vramTile = 42; break;
            case '.': vramTile = 43; break;
            case '<': vramTile = 44; break;
            case '>': vramTile = 45; break;
        }
    }

    return vramTile;
}

void DrawText(uint8_t column, uint8_t row, char* text){
    // Get the address of the first tile in the row
    uint8_t* vramAddress = get_bkg_xy_addr(column,row);
    uint16_t index=0;

    while(text[index] != '\0'){
        char character = text[index];

        // Draw our character at the address
        // THEN, increment the address
        uint8_t vramTile = GetCharacterVRamTile(character);
        set_vram_byte(vramAddress++,vramTile);

        index++;
    }
}

void DrawTextSound(uint8_t column, uint8_t row, char* text){
    // Get the address of the first tile in the row
    uint8_t* vramAddress = get_bkg_xy_addr(column,row);
    uint16_t index=0;

    while(text[index]!='\0'){
        char character = text[index];

        // Draw our character at the address
        // THEN, increment the address
        uint8_t vramTile = GetCharacterVRamTile(character);
        set_vram_byte(vramAddress++,vramTile);

        index++;
            
        // Play a basic sound effect
        NR10_REG = 0x34;
        NR11_REG = 0x81;
        NR12_REG = 0x41;
        NR13_REG = 0x7F;
        NR14_REG = 0x86;

        // Wait two frames
        // This creats a typewriter effect
        // Increas the amount of 'vsync's to increase the delay per character
        vsync();
        vsync();
        vsync();
        vsync();
        vsync();
    }
}

void main(void)
{
    // This enables Sound
    // these registers must be in this specific order!
    NR52_REG = 0x80; // is 1000 0000 in binary and turns on sound
    NR50_REG = 0x77; // sets the volume for both left and right channel just set to max 0x77
    NR51_REG = 0xFF; // is 1111 1111 in binary, select which chanels we want to use in this case all of them. One bit for the L one bit for the R of all four channels

    SHOW_BKG;

    // Load the font tiles and clear the background
    set_native_tile_data(0, Font_TILE_COUNT, Font_tiles);
    fill_bkg_rect(0, 0, DEVICE_SCREEN_WIDTH, DEVICE_SCREEN_HEIGHT, 0);

    // Draw basic text
    DrawText(1, 1, "ABCDEFGHIJKLMNOPQR");
    DrawText(1, 2, "STUVWXYZ0123456789");
    DrawText(1, 3, "!:?\\=,.<>");

    // Draw text with a typewriter sound effect
    DrawTextSound(1, 5, "GBDK BASIC TEXT");
    DrawTextSound(1, 6, "Z94SNQ");
}
