#!/usr/bin/perl

use LWP::Simple;

$url = 'http://www.yourturnmyturn.com/reversi/play.php?gamenumber=' . "$ARGV[0]";

$content = get $url;

die "Couldn't get $url" unless defined $content;

exit 1 if $content =~ /Invalid page, game is finished./;