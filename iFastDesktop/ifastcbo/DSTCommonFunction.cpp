// DSTCommonFunction.cpp: implementation of the DSTCommonFunction class.
//////////////////////////////////////////////////////////////////////
#define IFASTCBO_DLL
#include "stdafx.h"
#include <math.h>
#include "dstcommonfunction.hpp"
#include <bfutil\bfdate.hpp>
#include <bfdata\bfdata.hpp>
#include <bfdata\bfdatafield.hpp>

#include <ifastdataimpl\dse_dstc0052_vw.hpp>
#include <ifastdataimpl\dse_currency_vw.hpp>
#include <boost\scoped_ptr.hpp>
#include <bfdata\bfdatafieldfactory.hpp>
#include <bfdata\bfdatafieldproperties.hpp>
#include <bfdata\bfmask.hpp>
#include <bfutil/localetraits.hpp>

namespace ifds
{
   extern CLASS_IMPORT const BFDateFieldId CurrBusDate;
   extern CLASS_IMPORT const BFDataFieldProperties s_FldProp_USDollar;
   extern CLASS_IMPORT const BFDecimalFieldId Amount;
}

namespace MARKET_IDS
{
   extern CLASS_EXPORT I_CHAR * const CANADA       = I_( "Canada" );
   extern CLASS_EXPORT I_CHAR * const JAPAN        = I_( "Japan" );
   extern CLASS_EXPORT I_CHAR * const LUXEMBOURG   = I_( "Lux" );
}

namespace DSTCommonFunctions
{
   int nNoOfDaysOfMonth[] =  
   {
      0,31,28,31,30,31,30,31,31,30,31,30,31
   };

   //******************************************************************************
   DString getMarket()
   {
/*
      ConfigManager* theMgr = ConfigManager::getManager( I_( "DataBroker" ) );
      Configuration theConfig = theMgr->retrieveConfig( I_( "Market" ) );
      DString dstrMarket = theConfig.getValueAsString( I_( "Market" ) );
*/
      DString dstrMarket = GetConfigValueAsString( I_("Market"), I_("Market") );
      if( dstrMarket == I_( "" ) )
      {
         dstrMarket = I_( "No Market" );
      }
      return( dstrMarket );

   }

   //******************************************************************************
   DString getClient()
   {
/*
      ConfigManager* theMgr = ConfigManager::getManager( I_( "DataBroker" ) );
      Configuration theConfig = theMgr->retrieveConfig( I_( "Market" ) );
      DString dstrMarket = theConfig.getValueAsString( I_( "Client" ) );
*/
      DString dstrClient = GetConfigValueAsString(I_("Market"), I_("Client"));
      if( dstrClient == I_( "" ) )
      {
         dstrClient = I_( "No Client" );
      }
      return( dstrClient );

   }
   //******************************************************************************
   DString getMask( const BFFieldId& idField )
   {
      const BFDataFieldProperties* pProps = BFDataFieldProperties::get( idField );
      const BFMask* pMask = pProps->getMask( ClientLocaleContext::get() );
      if( NULL == pMask )
      {
         return( I_( "" ) );
      }
      DString mask = pMask->getMask();
      return( I_("(") + mask + I_(")") );
   }

   //******************************************************************************
   DString getRawMask( const BFFieldId& idField )
   {
      const BFDataFieldProperties* pProps = BFDataFieldProperties::get( idField );
      const BFMask* pMask = pProps->getMask( ClientLocaleContext::get() );
      if( NULL == pMask )
      {
         return( I_( "" ) );
      }
      return( pMask->getMask() );
   }

   //******************************************************************************
   DString getMask( const BFFieldId& idField, const DString& local )
   {
      throw "What a mess!";
   }

   //******************************************************************************
   bool isStringEmptyOrJustContainSpace( const DString& str )
   {
      if( str == NULL_STRING )
      {
         return( true );
      }
      DString tmp( str );
      return( tmp.strip() == NULL_STRING );
   }

   //******************************************************************************
   bool codeInList( const DString& dstrCode, const DString& dstrCodeList, bool bStripTrailingZeros /*= false*/) 
   {
      if( bStripTrailingZeros )
      {
         DString strCopyCodeList = dstrCodeList;
         strCopyCodeList.strip();
         DString strCopyCode = dstrCode;
         strCopyCode.strip().stripLeading('0');
         int nPos = strCopyCodeList.find(',');
         DString strFirstWord = NULL_STRING;
         if( nPos != DString::npos )//a hit
            strFirstWord = strCopyCodeList.left(nPos + 1).stripLeading('0');
         else
            strFirstWord = strCopyCodeList.stripLeading('0');

         strFirstWord.stripAll(',');
         if( strFirstWord == strCopyCode )
            return(true);
         else
         {
            if( nPos != DString::npos )
            {
               DString strRestOfList;
               strRestOfList =  strCopyCodeList.right(strCopyCodeList.length() -1 - nPos);
               return(codeInList(dstrCode, strRestOfList, true));
            }
            else
               return(false);
         }
      }

      DString codeList = I_( "," ) + dstrCodeList + I_( "," );

      DString testCode = I_( "," ) + dstrCode + I_( "," );

      bool bCodeInList = (codeList.find(testCode) != DString::npos);

      return(bCodeInList);

   }

   //******************************************************************************
   DString getDescription( const DString& strCode, const DString& strSubstList )
   {
      DString strDescription, strCopyOfSubstList(strSubstList);
      //add ';' to the beginning of the list
      strCopyOfSubstList = I_(";") + strCopyOfSubstList;

      //construct a specific string to search the code in list
      DString strTemp = I_(";") + strCode + I_("=");

      int iPosition = strCopyOfSubstList.find( strTemp );
      if( iPosition == DString::npos )
      {  //the code is not in list or
         //the list don't conform to the pattern for subst. list: "code=description;code=description;..."
         return(NULL_STRING);
      }

      //position at the begining of description substring
      iPosition = iPosition + strTemp.length();

      int iPositionEnd;
      iPositionEnd = strCopyOfSubstList.find( I_(";"), iPosition );
      if( iPositionEnd == DString::npos )
      {  //reach the end of strSubstList
         iPositionEnd = strCopyOfSubstList.length();
      }

      strDescription = strCopyOfSubstList.substr( iPosition, iPositionEnd - iPosition );
      return(strDescription);
   }

   //******************************************************************************
   DString getDescription( const DString& strCode, const BFFieldId& idField )
   {
      DString strAllSubstList;

      const BFDataFieldProperties* pProps = BFDataFieldProperties::get( idField );

      pProps->getAllSubstituteValues( strAllSubstList, ClientLocaleContext::get() );

      if( strAllSubstList.empty() )
      {
         assert(0);  //substitution list for this field is empty
         return(NULL_STRING);
      }

      return(getDescription( strCode, strAllSubstList ));
   }

   //******************************************************************************
   int NumOfDecimals(const DString& Amount)
   {
      DString str( Amount );
      const bfutil::LocaleTraits& localeTraits = bfutil::LocaleTraits::get( ClientLocaleContext::get() );
      I_CHAR RadixSeparator = localeTraits.getRadixSeparator();

      str.strip();
      if (str.find(RadixSeparator/*I_(".")*/) == DString::npos)
      {
         return(0);
      }
      str.stripTrailing('0');

      int i = str.find(RadixSeparator); //I_(".") );

      return (!i) ? 0 : str.size() - i - 1;
   }

