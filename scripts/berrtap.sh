#! /bin/sh


# Carry out specific functions when asked to by the system
case "$1" in
  start)
    echo "Starting beer tap"
    # run application you want to start
    screen -d -m python /home/support/beer-tap/scripts/raspberry/server.py
    ;;
  stop)
    echo "Stopping beer tap"
    # kill application you want to stop
    pkill -f /home/support/beer-tap/scripts/raspberry/server.py
    ;;
  *)
    echo "Usage: /etc/init.d/beertap {start|stop}"
    exit 1
    ;;
esac

exit 0