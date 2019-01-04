
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Min/Max Information Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/MinMaxDetail.doc">MinMaxDetail.doc</A>.
 * 
 * @author RTS Generated
 */
public class MinMaxDetailView extends IFastView implements Serializable
{

   /**
    * Min Amount Withdrawn member variable.
    */
   private String _MinAmtWith = null;
   
   /**
    * Min Amount Outstanding member variable.
    */
   private String _MinAmtOut = null;
   
   /**
    * Optional Amount Withdrawn member variable.
    */
   private String _OptAmtWith = null;
   
   /**
    * Optional Amount Outstanding member variable.
    */
   private String _OptAmtOut = null;
   
   /**
    * Total  Amount Withdrawn member variable.
    */
   private String _TotAmtWith = null;
   
   /**
    * Tax Amount Withdrawn member variable.
    */
   private String _TaxAmtWith = null;
   
   /**
    * Total  Amount Outstanding member variable.
    */
   private String _TotAmtOut = null;
   
   /**
    * Tax Amount Outstanding member variable.
    */
   private String _TaxAmtOut = null;
   
   /**
    * Other Withdrawals/Transfers member variable.
    */
   private String _OthAmtWith = null;
   
   /**
    * Calculated Min Amount member variable.
    */
   private String _MinAmt = null;
   
   /**
    * Min Amount Shortfall member variable.
    */
   private String _MinAmtShort = null;
   
   /**
    * Calculated Max Amount member variable.
    */
   private String _MaxAmt = null;
   
   /**
    * Remaining Max Amount member variable.
    */
   private String _MaxAmtRemain = null;
   
   /**
    * Mandatory Min Amount per Year member variable.
    */
   private String _sMandMinAmtYr = null;
   
   /**
    * Min Amount Withdrawn member variable.
    */
   private String _sMinAmtWith = null;
   
   /**
    * Min Amount Outstanding member variable.
    */
   private String _sMinAmtOut = null;
   
   /**
    * Scheduled Min Amount member variable.
    */
   private String _sMinSched = null;
   
   /**
    * Min Amount Shortfall member variable.
    */
   private String _sMinAmtShort = null;
   
   /**
    * Mandatory Max  Amount per Year member variable.
    */
   private String _sMandMaxAmtYr = null;
   
   /**
    * Max Amount Withdrawn member variable.
    */
   private String _sMaxAmtWith = null;
   
   /**
    * Max Amount Outstanding member variable.
    */
   private String _sMaxAmtOut = null;
   
   /**
    * Scheduled Max Amount member variable.
    */
   private String _sMaxSched = null;
   
   /**
    * Max Amount Shortfall member variable.
    */
   private String _sMaxAmtShort = null;
   
   /**
    * Current Year Deposits member variable.
    */
   private String _mCurrYrDep = null;
   
   /**
    * Current Market Value member variable.
    */
   private String _mCurrMktValue = null;
   
   /**
    * Previous Year End Market Value member variable.
    */
   private String _mPYEMktValue = null;
   
   /**
    * Calculated Min Amount member variable.
    */
   private String _mMinAmt = null;
   
   /**
    * Min Amount Remaining member variable.
    */
   private String _mMinAmtRemain = null;
   
   /**
    * Calculated Max Amount member variable.
    */
   private String _mMaxAmt = null;
   
   /**
    * Max Amount Remaining member variable.
    */
   private String _mMaxAmtRemain = null;
   
   /**
    * Free Amount Remaining member variable.
    */
   private String _mFreeAmtRemain = null;
   
   /**
    * Free Amount Used member variable.
    */
   private String _mFreeAmtUsed = null;
   
   /**
    * Scheduled Payments Gross Amount member variable.
    */
   private String _mSchedPayGrossAmt = null;
   
   /**
    * Unscheduled Withdrawals Gross Amount member variable.
    */
   private String _mUnSchedWithGrossAmt = null;
   
   /**
    * Transfers Gross Amount member variable.
    */
   private String _mTransfGrossAmt = null;
   
   /**
    * Total Gross Amount member variable.
    */
   private String _mTotGrossAmt = null;
   
   /**
    * Scheduled Payments Gross Charges member variable.
    */
   private String _mSchedPayChrg = null;
   
   /**
    * Unscheduled Withdrawals Gross Charges member variable.
    */
   private String _mUnSchedWithChrg = null;
   
