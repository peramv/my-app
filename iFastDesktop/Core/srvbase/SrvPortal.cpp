#include "stdafx.h"
#include "srvportal.hpp"
#include <bfutil\bfguard.hpp>
#include <bf\log\log.hpp>

SrvPortal::SrvPortal( const DString &name, BFJobQueue *jobQ, int threadCount ) 
: jobQ_( jobQ )
, name_( name )
, threadCount_( threadCount )
, threadPool_( NULL )
, csRequestCount_()
, cRequests_(0)
{
}

SrvPortal::~SrvPortal() {
}

void SrvPortal::close() {
   delete threadPool_;
   threadPool_ = NULL;
   wait();
   bf::log::theLog << bf::log::information << name_ << I_( " exited..." ) << bf::log::endlf;
}

void SrvPortal::run() {
   threadPool_ = new BFThreadPool( name_, jobQ_, threadCount_ );

   while ( run( threadPool_ ) ) {
      optimizeThreadPool( threadPool_ );
   }
   bf::log::theLog << bf::log::information << name_ << I_( " no longer processing requests..." ) << bf::log::endlf;
}

unsigned int SrvPortal::getRequestCount() const {
   BFGuard g( csRequestCount_ );
   return( cRequests_ );
}

void SrvPortal::incrementRequestCount() {
   BFGuard g( csRequestCount_ );
   ++cRequests_;
}

