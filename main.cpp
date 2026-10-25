#include <iostream>
#include <string>
#include <vector>
#include "Tokenizator.h"
#include "Parser.h"
#include "NodeParser.h"

using namespace std;

void loadPlugins(const std::string &folderPath);

int main() {
    // загрузка при старте
    loadPlugins("./plugins");
    cout << R"(To finish, enter "close" or "exit")" << endl;

    do {
        cout << "Enter the expression: " << endl;
        string inString; //{"2 * (4 + 16.5) - 4*2* ( 7 + 4 ) * sin(90)"}; -47
        getline(cin, inString);

        if (inString == "exit" || inString == "close")
            break;

        try {
            vector<Token> tokens{Tokenizator::tokenize(inString)};
            Parser parser(tokens);
            auto tree{parser.parse()};
            double result{tree->evaluate()};
            cout << "Result: " << result << endl;
        } catch (const std::domain_error &e) {
            cout << "Math Error: " << e.what() << endl;
        } catch (const std::invalid_argument &e) {
            cout << "Syntax Error: " << e.what() << endl;
        } catch (const std::exception &e) {
            cout << "Error: " << e.what() << endl;
        } catch (...) {
            cout << "ERROR_0: unknown error" << endl;
        }
    } while (true);

    return 0;
}
