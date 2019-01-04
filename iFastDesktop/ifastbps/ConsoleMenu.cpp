//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 1999 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   :  ConsoleMenu.cpp
// ^AUTHOR :  David Smith
// ^DATE   :  December 2000
//
// ----------------------------------------------------------
#include "stdafx.h"

#include <SrcPrag.h>
#include "ConsoleMenu.hpp"
#include <bfutil\Console.hpp>
#include <bfutil\ConsoleCanvas.hpp>
#include <bfutil\version_core.hpp>
#include <ifastcbo\version_app.hpp>

ConsoleMenu::ConsoleMenu()
{
   pCanvas_ = Console::getInstance()->createCanvas(4);

   // key command menu
   pCanvas_->write( 0, 0, ConsoleColor::BLACK, ConsoleColor::BRIGHT_WHITE, "Key Commands:" );

   pCanvas_->write( 4, 1, "<M> - toggle display modes" );
   pCanvas_->write( 4, 2, "<X> - shutdown" );
   pCanvas_->write( 4, 3, "<T> - toggle console tracing" );


   // resource legend
   pCanvas_->write( 44, 0, ConsoleColor::BLACK, ConsoleColor::BRIGHT_WHITE, "Resource Legend:" );

   pCanvas_->write( 47, 1, "  Active Resource" ); 
   pCanvas_->highlight( 47, 1, 1, ConsoleColor::GREEN, ConsoleColor::BLACK );

   pCanvas_->write( 47, 2, "  Inactive Resource" );
   pCanvas_->highlight( 47, 2, 1, ConsoleColor::DARK_GREEN , ConsoleColor::BLACK );

   pCanvas_->write( 47, 3, "  Resource Potential" );
   pCanvas_->highlight( 47, 3, 1, ConsoleColor::CYAN , ConsoleColor::BLACK );

   pCanvas_->update();
}


ConsoleMenu::~ConsoleMenu()
{
   delete pCanvas_;
}

ConsoleAppInfo::ConsoleAppInfo( const DString &appDesc ) : pCanvas_( NULL ) {

   pCanvas_ = Console::getInstance()->createCanvas( 3 );
   pCanvas_->write( 0, 0, ConsoleColor::BLACK, ConsoleColor::BRIGHT_WHITE, "Instance Descr: " );
   pCanvas_->write( 0, 1, ConsoleColor::BLACK, ConsoleColor::BRIGHT_WHITE, "App Version: " );
   pCanvas_->write( 0, 2, ConsoleColor::BLACK,  ConsoleColor::BRIGHT_WHITE, "Core Version: " );

   DStringA dstrCoreVer = 
      DStringA( ifds::getCoreVersion() ) +
      " bld" + 
      DStringA::asString( ifds::getCoreBuildNumber() ) + 
      "@" + 
      DStringA( ifds::getCoreBuildComputer() );

   DStringA dstrAppVer = 
      DStringA( ifds::getAppVersion() ) +
      " bld" + 
      DStringA::asString( ifds::getAppBuildNumber() ) + 
      "@" + 
      DStringA( ifds::getAppBuildComputer() );

   pCanvas_->write( 17, 0, appDesc.asA().c_str() );
   pCanvas_->write( 17, 1, dstrAppVer.c_str() );
   pCanvas_->write( 17, 2, dstrCoreVer.c_str() );

   pCanvas_->update();
}

ConsoleAppInfo::~ConsoleAppInfo() {
   delete pCanvas_;
}



