/* This is the main file for the `whoosh` interpreter and the part
   that you modify. */

// Lab 5 Shell MANIA :: Written by Tim Dorny u0829896

#include <stdlib.h>
#include <stdio.h>
#include "csapp.h"
#include "ast.h"
#include "fail.h"

static void run_script(script *scr);
static void run_group(script_group *group);
static void run_command(script_command *command, script_var *result);
static void set_var(script_var *var, int new_value);
static void run_or_commands(script_group *group, script_var *result);
static void run_and_commands(script_group *group, script_var *result);

/* You probably shouldn't change main at all. */

int main(int argc, char **argv) {
  script *scr;

  if ((argc != 1) && (argc != 2)) {
    fprintf(stderr, "usage: %s [<script-file>]\n", argv[0]);
    exit(1);
  }

  scr = parse_script_file((argc > 1) ? argv[1] : NULL);

  run_script(scr);

  return 0;
}

static void run_script(script *scr) {
  if (scr->num_groups == 1) {
    run_group(&scr->groups[0]);
  } else {
    // Simple for loop to run all groups.
    int i;
    for (i = 0; i < scr->num_groups; i++){
      run_group(&scr->groups[i]);
    }
  }
}

static void run_group(script_group *group) {
  // Used to hold a pointer to a variable that will recieve the exit status from group
  script_var *result = NULL;
  // Handle repititions
  int repetitions = 1;
  int i;
  if (group->repeats != 1){
    // Set # of repetitions if applicable
    repetitions = group->repeats;
  }
  if (group->result_to != NULL){
    // Set result to the pointer to the variable to store the result to
    result = group->result_to;
  }
  // Single Commands
  if (group->num_commands == 1) {
    // Loop for repetitions
    for (i = 0; i < repetitions; i++){
      run_command(&group->commands[0], result);
    }
  } else {
    // Or Command groups
    if (group->mode == 2){
      for (i = 0; i < repetitions; i++){
        run_or_commands(group, result);
      }
    }
    // And command groups
    if (group->mode == 1){
      for (i = 0; i < repetitions; i++){
        run_and_commands(group, result);
      }
    }
  }
}

/* This run_command function is a good start, but note that it runs
   the command as a replacement for the `whoosh` script, instead of
   creating a new process. */

static void run_command(script_command *command, script_var *result) {
  const char **argv;
  int i;
  pid_t pid;

  // Setup arguments
  argv = malloc(sizeof(char *) * (command->num_arguments + 2));
  argv[0] = command->program;

  for (i = 0; i < command->num_arguments; i++) {
    if (command->arguments[i].kind == ARGUMENT_LITERAL)
      argv[i+1] = command->arguments[i].u.literal;
    else{
      argv[i+1] = command->arguments[i].u.var->value;
    }
  }

  argv[command->num_arguments + 1] = NULL;
  // Fork process to run desired program
  pid = Fork();
  // If given an @ variable, store the child process's id into that variable
  if (command->pid_to != NULL){
    set_var(command->pid_to, pid);
  }
  // Child process
  if (pid == 0){
    // protect from kill 0
    setpgid(0, 0);
    Execve(argv[0], (char * const *)argv, environ);
  }
  // Parent
  else{
    // protect from kill 0
    setpgid(pid, pid);
    // store result of Wait[pid]()
    int child_status;
    Wait(&child_status);
    // If output of process was signaled to be put into variable, do so.
    if (result != NULL){
      // If terminated by signal, return corresponding value
      if (WIFSIGNALED(child_status)){
        set_var(result, -WTERMSIG(child_status));
      }
      // Else return exit status
      else{
        set_var(result, WEXITSTATUS(child_status));
      }
    }
    free(argv);
  }
}

