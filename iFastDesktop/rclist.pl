#!/usr/bin/perl
# $Id: rclist.pl 191 2012-02-02 13:29:50Z purdyec $

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

if( eval {require Time::HiRes;} ) { Time::HiRes->import( qw{ tv_interval gettimeofday} ); }
else { die "Time::HiRes is not available on this system.  It must be installed.\nTry http://search.cpan.org\n"; }
if ( ! eval { require Text::CSV::Encoded; } ) {
   die "Text::CSV::Encoded is not available on this system.  It must be installed.\nTry http://search.cpan.org\n";
}

our $VERSION = 1.0_000;
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

my %opts = (
   # general options that all programs will have
   q{cleanup}  => 1,
   q{version}  => 0,
   q{debug}    => 0,
   q{dump}     => 0,
   q{verbose}  => 0,
   q{tmp}      => ($OSNAME eq q{MSWin32} ? $ENV{TEMP} : q{/tmp}),
   q{LOGFILE}  => *STDERR,
   q{log}      => q{},
   q{logdir}   => q{},
   q{out}      => q{},
   q{OUT}      => *STDOUT,
   q{rc}       => q{},
   q{listing}  => q{},
   q{LISTING}  => *STDOUT,

   # specific options for this program
);



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

sub parseControl {
   my ($ctlLine, $rht) = @_;
   my $csv = Text::CSV::Encoded->new({encoding_in => "iso-8859-1", encoding_out=>"iso-8859-1"});
   if( $ctlLine =~ /^\s*(DEFPUSHBUTTON|PUSHBUTTON|ICON|CONTROL|GROUPBOX|LTEXT|CTEXT|RTEXT)\s+(.*)/ ) {
      my $status = $csv->parse($2);
      my @col = $csv->fields(); 
      my ($type,$ctl) = ($1,$col[1]);
      print (qq{Error parsing control line: $ctlLine}) if( $ctl eq q{} );
      $$rht{$ctl} = $type;
      debug( qq{Found $ctl ($type)} );
   }
   elsif( $ctlLine =~ /^\s*(COMBOBOX|EDITTEXT)\s+(.*)/ ) {
      my $status = $csv->parse($2);
      my @col = $csv->fields(); 
      my ($type,$ctl) = ($1,$col[0]);
      print (qq{Error parsing control line: $ctlLine}) if( $ctl eq q{} );
      $$rht{$ctl} = $type;
      debug( qq{Found $ctl ($type)} );
   }
   else {
      print ( qq{Unknown Control Line: $ctlLine} );
   }
}

sub parseDialog {
   my( $currentDialog, $riLine, $RC ) = @_;
   my %ht;  # hash table of controls within dialog
   my $ctlLine = q{};
   my $preamble = 1;
   
   debug( qq{Parsing dialog $currentDialog} );

   while( my $line = <$RC> ) {
      $riLine += 1;
      chomp $line;

      last if $line =~ /^END\s*$/;
      if($line =~ /^BEGIN\s*$/) {
         $preamble = 0;
         next;
      }
      next if $preamble;
      next if $line =~ /^\s*\/\//;  # ignore comment lines

      # look for controls.  Visual Studio will split the control definitions across 
      # multiple lines, so we need to account for broken lines
      if( $line =~ /^\s*(DEFPUSHBUTTON|PUSHBUTTON|CONTROL|ICON|GROUPBOX|CTEXT|LTEXT|RTEXT|COMBOBOX|EDITTEXT)\s+(.*)/ ) {
         # new control found!  
         # check to see if this is the terminator of a previous line
         if( q{} ne $ctlLine ) {
            parseControl( $ctlLine, \%ht );
         }
         $ctlLine = $line;
      }
      else {
         # this is a continuation line for a control
         $line =~ s/^\s+//; $line =~ s/\s+$//;
         $ctlLine .= $line;
      }
   }
   parseControl( $ctlLine, \%ht ) if q{} ne $ctlLine;

   return \%ht;
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
            q{rc=s}           => sub { $opts{rc} = $_[1]; },
            q{listing=s}      => sub { $opts{listing} = $_[1]; },
            );

if( q{} ne $opts{log} ) {
   open( my $L, q{>>}, $opts{log} ) or die "Can't open $opts{log} for append:$OS_ERROR\n";
   $opts{LOGFILE} = $L;
}   

if( $opts{dump} ) {
   $opts{debug} = 1;
   if ( ! eval { require Data::Dumper; } ) {
      die "Data::Dumper is not available on this system.  It must be installed.\nTry http://search.cpan.org\n";
   }
}

### technique to create a temporary file that gets automatically cleaned up on exit
###    my $dir = tempdir( DIR => $opts{tmp}, CLEANUP => $opts{cleanup} );
###    my ($fh, $temp) = tempfile( DIR => $dir );
###    close($fh);
### $temp is the name of the temporary file

