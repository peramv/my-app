import java.io.IOException;
import java.text.ParseException;
import java.util.Date;
import com.ifds.iFast.api.*;

public class TestClient 
{
   // Logon context members variables
   private String _userId;
   private String _sessionId;
   private String _languageCode;
   private String _companyId;

   // target server member variables
   private final String _host;
   private final int _port;

   /**
    * Main method for client program.
    * 
    * @param args
    */
   public static void main(String args[]) 
   {

      try
      {

         TestClient client = new TestClient( "cfxint", 2790 );
         if ( client.logon( "vistest1", "test11" ) )
         {
            client.accountDetails( "1008001", new Date() );
            client.logoff();
         }

      }
      catch ( Exception e )
      {
         System.err.println( e.toString() );
         e.printStackTrace();
      }
      
   }

   /**
    * TestClient constructor.
    * 
    * @param host   IP address of targer host
    * @param port   Port of targer host.
    */
   public TestClient( String host, int port )
   {
      _host = host;
      _port = port;

   }

   /**
    * Performs the logon request and print response to the standard output.
    * 
    * @param userId   User Identifier.
    * @param password User password.
    * @return true if sucessfull, false oterwise
    * @exception IOException
    * @exception ParseException
    * @exception IFastSystemResponseException
    */
   public final boolean logon( String userId, String password ) throws IOException, ParseException, IFastSystemResponseException
   {

      System.out.println("Logon(" + _host + ":" + _port + "):");
      
      _userId = userId;

      LogonView logonView = new LogonView();
      
      LogonRequest logonReq = logonView.getRequest();
      logonReq.setUser_Id( userId );
      logonReq.setPassword( password );

      if ( !logonView.receiveAll( _host, _port ) )
      {
         System.err.println( "Unable to logon [" +
                             logonView.getErrorResponse().getCode() +
                             "]: " + 
                             logonView.getErrorResponse().getMessage() );
         return false;
      }

      _sessionId    = logonView.getSessionId();
      _languageCode = logonView.getLanguageCode();
      
      System.out.println( logonView.getUsername() );
      System.out.println( _sessionId );
      System.out.println( _languageCode );
      System.out.println();

      for ( int i=0; i <logonView.getRepeatCount(); i++ )
      {
         System.out.println( logonView.getCompanyId(i) );
         System.out.println( logonView.getCompanyName(i) );
         System.out.println( logonView.getCoClientID(i) );

         System.out.println();
         
      }
      _companyId = logonView.getCompanyId(0);

      return true;

   }

   /**
    * Performs the Account Details request and print response to the standard output.
    * 
    * @param accountNumber
    *                 Account number for request.
    * @param asOfDate As-of-date for the request.
    * @return true if sucessfull, false oterwise
    * @exception IOException
    * @exception ParseException
    * @exception IFastSystemResponseException
    */
   public final boolean accountDetails( String accountNumber, Date asOfDate ) throws IOException, ParseException, IFastSystemResponseException
   {

      System.out.println("Account Details(" + _host + ":" + _port + "):");
      
      AccountDetailsAndHoldingsView acctDetailsView = new AccountDetailsAndHoldingsView();
      
      AccountDetailsAndHoldingsRequest acctDetailsReq = acctDetailsView.getRequest();
      acctDetailsReq.setSessionId( _sessionId );
      acctDetailsReq.setUser_Id( _userId );
      acctDetailsReq.setLanguageCode( _languageCode );
      acctDetailsReq.setCompanyId( _companyId );
      acctDetailsReq.setAccountNum( accountNumber );
      acctDetailsReq.setAsOfDate( asOfDate );

      if ( !acctDetailsView.receive( _host, _port ) )
      {
         if ( acctDetailsView.getErrorResponse().getCode() == IFastErrorResponse.DATA_NOT_FOUND )
         {
            System.out.println( "No data avaialble for the given criteria." );
            return true;
         }
         System.err.println( "Unable to logoff [" +
                             acctDetailsView.getErrorResponse().getCode() +
                             "]: " + 
                             acctDetailsView.getErrorResponse().getMessage() );
         return false;
      }

      System.out.println( acctDetailsView.getAcctType() );
      System.out.println( acctDetailsView.getAcctTypeDesc() );
      System.out.println( acctDetailsView.getAccountBalance() );
      System.out.println();
      
      for ( int i=0; i <acctDetailsView.getRepeatCount(); i++ )
      {
         System.out.println( acctDetailsView.getFundCode(i) );
         System.out.println( acctDetailsView.getClassCode(i) );
         System.out.println( acctDetailsView.getSettledUnits(i) );
         System.out.println( acctDetailsView.getSettledValue(i) );
         System.out.println();
      }

      return true;
   }
   
      
   /**
    * Performs the logoff request and print response to the standard output.
    * 
    * @return true if sucessfull, false oterwise
    * @exception IOException
    * @exception ParseException
    * @exception IFastSystemResponseException
    */
   public final boolean logoff() throws IOException, ParseException, IFastSystemResponseException
   {
      System.out.println("Logoff(" + _host + ":" + _port + "):");
      
      LogoffView logoffView = new LogoffView();
      
      LogoffRequest logoffReq = logoffView.getRequest();
      logoffReq.setSessionId( _sessionId );
      logoffReq.setUser_Id( _userId );
      logoffReq.setLanguageCode( _languageCode );

      if ( !logoffView.receiveAll( _host, _port ) )
      {
         System.err.println( "Unable to logoff [" +
                             logoffView.getErrorResponse().getCode() +
                             "]: " + 
                             logoffView.getErrorResponse().getMessage() );
         return false;
      }

      System.out.println( logoffView.getLogoutMsg() );
      
      return true;

   }
}
