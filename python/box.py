import socket;
import sys;
import re;

def connect(ip, port):
    status= True
    print "Connecting..."

    try:
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    except:
        status = False
        print "Couldn't open socket"

    try:
        s.connect((ip, int(port)));
    except socket.error, msg:
        status = False
        print "Invalid host or port"

    if not status:
        return

    print "Connected to", ip, "at port", port
    read_input(s)
    return True


def read_input(s):
    while True:
        cmd = raw_input('box> ')
        if cmd == "quit":
            s.close()
            break;
        else:
            s.send(cmd + '\r\n')


def get_args():
    argv = sys.argv
    if len(argv) <= 2:
        print "usage: ", argv[0], "<IP> <PORT>"
        return False
    else:
        if validate_args(argv[1], "ip") and validate_args(argv[2], "port"):
            return [argv[1], argv[2]]
        else:
            return False


def validate_args(value, kind):
    ipValid     = False
    portValid   = False

    if kind == "ip":
        ipValid = not not re.match('^\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3}$', value)
        return ipValid
    if kind == "port":
        portValid = not not re.match('^\d{1,5}$', value)
        return portValid
    else:
        return False

    return True
        

def init():
    args = get_args()
    if args:
        connect(args[0], args[1])

init()