   //******************************************************************************
   double convertToDouble(const DString& Amount)
   {
      DString dstrAmount;

      dstrAmount = Amount;
	  
	  const bfutil::LocaleTraits& localeTraits = bfutil::LocaleTraits::get( ClientLocaleContext::get() );
	  I_CHAR Groupseparator = localeTraits.getGroupSeparator();
	  
	  //check if is default format
	    DString dstrRadixSeparatorE, dstrGroupseparatorE;
	    dstrRadixSeparatorE = localeTraits.getRadixSeparator();
	    dstrGroupseparatorE = localeTraits.getGroupSeparator();
		int posGE = dstrAmount.find(dstrGroupseparatorE);
		int posRE = dstrAmount.find(dstrRadixSeparatorE);
		bool _bDispE = ( posRE > 0 ) && ( posGE < posRE );
		if( !_bDispE ) DisplayUnFormat( dstrAmount, ifds::Amount );
	  //end check

      dstrAmount.strip().stripAll( Groupseparator );	//I_CHAR( ',' ) );          
      double dec_amount = atof(dstrAmount.asA().c_str());

      return(dec_amount);
   }

   //******************************************************************************
   BigDecimal convertToBigDecimal(const DString& Amount)
   {
      DString dstrAmount, dstrUnformatedAmount;

      dstrAmount = Amount;
      dstrAmount.strip();

      // now we use unformat from amount,
      BFDataField::unformatValue( ifds::Amount, dstrAmount, true );
      dstrAmount.strip();

      const bfutil::LocaleTraits& localeTraits = bfutil::LocaleTraits::get( ClientLocaleContext::get() );
      I_CHAR Groupseparator = localeTraits.getGroupSeparator();

      //check if is default format
      DString dstrRadixSeparatorE, dstrGroupseparatorE;
      dstrRadixSeparatorE = localeTraits.getRadixSeparator();
      dstrGroupseparatorE = localeTraits.getGroupSeparator();
      int posGE = dstrAmount.find(dstrGroupseparatorE);
      int posRE = dstrAmount.find(dstrRadixSeparatorE);
      bool _bDispE = ( posRE > 0 ) && ( posGE < posRE );
      if( !_bDispE ) DisplayUnFormat( dstrAmount, ifds::Amount );
      //end check

      return(dstrAmount);
   }

   //******************************************************************************
   DString doubleToDString( const BFFieldId& idField, const double dValue )
   {
      DString dstrMask = getRawMask(idField);

      dstrMask.strip();
      int iNumDecimalMask = dstrMask.find(I_("."));

      if (iNumDecimalMask == DString::npos)
      {
         iNumDecimalMask = 0;
      }
      else
      {
         iNumDecimalMask = dstrMask.size() - iNumDecimalMask - 1;
      }

      const ClientLocale &clientLocale = ClientLocaleContext::get();
      const bfutil::LocaleTraits& localeTraits = bfutil::LocaleTraits::get(clientLocale);
      DString Radixseparator;
	  Radixseparator = localeTraits.getRadixSeparator();
      DString Negative;
	  Negative = localeTraits.getNegativeSign();
      int decimal, sign;
      DString dstrValue(DStringA(_fcvt(dValue, iNumDecimalMask, &decimal, &sign)));

      if (iNumDecimalMask != 0)
      {
         DString dstrValue1, dstrValue2;

         if (decimal >= 0)
         {
            dstrValue1 = dstrValue.left(decimal);
            dstrValue2 = dstrValue.right(dstrValue.length() - decimal);
            if (dstrValue1 == NULL_STRING)
            {
               dstrValue1 = I_("0");
            }
            dstrValue = dstrValue1 + Radixseparator;//I_('.');
            dstrValue += dstrValue2;
            if (dValue < 0)
            {
               dstrValue = Negative/*I_('-')*/ + dstrValue;
            }
         }
         else
         {
            if (dValue < 0) 
            {
               dstrValue1 = Negative + I_("0") + Radixseparator; //I_("-0.");
            }
            else
            {
               dstrValue1 = I_("0") + Radixseparator;	//I_("0.");
            }
            dstrValue1.padRight(dstrValue1.length() + abs(decimal), I_CHAR('0'));
            dstrValue = dstrValue1 + dstrValue;
         }
      }

      boost::scoped_ptr<BFDataField> pField(BFDataField::getFactory()->createField(idField));
      pField->set(dstrValue, true, clientLocale);
      pField->get(dstrValue, true, clientLocale, &BFMask(dstrMask));
      //due to the function is not working properly, manually padding or cutting
      //the decimals figure it out later
      dstrValue.strip();
      
      int iNumDecimalValue = dstrValue.find(Radixseparator);//I_("."));

      if (iNumDecimalValue == DString::npos)
      {
         iNumDecimalValue = 0;
      }
      else
      {
         iNumDecimalValue = dstrValue.size() - iNumDecimalValue - 1;
      }
      if (iNumDecimalValue > iNumDecimalMask)
      {
         dstrValue = dstrValue.left(dstrValue.size() - iNumDecimalValue + iNumDecimalMask);
      }
      else if (iNumDecimalValue < iNumDecimalMask)
      {
         //padding zeros of the number of decimals
         dstrMask.padRight(dstrValue.length() + iNumDecimalMask - iNumDecimalValue, I_CHAR('0'));
      }
      return dstrValue;
   }

   //******************************************************************************
   DATE_ORDER CompareDates( const DString& Date1, const DString& Date2, BFDate::DATE_FORMAT eFormat /*= BFDate::DF_DDATE_DEPRECATED*/ )
   {

      BFDate bfDate1( Date1, eFormat );
      if( bfDate1.isNull() )
      {
         bfDate1 = BFDate::highDate();
      }
      BFDate bfDate2( Date2, eFormat );
      if( bfDate2.isNull() )
      {
         bfDate2 = BFDate::highDate();
      }

      if( bfDate1 < bfDate2 )
      {
         return( FIRST_EARLIER );
      }
      else if( bfDate1 == bfDate2 )
      {
         return( EQUAL );
      }
      return( SECOND_EARLIER );
   }

   //*******************************************************************************
   bool  dateRangesOverlap(const DString& strStrtDate1, const DString& strEndDate1,
                           const DString& strStrtDate2, const DString& strEndDate2)

   {
      if( IsDateBetween(strStrtDate2,strEndDate2,strStrtDate1) ||  
          IsDateBetween(strStrtDate2,strEndDate2,strEndDate1) || 
          IsDateBetween(strStrtDate1,strEndDate1,strStrtDate2)  ||
          IsDateBetween(strStrtDate1,strEndDate1,strEndDate2) )
      {
         return(true);
      }
      return(false);
   }

   //*****************************************************************************
   bool  IsDateBetween(const DString& strStrtDate, const DString& strEndDate,
                       const DString& strDate)
   {
      if( ((CompareDates( strDate,strEndDate) ==FIRST_EARLIER) && 
           (CompareDates( strDate,strStrtDate) ==SECOND_EARLIER) ) ||
          ((CompareDates( strDate,strEndDate) ==EQUAL) || 
           (CompareDates( strDate,strStrtDate) ==EQUAL) ) )
      {
         return(true);    
      }
      return(false);
   }

