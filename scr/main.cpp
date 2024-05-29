#include "webpage_button.cpp"

int main()
{
    WebPageManager webPageManager;
    ChangeWebPageCommand changeWebPageCommand(webPageManager, "http://taeguk.me");

    Button button(&changeWebPageCommand);
    button.Click();

    auto genericCommand = MakeGenericCommand(
        []() -> void
        {
            std::cout << "This is generic command." << std::endl;
        });

    button.ChangeCommand(&genericCommand);
    button.Click();
}