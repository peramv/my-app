# build replacement fragment for iFAST Desktop build 

# this is *NOT* a standalone perl script ... it is intended to be used as
# part of the Surround Products Generic Build Script, build_gen.pl

use File::Spec;
use File::Temp;
use File::Copy;
use File::Path;
#use File::Spec::Win32;
use Win32::TieRegistry;
use Win32::File;

use IO::File;

sub BrandUCS2LEResource;
sub BrandASCIIResource;
sub MakeUCSString;

print "Building...\n" if( 1 == $args->verbose );

# brand the version_app.cpp file
if( '' ne $args->getBranderProject() ) {
   chdir( $args->targetdir . $args->getBranderProject() );
   Build::Brander( $args, $args->getBranderName() );
   chdir( $cwd );

   # write the version.txt file to the target diretory
   chdir( $args->targetdir );
   Build::Version( $args, $args->getBranderName() );
   chdir( $cwd );
}
{
   # brand the resource files
   my @aBRFs = $args->getBranderResourceFiles();
   foreach my $brf ( @aBRFs ) {
      my $dir = $$brf{'project'};
      chdir( $args->targetdir . $dir );
      my $resourceFile = $$brf{'file'};
      if( $resourceFile eq 'rescommonfr.rc' || $resourceFile eq 'rescanadafr.rc')
      {
         print "Branding binary resource file...", $resourceFile, "\n";
         BrandASCIIResource( $args, $resourceFile );
      }
      else
      {
         Build::BrandResource( $args, $resourceFile );
      }
      chdir( $cwd );
   }
}
{
   # brand the version .cpp files (usually dllmain.cpp, but don't have to be!)
   my @aBVFs = $args->getBranderVersionFiles();
   foreach my $bvf ( @aBVFs ) {
      my $dir = $$bvf{'project'};
      chdir( $args->targetdir . $dir );
      Build::BrandVersion( $args, $$bvf{'file'} );
      chdir( $cwd );
   }
}
{
   # brand the condition files
   my @aBCFs = $args->getBranderConditionFiles();
   foreach my $bcf ( @aBCFs ) {
      my $dir = $$bcf{'project'};
      chdir( $args->targetdir . $dir );
      Build::BrandCondition( $args, $$bcf{'file'} );
      chdir( $cwd );
   }
}

if ( $args->config eq 'all' || $args->config eq 'debug' ) {
   Build::Gen( $args, "Debug", $args->workspace, $args->project );
}
if ( $args->config eq 'all' || $args->config eq 'release' ) {
   
#CP20061018   my $package = "ifast_desktop_".$args->pvcs_version;
   # we compile differently in release mode...
   # we build the ifastgui project then we build resCanada/resDll and resEurope/resDll
   $project = "ifastgui";

   if( 0 == $args->rcBuild &&
       0 == Build::Gen( $args, "Release", $args->workspace, "ResEurope" ) &&
       0 == Build::Gen( $args, "Release", $args->workspace, "ResDll" ) ) {
      my $srcResDll = $args->targetdir."ifastgui\\resdll\\release\\resdll.dll";
      my $destResDll = $args->targetdir."bin\\release\\lux_eng.dll";
      $rc = copy( $srcResDll, $destResDll );
   }
   if( 0 == Build::Gen( $args, "Release", $args->workspace, "ResCommonFr" ) &&
       0 == Build::Gen( $args, "Release", $args->workspace, "ResCanadaFr" ) &&
       0 == Build::Gen( $args, "Release", $args->workspace, "ResDllFr" ) ) {
      my $srcResDll = $args->targetdir."ifastgui\\resdllfr\\release\\resdll_fr.dll";
      my $destResDll = $args->targetdir."bin\\release\\canada_fr.dll";
      $rc = copy( $srcResDll, $destResDll );

   }
   if( 0 == Build::Gen( $args, "Release", $args->workspace, "ResCanada" ) &&
       0 == Build::Gen( $args, "Release", $args->workspace, "ResDll" ) ) {
      my $srcResDll = $args->targetdir."ifastgui\\resdll\\release\\resdll.dll";
      my $destResDll = $args->targetdir."bin\\release\\canada_eng.dll";
      $rc = copy( $srcResDll, $destResDll );

   }
   $rcBuild = Build::Gen( $args, "Release", $args->workspace, $project );


#   if( 0 == $rcBuild ) {
#      # now run ant for ifastjd project
#      Build::Status( $args, q{ifastjd} );
#      chdir( $args->targetdir );
#      my $cmd = q{ant -f build.xml release};
#      Build::Notify( $args, q{Using ant on ifastjd project} );
#      $rc = system($cmd);
#      if( 0 != ($rc / 256) ) {
#         # error running ant
#         Build::NotifyAndDie( args, q{Error running ant: }.($rc/256) );
#      }
#      Build::Status( $args );
#   }

}

