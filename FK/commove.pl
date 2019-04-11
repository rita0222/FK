#!/usr/bin/env perl

use strict;
use warnings;

die "Usage: $0 CommentBase\n" if $#ARGV != 0;

my $count = 0;
my ($first, $last, $str);

while(defined(my $line = <STDIN>)) {
	if($count == 0) {
		$first = $line;
	}
	$str .= $line;
	$last = $line;
	$count++;
}

$str =~ s/^\xef\xbb\xbf//;
$str =~ s/\/\*\*\*\*\*\*.*\*\*\*\*\///s;
$str =~ s/\r//g;

open(BASE, $ARGV[0]) or die $!;

while(<BASE>) {
	print $_;
}

close(BASE);

print $str;