static void run_or_commands(script_group *group, script_var *result){
  const char **argv = NULL;
  pid_t pid = 0;
  int x;
  int i;
  // Number of commands
  int NOC = group->num_commands;
  int pids[NOC];
  script_command *command = NULL;
  // Fork for each command in group.
  for (x = 0; x < group->num_commands; x++){
    // Setup command
    command = &group->commands[x];
    // Fork new process
    pid = Fork();
    // Store child's pid into pids[]
    pids[x] = pid;
    // If given an @ variable, store the child process's id into that variable
    if (command->pid_to != NULL && pid != 0){
      set_var(command->pid_to, pid);
    }
    if (pid == 0){
      setpgid(0, 0);
      break;
    }
  }
  // Children processes
  if (pid == 0){
    // Setup arguments
    argv = malloc(sizeof(char *) * (command->num_arguments + 2));
    argv[0] = command->program;

    for (i = 0; i < command->num_arguments; i++) {
      if (command->arguments[i].kind == ARGUMENT_LITERAL)
        argv[i+1] = command->arguments[i].u.literal;
      else{
        argv[i+1] = command->arguments[i].u.var->value;
      }
    }

    argv[command->num_arguments + 1] = NULL;
    // Execute command
    Execve(argv[0], (char * const *)argv, environ);
  }
  // Parent process
  else{
    setpgid(pid, pid);
    int child_status;
    Waitpid(-1, &child_status, 0);
    // If output of process was signaled to be put into variable, do so.
    if (result != NULL){
      if (WIFSIGNALED(child_status)){
        set_var(result, -WTERMSIG(child_status));
      }
      else{
        set_var(result, WEXITSTATUS(child_status));
      }
    }
    free(argv);
    // Once a child process resolves, kill remaining processes
    int j;
    for (j = 0; j < NOC; j++){
      kill(pids[j], SIGTERM);
    }
  }
}

static void run_and_commands(script_group *group, script_var *result){
  const char **argv = NULL;
  pid_t pid = 0;
  int i;
  int j;
  // # of commands
  int NOC = group->num_commands;
  // # of pipes
  int NOP = NOC - 1;
  int pipes[2 * NOP];
  // Setup Pipes
  for (i = 0; i < group->num_commands; i++){
    Pipe(pipes + i*2);
  }

  // Run commands via fork
  for (i = 0; i < NOC; i++){
    script_command *command = &group->commands[i];

    pid = Fork();
    // If given an @ variable, store the child process's id into that variable
    if (command->pid_to != NULL){
      set_var(command->pid_to, pid);
    }
    if (pid == 0){
      setpgid(0, 0);
      // When not last command
      if (i < NOC - 1){
        Dup2(pipes[i*2 + 1], 1);
      }
      // When not first command
      if (i != 0){
        Dup2(pipes[i*2 - 2], 0);
      }
      // Close pipes
      for (j = 0; j < 2 * NOP; j++){
        Close(pipes[j]);
      }

      // EXECUTE COMMAND
      argv = malloc(sizeof(char *) * (command->num_arguments + 2));
      argv[0] = command->program;

      for (i = 0; i < command->num_arguments; i++) {
        if (command->arguments[i].kind == ARGUMENT_LITERAL)
          argv[i+1] = command->arguments[i].u.literal;
        else{
          argv[i+1] = command->arguments[i].u.var->value;
        }
      }

      argv[command->num_arguments + 1] = NULL;

      Execve(argv[0], (char * const *)argv, environ);
    }
  }
  // Parent Process
  for (j = 0; j < 2*NOP; j++){
    Close(pipes[j]);
  }
  setpgid(pid, pid);
  int child_status;
  // Once a child process resolves, kill remaining processes
  Waitpid(pid, &child_status, 0);
  // If output of process was signaled to be put into variable, do so.
  if (result != NULL){
    if (WIFEXITED(child_status)){
      set_var(result, -WTERMSIG(child_status));
    }
    else{
      set_var(result, WEXITSTATUS(child_status));
    }
  }
  free(argv);
}


/* You'll likely want to use this set_var function for converting a
   numeric value to a string and installing it as a variable's
   value: */

static void set_var(script_var *var, int new_value) {
  char buffer[32];
  free((void *)var->value);
  snprintf(buffer, sizeof(buffer), "%d", new_value);
  var->value = strdup(buffer);
}