sub BrandUCS2LEResource {
   my( $args, $rcFile ) = @_;
   my $gl = $args->pvcs_version;

   my $base = '';
   my @version = ();
   $version[0] = 0;
   $version[1] = 0;
   $version[2] = 0;
   $version[3] = 0;
   
   my $rfcNumber = 0;
   
   my $versionType = 0;
   
   # $args->addMessage( "\n" );
   # $args->addMessage( "Branding binary resource file...\n" );
   # $args->addMessage( "using version as " . $gl . " \n" );
   # $args->addMessage( "current working directory is " . $cwd . " \n" );

   if ( $gl =~ /Rel_(\d+)\.(\d+)\.(\d+)\.(\d+) */ ) {
      # Version label of form Rel_54.0.0.0
      $base = "Rel_";
      $version[0] = $1;
      $version[1] = $2;
      $version[2] = $3;
      $version[3] = $4;
      $versionType = 1;
      $args->addMessage( "version type is " . "$versiontype" . "\n" );
   } elsif ( $gl =~ /Rel_(\d+)\.(\d+)\.(\d+) */ ) {
      # Version label of form Rel_54.0.0
      $base = "Rel_";
      $version[0] = $1;
      $version[1] = $2;
      $version[2] = $3;
      $version[3] = "0";
      $versionType = 2;
   } elsif ( $gl =~ /Rel_(\d+)\.(\d+) */ ) {
      # Version label of form Rel_54.0
      $base = "Rel_";
      $version[0] = $1;
      $version[1] = $2;
      $versionType = 3;
   } elsif ( $gl =~ /fbps-(\d+)\.(\d+)-(\d+) */ ) {
      # Version label of form fbps-8.25-3504
      $base = "fbps-";
      $version[0] = $1;
      $version[1] = $2;
      $version[2] = '0';
      $version[3] = $3;
      $versionType = 4;
   } elsif ( $gl =~ /fbps-(\d+)\.(\d+)\.(\d+)-(\d+) */ ) {
      # Version label of form fbps-8.25.01-3504
      $base = "fbps-";
      $version[0] = $1;
      $version[1] = $2;
      $version[2] = $3;
      $version[3] = $4;
      $versionType = 5;
   } elsif ( $gl =~ /FAST_(\d+)\.(\d+)\.(\d+)\.(\d+) */ ) {
      # Version label of form iFAST_2.13.1.1
      $base = "FAST_";
      $version[0] = $1;
      $version[1] = $2;
      $version[2] = $3;
      $version[3] = $4;
      $versionType = 6;
   } elsif ( $gl =~ /FAST_(\d+)\.(\d+)\.(\d+) */ ) {
      # Version label of form iFAST_2.13.1
      $base = "FAST_";
      $version[0] = $1;
      $version[1] = $2;
      $version[2] = $3;
      $versionType = 7;
   } elsif ( $gl =~ /FAST_(\d+)\.(\d+) */ ) {
      # Version label of form iFAST_2.13
      $base = "FAST_";
      $version[0] = $1;
      $version[1] = $2;
      $versionType = 8;
   } elsif ( $gl =~ /RFC(\d+)\_PREREL_(\d+)\.(\d+)\.(\d+)\.(\d+) */ ) {
      $base = "RFC";
      $rfcNumber  = $1;
      $version[0] = $2;
      $version[1] = $3;
      $version[2] = $4;
      $version[3] = $5;
      $versionType = 9;
   } elsif ( $gl =~ /RFC(\d+)\_PREREL_(\d+)\.(\d+)\.(\d+) */ ) {
      $base = "RFC";
      $rfcNumber  = $1;
      $version[0] = $2;
      $version[1] = $3;
      $version[2] = $4;
      $version[3] = '0';
      $versionType = 10;   
   } else {
      # don't brand anything ... the version string is in the wrong format
      return;
   }

   if( 1 == open( RESOURCE, "<:raw", $rcFile ) ) {
      local $/;
      my $binResource = <RESOURCE>;
      close( RESOURCE );

      my $OrigFILEVERSION = " FILEVERSION 3,2,0,0";
      my $ucOrigFILEVERSION = MakeUCSString($OrgFILEVERSION,30);
      
      my $NewFILEVERSION = " FILEVERSION " . $version[0] . "," . $version[1] . "," . $version[2] . "," . $version[3];
      my $ucNewFILEVERSION = MakeUCSString($NewFILEVERSION,30);
      
      my $OrigPRODUCTVERSION = " PRODUCTVERSION 3,2,0,0";
      my $ucOrigPRODUCTVERSION = MakeUCSString($OrgPRODUCTVERSION,30);
      
      my $NewPRODUCTVERSION = " PRODUCTVERSION " . $version[0] . "," . $version[1] . "," . $version[2] . "," . $version[3];
      my $ucNewPRODUCTVERSION = MakeUCSString($NewPRODUCTVERSION,30);
      
      my $OrigValueFileVer1 = "            VALUE \"FileVersion\", \"93.0.0.0\"";
      my $ucOrigValueFileVer1 = MakeUCSString($OrigValueFileVer1,30);
      
      my $OrigValueProductVer1 = "            VALUE \"ProductVersion\", \"93.0.0.0\"";
      my $ucOrigValueProductVer1 = MakeUCSString($OrigValueProductVer1,30);
      
      my $OrigValueFileVer2 = "            VALUE \"FileVersion\", \"1, 0, 0, 1\"";
      my $ucOrigValueFileVer2 = MakeUCSString($OrigValueFileVer2,30);
      
      my $OrigValueProductVer2 = "            VALUE \"ProductVersion\", \"1, 0, 0, 1\"";
      my $ucOrigValueProductVer2 = MakeUCSString($OrigValueProductVer2,30);
      
      my $NewValueFileVer1 = "            VALUE \"FileVersion\", \"" . $version[0] . "." . $version[1] . "." . $version[2] . "." . $version[3] . "\"";
      my $ucNewValueFileVer1 = MakeUCSString($NewValueFileVer1,30);
      
      my $NewValueProductVer1 = "            VALUE \"ProductVersion\", \"" . $version[0] . "." . $version[1] . "." . $version[2] . "." . $version[3] . "\"";
      my $ucNewValueProductVer1 = MakeUCSString($NewValueProductVer1,30);
      
      my $NewValueFileVer2 = "            VALUE \"FileVersion\", \"" . $version[0] . "," . $version[1] . "," . $version[2] . "," . $version[3] . "\"";
      my $ucNewValueFileVer2 = MakeUCSString($NewValueFileVer2,30);
      
      my $NewValueProductVer2 = "            VALUE \"ProductVersion\", \"" . $version[0] . "," . $version[1] . "," . $version[2] . "," . $version[3] . "\"";
      my $ucNewValueProductVer2 = MakeUCSString($NewValueProductVer2,30);

      $binResource =~ s/$ucOrigFILEVERSION/$ucNewFILEVERSION/g;
      $binResource =~ s/$ucOrigPRODUCTVERSION/$ucNewPRODUCTVERSION/g;
      $binResource =~ s/$ucOrigValueFileVer1/$ucNewValueFileVer1/g;
      $binResource =~ s/$ucOrigValueProductVer1/$ucNewValueProductVer1/g;
      $binResource =~ s/$ucOrigValueFileVer2/$ucNewValueFileVer2/g;
      $binResource =~ s/$ucOrigValueProductVer2/$ucNewValueProductVer2/g;

      my $rc2;

      chmod( 0666, $rcFile );
      $rc2 = open( RESOURCE, ">:raw", $rcFile );

      if( 0 == $rc2 ) {
         Build::Notify( $rcfile, "*** Error creating new $rcFile file ***\n$!\n" );
      }
      else
      {
        $args->addMessage( "overwrite file\n" );
         print RESOURCE $binResource;
         close( RESOURCE );
      }

      chmod( 0444, $rcFile );

   } else {
      print "Could not read $rcFile for output: $!\n";
   }
}