   /**
    * Transfers Gross Charges member variable.
    */
   private String _mTransfChrg = null;
   
   /**
    * Total Charges Amount member variable.
    */
   private String _mTotChrg = null;
   
   /**
    * Tax Amount on Scheduled Payments member variable.
    */
   private String _mSchedPymtTaxAmt = null;
   
   /**
    * Tax Amount on Unscheduled  Withdrawals member variable.
    */
   private String _mUnSchedWithTaxAmt = null;
   
   /**
    * Tax Amount on Transfers member variable.
    */
   private String _mTransfTaxAmt = null;
   
   /**
    * Total Tax Withheld member variable.
    */
   private String _mTotTax = null;
   
   /**
    * Scheduled Payments Net Amount member variable.
    */
   private String _mSchedPayNetAmt = null;
   
   /**
    * Unscheduled Withdrawals Net Amount member variable.
    */
   private String _mUnSchedWithNetAmt = null;
   
   /**
    * Transfers Net Amount member variable.
    */
   private String _mTransfNetAmt = null;
   
   /**
    * Total Net Amount member variable.
    */
   private String _mTotNetAmt = null;
   
   /**
    * Gross amount of the last PW with Unlocking Red Code member variable.
    */
   private String _UnLockGrossAmt = null;
   
   /**
    * Effective Date of the Last Redemption with unlocking red code member variable.
    */
   private Date _UnLockDeff = null;
   

   /**
    * Constructs the MinMaxDetailView object.
    * 
    */
   public MinMaxDetailView()
   {
      super ( new MinMaxDetailRequest() );
   }

   /**
    * Constructs the MinMaxDetailView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public MinMaxDetailView( String hostEncoding )
   {
      super ( new MinMaxDetailRequest( hostEncoding ) );
   }

   /**
    * Gets the MinMaxDetailRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The MinMaxDetailRequest object.
    */
   public final MinMaxDetailRequest getRequest()
   {
      return (MinMaxDetailRequest)getIFastRequest();
   }
        
   /**
    * Gets the Min Amount Withdrawn field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Min Amount Withdrawn or null.
    */
   public final String getMinAmtWith()
   {
      return _MinAmtWith;
   }
	
   /**
    * Gets the Min Amount Withdrawn field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Min Amount Withdrawn or the specified default value.
    */
   public final String getMinAmtWith( String defaultValue )
   {
      return _MinAmtWith == null ? defaultValue : _MinAmtWith;
   }
                  
   /**
    * Gets the Min Amount Outstanding field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Min Amount Outstanding or null.
    */
   public final String getMinAmtOut()
   {
      return _MinAmtOut;
   }
	
   /**
    * Gets the Min Amount Outstanding field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Min Amount Outstanding or the specified default value.
    */
   public final String getMinAmtOut( String defaultValue )
   {
      return _MinAmtOut == null ? defaultValue : _MinAmtOut;
   }
                  
   /**
    * Gets the Optional Amount Withdrawn field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Optional Amount Withdrawn or null.
    */
   public final String getOptAmtWith()
   {
      return _OptAmtWith;
   }
	
   /**
    * Gets the Optional Amount Withdrawn field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Optional Amount Withdrawn or the specified default value.
    */
   public final String getOptAmtWith( String defaultValue )
   {
      return _OptAmtWith == null ? defaultValue : _OptAmtWith;
   }
                  
   /**
    * Gets the Optional Amount Outstanding field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Optional Amount Outstanding or null.
    */
   public final String getOptAmtOut()
   {
      return _OptAmtOut;
   }
	
   /**
    * Gets the Optional Amount Outstanding field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Optional Amount Outstanding or the specified default value.
    */
   public final String getOptAmtOut( String defaultValue )
   {
      return _OptAmtOut == null ? defaultValue : _OptAmtOut;
   }
                  
   /**
    * Gets the Total  Amount Withdrawn field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Total  Amount Withdrawn or null.
    */
   public final String getTotAmtWith()
   {
      return _TotAmtWith;
   }
	
   /**
    * Gets the Total  Amount Withdrawn field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Total  Amount Withdrawn or the specified default value.
    */
   public final String getTotAmtWith( String defaultValue )
   {
      return _TotAmtWith == null ? defaultValue : _TotAmtWith;
   }
                  
   /**
    * Gets the Tax Amount Withdrawn field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Tax Amount Withdrawn or null.
    */
   public final String getTaxAmtWith()
   {
      return _TaxAmtWith;
   }
	
