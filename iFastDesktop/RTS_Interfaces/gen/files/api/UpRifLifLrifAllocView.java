
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Account RRIF/LIF/LRIF Allocations  Maint view.
 * For additional view information see <A HREF="../../../../viewspecs/UpRifLifLrifAlloc.doc">UpRifLifLrifAlloc.doc</A>.
 * 
 * @author RTS Generated
 */
public class UpRifLifLrifAllocView extends IFastView implements Serializable
{

   /**
    * Market Value of the Plan member variable.
    */
   private String _NowPlanValue = null;
   
   /**
    * Previous Year End Plan Value member variable.
    */
   private String _PYEPlanValue = null;
   
   /**
    * Calc Mandatory Payment per Year member variable.
    */
   private String _CalcMandYr = null;
   
   /**
    * Calc Max Payment per Year member variable.
    */
   private String _CalcMaxYr = null;
   
   /**
    * Payment Period member variable.
    */
   private Integer _PayTerm = null;
   
   /**
    * Number of years to factor payment amounts member variable.
    */
   private String _Factor = null;
   
   /**
    * Mandatory Yearly Amount calculated by RRIF00C.P member variable.
    */
   private String _MandAmtYrSysCalc = null;
   
   /**
    * Maximum Yearly Amount calculated by RRIF00C.P member variable.
    */
   private String _MaxAmtYrSysCalc = null;
   
   /**
    * Current account value calculated by RRIF001.P member variable.
    */
   private String _AcctValue = null;
   
   /**
    * Upper limit for regular LIF/LRIF payment calculated in RRIF00.EH member variable.
    */
   private String _TotRedem = null;
   
   /**
    * Mandatory Amount per Pay calculated by   RRIF00C.P member variable.
    */
   private String _MandAmtPaySysCalc = null;
   
   /**
    * Amount recalculated by the system member variable.
    */
   private String _AmountSysCalc = null;
   
   /**
    * Provincial Tax calc by system member variable.
    */
   private String _ProvRateSysCalc = null;
   
   /**
    * Federal Tax calc by system member variable.
    */
   private String _FedRateSysCalc = null;
   
   /**
    * Net amount calc by system member variable.
    */
   private String _NetAmountSysCalc = null;
   
   /**
    * Calculated min percentage allowable member variable.
    */
   private String _MinPrevYrBalPctSysCalc = null;
   
   /**
    * Calculated max percentage allowable member variable.
    */
   private String _MaxPrevYrBalPctSysCalc = null;
   
   /**
    * PY Unsed Maximun Amount member variable.
    */
   private String _PYUnusedMaxSysCalc = null;
   
   /**
    * Flag indicates if the original plan date is enable member variable.
    */
   private Boolean _OrigPlanDeffApplied = null;
   

   /**
    * Constructs the UpRifLifLrifAllocView object.
    * 
    */
   public UpRifLifLrifAllocView()
   {
      super ( new UpRifLifLrifAllocRequest() );
   }

   /**
    * Constructs the UpRifLifLrifAllocView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public UpRifLifLrifAllocView( String hostEncoding )
   {
      super ( new UpRifLifLrifAllocRequest( hostEncoding ) );
   }

   /**
    * Gets the UpRifLifLrifAllocRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The UpRifLifLrifAllocRequest object.
    */
   public final UpRifLifLrifAllocRequest getRequest()
   {
      return (UpRifLifLrifAllocRequest)getIFastRequest();
   }
        
   /**
    * Gets the Market Value of the Plan field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Market Value of the Plan or null.
    */
   public final String getNowPlanValue()
   {
      return _NowPlanValue;
   }
	
   /**
    * Gets the Market Value of the Plan field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Market Value of the Plan or the specified default value.
    */
   public final String getNowPlanValue( String defaultValue )
   {
      return _NowPlanValue == null ? defaultValue : _NowPlanValue;
   }
                  
   /**
    * Gets the Previous Year End Plan Value field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Previous Year End Plan Value or null.
    */
   public final String getPYEPlanValue()
   {
      return _PYEPlanValue;
   }
	
   /**
    * Gets the Previous Year End Plan Value field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Previous Year End Plan Value or the specified default value.
    */
   public final String getPYEPlanValue( String defaultValue )
   {
      return _PYEPlanValue == null ? defaultValue : _PYEPlanValue;
   }
                  
   /**
    * Gets the Calc Mandatory Payment per Year field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Calc Mandatory Payment per Year or null.
    */
   public final String getCalcMandYr()
   {
      return _CalcMandYr;
   }
	
   /**
    * Gets the Calc Mandatory Payment per Year field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Calc Mandatory Payment per Year or the specified default value.
    */
   public final String getCalcMandYr( String defaultValue )
   {
      return _CalcMandYr == null ? defaultValue : _CalcMandYr;
   }
                  
   /**
    * Gets the Calc Max Payment per Year field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Calc Max Payment per Year or null.
    */
   public final String getCalcMaxYr()
   {
      return _CalcMaxYr;
   }
	