sub BrandASCIIResource {
   my( $args, $rcFile ) = @_;
   my $gl = $args->pvcs_version;

   my $base = '';
   my @version = ();
   $version[0] = 0;
   $version[1] = 0;
   $version[2] = 0;
   $version[3] = 0;

   if ( $gl =~ /Rel_(\d+)\.(\d+)\.(\d+)\.(\d+) */ ) {
      # Version label of form Rel_54.0.0.0
      $base = "Rel_";
      $version[0] = $1;
      $version[1] = $2;
      $version[2] = $3;
      $version[3] = $4;
   } elsif ( $gl =~ /Rel_(\d+)\.(\d+)\.(\d+) */ ) {
      # Version label of form Rel_54.0.0
      $base = "Rel_";
      $version[0] = $1;
      $version[1] = $2;
      $version[2] = $3;
   } elsif ( $gl =~ /Rel_(\d+)\.(\d+) */ ) {
      # Version label of form Rel_54.0
      $base = "Rel_";
      $version[0] = $1;
      $version[1] = $2;
   } elsif ( $gl =~ /fbps-(\d+)\.(\d+)-(\d+) */ ) {
      # Version label of form fbps-8.25-3504
      $base = "fbps-";
      $version[0] = $1;
      $version[1] = $2;
      $version[2] = '0';
      $version[3] = $3;
   } elsif ( $gl =~ /fbps-(\d+)\.(\d+)\.(\d+)-(\d+) */ ) {
      # Version label of form fbps-8.25.01-3504
      $base = "fbps-";
      $version[0] = $1;
      $version[1] = $2;
      $version[2] = $3;
      $version[3] = $4;
   } elsif ( $gl =~ /FAST_(\d+)\.(\d+)\.(\d+)\.(\d+) */ ) {
      # Version label of form iFAST_2.13.1.1
      $base = "FAST_";
      $version[0] = $1;
      $version[1] = $2;
      $version[2] = $3;
      $version[3] = $4;
   } elsif ( $gl =~ /FAST_(\d+)\.(\d+)\.(\d+) */ ) {
      # Version label of form iFAST_2.13.1
      $base = "FAST_";
      $version[0] = $1;
      $version[1] = $2;
      $version[2] = $3;
   } elsif ( $gl =~ /FAST_(\d+)\.(\d+) */ ) {
      # Version label of form iFAST_2.13
      $base = "FAST_";
      $version[0] = $1;
      $version[1] = $2;
   } elsif ( $gl =~ /RFC(\d+)\_PREREL_(\d+)\.(\d+)\.(\d+)\.(\d+) */ ) {
      $base = "RFC";
      $rfcNumber  = $1;
      $version[0] = $2;
      $version[1] = $3;
      $version[2] = $4;
      $version[3] = $5;
   } elsif ( $gl =~ /RFC(\d+)\_PREREL_(\d+)\.(\d+)\.(\d+) */ ) {
      $base = "RFC";
      $rfcNumber  = $1;
      $version[0] = $2;
      $version[1] = $3;
      $version[2] = $4;
      $version[3] = '0';
   } else {
      # don't brand anything ... the version string is in the wrong format
      return;
   }

   # my $tmpFile = File::Spec->tmpdir() ."\\". mktemp("vrXXXXX");
   my $tmpFile = File::Spec->tmpdir() ."\\". tmpnam("vrXXXXX");
   # my $tmpFile = File::Spec->tmpdir() ."\\". IO::File::new_tmpfile("vrXXXXX");
   my $rc = open( TMP, ">$tmpFile" );
   if( 1 == $rc ) {
      # read the resource file in and rewrite the lines as appropriate
      if( 1 == open( RESOURCE, $rcFile ) ) {
         while( <RESOURCE> ) {
            chomp;
            if ( /^( *)FILEVERSION (\d+),(\d+),(\d+),(\d+) *$/ ) {
               $_ = "${1}FILEVERSION $version[0],$version[1],$version[2],$version[3]";
            } elsif ( /^( *)PRODUCTVERSION (\d+),(\d+),(\d+),(\d+) *$/ ) {
               $_ = "${1}PRODUCTVERSION $version[0],$version[1],$version[2],$version[3]";
            } elsif ( /^( *)VALUE "FileVersion", "(\d+)\.(\d+)\.(\d+)\.(\d+)\\0" *$/ ) {
               $_ = "${1}VALUE \"FileVersion\", \"$version[0].$version[1].$version[2].$version[3]\\0\"";
            } elsif ( /^( *)VALUE "FileVersion", "(.*)\\0" *$/ ) {
               $_ = "${1}VALUE \"FileVersion\", \"$gl\\0\"";
            } elsif ( /^( *)VALUE "ProductVersion", "(\d+)\.(\d+)\.(\d+)\.(\d+)\\0" *$/ ) {
               $_ = "${1}VALUE \"ProductVersion\", \"$version[0].$version[1].$version[2].$version[3]\\0\"";
            } elsif ( /^( *)VALUE "ProductVersion", "(.*)\\0" *$/ ) {
               $_ = "${1}VALUE \"ProductVersion\", \"$gl\\0\"";
            }
            print TMP "$_\n";
         }
         close( RESOURCE );
         close( TMP );

         my $rc;
         $rc = chmod( 0666, "$rcFile" );
         # copy temp version file onto real one
         $rc = copy( $tmpFile, $rcFile );

         if( 0 == $rc ) {
            Build::Notify( $args, "*** Error creating new $rcFile file ***\n$!\n" );
         }
         open( TMP, $tmpFile );  # we always want to be able to close the TMP file
                                 # outside this loop, so just reopen it for reading
                                 # so the close below works!
      }
      close( TMP );
      unlink( $tmpFile );
   }
}

sub MakeUCSString {
   my( $srcString, $totalSize ) = @_;
  
   my $i = 0;
   
   my $dstString = "";
   foreach $char (split //, $srcString) {
      $dstString .= $char . "\0";
      ++$i;
   }
   for( ; $i < $totalSize; ++$i ) { $dstString .= " \0"; }
   
   return $dstString;
}
