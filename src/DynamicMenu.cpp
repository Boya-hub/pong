#include <string>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "DynamicMenu.h"

DynamicMenu::DynamicMenu(unsigned int lenght, unsigned int width, unsigned int fps, std::string name): RenderWindow(VideoMode(lenght, width, fps), name)
{
     m_nbText = 0;
}

unsigned int DynamicMenu::addText(Text text)
{
    if(m_nbText == 4)
        return -1;
    m_texts[m_nbText] = text;
    m_nbText++;
    return 0;
}


DynamicMenu::~DynamicMenu()
{
    //dtor
}
