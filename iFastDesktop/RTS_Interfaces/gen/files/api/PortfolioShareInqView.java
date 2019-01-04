
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Portfolio Inquiry by Shareholder Group view.
 * For additional view information see <A HREF="../../../../viewspecs/PortfolioShareInq.doc">PortfolioShareInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class PortfolioShareInqView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * ProdPortfolio UUID member array.
    */
   private String[] _ProdPortfolioUUID = null;
   
   /**
    * ProdPortfolio Code member array.
    */
   private String[] _ProdPortfolioCode = null;
   
   /**
    * ProdPortfolio Name member array.
    */
   private String[] _ProdPortfolioName = null;
   
   /**
    * Effective Date member array.
    */
   private Date[] _Deff = null;
   
   /**
    * Stop Date member array.
    */
   private Date[] _StopDate = null;
   
   /**
    * Flag indicating if seq funds are parts of the portfolio member array.
    */
   private Boolean[] _SegFundIncl = null;
   
   /**
    * Flag that indicates if Shareholder Group has Portfolio with Commitment Fund member array.
    */
   private Boolean[] _CommitApplicable = null;
   

   /**
    * Constructs the PortfolioShareInqView object.
    * 
    */
   public PortfolioShareInqView()
   {
      super ( new PortfolioShareInqRequest() );
   }

   /**
    * Constructs the PortfolioShareInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public PortfolioShareInqView( String hostEncoding )
   {
      super ( new PortfolioShareInqRequest( hostEncoding ) );
   }

   /**
    * Gets the PortfolioShareInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The PortfolioShareInqRequest object.
    */
   public final PortfolioShareInqRequest getRequest()
   {
      return (PortfolioShareInqRequest)getIFastRequest();
   }
        
   /**
    * Gets the Record Count for the repeatable response.
    * 
    * @return The number of records in the repeating fields.
    */
   public int getRecordCount()
   {
      return _RepeatCount;
   }

   /**
    * Gets the Record Count for the repeatable response.
    * 
    * @return The number of records in the repeating fields.
    */
   public final int getRepeatCount()
   {
      return _RepeatCount;
   }

   /**
    * Decodes the repeat count value from the host 
    * respones.
    * 
    * @param response Host formatted response object.
    * @exception ParseException
    */
   private final void decodeRepeatCount( RTSResponseDecodeBuffer responseBuffer ) throws ParseException, UnsupportedEncodingException
   {
      int receivedRecordCount = responseBuffer.decodeInteger(responseBuffer.getNextField()).intValue();
      _RepeatCount += receivedRecordCount;
   }

   /**
    * Gets the ProdPortfolio UUID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ProdPortfolio UUID or null.
    */
   public final String getProdPortfolioUUID( int index )
   {
      return _ProdPortfolioUUID[index];
   }
    
   /**
    * Gets the ProdPortfolio UUID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ProdPortfolio UUID or the specified default value.
    */
   public final String getProdPortfolioUUID( int index, String defaultValue )
   {
      return _ProdPortfolioUUID[index] == null ? defaultValue : _ProdPortfolioUUID[index];
   }
    
   /**
    * Gets the array of ProdPortfolio UUID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ProdPortfolio UUID values.
    */
   public final String[] getProdPortfolioUUIDArray()
   {
      return _ProdPortfolioUUID;
   }
    
   /**
    * Gets the ProdPortfolio Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ProdPortfolio Code or null.
    */
   public final String getProdPortfolioCode( int index )
   {
      return _ProdPortfolioCode[index];
   }
    
   /**
    * Gets the ProdPortfolio Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ProdPortfolio Code or the specified default value.
    */
   public final String getProdPortfolioCode( int index, String defaultValue )
   {
      return _ProdPortfolioCode[index] == null ? defaultValue : _ProdPortfolioCode[index];
   }
    
   /**
    * Gets the array of ProdPortfolio Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ProdPortfolio Code values.
    */
   public final String[] getProdPortfolioCodeArray()
   {
      return _ProdPortfolioCode;
   }
    
   /**
    * Gets the ProdPortfolio Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ProdPortfolio Name or null.
    */
   public final String getProdPortfolioName( int index )
   {
      return _ProdPortfolioName[index];
   }
    
   /**
    * Gets the ProdPortfolio Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ProdPortfolio Name or the specified default value.
    */
   public final String getProdPortfolioName( int index, String defaultValue )
   {
      return _ProdPortfolioName[index] == null ? defaultValue : _ProdPortfolioName[index];
   }
    
   /**
    * Gets the array of ProdPortfolio Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ProdPortfolio Name values.
    */
   public final String[] getProdPortfolioNameArray()
   {
      return _ProdPortfolioName;
   }
    
   /**
    * Gets the Effective Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Effective Date or null.
    */
   public final Date getDeff( int index )
   {
      return _Deff[index];
   }
    
   /**
    * Gets the Effective Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Effective Date or the specified default value.
    */
   public final Date getDeff( int index, Date defaultValue )
   {
      return _Deff[index] == null ? defaultValue : _Deff[index];
   }
    
   /**
    * Gets the array of Effective Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Effective Date values.
    */
   public final Date[] getDeffArray()
   {
      return _Deff;
   }
    
   /**
    * Gets the Stop Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Stop Date or null.
    */
   public final Date getStopDate( int index )
   {
      return _StopDate[index];
   }
    
   /**
    * Gets the Stop Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Stop Date or the specified default value.
    */
   public final Date getStopDate( int index, Date defaultValue )
   {
      return _StopDate[index] == null ? defaultValue : _StopDate[index];
   }
    
   /**
    * Gets the array of Stop Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Stop Date values.
    */
   public final Date[] getStopDateArray()
   {
      return _StopDate;
   }
    
   /**
    * Gets the Flag indicating if seq funds are parts of the portfolio field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Flag indicating if seq funds are parts of the portfolio or null.
    */
   public final Boolean getSegFundIncl( int index )
   {
      return _SegFundIncl[index];
   }
    
   /**
    * Gets the Flag indicating if seq funds are parts of the portfolio field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag indicating if seq funds are parts of the portfolio or the specified default value.
    */
   public final boolean getSegFundIncl( int index, boolean defaultValue )
   {
      return _SegFundIncl[index] == null ? defaultValue : _SegFundIncl[index].booleanValue();
   }
    
   /**
    * Gets the array of Flag indicating if seq funds are parts of the portfolio fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Flag indicating if seq funds are parts of the portfolio values.
    */
   public final Boolean[] getSegFundInclArray()
   {
      return _SegFundIncl;
   }
    
   /**
    * Gets the Flag that indicates if Shareholder Group has Portfolio with Commitment Fund field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Flag that indicates if Shareholder Group has Portfolio with Commitment Fund or null.
    */
   public final Boolean getCommitApplicable( int index )
   {
      return _CommitApplicable[index];
   }
    
   /**
    * Gets the Flag that indicates if Shareholder Group has Portfolio with Commitment Fund field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag that indicates if Shareholder Group has Portfolio with Commitment Fund or the specified default value.
    */
   public final boolean getCommitApplicable( int index, boolean defaultValue )
   {
      return _CommitApplicable[index] == null ? defaultValue : _CommitApplicable[index].booleanValue();
   }
    
   /**
    * Gets the array of Flag that indicates if Shareholder Group has Portfolio with Commitment Fund fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Flag that indicates if Shareholder Group has Portfolio with Commitment Fund values.
    */
   public final Boolean[] getCommitApplicableArray()
   {
      return _CommitApplicable;
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
      decodeMoreAvailableField( responseBuffer );
      decodeNextKeyField( responseBuffer );
                  
      // multi-record section
      int oldRepeatCount = _RepeatCount;
      decodeRepeatCount( responseBuffer );
      
      _ProdPortfolioUUID = resizeArray( _ProdPortfolioUUID, _RepeatCount );
      _ProdPortfolioCode = resizeArray( _ProdPortfolioCode, _RepeatCount );
      _ProdPortfolioName = resizeArray( _ProdPortfolioName, _RepeatCount );
      _Deff = resizeArray( _Deff, _RepeatCount );
      _StopDate = resizeArray( _StopDate, _RepeatCount );
      _SegFundIncl = resizeArray( _SegFundIncl, _RepeatCount );
      _CommitApplicable = resizeArray( _CommitApplicable, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _ProdPortfolioUUID[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ProdPortfolioCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ProdPortfolioName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Deff[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _StopDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _SegFundIncl[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _CommitApplicable[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      }
      

   }

}
      