   /**
    * Gets the Tax Amount Withdrawn field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Tax Amount Withdrawn or the specified default value.
    */
   public final String getTaxAmtWith( String defaultValue )
   {
      return _TaxAmtWith == null ? defaultValue : _TaxAmtWith;
   }
                  
   /**
    * Gets the Total  Amount Outstanding field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Total  Amount Outstanding or null.
    */
   public final String getTotAmtOut()
   {
      return _TotAmtOut;
   }
	
   /**
    * Gets the Total  Amount Outstanding field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Total  Amount Outstanding or the specified default value.
    */
   public final String getTotAmtOut( String defaultValue )
   {
      return _TotAmtOut == null ? defaultValue : _TotAmtOut;
   }
                  
   /**
    * Gets the Tax Amount Outstanding field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Tax Amount Outstanding or null.
    */
   public final String getTaxAmtOut()
   {
      return _TaxAmtOut;
   }
	
   /**
    * Gets the Tax Amount Outstanding field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Tax Amount Outstanding or the specified default value.
    */
   public final String getTaxAmtOut( String defaultValue )
   {
      return _TaxAmtOut == null ? defaultValue : _TaxAmtOut;
   }
                  
   /**
    * Gets the Other Withdrawals/Transfers field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Other Withdrawals/Transfers or null.
    */
   public final String getOthAmtWith()
   {
      return _OthAmtWith;
   }
	
   /**
    * Gets the Other Withdrawals/Transfers field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Other Withdrawals/Transfers or the specified default value.
    */
   public final String getOthAmtWith( String defaultValue )
   {
      return _OthAmtWith == null ? defaultValue : _OthAmtWith;
   }
                  
   /**
    * Gets the Calculated Min Amount field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Calculated Min Amount or null.
    */
   public final String getMinAmt()
   {
      return _MinAmt;
   }
	
   /**
    * Gets the Calculated Min Amount field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Calculated Min Amount or the specified default value.
    */
   public final String getMinAmt( String defaultValue )
   {
      return _MinAmt == null ? defaultValue : _MinAmt;
   }
                  
   /**
    * Gets the Min Amount Shortfall field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Min Amount Shortfall or null.
    */
   public final String getMinAmtShort()
   {
      return _MinAmtShort;
   }
	
   /**
    * Gets the Min Amount Shortfall field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Min Amount Shortfall or the specified default value.
    */
   public final String getMinAmtShort( String defaultValue )
   {
      return _MinAmtShort == null ? defaultValue : _MinAmtShort;
   }
                  
   /**
    * Gets the Calculated Max Amount field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Calculated Max Amount or null.
    */
   public final String getMaxAmt()
   {
      return _MaxAmt;
   }
	
   /**
    * Gets the Calculated Max Amount field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Calculated Max Amount or the specified default value.
    */
   public final String getMaxAmt( String defaultValue )
   {
      return _MaxAmt == null ? defaultValue : _MaxAmt;
   }
                  
   /**
    * Gets the Remaining Max Amount field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Remaining Max Amount or null.
    */
   public final String getMaxAmtRemain()
   {
      return _MaxAmtRemain;
   }
	
   /**
    * Gets the Remaining Max Amount field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Remaining Max Amount or the specified default value.
    */
   public final String getMaxAmtRemain( String defaultValue )
   {
      return _MaxAmtRemain == null ? defaultValue : _MaxAmtRemain;
   }
                  
   /**
    * Gets the Mandatory Min Amount per Year field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Mandatory Min Amount per Year or null.
    */
   public final String getsMandMinAmtYr()
   {
      return _sMandMinAmtYr;
   }
	
   /**
    * Gets the Mandatory Min Amount per Year field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Mandatory Min Amount per Year or the specified default value.
    */
   public final String getsMandMinAmtYr( String defaultValue )
   {
      return _sMandMinAmtYr == null ? defaultValue : _sMandMinAmtYr;
   }
                  
   /**
    * Gets the Min Amount Withdrawn field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Min Amount Withdrawn or null.
    */
   public final String getsMinAmtWith()
   {
      return _sMinAmtWith;
   }
	
   /**
    * Gets the Min Amount Withdrawn field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Min Amount Withdrawn or the specified default value.
    */
   public final String getsMinAmtWith( String defaultValue )
   {
      return _sMinAmtWith == null ? defaultValue : _sMinAmtWith;
   }
                  
