/*******************************************************************************
 *
 * COPYRIGHT:
 *
 *    The computer systems, procedures, data bases and
 *    programs created and maintained by DST Systems, Inc.,
 *    are proprietary in nature and as such are confidential.
 *    Any unauthorized use or disclosure of such information
 *    may result in civil liabilities.
 *
 *    Copyright 2000 by DST Systems, Inc.
 *
*******************************************************************************/
#include "stdafx.h"
#include "ConditionWriter.hpp"
#include "SeverityAttribute.hpp"

using namespace xp;

namespace
{
   const DString STR_CONDITION   = I_( "Condition" );
   const DString STR_CODE        = I_( "Code" );
   const DString STR_COMPONENT   = I_( "Component" );
   const DString STR_MESSAGE     = I_( "Message" );
   const DString STR_CORRECTION  = I_( "Correction" );
   const DString STR_FILE        = I_( "File" );
   const DString STR_LINE        = I_( "Line" );
   const DString STR_METHOD      = I_( "Method" );
}

bool ConditionWriter::s_alternateStyle = false;

//******************************************************************************
ConditionWriter::ConditionWriter( const Condition& condition, BFDocument &out, bool verbose /* = false */ )
: ElementWriter ( out, STR_CONDITION, SeverityAttribute(condition.getSeverity()) )
, _condition( condition )
, _verbose( verbose )
{
}

//******************************************************************************
ConditionWriter::~ConditionWriter()
{
}

//******************************************************************************
void ConditionWriter::writeBody()
{
   if( s_alternateStyle )
   {
      writeComponent();
      writeShortCode();
   }
   else
   {
      writeUniqueCode();
   }

   writeMessage();
   writeCorrection();

   if( _verbose )
   {
      writeFile();
      writeMethod();
      writeLine();
   }
}

//******************************************************************************
void ConditionWriter::writeCode()
{
   ElementWriter::write( getOutputDoc(), STR_CODE, DString::asString(_condition.getCode()) );
}

//******************************************************************************
void ConditionWriter::writeShortCode()
{
   DString dstrCode = DString::asString( _condition.getCode() );
   if( /*_condition.getCode() >= 40000000 ||*/
       I_( 'F' ) == _condition.getComponentName()[0] ) 
   {
      // FAST Conditions should have the 40000000 stripped off.
      // FAST Conditions are those with a module which starts with F.  This is not *strictly* 
      // speaking 'true' (or even loosely speaking), but Paul Ives wants this fixed pronto and
      // we don't have any other way of fixing it quickly.
      //     CP 15Oct2003
      dstrCode = dstrCode.stripAll().substr( 1, dstrCode.length() );
      dstrCode = DString( DString::asString( dstrCode.asInteger() ) );
   }
   ElementWriter::write( getOutputDoc(), STR_CODE, dstrCode );
}

//******************************************************************************
void ConditionWriter::writeUniqueCode()
{
   DString uniqueCode( _condition.getComponentName() );
   uniqueCode += I_(" - ") + asString( _condition.getCode() );

   ElementWriter::write( getOutputDoc(), STR_CODE, uniqueCode );
}

//******************************************************************************
void ConditionWriter::writeComponent()
{
   ElementWriter::write( getOutputDoc(), STR_COMPONENT, _condition.getComponentName() );
}

//******************************************************************************
void ConditionWriter::writeMessage()
{
   ElementWriter::write( getOutputDoc(), STR_MESSAGE, _condition.getMessage());
}

//******************************************************************************
void ConditionWriter::writeCorrection()
{
   // a little much this line, however...
   DString correction = DString(_condition.getCorrection()).strip();

   if( correction != NULL_STRING )
      ElementWriter::write( getOutputDoc(), STR_CORRECTION, correction );

}

//******************************************************************************
void ConditionWriter::writeFile()
{
   ElementWriter::write( getOutputDoc(), STR_FILE, DStringA( _condition.getFileName() ) );
}

//******************************************************************************
void ConditionWriter::writeMethod()
{
   ElementWriter::write( getOutputDoc(), STR_METHOD, _condition.getMethodName());
}

//******************************************************************************
void ConditionWriter::writeLine()
{
   ElementWriter::write( getOutputDoc(), STR_LINE, asString( _condition.getLineNumber() ) );
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF Core/xparser/ConditionWriter.cpp-arc  $
//
//   Rev 1.13   Mar 05 2004 13:28:24   SMITHDAV
//Fix stupid class initialization bugs.
//
//   Rev 1.12   Mar 02 2004 10:56:10   SMITHDAV
//Change element writers to make them mor robust.
//
//   Rev 1.11   Oct 15 2003 14:32:58   PURDYECH
//Change writeShortCode() so that it decides if the 40000000 should be stripped off solely by the first letter of the component name (!!!)
//
//   Rev 1.10   Sep 03 2003 11:42:50   PURDYECH
//writeShortCode should only trim off the code differentiating value (e.g. 40,000,000) if the code is application specific.  Core conditions should continue to display their full value.
// 
//    Rev 1.9   Oct 09 2002 17:43:12   PURDYECH
// New PVCS Database
// 
//    Rev 1.8   Sep 19 2002 09:28:34   IVESPAUL
// Adapted the transaction stats to write results using XML ElementWriter.  Moved ElementAttribute and ElementWriter to BFUtil.
//
//    Rev 1.7   Sep 18 2002 14:12:00   IVESPAUL
// Changed alternate condition style.
//
//    Rev 1.6   Sep 11 2002 16:04:10   SMITHDAV
// An alternate style of condition has been added for the purposes  of FAST. We use a static settable to invoke the behaviour instead of a more complex project specific specialization technique because, we do not want to support many variations.
//
//    Rev 1.5   Sep 11 2002 14:19:02   SMITHDAV
// Temporary change to meet FAST condition needs.
//
//    Rev 1.4   Aug 02 2002 17:13:38   SMITHDAV
// Major EBF to deal with post-commit data outputs using abstract document model and random access document implementation.
//
//    Rev 1.3   07 Jun 2002 17:08:56   SMITHDAV
// Add support for root level attributes to turn on statistics writing and verbose conditions.
//
//    Rev 1.2   14 May 2002 16:42:54   SMITHDAV
// put xparser code namespace xp.
//
//    Rev 1.1   01 May 2002 17:16:46   SMITHDAV
// Simple writer changes. Add TxnStats. And Fix key handling for CBO add and replace ations.
//
//    Rev 1.0   02 Apr 2002 13:50:04   SMITHDAV
// Initial revision.
 *
 */
