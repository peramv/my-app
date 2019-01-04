#pragma once
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
// ^FILE   : DSTCommonFunction.hpp
// ^AUTHOR : Zijian Ying
// ^DATE   : Nov.19, 1999
//
// ^CLASS    : DSTCommonFunction
// ^INHERITS FROM :           
//
// ^CLASS DESCRIPTION : 
//
//
//******************************************************************************
#pragma warning( disable : 4786)  

#include <srcprag.h>
#include <commonport.h>
#include <dstring.hpp>
#include <vector>
#include <boost\utility.hpp>
#include <bfutil\bfdate.hpp>

class BFData;
class BFFieldId;
class BigDecimal;

// Import/Export resolution
#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

namespace MARKET_IDS
{
   extern IFASTCBO_LINKAGE I_CHAR * const CANADA;
   extern IFASTCBO_LINKAGE I_CHAR * const JAPAN;
   extern IFASTCBO_LINKAGE I_CHAR * const LUXEMBOURG;
}

namespace DSTCommonFunctions
{
   IFASTCBO_LINKAGE DString getMarket();
   IFASTCBO_LINKAGE DString getClient();

   IFASTCBO_LINKAGE DString getMask(const BFFieldId& idField);
   IFASTCBO_LINKAGE DString getRawMask(const BFFieldId& idField);
   IFASTCBO_LINKAGE DString getMask(const BFFieldId& idField, const DString& _locale);

   IFASTCBO_LINKAGE bool isStringEmptyOrJustContainSpace( const DString& str );
   IFASTCBO_LINKAGE bool codeInList( const DString& dstrCode, const DString& dstrCodeList, bool bStripTrailingZeros = false ); 
   /**
    * returns the description coresponding to the code in strSubstList
    * @param dstrCode - the code
    * @param strSubstList - the substitution list with the pattern: "code=description;code=description;..."
   */
   IFASTCBO_LINKAGE DString getDescription( const DString& strCode, const DString& strSubstList );
   /**
    * returns the description coreponding to the code in the substitution list for idField and pClientLocale 
    * @param dstrCode - the code
    * @param idField
   */
   IFASTCBO_LINKAGE DString getDescription( const DString& strCode, const BFFieldId& idField );

   IFASTCBO_LINKAGE int NumOfDecimals( const DString& Amount );
   IFASTCBO_LINKAGE double convertToDouble( const DString& Amount );
   IFASTCBO_LINKAGE BigDecimal convertToBigDecimal( const DString& Amount );
   IFASTCBO_LINKAGE DString doubleToDString(const BFFieldId& idField, const double dValue);

   enum DATE_ORDER
   {
      FIRST_EARLIER, EQUAL, SECOND_EARLIER
   };

   IFASTCBO_LINKAGE DATE_ORDER CompareDates( const DString& Date1, const DString& Date2, BFDate::DATE_FORMAT eFormat = BFDate::DF_DDATE_DEPRECATED);
   IFASTCBO_LINKAGE bool dateRangesOverlap( const DString& strStrtDate1, const DString& strEndDate1, const DString& strStrtDate2, const DString& strEndDate2);
   IFASTCBO_LINKAGE bool IsDateBetween( const DString& strStrtDate, const DString& strEndDate, const DString& strDate);
   IFASTCBO_LINKAGE void UnformatDate( const DString& formattedDate, DString &unformattedDate );
   IFASTCBO_LINKAGE bool isValidDate( DString& strDate );
   IFASTCBO_LINKAGE bool BuildAge( const DString& birthDate, const DString& currDate, DString& years, DString& months );
   IFASTCBO_LINKAGE bool addDays( DString& dstrDateIn, DString& dstrDateOut, int nDays );
   IFASTCBO_LINKAGE bool subtractDays( DString& dstrDateIn, DString& dstrDateOut, int nDays );
   IFASTCBO_LINKAGE void addMonths( DString& dstrDateIn, DString& dstrDateOut, double& dMonths );

   IFASTCBO_LINKAGE void convertToSortableDate ( const BFFieldId& idField, const DString& dstrOriDate, DString& dstrSortableDate );
   IFASTCBO_LINKAGE void getFormat12319999Date(DString &Date);
   IFASTCBO_LINKAGE int getDayFromUnFormattedDate ( const DString& dstrDate );
   IFASTCBO_LINKAGE int getMonthFromUnFormattedDate ( const DString& dstrDate );
   IFASTCBO_LINKAGE int getYearFromUnFormattedDate ( const DString& dstrDate );
   IFASTCBO_LINKAGE void getEndOfMonthUnFormattedDate ( int nMonth, int nYear, DString& dstrDate );
   IFASTCBO_LINKAGE void getBeginOfMonthUnFormattedDate ( int nMonth, int nYear, DString& dstrDate );