   /**
    * Gets the Min Amount Outstanding field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Min Amount Outstanding or null.
    */
   public final String getsMinAmtOut()
   {
      return _sMinAmtOut;
   }
	
   /**
    * Gets the Min Amount Outstanding field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Min Amount Outstanding or the specified default value.
    */
   public final String getsMinAmtOut( String defaultValue )
   {
      return _sMinAmtOut == null ? defaultValue : _sMinAmtOut;
   }
                  
   /**
    * Gets the Scheduled Min Amount field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Scheduled Min Amount or null.
    */
   public final String getsMinSched()
   {
      return _sMinSched;
   }
	
   /**
    * Gets the Scheduled Min Amount field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Scheduled Min Amount or the specified default value.
    */
   public final String getsMinSched( String defaultValue )
   {
      return _sMinSched == null ? defaultValue : _sMinSched;
   }
                  
   /**
    * Gets the Min Amount Shortfall field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Min Amount Shortfall or null.
    */
   public final String getsMinAmtShort()
   {
      return _sMinAmtShort;
   }
	
   /**
    * Gets the Min Amount Shortfall field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Min Amount Shortfall or the specified default value.
    */
   public final String getsMinAmtShort( String defaultValue )
   {
      return _sMinAmtShort == null ? defaultValue : _sMinAmtShort;
   }
                  
   /**
    * Gets the Mandatory Max  Amount per Year field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Mandatory Max  Amount per Year or null.
    */
   public final String getsMandMaxAmtYr()
   {
      return _sMandMaxAmtYr;
   }
	
   /**
    * Gets the Mandatory Max  Amount per Year field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Mandatory Max  Amount per Year or the specified default value.
    */
   public final String getsMandMaxAmtYr( String defaultValue )
   {
      return _sMandMaxAmtYr == null ? defaultValue : _sMandMaxAmtYr;
   }
                  
   /**
    * Gets the Max Amount Withdrawn field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Max Amount Withdrawn or null.
    */
   public final String getsMaxAmtWith()
   {
      return _sMaxAmtWith;
   }
	
   /**
    * Gets the Max Amount Withdrawn field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Max Amount Withdrawn or the specified default value.
    */
   public final String getsMaxAmtWith( String defaultValue )
   {
      return _sMaxAmtWith == null ? defaultValue : _sMaxAmtWith;
   }
                  
   /**
    * Gets the Max Amount Outstanding field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Max Amount Outstanding or null.
    */
   public final String getsMaxAmtOut()
   {
      return _sMaxAmtOut;
   }
	
   /**
    * Gets the Max Amount Outstanding field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Max Amount Outstanding or the specified default value.
    */
   public final String getsMaxAmtOut( String defaultValue )
   {
      return _sMaxAmtOut == null ? defaultValue : _sMaxAmtOut;
   }
                  
   /**
    * Gets the Scheduled Max Amount field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Scheduled Max Amount or null.
    */
   public final String getsMaxSched()
   {
      return _sMaxSched;
   }
	
   /**
    * Gets the Scheduled Max Amount field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Scheduled Max Amount or the specified default value.
    */
   public final String getsMaxSched( String defaultValue )
   {
      return _sMaxSched == null ? defaultValue : _sMaxSched;
   }
                  
   /**
    * Gets the Max Amount Shortfall field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Max Amount Shortfall or null.
    */
   public final String getsMaxAmtShort()
   {
      return _sMaxAmtShort;
   }
	
   /**
    * Gets the Max Amount Shortfall field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Max Amount Shortfall or the specified default value.
    */
   public final String getsMaxAmtShort( String defaultValue )
   {
      return _sMaxAmtShort == null ? defaultValue : _sMaxAmtShort;
   }
                  
   /**
    * Gets the Current Year Deposits field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Current Year Deposits or null.
    */
   public final String getmCurrYrDep()
   {
      return _mCurrYrDep;
   }
	
   /**
    * Gets the Current Year Deposits field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Current Year Deposits or the specified default value.
    */
   public final String getmCurrYrDep( String defaultValue )
   {
      return _mCurrYrDep == null ? defaultValue : _mCurrYrDep;
   }
                  
   /**
    * Gets the Current Market Value field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Current Market Value or null.
    */
   public final String getmCurrMktValue()
   {
      return _mCurrMktValue;
   }
	
