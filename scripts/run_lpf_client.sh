EXECUTABLE=/lpf

run_command()
{
    if [[ "$command" == "help" ]]; then
        ${EXECUTABLE} --help
        echo "Script commands:"
        echo "  - user: Change current user"
        echo "  - exit: Exit script"
    elif [[ "$command" == "user" ]]; then
        read -p "Username: " name
        read -sp "Password: " password
    elif [[ "$command" == "exit" ]]; then
        exit 0
    else echo $password | ${EXECUTABLE} ${name}@${LPF_SERVER_ADDR}:${LPF_SERVER_PORT} -${command};
    fi

    return 0
}

read -p "Username: " name
read -sp "Password: " password

echo
read -p "Command: " command

while run_command;
do
    echo
    read -p "Command: " command
done