   IFASTCBO_LINKAGE void logTime( const DString&  dstrComment );
   IFASTCBO_LINKAGE int getDayPosition( );
   IFASTCBO_LINKAGE int getMonthPosition( );
   IFASTCBO_LINKAGE int getYearPosition( );
   IFASTCBO_LINKAGE void formatToolTipDate( const BFFieldId& idField, DString& strDate );
   IFASTCBO_LINKAGE long getOffSetBetweenTwoDates( const DString& dstrDate1, const DString& dstrDate2, long lOffSet );
   IFASTCBO_LINKAGE void formattedField( const BFFieldId& idField, int iPrecision, DString &dstrValue );
   IFASTCBO_LINKAGE void convertToSortableDateInDec ( const DString& dstrOriDate, DString& dstrSortableDate );
   IFASTCBO_LINKAGE void stripSeparatorforDecimal(DString& dstrValue);
   IFASTCBO_LINKAGE int extractFieldFromDate( const DString& strField, DString& strDateField );
   IFASTCBO_LINKAGE int  compareDateYear(const DString& date1,const DString& date2 );
   IFASTCBO_LINKAGE void FormatDate( DString &dstrDate );
   IFASTCBO_LINKAGE void FormatDateByString( DString &dstrDate, const DString& dateFormat);
   IFASTCBO_LINKAGE void DisplayFormat( DString &dstrDecimalValue, const BFFieldId& idField );
   IFASTCBO_LINKAGE void DisplayUnFormat( DString &dstrDecimalValue, const BFFieldId& idField );
   IFASTCBO_LINKAGE std::vector<DString>& tokenizeString( DString dstrInput, std::vector<DString>& vOutput ); 
   IFASTCBO_LINKAGE bool bValidateTime(DString dstrTime);
 }

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCommonFunction.hpp-arc  $
 * 
 *    Rev 1.54   Mar 16 2012 13:35:02   dchatcha
 * P0186484 FN05 - SEG Trade Processing, new validations.
 * 
 *    Rev 1.53   Jun 18 2010 10:23:08   jankovii
 * IN 1923112 -  R96_RRIF Transfer_Error Msg displays when Sum of allocation 
 * 
 *    Rev 1.52   Aug 22 2007 17:09:54   smithdav
 * IN 982850,  IN    - Add DayOfMonth field conditions to RRIF.
 * 
 *    Rev 1.51   Jul 11 2005 17:22:40   Fengyong
 * PET1250FN02 - European numeric enahncement - conditions
 * decimal format 
 * 
 *    Rev 1.50   Nov 26 2004 14:13:20   popescu
 * PTS 10034524, CompareDates method has an extra parameter to allow callers to pass in the date format to be used. Callers can use DF_DISPLAY to force the use of the Reg 'Display Masks' value.
 * 
 *    Rev 1.49   Nov 14 2004 14:33:08   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.48   Sep 08 2003 09:11:26   YINGBAOL
 * add  formatdate method
 * 
 *    Rev 1.47   Jul 04 2003 15:35:48   YINGBAOL
 * add  extractFieldFromDate( ...)	and   compareDateYear(...) method
 * 
 *    Rev 1.46   Apr 22 2003 14:49:36   FENGYONG
 * Add fundction strip seperator for decimal
 * 
 *    Rev 1.45   Mar 21 2003 18:06:20   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.44   Oct 09 2002 23:54:22   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.43   Aug 29 2002 12:52:12   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.42   Jun 25 2002 09:38:08   PURDYECH
 * Default ClientLocale is now set at application level through the Market Registry setting
 * 
 *    Rev 1.41   Jun 07 2002 17:36:02   KOVACSRO
 * Removed bank information since it belongs to bank.
 * 
 *    Rev 1.40   22 May 2002 18:21:22   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.39   19 Mar 2002 13:15:38   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.38   Feb 28 2002 12:50:10   YINGBAOL
 * add   convertToSortableDateInDec method ;
 * 
 *    Rev 1.37   Dec 17 2001 15:41:54   ZHANGCEL
 * Added a new function: formattedField()
 * 
 *    Rev 1.36   Nov 20 2001 09:53:08   JANKAREN
 * added new method getOffSetBetweenTwoDates()
 * 
 *    Rev 1.35   21 Oct 2001 16:36:34   HSUCHIN
 * added new function formatToolTipDate to format date into mm/dd/yyyy (with slashes)
 * 
 *    Rev 1.34   14 Oct 2001 15:24:00   HSUCHIN
 * added 3 new functions getDayPosition, getMonthPosition, getYearPosition.
 * 
 *    Rev 1.33   02 Oct 2001 11:41:06   KOVACSRO
 * Added logTime method.
 * 
 *    Rev 1.32   14 Sep 2001 16:54:40   KOVACSRO
 * Added some new methods for dates.
 * 
 *    Rev 1.31   Aug 07 2001 15:18:06   YINGBAOL
 * fix default value issues
 * 
 *    Rev 1.30   17 Jul 2001 13:23:08   HSUCHIN
 * added convertToSortableDate function
 * 
 *    Rev 1.29   Jun 12 2001 14:19:38   DINACORN
 * Sync. up with SSB (1.24.1.2 + 1.24.1.3)
 * 
 *    Rev 1.28   01 Jun 2001 11:35:30   HSUCHIN
 * bug fix in addmonths function
 * 
 *    Rev 1.27   23 May 2001 12:31:52   HSUCHIN
 * added 2 functions addmonths and subtractdays for date manipulation
 * 
 *    Rev 1.26   10 May 2001 11:38:28   HSUCHIN
 * Sync up with SSB
 * 
 *    Rev 1.25   03 May 2001 14:04:02   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.24   Mar 30 2001 16:48:32   YINGZ
 * add getRunMode
 * 
 *    Rev 1.23   Mar 30 2001 10:14:56   OLTEANCR
 * added getDescription(..)
 * 
 *    Rev 1.22   30 Mar 2001 10:05:20   HSUCHIN
 * added funtion to retrieve SplitComm flag 
 * 
 *    Rev 1.21   Mar 29 2001 15:37:48   DINACORN
 * Used DSTCommonFunctions MARKET_IDS constants
 * 
 *    Rev 1.20   Mar 21 2001 14:34:34   FENGYONG
 * Add function
 * 
 *    Rev 1.18   21 Mar 2001 12:20:18   KOVACSRO
 * Added new parameter bStripTrailingZeros for codeInList.
 * 
 *    Rev 1.17   Feb 12 2001 15:04:40   DINACORN
 * Change "MSDW_JAP" to "JAPAN
 * 
 *    Rev 1.16   Feb 06 2001 14:15:36   JANKAREN
 * Add addDays method
 * 
 *    Rev 1.15   Nov 17 2000 12:17:14   OLTEANCR
 * codeInList(...) - static
 * 
 *    Rev 1.14   Nov 17 2000 10:37:34   WINNIE
 * add codelnlist function
 * 
 *    Rev 1.13   Oct 23 2000 13:59:00   FENGYONG
 * Add local to getmask function
 * 
 *    Rev 1.12   Oct 23 2000 13:54:54   FENGYONG
 * Add function
 * 
 *    Rev 1.11   Aug 29 2000 16:17:56   YINGZ
 * add isValidDate to check date
 * 
 *    Rev 1.10   Jul 31 2000 17:13:38   YINGZ
 * add getMask
 * 
 *    Rev 1.9   Jul 14 2000 11:14:32   YINGBAOL
 * pass by reference instead of value
 * 
 *    Rev 1.8   Jul 11 2000 13:35:26   YINGBAOL
 * add GetFundClassCode method
 * 
 *    Rev 1.7   Jun 01 2000 14:56:50   BUZILA
 * putting LastName first on entity search
 * 
 *    Rev 1.6   Apr 25 2000 15:37:02   HUANGSHA
 * added function doubleToDString()
 * 
 *    Rev 1.5   Apr 18 2000 11:14:48   WINNIE
 * new convertTodouble
 * 
 *    Rev 1.4   Apr 13 2000 15:04:50   DT24433
 * not much
 * 
 *    Rev 1.3   Mar 20 2000 17:11:26   HSUCHIN
 * added GetFundNumber
 * 
 *    Rev 1.2   Mar 09 2000 14:30:52   VASILEAD
 * Updated Entity screen for C2
 * 
 *    Rev 1.1   Mar 07 2000 17:01:08   POPESCUS
 * added a flag to the getFirstSequenced01AccountholderEntityName;
 * based on it the kana or kanji name is retrieved;
 * default is kanji
 * 
 *    Rev 1.0   Feb 15 2000 10:59:06   SMITHDAV
 * Initial revision.
// 
//    Rev 1.11   Feb 02 2000 18:09:52   BUZILA
// changes
// 
//    Rev 1.10   Jan 21 2000 13:11:20   YINGZ
// add getDateInHostFormat
// 
//    Rev 1.9   Jan 18 2000 11:29:48   POPESCUS
// fixed some of the settings of the global values (account & shareholder)
// 
//    Rev 1.8   Jan 14 2000 15:09:42   YINGBAOL
// modify validation
// 
//    Rev 1.7   Jan 06 2000 09:58:14   POPESCUS
// cleanup code and remove some unused methods
// 
//    Rev 1.6   Jan 04 2000 17:43:50   YINGZ
// save work
// 
//    Rev 1.5   Dec 23 1999 11:26:46   YINGZ
// add getFirstSequenced01AccountholderEntityName
// 
//    Rev 1.4   Dec 16 1999 12:35:24   YINGZ
// add NumOfDecimals
// 
//    Rev 1.3   Dec 12 1999 15:28:52   YINGZ
// add UnformatDate
// 
//    Rev 1.2   Dec 12 1999 12:26:00   PRAGERYA
// add CompareDates
// 
//    Rev 1.1   Dec 08 1999 12:19:44   YINGBAOL
// added getmarket method
 * 
   */