   /**
    * Gets the Current Market Value field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Current Market Value or the specified default value.
    */
   public final String getmCurrMktValue( String defaultValue )
   {
      return _mCurrMktValue == null ? defaultValue : _mCurrMktValue;
   }
                  
   /**
    * Gets the Previous Year End Market Value field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Previous Year End Market Value or null.
    */
   public final String getmPYEMktValue()
   {
      return _mPYEMktValue;
   }
	
   /**
    * Gets the Previous Year End Market Value field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Previous Year End Market Value or the specified default value.
    */
   public final String getmPYEMktValue( String defaultValue )
   {
      return _mPYEMktValue == null ? defaultValue : _mPYEMktValue;
   }
                  
   /**
    * Gets the Calculated Min Amount field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Calculated Min Amount or null.
    */
   public final String getmMinAmt()
   {
      return _mMinAmt;
   }
	
   /**
    * Gets the Calculated Min Amount field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Calculated Min Amount or the specified default value.
    */
   public final String getmMinAmt( String defaultValue )
   {
      return _mMinAmt == null ? defaultValue : _mMinAmt;
   }
                  
   /**
    * Gets the Min Amount Remaining field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Min Amount Remaining or null.
    */
   public final String getmMinAmtRemain()
   {
      return _mMinAmtRemain;
   }
	
   /**
    * Gets the Min Amount Remaining field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Min Amount Remaining or the specified default value.
    */
   public final String getmMinAmtRemain( String defaultValue )
   {
      return _mMinAmtRemain == null ? defaultValue : _mMinAmtRemain;
   }
                  
   /**
    * Gets the Calculated Max Amount field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Calculated Max Amount or null.
    */
   public final String getmMaxAmt()
   {
      return _mMaxAmt;
   }
	
   /**
    * Gets the Calculated Max Amount field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Calculated Max Amount or the specified default value.
    */
   public final String getmMaxAmt( String defaultValue )
   {
      return _mMaxAmt == null ? defaultValue : _mMaxAmt;
   }
                  
   /**
    * Gets the Max Amount Remaining field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Max Amount Remaining or null.
    */
   public final String getmMaxAmtRemain()
   {
      return _mMaxAmtRemain;
   }
	
   /**
    * Gets the Max Amount Remaining field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Max Amount Remaining or the specified default value.
    */
   public final String getmMaxAmtRemain( String defaultValue )
   {
      return _mMaxAmtRemain == null ? defaultValue : _mMaxAmtRemain;
   }
                  
   /**
    * Gets the Free Amount Remaining field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Free Amount Remaining or null.
    */
   public final String getmFreeAmtRemain()
   {
      return _mFreeAmtRemain;
   }
	
   /**
    * Gets the Free Amount Remaining field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Free Amount Remaining or the specified default value.
    */
   public final String getmFreeAmtRemain( String defaultValue )
   {
      return _mFreeAmtRemain == null ? defaultValue : _mFreeAmtRemain;
   }
                  
   /**
    * Gets the Free Amount Used field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Free Amount Used or null.
    */
   public final String getmFreeAmtUsed()
   {
      return _mFreeAmtUsed;
   }
	
   /**
    * Gets the Free Amount Used field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Free Amount Used or the specified default value.
    */
   public final String getmFreeAmtUsed( String defaultValue )
   {
      return _mFreeAmtUsed == null ? defaultValue : _mFreeAmtUsed;
   }
                  
   /**
    * Gets the Scheduled Payments Gross Amount field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Scheduled Payments Gross Amount or null.
    */
   public final String getmSchedPayGrossAmt()
   {
      return _mSchedPayGrossAmt;
   }
	
   /**
    * Gets the Scheduled Payments Gross Amount field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Scheduled Payments Gross Amount or the specified default value.
    */
   public final String getmSchedPayGrossAmt( String defaultValue )
   {
      return _mSchedPayGrossAmt == null ? defaultValue : _mSchedPayGrossAmt;
   }
                  
   /**
    * Gets the Unscheduled Withdrawals Gross Amount field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Unscheduled Withdrawals Gross Amount or null.
    */
   public final String getmUnSchedWithGrossAmt()
   {
      return _mUnSchedWithGrossAmt;
   }
	
   /**
    * Gets the Unscheduled Withdrawals Gross Amount field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Unscheduled Withdrawals Gross Amount or the specified default value.
    */
   public final String getmUnSchedWithGrossAmt( String defaultValue )
   {
      return _mUnSchedWithGrossAmt == null ? defaultValue : _mUnSchedWithGrossAmt;
   }
                  
