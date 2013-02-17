until ./link.sh; do 
 echo " CodeRunner crashed with exit code $?.  Respawning.. " >&2 
 sleep 1 
 done
