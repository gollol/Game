#include <mygame.hpp>

namespace sf {

    void MenuInterface::createButtons(){
        float offSet = 2.f * buttonOffSet;

        buttons[MENU_SCREEN].push_back(createButton(offSet, "Start Next Round", START_ROUND_BUTTON));
        buttons[MENU_SCREEN].push_back(createButton(offSet, "Settings", SETTINGS_BUTTON));
        buttons[MENU_SCREEN].push_back(createButton(offSet, "Quit Game", QUIT_BUTTON));

        offSet = 2.f * buttonOffSet;

        buttons[SETTINGS_SCREEN].push_back(createButton(offSet, "Return To Menu", RETURN_TO_MENU_BUTTON));
        buttons[SETTINGS_SCREEN].push_back(createButton(offSet, "Flip Window Mode", WINDOW_MODE_BUTTON));
        buttons[SETTINGS_SCREEN].push_back(createButton(offSet, "Set Max FPS", MAX_FPS_BUTTON));
    }

    Button MenuInterface::createButton(float &offset, const std::string label, ButtonId buttonId){
        RectangleShape buttonBase = createRectangle(buttonWidth, buttonHeight, Vector2f(windowCenter.x, offset), buttonColor, Color::Black);
        Text buttonLabel = createText(label, {0.f, 0.f}, font, Color::White);
        centerText(buttonLabel, buttonBase.getPosition());
        offset += buttonOffSet;
        return Button(buttonBase, buttonLabel, buttonId);
    }
    
    PopUpWindow MenuInterface::popUp(RenderWindow &window, const std::string text) {
        RectangleShape popUpBase = createRectangle(1.25f*buttonWidth, 1.25f*buttonHeight, windowCenter, Color(125,125,200), Color::Black);
        Text popUpLabel = createText(text, {0.f, 0.f}, font, Color::White);
        centerText(popUpLabel, popUpBase.getPosition());
        return PopUpWindow(popUpBase, popUpLabel);
    }

}