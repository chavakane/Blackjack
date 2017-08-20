typedef void (*callback_function)(void); 
struct Command{
    string CommandName;
    callback_function Action;
};
vector<Command> globalCommands;

void toLower(basic_string<char>& s) {
    for (basic_string<char>::iterator p = s.begin();
         p != s.end(); ++p) {
       *p = tolower(*p);
    }
 }

 void questionDialog(string question, vector<Command> &commands) {
    cout << question << endl;
    string choice;    
    getline(cin,choice);
    toLower(choice);

    for (vector<Command>::iterator it = commands.begin() ; it != commands.end(); ++it){
        if((*it).CommandName== choice){
            (*it).Action();
            return;
        }
    }
    
    //process static commands
    for (vector<Command>::iterator it = globalCommands.begin() ; it != globalCommands.end(); ++it){
        if((*it).CommandName== choice){
            (*it).Action();
            questionDialog(question, commands);
            return;
        }
    }
    cout << "Sorry, you typed an invalid answer/command.\nLet me repeat the question...\n" << endl;
    questionDialog(question, commands);
}