   //******************************************************************************
   void 
   getFormat12319999Date(DString &Date)
   {
      //  look in the registry for the date format mask
      DString dstrConfiguration( I_( "HostMasks" ) );
      DString dstrKey( I_("D") );

      Date = GetConfigValueAsString( I_( "LocaleFormats" ), dstrConfiguration, dstrKey );

      Date.replace(Date.find(I_("MM")), 2, I_("12"));
      Date.replace(Date.find(I_("dd")), 2, I_("31"));
      Date.replace(Date.find(I_("yyyy")), 4, I_("9999"));
   }

   // formatedDate = input date with displaymask
   // unformatedDate = output date using host mask
   // using DSTC0052_VWRepeat_Record's EffectiveDate and Data as tool. stupid but work
   //******************************************************************************
   void UnformatDate( const DString& formattedDate, DString &unformattedDate )
   {
      BFData dd( ifds::DSTC0052_VWRepeat_Record );

      dd.setElementValue( ifds::EffectiveDate, formattedDate, true, true );
      dd.getElementValue( ifds::EffectiveDate, unformattedDate);
   }
   //******************************************************************************
   // format date,
   //  input: unformat date
   //  out put: format date
   void FormatDate( DString &dstrDate )
   {
      BFDataField::formatValue( ifds::EffectiveDate, dstrDate  );
   }

   void FormatDateByString( DString &dstrDate, const DString& dateFormat)
   {
      if(!dateFormat.empty() && !dstrDate.empty())
      {
         DString strNoSlash = dstrDate.stripAll(I_CHAR('/'));
         dstrDate = NULL_STRING;
         dstrDate = strNoSlash;

         DString strMask = NULL_STRING;
         if(dateFormat == I_("dmy"))
         {
            strMask = I_("DDMMYYYY");
         }
         else if(dateFormat == I_("mdy"))
         {
            strMask = I_("MMDDYYYY");
         }
         else if(dateFormat == I_("ymd"))
         {
            strMask = I_("YYYYMMDD");
         }

         if(!strMask.empty())
         {
            DString tmpDate, tmp;
            int pos = strMask.find( I_( "MM" ) );
            if( (pos - 1) != DString::npos )
            {
               tmp.assign( dstrDate, pos, 2);
               tmpDate = tmp + I_("/");
            }

            pos = strMask.find( I_( "DD" ) );
            //if( (pos - 1) != DString::npos )
            {
               tmp.assign( dstrDate, pos, 2);
               tmpDate += tmp + I_("/");
            }

            pos = strMask.find( I_( "YYYY" ) );
            if( (pos - 1) != DString::npos )
            {
               tmp.assign( dstrDate, pos, 4);
               tmpDate += tmp;
            }

            dstrDate = NULL_STRING;
            dstrDate += tmpDate;
         }
      }
   }

   //******************************************************************************
   bool isValidDate( DString& strDate )
   {
      // at the moment, infra only recognize date in the form MM/DD/YYYY, so we change to that first!
      DString tmpDate, tmp, Mask = getMask( ifds::CurrBusDate ).upperCase();

      int pos = Mask.find( I_( "MM" ) )-1;
      if( pos != DString::npos )
      {
         tmp.assign( strDate, pos, 2);
         tmpDate = tmp + I_("/");
      }

      pos = Mask.find( I_( "DD" ) )-1;
      if( pos != DString::npos )
      {
         tmp.assign( strDate, pos, 2);
         tmpDate += tmp + I_("/");
      }

      pos = Mask.find( I_( "YYYY" ) )-1;
      if( pos != DString::npos )
      {
         tmp.assign( strDate, pos, 4);
         tmpDate += tmp;
      }

      try
      {
         BFDate date( tmpDate, BFDate::DF_FSUS );
      }
      catch( BFDateInvalidException& )
      {
         return( false );
      }
      return( true );
   }

   //******************************************************************************
   bool BuildAge( const DString& birthDate, const DString& currDate, DString& years, DString& months ) 
   {
      int mo1, mo2, yr1, yr2, rez_mo;
      DString date1, date2, rez;
      bool flgBadDate = false;

      // look in the registry for the date format mask
      // birth date and current date should be in host format
      DString dstrConfiguration( I_( "HostMasks" ) );
      DString dstrKey( I_("D") );

      DString mask = GetConfigValueAsString( I_( "LocaleFormats" ), 
                                             dstrConfiguration,
                                             dstrKey );

      if( birthDate == NULL_STRING )
      {
         years = NULL_STRING;
         months = NULL_STRING;
         return(true);
      }
      int month_pos = mask.find( I_( "MM" ) );
      int year_pos = mask.find( I_( "yyyy" ) );
      if( DString::npos != month_pos && DString::npos != year_pos )
      {
         date1.assign( birthDate, month_pos, 2);
         date2.assign( currDate, month_pos, 2);
         mo1 = convertToULong( date1 );
         mo2 = convertToULong( date2 );
         if( mo1 == 0 || mo2 == 0 )
            flgBadDate = true;
         rez_mo = mo2 - mo1;
         if( rez_mo < 0 )
            convertIntToString( 12 - ( mo1 - mo2 ), months );
         else
            convertIntToString( mo2 - mo1, months );

         date1.assign( birthDate, year_pos, 4);
         date2.assign( currDate, year_pos, 4);
         yr1 = convertToULong( date1 );
         yr2 = convertToULong( date2 );
         if( yr1 == 0 || yr2 == 0 )
            flgBadDate = true;
         if( rez_mo < 0 )
            convertIntToString( yr2 - yr1 - 1, years );
         else
            convertIntToString( yr2 - yr1, years );
      }
      else if( DString::npos != mask.find( I_( "##" ) ) ) //this case should never be true anymore
      {
         date1.assign( birthDate, 0, 2);
         date2.assign( currDate, 0, 2);
         mo1 = convertToULong( date1 );
         mo2 = convertToULong( date2 );
         if( mo1 == 0 || mo2 == 0 )
            flgBadDate = true;
         rez_mo = mo2 - mo1;
         if( rez_mo < 0 )
            convertIntToString( 12 - ( mo1 - mo2 ), months );
         else
            convertIntToString( mo2 - mo1, months );

         date1.assign( birthDate, 6, 4);
         date2.assign( currDate, 6, 4);
         yr1 = convertToULong( date1 );
         yr2 = convertToULong( date2 );
         if( yr1 == 0 || yr2 == 0 )
            flgBadDate = true;
         if( rez_mo < 0 )
            convertIntToString( yr2 - yr1 - 1, years );
         else
            convertIntToString( yr2 - yr1, years );
      }
      else
         flgBadDate = true;
      return(flgBadDate);
   }

   //******************************************************************************
   bool addDays( DString& dstrDateIn, DString& dstrDateOut, int nDays )
   {
      BFDate::DATE_FORMAT fmt = BFDate::inferFormat( dstrDateIn );
      assert( fmt != BFDate::DF_NULL );
      BFDate dateIn( dstrDateIn, fmt );
      dateIn += nDays;
      dstrDateOut = dateIn.get( fmt );
      return( true );
   }

   void addMonths( DString& dstrDateIn, DString& dstrDateOut, double& dMonths )
   {
      // This algorithmn is used by Indexing.  It assumes 30 days are in a Month.
      BFDate dateIn( dstrDateIn, BFDate::DF_DDATE_DEPRECATED );
      BFDate dateOut( dstrDateOut, BFDate::DF_DDATE_DEPRECATED );
      dMonths = fabs( static_cast<double>(dateIn - dateOut) ) / 30.0;
   }

