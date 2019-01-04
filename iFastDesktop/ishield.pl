#!/usr/bin/perl
# $Id: ishield.pl 182 2011-10-13 18:39:21Z purdyec $

use strict;
use English qw( -no_match_vars );
use Fatal qw( open close );
use Getopt::Long;
use File::Temp qw( tempfile tempdir );
use File::Spec;
use File::Copy;
use File::Basename;
use Carp;
use Cwd;
use Time::HiRes qw( tv_interval gettimeofday );

our $VERSION = 0.2_000;
my $g_revision = sprintf q{%d}, q$Rev$ =~ /(\d+)/g;
our $g_scriptDir = File::Spec->rel2abs(dirname(__FILE__));
if( readlink( __FILE__ ) ) {
   $g_scriptDir = File::Spec->rel2abs(dirname(readlink(__FILE__)));
}

my %opts;

# Convenient Signal handler for Ctrl-C
sub catchSigInt {
   print {*STDERR} qq{\nBreak\n};
   exit 4;
}
$SIG{INT} = \&catchSigInt;


# set $opts{cleanup} to 1 to force cleanup of temporary files after script completes
$opts{cleanup}       = 1;

# Command Line options
$opts{version}       = 0;  # display version
$opts{debug}         = 0;  # use debug mode
$opts{verbose}       = 0;  # display status info to STDERR

$opts{tmp}           = q{/tmp};
$opts{tmp}           = $ENV{TEMP} if $OSNAME eq q{MSWin32};

$opts{LOGFILE}       = *STDOUT;
$opts{log}           = q{};

$opts{project}       = q{DST Graphical Front End.ism};
#$opts{project}       = q{Fribble.ism};
$opts{client}        = q{};
$opts{relLabel}      = q{};
$opts{buildRoot}     = $g_scriptDir;
$opts{'7z'}          = q{c:\\ishield9\\7za.exe};
$opts{'versionFile'} = q{version.txt};

# These functions only work when called from within other subroutines!
sub whoami{ (caller(1))[3];}
sub whereami{ (caller(1))[2];}
sub whowasi{ (caller(2))[3];}
sub wherewasi{ (caller(2))[2];}

sub error {
   print {*STDERR} (@_,qq{\n});
}
sub verbose {
   logger(@_,qq{\n}) if $opts{verbose};
}

sub debugDump {
   return if (scalar(@_) != 2 || !$opts{debug});
   require Data::Dumper;
   print {*STDERR} ($_[0],Dumper($_[1]),qq{\n}) if $opts{dump};
}

sub debug {
   return logger( @_,qq{\n} ) if $opts{debug};
}

sub logger {
   my @aArgs = @_;
   my ($secs,$usecs) = gettimeofday();
   my @T = localtime($secs);
   my $t = sprintf(q{%.4d-%.2d-%.2d %.2d:%.2d:%.2d.%03d [%5d]},
                    $T[5]+1900,
                    $T[4]+1,
                    $T[3],
                    $T[2],
                    $T[1],
                    $T[0],
                    $usecs/1000,
                    $PROCESS_ID);
   print {$opts{LOGFILE}} qq{$t: },@aArgs;

}


GetOptions( q{usage!}         => sub { require q{Pod/Usage.pm};
                                       import Pod::Usage;
                                       pod2usage( -verbose => 0 ); },
            q{help!}          => sub { require q{Pod/Usage.pm};
                                       import Pod::Usage;
                                       pod2usage( -verbose => 1 ); },
            q{man!}           => sub { require q{Pod/Usage.pm};
                                       import Pod::Usage;
                                       pod2usage( -verbose => 2 ); },
            q{version!}       => sub { print {*STDOUT} qq{$VERSION (Revision $g_revision)\n}; exit( 0 );},
            q{verbose!}       => sub { $opts{verbose} = $_[1]; },
            q{debug!}         => sub { $opts{debug} = $_[1]; },
            q{dump!}          => sub { $opts{dump} = $_[1]; },
            q{cleanup!}       => sub { $opts{cleanup} = $_[1]; },
            q{tmp=s}          => sub { $opts{tmp} = $_[1]; },
            q{log=s}          => sub { $opts{log} = $_[1]; },
            q{buildRoot=s}    => sub { $opts{buildRoot} = $_[1]; },
            q{client=s}       => sub { $opts{client} = $_[1]; },
            q{relLabel=s}     => sub { $opts{relLabel} = $_[1]; },
            q{project=s}      => sub { $opts{project} = $_[1]; },
            q{versionFile=s}  => sub { $opts{versionFile} = $_[1]; },
            );

