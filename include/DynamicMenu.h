#ifndef DYNAMICMENU_H
#define DYNAMICMENU_H

#define NB_MAX_TEXTS 4

using namespace sf;

class DynamicMenu : public RenderWindow
{
    public:
        DynamicMenu(unsigned int lenght, unsigned int width, unsigned int fps, std::string name);
        unsigned int addText(Text text);
        virtual ~DynamicMenu();

    protected:

    private:
    Text m_texts[NB_MAX_TEXTS];
    unsigned m_nbText;


};

#endif // DYNAMICMENU_H
