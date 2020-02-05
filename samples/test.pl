#!/usr/bin/perl

sub testfunc
{
 open(FF,">ff");
 $aaa="TeSt!\n";
 print FF $aaa;
 print FF time ;
 close FF;
}

sub testfunc222
{
 open(FF,">>gg");
# print FF "\$ConfigFile: $ConfigFile\n";
# print FF "\$LogFile   : $LogFile\n";
# print FF "\$SysopName : $SysopName\n";
# print FF "\$TrafficLog: $TrafficLog\n";
# print FF "\$Version   : $Version\n";

print FF <<END;
\$FMSG{"FromName"}	: $FMSG{"FromName"}
\$FMSG{"FromAddr"}	: $FMSG{"FromAddr"}
\$FMSG{"InetFromAddr"}	: $FMSG{"InetFromAddr"}
\$FMSG{"ToName"}	: $FMSG{"ToName"}
\$FMSG{"ToAddr"}	: $FMSG{"ToAddr"}
\$FMSG{"InetToAddr"}	: $FMSG{"InetToAddr"}
\$FMSG{"Subject"}	: $FMSG{"Subject"}
\$FMSG{"Date"}		: $FMSG{"Date"}
\$FMSG{"Age"}		: $FMSG{"Age"}
\$FMSG{"Attr"}		: $FMSG{"Attr"}
\$FMSG{"Lines"}		: $FMSG{"Lines"}
\$FMSG{"Cost"}		: $FMSG{"Cost"}
\$FMSG{"TimesRead"}	: $FMSG{"TimesRead"}
\$FMSG{"ReplyTo"}	: $FMSG{"ReplyTo"}
\$FMSG{"NextReply"}	: $FMSG{"NextReply"}
\$FMSG{"AreaName"}	: $FMSG{"AreaName"}
END

 my $tmp=$FMSG{"Body"};
  $tmp=~s/\xd/\n/g;
 print FF $tmp;
 
 print FF "\n";
 
 for $kludge (keys %FKludges)
 {
  for $kl (@{$FKludges{$kludge}})
  {
   print FF "Kludge \"$kludge\"=\"$kl\"\n";  
  }

 }
 
 print FF "\n\n";
 
 close FF;
 #Update();
 #ExistsInNodelist();
 Log("Msg 666\n");
}

sub testfunc13
{
 my $subj;
 $subj=$FMSG{"Subject"};
 $faddr=$FMSG{"FromAddr"};
 Log("subj before=$subj");
 Log("from before=$faddr");
 $FMSG{"Subject"}="SaTaN WAS HERE!";
 $FMSG{"FromAddr"}="57:812/11.9";
 Log("start update");
 $rc=Update();
 $subj=$FMSG{"Subject"};
 $faddr=$FMSG{"FromAddr"};
 Log("subj after=$subj");
 Log("faddr after=$faddr");
 Log("end update"); 
 return $rc;
}

sub sbefore
{
 Log("Hello from sbefore()!");
 return 1;
}

sub safter
{
 Log("Hello from safter()!");
 return 1;
}


sub smask
{
# if ($FMSG{"Body"} =~ /spam/i)
# {
#  Log("SPAM detected!");
#  return 1;
# }
 open(TTT,">testf.txt");
 print TTT $FMSG{Body};
 close(TTT);
 return 0;
}

sub testfunc_nl
{
 Log("testfunc_nl() start");
 my $tt=FindHub("2:5030/1037");
 Log("\$tt=$tt");
 Log("testfunc_nl() stop"); 
 return 1;
}

sub msgtest
{
 Log("msgtest() start");
 NewMsg("msgs","Alex","2:5030/1666","User","2:5030/1157.1","msg test","","","It is My test");
 Log("msgtest() stop");
}


1;