   //******************************************************************************
   bool subtractDays( DString& dstrDateIn, DString& dstrDateOut, int nDays )
   {
      // hey ... its the opposite of addDays!
      return( addDays( dstrDateIn, dstrDateOut, nDays * -1 ) );
   }

   //******************************************************************************

   void convertToSortableDate ( const BFFieldId& idField, const DString& dstrOriDate, DString& dstrSortableDate )
   {
      DString dstrConfiguration( I_( "HostMasks" ) );
      DString dstrKey( I_("D") );
      DString mask = GetConfigValueAsString( I_( "LocaleFormats" ), dstrConfiguration, dstrKey );
      mask.upperCase();
      int month_pos = mask.find( I_( "MM" ) );
      int year_pos = mask.find( I_( "YYYY" ) );
      int day_pos = mask.find( I_( "DD" ) );
      dstrSortableDate = dstrOriDate.substr ( year_pos, 4 ) + dstrOriDate.substr ( month_pos, 2 ) + dstrOriDate.substr ( day_pos, 2 );
   }

   //*********************************************************************************************
   void convertToSortableDateInDec ( const DString& dstrOriDate, DString& dstrSortableDate )
   {
      DString dstrConfiguration( I_( "HostMasks" ) );
      DString dstrKey( I_("D") );
      DString mask = GetConfigValueAsString( I_( "LocaleFormats" ), dstrConfiguration, dstrKey );
      mask.upperCase();
      int month_pos = mask.find( I_( "MM" ) );
      int year_pos = mask.find( I_( "YYYY" ) );
      int day_pos = mask.find( I_( "DD" ) );
      int iYear,iMonth,iDay;
      DString dstrYear = dstrOriDate.substr ( year_pos, 4 );
      iYear =  dstrYear.asInteger();
      DString dstrMonth = dstrOriDate.substr ( month_pos, 2 );
      iMonth = dstrMonth.asInteger();
      DString dstrDay = dstrOriDate.substr ( day_pos, 2 );     
      iDay = dstrDay.asInteger();
      iYear = 9999-iYear;
      iMonth = 12 - iMonth;
      iDay = 31 - iDay;

      DString dstrSortYear,
         dstrSortMonth,
         dstrSortDay;
      dstrSortYear  = DString::asString( iYear );
      dstrSortMonth = DString::asString( iMonth );
      dstrSortDay   = DString::asString( iDay );

      if ( 2 > dstrSortMonth.length() )
         dstrSortMonth = I_( "0" ) + dstrSortMonth;
      if ( 2 > dstrSortDay.length() )
         dstrSortDay = I_( "0" ) + dstrSortDay;

      dstrSortableDate = dstrSortYear + dstrSortMonth + dstrSortDay;
   }

   //******************************************************************************

   int getDayFromUnFormattedDate ( const DString& dstrDate )
   {
      DString dstrConfiguration( I_( "HostMasks" ) );
      DString dstrKey( I_("D") );
      DString mask = GetConfigValueAsString( I_( "LocaleFormats" ), dstrConfiguration, dstrKey );
      mask.upperCase();
      int day_pos = mask.find( I_( "DD" ) );
      DString strDay = dstrDate.substr ( day_pos, 2 );
      return(strDay.asInteger());
   }
   //******************************************************************************

   int getMonthFromUnFormattedDate ( const DString& dstrDate )
   {
      DString dstrConfiguration( I_( "HostMasks" ) );
      DString dstrKey( I_("D") );
      DString mask = GetConfigValueAsString( I_( "LocaleFormats" ), dstrConfiguration, dstrKey );
      mask.upperCase();
      int month_pos = mask.find( I_( "MM" ) );
      DString strMonth = dstrDate.substr ( month_pos, 2 );
      return(strMonth.asInteger());
   }
   //******************************************************************************

   int getYearFromUnFormattedDate ( const DString& dstrDate )
   {
      DString dstrConfiguration( I_( "HostMasks" ) );
      DString dstrKey( I_("D") );
      DString mask = GetConfigValueAsString( I_( "LocaleFormats" ), dstrConfiguration, dstrKey );
      mask.upperCase();
      int year_pos = mask.find( I_( "YYYY" ) );
      DString strYear = dstrDate.substr ( year_pos, 4 );
      return(strYear.asInteger());
   }
   //******************************************************************************

   void getEndOfMonthUnFormattedDate ( int nMonth, int nYear, DString& dstrDate )
   {
      dstrDate = NULL_STRING;
      DString dstrConfiguration( I_( "HostMasks" ) );
      DString dstrKey( I_("D") );
      DString mask = GetConfigValueAsString( I_( "LocaleFormats" ), dstrConfiguration, dstrKey );
      mask.upperCase();
      int month_pos = mask.find( I_( "MM" ) );
      int year_pos = mask.find( I_( "YYYY" ) );
      int day_pos = mask.find( I_( "DD" ) );
      DString strLastDay;
      int nDay = nNoOfDaysOfMonth[nMonth];
      if( (nMonth == 2) && (BFDate::isLeapYear( nYear )) )
         nDay = 29;
      strLastDay = DString::asString(nDay);
      if( !month_pos )
      {
         if( nMonth < 10 )
            dstrDate += I_("0");
         dstrDate = dstrDate.appendInt(nMonth);
         if( day_pos < year_pos )
         {
            dstrDate += strLastDay;
            dstrDate = dstrDate.appendInt(nYear);
         }
         else
         {
            dstrDate = dstrDate.appendInt(nYear);
            dstrDate += strLastDay;
         }
      }
      else if( !day_pos )
      {
         dstrDate += strLastDay;
         if( month_pos < year_pos )
         {
            if( nMonth < 10 )
               dstrDate += I_("0");
            dstrDate = dstrDate.appendInt(nMonth);
            dstrDate = dstrDate.appendInt(nYear);
         }
         else
         {
            dstrDate = dstrDate.appendInt(nYear);
            if( nMonth < 10 )
               dstrDate += I_("0");
            dstrDate = dstrDate.appendInt(nMonth);
         }
      }
      else if( !year_pos )
      {
         dstrDate = dstrDate.appendInt(nYear);
         if( day_pos < month_pos )
         {
            dstrDate += strLastDay;
            if( nMonth < 10 )
               dstrDate += I_("0");
            dstrDate = dstrDate.appendInt(nMonth);
         }
         else
         {
            if( nMonth < 10 )
               dstrDate += I_("0");
            dstrDate = dstrDate.appendInt(nMonth);
            dstrDate += strLastDay;
         }
      }
   }
   //******************************************************************************

