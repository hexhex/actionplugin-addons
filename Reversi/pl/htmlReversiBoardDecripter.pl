#!/usr/bin/perl

use LWP::Simple;

$url = 'http://www.yourturnmyturn.com/reversi/show.php?gamenumber=' . "$ARGV[0]";
# $url = 'http://www.yourturnmyturn.com/reversi/showusergame.php?gamenumber=' . '918719';
# print "$url\n";

$content = get $url;
# print "$content";

die "Couldn't get $url" unless defined $content;

# open(FILE_HTML, "$ARGV[0]") or die "manca il file di input\n";
# 
# foreach (<FILE_HTML>)
# {
# 
# 	chomp($_);
# 
# 	$content = $_;


# if($content =~ /<span class="menu"><b>You are:(.*)<\/td>/)
# {
# 	if($_ =~ /<img src=http:\/\/images.yourturnmyturn.com\/witicoon.gif>/)
# 	{
# 		print "w\n";
# 	} elsif ($_ =~ /<img src=http:\/\/images.yourturnmyturn.com\/zwarticoon.gif>/)
# 	{
# 		print "b\n";
# 	}
# }


	if($content =~ /<TABLE cellspacing='0' cellpadding='0'  border='1' style='border:2px solid brown;'>(.*)<\/TABLE>/)
	{

		@rows = split(/<TR>/, $1);

		foreach (@rows)
		{

			@columns = split(/<TD BGCOLOR=#008400>/, $_);

			$printedSomething = 0;

			foreach (@columns)
			{		
				if($_ =~ /<IMG height="34" src="http:\/\/images.yourturnmyturn.com\/g.gif" width="34" border="0">/)
				{
					print "0";
					$printedSomething++;
				} elsif($_ =~ /<IMG height="34" src="http:\/\/images.yourturnmyturn.com\/owito?.gif" width="34" border="0">/)
				{
					print "w";
					$printedSomething++;
				} elsif($_ =~ /<IMG height="34" src="http:\/\/images.yourturnmyturn.com\/ozwarto?.gif" width="34" border="0">/)
				{
					print "b";
					$printedSomething++;
				}
			}

			if($printedSomething > 0)
			{
				if($printedSomething != 8)
				{
					print "\nERROR\n";
				} else
				{
					print "\n";	
				}
			}

		}
		
	}

# }