   /**
    * Gets the Transfers Gross Amount field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Transfers Gross Amount or null.
    */
   public final String getmTransfGrossAmt()
   {
      return _mTransfGrossAmt;
   }
	
   /**
    * Gets the Transfers Gross Amount field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Transfers Gross Amount or the specified default value.
    */
   public final String getmTransfGrossAmt( String defaultValue )
   {
      return _mTransfGrossAmt == null ? defaultValue : _mTransfGrossAmt;
   }
                  
   /**
    * Gets the Total Gross Amount field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Total Gross Amount or null.
    */
   public final String getmTotGrossAmt()
   {
      return _mTotGrossAmt;
   }
	
   /**
    * Gets the Total Gross Amount field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Total Gross Amount or the specified default value.
    */
   public final String getmTotGrossAmt( String defaultValue )
   {
      return _mTotGrossAmt == null ? defaultValue : _mTotGrossAmt;
   }
                  
   /**
    * Gets the Scheduled Payments Gross Charges field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Scheduled Payments Gross Charges or null.
    */
   public final String getmSchedPayChrg()
   {
      return _mSchedPayChrg;
   }
	
   /**
    * Gets the Scheduled Payments Gross Charges field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Scheduled Payments Gross Charges or the specified default value.
    */
   public final String getmSchedPayChrg( String defaultValue )
   {
      return _mSchedPayChrg == null ? defaultValue : _mSchedPayChrg;
   }
                  
   /**
    * Gets the Unscheduled Withdrawals Gross Charges field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Unscheduled Withdrawals Gross Charges or null.
    */
   public final String getmUnSchedWithChrg()
   {
      return _mUnSchedWithChrg;
   }
	
   /**
    * Gets the Unscheduled Withdrawals Gross Charges field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Unscheduled Withdrawals Gross Charges or the specified default value.
    */
   public final String getmUnSchedWithChrg( String defaultValue )
   {
      return _mUnSchedWithChrg == null ? defaultValue : _mUnSchedWithChrg;
   }
                  
   /**
    * Gets the Transfers Gross Charges field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Transfers Gross Charges or null.
    */
   public final String getmTransfChrg()
   {
      return _mTransfChrg;
   }
	
   /**
    * Gets the Transfers Gross Charges field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Transfers Gross Charges or the specified default value.
    */
   public final String getmTransfChrg( String defaultValue )
   {
      return _mTransfChrg == null ? defaultValue : _mTransfChrg;
   }
                  
   /**
    * Gets the Total Charges Amount field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Total Charges Amount or null.
    */
   public final String getmTotChrg()
   {
      return _mTotChrg;
   }
	
   /**
    * Gets the Total Charges Amount field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Total Charges Amount or the specified default value.
    */
   public final String getmTotChrg( String defaultValue )
   {
      return _mTotChrg == null ? defaultValue : _mTotChrg;
   }
                  
   /**
    * Gets the Tax Amount on Scheduled Payments field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Tax Amount on Scheduled Payments or null.
    */
   public final String getmSchedPymtTaxAmt()
   {
      return _mSchedPymtTaxAmt;
   }
	
   /**
    * Gets the Tax Amount on Scheduled Payments field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Tax Amount on Scheduled Payments or the specified default value.
    */
   public final String getmSchedPymtTaxAmt( String defaultValue )
   {
      return _mSchedPymtTaxAmt == null ? defaultValue : _mSchedPymtTaxAmt;
   }
                  
   /**
    * Gets the Tax Amount on Unscheduled  Withdrawals field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Tax Amount on Unscheduled  Withdrawals or null.
    */
   public final String getmUnSchedWithTaxAmt()
   {
      return _mUnSchedWithTaxAmt;
   }
	
   /**
    * Gets the Tax Amount on Unscheduled  Withdrawals field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Tax Amount on Unscheduled  Withdrawals or the specified default value.
    */
   public final String getmUnSchedWithTaxAmt( String defaultValue )
   {
      return _mUnSchedWithTaxAmt == null ? defaultValue : _mUnSchedWithTaxAmt;
   }
                  
   /**
    * Gets the Tax Amount on Transfers field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Tax Amount on Transfers or null.
    */
   public final String getmTransfTaxAmt()
   {
      return _mTransfTaxAmt;
   }
	