   void getBeginOfMonthUnFormattedDate ( int nMonth, int nYear, DString& dstrDate )
   {
      dstrDate = NULL_STRING;
      DString dstrConfiguration( I_( "HostMasks" ) );
      DString dstrKey( I_("D") );
      DString mask = GetConfigValueAsString( I_( "LocaleFormats" ), dstrConfiguration, dstrKey );
      mask.upperCase();
      int month_pos = mask.find( I_( "MM" ) );
      int year_pos = mask.find( I_( "YYYY" ) );
      int day_pos = mask.find( I_( "DD" ) );
      if( !month_pos )
      {
         if( nMonth < 10 )
            dstrDate += I_("0");
         dstrDate = dstrDate.appendInt(nMonth);
         if( day_pos < year_pos )
         {
            dstrDate += I_("01");
            dstrDate = dstrDate.appendInt(nYear);
         }
         else
         {
            dstrDate = dstrDate.appendInt(nYear);
            dstrDate += I_("01");
         }
      }
      else if( !day_pos )
      {
         dstrDate += I_("01");
         if( month_pos < year_pos )
         {
            if( nMonth < 10 )
               dstrDate += I_("0");
            dstrDate = dstrDate.appendInt(nMonth);
            dstrDate = dstrDate.appendInt(nYear);
         }
         else
         {
            dstrDate = dstrDate.appendInt(nYear);
            if( nMonth < 10 )
               dstrDate += I_("0");
            dstrDate = dstrDate.appendInt(nMonth);
         }
      }
      else if( !year_pos )
      {
         dstrDate = dstrDate.appendInt(nYear);
         if( day_pos < month_pos )
         {
            dstrDate += I_("01");
            if( nMonth < 10 )
               dstrDate += I_("0");
            dstrDate = dstrDate.appendInt(nMonth);
         }
         else
         {
            if( nMonth < 10 )
               dstrDate += I_("0");
            dstrDate = dstrDate.appendInt(nMonth);
            dstrDate += I_("01");
         }
      }
   }
   //******************************************************************************

   void logTime( const DString&  dstrComment )
   {

      DString dstrTimeCheckingFileName = GetConfigValueAsString( I_( "LocaleFormats" ), 
                                                                 I_( "TraceFiles" ), 
                                                                 I_( "logTimeFileName" ) );

      if( dstrTimeCheckingFileName.empty() )
      {
         return;
      }

      FILE *file1 = fopen( dstrTimeCheckingFileName.asA().c_str(), "r" );
      if( !file1 )
      {
         return;
      }

      fclose( file1 );

      //map pair: comment, nbr.of appearance.
      int iNumberOfAppearance = 0;

      typedef std::map< DString, int > TIME_CHECKING;
      static TIME_CHECKING m_mapTimeChecking;

      typedef TIME_CHECKING::iterator TIME_CHECKING_ITER;
      TIME_CHECKING_ITER iter = m_mapTimeChecking.begin();

      iter = m_mapTimeChecking.find( dstrComment );
      if( iter == m_mapTimeChecking.end() )
      {  //new entry
         iNumberOfAppearance = 1;
         m_mapTimeChecking.insert( TIME_CHECKING::value_type( dstrComment, iNumberOfAppearance ) );
      }
      else
      {
         iNumberOfAppearance = (*iter).second;
         iNumberOfAppearance++;
         (*iter).second = iNumberOfAppearance;
      }

      //open the file for append
      file1 = fopen( dstrTimeCheckingFileName.asA().c_str(), "a" );
      if( !file1 )
      {
         fprintf( file1, "\n !!ERROR!! Cannot open text file for append");
         //cant open for append the TimeCheckingFile
         return;
      }

      static LARGE_INTEGER dTimeCheckingStatic;
      static bool bFirstTime = true;

      LARGE_INTEGER dTimeChecking;

      FILETIME f;
      GetSystemTimeAsFileTime(&f);
      dTimeChecking.LowPart = f.dwLowDateTime;
      dTimeChecking.HighPart = f.dwHighDateTime;

      if( !bFirstTime )
      {
         double fTime1 = dTimeChecking.QuadPart / 10000000.0;
         double fTime2 = dTimeCheckingStatic.QuadPart / 10000000.0;

         fprintf(file1, "\n%37.3lf sec."
                 , fTime1-fTime2 );
      }

      if( bFirstTime )
      {
         fprintf( file1, "\n========================================================================"
                  "\nNUMBER OF        TIME           INTERVAL        COMMENT                 " 
                  "\nAPPEARANCE                                                              " 
                  "\n========================================================================" );
      }
      double fTime = dTimeChecking.QuadPart / 10000000.0;
      fprintf( file1, "\n%5d%22.3lf                     %-s"
               , iNumberOfAppearance, fTime, dstrComment.asA().c_str() );

      fclose( file1 );

      dTimeCheckingStatic = dTimeChecking;
      bFirstTime = false;
   }

   //******************************************************************************

   int getDayPosition( )
   {
      // Retreive the Date Format 
      DString dstrConfiguration( I_( "HostMasks" ) );
      DString dstrKey( I_("D") );
      DString mask = GetConfigValueAsString( I_( "LocaleFormats" ), dstrConfiguration, dstrKey );
      mask.upperCase();
      return(mask.find( I_( "DD" ) ));   
   }

   //******************************************************************************

   int getMonthPosition( )
   {
      // Retreive the Date Format 
      DString dstrConfiguration( I_( "HostMasks" ) );
      DString dstrKey( I_("D") );
      DString mask = GetConfigValueAsString( I_( "LocaleFormats" ), dstrConfiguration, dstrKey );
      mask.upperCase();
      return(mask.find( I_( "MM" ) ));
   }

   //******************************************************************************

   int getYearPosition( )
   {
      // Retreive the Date Format 
      DString dstrConfiguration( I_( "HostMasks" ) );
      DString dstrKey( I_("D") );
      DString mask = GetConfigValueAsString( I_( "LocaleFormats" ), dstrConfiguration, dstrKey );
      mask.upperCase();   
      return(mask.find( I_( "YYYY" ) ));
   }

   //******************************************************************************
   void formatToolTipDate( const BFFieldId& idField, DString& strDate )
   {  
      DString tmp, dstrMask ;
	  dstrMask = getMask( idField ).upperCase();
	  dstrMask.stripAll();
	  if(!dstrMask.length())//if no field mask
	  {
		DString dstrConfiguration( I_( "DisplayMasks" ) );
	    DString dstrKey( I_("enUS-D") );
        dstrMask = GetConfigValueAsString( I_( "LocaleFormats" ), dstrConfiguration, dstrKey );
		dstrMask.stripAll();
		if(!dstrMask.length())//not found in registery use US default.
			dstrMask = I_("MM/DD/YYYY");
	  }       
      dstrMask.upperCase();
	  tmp.assign( strDate, getMonthPosition(), 2);
      dstrMask .replace ( dstrMask.find( I_("MM") ), 2, tmp );
      tmp.assign( strDate, getDayPosition(), 2);
      dstrMask .replace ( dstrMask.find( I_("DD") ), 2, tmp );
      tmp.assign( strDate, getYearPosition(), 4);
      dstrMask .replace ( dstrMask.find( I_("YYYY") ), 4, tmp );
	  strDate = dstrMask;
      //Mask.replace ( Mask.find(I_("(")), 1, I_(""));
      //strDate = Mask.strip('(').strip(')') ;
   }

   //******************************************************************************
   long getOffSetBetweenTwoDates( const DString& dstrDate1, const DString& dstrDate2, long lOffSet )
   {
      BFDate date1( dstrDate1, BFDate::DF_DDATE_DEPRECATED );
      BFDate date2( dstrDate2, BFDate::DF_DDATE_DEPRECATED );
      return( date1 - date2 );
   }

