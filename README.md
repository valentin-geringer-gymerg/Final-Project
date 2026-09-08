# File utils
#### Video Demo:  <URL HERE>
#### Description:
As you can already tell from the name, file utils (File utilities) offers utilities for different types of files. To be specific, these are the file types and file extensions supported:

Text:\
.txt


In general, the format for all commands is `file-utils [command] [options] [flags]`.\
While the commands attempt to differentiate between flags and options, thus allowing you to insert flags between options and vice versa, the code expects you to use the commands the intended way and therefore also works best if you do so.\
Additionally, the options have to be in the correct order as stated in the command template.

To see all available commands, use the `-h` flag and don't specify a command:

Example:

```console
file-utils -h
```
If you want to see a command's functionality and template, specify a command and use the `-h` flag (`file-utils [command] -h`):

Example:

```console
file-utils find-name -h
```
The options first state each option's name, followed by a colon, then whether the option needs to be specified and then the meaning in brackets. If you want to specify an option where specification is not necessary, preceded by an option you don't want to specify, use the according flags.

File utils offers the following commands:

All files:\
`cp-it`\
`find-name`

Text:\
`find-content`
