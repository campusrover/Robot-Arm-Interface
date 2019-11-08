 #!/bin/bash
#Jacob smith COSI 119A 11/7/2019 ASrm Interface
#from https://github.com/jsmith2021Brandeis/COSI-119A-Repo-All-Packages/blob/master/scripts/4.1Script
#I created this set of bash scripts so I don't have to open and close 3 linux terminals manually
# and enter the commands

#create variable for window coordinate
count="0"
#launch roscore in other terminal and wait for it to start up
gnome-terminal --geometry 73x31+$count+0 -- /bin/sh -c 'export ROS_MASTER_URI=http://localhost:11311;roscore'
sleep 2
#loop through every python file in program
for f in *.py; do 
   #increment count by fixed amount so new window starts in new place
    count=`expr "$count" + "200"`
    sleep 1
    #give file permissions and run python file
    gnome-terminal --geometry 73x31+$count+0 -- /bin/sh -c 'export ROS_MASTER_URI=http://localhost:11311;chmod +x '$f';python '$f
done
#close terminal windows after X  seconds
sleep 20
pkill gnome-terminal-