   /**
    * Gets the Calc Max Payment per Year field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Calc Max Payment per Year or the specified default value.
    */
   public final String getCalcMaxYr( String defaultValue )
   {
      return _CalcMaxYr == null ? defaultValue : _CalcMaxYr;
   }
                  
   /**
    * Gets the Payment Period field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Payment Period or null.
    */
   public final Integer getPayTerm()
   {
      return _PayTerm;
   }
	
   /**
    * Gets the Payment Period field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Payment Period or the specified default value.
    */
   public final int getPayTerm( int defaultValue )
   {
      return _PayTerm == null ? defaultValue : _PayTerm.intValue();
   }
                  
   /**
    * Gets the Number of years to factor payment amounts field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Number of years to factor payment amounts or null.
    */
   public final String getFactor()
   {
      return _Factor;
   }
	
   /**
    * Gets the Number of years to factor payment amounts field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Number of years to factor payment amounts or the specified default value.
    */
   public final String getFactor( String defaultValue )
   {
      return _Factor == null ? defaultValue : _Factor;
   }
                  
   /**
    * Gets the Mandatory Yearly Amount calculated by RRIF00C.P field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Mandatory Yearly Amount calculated by RRIF00C.P or null.
    */
   public final String getMandAmtYrSysCalc()
   {
      return _MandAmtYrSysCalc;
   }
	
   /**
    * Gets the Mandatory Yearly Amount calculated by RRIF00C.P field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Mandatory Yearly Amount calculated by RRIF00C.P or the specified default value.
    */
   public final String getMandAmtYrSysCalc( String defaultValue )
   {
      return _MandAmtYrSysCalc == null ? defaultValue : _MandAmtYrSysCalc;
   }
                  
   /**
    * Gets the Maximum Yearly Amount calculated by RRIF00C.P field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Maximum Yearly Amount calculated by RRIF00C.P or null.
    */
   public final String getMaxAmtYrSysCalc()
   {
      return _MaxAmtYrSysCalc;
   }
	
   /**
    * Gets the Maximum Yearly Amount calculated by RRIF00C.P field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Maximum Yearly Amount calculated by RRIF00C.P or the specified default value.
    */
   public final String getMaxAmtYrSysCalc( String defaultValue )
   {
      return _MaxAmtYrSysCalc == null ? defaultValue : _MaxAmtYrSysCalc;
   }
                  
   /**
    * Gets the Current account value calculated by RRIF001.P field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Current account value calculated by RRIF001.P or null.
    */
   public final String getAcctValue()
   {
      return _AcctValue;
   }
	
   /**
    * Gets the Current account value calculated by RRIF001.P field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Current account value calculated by RRIF001.P or the specified default value.
    */
   public final String getAcctValue( String defaultValue )
   {
      return _AcctValue == null ? defaultValue : _AcctValue;
   }
                  
   /**
    * Gets the Upper limit for regular LIF/LRIF payment calculated in RRIF00.EH field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Upper limit for regular LIF/LRIF payment calculated in RRIF00.EH or null.
    */
   public final String getTotRedem()
   {
      return _TotRedem;
   }
	
   /**
    * Gets the Upper limit for regular LIF/LRIF payment calculated in RRIF00.EH field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Upper limit for regular LIF/LRIF payment calculated in RRIF00.EH or the specified default value.
    */
   public final String getTotRedem( String defaultValue )
   {
      return _TotRedem == null ? defaultValue : _TotRedem;
   }
                  
   /**
    * Gets the Mandatory Amount per Pay calculated by   RRIF00C.P field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Mandatory Amount per Pay calculated by   RRIF00C.P or null.
    */
   public final String getMandAmtPaySysCalc()
   {
      return _MandAmtPaySysCalc;
   }
	
   /**
    * Gets the Mandatory Amount per Pay calculated by   RRIF00C.P field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Mandatory Amount per Pay calculated by   RRIF00C.P or the specified default value.
    */
   public final String getMandAmtPaySysCalc( String defaultValue )
   {
      return _MandAmtPaySysCalc == null ? defaultValue : _MandAmtPaySysCalc;
   }
                  
   /**
    * Gets the Amount recalculated by the system field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Amount recalculated by the system or null.
    */
   public final String getAmountSysCalc()
   {
      return _AmountSysCalc;
   }
	
   /**
    * Gets the Amount recalculated by the system field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Amount recalculated by the system or the specified default value.
    */
   public final String getAmountSysCalc( String defaultValue )
   {
      return _AmountSysCalc == null ? defaultValue : _AmountSysCalc;
   }
                  
   /**
    * Gets the Provincial Tax calc by system field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Provincial Tax calc by system or null.
    */
   public final String getProvRateSysCalc()
   {
      return _ProvRateSysCalc;
   }
	
   /**
    * Gets the Provincial Tax calc by system field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Provincial Tax calc by system or the specified default value.
    */
   public final String getProvRateSysCalc( String defaultValue )
   {
      return _ProvRateSysCalc == null ? defaultValue : _ProvRateSysCalc;
   }
                  
