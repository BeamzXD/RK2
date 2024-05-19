#include <gtest/gtest.h>
#include "webpage_button.cpp"

TEST(WebPageManagerTest, ChangeWebPage) {
    std::stringstream output;
    std::streambuf* oldCoutBuf = std::cout.rdbuf(output.rdbuf());

    WebPageManager manager;
    std::string url = "https://example.com";
    manager.ChangeWebPage(url);

    std::cout.rdbuf(oldCoutBuf);
    std::string expected = "Change web page to " + url + ".\n";
    EXPECT_EQ(output.str(), expected);
}

TEST(ChangeWebPageCommandTest, Execute) {
    std::stringstream output;
    std::streambuf* oldCoutBuf = std::cout.rdbuf(output.rdbuf());

    WebPageManager manager;
    std::string url = "https://example.com";
    ChangeWebPageCommand command(manager, url);
    command.Execute();

    std::cout.rdbuf(oldCoutBuf);
    std::string expected = "Change web page to " + url + ".\n";
    EXPECT_EQ(output.str(), expected);
}

TEST(ButtonTest, ClickWithChangeWebPageCommand) {
    std::stringstream output;
    std::streambuf* oldCoutBuf = std::cout.rdbuf(output.rdbuf());

    WebPageManager manager;
    std::string url = "https://example.com";
    ChangeWebPageCommand command(manager, url);
    Button button(&command);
    button.Click();

    std::cout.rdbuf(oldCoutBuf);
    std::string expected = "Change web page to " + url + ".\n";
    EXPECT_EQ(output.str(), expected);
}

TEST(ButtonTest, ClickWithGenericCommand) {
    std::stringstream output;
    std::streambuf* oldCoutBuf = std::cout.rdbuf(output.rdbuf());

    auto genericCommand = MakeGenericCommand([]() -> void {
        std::cout << "This is generic command." << std::endl;
    });
    Button button(&genericCommand);
    button.Click();

    std::cout.rdbuf(oldCoutBuf);
    std::string expected = "This is generic command.\n";
    EXPECT_EQ(output.str(), expected);
}

TEST(ButtonTest, ChangeCommand) {
    std::stringstream output;
    std::streambuf* oldCoutBuf = std::cout.rdbuf(output.rdbuf());

    WebPageManager manager;
    std::string url = "https://example.com";
    ChangeWebPageCommand changeCommand(manager, url);
    auto genericCommand = MakeGenericCommand([]() -> void {
        std::cout << "This is generic command." << std::endl;
    });

    Button button(&changeCommand);
    button.Click(); // Выполняет ChangeWebPageCommand

    button.ChangeCommand(&genericCommand);
    button.Click(); // Выполняет GenericCommand

    std::cout.rdbuf(oldCoutBuf);
    std::string expected = "Change web page to " + url + ".\nThis is generic command.\n";
    EXPECT_EQ(output.str(), expected);
}
