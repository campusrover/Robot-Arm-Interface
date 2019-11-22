 #!/bin/bash
#Jacob smith COSI 119A 11/7/2019 ASrm Interface
#run publisher node with a delay so robot can start up
gnome-terminal -e 'sh -c "echo \"This Window will publish commands, please look at main window for now\";sleep 40;cd ~/catkin_ws/src/arminterface/scripts;python topic_publisher.py"'
#start robot and run subscriber node
ssh mutant@mutant.dyn.brandeis.edu 'bash' < '/home/robot/catkin_ws/src/arminterface/scripts/mutantStartup.sh'
