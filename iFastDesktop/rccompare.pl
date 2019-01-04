#!/usr/bin/perl
# $Id: rccompare.pl 191 2012-02-02 13:29:50Z purdyec $

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
use Data::Dumper;

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

   # specific options for this program
   q{f1}       => q{},  # first file to compare
   q{f2}       => q{},  # second file to compare
   q{rclist}   => q{},  # fully-qualified path to rclist.pl.  Defaults to ./rclist.pl if not specified
   q{ignore}   => q{},  # file that contains controls to ignore
   q{static}   => 1,    # consider missing static controls to be an error
   q{return}   => 0,    # result of compares.  Will be 1 if a mismatch was found.
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

################
# Load a file to be compared and populate a hash table of dialogs and controls
#
# The file to be loaded can either be a Win32 .rc file, or a listing file generated
# by rclist.pl.  rclist.pl converts the not-entirely-complicated .rc file into
# a very straightforward list of controls in each dialog.  These listing files are
# very easy to compare.
#
# $rht is a reference to a hash keyed by dialog name.  Each hash entry is a hash keyed
# by control name that points to the control type.
# 
sub loadCompareFile {
   my( $cmpFile, $rht ) = @_;
   debug(qq{Loading $cmpFile});
   # if this is an .rc file then convert it to a listing file first
   if( $cmpFile =~ /\.rc$/ ) {
      # convert .rc into a temporary listing file.
      my ($fh, $temp) = tempfile( DIR => $opts{tmpdir} );
      close($fh);
      debug(qq{$cmpFile is an RC file, converting to listing as $temp});

      my $cmd = $opts{rclist}.q{ }.$cmpFile.qq{ --listing=$temp};
      debug(qq{\$cmd=$cmd});
      my $rc = qx/$cmd/;
      return 1 if( $CHILD_ERROR );

      $cmpFile = $temp;
      # $temp is the name of the temporary listing file.  It will
      # be automatically deleted when this program exits.  
   }
   debug(qq{Opening listing file $cmpFile for loading});
   open( my $CMP, qq{<$cmpFile} ) or die( qq{Couldn't open $cmpFile: $!\n} );
   while( <$CMP> ) {
      chomp;
      next if /^\s*\/\//;  # consider lines starting with // to be comments 
      if( /^(.*?),(.*?),(.*)$/ ) {
         my ($dlg,$ctl,$type) = ($1,$2,$3);
         if( !exists($$rht{$dlg}) ) {
            my %ht;
            $$rht{$dlg} = \%ht;
         }
         $$rht{$dlg}->{$ctl} = $type;
      }
   }
   close( $CMP ) or die( qq{Couldn't close $cmpFile: $!\n} );
   return( 0 );
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
            q{f1=s}           => sub { $opts{f1} = $_[1]; },
            q{f2=s}           => sub { $opts{f2} = $_[1]; },
            q{ignore=s}       => sub { $opts{ignore} = $_[1]; },
            q{static!}        => sub { $opts{static} = $_[1]; },
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

$opts{rclist} = $g_scriptDir.q{/rclist.pl} if q{} eq $opts{rclist};

badArgs(24,q{Temporary directory }.$opts{tmp}.q{ does not exist }) if ( ! (-e $opts{tmp} ) );
badArgs(25,q{Temporary directory }.$opts{tmp}.q{ is not a directory }) if ( ! (-d $opts{tmp} ) );
badArgs(26,q{Temporary directory }.$opts{tmp}.q{ is not writable }) if ( ! (-w $opts{tmp} ) );


### technique to create a temporary file that gets automatically cleaned up on exit
$opts{tmpdir} = tempdir( DIR => $opts{tmp}, CLEANUP => $opts{cleanup} );
### $temp is the name of the temporary file

$opts{f1} = shift @ARGV if $opts{f1} eq q{};
$opts{f2} = shift @ARGV if $opts{f2} eq q{};

debug( Dumper(\%opts) );

# make sure that we have two files to compare, and that the exist and are readable
badArgs(11,q{No files to compare.}) if $opts{f1} eq q{};
badArgs(12,q{Two files must be specified.  You specified only one.}) if $opts{f2} eq q{};
badArgs(13,$opts{f1}.q{ does not exist}) if( ! (-e $opts{f1}) );
badArgs(14,$opts{f2}.q{ does not exist}) if( ! (-e $opts{f2}) );
badArgs(15,$opts{f1}.q{ is not readable}) if( ! (-r $opts{f1}) );
badArgs(16,$opts{f2}.q{ is not readable}) if( ! (-r $opts{f2}) );

# load the files to compare and put them into a hash structure
# see 'loadCompareFile' for a description of the structure of the hash
my %htCmp1;
if( loadCompareFile($opts{f1},\%htCmp1) ) {
   error( qq[Error loading compare file $opts{f1}\n] );
   exit( 30 );
}
debugDump($opts{f1},\%htCmp1);
my %htCmp2;
if( loadCompareFile($opts{f2},\%htCmp2) ) {
   error( qq[Error loading compare file $opts{f2}\n] );
   return( 30 );
}

debugDump($opts{f2},\%htCmp2);

# The 'ignore' file lists the controls within each dialog that should
# be ignored if they aren't found in both .rc files.  The format of the
# ignore file can be found in the documentation at the end of this program
my %htIgnore;
loadCompareFile($opts{ignore}, \%htIgnore) if q{} ne $opts{ignore};
debugDump(q{htIgnore},\%htIgnore);

compareFiles(\%htCmp1, $opts{f1}, \%htCmp2, $opts{f2}, \%htIgnore );
compareFiles(\%htCmp2, $opts{f2}, \%htCmp1, $opts{f1}, \%htIgnore );

sub compareFiles {
   my( $rhtLHS, $lhs, $rhtRHS, $rhs, $rhtIgnore ) = @_;
   
   # check for controls in htCmp1 that are not in htCmp2
   debug(qq{Checking $rhs for missing items from $lhs});
   foreach my $dlg (sort(keys(%{$rhtLHS}))) {
      debug(qq{Checking $dlg});
      my $rhtLeftDlg = $$rhtLHS{$dlg};
      if( ! exists($$rhtRHS{$dlg}) ) {
         if( exists $htIgnore{$dlg} ) {
            # control is in the ignore list for this dialog
            print {*STDOUT} qq{IGNORE: Dialog $dlg not in $rhs\n};
         } 
         else {
            $opts{return} = 1;
            print {*STDOUT} qq{MISSING: Dialog $dlg not in $rhs\n};
         }
      } 
      else {
         my $rhtRightDlg = $$rhtRHS{$dlg};
         foreach my $ctl (sort(keys(%{$rhtLeftDlg}))) {
            debug( qq{Checking $dlg::$ctl} );
            if( !exists($$rhtRightDlg{$ctl}) ) {
               if( exists $htIgnore{$dlg} && exists $htIgnore{$dlg}->{$ctl} ) {
                  # control is in the ignore list for this dialog
                  print {*STDOUT} qq{IGNORE: Control $dlg:$ctl not in $rhs\n};
               } 
               else {
                  if( !$opts{static} && 
                      $$rhtLeftDlg{$ctl} =~ /LTEXT|CTEXT|RTEXT|GROUPBOX/ ) {
                     print {*STDOUT} qq{WARNING: Static Control $dlg:$ctl not in $rhs\n};
                  }
                  else {
                     $opts{return} = 1;
                     print {*STDOUT} qq{MISSING: Control $dlg:$ctl not in $rhs\n};
                  }
               }
            }
            elsif( $$rhtLeftDlg{$ctl} ne $$rhtRightDlg{$ctl} ) {
               $opts{return} = 1;
               print {*STDOUT} qq[CONFLICT: Control $dlg:$ctl is different type ($$rhtRightDlg{$ctl} instead of $$rhtLeftDlg{$ctl}\n];
            }
         }
      }
   }
}

exit( $opts{return} );

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

rccompare.pl - Compare two RC files for differences

=head1 VERSION

This documentation refers to rccompare.pl version 1.0

=head1 SYNOPSIS

   rccompare.pl RC1 RC2 [--ignore=] [--[no]static] 
         [--tmp=dir] [--log=file]
         [--man] [--help] [--usage] [--version] 
         [--verbose] [--debug] [--dump] [--[no]cleanup]

=head1 OPTIONS

=over

=item RC1, RC2

=item --f1=, --f2=

The names of the RC files to compare.  You may specify a I<listing> file
generated previously by C<rclist.pl> for either file.  The order of the files
on the command line does not matter.

=item --ignore=

This program can be configured to ignore certain dialogs or controls within dialogs.
This is done through the use of an 'ignore' file.  The format of this file is identical
to that of the listing files and is explained below under L<CONFIGURATION AND ENVIRONMENT>

=item --[no]static

Certain classes of controls are not as significant as others when comparing the two .rc files.
Static controls are defined as LTEXT, CTEXT, RTEXT and GROUPBOX.
If this option is true (--static) then missing static controls are treated as errors.  
If the option is false (--nostatic) then missing static controls are treated as warnings.  
The default value is --static.

=item --tmp=dir

The name of the directory to use when creating temporary files.  
This defaults to /tmp for Linux and the value of the TEMP environment variable
for for Windows (e.g. "c:\Documents and Settings\user\Local Settings\Temp")

=item --log=file

The name of a file to which log messages will be written.  
This defaults to STDOUT (i..e the console).

=item --[no]verbose

This option can be used to print out progress and other informational messages
about the operation of rccompare.pl

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

rccompare.pl will return a value upon completion

=over

=item 0

There were no MISSING controls or dialogs and no CONFLICT control types.
THere may be WARNING and IGNORE messages for this return value.

=item 1

At least one MISSING control or dialog or a CONFLICT control type was found.

=item 11

A resource or listing file was not specified.

=item 12

A resource or listing file was not specified.

=item 13

A resource or listing file does not exist

=item 14

A resource or listing file does not exist

=item 15

A resource or listing file is not readable

=item 16

A resource or listing file is not readable

=item 24

The temporary directory does not exist

=item 25

The temporary directory is not actually a directory!

=item 26

The temporary directory is not writeable.

=item 30

Error when rclist.pl generated the listing file.  Try running rclist.pl directly.

=back

=head1 DESCRIPTION

This program will compare two Visual Studio Resource files (B<RC>) and display 
a list of differences in the dialogs.

The only differences noted are 1) a dialog is in one RC file and not in the other,
2) a control is missing from a dialog in one RC file, and 3) two controls are of
different types in each RC file.

rccompare.pl will invoke a preprocess step, rclist.pl, that converts the RC file
into a listing of controls within a each dialog.  rccompare.pl can process the 
listing files instead of the RC files.

=head1 EXAMPLES

Suppose that you have two RC files, ifastgui_en.rc and ifastgui_fr.rc.  You compare 
the two by running 

   rccompare.pl ifastgui_en.rc ifastgui_fr.rc

It is possible to compare the listing files instead

   rclist.pl ifastgui_en.rc --listing=en.lst
   rclist.pl ifastgui_fr.rc --listing=fr.lst
   rccompare.pl en.lst fr.lst

=head1 DIAGNOSTICS

Add C<--debug> to the command line to display useful debugging information.

Add C<--dump> to display certain data structures.

Add C<--nocleanup> to prevent the deletion of temporary files.

=head1 CONFIGURATION AND ENVIRONMENT

rccompare.pl requires that rclist.pl is installed in the same directory.

=head2 Listing File Format

rccompare.pl expects to process the output of rclist.pl.  rclist.pl 
produces listing files in the format

   dialog,control,type

rccompare.pl can be configured to ignore certain dialogs and controls
within dialogs through the use of an I<ignore file>.  This file has
the same syntax as a listing file.  The 'type' is not considered.  To 
mark an entire dialog to be ignored simply include a line that mentions
the dialog with no controls.  The extra commas at the end of the line
are significant and required!

You don't need to specify for which language a dialog or control is
to be ignored.  An entry in the I<ignore file> will cause the dialog
or control to be ignored in all resource files that are considered.

For example,

   // IDD_ENGLISH_ONLY dialog is not in French resources
   IDD_ENGLISH_ONLY,,
   // ignore IDC_ENGLISH_TXT in IDD_EN_DIALOG if not in French resources
   IDD_EN_DIALOG,IDC_ENGLISH_TXT,
   // ignore IDC_FRANCAIS_CB in IDD_FR_DIALOG if not in English resources
   IDD_FR_DIALOG,IDC_FRANCAIS_CB,


=head1 REQUIRED MODULES

This program requires the following non-standard Perl modules.  They may be installed from 
CPAN (http://search.cpan.org) as needed.

   Data::Dumper  (only if --dump is specified)
   Time::HiRes

=head1 SEE ALSO

   rclist.pl

=head1 AUTHOR

Chris Purdye cpurdye@ifdsgroup.com

=head1 LICENCE AND COPYRIGHT

Copyright (C) 2012 International Financial Data Services.  All Rights Reserved.