$opts{rc} = $ARGV[0] if q{} eq $opts{rc};
badArgs(1, qq{No RC file specified} ) if q{} eq $opts{rc};
badArgs(2, $opts{rc}.qq{ does not exist\n} ) if( !(-e $opts{rc}));
badArgs(3, $opts{rc}.qq{ is not readable\n} ) if( !(-r $opts{rc}));

if( q{} ne $opts{listing} ) {
   badArgs(4, $opts{listing}.qq{ is not writable\n} ) if( -e $opts{listing} && ! (-w $opts{listing}));
   open( $opts{LISTING}, q{>:encoding(iso-8859-1)},$opts{listing} ) or die "Couldn't open $opts{listing}: $!\n";
}

my %htDlg;
my $rht;

my $iLine = 0;
my $currentDialog = q{};
my $checkNext = q{};

debug(qq[Opening $opts{rc}]);
open( my $RC, q{<:encoding(iso-8859-1)},$opts{rc} ) or die q{Couldn't open }.$opts{rc}.qq{: $!\n};
while( my $line = <$RC> ) {
   ++$iLine;
   chomp $line;
   next if( $line =~ /^\s+\/\// );  # ignore lines that begin with a comment 
   if( $line =~ /^([A-Za-z0-9_]+?)\s*DIALOG/ ) {
      debug( qq{$iLine: Found dialog $currentDialog} );
      my $currentDialog = $1;
      my %ht;
      { my %ht; $htDlg{$currentDialog} = \%ht; }
      $htDlg{$currentDialog} = parseDialog( $currentDialog, \$iLine, $RC );
   }
}
close( $RC ) or die q{Couldn't close }.$opts{rc}.qq{: $!\n};

debugDump(q{htDlg},\%htDlg);

foreach my $dlg (sort(keys(%htDlg))) {
   my $r = $htDlg{$dlg};
   foreach my $ctl (sort(keys(%{$r}))) {
      my $type = $$r{$ctl};
      print {$opts{LISTING}} qq{$dlg,$ctl,$type\n};
   }
}

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

rclist.pl - Convert a Win32 .rc file into a sorted list of controls by dialog.

=head1 VERSION

This documentation refers to rclist.pl version 1.0

=head1 SYNOPSIS

   rclist.pl <RC file| --rc=> [--listing=]
         [--log=file]
         [--man] [--help] [--usage] [--version]
         [--verbose] [--debug] [--dump] 



=head1 OPTIONS

=over

=item RC file

=item --rc=

Name of the RC file to process.  The file must exist and must be a valid .rc file

=item --listing=

The name of the listing file.  If this is not specified then it is written to STDOUT.

=item --log=file

The name of a file to which log messages will be written.  
This defaults to STDOUT (i..e the console).

=item --[no]verbose

This option can be used to print out progress and other informational messages
about the operation of rclist.pl

=item --[no]debug

This option can be used to print out debugging messages to STDERR.  It can be useful
for diagnosing problems with the program itself

=item --[no]dump

This option will dump certain data structures to STDERR.  Setting --dump will cause --debug
to also be set.

=item --[no]cleanup

This option will cause all temporary files to be automatically deleted on completion of
the program.  Setting --nocleanup will leave the temporary files in place.

=item --[no]usage

Print usage information to the console and exit.

=item --[no]man

Display a man page for this program.

=item --[no]help

Print the usage information, and a description of the options.

=item --[no]version

Print the current version number and exit.

=back

=head1 RETURN VALUES

rclist.pl will return a value upon completion

=over

=item 0

There were no errors

=item 1

No RC file was specified

=item 2

RC file does not exist

=item 3

RC file is not readable

=back

=head1 DESCRIPTION

This program reads a Visual Studio Resource file (RC file) and produces a listing file
of dialogs and controls.

Each line in the listing contains the ID of the dialog, the ID of the control, and the type
of the control.

=head1 EXAMPLES

   rclist.pl ifastgui_en.rc --listing=en.lst

=head1 DIAGNOSTICS

Add C<--debug> to the command line to display useful debugging information

=head1 CONFIGURATION AND ENVIRONMENT

There is no special configuration that is required.

=head1 REQUIRED MODULES

This program requires the following non-standard Perl modules.  They may be installed from 
CPAN (http://search.cpan.org) as needed.

   Data::Dumper  (only if --dump is specified)
   Time::HiRes
   Text::CSV::Encoded

=head1 AUTHOR

Chris Purdye cpurdye@ifdsgroup.com

=head1 LICENCE AND COPYRIGHT

Copyright (C) 2012 International Financial Data Services.  All Rights Reserved.
