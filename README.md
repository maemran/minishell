                                                            MiniShell

(expander)
 
(lexer/parser)

(executer)


                                                              TASKS
----------------------------------------------------------------------------------------------------------------------------------------------------------------------

                                                                
->> "   "

->> '     '

->> redirection    <   >    <<  >>

->> Pipe

->> environment  variable ---> what the mean of this concept and every seq char or strings after $

->> $?

->> ctrl-C, ctrl- D, ctrl-\

----------------------------------------------------------------------------------------------------------------------------------------------------------------------

                                                            Builtins
◦ (echo)     with option -n

◦  (cd)      with only a  relative   or   absolute path

◦  (pwd)
 
◦ (export)
 
◦  (unset)

◦  (env)
 
◦  (exit)

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ 



						Explaintion about Minishell Functions

#1 readline()
char *readline (const char *prompt);

This function used to take cmds from shell to do some action and save the cmds in *(char *) variable* 
you need to free the value of *(char *) variable* 

#2 add_history()
void add_history(char *s);

This function dont return anything and when the readline return the *(char *) variable*
this fuction added it to the history 

What is the history: history is when you move the Arrows to back and front that display all command you was written

#3  rl_clear_history()
void rl_clear_history(void);

used to clear history

#4 rl_on_new_line()
int rl_on_new_line(void);

rl_on_new_line(); → "Start Fresh"
👉 Think of it as telling the notebook, "Okay, I'm starting a new clean line!"
👉 It resets the input so Readline knows a fresh command is coming.

#5 rl_replace_line()

rl_replace_line("", 0); → "Erase Mistakes"
👉 This is like erasing what you were writing before you got distracted.
👉 It clears the current input, just like wiping off a whiteboard.

#6 rl_redisplay()
int rl_redisplay(void);

rl_redisplay(); → "Redraw the Notebook"
👉 Now that everything is cleared, this function redraws the screen.
👉 It’s like reopening your notebook so you can continue writing smoothly.

So when you enter ^c in readlin and you was write something like this (minishell> jkdsfkj^c)
this function clear the (jkdsfkj)
start the prompt in new line
and refresh the prompt

_____________________________________________________________________________________________________________________________________________________________________________

                                                                     Environment Variable


- Environment variables passed to a process when it starts. It is an array of strings.

- Environment variables store system-wide or user-specific settings, such as PATH, HOME, SHELL, etc.

- They are inherited by child processes unless explicitly modified:
                                  👇
                                  👇
  	How Environment Variables Are Inherited by Child Processes
  
When you run a program in Linux, it is executed as a process. Each process has its own set of environment variables,
and these variables are inherited by child processes unless explicitly modified

👉 What Does "Inherited by Child Processes" Mean?

When a parent process (like your terminal shell) starts a new process (like running a program), it passes its environment variables to the new process. 
The child process gets a copy of the environment variables of the parent.


__________________________________________________________________________________________________________________________________________________________________________________
  