   /**
    * Gets the Tax Amount on Transfers field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Tax Amount on Transfers or the specified default value.
    */
   public final String getmTransfTaxAmt( String defaultValue )
   {
      return _mTransfTaxAmt == null ? defaultValue : _mTransfTaxAmt;
   }
                  
   /**
    * Gets the Total Tax Withheld field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Total Tax Withheld or null.
    */
   public final String getmTotTax()
   {
      return _mTotTax;
   }
	
   /**
    * Gets the Total Tax Withheld field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Total Tax Withheld or the specified default value.
    */
   public final String getmTotTax( String defaultValue )
   {
      return _mTotTax == null ? defaultValue : _mTotTax;
   }
                  
   /**
    * Gets the Scheduled Payments Net Amount field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Scheduled Payments Net Amount or null.
    */
   public final String getmSchedPayNetAmt()
   {
      return _mSchedPayNetAmt;
   }
	
   /**
    * Gets the Scheduled Payments Net Amount field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Scheduled Payments Net Amount or the specified default value.
    */
   public final String getmSchedPayNetAmt( String defaultValue )
   {
      return _mSchedPayNetAmt == null ? defaultValue : _mSchedPayNetAmt;
   }
                  
   /**
    * Gets the Unscheduled Withdrawals Net Amount field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Unscheduled Withdrawals Net Amount or null.
    */
   public final String getmUnSchedWithNetAmt()
   {
      return _mUnSchedWithNetAmt;
   }
	
   /**
    * Gets the Unscheduled Withdrawals Net Amount field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Unscheduled Withdrawals Net Amount or the specified default value.
    */
   public final String getmUnSchedWithNetAmt( String defaultValue )
   {
      return _mUnSchedWithNetAmt == null ? defaultValue : _mUnSchedWithNetAmt;
   }
                  
   /**
    * Gets the Transfers Net Amount field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Transfers Net Amount or null.
    */
   public final String getmTransfNetAmt()
   {
      return _mTransfNetAmt;
   }
	
   /**
    * Gets the Transfers Net Amount field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Transfers Net Amount or the specified default value.
    */
   public final String getmTransfNetAmt( String defaultValue )
   {
      return _mTransfNetAmt == null ? defaultValue : _mTransfNetAmt;
   }
                  
   /**
    * Gets the Total Net Amount field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Total Net Amount or null.
    */
   public final String getmTotNetAmt()
   {
      return _mTotNetAmt;
   }
	
   /**
    * Gets the Total Net Amount field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Total Net Amount or the specified default value.
    */
   public final String getmTotNetAmt( String defaultValue )
   {
      return _mTotNetAmt == null ? defaultValue : _mTotNetAmt;
   }
                  
   /**
    * Gets the Gross amount of the last PW with Unlocking Red Code field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Gross amount of the last PW with Unlocking Red Code or null.
    */
   public final String getUnLockGrossAmt()
   {
      return _UnLockGrossAmt;
   }
	
   /**
    * Gets the Gross amount of the last PW with Unlocking Red Code field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Gross amount of the last PW with Unlocking Red Code or the specified default value.
    */
   public final String getUnLockGrossAmt( String defaultValue )
   {
      return _UnLockGrossAmt == null ? defaultValue : _UnLockGrossAmt;
   }
                  
   /**
    * Gets the Effective Date of the Last Redemption with unlocking red code field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Effective Date of the Last Redemption with unlocking red code or null.
    */
   public final Date getUnLockDeff()
   {
      return _UnLockDeff;
   }
	
   /**
    * Gets the Effective Date of the Last Redemption with unlocking red code field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Effective Date of the Last Redemption with unlocking red code or the specified default value.
    */
   public final Date getUnLockDeff( Date defaultValue )
   {
      return _UnLockDeff == null ? defaultValue : _UnLockDeff;
   }
                  
