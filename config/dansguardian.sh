#!/bin/bash

gksu chmod 777 /etc/dansguardian/dansguardian.conf

if ! more /etc/dansguardian/dansguardian.conf | grep '/etc/dansguardian/lists/bannediplist'
then echo 'bannediplist=/etc/dansguardian/lists/bannediplist' >> /etc/dansguardian/dansguardian.conf
  fi

if ! more /etc/dansguardian/dansguardian.conf | grep '/etc/dansguardian/lists/bannedextensionlist'
then echo 'bannedextensionlist=/etc/dansguardian/lists/bannedextensionlist' >> /etc/dansguardian/dansguardian.conf 
  fi

if ! more /etc/dansguardian/dansguardian.conf | grep '/etc/dansguardian/lists/bannedmimetypelist'
then echo 'bannedmimetypelist=/etc/dansguardian/lists/bannedmimetypelist' >> /etc/dansguardian/dansguardian.conf 
  fi

if ! more /etc/dansguardian/dansguardian.conf | grep '/etc/dansguardian/lists/bannedregexpurllist'
then echo 'bannedregexpurllist=/etc/dansguardian/lists/bannedregexpurllist' >> /etc/dansguardian/dansguardian.conf 
  fi

if ! more /etc/dansguardian/dansguardian.conf | grep '/etc/dansguardian/lists/bannedsitelist'
then echo 'bannedsitelist=/etc/dansguardian/lists/bannedsitelist' >> /etc/dansguardian/dansguardian.conf 
  fi

if ! more /etc/dansguardian/dansguardian.conf | grep '/etc/dansguardian/lists/exceptionregexpurllist'
then echo 'exceptionregexpurllist=/etc/dansguardian/lists/exceptionregexpurllist' >> /etc/dansguardian/dansguardian.conf 
  fi

if ! more /etc/dansguardian/dansguardian.conf | grep '/etc/dansguardian/lists/exceptionsitelist'
then echo 'exceptionsitelist=/etc/dansguardian/lists/exceptionsitelist' >> /etc/dansguardian/dansguardian.conf 
  fi

if ! more /etc/dansguardian/dansguardian.conf | grep '/etc/dansguardian/lists/exceptionurllist'
then echo 'exceptionurllist=/etc/dansguardian/lists/exceptionurllist' >> /etc/dansguardian/dansguardian.conf 
  fi

if ! more /etc/dansguardian/dansguardian.conf | grep '/etc/dansguardian/lists/exceptioniplist'
then echo 'exceptioniplist=/etc/dansguardian/lists/exceptioniplist' >> /etc/dansguardian/dansguardian.conf 
  fi

gksu chmod 644 /etc/dansguardian/dansguardian.conf