   //******************************************************************************
   void formattedField( const BFFieldId& idField, int iPrecision, DString &dstrValue )
   {
      DString dstrMask = getRawMask(idField);

      if( dstrMask.find( I_(".")) != DString::npos )
         dstrMask.strip().stripTrailing('0').stripTrailing('.');

      //padding zeros of the number of decimals
      if( iPrecision > 0 )
      {
         dstrMask += I_(".");
         dstrMask.padRight(dstrMask.length() + iPrecision, I_CHAR('0'));
      }
      if( idField == ifds::USDollar )
      {
         BFDecimalField df( ifds::USDollar, &ifds::s_FldProp_USDollar );

         const ClientLocale &clientLocale = ClientLocaleContext::get();
         df.set( dstrValue, false, clientLocale );
         dstrValue = df.get( dstrValue, true, clientLocale, &BFMask( dstrMask ) );
      }
   }

   void stripSeparatorforDecimal(DString& dstrValue)
   {
      const bfutil::LocaleTraits& localeTraits = bfutil::LocaleTraits::get( ClientLocaleContext::get() );
      I_CHAR separator = localeTraits.getGroupSeparator();
      dstrValue.stripAll(separator);
   }

//strDateField always use upper case
   int extractFieldFromDate( const DString& strField, DString& strDateField )
   {
      // look in the registry for the date format mask
      // the current date should be in host format
      DString dstrConfiguration( I_( "HostMasks" ) );
      DString dstrKey( I_("D") );
      DString mask = GetConfigValueAsString( I_( "LocaleFormats" ), dstrConfiguration, dstrKey );
      mask.upperCase();
      int field = 0;

      DString strDateFld;
      int field_pos = mask.find( strDateField);

      if( strField == NULL_STRING )
      {
         return(field);
      }
      else if( DString::npos != field_pos )
      {
         strDateFld.assign( strField, field_pos, strDateField.length() );
         field = convertToULong( strDateFld );
      }

      return(field);
   }

// return 1: same year,0:first date earlier;2: second earlier
// data pass in must be in host format
   int  compareDateYear(const DString& date1,const DString& date2 )
   {
      int iRet = 1;
      DString dstrYrMask(I_("YYYY") );
      int iYear1 = extractFieldFromDate(date1,dstrYrMask );
      int	iYear2 = extractFieldFromDate(date2,dstrYrMask );
      if( iYear1 > iYear2 )
      {
         iRet = 2;
      }
      else if ( iYear1 < iYear2 )
      {
         iRet = 0;	  
      }
      return iRet;	
   }

   //******************************************************************************
   void DisplayFormat( DString& strText, const BFFieldId& idField )
   {
      const bfutil::LocaleTraits& localeTraitsE = bfutil::LocaleTraits::get( ClientLocaleContext::get() );
      I_CHAR RadixSeparatorE = localeTraitsE.getRadixSeparator();
      I_CHAR GroupseparatorE = localeTraitsE.getGroupSeparator();

      const bfutil::LocaleTraits& localeTraitsDisp = bfutil::LocaleTraits::get( ClientLocaleContext::get(), true );
      DString dstrRadixSeparatorDisp, dstrGroupseparatorDisp;
      dstrRadixSeparatorDisp = localeTraitsDisp.getRadixSeparator();
      dstrGroupseparatorDisp = localeTraitsDisp.getGroupSeparator();

      DString tempchar = I_(";");

      DString dstLocaleStr = ClientLocaleContext::get().getLocale();
      if( dstLocaleStr == I_("deDE") )
      {
         bool bdecimal = false;

         //if( idField == ifds::NullFieldId || idField.getId() < 4000000   ) 
         {
            DString tmp = strText;
            tmp.stripAll('%');
            tmp.stripAll();
            bdecimal = tmp.isDecimal();
         }
         /*else 
         {
         const BFDataFieldProperties* pProps = BFDataFieldProperties::get( idField );
         bdecimal = pProps->isDecimal();
         }*/

         if( bdecimal )
         {
            int iPos;
            while( true )
            {
               iPos = strText.find( RadixSeparatorE );
               if( iPos == DString::npos ) break;
               strText.replace( iPos, 1, tempchar );
            }

            while( true )
            {
               iPos = strText.find( GroupseparatorE );
               if( iPos == DString::npos ) break;
               strText.replace( iPos, 1, dstrGroupseparatorDisp );
            }

            while( true )
            {
               iPos = strText.find( tempchar );
               if( iPos == DString::npos ) break;
               strText.replace( iPos, 1, dstrRadixSeparatorDisp );
            }
         }
      }
   }

   //******************************************************************************
   void DisplayUnFormat( DString& strText, const BFFieldId& idField )
   {
      const bfutil::LocaleTraits& localeTraitsE = bfutil::LocaleTraits::get( ClientLocaleContext::get() );
      DString dstrRadixSeparatorE, dstrGroupseparatorE;
      dstrRadixSeparatorE = localeTraitsE.getRadixSeparator();
      dstrGroupseparatorE = localeTraitsE.getGroupSeparator();

      const bfutil::LocaleTraits& localeTraitsDisp = bfutil::LocaleTraits::get( ClientLocaleContext::get(), true );
      I_CHAR RadixSeparatorDisp = localeTraitsDisp.getRadixSeparator();
      I_CHAR GroupseparatorDisp = localeTraitsDisp.getGroupSeparator();

      DString tempchar = I_(";");

      DString dstLocaleStr = ClientLocaleContext::get().getLocale();
      if( dstLocaleStr == I_("deDE") )
      {
         bool bdecimal = false;

         //if( idField == ifds::NullFieldId || idField.getId() < 4000000 )
         {
            DString tmp = strText;
            tmp.stripAll();
            tmp.stripAll('%');
            tmp.stripAll( GroupseparatorDisp );
            tmp.stripAll( RadixSeparatorDisp );
            bdecimal = tmp.isAllDigits();
         }
         /*else
         {
         const BFDataFieldProperties* pProps = BFDataFieldProperties::get( idField );
         bdecimal = pProps->isDecimal();
         }*/

         if( bdecimal )
         {
            int iPos;
            while( true )
            {
               iPos = strText.find( RadixSeparatorDisp );
               if( iPos == DString::npos ) break;
               strText.replace( iPos, 1, tempchar );
            }

            while( true )
            {
               iPos = strText.find( GroupseparatorDisp );
               if( iPos == DString::npos ) break;
               strText.replace( iPos, 1, dstrGroupseparatorE );
            }

            while( true )
            {
               iPos = strText.find( tempchar );
               if( iPos == DString::npos ) break;
               strText.replace( iPos, 1, dstrRadixSeparatorE );
            }
         }
      }
   }