   /**
    * Implements the abstract base method to decode
    * the host formatted response.
    * 
    * @param response Host formatted response object.
    * @exception ParseException
    */
   protected void decodeFields( RTSResponseDecodeBuffer responseBuffer ) throws ParseException, UnsupportedEncodingException
   {
      
      // single-record section
      _MinAmtWith = responseBuffer.decodeString(responseBuffer.getNextField());
      _MinAmtOut = responseBuffer.decodeString(responseBuffer.getNextField());
      _OptAmtWith = responseBuffer.decodeString(responseBuffer.getNextField());
      _OptAmtOut = responseBuffer.decodeString(responseBuffer.getNextField());
      _TotAmtWith = responseBuffer.decodeString(responseBuffer.getNextField());
      _TaxAmtWith = responseBuffer.decodeString(responseBuffer.getNextField());
      _TotAmtOut = responseBuffer.decodeString(responseBuffer.getNextField());
      _TaxAmtOut = responseBuffer.decodeString(responseBuffer.getNextField());
      _OthAmtWith = responseBuffer.decodeString(responseBuffer.getNextField());
      _MinAmt = responseBuffer.decodeString(responseBuffer.getNextField());
      _MinAmtShort = responseBuffer.decodeString(responseBuffer.getNextField());
      _MaxAmt = responseBuffer.decodeString(responseBuffer.getNextField());
      _MaxAmtRemain = responseBuffer.decodeString(responseBuffer.getNextField());
      _sMandMinAmtYr = responseBuffer.decodeString(responseBuffer.getNextField());
      _sMinAmtWith = responseBuffer.decodeString(responseBuffer.getNextField());
      _sMinAmtOut = responseBuffer.decodeString(responseBuffer.getNextField());
      _sMinSched = responseBuffer.decodeString(responseBuffer.getNextField());
      _sMinAmtShort = responseBuffer.decodeString(responseBuffer.getNextField());
      _sMandMaxAmtYr = responseBuffer.decodeString(responseBuffer.getNextField());
      _sMaxAmtWith = responseBuffer.decodeString(responseBuffer.getNextField());
      _sMaxAmtOut = responseBuffer.decodeString(responseBuffer.getNextField());
      _sMaxSched = responseBuffer.decodeString(responseBuffer.getNextField());
      _sMaxAmtShort = responseBuffer.decodeString(responseBuffer.getNextField());
      _mCurrYrDep = responseBuffer.decodeString(responseBuffer.getNextField());
      _mCurrMktValue = responseBuffer.decodeString(responseBuffer.getNextField());
      _mPYEMktValue = responseBuffer.decodeString(responseBuffer.getNextField());
      _mMinAmt = responseBuffer.decodeString(responseBuffer.getNextField());
      _mMinAmtRemain = responseBuffer.decodeString(responseBuffer.getNextField());
      _mMaxAmt = responseBuffer.decodeString(responseBuffer.getNextField());
      _mMaxAmtRemain = responseBuffer.decodeString(responseBuffer.getNextField());
      _mFreeAmtRemain = responseBuffer.decodeString(responseBuffer.getNextField());
      _mFreeAmtUsed = responseBuffer.decodeString(responseBuffer.getNextField());
      _mSchedPayGrossAmt = responseBuffer.decodeString(responseBuffer.getNextField());
      _mUnSchedWithGrossAmt = responseBuffer.decodeString(responseBuffer.getNextField());
      _mTransfGrossAmt = responseBuffer.decodeString(responseBuffer.getNextField());
      _mTotGrossAmt = responseBuffer.decodeString(responseBuffer.getNextField());
      _mSchedPayChrg = responseBuffer.decodeString(responseBuffer.getNextField());
      _mUnSchedWithChrg = responseBuffer.decodeString(responseBuffer.getNextField());
      _mTransfChrg = responseBuffer.decodeString(responseBuffer.getNextField());
      _mTotChrg = responseBuffer.decodeString(responseBuffer.getNextField());
      _mSchedPymtTaxAmt = responseBuffer.decodeString(responseBuffer.getNextField());
      _mUnSchedWithTaxAmt = responseBuffer.decodeString(responseBuffer.getNextField());
      _mTransfTaxAmt = responseBuffer.decodeString(responseBuffer.getNextField());
      _mTotTax = responseBuffer.decodeString(responseBuffer.getNextField());
      _mSchedPayNetAmt = responseBuffer.decodeString(responseBuffer.getNextField());
      _mUnSchedWithNetAmt = responseBuffer.decodeString(responseBuffer.getNextField());
      _mTransfNetAmt = responseBuffer.decodeString(responseBuffer.getNextField());
      _mTotNetAmt = responseBuffer.decodeString(responseBuffer.getNextField());
      _UnLockGrossAmt = responseBuffer.decodeString(responseBuffer.getNextField());
      _UnLockDeff = responseBuffer.decodeDate(responseBuffer.getNextField());
                  

   }

}
      