if( q{} ne $opts{log} ) {
   open( my $L, q{>>}, $opts{log} ) or die "Can't open $opts{log} for append:$OS_ERROR\n";
   $opts{LOGFILE} = $L;
}

if( $opts{debug} ) {
   use Data::Dumper;
   print Dumper(\%opts),qq{\n};
}

badArgs( 1, qq{--buildRoot not specified} ) if( q{} eq $opts{buildRoot} );
badArgs( 2, q{Build root (}.$opts{buildRoot}.q{ not found} ) if( ! (-d $opts{buildRoot}) );
my $isRoot = $opts{buildRoot}.q{/InstallShield/Desktop};
badArgs(3, qq{InstallShield source not found: $isRoot} ) if( ! (-d $isRoot) );
badArgs(4, qq{--project= not specified} ) if( q{} eq $opts{project} );
my $projectFile = $isRoot.q{/}.$opts{project};
badArgs(5, qq{No project file: $projectFile} ) if( ! (-r $projectFile) );
badArgs(6, qq{--client= not specified} ) if( q{} eq $opts{client} );
my $optionFileSrc = $isRoot.q{/Option Files/option_}.$opts{client}.q{.ini};
badArgs(7, qq{No option file: $optionFileSrc} ) if( ! (-r $optionFileSrc) );
badArgs(8, q{Either --relLabel= or --versionFile must be specified} ) if ( q{} eq $opts{versionFile} && q{} eq $opts{relLabel} );
badArgs(9, q{Only one of --relLabel= and --versionFile may be specified} ) if ( q{} ne $opts{versionFile} && q{} ne $opts{relLabel} );

if( q{} ne $opts{versionFile} )  {
   my $versionFile = $opts{buildRoot}.q{/}.$opts{versionFile};
   badArgs( 10, qq{Version file is not readable: $versionFile} ) if( ! (-r qq{$versionFile}) );
   open(my $VER, qq{<$versionFile} ) or die qq{Coulkd not open $versionFile: $!};
   my $l = <$VER>;
   $l =~ s/^\s+//; $l =~ s/\s+$//;
   $opts{relLabel} = $l;
   close $VER;
}

my $CMD;

# clean out existing installshield artifacts
{
   # Perl for Windows really sucks.  Look at this crap that I have to do to delete files in a directory!
   use File::Find;
   find( \&wanted, $opts{buildRoot}.q{/Disk Images/Disk1} );
   sub wanted {
      if( -f $File::Find::name ) {
         unlink($File::Find::name);
      }
   }
}

# compile!
my $cmd = q{c:\\ishield9\\IsSABld.exe -b "}.$opts{buildRoot}.q{" -p "}.$projectFile.q{"};
print {*STDERR} qq{\$cmd=$cmd\n} if $opts{debug};
open( my $CMD, qq{$cmd|} ) || die qq{Can execute $cmd\n};
while( <$CMD> ) {
   print $_;
}
close( $CMD );
# copy option file
#my $optionFileSrc = $isRoot.q{/Option Files/option_}.$opts{client}.q{.ini};
my $optionFileDest = $opts{buildRoot}.q{/Disk Images/Disk1};
copy( $optionFileSrc, $optionFileDest );
# zip it up
my ($d, $m, $y) = (localtime)[3,4,5];
$cmd = sprintf( q{%s a -tzip "%s/Disk Images/ifast_Desktop_%s_%s_%04d_%02d_%02d.zip" "%s/Disk Images/Disk1/*"},
                $opts{'7z'},
                $opts{buildRoot},
                $opts{client},
                $opts{relLabel},
                $y+1900, $m+1, $d,
                $opts{buildRoot});
print {*STDERR} qq{\$cmd=$cmd\n} if $opts{debug};
open( my $CMD, qq{$cmd|} ) || die qq{Can execute $cmd\n};
while( <$CMD> ) {
   print $_;
}
close( $CMD );

### technique to create a temporary file that gets automatically cleaned up on exit
###    my $dir = tempdir( DIR => $opts{tmp}, CLEANUP => $opts{cleanup} );
###    my ($fh, $temp) = tempfile( DIR => $dir );
###    close($fh);
### $temp is the name of the temporary file


sub badArgs
{
   my ($rc, $msg) = @_;

   print {*STDERR} qq{$msg\n};

   require q{Pod/Usage.pm};
   import Pod::Usage;
   pod2usage( -verbose => 0 );

   if( 0 != $rc ) {exit($rc);}
   return(0);
}


=head1 NAME

ishield.pl - Invoke InstallShield compiler for iFAST/Desktop

=head1 VERSION

This documentation refers to ishield.pl version 0.2

=head1 SYNOPSIS

   ishield.pl 
         <--buildRoot=> <--project=> <--client=> 
         <[--relLabel=>]|[--versionFile=]>
         [--tmp=dir] [--log=file]
         [--man] [--help] [--usage] [--version] [--verbose] [--debug]


=head1 OPTIONS

=over

=item --buildRoot=dir

Fully qualified directory that is the root of the iFAST/Desktop build.
This defaults to the directory where ishield.pl is run from.  This will
I<usually> be the correct buildRoot

=item --project=

Name of the project file.  This defaults to foozle.ism

=item --client=

Which client to build.  There must be a corresponding C<option_>I<client>.ini file

=item --versionFile=

The name of the C<version.txt> file that contains the current iFAST version number.
This defaults to version.txt in the buildRoot.

=item --relLabel=

The release label to stamp into the deployed .zip files

=item --tmp=dir

The name of the directory to use when creating temporary files.
This defaults to /tmp for Linux and the value of the TEMP environment variable
for for Windows (e.g. "c:\Documents and Settings\user\Local Settings\Temp")

=item --log=file

The name of a file to which log messages will be written.
This defaults to STDOUT (i..e the console).

=item --[no]verbose

This option can be used to print out progress and other informational messages
about the operation of ishield.pl

=item --[no]usage

Print usage information to the console and exit.

=item --[no]man

Display a man page for this program.

=item --[no]help

Print the usage information, and a description of the options.

=item --[no]version

Print the current version number and exit.

=back

=head1 DESCRIPTION

Very quick and dirty script to invoke installshield for Jenkins build of iFAST/Desktop

The script assumes that everything is centred around the buildRoot.  The buildRoot is 
the directory where the iFAST/Desktop build was done.   

Files must be copied into a 'shipset' directory structure as specified in CONFIGURATION

The output will be a zip file in Disk Images, named

ifast_Desktop_I<client>_I<release>_I<date>.zip

=head1 EXAMPLES

perl ishield.pl --client=TA --relLabel=12.2.0

This will compile everything up into Disk Images/Disk1, and zip it into Disk Images

=head1 DIAGNOSTICS

As always, add --debug to get loads'o'crap spit out to stderr

=head1 CONFIGURATION AND ENVIRONMENT

Assumptions!  Many, many, many...

The project is Fribble.ism.  Why Fribble?  Why not!

Files are moved into the 'shipset' folders as appropriate.

   shipset/win32
      bin/Release/*.dll,*.exe,*.ocx
   shipset/csi
      ifastcsi/ifast.ek*
      ifastcsi/guicbie.*
   shipset/data
      data/*.cnd
      data/databroker.bin
      data/*.chm
      data/*.avi
   shipset/data/config
      data/config/*
      data/config/*

Installshield compiler is version 9 and is installed to c:\ishield9

7-Zip all-in-one compression utility, 7za.exe, is installed in c:\ishield9

=head1 AUTHOR

Chris Purdye cpurdye@ifdsgroup.com

=head1 LICENCE AND COPYRIGHT

Copyright (C) 2012 International Financial Data Services.  All Rights Reserved.
