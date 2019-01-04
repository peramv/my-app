#include "stdafx.h"

#include "BFIPBlast.hpp"
#include "BFCritSec.hpp"
#include "BFGuard.hpp"

#include <fstream>

static BFCritSec g_cs;

BFIPBlast* BFIPBlast::s_pInstance_ = NULL;

BFIPBlast* BFIPBlast::getInstance()
{
   BFGuard g( g_cs );
   if( NULL == s_pInstance_ )
   {
      s_pInstance_ = new BFIPBlast();
   }
   return( s_pInstance_ );
}

void BFIPBlast::killInstance()
{
   BFGuard g( g_cs );
   delete s_pInstance_;
   s_pInstance_ = NULL;
}

BFIPBlast::BFIPBlast()
: fileName_( I_( "" ) )
, pFile_( NULL)
, iBuf_( 0 )
{
}

BFIPBlast::~BFIPBlast()
{
   BFGuard g( cs_ );

   if( NULL != pFile_ )
   {
      // write out the transaction records
      *pFile_ << std::endl;
      *pFile_ << "begin init" << std::endl;
      *pFile_ << "end init" << std::endl;
      *pFile_ << std::endl;
      *pFile_ << "begin body" << std::endl;
      TXNMAP_ITER iter = mapTxn_.begin();
      TXNMAP_ITER iterEnd = mapTxn_.end();

      DStringA dstrLastTxnName("");
      int iTxn = 0;
      for( ; iter != iterEnd; ++iter )
      {
         const DStringA& dstrTxnName = (*iter).first;
         DStringA& dstrBufferName = (*iter).second;
         if( dstrTxnName != dstrLastTxnName )
         {
            dstrLastTxnName = dstrTxnName;
            iTxn = 0;
         }
         *pFile_ << "\t;transact " << dstrTxnName.c_str() << ++iTxn << " " << dstrBufferName << std::endl;
      }

      *pFile_ << "end body" << std::endl;
      *pFile_ << std::endl;
      *pFile_ << "begin term" << std::endl;
      *pFile_ << "end term" << std::endl;
      *pFile_ << std::endl;

      delete pFile_;
   }
}

int BFIPBlast::setFile( const char *pszFile )
{

   if( pFile_ == NULL )
   {
      BFGuard g( cs_ );
      fileName_ = pszFile;
      pFile_ = new std::ofstream( pszFile );
      if( pFile_->fail() )
      {
         delete pFile_;
         pFile_ = NULL;
         return( -1 );
      }
      *pFile_ << "; IPBlast Script file" << std::endl;
      *pFile_ << std::endl;
      *pFile_ << ";define parmBegin [" << std::endl;
      *pFile_ << ";define parmTerm ]" << std::endl;
      *pFile_ << std::endl;
      *pFile_ << ";Request Buffers" << std::endl;
   }
   return( 0 );
}

int BFIPBlast::writeBuffer( const DString &name, const DString &buffer )
{
   if( NULL == pFile_ )
   {
      return( -1 );     // file not open!
   }

   BFGuard g( cs_ );
   ++iBuf_;

   *pFile_ << "; Request Name = " << name.asA().c_str() << std::endl;
   DStringA dstrBufferName;
   dstrBufferName = "buf" + DStringA::asString( iBuf_ );
   *pFile_ << "begin buf " << dstrBufferName.c_str() << std::endl;
   DString dstrChunk;
   int iBegin = 0;
   while( iBegin != buffer.npos )
   {
      int iNL = buffer.find( '\n', iBegin );
      if( iNL != buffer.npos )
      {
         dstrChunk = buffer.substr( iBegin, iNL - iBegin - 1);
         iBegin = ++iNL;
      }
      else
      {
         dstrChunk = buffer.substr( iBegin );
         iBegin = iNL;
      }
      if( !dstrChunk.empty() )
      {
         *pFile_ << "\t\"" << dstrChunk.asA().c_str() << "\"" << std::endl;
      }
   }
   *pFile_ << "end buf" << std::endl;
   *pFile_ << std::endl;

   if( mapTxn_.end() == mapTxn_.insert( TXNMAP::value_type( name, dstrBufferName ) ) )
   {
      i_cout << I_( "Whoop! Whoop! Whoop!" ) << std::endl;
   }
   return( 0 );
}


