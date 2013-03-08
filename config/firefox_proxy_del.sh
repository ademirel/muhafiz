#!/bin/bash
#version="`firefox -v | awk '{print substr($3,1,3)}'`"
#kill firefox
pgrep firefox && pkill firefox
#find user's default firefox directory
file="`find $HOME/.mozilla/firefox -type f -name prefs.js`"
#change file permission for writing
chmod 777 $file
#if there is not proxy settings in prefs.js add them,
if
! more $file | grep 'network.proxy.http'
  then echo 'user_pref("network.proxy.http", "127.0.0.1");' >> $file
  else sed -i 's/^.*network.proxy.http\".*$/user_pref(\"network.proxy.http\", \"127.0.0.1\");/'  $file
  fi
  # Set the port
  if ! more $file | grep 'network.proxy.http_port'
    then echo 'user_pref("network.proxy.http_port", 8080);' >> $file
      else sed -i 's/^.*network.proxy.http_port.*$/user_pref(\"network.proxy.http_port\", 8080);/' $file
      fi
      
      # Turn on the proxy
      if ! more  $file | grep 'network.proxy.type'
        then echo 'user_pref("network.proxy.type", 1);' >> $file
          else sed -i 's/^.*network.proxy.type.*$/user_pref(\"network.proxy.type\", 0)";/' $file
          fi
#change file permission as default
chmod 644 $file
#firefox &