   std::vector<DString>& tokenizeString( DString dstrInput, std::vector<DString>& vOutput ) 
   {
      while( true ) {
         int nPos = dstrInput.find(',');
         if( nPos != DString::npos ) {
            vOutput.push_back( dstrInput.left(nPos).strip() );
            dstrInput = dstrInput.right(dstrInput.length() - nPos -1);
         } else {
            vOutput.push_back(dstrInput.strip());
            return vOutput;
         }
      }
   }
	/******************************************************************************
	Input: dstrTime 
	OutPut:None
	Return:Bool
	Functionality:Checks for the user entered Time in Format HHMMSS/HH:MM 
	******************************************************************************/
	bool bValidateTime(DString dstrTime)
	{
		DString mask = NULL_STRING;
		if(dstrTime.length()== 8)
		  mask = I_("##:##:##");
		//We should always allow time in HH:MM:SS format .Else this can crate crash 
		//while removing the mask and sedning to the view.Remove mask ##:##:## works only
		//if there are excatly 8 digits.
		//if(dstrTime.length()== 7)
		//  mask = I_("#:##:##");
		removeMaskFromString(dstrTime, mask );
		if(!dstrTime.stripAll().empty())
		{
			int iHour,iMin,iSec,iTime;
			if(!isAllDigits(dstrTime) || (dstrTime.length() < 5))
				return false; 

			iTime = dstrTime.asInteger();

			 iHour = iTime / 10000;
			 iTime = iTime % 10000;
			 iMin  = iTime / 100;
			 iTime = iTime % 100;
			 iSec  = iTime;
			if (iHour < 0 || iHour > 23 || iMin < 0 || iMin > 59 || iSec < 0 || iSec > 59  )
			{
				return false;
			}
			return true;
		}
	  return false;
	}
} // end of namespace DSTCommonFunctions

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCommonFunction.cpp-arc  $
 * 
 *    Rev 1.86   Mar 16 2012 13:36:04   dchatcha
 * P0186484 FN05 - SEG Trade Processing, new validations.
 * 
 *    Rev 1.85   Jul 20 2010 02:22:46   dchatcha
 * IN# 2187105 - Not able to add trade with amount 1000 and more in desktop.
 * 
 *    Rev 1.84   14 May 2010 18:01:06   smithdav
 * Add BFBigDecimal field type as an improvement to the double backed BFDecimal.
 * 
 *    Rev 1.83   Jun 15 2009 11:58:50   purdyech
 * getMarket() was inconsistent with other methods used to get the market.  This was exposed by the XML parameter setting.
 * 
 *    Rev 1.82   Aug 22 2007 17:09:56   smithdav
 * IN 982850,  IN    - Add DayOfMonth field conditions to RRIF.
 * 
 *    Rev 1.81   Aug 12 2005 17:21:40   Fengyong
 * Incident 378244 - european numeric: formatting code do not check field type, just check value is decimal or not.
 * 
 *    Rev 1.80   Jul 22 2005 15:14:40   Fengyong
 * PET1250FN02 - European format - syncup
 * 
 *    Rev 1.79   Jul 11 2005 17:22:34   Fengyong
 * PET1250FN02 - European numeric enahncement - conditions
 * decimal format 
 * 
 *    Rev 1.78   Apr 05 2005 15:46:18   yingbaol
 * Incident 243363: compareDateYear method
 * 
 *    Rev 1.77   Nov 26 2004 14:13:14   popescu
 * PTS 10034524, CompareDates method has an extra parameter to allow callers to pass in the date format to be used. Callers can use DF_DISPLAY to force the use of the Reg 'Display Masks' value.
 * 
 *    Rev 1.76   Nov 14 2004 14:33:06   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.75   Sep 08 2003 09:11:12   YINGBAOL
 * add  formatdate method
 * 
 *    Rev 1.74   Jul 04 2003 15:35:58   YINGBAOL
 * add  extractFieldFromDate( ...)	and   compareDateYear(...) method
 * 
 *    Rev 1.73   May 13 2003 15:22:42   WINNIE
 * Ticket 10016965 : Fix convert from dstring to double. Must strip the comma before conversion.
 * 
 *    Rev 1.72   May 13 2003 09:46:06   popescu
 * Bug fix in doubleToDString method. Two char * were added and this produced a memory overlap.
 * 
 *    Rev 1.71   Apr 22 2003 14:50:06   FENGYONG
 * Add fundction strip seperator for decimal and
 * fix stripAll(',') for multilanguage
 * 
 *    Rev 1.70   Apr 09 2003 12:43:16   VADEANUM
 * PTS10015557 Fixed convertToSortableDateInDec() when Day or Month single digit.
 * 
 *    Rev 1.69   Mar 21 2003 18:06:16   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.68   Oct 09 2002 23:54:20   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.67   Aug 29 2002 12:55:34   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.66   Jul 05 2002 11:49:38   PURDYECH
 * Infrastructure Fixup ... no more ICU!
 * 
 *    Rev 1.65   Jun 27 2002 09:39:30   PURDYECH
 * Back out some BFDate stuff
 * 
 *    Rev 1.64   Jun 25 2002 09:38:08   PURDYECH
 * Default ClientLocale is now set at application level through the Market Registry setting
 * 
 *    Rev 1.63   Jun 14 2002 16:48:28   PURDYECH
 * Sigh ... another hack ... deep sigh.  We'll use the registry to store the market information instead of inferring it from the DataBroker.bin file
 * 
 *    Rev 1.62   Jun 14 2002 16:20:32   PURDYECH
 * Cheesy hack to remove dependency on BinFileHeader in getMarket.  We'll fix this REAL SOON NOW.
 * 
 *    Rev 1.61   Jun 07 2002 17:45:20   KOVACSRO
 * Removed bank information
 * 
 *    Rev 1.60   May 28 2002 12:18:38   PURDYECH
 * BFData Implementation - Phase II
 * 
 *    Rev 1.59   22 May 2002 18:27:58   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.58   Feb 28 2002 12:44:36   YINGBAOL
 * add convertToSortableDateInDec method
 * 
 *    Rev 1.57   Dec 17 2001 15:23:48   ZHANGCEL
 * Added a new function: formattedField() which is used to format a field using a specific mask
 * 
 *    Rev 1.56   Nov 20 2001 09:52:32   JANKAREN
 * added new method getOffSetBetweenTwoDates()
 * 
 *    Rev 1.55   07 Nov 2001 13:46:56   KOVACSRO
 * changed a bit getDescription().
 * 
 *    Rev 1.54   21 Oct 2001 16:36:56   HSUCHIN
 * added new function formatToolTipDate to format date into mm/dd/yyyy (with slashe
 * 
 *    Rev 1.53   14 Oct 2001 15:24:00   HSUCHIN
 * added 3 new functions getDayPosition, getMonthPosition, getYearPosition.
 * 
 *    Rev 1.52   02 Oct 2001 11:40:00   KOVACSRO
 * Added logTime method.
 * 
 *    Rev 1.51   18 Sep 2001 16:49:58   KOVACSRO
 * bug fixed for getEndOfMonth()...
 * 
 *    Rev 1.50   14 Sep 2001 16:55:26   KOVACSRO
 * Added some new methods for dates.
 * 
 *    Rev 1.49   17 Jul 2001 13:23:10   HSUCHIN
 * added convertToSortableDate function
 * 
 *    Rev 1.48   Jun 12 2001 14:17:02   DINACORN
 * Sync. up with SSB (1.41.1.3)
 * 
 *    Rev 1.47   06 Jun 2001 17:07:58   KOVACSRO
 * sync up (codeInList bug)
 * 
 *    Rev 1.46   01 Jun 2001 11:35:30   HSUCHIN
 * bug fix in addmonths function
 * 
 *    Rev 1.45   01 Jun 2001 09:29:02   YINGZ
 * add precompile header
 * 
 *    Rev 1.44   23 May 2001 12:31:52   HSUCHIN
 * added 2 functions addmonths and subtractdays for date manipulation
 * 
 *    Rev 1.43   10 May 2001 11:37:50   HSUCHIN
 * Sync up with SSB
 * 
 *    Rev 1.42   03 May 2001 14:06:20   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.41   Mar 30 2001 16:49:10   YINGZ
 * add getRunMode
 * 
 *    Rev 1.40   Mar 30 2001 10:13:46   OLTEANCR
 * added getDescription(..).
 * 
 *    Rev 1.39   30 Mar 2001 10:05:00   HSUCHIN
 * added funtion to retrieve SplitComm flag 
 * 
 *    Rev 1.38   Mar 29 2001 15:36:40   DINACORN
 * Used DSTCommonFunctions MARKET_IDS constants
 * 
 *    Rev 1.37   Mar 21 2001 14:34:10   FENGYONG
 * add getoption2
 * 
 *    Rev 1.35   21 Mar 2001 12:22:58   KOVACSRO
 * Added bStripTrailingZeros param. to codeInList. 
 * 
 *    Rev 1.34   Feb 12 2001 14:58:38   DINACORN
 * Change "MSDW - Japan" to "Japan"
 * 
 *    Rev 1.33   Feb 06 2001 14:16:18   JANKAREN
 * Add addDays method
 * 
 *    Rev 1.32   Jan 17 2001 12:08:28   VASILEAD
 * Added workSessionId param for MgmtCo::getMgmtCoOptions()
 * 
 *    Rev 1.31   Dec 17 2000 20:23:12   OLTEANCR
 * changed to use a precompiled header
 * 
 *    Rev 1.30   Nov 17 2000 10:39:36   WINNIE
 * add new method for codeinlist
 * 
 *    Rev 1.29   Nov 02 2000 13:39:34   ZHANGCEL
 * Remove the stripLeading('0') in GetFundClassCode
 * 
 *    Rev 1.28   Nov 01 2000 16:15:38   FENGYONG
 * Add MastCode
 * 
 *    Rev 1.27   Oct 23 2000 13:54:32   FENGYONG
 * Pass local to Get mask  function
 * 
 *    Rev 1.26   Oct 05 2000 12:01:24   WINNIE
 * Do not display ';' if both first name and last name are blank
 * 
 *    Rev 1.25   Sep 29 2000 13:27:10   YINGZ
 * change market from cfds - canada to canada
 * 
 *    Rev 1.24   Sep 22 2000 16:22:58   OLTEANCR
 * Added ' ; ' between first and last name (just  for canadian market)
 * 
 *    Rev 1.23   Sep 14 2000 17:28:02   VASILEAD
 * Modified to accomodate the new infra from Sept 12
 * 
 *    Rev 1.22   Aug 29 2000 16:18:22   YINGZ
 * add isValidDate to check date
 * 
 *    Rev 1.21   Jul 31 2000 17:13:22   YINGZ
 * add getMask
 * 
 *    Rev 1.20   Jul 14 2000 11:18:22   YINGBAOL
 * pass by reference instead of value
 * 
 *    Rev 1.19   Jul 11 2000 13:34:34   YINGBAOL
 * add GetFundClassCode method
 * 
 *    Rev 1.18   Jun 13 2000 18:22:08   DT24433
 * new Infra interfaces use ClientLocale
 * 
 *    Rev 1.17   Jun 08 2000 15:13:46   HUANGSHA
 * Fix getting the Birth name
 * 
 *    Rev 1.16   Jun 01 2000 14:56:52   BUZILA
 * putting LastName first on entity search
 * 
 *    Rev 1.15   May 19 2000 16:56:54   YINGZ
 * fix CompareDates to handle empty date case
 * 
 *    Rev 1.14   May 15 2000 16:39:26   YINGBAOL
 * fix UnformatDate method
 * 
 *    Rev 1.13   May 02 2000 14:02:50   HUANGSHA
 * release
 * 
 *    Rev 1.12   Apr 28 2000 17:07:16   HUANGSHA
 * Fix
 * 
 *    Rev 1.11   Apr 26 2000 17:25:04   HUANGSHA
 * fix for doubleToDString()
 * 
 *    Rev 1.10   Apr 25 2000 15:39:04   HUANGSHA
 * added doubleToDString()
 * 
 *    Rev 1.9   Apr 18 2000 11:14:28   WINNIE
 * new convertTodouble
 * 
 *    Rev 1.8   Apr 14 2000 17:55:40   WINNIE
 * Move validation to Groupfund and MFAccount CBO to allow other CBO to use the same method. Bug fix for NumOfDecimals function
 * 
 *    Rev 1.7   Apr 13 2000 14:56:54   DT24433
 * switched to new CompareDates function
 * 
 *    Rev 1.6   Apr 06 2000 10:40:54   YINGZ
 * code sync
 * 
 *    Rev 1.5   Apr 05 2000 13:21:58   POPESCUS
 * New CompareDates method that fixes the memory leaks. It is commented out for; should be uncommented when we get a new infra release
 * 
 *    Rev 1.4   Mar 20 2000 17:10:54   HSUCHIN
 * GetFundNumber added
 * 
 *    Rev 1.3   Mar 09 2000 14:30:54   VASILEAD
 * Updated Entity screen for C2
 * 
 *    Rev 1.2   Mar 07 2000 17:01:08   POPESCUS
 * added a flag to the getFirstSequenced01AccountholderEntityName;
 * based on it the kana or kanji name is retrieved;
 * default is kanji
 * 
 *    Rev 1.1   Feb 15 2000 18:57:42   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 10:59:56   SMITHDAV
 * Initial revision.
// 
//    Rev 1.12   Feb 02 2000 18:09:54   BUZILA
// changes
// 
//    Rev 1.11   Jan 21 2000 15:57:32   YINGZ
// change back to old version of CompareDates
// 
//    Rev 1.10   Jan 21 2000 13:11:56   YINGZ
// add getDateInHostFormat
// 
//    Rev 1.9   Jan 21 2000 10:24:04   YINGZ
// change DSTCommonFunctions::CompareDates using infra function
// 
//    Rev 1.8   Jan 18 2000 16:47:02   YINGZ
// change name order
// 
//    Rev 1.7   Jan 18 2000 15:09:32   YINGZ
// fix bug in getFirstSequenced01AccountholderEntityName
// 
//    Rev 1.6   Jan 18 2000 11:29:52   POPESCUS
// fixed some of the settings of the global values (account & shareholder)
// 
//    Rev 1.5   Jan 14 2000 15:06:16   YINGBAOL
// add dateRangesOverlap,IsDateBetween methods
// 
//    Rev 1.4   Jan 06 2000 09:58:22   POPESCUS
// cleanup code and remove some unused methods
// 
//    Rev 1.3   Jan 05 2000 09:33:32   YINGZ
// change back to old version to avoid chaos
// 
//    Rev 1.1   Dec 23 1999 11:26:36   YINGZ
// add getFirstSequenced01AccountholderEntityName
// 
//    Rev 1.0   Dec 16 1999 12:36:28   YINGZ
// Initial revision.
// 
//    Rev 1.6   Dec 16 1999 09:58:38   YINGZ
// ?
// 
//    Rev 1.5   Dec 13 1999 14:50:12   PRAGERYA
// UnformatDate function modified
// 
//    Rev 1.4   Dec 12 1999 15:28:34   YINGZ
// add UnformatDate
// 
//    Rev 1.3   Dec 12 1999 12:21:38   PRAGERYA
// add CompareDates
// 
//    Rev 1.2   Dec 08 1999 12:20:08   YINGBAOL
// added getmarket method
*/
