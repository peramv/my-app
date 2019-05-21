#!/usr/bin/perl
# $Id: dtop_brander.pl 182 2011-10-13 18:39:21Z purdyec $

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
use Sys::Hostname;
use Time::HiRes qw( tv_interval gettimeofday );

our $VERSION = 0.1_000;
my $g_revision = sprintf q{%s}, q$Rev$ =~ /(\d+)/g;
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

$opts{buildRoot}     = $g_scriptDir;
$opts{cpp}           = q{ifastcbo/version_app.cpp};
$opts{versionFile}   = q{version.txt};
$opts{rev}           = 0;
$opts{label}         = q{};

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
            q{cpp=s}          => sub { $opts{log} = $_[1]; },
            q{versionFile=s}  => sub { $opts{log} = $_[1]; },
            q{label=s}        => sub { $opts{label} = $_[1]; },
            q{rev=i}          => sub { $opts{rev} = $_[1]; },
            );

if( q{} ne $opts{log} ) {
   open( my $L, q{>>}, $opts{log} ) or die "Can't open $opts{log} for append:$OS_ERROR\n";
   $opts{LOGFILE} = $L;
}   

badArgs(1, q{--buildRoot must be specified} ) if ( q{} eq $opts{buildRoot} );
badArgs(2, q{buildRoot is not a validDirectory: }.$opts{buildRoot} ) if ( ! (-d $opts{buildRoot}) );
badArgs(3, q{--cpp must be specified} ) if ( q{} eq $opts{cpp} );
my $cpp = $opts{buildRoot}.q{/}.$opts{cpp};
badArgs(4, qq{cpp is not readable: $cpp} ) if ( ! (-r qq{$cpp}) );
badArgs(5, q{--versionFile must be specified if --label is not} ) if ( q{} eq $opts{label} && q{} eq $opts{versionFile} );
my $versionFile = $opts{buildRoot}.q{/}.$opts{versionFile};
if( q{} eq $opts{label} ) {
   debug(qq{Reading $versionFile to get release label} );
   badArgs(6, q{versionFile is not readable: }.$versionFile ) if ( ! (-r $versionFile) );
   open(my $VER, qq{<$versionFile} ) or die qq{Could not open $versionFile: $!};
   my $l = <$VER>;
   debug( $l );
   chomp $l;
   # strip leading/trailing blanks.
   $l =~ s/^\s+//; $l =~ s/\s+$//;
   $opts{label} = $l;
   close $VER;
}
$opts{label} = q{Checked} if( q{} eq $opts{label} );

if( $opts{debug} ) {
   use Data::Dumper;
   print {*STDERR} Dumper(\%opts).qq{\n};
   print {*STDERR} qq{\n};
   print {*STDERR} qq{\$cpp: $cpp\n};
   print {*STDERR} qq{\$versionFile: $versionFile\n};
}

### technique to create a temporary file that gets automatically cleaned up on exit
my $dir = tempdir( DIR => $opts{tmp}, CLEANUP => $opts{cleanup} );
my ($TEMP, $temp) = tempfile( DIR => $dir );

### $temp is the name of the temporary file
open( my $CPP, qq{<$cpp} ) or die qq{Couldn't open $cpp for reading: $!};
while( <$CPP> ) {
   chomp;
   if( /^#define THIS_BUILD / ) {
      debug( qq{Rewriting THIS_BUILD: }.$opts{rev} );
      $_ = qq[#define THIS_BUILD $opts{rev}];
   }
   if( /^#define THIS_COMPUTER / ) {
      my $host = hostname;
      debug( qq{Rewriting THIS_COMPUTER: }.$host );
      $_ = q{#define THIS_COMPUTER I_("}.$host.q{")};
   }
   if( /^#define THIS_VERSION / ) {
      debug( qq{Rewriting THIS_VERSION: }.$opts{label} );
      $_ = q{#define THIS_VERSION I_("}.$opts{label}.q{")};
   }
   print $TEMP qq{$_\n}; 
}
close $TEMP;
chmod( 0644, $cpp );
copy( $temp, $cpp );
chmod( 0444, $cpp );


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

dtop_brander.pl - Update the iFAST/Desktop 'version' source file

=head1 VERSION

This documentation refers to dtop_brander.pl version 0.1

=head1 SYNOPSIS

   dtop_brander.pl [--versionFile=] [--cpp=] [--label=] [--rev=]
         [-buildRoot=]
         [--man] [--help] [--usage] [--version] [--verbose] [--debug] 


=head1 OPTIONS

=over

=item --cpp=

The name of the version file.  This is relative to the buildRoot and defaults
to ifastcbo/version_app.cpp

=item --buildRoot=

The root directory of the build.  This defaults to the directory of this script.
It is expected that this script will be checked in to source control in the 
root of the source tree.

=item --versionFile=

The file that contains the release label.  This is specified relative to the
buildRoot.  It defaults to 'version.txt'.

Specifying --label will override --versionFile

See L<CONFIGURATION AND ENVIRONMENT> for more information on the version file.

=item --label=

The label to stamp into the file specified by --cpp

If --label is specified as blank (i.e. --label=) and the version file is empty 
then the label will be "Checked".  Pretty arbitrary, eh?

=item --rev=

The subversion revision of this build.  This defaults to 0.

=item --tmp=dir

The name of the directory to use when creating temporary files.  
This defaults to /tmp for Linux and the value of the TEMP environment variable
for Windows (e.g. "c:\Documents and Settings\user\Local Settings\Temp")

=item --log=file

The name of a file to which log messages will be written.  
This defaults to STDOUT (i..e the console).

=item --[no]verbose

This option can be used to print out progress and other informational messages
about the operation of dtop_brander.pl

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

iFAST/Desktop has a version module that is updated during each build.  The module
has functions that the application invokes when it needs version or
build information.

The version module consists of a C++ source file and corresponding header file.  The C++
source file is updated during the build with the following information:
    
    Computer on which it was built
    The Subversion revision number
    An arbitrary release label

This script is used to customize the C++ source file with the above information before
a compile is executed.  

=head1 EXAMPLES

=over

=item Stamp an arbitrary label and revision

Brand this build as "Rel_12.2.2" from Subversion revision 4343

   dtop_brander.pl --label=Rel_12.2.2 --rev=4343

=item Stamp the label as defined in Subversion

The default version file, ./version.txt, is used instead of an arbitrary label.
In this case we don't specify a Subversion revision, so it will stamp it with '0'.

   dtop_brander.pl

=back   

=head1 DIAGNOSTICS

Specify --debug on the command line to get loads of information.

=head1 CONFIGURATION AND ENVIRONMENT

It is expected that the SCM team will maintain a file in the root of the build tree in Subversion.
This file, version.txt, will have a single line that contains the release label.  This script will
read that line, strip leading and trailing spaces, and stamp it into the C++ source file.

Speaking of the C++ source file that is used by the version module, that file is 
expected to be ifastcbo/version_app.cpp.  This can be changed at execution time with the
--versionFile option.

=head1 AUTHOR

Chris Purdye cpurdye@ifdsgroup.com

=head1 LICENCE AND COPYRIGHT

Copyright (C) 2012 International Financial Data Services.  All Rights Reserved.