   /**
    * Gets the Federal Tax calc by system field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Federal Tax calc by system or null.
    */
   public final String getFedRateSysCalc()
   {
      return _FedRateSysCalc;
   }
	
   /**
    * Gets the Federal Tax calc by system field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Federal Tax calc by system or the specified default value.
    */
   public final String getFedRateSysCalc( String defaultValue )
   {
      return _FedRateSysCalc == null ? defaultValue : _FedRateSysCalc;
   }
                  
   /**
    * Gets the Net amount calc by system field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Net amount calc by system or null.
    */
   public final String getNetAmountSysCalc()
   {
      return _NetAmountSysCalc;
   }
	
   /**
    * Gets the Net amount calc by system field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Net amount calc by system or the specified default value.
    */
   public final String getNetAmountSysCalc( String defaultValue )
   {
      return _NetAmountSysCalc == null ? defaultValue : _NetAmountSysCalc;
   }
                  
   /**
    * Gets the Calculated min percentage allowable field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Calculated min percentage allowable or null.
    */
   public final String getMinPrevYrBalPctSysCalc()
   {
      return _MinPrevYrBalPctSysCalc;
   }
	
   /**
    * Gets the Calculated min percentage allowable field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Calculated min percentage allowable or the specified default value.
    */
   public final String getMinPrevYrBalPctSysCalc( String defaultValue )
   {
      return _MinPrevYrBalPctSysCalc == null ? defaultValue : _MinPrevYrBalPctSysCalc;
   }
                  
   /**
    * Gets the Calculated max percentage allowable field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Calculated max percentage allowable or null.
    */
   public final String getMaxPrevYrBalPctSysCalc()
   {
      return _MaxPrevYrBalPctSysCalc;
   }
	
   /**
    * Gets the Calculated max percentage allowable field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Calculated max percentage allowable or the specified default value.
    */
   public final String getMaxPrevYrBalPctSysCalc( String defaultValue )
   {
      return _MaxPrevYrBalPctSysCalc == null ? defaultValue : _MaxPrevYrBalPctSysCalc;
   }
                  
   /**
    * Gets the PY Unsed Maximun Amount field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the PY Unsed Maximun Amount or null.
    */
   public final String getPYUnusedMaxSysCalc()
   {
      return _PYUnusedMaxSysCalc;
   }
	
   /**
    * Gets the PY Unsed Maximun Amount field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the PY Unsed Maximun Amount or the specified default value.
    */
   public final String getPYUnusedMaxSysCalc( String defaultValue )
   {
      return _PYUnusedMaxSysCalc == null ? defaultValue : _PYUnusedMaxSysCalc;
   }
                  
   /**
    * Gets the Flag indicates if the original plan date is enable field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Flag indicates if the original plan date is enable or null.
    */
   public final Boolean getOrigPlanDeffApplied()
   {
      return _OrigPlanDeffApplied;
   }
	
   /**
    * Gets the Flag indicates if the original plan date is enable field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag indicates if the original plan date is enable or the specified default value.
    */
   public final boolean getOrigPlanDeffApplied( boolean defaultValue )
   {
      return _OrigPlanDeffApplied == null ? defaultValue : _OrigPlanDeffApplied.booleanValue();
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
      _NowPlanValue = responseBuffer.decodeString(responseBuffer.getNextField());
      _PYEPlanValue = responseBuffer.decodeString(responseBuffer.getNextField());
      _CalcMandYr = responseBuffer.decodeString(responseBuffer.getNextField());
      _CalcMaxYr = responseBuffer.decodeString(responseBuffer.getNextField());
      _PayTerm = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _Factor = responseBuffer.decodeString(responseBuffer.getNextField());
      _MandAmtYrSysCalc = responseBuffer.decodeString(responseBuffer.getNextField());
      _MaxAmtYrSysCalc = responseBuffer.decodeString(responseBuffer.getNextField());
      _AcctValue = responseBuffer.decodeString(responseBuffer.getNextField());
      _TotRedem = responseBuffer.decodeString(responseBuffer.getNextField());
      _MandAmtPaySysCalc = responseBuffer.decodeString(responseBuffer.getNextField());
      _AmountSysCalc = responseBuffer.decodeString(responseBuffer.getNextField());
      _ProvRateSysCalc = responseBuffer.decodeString(responseBuffer.getNextField());
      _FedRateSysCalc = responseBuffer.decodeString(responseBuffer.getNextField());
      _NetAmountSysCalc = responseBuffer.decodeString(responseBuffer.getNextField());
      _MinPrevYrBalPctSysCalc = responseBuffer.decodeString(responseBuffer.getNextField());
      _MaxPrevYrBalPctSysCalc = responseBuffer.decodeString(responseBuffer.getNextField());
      _PYUnusedMaxSysCalc = responseBuffer.decodeString(responseBuffer.getNextField());
      _OrigPlanDeffApplied = responseBuffer.decodeBoolean(responseBuffer.getNextField());
                  

   }

}
      
