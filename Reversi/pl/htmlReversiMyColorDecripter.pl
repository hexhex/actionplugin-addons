#!/usr/bin/perl

use LWP::Simple;

$url = 'http://www.yourturnmyturn.com/reversi/show.php?gamenumber=' . "$ARGV[0]";

$content = get $url;

die "Couldn't get $url" unless defined $content;

if($content =~ /<span class="menu"><b>You are:(.*)<\/td>/)
{
	if($_ =~ /<img src=http:\/\/images.yourturnmyturn.com\/witicoon.gif>/)
	{
		print "w\n";
	} elsif ($_ =~ /<img src=http:\/\/images.yourturnmyturn.com\/zwarticoon.gif>/)
	{
		print "b\n";
	} else
	{
		print "e\n";
	}
}
